PROGRAMS = hextest
INCLUDES = -I.

CFLAGS = -g -O0 -Wall -Wpedantic $(INCLUDES)
OBJFILES = main.o hexdump.o

all: $(PROGRAMS)

deploy:
	cp main.c ../tests/soln_main.c
	cp hexdump.c ../tests/soln_hexdump.c
	cp hexdump.h ../tests/hexdump.h
	cp test-files/* ../workspace/test-files/*

%.o:%.c
	$(CC) $(CFLAGS) -c $<

hextest: $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $(OBJFILES)

clean:
	rm -f $(PROGRAMS) $(OBJFILES) core a.out

