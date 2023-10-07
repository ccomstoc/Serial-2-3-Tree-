
//Idea, make a new recursive helper called ghost helper, fills with empty space and is liek a psydo tree traversal
//Format tree print with 1's, print on a grid, change normalSpacer = (((sizeAtDepth*3)/(pow(3,i)))-1); to normalSpacer = (((sizeAtDepth)/(pow(3,i)))-1)*3;?
//Reconsider charecter spacing, with updated spacer
//Or just use built in cout formating lol, but this is more fun
#include "tree.h"

void Tree::printFancy(){

	int depth = 0;
	bool trav = true;
	Node * curr = root;

	if(!curr->hasChildren()){
		cout << "Root has no children" << endl;
		return;
	}

	//get depth
	while(trav){
		if(curr->hasChildren())
			depth++;
		else
			trav = false;
		curr = curr->getLeft();
	}

	cout << "DEPTH: " << depth << endl;
	int sizeAtDepth = pow(3,depth);

	int * ppd = new int[depth+1];
	for(int i = 0; i< depth+1; i++)
		ppd[i] = 0;
	int rowSize = depth+1;
	int colSize = sizeAtDepth*3;
	int** mega = (int**)malloc(rowSize * sizeof(int*));
  	for(int i = 0; i < rowSize; i++)
  		mega[i] = (int*)malloc(colSize * sizeof(int));

	for(int i = 0; i < depth+1; i++){
		for(int x  = 0; x < sizeAtDepth*3; x++)
				mega[i][x] = -1;
	}

	pfHelper(mega,root,ppd, 0);

	for(int i = 0; i < depth+1; i++){

	int normalSpacer = (((sizeAtDepth*3)/(pow(3,i)))-1);
	int beggingSpacer = (normalSpacer/2)-normalSpacer/4;

	//cout << "normalSpacer" << normalSpacer

		if(i == 0){
			for(int z = 0; z < beggingSpacer; z++)
				cout << " ";
			cout << "|";
			cout << mega[i][0] << ", ";
			cout << mega[i][1]<< ", ";
			cout << mega[i][2];
			cout << "|" <<endl;
		}
		else{
			for(int z = 0; z < beggingSpacer; z++)
				cout << " ";
				cout << "|";
			for(int x  = 0; x < sizeAtDepth*3; x++){
				if(mega[i][x] != -1){
					cout << mega[i][x];
					if((x+1)%3 != 0)
						cout << ",";
				}
				else
					break;
				if((x+1)%3 == 0){
					int prevCharCount = 0;
					for(int u = 0; u < 3; u++){
						int curr = x-u;
						if(mega[i][curr]<10)
							prevCharCount +=1;
						else if(mega[i][curr]<100)
							prevCharCount +=2;
						else if(mega[i][curr]<1000)
							prevCharCount +=3;
						else if(mega[i][curr]<1000)
							prevCharCount +=4;
					}

					cout << "|";
					int updatedSpacer;
						if(normalSpacer-prevCharCount<0)
							updatedSpacer = 0;
						else
							updatedSpacer = normalSpacer-prevCharCount;

					for(int k = 0; k < updatedSpacer; k++)
						cout<< " ";
					cout << "|";
				}
			}
				cout << endl;
		}
	}


	//Frees malloc, similar to delete?
	for(int i = 0; i < rowSize; i++)
		free(mega[i]);
	free(mega);

	cout << endl;
	parentPrint(root);


}
void Tree::pfHelper(int **megaArray,Node * currNode,int * posCurDepth, int currDepth){

	//cout << "Recurse" << currDepth << endl;
	int pcd = posCurDepth[currDepth];
	for(int i = 0; i < 3; i++)
		megaArray[currDepth][pcd+i] = currNode->getValue(i);
	posCurDepth[currDepth] += 3;

	if(!currNode->hasChildren())//Have reached a leaf node
		return;

	pfHelper(megaArray,currNode->getLeft(),posCurDepth,currDepth+1);
	if(currNode->getMiddle() != nullptr)
		pfHelper(megaArray,currNode->getMiddle(),posCurDepth,currDepth+1);
	if(currNode->getRight() != nullptr)
		pfHelper(megaArray,currNode->getRight(),posCurDepth,currDepth+1);

	return;
}

void Tree::parentPrint(Node* curr){
	if (curr == nullptr)
		return;

	curr->printNode(); //print's values of current node
	if(curr->getParent() != nullptr)
	{
		cout << " Parent ";
		curr->getParent()->printNode();
		cout << endl;
	}
	else
	{
		cout << " NO Parent " << endl;
	}


	parentPrint(curr->getLeft());		// traverse the left subtree
	parentPrint(curr->getMiddle());		// traverse the middle subtree
	parentPrint(curr->getRight());		// traverse the right subtree
}
