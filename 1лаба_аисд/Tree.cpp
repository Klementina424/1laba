#include "Tree.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	Tree_Node<int, char> Tree;

	Tree.NIL_Root();
	char data[5] = { 'a', 'b','c','d','e' };
	for (int i = 0; i < 5; i++)
	Tree.Insert(i, data[i]);
	
	cout << "Вывод дерева на экран: " << endl;
	Tree.Print(Tree.get_Root());
	Tree.Insert(10, 'f');
	Tree.Insert(-10, 'g');
	Tree.Insert(15, 'h');
	Tree.Insert(-6, 'i');
	Tree.Insert(11, 'j');

	cout<<"Вывод дерева на экран после добавления новых элементов: "<<endl;
	Tree.Print(Tree.get_Root());
	return 0;
}

