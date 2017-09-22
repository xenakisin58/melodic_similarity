
//#define MAX_CHAR 16386 //16384 + 2 placeholder characters
//#define MAX_CHAR 1538 //128 * 12 + 2 for ModOctave
//#define MAX_CHAR 258 //interval - uses a shift up of 127
//#define MAX_CHAR 130 //rhythm
//#define MAX_CHAR 15 //noteValMod
#define MAX_CHAR 5 //parsons

int best_seq[500];
int best_length;

struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];

    //pointer to other node via suffix link
    struct SuffixTreeNode *suffixLink;

    /*(start, end) interval specifies the edge, by which the
     node is connected to its parent node. Each edge will
     connect two nodes,  one parent and one child, and
     (start, end) interval of a given edge  will be stored
     in the child node. Lets say there are two nods A and B
     connected by an edge with indices (5, 8) then this
     indices (5, 8) will be stored in node B. */
    int start;
    int *end;

    /*for leaf nodes, it stores the index of suffix for
      the path  from root to leaf*/
    int suffixIndex;
};

typedef enum { false, true } bool; //flag for comparing durations as well
extern bool compare_duration;
extern int text[50000]; //Holds both melodies
//extern Node *root; /* Pointer to root node */

/*activeEdge is represeted as input string character
  index (not the character itself)*/
int activeEdge;
int activeLength;

/* remainingSuffixCount tells how many suffixes yet to
   be added in tree */
extern int remainingSuffixCount;
extern int leafEnd;
extern int *rootEnd;
extern int *splitEnd;
extern int size; /* Length of input string */
extern int size1; /* Size of 1st string */

//extern int numNodes;

typedef struct SuffixTreeNode Node;

Node *newNode(int start, int *end);

//reinitializes the suffixTree global variables
void reinitialize();

/* Print the suffix tree as well along with setting suffix index
   So tree will be printed in DFS manner
   Each edge along with it's suffix index will be printed */
void print(int i, int j);

int edgeLength(Node *n);

int walkDown(Node *currNode);

void extendSuffixTree(int pos);

void setSuffixIndexByDFS(Node *n, int labelHeight);

void freeSuffixTreeByPostOrder(Node *n);

/* Build the suffix tree and print the edge labels along with
   suffixIndex. suffixIndex for leaf edges will be >= 0 and
   for non-leaf edges will be -1*/
void buildSuffixTree(int size);

int doTraversal_lcs(Node *n, int labelHeight, int* maxHeight, int* substringStartIndex);

/* Prints longest common substring to STDOUT */
void getLongestCommonSubstring();

/* get LCS method for best-of-3 noteValMod tests */
void getLongestCommonSubstring_bestOfThree();

int doTraversal_lrs(Node *n, int labelHeight, int* maxHeight, int* substringStartIndex);

/* Prints longest common substring to STDOUT */
void getLongestRepeatedSubstring();

/* get LRS method for best-of-3 noteValMod tests */
void getLongestRepeatedSubstring_bestOfThree();

/* traverse edge of suffix tree (to check for substring match) */
int traverseEdge(int* subStr, int idx, int start, int end, int subStr_size);

/* perform traversalto check for substring match */
int doTraversal_subStr(Node *n, int* subStr, int idx, int subStr_size);

/* check for a substringin suffix tree */
void checkForSubString(int* str, int subStr_size);
