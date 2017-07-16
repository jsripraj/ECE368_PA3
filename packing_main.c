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
	printTreeLeavesPostorder(tree);

	// Free binary tree
	freeTree(tree);
	return 0;
}
