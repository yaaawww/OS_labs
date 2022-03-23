#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>

char* get_value(char* filename, char* key);
char* status = "status";
char* Pid = "Pid";
char* PPid = "PPid";
char* Tgid = "Tgid";
char* name = "Name";
char filename[512][512];
int len = 0;

int search(char* path, int depth) {
	DIR *d;
	struct dirent *file;
	if (!(d = opendir(path)))
		return -1;
	
	while ((file = readdir(d)) != NULL) {
		if (strncmp (file->d_name, ".", 1) == 0)
			continue;
		if (file->d_type == 4) {
			//for (int i = 0; i < depth; ++i) {
				//printf("--");
			//}
			//printf("%s\n", file->d_name);
			char temp[50];
			strcpy(temp, path);
			strcat(temp, file->d_name);
			strcat(temp, "/");
			search(temp, depth + 1);
		} else {
			//for (int i = 0; i < depth; ++i) {
			//	printf("--");
			//}
			if (strcmp(file->d_name, status) == 0) {
				char filename[50];
				strcpy(filename, path);
				strcat(filename, file->d_name);
				//char* ptr_str = get_value(filename, Pid);
				//printf("%s", ptr_str);
				if(strcmp(get_value(filename, PPid), "1") == 0) {
					for (int i = 0; i < depth - 1; ++i) {
						printf("\t");
					}
					printf("--");
					printf("%s", get_value(filename, name));
					printf("(%s)\n", get_value(filename, Pid));
				}				
			}
		}
	}
	closedir(d);
	return 0;
}
