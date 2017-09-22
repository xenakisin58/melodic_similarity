extern int text[50000];

int best_length;
int best_length_a;
int best_length_b;
int best_edits;
double best_score;

enum flag{
    rows,
    columns,
    diagonal
};


int max3(int a, int b);
int max4(int a, int b, int c);
int access(int i, int j, int n, int * table);
void print_table(int m, int n, int la_table[m][n]);
void backtrace_sw(int m, int n, int i, int j, int la_table[m][n]);
void sw(int m, int n);

void backtrace_sw_stack(int m, int n, int i, int j, int la_table[m][n]);
void sw_stack(int m, int n);
void backtrace_sw_heap(int m, int n, int i, int j, int * la_table);
void sw_heap(int m, int n);

void backtrace_nw(int m, int n, int la_table[m][n]);
void nw_heap(int m, int n);
