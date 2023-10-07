#ifndef Tree_H
#define Tree_H

#include <iostream>
#include <cmath>
using namespace std;
#include "node.h"



class Tree {

	Node * root;
	void print(Node * start);
	void preOrderHelper(Node* curr);
	Node * searchHelper(Node* curr, int valToFind);

	public:
		Tree();
		Tree(Node * r);
		Node * search(int valToFind);
		bool insert(int valToAdd);
		bool myDelete(int valToKill);
		void print();
		Node * getRoot() { return root;}
		void discard(Node * removeChild);
		void distribute(Node* grandparent, int totchildren, int cPos);
		void updateParents(Node * curr, int pos);
		void updateParents(Node * curr, int pos, Node * ogChild);
		void shiftChildrenR(Node * gp, bool odd);
		void shiftChildrenL(Node * gp, bool odd);
		void updateParents2(Node * curr);

		//Extra Prints
		void pfHelper(int **megaArray, Node * currNode,int * posCurDepth, int currDepth);
		void printFancy();
		void parentPrint(Node* curr);



}; // end class Tree

Tree::Tree()//default constructor...
{
	root = new Node();
	Node * node2000 = new Node();
	node2000->setParent(root);
	node2000->setValue(2000,2);
	root->setValue(2000,2);
	root->setChild(node2000,2);
}

Tree::Tree(Node * r)
{
	root = r;
	//also evenutally add default node 2000... for implementation purposes.
}

void Tree::print()
{
	preOrderHelper(root);
}

void Tree::preOrderHelper(Node* curr){
	if (curr == nullptr)
	{
		//cout << " NO NODE " << endl;
		return;
	}

	preOrderHelper(curr->getLeft());		// traverse the left subtree
	preOrderHelper(curr->getMiddle());		// traverse the middle subtree
	preOrderHelper(curr->getRight());		// traverse the right subtree
} // end preOrderHelper

Node * Tree::search(int valToFind)
{
	//call search helper
	return searchHelper(root, valToFind);

}

Node * Tree::searchHelper(Node* curr, int valToFind)
{

	if(curr->hasChildren()==false)
		return curr;
	if(valToFind <= curr->getValue(0))
	{
		return searchHelper(curr->getLeft(), valToFind);
	}
	else if(valToFind <= curr->getValue(1))
	{
		return searchHelper(curr->getMiddle(), valToFind);
	}
	else
	{
		return searchHelper(curr->getRight(), valToFind);
	}

} // end

bool Tree::insert(int valToAdd)
{
	Node * b = search(valToAdd);

	if(b->getValue(0) == valToAdd)
	{
		return true;
	}
	if(valToAdd > 2000)
	{
		return false;
	}

	int nodeVals[6] = {0,0,valToAdd,0,0,0};
	Node * nodeToAdd = new Node(&nodeVals[0]);
	Node * tempRoot;
	tempRoot = b->absorb(nodeToAdd,b);
	if(tempRoot != nullptr)
	{
		root = tempRoot;
	}
	return true;

}

bool Tree::myDelete(int valToKill)
{
	Node * b = search(valToKill);

	if(b->getValue(2) == valToKill)
	{
		//cout << "Discard is being called now " << endl;
		discard(b);
		updateParents2(root);
		return true;
	}
	else
	{
		//cout << "Value was not in the tree " << endl;
		return false;
	}

}

void Tree::updateParents(Node * curr, int pos) //only recurses for left values
{
	int parentPos = -1;
	if(curr->getParent()==nullptr)
	{
		return;
	}

	if(curr->getParent()->getParent() != nullptr)
	{
		parentPos = curr->getParent()->whichChild();
	}

	curr->getParent()->setValue(curr->getValue(2),pos);

	if(pos==2 && curr->getParent()->getParent() != nullptr)
	{
		updateParents(curr->getParent(),parentPos);
	}
	return;
}
void Tree::updateParents2(Node * curr)////makes sure all parent vals are right
{
	if(curr->hasChildren()==false)
	{
		return;
	}
	if(curr->getLeft()!=nullptr)
	{
		updateParents2(curr->getLeft());
		curr->setValue(curr->getLeft()->getValue(2),0);
	}
	if(curr->getMiddle()!=nullptr)
	{
		updateParents2(curr->getMiddle());
		curr->setValue(curr->getMiddle()->getValue(2),1);
	}
	if(curr->getRight()!=nullptr)
	{
		updateParents2(curr->getRight());
		curr->setValue(curr->getRight()->getValue(2),2);
	}
	return;

}

void Tree::shiftChildrenR(Node * gp, bool odd) //moves all children right so spaced correctly
{
	int index1;
	int end1;
	int needs3Check;
	int needs2Check;
	int destPos;
	int destNodeTracker;
	Node * destNode;
	Node * sourceNode;

	int fullnessCount[3] = {0,0,0};

	index1 = 0;
	end1 = 3;
	needs3Check = 2;
	needs2Check = 3;
	destPos = 0;
	destNodeTracker = 0;
	if(odd == 1)
	{
		fullnessCount[0] = 3;
		fullnessCount[1] = 2;
		fullnessCount[2] = 2;
	}
	else
	{
		fullnessCount[0] = 2;
		fullnessCount[1] = 2;
		fullnessCount[2] = 2;
	}
	for(int i=index1; i<end1; i++)
	{
		if(gp->getChild(i)!=nullptr)//iterate through grandparent's children
		{
			for(int sourcePos=index1; sourcePos<end1; sourcePos++)
			{
				if(gp->getChild(i)->getChild(sourcePos)!=nullptr)
				{

					destNode = gp->getChild(destNodeTracker);
					sourceNode = gp->getChild(i)->getChild(sourcePos);

					//check if there needs to be a move
					if(!((sourceNode->getParent() == destNode) && (sourcePos == destPos))) //do nothing
					{
						gp->moveNode(sourceNode, sourcePos, destNode, destPos);

						if(destPos == 2)
						{	//we need to update parent value information
							updateParents(destNode,destNodeTracker);
						}
					}
					if(fullnessCount[destNodeTracker]==needs3Check)
					{
						destPos += 2;
					}
					else
					{
						destPos++;
					}
					//cout << "Current Fullness Count " << fullnessCount[destNodeTracker] << endl;
					if(destPos > fullnessCount[destNodeTracker] || destPos == needs2Check)
					{
						//time to reset and or increment
						destNodeTracker ++;
						destPos = 0;
					}
				}
			}
		}
	}
}

void Tree::shiftChildrenL(Node * gp, bool odd)
{
	//cout << "In shiftChildrenL " << endl;
	int index1;
	int end1;
	int needs3Check;
	int needs2Check;
	int destPos;
	int destNodeTracker;
	Node * destNode;
	Node * sourceNode;

	int fullnessCount[3] = {0,0,0};

	index1 = 2;
	end1 = -1;
	needs3Check = 0;
	needs2Check = -1;
	destPos = 2;
	destNodeTracker = 2;
	if(odd == 1)
	{
		fullnessCount[0] = 0;
		fullnessCount[1] = 0;
		fullnessCount[2] = -1;
	}
	else
	{
		fullnessCount[0] = 0;
		fullnessCount[1] = 0;
		fullnessCount[2] = 0;
	}
	for(int i=index1; i>end1; i--)
	{
		//cout << "Start of loop i =  " << i << endl;

		if(gp->getChild(i)!=nullptr)//iterate through grandparent's children
		{
			for(int sourcePos=index1; sourcePos>end1; sourcePos--)
			{
				if(gp->getChild(i)->getChild(sourcePos)!=nullptr)
				{

					destNode = gp->getChild(destNodeTracker);
					sourceNode = gp->getChild(i)->getChild(sourcePos);

					if(!((sourceNode->getParent() == destNode) && (sourcePos == destPos))) //do nothing
					{

						gp->moveNode(sourceNode, sourcePos, destNode, destPos);

						if(destPos == 2)
						{	//we need to update parent value information
							updateParents(destNode,destNodeTracker);
						}
					}
					if(fullnessCount[destNodeTracker]==needs3Check)
					{
						destPos = destPos - 2;
					}
					else
					{
						destPos--;
					}
					if(destPos < fullnessCount[destNodeTracker] || destPos == needs2Check)
					{
						//time to reset and or increment
						destNodeTracker --;
						destPos = 2;
					}
				}
			}
		}
	}
}

void Tree::distribute(Node * grandparent, int totChildren, int cPos)
{
	int numNodes = grandparent->numChildren();
	int fullness = 0;
	int maxFullness;

	//help us figure out if we need to shift everything right or left
	//depending on situation if there is a node with three values we
	//want to keep them to one side and shift in the opposite direction
	int numChildren0 = 0;
	int numChildren1 = 0;
	if(grandparent->getChild(0)!=nullptr)
	{
		numChildren0 = grandparent->getChild(0)->numChildren();
	}
	if(grandparent->getChild(1)!=nullptr)
	{
		numChildren1 = grandparent->getChild(1)->numChildren();
	}
	if((cPos == 1 && numChildren0 == 3) || (cPos == 1 && numChildren1 == 3) || (cPos == 2 && numChildren1 == 3))
	{
		//cout << "We are in the weird case aka backwards... " << endl;
		shiftChildrenL(grandparent, totChildren%numNodes != 0);
	}
	else
	{
		//cout << "We are in the forwards case ... " << endl;
		shiftChildrenR(grandparent, totChildren%numNodes != 0);
	}

	if(totChildren == 5)
	{
		grandparent->setChild(grandparent->getChild(1),2);
		grandparent->setValue(0,1);
		grandparent->setChild(nullptr,1);
	}



}

void Tree::discard(Node * a) //a is child to be removed
{
	//cout << "START OF DISCARD " << endl;
	Node * p = a->getParent();
	int childPos = a->whichChild();
	int parentPos = p->whichChild();
	p->setChild(nullptr,childPos);

	int totChildren = 0;
	for(int i=0; i<3; i++)
	{
		if(p->getParent()->getChild(i)!= nullptr) //p is not the root
		{
			totChildren += p->getParent()->getChild(i)->numChildren();
		}
	}

	if(p->numChildren()==2)//easy we can just delete!
	{
		if(childPos == 1)
		{
			p->setValue(0,1);
			return;
		}
		else if(childPos == 0) //we need to move middle node to the left
		{
			a->moveNode(p->getMiddle(),1,p,0);
		}
		else if(childPos == 2) //we need to move middle node to the right..
		{
			a->moveNode(p->getMiddle(),1,p,2);
			updateParents(p,parentPos);
		}
	}

	else if(totChildren >=4)
	{
		distribute(p->getParent(),totChildren, parentPos);
	}

	else
	{
		Node * b;
		for(int i=0; i<3; i++)
		{
			if(p->getChild(i)!=nullptr)
			{
				b = p->getChild(i);
			}
		}
		//now we know there are <= 3 children of p
		if(p->getParent()==nullptr) //aka if p is the root
		{
			root = b;
			delete p;
		} //this may not be a 2-3 tree anymore...

		Node * sibling;
		//otherwise allocate b to the sibling of p, return discard(p)
		if(parentPos == 0) //we want to put b into 2
		{
			sibling = p->getParent()->getChild(2);

			int bChildPos = b->whichChild();

			//case 1 when value is smaller than any children in child...
			if(sibling->getValue(0) > b->getValue(2))
			{

				b->moveNode(sibling->getLeft(),0,sibling,1);
				b->moveNode(b,b->whichChild(),sibling,0);
				//b->getParent()->setValue(sibling->getValue(0),bChildPos);
				p->setValue(sibling->getValue(0),bChildPos);

			}
			//case 2 When smaller than 3rd one...
			else if(sibling->getValue(2) < b->getValue(2))
			{
				b->moveNode(sibling->getRight(),2,sibling,1);
				b->moveNode(b,b->whichChild(),sibling,2);
				p->setValue(sibling->getValue(2),bChildPos);

			}
			else
			{
				b->moveNode(b,b->whichChild(),sibling,1);
				p->getParent()->setValue(sibling->getValue(1),bChildPos);

			}

			sibling = p->getParent()->getChild(2);
			b->setParent(sibling); //set parent of node we are adding to sibling
			discard(p);
		}
		//we know if there are only 2 nodes they will be the left and right
		//and never the middle!
		if(parentPos == 2) //we want to put b into 0
		{
			sibling = p->getParent()->getChild(0);

			int bChildPos = b->whichChild();

			//case 1 when value is smaller than any children in child...
			if(sibling->getValue(0) > b->getValue(2))
			{
				b->moveNode(sibling->getLeft(),0,sibling,1);
				b->moveNode(b,b->whichChild(),sibling,0);
				p->setValue(sibling->getValue(0),bChildPos);

			}
			//case 2 When smaller than 3rd one...
			else if(sibling->getValue(2) < b->getValue(2))
			{
				b->moveNode(sibling->getRight(),2,sibling,1);
				b->moveNode(b,b->whichChild(),sibling,2);
				p->setValue(sibling->getValue(2),bChildPos);

			}
			else
			{
				b->moveNode(b,b->whichChild(),sibling,1);
				p->setValue(sibling->getValue(1),bChildPos);
			}

			sibling = p->getParent()->getChild(0);
			//cout << "Sibling After adding b ";

			b->setParent(sibling); //set parent of node we are adding to sibling
			discard(p);
		}

	}
	//cout << "END Discard " << endl;
	return;

}



#endif
