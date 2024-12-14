typedef struct opticItem {
        char name[100];
        float price;
        char type[100];
        char manufacturer[100];
        char brand[100];
        struct opticItem *next;
}opticItem;

typedef struct List {
        opticItem *first;
        opticItem *last;
        int n;
}List;

void push(List *items, int index);
void erase(List *items, int index);
void search(List items);
void edit(List *items, int index);
void loadFromFile(List *items, const char *filename);
void saveToFile(List items, const char *filename);
void print(List items, const char *filename);
