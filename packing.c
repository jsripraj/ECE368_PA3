#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

Input loadFromFile(FILE *fp) {
	// Count the number of lines in the file
	int lines = 0;
	do {
		if (fgetc(fp) == '\n') { lines++; }
	} while(!feof(fp));
	rewind(fp);
	// Create structure to hold data
	Input Data;
	Data.array = malloc(lines * sizeof(tnode *));
	Data.size = lines;
	// Load data from file into array
	int i = 0;
	for (i = 0; i < lines; i++) {
		// Array holds pointer to tnode
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
		// If the second byte is a \n, then the element was an inner node
		// If it's not, then the element is a leaf node
		if (fgetc(fp) != '\n') {
			// Seek back to line beginning and read leaf data
			fseek(fp, -2, SEEK_CUR);
			fscanf(fp, "%d(%le,%le)\n", &(Data.array[i] -> index), &(Data.array[i] -> width), &(Data.array[i] -> height));
			// Leaf nodes have label = 0
			Data.array[i] -> label = 0;
		}
	}
	return Data;
}

tnode *buildTree(int *pos, tnode **array) {
	// pos is cursor for the array
	// Since array is a stack, pos starts at the end or the "top"
	(*pos)--;
	int cur = *pos;
	// Return when reach a leaf node
	if (array[cur] -> index > 0) {
		return array[cur];
	}
	array[cur] -> right = buildTree(pos, array);
	array[cur] -> left = buildTree(pos, array);
	return array[cur];
}

void printTreeLeavesPostorder(tnode *root) {
	if (root -> index > 0) {
		printf("%d, ", root -> index);
		return;
	}
	printTreeLeavesPostorder(root -> left);
	printTreeLeavesPostorder(root -> right);
	return;
}

void freeTree(tnode *root) {
	if (root == NULL) { return; }
	freeTree(root -> left);
	freeTree(root -> right);
	free(root);
	return;
}
