#ifndef header_file
#define header_file

typedef struct node_str
{
    int value;
    int height;
    struct node_str *left;
    struct node_str *right;

} node_str;

int find_max(int right, int left);
int find_height(node_str *node);
int find_balance(node_str *node);
node_str *create_node(int value);
node_str *insert_node(node_str *node, int value);
node_str *leftRotate(node_str *x);
node_str *rightRotate(node_str *y);
void inorder(node_str *root);
void print_tree(node_str *root, int space);
void delete_tree(node_str *root);
node_str *delete_node(node_str *root, int value);
node_str *find_replace(node_str *node);
bool find_node(node_str *root, int value);

#endif