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

Input loadFromFile(FILE *fp);

tnode *buildTree(int *pos, tnode **array);

void getDimensions();

void getCoordinates();

void saveToFile();
