//Authors Maddie Neely and  Connor Comstock
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include "tree.h"
#include "node.h"
#include "printFancy.h"

void createTestTree(Tree t);
//void helperNodeVals(int * vals, int setVals[6]);
void makeLeaves(Node * curr);
int main()
{

	//This is horribly coded... but this was our manual tree...
	//This creates a root with values
	int rootVals[6] = {17,28,2000,0,0,0};
	Node root(&rootVals[0]);
	Tree t(&root);
	//set parent of root to null ptr.
	t.getRoot()->setParent(nullptr);

	//create left child with values and set parent
	int nodeVals[6] = {3,8,17,0,0,0};
	Node leftChild(&nodeVals[0]);
	leftChild.setParent(t.getRoot());

	//create middle child with values and set parent
	int nodeVals2[6] = {21,0,28,0,0,0};
	Node middleChild(&nodeVals2[0]);
	middleChild.setParent(t.getRoot());

	//create right child with values and set parent
	int nodeVals3[6] = {33,0,2000,0,0,0};
	Node rightChild(&nodeVals3[0]);
	rightChild.setParent(t.getRoot());

	//create child array
	Node * childrenArray[6];
	childrenArray[0] = &leftChild;
	//childrenArray[0]->printNode();
	childrenArray[1] = &middleChild;
	childrenArray[2] = &rightChild;
	childrenArray[3] = nullptr;
	childrenArray[4] = nullptr;
	childrenArray[5] = nullptr;

	t.getRoot()->setChild(childrenArray);

	//now let's add the next level of children
	int nodeVals4[6] = {1,0,3,0,0,0};
	Node leftChild1(&nodeVals4[0]);
	leftChild1.setParent(&leftChild);

	int nodeVals5[6] = {5,0,8,0,0,0};
	Node middleChild1(&nodeVals5[0]);
	middleChild1.setParent(&leftChild);

	int nodeVals6[6] = {11,14,17,0,0,0};
	Node rightChild1(&nodeVals6[0]);
	rightChild1.setParent(&leftChild);

	childrenArray[0] = &leftChild1;
	childrenArray[1] = &middleChild1;
	childrenArray[2] = &rightChild1;
	childrenArray[3] = nullptr;
	childrenArray[4] = nullptr;
	childrenArray[5] = nullptr;

	//set children of the leftchild
	//cout << "PRINT second Round SET CHILDREN" << endl;
	leftChild.setChild(childrenArray);

	int nodeVals7[6] = {19,0,21,0,0,0};
	Node leftChild2(&nodeVals7[0]);
	leftChild2.setParent(&middleChild);

	//int nodeVals8[6] = {0,0,0,0,0,0};
	//Node middleChild2(&nodeVals8[0]);
	//rightChild.setParent(&middleChild);

	int nodeVals9[6] = {24,0,28,0,0,0};
	Node rightChild2(&nodeVals9[0]);
	rightChild2.setParent(&middleChild);

	childrenArray[0] = &leftChild2;
	//childrenArray[1] = &middleChild2;
	childrenArray[1] = nullptr;
	childrenArray[2] = &rightChild2;
	childrenArray[3] = nullptr;
	childrenArray[4] = nullptr;
	childrenArray[5] = nullptr;

	//set children of the leftchild
	//cout << "PRINT third Round SET CHILDREN" << endl;
	middleChild.setChild(childrenArray);

	int nodeVals10[6] = {31,0,33,0,0,0};
	Node leftChild3(&nodeVals10[0]);
	leftChild3.setParent(&rightChild);


	int nodeVals12[6] = {36,0,2000,0,0,0};
	Node rightChild3(&nodeVals12[0]);
	rightChild3.setParent(&rightChild);

	childrenArray[0] = &leftChild3;
	//childrenArray[1] = &middleChild3;
	childrenArray[1] = nullptr;
	childrenArray[2] = &rightChild3;
	childrenArray[3] = nullptr;
	childrenArray[4] = nullptr;
	childrenArray[5] = nullptr;

	//set children of the leftchild
	//cout << "PRINT Four Round SET CHILDREN" << endl;
	rightChild.setChild(childrenArray);

	//Now let's add the last level ...aka the leaves...
	makeLeaves(&root);
	
	
	//here's a few tests for insert and delete that we did 
	//we tried many not listed here...
	t.printFancy();
	
	cout << "INSERT 20 "<< endl; 
	t.insert(20);
	
	cout << "INSERT 22" << endl; 
	t.insert(22);
	
	
	cout << "INSERT 23" << endl; 
	t.insert(23);
	
	cout << "INSERT 25" << endl; 
	t.insert(25); 
	t.printFancy();

	
	
	cout << endl << endl; 
	
	
	
	cout << "Delete 1" << endl; 
	t.myDelete(1);

	
	cout << "Delete 3" << endl; 
	t.myDelete(3);
	
	
	cout << "Delete 11" << endl; 
	t.myDelete(11);

	
	cout << "Delete 14" << endl; 
	t.myDelete(14);

	
	cout << "Delete 21" << endl; 
	t.myDelete(21);
	t.printFancy(); 




	return 0;
}


void makeLeaves(Node * curr)
{
	if (curr == nullptr)
	{
		return;
	}

	//if this should have leaves...
	//cout << "has children " << curr->hasChildren() << endl;
	if(curr->hasChildren()==false)
	{
		Node * tempChildrenArray[6];
		for(int i=0; i<6; i++)
		{
			if(curr->getValue(i)!=0)
			{
				int nodeValsTemp[6] = {0,0,curr->getValue(i),0,0,0};
				Node * tempNode = new Node(&nodeValsTemp[0]); //we will have mem leaks if not delete
				tempChildrenArray[i] = tempNode;
				tempNode->setParent(curr);
			}
			else
			{
				tempChildrenArray[i] = nullptr;
			}
		}
		curr->setChild(tempChildrenArray);
		return;
	}
	//cout << "recurse left " << endl;
	makeLeaves(curr->getLeft());
	//cout << "recurse middle " << endl;
	makeLeaves(curr->getMiddle());
	//cout << "recurse right " << endl;
	makeLeaves(curr->getRight());

}

