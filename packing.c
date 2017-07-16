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
		printf("%d %le %le %le %le\n", root -> index, root -> width, root -> height, root -> x, root -> y);
		return;
	}
	printTreeLeavesPostorder(root -> left);
	printTreeLeavesPostorder(root -> right);
	return;
}

void getDimensions(tnode *root) {
	// Return when leaf node is reached
	if (root -> label == 0) { return; }
	getDimensions(root -> left);
	getDimensions(root -> right);
	if (root -> label == 'H') {
		// Root's width is the larger of the two children's widths
		root -> width = root -> right -> width;
		if (root -> left -> width > root -> right -> width) {
			root -> width = root -> left -> width;
		}
		// Root's heigh is the sum of the two children's heights
		root -> height = root -> left -> height + root -> right -> height;
	}
	if (root -> label == 'V') {
		// Root's height is the larger of the two children's heights
		root -> height = root -> right -> height;
		if (root -> left -> height > root -> right -> height) {
			root -> height = root -> left -> height;
		}
		// Root's width is the sum of the two children's widths
		root -> width = root -> left -> width + root -> right -> width;
	}
	return;
}

void getCoordinates(tnode *root, double xCur, double yCur) {
	if (root -> label == 0) { return; }
	getCoordinates(root -> left, xCur, yCur);
	if (root -> label == 'V') {
		if (root -> left -> label == 0) {
			root -> left -> x = xCur;
			root -> left -> y = yCur - root -> height;
		}
		xCur += root -> left -> width;
		if (root -> right -> label == 0) {
			root -> right -> x = xCur;
			root -> right -> y = yCur - root -> height;
		}
	}
	if (root -> label == 'H') {
		if (root -> left -> label == 0) {
			root -> left -> x = xCur;
			root -> left -> y = yCur - root -> left -> height;
		}
		yCur -= root -> left -> height;
		if (root -> right -> label == 0) {
			root -> right -> x = xCur;
			root -> right -> y = yCur - root -> right -> height;
		}
	}
	getCoordinates(root -> right, xCur, yCur);
	return;
}

void freeTree(tnode *root) {
	if (root == NULL) { return; }
	freeTree(root -> left);
	freeTree(root -> right);
	free(root);
	return;
}
