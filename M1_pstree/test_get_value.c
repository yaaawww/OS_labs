#include<stdio.h>
char* get_value(char* filename, char* key);

int main (int argc, int* argv[]) {
	char* str = get_value(argv[1], "name");
	printf("%s\n", str);
	return 0;
}
