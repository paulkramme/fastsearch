#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define VERSION "v0.1"

/*Modify if not correct for your system*/
#define MAX_FILENAME_LENGH 256
#define MAX_PATH_LENGH 4096

int main(int argc, char *argv[])
{
	DIR *path;
	char searched_file[MAX_FILENAME_LENGH];
	char searched_in_path[MAX_PATH_LENGH];
	struct dirent *filestuff;
	char path_to_found_file[MAX_PATH_LENGH];
	short int found_something;

	found_something = 0;

	printf("FASTSCAN %s\n", VERSION);
	if(argc < 3)
	{
		puts("You gave too few arguments. Aborting.");
		return 1;
	}

	strcpy(searched_file, argv[2]);
	strcpy(searched_in_path, argv[1]);
	path = opendir(searched_in_path);
	for(;;)
	{
		filestuff = readdir(path);
		if(filestuff == NULL)
		{
			if(found_something == 0)
			{
				printf("The specified file or directory weren't found.\n");
			}
			else
			{
				printf("Not found.\n");
			}
			break;
		}
		/* LEARN THIS */
/*
		printf("NAME: %s\n", filestuff->d_name);
		printf("INODE: %lu\n", filestuff->d_ino);
*/
		if(strcmp(filestuff->d_name, searched_file) == 0)
		{
			printf("Found!\n");
			strcpy(path_to_found_file, strcat(searched_in_path, filestuff->d_name));
			printf("%s\n", path_to_found_file);
			found_something = 1;
		}
	}
	closedir(path);
	return 0;
}

