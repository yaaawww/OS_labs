#include<stdio.h> 
#include<string.h>
#include<stdlib.h>

char* get_value(char* filename, char* key) {
	char buf[1024];
	FILE *fp = fopen(filename, "r");
	int index = 0;
	static char value[1024];
	char* value = (char*) malloc(sizeof(char)*1024);
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
				break;
			}
		}
	} else {
		printf("Warning, there no such file.\n");
		return NULL;
	}
	fclose(fp);
	int re = 0;
	while(*(value + index + re) != '\n') {
		re++;
		if (*(value + index + re) == '\0') {
			break;
		}
	}
	*(value + index + re) = '\0';
	return value + index;
}
