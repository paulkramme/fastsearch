/*This software is licensed under CC0*/
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

/*MAX values for every linux system... Only change if you know better.*/
#define MAX_FILENAME_LENGH 256
#define MAX_PATH_LENGH 4096

/*static settings*/
const char conffilepath[] = "/etc/fastsearch/fastsearch.conf";
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
	/*Declarations*/
	FILE *configfile;
	char confdirs[1000];

	/*fd's*/
	configfile = fopen(conffilepath, "r");
	
	/*code*/
	while(fgets(confdirs, 1000, configfile))
	{
		/*Remove ending newline and reassign back to original variable*/
		strcpy(confdirs, strtok(confdirs, "\n"));
		puts(confdirs);
	}

	/*close fd's*/
	close(configfile);	
	return 0;
}
