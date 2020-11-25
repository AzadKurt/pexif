CC = gcc
CFLAGS = -Wall -O3
SRCDIR = src/
MAIN = main
PEXIF = pexif
HELPER = helper

all:
	$(CC) $(CFLAGS) $(SRCDIR)$(MAIN).c $(SRCDIR)$(PEXIF).c $(SRCDIR)$(HELPER).c -o $(PEXIF)