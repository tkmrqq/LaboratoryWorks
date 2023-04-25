typedef struct Node Node;

#define size 100

struct Node {
    char* question;
    Node* yes;
    Node* no;
};


//void save(const char* filename, Node* root);

Node* load(const char* filename);

Node* create_node(int id, const char* name);

void insert_node(Node* root, Node* node);

Node* find_node(Node* node, int id);

void play(Node *node, Node ***answers, int *answersSize);