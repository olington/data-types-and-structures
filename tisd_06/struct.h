#ifndef STRUCT_H
#define STRUCT_H

typedef struct node node;
struct node
{
	int data;
	unsigned char height;
    node* left;
	node* right;
};

typedef struct my_int my_int;
struct my_int
{
	int flag;
	int value;
};

#endif /*STRUCT_H*/
