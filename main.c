#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define VERSION "v0.1"
#define MAX_FILENAME_LENGH 256
#define MAX_PATH_LENGH 4096
#define PERMS 0777

int main(int argc, char *argv[])
{
	char searched_file[MAX_FILENAME_LENGH];
	char searched_in_path[MAX_PATH_LENGH];
	printf("FASTSCAN %s\n", VERSION);
	if(argc < 3)
	{
		puts("You gave too few arguments. Aborting.");
		return 1;
	}
	path = DIR opendir(searched_in_path);

	return 0;
}

