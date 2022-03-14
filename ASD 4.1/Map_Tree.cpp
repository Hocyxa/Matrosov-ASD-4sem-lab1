#include "Map_Tree.h"
#include <iostream>

unsigned Map_Tree::height(Tree* p)
{
	return p ? p->height : 0;
}
int Map_Tree::bal_factor(Tree* p)
{
	return height(p->right) - height(p->left);
}
void Map_Tree::fix_height(Tree* p)
{
	unsigned  hl = height(p->left);
	unsigned  hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}
void Map_Tree::delete_tree(Tree* p)
{
	if (p) 
	{
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}
void Map_Tree::print(Tree* p, int level = 0) const
{
	if (p)
	{
		print(p->left, level + 1);
		for (int i = 0; i < level; i++) std::cout << "   ,";
		std::cout << p->key << std::endl;
		print(p->right, level + 1);
	}
}
Tree* Map_Tree::rotate_right(Tree* p)
{
	Tree* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}
Tree* Map_Tree::rotate_left(Tree* q)
{
	Tree* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}
Tree* Map_Tree::balance(Tree* p)
{
	fix_height(p);
	if (bal_factor(p) == 2)
	{
		if (bal_factor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}
	if (bal_factor(p) == -2)
	{
		if (bal_factor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}
	return p;
}
Tree* Map_Tree::find_min(Tree* p)
{
	return p->left ? find_min(p->left) : p;
}
Tree* Map_Tree::erase_min(Tree* p)
{
	if (p->left == 0)
		return p->right;
	p->left = erase_min(p->left);
	return balance(p);
}
Tree* Map_Tree::erase_elem(Tree* p, int key)
{
	if (!p) return 0;
	if (key < p->key)
		p->left = erase_elem(p->left, key);
	else if (key > p->key)
		p->right = erase_elem(p->right, key);
}
Tree* Map_Tree::insert(int key, std::string value, Tree* root)
{
	if (!root) return new Tree(key, value);
	else if (key < root->key)
		root->left = insert(key, value, root->left);
	else if (key > root->key)
		root->right = insert(key, value, root->left);
	else throw "Elem exists";
	return balance(root);
}
Map_Tree::Map_Tree()
{}
Map_Tree::~Map_Tree()
{}
void Map_Tree::print() const
{}
bool Map_Tree::insert(int key, std::string value)
{}
const std::string& Map_Tree::find(int key) const
{}
bool Map_Tree::erase(int key)
{}