#ifndef LIST_H
#define LIST_H

node* create_item(int data, unsigned char height);
node* insert(node *head, node *item, int* back);
node* find(node* head, int key);
node* find_comp(node* head, int key, int* comp);
unsigned char height(node* p);
int bfactor(node* p);
void fixheight(node* p);
node* rotateright(node* p);
node* rotateleft(node* q);
node* balance(node* p);
node* insert_balance(node* p, node* k, int* back);
void apply(node* head, void (*f)(node*, void*), void *arg);
void free_tree(node *head);
void to_dot(node *head, void *param);
void export_to_dot(FILE *f, node *head);

#endif /*LISt_H*/
