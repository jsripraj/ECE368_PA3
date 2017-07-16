#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) { return EXIT_FAILURE; }
	
	Input Data = loadFromFile(fp);
	fclose(fp);
	
	tnode *tree = buildTree(&(Data.size), Data.array);
	printTreeLeavesPostorder(tree);

	free(Data.array);
	freeTree(tree);
	return 0;
}
