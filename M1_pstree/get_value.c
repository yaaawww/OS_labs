#include<stdio.h> 
#include<string.h>
#include<stdlib.h>

char* get_value(char* filename, char* key) {
	char buf[1024];
	FILE *fp = fopen(filename, "r");
	int index = 0;
	char* value = (char*)malloc(20);
	char* temp;
	if (fp) {
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			if ((temp = strstr(buf, key)) == NULL) {
				continue;
			} else {
				strcpy(value, temp);
				while(*(value + index) != '\t') {
					index++;
				}
				index++;
			}
		}
	} else {
		printf("Warning, there no such file.\n");
		return NULL;
	}
	fclose(fp);
	return value + index;
}
