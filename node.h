#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node {
	Node * parent;
	int value[6];
	Node * child[6];

	public:
		Node(); //default ... constructor
		Node(int val);
		Node(int * valArray);
		int numChildren();
		bool hasChildren();
		Node* absorb(Node * newChild,Node * b);
		void discard(Node * removeChild); //we moved this to tree... it made more sense to us.
		void printNode();
		void setParent(Node * p);
		void moveNode(Node * sourceNode, int sourcePos, Node * destNode, int destPos);

		void setChild(Node * c[6] );
		void setValue(int v, int pos);
		void setChild(Node * c, int pos);

		int whichChild();


		Node * getParent();
		Node* getLeft();
		Node* getMiddle();
		Node* getRight();
		Node* getChild(int i);
		int getValue(int pos);



}; // end class Node

Node::Node()
{
	parent = nullptr;

	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	value[3] = 0;
	value[4] = 0;
	value[5] = 0;

	child[0] = nullptr;
	child[1] = nullptr;
	child[2] = nullptr;
	child[3] = nullptr;
	child[4] = nullptr;
	child[5] = nullptr;
}

Node::Node(int * valArray)
{
	for(int i =0; i<6; i++)
	{
		value[i] = valArray[i];
	}
	child[0] = nullptr;
	child[1] = nullptr;
	child[2] = nullptr;
	child[3] = nullptr;
	child[4] = nullptr;
	child[5] = nullptr;
}

void Node::printNode()
{
	cout << "|";
	for(int i =0; i<3; i++)
	{
		cout << value[i];
		if((i+1)%3 != 0)
			cout << ",";

	}
	cout << "| ";
	//cout << endl;
}

void Node::setParent(Node * p)
{
	parent = p;
}
Node * Node::getParent()
{
	return parent;
}

void Node::setChild(Node * c[6])
{

	for(int i =0; i<6; i++)
	{
		child[i] = c[i];

	}
}


Node* Node::getLeft()
{
	return child[0];
}

Node* Node::getMiddle()
{
	return child[1];
}

Node* Node::getRight()
{
	return child[2];
}
Node* Node::getChild(int i){

	return child[i];

}

bool Node::hasChildren()
{
	bool hasC;
	hasC = false;
	for(int i =0; i<6; i++)
	{
		if(child[i]!=nullptr)
		{
			hasC=true;
		}
	}
	return hasC;
}

int Node::numChildren()
{
	int numC;
	numC = 0;
	for(int i =0; i<6; i++)
	{
		if(child[i]!=nullptr)
		{
			numC++;
		}
	}
	return numC;
}

int Node::getValue(int pos)
{
	return value[pos];
}

void Node::setValue(int v, int pos)
{
	value[pos] = v;
}

void Node::setChild(Node * c, int pos)
{
	child[pos] = c;
}

int Node::whichChild()//returns which child position it is in
{
	for(int i =0; i<3; i++)
	{
		if(value[2]==parent->getValue(i))
		{
			return i;
		}
	}
	return -1;
}

void Node::moveNode(Node * sourceNode, int sourcePos, Node * destNode, int destPos)
{

	bool parentChange = false;
	if(sourceNode->parent != destNode)
	{
		parentChange = true;
	}

	Node * sourceParent = sourceNode->getParent(); //create temp to hold source parent info
	destNode->setChild(sourceNode,destPos);
	//cout << "moveNode ... source parent value " << sourceParent->getValue(sourcePos) << endl;

	destNode->setValue(sourceParent->getValue(sourcePos),destPos);
	sourceNode->setParent(destNode);


	sourceParent->setChild(nullptr, sourcePos);
	sourceParent->setValue(0,sourcePos);


}


Node* Node::absorb(Node * newChild,Node * b)
{
	Node * ogParent = nullptr;
	if(b->getParent() != nullptr){
		ogParent = b->getParent();

	}
	//cout << "In Absorb" << endl;
	//base case to stop recursion....
	if(parent == nullptr)
	{
		Node* MegaRoot = new Node();

		MegaRoot->setChild(newChild,0);
		newChild->setParent(MegaRoot);


		MegaRoot->setChild(this,2);
		parent=MegaRoot;

		MegaRoot->setValue(MegaRoot->getLeft()->getValue(2),0);
		MegaRoot->setValue(MegaRoot->getRight()->getValue(2),2);


		return MegaRoot;
	}

	/*cout << "This is the parent of b which was serached node..." << endl;
	parent->printNode();
	cout << endl;*/
	Node * tempNode;

	if(parent->numChildren()==1)
	{
		newChild->setParent(parent);
		parent->setChild(newChild,0);
		parent->setValue(newChild->getValue(2),0);
		return nullptr;
	}

	else if(parent->numChildren() < 3) //easy case....
	{
		//easy insert case... and there are three...
		newChild->setParent(parent); //set parent of node we are adding

		//case 1 when value is smaller than any children in child...
		if(parent->getValue(0) > newChild->getValue(2))
		{

			moveNode(parent->getLeft(),0,parent,1);
			parent->setChild(newChild,0);
			parent->setValue(newChild->getValue(2),0);

		}
		//case 2 When smaller than 3rd one...
		else
		{
			parent->setChild(newChild,1);
			parent->setValue(newChild->getValue(2),1);
		}
		return nullptr;
	}

	//hard case
	else
	{
		Node * pLeft = new Node();

		//now we need to move the smallest two children into pLeft
		//and keep bigger two in parent
		//then we need to make sure all children and parent pointers
		//and values are correct...

		//move both over to PLeft and newValue is smallest
		if(newChild->getValue(2) <ogParent->getValue(0))
		{
			pLeft->setChild(newChild,0);
			pLeft->setValue(newChild->getValue(2),0);
			newChild->setParent(pLeft);

			//now we want to move OG left child over...

			//This parent-getLeft() is basicly the current node
			moveNode(ogParent->getLeft(),0,pLeft,2);

			//finally we want to move OG middle child over to the left...
			moveNode(ogParent->getMiddle(),1,ogParent,0);



		}

		//new value is bigger than first value but less than rest
		else if(newChild->getValue(2) < ogParent->getValue(1))
		{
			//cout << "-----HARD CASE 2-----"<<endl;
			//set new child
			pLeft->setChild(newChild,2);
			pLeft->setValue(newChild->getValue(2),2);
			newChild->setParent(pLeft);

			//move original left value to 1st pos of pleft
			moveNode(ogParent->getLeft(),0,pLeft,0);

			//now move original middle to 1st pos of p
			moveNode(ogParent->getMiddle(),1,ogParent,0);


		}
		else
		{
			//cout << "-----HARD CASE 3-----"<<endl;

			//move 1st pos of OG parent to 1st pos of pLeft
			moveNode(ogParent->getLeft(),0,pLeft,0);

			//move 2nd pos of OG parent to 3rd pos of pLeft
			moveNode(ogParent->getMiddle(),1,pLeft,2);

			//Insert newChild into parent of 0

			ogParent->setChild(newChild,0);
			ogParent->setValue(newChild->getValue(2),0);

			newChild->setParent(ogParent);


		}


		//cout << "This is pLeft....." << endl;
		pLeft->printNode();
		cout <<endl;
		//cout << "This is ogparent..... " << endl;
		ogParent->printNode();
		cout << endl;

		return ogParent->absorb(pLeft,ogParent);

	}
}

#endif
