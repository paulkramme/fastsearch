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
	DIR *path;
	char searched_file[MAX_FILENAME_LENGH];
	char searched_in_path[MAX_PATH_LENGH];
	int pointer_to_dirent_array = 0;

	printf("FASTSCAN %s\n", VERSION);
	if(argc < 3)
	{
		puts("You gave too few arguments. Aborting.");
		return 1;
	}
	strcpy(searched_file, argv[2]);
	strcpy(searched_in_path, argv[1]);
	path = opendir(searched_in_path);
	pointer_to_dirent_array = readdir(path);
	print("NAME: %s", pointer_to_dirent_array.d_name[]);
	closedir(path);
	return 0;
}

