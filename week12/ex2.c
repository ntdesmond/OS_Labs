#include <signal.h> // For handling CTRL+C (SIGINT)
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int interrupted = 0;

void interrupt(int sig) {
	interrupted = 1;
}

int main(int argc, char *argv[])
{
	// open the files given in args
	int *files = malloc((argc - 1) * sizeof(int));
	for (int i = 0; i < argc - 1; i++) {
		files[i] = open(
				argv[i + 1],
				O_CREAT | O_APPEND | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
		);
	}

	// Set SIGINT handler
	struct sigaction action;
	action.sa_handler = interrupt;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);

	// read stdin byte after byte; stop on SIGINT
	char tmp;
	while (!interrupted && read(STDIN_FILENO, &tmp, 1) > 0)
	{
		// write the byte to each of the files
		for (int i = 0; i < argc - 1; i++) {
			write(files[i], &tmp, 1);
		}
		// and to stdout
		write(STDOUT_FILENO, &tmp, 1);
	}

	// Close files and release the memory
	for (int i = 0; i < argc - 1; i++) {
		close(files[i]);
	}
	free(files);
}
