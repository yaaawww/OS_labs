#include<stdio.h>
int search(char* path, int depth);

int main (int argc, int *argv[]) {
	search("./test_dir/", 0);
	return 0;
}
