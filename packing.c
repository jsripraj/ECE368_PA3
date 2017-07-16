#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

Input loadFromFile(FILE *fp) {
	// Count the number of lines in the file
	int lines = 0;
	do {
		if (fgetc(fp) == '\n') { lines++; }
	} while(!feof(fp));
	// Create structure to hold data
	Input Data;
	Data.array = malloc(lines * sizeof(tnode *));
	Data.size = lines;
	// Load data from file into array
	int i = 0;
	for (i = 0; i < lines; i++) {
		Data.array[i] = malloc(sizeof(tnode));
		// Initialize fields to 0 or NULL
		Data.array[i] -> index = 0;
		Data.array[i] -> left = NULL;
		Data.array[i] -> right = NULL;
		Data.array[i] -> width = 0;
		Data.array[i] -> height = 0;
		Data.array[i] -> x = 0;
		Data.array[i] -> y = 0;
		// Read in first byte
		Data.array[i] -> label = fgetc(fp);
		if (fgetc(fp) != '\n') {
			fseek(fp, -2, SEEK_CUR);
			fscanf(fp, "%d(%le, %le)\n", &(Data.array[i] -> index), &(Data.array[i] -> width), &(Data.array[i] -> height));
			Data.array[i] -> label = 0;
		}
	}
	return Data;
}
