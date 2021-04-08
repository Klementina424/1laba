#include "LinkedList.h"
#include "Tree.h"
#include <iostream>

template<class NODE_TYPE_1, class NODE_TYPE_2>
Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::~Tree_Node()
{
	Clear(root);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::NIL_Root()
{
	NIL = new Tree_Node;
	NIL->color = BLACK;
	root = NIL;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Left_turn(Tree_Node* node_x)
{
	Tree_Node* node_y = node_x->right;
	node_x->right = node_y->left;
	if (node_y->left != NIL)
		node_y->left->parent = node_x;
	if (node_y != NIL)
		node_y->parent = node_x->parent;
	if (node_x->parent == NIL)
		root = node_y;
	else if (node_x == node_x->parent->left)
		node_x->parent->left = node_y;
	else
		node_x->parent->right = node_y;
	node_y->left = node_x;
	if (node_x != NIL)
		node_x->parent = node_y;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Right_turn(Tree_Node* node_x)
{
	Tree_Node* node_y = node_x->left;
	node_x->left = node_y->right;
	if (node_y->right != NIL)
		node_y->right->parent = node_x;
	if (node_y != NIL)
		node_y->parent = node_x->parent;
	if (node_x->parent == NIL)
		root = node_y;
	else if (node_x == node_x->parent->left)
		node_x->parent->left = node_y;
	else
		node_x->parent->right = node_y;
	node_y->right = node_x;
	if (node_x != NIL)
		node_x->parent = node_y;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Insert(NODE_TYPE_1 key, NODE_TYPE_2 data)
{
	Tree_Node* node_z = new Tree_Node;
	node_z->key = key;
	node_z->data = data;
	Tree_Node* node_x = root;
	Tree_Node* node_y = NIL;
	while (node_x != NIL)
	{
		node_y = node_x;
		if (node_z->key < node_x->key)
			node_x = node_x->left;
		else
			node_x = node_x->right;
	}
	node_z->parent = node_y;
	if (node_y == NIL)
		root = node_z;
	else if (node_z->key < node_y->key)
		node_y->left = node_z;
	else
		node_y->right = node_z;
	node_z->left = NIL;
	node_z->right = NIL;
	node_z->color = RED;
	Insert_fixup(node_z);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Insert_fixup(Tree_Node* node_z)
{
	while (node_z->parent->color == RED && node_z != root)
	{
		if (node_z->parent == node_z->parent->parent->left)
		{
			Tree_Node* node_y = node_z->parent->parent->right;
			if (node_y->color == RED)
			{
				node_z->parent->color = BLACK;
				node_y->color = BLACK;
				node_z->parent->parent->color = RED;
				node_z = node_z->parent->parent;
			}
			else
			{
				if (node_z == node_z->parent->right)
				{
					node_z = node_z->parent;
					Left_turn(node_z);
				}
				node_z->parent->color = BLACK;
				node_z->parent->parent->color = RED;
				Right_turn(node_z->parent->parent);
			}
		}
		else
		{
			Tree_Node* node_y = node_z->parent->parent->left;
			if (node_y->color == RED)
			{
				node_z->parent->color = BLACK;
				node_y->color = BLACK;
				node_z->parent->parent->color = RED;
				node_z = node_z->parent->parent;
			}
			else
			{
				if (node_z == node_z->parent->left)
				{
					node_z = node_z->parent;
					Right_turn(node_z);
				}
				node_z->parent->color = BLACK;
				node_z->parent->parent->color = RED;
				Left_turn(node_z->parent->parent);

			}
		}
	}
	root->color = BLACK;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Transplant(Tree_Node* node_u, Tree_Node* node_v)
{
	if (node_u->parent == NIL)
		root = node_v;
	else if (node_u == node_u->parent->left)
		node_u->parent->left = node_v;
	else
		node_u->parent->right = node_v;
	node_v->parent = node_u->parent;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Remove(NODE_TYPE_1 key)
{
	Tree_Node* node_z = Find(key, root);
	Tree_Node* node_y = node_z, * node_x;
	NodeColor node_y_original_color = node_y->color;
	if (node_z->left == NIL)
	{
		node_x = node_z->right;
		Transplant(node_z, node_z->right);
	}
	else if (node_z->right == NIL)
	{
		node_x = node_z->left;
		Transplant(node_z, node_z->left);
	}
	else
	{
		node_y = Tree_min(node_z->right);
		node_y_original_color = node_y->color;
		node_x = node_y->right;
		if (node_y->parent == node_z)
			node_x->parent = node_y;
		else
		{
			Transplant(node_y, node_y->right);
			node_y->right = node_z->right;
			node_y->right->parent = node_y;
		}
		Transplant(node_z, node_y);
		node_y->left = node_z->left;
		node_y->left->parent = node_y;
		node_y->color = node_z->color;
	}
	if (node_y_original_color == BLACK)
		Remove_fixup(node_x);
}

template <class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Remove_fixup(Tree_Node* node_x)
{
	while (node_x != root && node_x->color == BLACK)
	{
		if (node_x == node_x->parent->left)
		{
			Tree_Node* node_w = node_x->parent->right;
			if (node_w->color == RED)
			{
				node_w->color = BLACK;
				node_x->parent->color = RED;
				Left_turn(node_x->parent);
				node_w = node_x->parent->right;
			}
			if (node_w->left->color == BLACK && node_w->right->color == BLACK)
			{
				node_w->color = RED;
				node_x = node_x->parent;
			}
			else
			{
				if (node_w->right->color == BLACK)
				{
					node_w->left->color = BLACK;
					node_w->color = RED;
					Right_turn(node_w);
					node_w = node_x->parent->right;
				}
				node_w->color = node_x->parent->color;
				node_x->parent->color = BLACK;
				node_w->right->color = BLACK;
				Left_turn(node_x->parent);
				node_x = root;
			}
		}
		else
		{
			Tree_Node* node_w = node_x->parent->left;
			if (node_w->color == RED)
			{
				node_w->color = BLACK;
				node_x->parent->color = RED;
				Right_turn(node_x->parent);
				node_w = node_x->parent->left;
			}
			if (node_w->right->color == BLACK && node_w->left->color == BLACK)
			{
				node_w->color = RED;
				node_x = node_x->parent;
			}
			else
			{
				if (node_w->left->color == BLACK)
				{
					node_w->right->color = BLACK;
					node_w->color = RED;
					Left_turn(node_w);
					node_w = node_x->parent->left;
				}
				node_w->color = node_x->parent->color;
				node_x->parent->color = BLACK;
				node_w->left->color = BLACK;
				Right_turn(node_x->parent);
				node_x = root;
			}
		}
	}
	node_x->color = BLACK;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
Tree_Node<NODE_TYPE_1, NODE_TYPE_2>* Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Find(NODE_TYPE_1 key, Tree_Node* node_x)
{
	if (node_x->get_Parent() == NULL)
		throw "Element not found";
	if (node_x == NIL || node_x->key == key)
		return node_x;
	if (key < node_x->key)
		return Find(key, node_x->left);
	else
		return Find(key, node_x->right);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Clear(Tree_Node* tree)
{
	if (tree == NIL)
		return;
	else
	{
		if (tree->left)
			Clear(tree->left);
		if (tree->right)
			Clear(tree->right);
	}
	delete tree;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::get_Keys(Tree_Node* node_x, LinkedList<NODE_TYPE_1>* List_of_Keys)
{
	if (node_x->get_Parent() == NULL)
		throw "Tree is empty";
	if (node_x == NIL)
		return;
	else
	{
		List_of_Keys->push_back(node_x->key);
		if (node_x->left != NIL)
			get_Keys(node_x->left, List_of_Keys);
	}
	if (node_x->right != NIL)
		get_Keys(node_x->right, List_of_Keys);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::get_Values(Tree_Node* node_x, LinkedList<NODE_TYPE_2>* List_of_Values)
{
	if (node_x->get_Parent() == NULL)
		throw "Tree is empty";
	if (node_x == NIL)
		return;
	else
	{
		List_of_Values->push_back(node_x->data);
		if (node_x->left != NIL)
			get_Values(node_x->left, List_of_Values);
	}
	if (node_x->right != NIL)
		get_Values(node_x->right, List_of_Values);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Print(Tree_Node* node_x)
{
	if (node_x->get_Parent() == NULL)
		throw "Tree is empty";
	if (node_x == NIL)
		return;
	else
	{
		std::cout << "Key = " << node_x->key << ", data = " << node_x->data << std::endl;
		if (node_x->left != NIL)
			Print(node_x->left);
	}
	if (node_x->right != NIL)
		Print(node_x->right);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
Tree_Node<NODE_TYPE_1, NODE_TYPE_2>* Tree_Node<NODE_TYPE_1, NODE_TYPE_2>::Tree_min(Tree_Node* node_x)
{
	if (node_x->get_Parent() == NULL)
		throw "Tree is empty";
	while (node_x->left != NIL)
		node_x = node_x->left;
	return node_x;
}