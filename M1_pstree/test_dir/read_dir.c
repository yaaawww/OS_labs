#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
int main (int argc, int* argv[]) {
	DIR *d;
	struct dirent *file;
	struct stat sb;
	d = opendir("./");
	while((file = readdir(d)) != NULL) {
		printf("%d\n", file->d_ino);
		printf("%d\n", file->d_type);
		printf("%s\n", file->d_name);
	}
	return 0;
}
