#include "catch.hpp"
#include <string>
extern "C"
{
#include "parsePath.h"
}

using namespace std;

void equals(char *actual, string expected)
{
    REQUIRE(!!actual); // not null
    REQUIRE(string(actual) == expected);
}

TEST_CASE("test1", "[weight=1][part=test]")
{
    char absolutePath[] = "/this/is/an/absolute/path";
    path_parser_t *path_parser = new_path_parser(absolutePath);
    equals(next_path_component(path_parser), "/");
    equals(next_path_component(path_parser), "this");
    equals(next_path_component(path_parser), "is");
    equals(next_path_component(path_parser), "an");
    equals(next_path_component(path_parser), "absolute");
    equals(next_path_component(path_parser), "path");
    REQUIRE(next_path_component(path_parser) == NULL);
    free_path_parser(path_parser);
}

TEST_CASE("test2", "[weight=1][part=test]")
{
    char relativePath[] = "this/is/a/relative/path";
    path_parser_t *path_parser = new_path_parser(relativePath);
    equals(next_path_component(path_parser), "this");
    equals(next_path_component(path_parser), "is");
    equals(next_path_component(path_parser), "a");
    equals(next_path_component(path_parser), "relative");
    equals(next_path_component(path_parser), "path");
    REQUIRE(next_path_component(path_parser) == NULL);
    free_path_parser(path_parser);
}

TEST_CASE("test3", "[weight=1][part=test]")
{
    char pathWithDoubleSlash[] = "a//b";
    path_parser_t *path_parser = new_path_parser(pathWithDoubleSlash);
    equals(next_path_component(path_parser), "a");
    equals(next_path_component(path_parser), "b");
    REQUIRE(next_path_component(path_parser) == NULL);
    free_path_parser(path_parser);
}

TEST_CASE("test4", "[weight=1][part=test]")
{
    char dotPath[] = "./myprog";
    path_parser_t *path_parser = new_path_parser(dotPath);
    equals(next_path_component(path_parser), ".");
    equals(next_path_component(path_parser), "myprog");
    REQUIRE(next_path_component(path_parser) == NULL);
    free_path_parser(path_parser);
}

TEST_CASE("test5", "[weight=1][part=test]")
{
    char dotDotPath[] = "down/../down";
    path_parser_t *path_parser = new_path_parser(dotDotPath);
    equals(next_path_component(path_parser), "down");
    equals(next_path_component(path_parser), "..");
    equals(next_path_component(path_parser), "down");
    REQUIRE(next_path_component(path_parser) == NULL);
    free_path_parser(path_parser);
}

TEST_CASE("test6", "[weight=1][part=test]")
{
    // Write your own tests here. 
}
