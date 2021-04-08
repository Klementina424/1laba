#pragma once
#pragma once
#include "LinkedList.h"
#include <iostream>


enum NodeColor { BLACK, RED };
template<class NODE_TYPE_1, class NODE_TYPE_2>
class Tree_Node
{
public:

	~Tree_Node();
	void Insert(NODE_TYPE_1 key, NODE_TYPE_2 data);
	void Remove(NODE_TYPE_1 key);
	Tree_Node* Find(NODE_TYPE_1 key, Tree_Node* node_x);
	void Clear(Tree_Node* tree);
	void get_Keys(Tree_Node* node_x, LinkedList<NODE_TYPE_1>* List_of_Keys);
	void get_Values(Tree_Node* node_x, LinkedList<NODE_TYPE_2>* List_of_Values);
	void Print(Tree_Node* node_x);
	
	void NIL_Root();
	void Left_turn(Tree_Node* node_x);
	void Right_turn(Tree_Node* node_y);
	void Insert_fixup(Tree_Node* node_z);
	void Transplant(Tree_Node* u, Tree_Node* v);
	void Remove_fixup(Tree_Node* node_x);
	Tree_Node* get_Root() { return root; }
	Tree_Node* get_Parent() { return parent; }
	Tree_Node* Tree_min(Tree_Node* node_x);

private:

	Tree_Node* left, * right, * parent;
	Tree_Node* root;
	Tree_Node* NIL;
	NodeColor color;
	NODE_TYPE_1 key;
	NODE_TYPE_2 data;
};

#include "Tree.inl"