
CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: userprog

userprog: prog.c
	$(CC) $(CFLAGS) -o userprog prog.c

clean veryclean:
	$(RM) userprog

