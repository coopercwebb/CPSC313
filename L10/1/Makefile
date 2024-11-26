CFLAGS = -Wall -Werror -Wextra -Wno-unused-variable -g
OBJECTS = main.o dirLookup.o
all: dirtest

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirtest: $(OBJECTS)
	$(CC) -o dirtest $(CLAGS) $(OBJECTS)

clean:
	rm -rf dirtest $(OBJECTS)
	

