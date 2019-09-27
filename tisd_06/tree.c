#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tree.h"

node* create_item(int data, unsigned char height)
{
    node *item = malloc(sizeof(node));
    if (item)
    {
        item->data = data;
		item->height = height;
        item->left = NULL;
		item->right = NULL;
    }
    return item;
}

node* insert(node *head, node *elem, int* back)
{
	if (head == NULL)
		return elem;
	else
	{
		if (elem->data < head->data)
			head->left = insert(head->left, elem, back);
		else if (elem->data > head->data)
			head->right = insert(head->right, elem, back);
		else if (elem->data == head->data)
		{
			*back = -1;
			return head;
		}
	}
	return head;
}

node* find(node* head, int key)
{
	node* cur = NULL;
	if (head != NULL)
	{
		if (key == head->data)
			return head;
		else if (key > head->data)
			cur = find(head->right, key);
		else if (key < head->data)
			cur = find(head->left, key);
	}
	return cur;
}

node* find_comp(node* head, int key, int* comp)
{
	node* cur = NULL;
	if (head != NULL)
	{
		if (key == head->data)
		{
			*comp += 1;
			return head;
		}
		else if (key > head->data)
		{
			*comp += 1;
			cur = find_comp(head->right, key, comp);
		}
		else if (key < head->data)
		{
			*comp += 1;
			cur = find_comp(head->left, key, comp);
		}
	}
	return cur;
}

void apply(node* head, void (*f)(node*, void*), void *arg)
{
    if (head == NULL)
	{
        return;
	}
	f(head, arg);
	apply(head->left, f, arg);
    apply(head->right, f, arg);
}

void to_dot(node *head, void *param)
{
    FILE *f = param;

    if (head->left)
        fprintf(f, "%d -> %d;\n", head->data, head->left->data);

    if (head->right)
        fprintf(f, "%d -> %d;\n", head->data, head->right->data);
}

void export_to_dot(FILE *f, node *head)
{
    fprintf(f, "digraph %s {\n", "my_graph");

    apply(head, to_dot, f);

    fprintf(f, "}\n");
}

unsigned char height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p)
{
	fixheight(p);
	if(bfactor(p) == 2)
	{
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if(bfactor(p) ==- 2)
	{
		if(bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

node* insert_balance(node* p, node* k, int* back)
{
	if(p == NULL) 
		return k;
	if (k->data < p->data)
		p->left = insert_balance(p->left, k, back);
	else if (k->data > p->data)
		p->right = insert_balance(p->right, k, back);
	else if (k->data == p->data)
	{
		*back = -1;
		return p;
	}
	return balance(p);
}

void free_tree(node* tree)
{ 
    if (tree->left)
		free_tree(tree->left); 
    if (tree->right)
		free_tree(tree->right); 
    free(tree); 
}
