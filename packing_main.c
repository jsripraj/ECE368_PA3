#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char **argv) {
	// Open the input file
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) { return EXIT_FAILURE; }

	// Load data from input file into array
	Input Data = loadFromFile(fp);

	// Close file
	fclose(fp);

	// Build binary tree from input array
	tnode *tree = buildTree(&(Data.size), Data.array);

	// Free input array
	free(Data.array);

	// Calculate dimensions
	getDimensions(tree);

	// Calculate coordinates
	getCoordinates(tree, 0, tree -> height);

	// Open the output file
	fp = fopen(argv[2], "w");
	if (fp == NULL) { return EXIT_FAILURE; }

	// Print leaf node information to file
	writeTreeLeavesPostorder(tree, fp);

	// Close the output file
	fclose(fp);

	// Print screen output
	printf("\nWidth: %le\nHeight: %le\n", tree -> width, tree -> height);
	tnode *largest = tree;
	getLargestNode(tree, &largest);
	printf("X-coordinate: %le\nY-Coordinate: %le\n\n", largest -> x, largest -> y);

	// Free binary tree
	freeTree(tree);

	return 0;
}
