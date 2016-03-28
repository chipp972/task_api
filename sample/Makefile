CC=gcc
CFLAGS=-Wall -g -I../include
LDFLAGS=-L../lib -Wl,-rpath=../lib -ltask

EXEC=sample

all: $(EXEC)

sample: sample.o samplerTask.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -exec rm -f {} \;
	find . -name "*~" -exec rm -f {} \;

mrproper: clean
	rm -f $(EXEC)
