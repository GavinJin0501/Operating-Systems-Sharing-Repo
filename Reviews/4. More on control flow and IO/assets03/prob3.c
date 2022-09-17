#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRSIZE 100
#define NFIELDS 9


int main() {
	char input_file[] = "stateoutflow0708.txt";
	char state_code_org[STRSIZE];
	char country_code_org[STRSIZE];
	char state_code_dest[STRSIZE];
	char country_code_dest[STRSIZE];
	char line[STRSIZE * NFIELDS];
	char state_abbrv[STRSIZE];
	char state_name[STRSIZE];
	int return_num = 0;
	int exmpt_num = 0;
	int aggr_agi = 0;
	int total = 0;
	
	FILE* fp = fopen(input_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot open the file\n");
		exit(-1);
	}
	fgets(line, STRSIZE * NFIELDS, fp);

	printf("%-30s%6s\n", "STATE", "TOTAL");
	printf("--------------------------------------\n");

	while (fgets(line, STRSIZE * NFIELDS, fp)) {
		sscanf(line, "%s %s %s %s %s %s %d %d %d", 
			state_code_org,
			country_code_org,
			state_code_dest,
			country_code_dest,
			state_abbrv,
			state_name,
			&return_num,
			&exmpt_num,
			&aggr_agi
		);

		if (strcmp(state_code_org, "\"25\"") == 0) {
			printf("%-30s%6d\n", state_name, aggr_agi);
			total += aggr_agi;
		}
	}

	printf("--------------------------------------\n");
	printf("%-30s%6d\n", "TOTAL", total);
	fclose(fp);

	return 0;
}