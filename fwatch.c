#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ftw.h>
#include <fnmatch.h>

struct Arguments {
	char *pattern;
	char *command;
} arguments;

int handle_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	// printf("%lu: %s\n", sb->st_ino, fpath);
	// see fnmatch
	
	if (fnmatch(arguments.pattern, fpath, 0) != FNM_NOMATCH) {
		printf(" * %s matches %s\n", fpath, arguments.pattern);
	}
	return 0;
}


int main(int argc, char* argv[]) {
	// quick and dirty version
	// TODO: handle varioous errors and unsafe handlings
	if (argc != 3) {
		printf("Wrong arguments number: %d\n", argc);
		return 1;
	}
	printf("1: %s\n2: %s\n", argv[1], argv[2]);
	arguments.pattern = argv[1];
	arguments.command = argv[2];
	
	size_t buffer_size = 8 * 1024 * 1024;
	char *cwd = malloc(buffer_size);
	getcwd(cwd, buffer_size-1);
	printf("%s\n", cwd);

	nftw(cwd, handle_file, 1024, FTW_F);
	free(cwd);
	return 0;
}
