#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) { return EXIT_FAILURE; }
	
	Input Data = loadFromFile(fp);
	Data.size += 0;
	fclose(fp);
	return 0;
}
