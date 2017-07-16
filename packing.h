typedef struct tnode {
	char label;
	int index;
	struct tnode *left;
	struct tnode *right;
	double width;
	double height;
	double x;
	double y;
} tnode;

typedef struct Input {
	tnode **array;
	int size;
} Input;

// Loads input from file into an array
Input loadFromFile(FILE *fp);

// Builds binary tree from information stored in array
tnode *buildTree(int *pos, tnode **array);

// Frees a binary tree
void freeTree(tnode *root);

// Gets dimensions in a tree (including dimensions of subtrees)
void getDimensions(tnode *root);

// Gets coordinates of the leaf nodes in a tree
void getCoordinates(tnode *root, double xCur, double yCur);

// Writes the leaves of a postorder traversal of a tree to a file
void writeTreeLeavesPostorder(tnode *root, FILE *fp);

// Gets the largest (highest index) node in a tree
void getLargestNode(tnode *root, tnode **largest);
