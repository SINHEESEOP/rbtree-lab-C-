#.PHONY: clean
#
#CFLAGS=-Wall -g
#
#driver: driver.o rbtree.o
#
#clean:
#	rm -f driver *.o

.PHONY: clean

CFLAGS=-Wall -g

driver: driver.o rbtree.o
	$(CC) $(CFLAGS) -o driver driver.o rbtree.o

driver.o: driver.c rbtree.h
	$(CC) $(CFLAGS) -c driver.c

rbtree.o: rbtree.c rbtree.h
	$(CC) $(CFLAGS) -c rbtree.c

clean:
	rm -f driver *.o

