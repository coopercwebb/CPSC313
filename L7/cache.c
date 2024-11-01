#include "cache.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Initialize a new cache set with the given associativity and index of the
 * first cache line.
 */
static void cache_set_init(cache_set_t *cache_set, size_t associativity,
                           cache_line_t *lines) {
  cache_set->lines = lines;
  cache_set->lru_list = malloc(associativity * sizeof(size_t));
  cache_set->num_marked = 0;

  for (int i = 0; i < associativity; i++) {
    cache_set->lru_list[i] = i;
    lines[i].is_valid = false;
  }
}

/*
 * Given a value n which is a power of 2 (for example, a block size or a
 * number of sets in a cache), calculate log_2 of n.
 */
static size_t logbase2(size_t value) {
  size_t ans = 0;
  while (value > 1) {
    ans++;
    value >>= 1;
  }
  return ans;
}

/*
 * Given a number of bits, return a mask that many bits wide.
 */
static uint64_t maskbits(int nbits) { return (1L << nbits) - 1; }

/*
 * Create a new cache that contains a total of num_bytes bytes, divided into
 * lines each of which is block_size bytes long, with the given associativity,
 * and the given set of cache policies for replacement and write operations.
 */
simcache_t *cache_new(size_t num_bytes, size_t associativity, size_t block_size,
                      uint8_t policies) {

  // Create the cache and initialize constant fields.
  simcache_t *cache = (simcache_t *)malloc(sizeof(simcache_t));
  cache->age = 0;
  cache->access_count = 0;
  cache->miss_count = 0;
  cache->policies = policies;

  // Initialize size fields.
  cache->line_size = block_size;
  cache->num_lines = num_bytes / block_size;
  cache->associativity = associativity;
  cache->num_sets = cache->num_lines / associativity;

  // Initialize shifts and masks in cache structure
  uint64_t offset_mask, index_mask;
  unsigned int offset_bits, index_bits;

  offset_bits = logbase2(block_size);
  offset_mask = maskbits(offset_bits);
  index_bits = logbase2(cache->num_sets);
  index_mask = maskbits(index_bits);

  // We shift by the number of bits in the offset to get
  // to the index bits.
  cache->block_offset_mask = offset_mask;
  cache->cache_index_shift = offset_bits;
  cache->cache_index_mask = index_mask << offset_bits;

  // We shift by the number of offset bits and index bits
  // to get the tag bits.
  cache->tag_shift = offset_bits + index_bits;
  cache->tag_mask = maskbits(sizeof(uintptr_t) - cache->tag_shift)
                    << cache->tag_shift;

  // Allocate the cache memory
  cache->memory = malloc(num_bytes);
  uint8_t *memory = cache->memory;

  // Initialize cache lines.
  cache->lines = (cache_line_t *)calloc(cache->num_lines, sizeof(cache_line_t));
  for (size_t i = 0; i < cache->num_lines; i++) {
    cache->lines[i].block = memory;
    memory += cache->line_size;
  }

  // Initialize cache sets.
  cache->sets = (cache_set_t *)calloc(cache->num_sets, sizeof(cache_set_t));
  size_t first_index = 0;
  for (size_t i = 0; i < cache->num_sets; i++) {
    cache_set_init(&cache->sets[i], associativity, cache->lines + first_index);
    first_index += associativity;
  }

  return cache;
}

/**
 * Frees all memory allocated for a cache.
 */
void cache_free(simcache_t *cache) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */
}

/*
 * Determine whether or not a cache line is valid for a given tag.
 */
bool cache_line_is_valid_tag_matches(cache_line_t *cache_line, uintptr_t tag) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */
  if (cache_line->is_valid) {
    return ((cache_line->tag == tag));
  }
  return 0;
}

/*
 * Return uint64_t integer data from a cache line.
 */
uint64_t cache_line_retrieve_data(cache_line_t *cache_line, size_t offset) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */
  return (*((uint64_t *)(cache_line->block + offset)));
}

/*
 * Move the cache lines inside a cache set so the cache line with the
 * given index is tagged as the most recently used one. The most
 * recently used cache line will be the 0'th one in the set, the
 * second most recently used cache line will be next, etc.  Cache
 * lines whose valid bit is 0 will occur after all cache lines whose
 * valid bit is 1.
 */
static void cache_line_make_mru(simcache_t *cache, cache_set_t *cache_set,
                                size_t line_index) {
  size_t index_of_line_index = -1;
  for (size_t i = 0; i < cache->associativity; i++) {
    if (cache_set->lru_list[i] == line_index) {
      index_of_line_index = i;
      break;
    }
  }

  for (size_t i = index_of_line_index + 1; i < cache->associativity; i++) {
    cache_set->lru_list[i - 1] = cache_set->lru_list[i];
  }
  cache_set->lru_list[cache->associativity - 1] = line_index;
}

/*
 * Compute a cache line's priority (age + use count).
 */
static uint32_t get_priority(cache_line_t *cache_line) {
  return cache_line->age + cache_line->use_count;
}

/*
 * Order the cache lines in the set (using cache_set->lru_list) so they occur in
 * order of decreasing age + use_count. Because we only ever update one cache
 * line at a time, it suffices to run the inner loop of insertion sort (sorting
 * in decreasing order) to update the sorted order.
 */
static void cache_lines_sort(simcache_t *cache, cache_set_t *cache_set,
                             size_t line_index) {
  size_t index_of_line_index = -1;
  for (size_t i = 0; i < cache->associativity; i++) {
    if (cache_set->lru_list[i] == line_index) {
      index_of_line_index = i;
      break;
    }
  }

  if (index_of_line_index == -1) {
    fprintf(stderr, "Error: index of line_index is -1\n");
  }

  uint32_t current_priority = get_priority(cache_set->lines + line_index);

  int j = index_of_line_index - 1;
  while (j >= 0 && get_priority(cache_set->lines + cache_set->lru_list[j]) <=
                       current_priority) {
    cache_set->lru_list[j + 1] = cache_set->lru_list[j];
    j--;
  }
  cache_set->lru_list[j + 1] = line_index;
}

/*
 * Setup a cache line for new data using the LFU policy.
 */
static void lfu_cache_line_setup(simcache_t *cache, cache_set_t *cache_set,
                                 size_t line_index, int32_t count) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */
  return; // Added to remove warning.
}

/*
 * Retrieve a matching cache line from a set, if one exists.
 */
cache_line_t *cache_set_find_line_matching(simcache_t *cache,
                                           cache_set_t *cache_set,
                                           uintptr_t tag) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */
  /* Don't forget to make appropriate updates to *all* the metadata in the
   * cache line (not only the tag).
   */
  cache_line_t *cur_line = cache_set->lines;
  uint64_t cur_set = 0;
  while (cur_set < cache->num_sets) {
    if (cur_line->tag == tag && cur_line->is_valid) {
      cur_line->age = cache->age;
      if (cache->policies == CACHE_REPLACEMENTPOLICY_LFU) {
        cur_line->use_count++;
        // sort lru_list, new priorities
        cache_lines_sort(cache, cache_set, cur_set);
      }
      return cur_line;
    }
    cur_line++;
    cur_set++;
  }
  return NULL;
}

/*
 * Function to choose a random unmarked line from the cache. If all lines are
 * marked, then it unmarks them all first.
 */
size_t choose_unmarked_cache_line(simcache_t *cache, cache_set_t *cache_set,
                                  func_t generate_random_number) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */
  /* MARKING LINES IS USE_COUNT, 1 is marked, 0 is unmarked */
  cache_line_t *cur_line = cache_set->lines;
  uint64_t cur_set = 0;

  if (cache_set->num_marked >= cache->num_sets) {
    // unmark all lines
    cache_set->num_marked = 0;
    while (cur_set < cache->num_sets) {
      cur_line->use_count = 0;
      cur_line++;
      cur_set++;
    }
  }

  // return (generate_random_number() % cache->num_sets);
  return (generate_random_number() % (cache->num_sets - cache_set->num_marked));
}

/*
 * Function to find a cache line to use for new data. Uses either a
 * line not being used, or a suitable line to be replaced, based on
 * the cache's replacement policy.
 */
cache_line_t *find_available_cache_line(simcache_t *cache,
                                        cache_set_t *cache_set,
                                        func_t generate_random_number) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */
  /* If the cache replacement policy is RANDOMIZED_MARKING, don't forget to
   * mark the line. To generate a random number in the range [0, n), you can
   * use "generate_random_number() % n". If the cache replacement policy is
   * LFU, don't forget to implement dynamic aging correctly. In both cases,
   * the is_valid flag needs to be set to true when this function returns in
   * order for our test cases to pass.
   */

  //  TODO: NEED TO SET VALID FLAG

  // first iterate through and find invalid lines, and then use replacement
  // policy if nec.

  cache_line_t *cur_line = cache_set->lines;
  uint64_t cur_set = 0;

  while (cur_set < cache->num_sets) {
    if (!cur_line->is_valid) {
      // found avail line
      cur_line->use_count = 1;
      cur_line->is_valid = 1;
      if (cache->policies == CACHE_REPLACEMENTPOLICY_RANDOMIZED_MARKING) {
        cache_set->num_marked++;
      } else if (cache->policies == CACHE_REPLACEMENTPOLICY_LFU) {
        cur_line->age = cache->age;
        cache_lines_sort(cache, cache_set, cur_set);
      }
      return cur_line;
    }
    cur_line++;
    cur_set++;
  }

  // all lines are currently taken, fallback to replacement policy

  size_t sel_index;
  cache_line_t *sel_line;

  if (cache->policies == CACHE_REPLACEMENTPOLICY_RANDOMIZED_MARKING) {
    sel_index =
        choose_unmarked_cache_line(cache, cache_set, generate_random_number);
    sel_line = cache_set->lines + sel_index;
    while (sel_line->use_count) {
      sel_line++;
      sel_index++;
      if (sel_index == cache->num_sets) {
        sel_line = cache_set->lines;
        sel_index = 0;
      }
    }
    sel_line->use_count++;
  } else if (cache->policies == CACHE_REPLACEMENTPOLICY_LFU) {
    // evict last item in lru_list, reset age and use_count
    sel_index = *(cache_set->lru_list + (cache->num_sets - 1));
    sel_line = cache_set->lines + sel_index;
    // We then update the age of the cache to be the value of age + use_count
    // from the evicted cache line.
    cache->age = sel_line->age + sel_line->use_count;
    sel_line->use_count = 1;
    sel_line->age = cache->age;
    cache_lines_sort(cache, cache_set, sel_index);
  }

  cache_set->num_marked++;
  return sel_line;
}

/*
 * Add a block to a given cache set.
 */
static cache_line_t *cache_set_add(simcache_t *cache, cache_set_t *cache_set,
                                   uintptr_t address, uintptr_t tag,
                                   func_t generate_random_number) {

  // First locate the cache line to use.
  cache_line_t *line =
      find_available_cache_line(cache, cache_set, generate_random_number);

  // Now set it up.
  line->tag = tag;
  memcpy(line->block, (void *)(address & ~cache->block_offset_mask),
         cache->line_size);

  // And return it.
  return line;
}

/*
 * Read a single uint64_t integer from the cache.
 */
uint64_t cache_read(simcache_t *cache, uintptr_t address,
                    func_t generate_random_number) {
  /* TODO: TO BE COMPLETED BY THE STUDENT */

  // cache_line_retrieve_data(cache_line_t *cache_line, size_t offset)

  // need to determine index, aka cache set number
  size_t index =
      (address & cache->cache_index_mask) >> cache->cache_index_shift;
  size_t offset = (address & cache->block_offset_mask);

  uintptr_t tag = (address & cache->tag_mask) >> cache->tag_shift;

  cache_set_t *indexed_set = cache->sets + index;

  // need to iterate throught the set and determine where tag matches
  cache_line_t *sel_line =
      cache_set_find_line_matching(cache, indexed_set, tag);

  cache->access_count++;
  if (sel_line) {
    return cache_line_retrieve_data(sel_line, offset);
  }

  // integer was not found in cache, read in int from address, store into
  // cacheline
  cache->miss_count++;

  // we have the indexed set, use functions
  cache_set_add(cache, indexed_set, address, tag, generate_random_number);

  // For testing, *(int*)x
  return *(int *)address;
}

/*
 * Write a single integer to the cache.
 */
void cache_write(simcache_t *cache, uintptr_t address, uint64_t value,
                 func_t generate_random_number) {
  /* TODO: OPTIONAL FUNCTION, YOU ARE NOT REQUIRED TO IMPLEMENT IT */
}

/*
 * Return the number of cache misses since the cache was created.
 */
uint32_t cache_miss_count(simcache_t *cache) { return cache->miss_count; }

/*
 * Return the number of cache accesses since the cache was created.
 */
uint32_t cache_access_count(simcache_t *cache) { return cache->access_count; }
