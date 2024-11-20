
CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: userprog

userprog: ioperm.c
	$(CC) $(CFLAGS) -o userprog ioperm.c

clean veryclean:
	$(RM) userprog

