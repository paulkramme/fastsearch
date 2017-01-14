#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define VERSION "v0.1"
#define MAX_FILENAME_LENGH 256
#define PERMS 0777

int main(int argc, char *argv[])
{
	printf("Fast Search %s\n", VERSION);

	if(argc > 2)
	{
		if(strcmp(argv[1], "add") == 0)
		{
			int conffile = 0;
			char dir_to_add[256];

			strcpy(dir_to_add, argv[2]);
			printf("Adding dir %s\n", dir_to_add);
			conffile = open("fs.conf", O_APPEND | O_RDWR | O_CREAT, PERMS);
			write(conffile, dir_to_add, sizeof(dir_to_add));
			close(conffile);
		}
	}
	else
	{
		puts("You gave to few commands...");
		return 1;
	}
	return 0;
}

