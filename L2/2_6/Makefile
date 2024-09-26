PROG=	tester
SRCS=	main.c insts.c
OBJS=	$(SRCS:.c=.o)
CFLAGS=	-Wall -Werror -g

$(PROG) : $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c


clean:
	rm -rf $(PROG) $(OBJS)
