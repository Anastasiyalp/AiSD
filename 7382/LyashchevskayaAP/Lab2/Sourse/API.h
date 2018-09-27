typedef struct Node {
        int flag_type[2];
        char sign;
        union {
                int one;
                struct Node *left;
        };
        union {
                int two;
                struct Node *right;
        };
} Node;

typedef struct List {
        Node *top;
} List;

void abort_(const char * , ...);                                        //Insert in case of incorrect length string
void fill_list(Node *, char *);
void find_args(char *, int *);
int find_sec_bracket(char *);
void fill_node(Node *, int *, char *);
void fill_expr(Node *,int , int ,char *);
void print_list(Node *);


