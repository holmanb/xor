/*
 * XOR + one time pad tool. Arbitrary pad size supported using pad wraparound.
 */
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"
#include "string.h"

int main(char argc, char *argv[]){
	if (argc != 3) {
		printf("\tusage: %s [pad_file] [msg_file]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	const int SIZE = 4096;
	const char *pad_path = argv[1];
	const char *msg_path = argv[2];
	char msg, pad;

	FILE *pad_file, *msg_file;
	ssize_t rc;
	pad_file = fopen(pad_path, "r");
	if (!pad_file) {
		fprintf(stderr, "err: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	msg_file = fopen(msg_path, "r");
	if (!msg_file) {
		fprintf(stderr, "err: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	/*
	* Is it fast? No.
	* Does it handle all error conditions? No.
	* Does it work? Presumably.
	*/
	while (1) {
		msg = fgetc(msg_file);
		if (msg == EOF)
			exit(EXIT_SUCCESS);

		pad = fgetc(pad_file);

		/* seek to begining if eof hit */
		if (pad == EOF){
			fseek(pad_file, 0, SEEK_SET);
		}
		fputc(pad^msg, stdout);
	}
	fclose(pad_file);
	fclose(msg_file);
	return 0;
}
