#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <ftw.h>
#include <fnmatch.h>
#include <fcntl.h>

struct Arguments {
	char *filename;
	char *command;
} arguments;

// int handle_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
// 	// printf("%lu: %s\n", sb->st_ino, fpath);
// 	// see fnmatch
//
// 	if (fnmatch(arguments.pattern, fpath, 0) != FNM_NOMATCH) {
// 		printf(" * %s matches %s\n", fpath, arguments.pattern);
// 	}
// 	return 0;
// }


int main(int argc, char* argv[]) {
	struct stat file_stat = {0};
	struct inotify_event event =  {0};
	char buf[4096] __attribute__ ((aligned(__alignof__(struct inotify_event))));

	int inotify_fd = inotify_init();

	// quick and dirty version
	// TODO: handle various errors and unsafe handlings
	if (argc != 3) {
		printf("Wrong arguments number: %d\n", argc);
		return 1;
	}
	printf("1: %s\n2: %s\n", argv[1], argv[2]);
	arguments.filename = argv[1];
	arguments.command = argv[2];
	
	if (lstat(arguments.filename, &file_stat) == -1) {
		perror("lstat");
		return EXIT_FAILURE;
	}
	printf("file: %s -> %jo\n", arguments.filename, (uintmax_t)file_stat.st_mode);

	if (file_stat.st_mode & S_IFREG) {
		printf("Regural file\n");
	}

	if (file_stat.st_mode & S_IFDIR) {
		// TODO: implement it
		printf("Directory\n");
		return EXIT_SUCCESS;
	}

	int watch_descriptor = inotify_add_watch(inotify_fd, arguments.filename, IN_MODIFY | IN_CLOSE_WRITE);

	if (watch_descriptor == -1) {
		fprintf(stderr, "Cannot watch '%s': %s\n",
                           arguments.filename, strerror(errno));
		return EXIT_FAILURE;
	}

	while (1) {

	}
	// size_t buffer_size = 8 * 1024 * 1024;
	// char *cwd = malloc(buffer_size);
	// getcwd(cwd, buffer_size-1);
	// printf("%s\n", cwd);

	// nftw(cwd, handle_file, 1024, FTW_F);
	// free(cwd);
	return EXIT_SUCCESS;
}
