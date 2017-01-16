#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

/*Modify if not correct for your system*/
#define MAX_FILENAME_LENGH 256
#define MAX_PATH_LENGH 4096

/*Typedefs*/
typedef enum { false, true } bool;



/*Prototypes*/
int isfiledirectory(const char name[]);


int isfiledirectory(const char name[])
{
	DIR *directory = opendir(name);

	if(directory != NULL)
	{
		closedir(directory);
		return 0;
	}

	if(errno == ENOTDIR)
	{
		return 1;
	}

	/*if something is going seriously wrong...*/
	return -1;
}


int main(int argc, char *argv[])
{
	DIR *path;
	char searched_file[MAX_FILENAME_LENGH];
	char searched_in_path[MAX_PATH_LENGH];
	struct dirent *filestuff;
	char path_to_found_file[MAX_PATH_LENGH];
	bool found_something;

	found_something = false;

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
			if(isfiledirectory(filestuff->d_name) == 0)
			{
				path = strcat(searched_in_path, filestuff->d_name);
			}
			if(found_something == 0)
			{
				printf("The specified file or directory wasn't found.\n");
			}
			else
			{
				printf("Not found.\n");
			}
			break;
		}

		if(strcmp(filestuff->d_name, searched_file) == 0)
		{
			printf("Found!\n");
			strcpy(path_to_found_file, strcat(searched_in_path, filestuff->d_name));
			printf("%s\n", path_to_found_file);
			found_something = true;
		}
	}
	closedir(path);
	return 0;
}
