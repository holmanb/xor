.PHONY:
all:
	$(CC) -g xor.c -o xor

.PHONY:
clean:
	rm xor

.PHONY:
test: all
	./test.sh
