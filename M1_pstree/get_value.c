#include<stdio.h> 
#include<string.h>

int get_value(char* filename, char* key) {
	char buf[1024];
	FILE *fp = fopen(filename, "r");
	if (fp) {
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			char* value;
			if ((value = strstr(buf, key)) == NULL) {
				continue;
			} else {
				while(*(value) != '\t') {
					value++;
				}
				value++;
				printf("%s", value);
				fclose(fp);
				return 1;
			}
		}
	} else {
		printf("Warning, there no such file.\n");
		return 0;
	}
	fclose(fp);
	return 1;
}
