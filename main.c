#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
	char path[100];
	
	if (argc > 1) {
		strcpy(path, argv[1]);
	} else {
		printf("Directory Path: ");
		fgets(path, sizeof(path)-1, stdin);
		path[strlen(path)-1] = 0;
		printf("\n");
	}
	struct stat st;

	DIR *d = opendir(path);
	struct dirent *dir_ent;

	int size = 0;

	if(!d) {
		printf("Error: %s\n", strerror(errno));
	}
	if (d) {
		dir_ent = readdir(d);
		printf("Total Directory Size: %d Bytes\n", size);

		printf("Directories:\n");
		rewinddir(d);
		dir_ent = readdir(d);
		while (dir_ent) {
			if (dir_ent->d_type == 4) {
			printf("\t%s\n", dir_ent->d_name);
			}
			dir_ent = readdir(d);
		}

		printf("Regular files:\n");
		rewinddir(d);
		dir_ent = readdir(d);
		while (dir_ent) {
			if (dir_ent->d_type == 8) {
			printf("\t%s\n", dir_ent->d_name);
			}
			dir_ent = readdir(d);
		}

		closedir(d);
	}
	
	return 0;
}