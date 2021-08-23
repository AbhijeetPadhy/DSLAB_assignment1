//dot -Tpng graph.gv -o graph.png

#include <iostream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// Class of a linked list node
class LLNode{
	int key;
	public:
		LLNode *next;
		LLNode(int val){
			key = val;
			next = NULL;
		}
		
		int getKey(){
			return key;
		}
};

// Class of a linked list
class LinkedList{
	LLNode *head;
	LLNode *tail;
	
	public:
		LinkedList(){
			head = NULL;
			tail = NULL;
		}
		
		void addNode(int val){
			LLNode *tmp = new LLNode(val);
			if(head == NULL)
				head = tail = tmp;
			else{
				tail->next = tmp;
				tail = tail->next;
			}
				
		}
		
		void printList(){
			LLNode * cur = head;
			while(cur != NULL){
				cout << cur->getKey() << " -> ";
				cur = cur->next;
			}
		}
};

// Class for implementation of a Threaded Binary Search Tree
class ThreadedBST{
		ThreadedBST *leftChild; // Stores pointer of left child. It can be NULL, or it can also point as a thread to its predecessor if there is no left child.
		bool leftThread;        // It is true when leftChild is NULL or is pointing as a thread to its predecessor. It is false when leftChild is pointing to its left child node
		int key;                // Data value of a tree node
		bool rightThread;       // It is true when rightChild is NULL or is pointing as a thread to its successor. It is false when rightChild is pointing to its right child node.
		ThreadedBST *rightChild;// Stores pointer of right child. It can be NULL, or it can also point as a thread to its successor if there is no right child.
		int rcount;             // Stores size of right subtree
		
		ThreadedBST *leftMost(ThreadedBST *root);                   //Returns the left most tree node
		ThreadedBST *rightMost(ThreadedBST *root);                  //Returns the right most tree node
		struct Splits *splitUtil(int k);                            // Utility function to split a given tree
		int printTreeUtil(FILE*);                                   // Utility helper function for printTree
		void printTree(char *);                                     // Creates a pictorial image of the tree but the gv file name has to be specified in arguement
		ThreadedBST *allElementsBetweenUtil(int , ThreadedBST *);   // Utility Helper function for allElementsBetween
		
		// A class to store reference to a ThreadedBST object and is used to make a linked list of those objects
		class TNode{
			public:
				TNode *next;
				ThreadedBST *root;
			
				TNode(){
					root = NULL;
					next = NULL;
				}
				
				
		};
		
		// A class to store a linked list of TNode objects. This linked list is used to store references to newly created ThreadedBST nodes during cloning. 
		class LListOfTNode{
			public:
			TNode *head;
			TNode *tail;
			LListOfTNode(){
				head = tail = NULL;
			}
			
			ThreadedBST *search(int val){
					TNode *cur = head->next;
					while(cur != NULL){
						if(cur->root->key == val)
							return cur->root;
						cur = cur->next;
					}
					return NULL;
				}
		};
		
		void clone(ThreadedBST *, LListOfTNode *list);              // Function to create clone of a tree
		
	public:
		//constructor
		ThreadedBST(int val){                                       // Constructor to create a new tree node having key value val
			key = val;
			leftThread = true;
			rightThread = true;
			leftChild = NULL;
			rightChild = NULL;
			rcount = 0;
		}
		
		//Copy Constructor
		ThreadedBST(ThreadedBST *);                                 // Copy constructor that creates a new Threaded BST using an existing one which is sent as an arguement
		
		void insert(int val);                                       // Inserts a new tree node with value val
		void inorder();                                             // Prints the inorder traversal of the nodes of the tree
		ThreadedBST *search(int val);                               // Searches the tree for a node with value val
		int getKey();                                               // Returns the key value of the current node
		ThreadedBST *deleteElement(int val);                        // Delete a node of the tree with value equal to val
		ThreadedBST *successor(ThreadedBST *);                      // Returns pointer to the successor node of the node passed in arguement.
		LinkedList * reverseInorder();                              // Returns a linked list of elements which contains the reverse inorder traversal of the tree nodes
		void printTree();                                           // Creates a pictorial image of the tree
		LinkedList * allElementsBetween(int,int);                   // Creates a linked list of elements with values between a given range k1<=k<=k2
		ThreadedBST * kthElement(int k);                            // Returns pointer to the kth largest element
		struct Splits *split(int k);                                // Creates a new tree to split it into two halves and then return the two new trees
};

// Structure to store references to two ThreadedBST tree objects
struct Splits{
	ThreadedBST *left=NULL;
	ThreadedBST *right=NULL;
};

// Function to find out left most node in a tree
ThreadedBST *ThreadedBST::leftMost(ThreadedBST *root){
	ThreadedBST *cur = root;
	while(cur->leftThread == false)
		cur = cur->leftChild;
	return cur;
}

// Function to find out right most node in a tree
ThreadedBST *ThreadedBST::rightMost(ThreadedBST *root){
	ThreadedBST *cur = root;
	while(cur->rightThread == false)
		cur = cur->rightChild;
	return cur;
}

// Function to find inorder traversal of a tree
void ThreadedBST::inorder(){
	ThreadedBST *cur;
	cur = leftMost(this);
	while(cur != NULL){
		cout << cur->key << " ";
		if(cur->rightThread == true){
			if(cur->rightChild == NULL)
				break;
			else
				cur = cur->rightChild;
		}
		else
			cur = leftMost(cur->rightChild);
	}
}

// Function to insert a new node with a key value of val in a tree
void ThreadedBST::insert(int val){
	// If val < key, recur for left sub tree
	if(val<key){
		if(leftThread == true){
			ThreadedBST *temp = new ThreadedBST(val);
			if(leftChild != NULL){
				temp->leftChild = leftChild;
				temp->leftThread = leftThread;
			}
			temp->rightChild = this;
			temp->rightThread = true;
			leftThread = false;
			leftChild = temp;
			
		}else
			leftChild->insert(val);
	}
	// If val > key, recur for right sub tree	
	else if(val > key){
		rcount++;
		if(rightThread == true){
			ThreadedBST *temp = new ThreadedBST(val);
			if(rightChild != NULL){
				temp->rightChild = rightChild;
				temp->rightThread = rightThread;
			}
			temp->leftChild = this;
			temp->leftThread = true;
			rightThread = false;
			rightChild = temp;
		}
		else
			rightChild->insert(val);
	}
	// If element already exists, return exception
	else 
		throw "Element already exists Exception!";
}

// Function to search for an element in a tree, NULL is returned if element is not found
ThreadedBST *ThreadedBST::search(int val){
	if(key == val){
		return this;
	}else if(val < key){
		if(leftThread == false)
			return leftChild->search(val);
		else
			return NULL;
	}
	else{
		if(rightThread == false)
			return rightChild->search(val);
		else
			return NULL;
	}
}

// Function to delete an element in a tree, Exception is thrown if element to be deleted is not found
ThreadedBST* ThreadedBST::deleteElement(int val){
	// If this is the node to be deleted
	if(key == val){
		//case1: leaf node
		if(leftThread == true && rightThread == true){
			delete(this);
			return NULL;
		}
		//case2: one child
		else if(leftThread || rightThread){
			if(leftThread == false){ //left child exists
				ThreadedBST *left = leftChild;
				//If left child does not have a right child, then it points to the current node. Hence we need to set rightChild pointer
				//of leftChild to point to rightChild pointer of current node.
				if(leftChild->rightThread == true){
					leftChild->rightChild = rightChild;
				}else{
					ThreadedBST *rightMostOfLeft = rightMost(leftChild);
					rightMostOfLeft->rightChild = rightChild;
				}	
				delete(this);
				return left;
			}else{//right child exists
				ThreadedBST *right = rightChild;
				//If right child does not have a left child, then it points to the current node. Hence we need to set leftChild pointer
				//of rightChild to point to leftChild pointer of current node.
				if(rightChild->leftThread == true ){
					rightChild->leftChild = leftChild;
				}else{
					ThreadedBST *leftMostOfRight = leftMost(rightChild);
					leftMostOfRight->leftChild = leftChild;
				}
				delete(this);
				return right;
			}
		}
		//case3: two children
		else{
			ThreadedBST *successor = leftMost(rightChild);
			
			key = successor->key;
			rightChild = rightChild->deleteElement(key);
			
			if(rightChild == NULL)
				rightThread = true;
			rcount--;
			return this;
		}
	// If val  <key recur for left sub tree
	}else if(val < key){
		if(leftThread == false){
			ThreadedBST *leftOfLeft = leftChild->leftChild;
			ThreadedBST *left = leftChild->deleteElement(val);
			
			if(left == NULL){
				leftChild = leftOfLeft;
				leftThread = true;
			}
			else
				leftChild = left;
		}
		else
			throw "Element not Found Exception!";
	// If val > key recur for right sub tree
	}else{
		if(rightThread == false){
			ThreadedBST *rightOfRight = rightChild->rightChild;
			ThreadedBST *right = rightChild->deleteElement(val);
			rcount--;
			if(right == NULL){
				rightChild = rightOfRight;
				rightThread = true;
			}	
			else
				rightChild = right;
		}
		else
			throw "Element not Found Exception!";
	}
	return this;
}

// Getter function to get the value of private member variable key
int ThreadedBST::getKey(){
	return key;
}

// Function to find successor of a node passed in argument
ThreadedBST *ThreadedBST::successor(ThreadedBST *root){
	if(root->rightThread == true){
		return root->rightChild;	
	}
	return leftMost(root->rightChild);
}

// Function to find reverse inorder traversal in a tree
LinkedList *ThreadedBST::reverseInorder(){
	LinkedList *list = new LinkedList();
	ThreadedBST *cur = rightMost(this);
	while(cur->leftChild != NULL){
		list->addNode(cur->key);
		if(cur->leftThread == true)
			cur = cur->leftChild;
		else
			cur = rightMost(cur->leftChild);
	}
	list->addNode(cur->key);
	return list;
}

// Utility function which helps to print tree in a .gv file to be used by graphviz tool to produce an image
int ThreadedBST::printTreeUtil(FILE *fptr){
	fprintf(fptr,"node%d [label = \"<f0> | <f1> %d | <f2>\"];\n",key,key);
	if(leftThread == false){
		leftChild->printTreeUtil(fptr);
		fprintf(fptr,"\"node%d\":f0 -> \"node%d\":f1;\n",key,leftChild->key);
	}else if(leftChild != NULL)
		fprintf(fptr,"\"node%d\":f0 -> \"node%d\":f1 [style=dotted];\n",key,leftChild->key);
		
	if(rightThread == false){
		rightChild->printTreeUtil(fptr);
		fprintf(fptr,"\"node%d\":f2 -> \"node%d\":f1;\n",key,rightChild->key);
	}else if(rightChild != NULL)
		fprintf(fptr,"\"node%d\":f2 -> \"node%d\":f1 [style=dotted];\n",key,rightChild->key);
	
	return key;
}

// Function to print tree in a .gv file to be used by graphviz tool to produce an image 
void ThreadedBST::printTree(){
	char str[] = "graph.gv";
	printTree(str);
}

// Creates a pictorial image of the tree but the gv file name has to be specified in argument
void ThreadedBST::printTree(char *str){
	FILE *fptr;
	fptr = fopen(str,"w");
	fprintf(fptr,"digraph G {\n");
	fprintf(fptr,"node [shape = record,height=.1];\n");
	printTreeUtil(fptr);
	fprintf(fptr,"}");
	fclose(fptr);
}

//The purpose of this function is to find that node whose key value is greater than or equal to k. 
ThreadedBST *ThreadedBST::allElementsBetweenUtil(int k, ThreadedBST *root){
	if(root->key == k)
		return root;
	else if(k < root->key){
		if(root->leftThread == true)
			return root;
		else
			return allElementsBetweenUtil(k,root->leftChild);
	}else{
		if(root->rightThread == true)
			return successor(root);
		else
			return allElementsBetweenUtil(k,root->rightChild);
	}
}

//This function returns a singly linked list of all those elements in the tree which lie between values k1 and k2(inclusive). k1<=k<=k2 .
LinkedList * ThreadedBST::allElementsBetween(int k1, int k2){
	ThreadedBST *cur = allElementsBetweenUtil(k1,this);
	LinkedList *list = new LinkedList();
	
	while(cur != NULL && cur->key <= k2){
		list->addNode(cur->key);
		cur = successor(cur);
	}
	return list;
}

// Returns pointer to the kth largest element
ThreadedBST *ThreadedBST::kthElement(int k){
	if(k == rcount+1){
		return this;
	}else if(k < rcount+1){
		if(rightChild != NULL)
			return rightChild->kthElement(k);
	}else{
		if(leftChild != NULL)
			return leftChild->kthElement(k-rcount-1);
	}
	return NULL;
}

// Utility function to split a given tree
struct Splits *ThreadedBST::splitUtil(int k){
	struct Splits *trees = new Splits();
	ThreadedBST *left = NULL, *right = NULL;
	if(k == key){
		if(rightThread != true)
			trees->right = rightChild;
		trees->left = this;
		if(rightThread == false){
			ThreadedBST *leftMostOfRight = leftMost(rightChild);
			leftMostOfRight->leftChild = NULL;
		}		
		rightThread = true;
		rightChild = NULL;
	}
	else if(k < key){
		if(leftThread == true){
			trees->left = NULL;
			trees->right = this;
			if(trees->right!=NULL && trees->right->leftThread == true){
				trees->right->leftChild = NULL;
			}
		}else{
			trees = leftChild->splitUtil(k);
			leftChild = trees->right;
			if(trees->right == NULL)
				leftThread = true;
			trees->right = this;
			
			if(trees->left != NULL && trees->left->rightThread == true)
				trees->left->rightChild = NULL;
		}
	}else{
		if(rightThread == true){
			trees->right = NULL;
			trees->left = this;
			rightChild = NULL;
		}else{
			trees = rightChild->splitUtil(k);
			rightChild = trees->left;
			if(rightChild == NULL)
				rightThread = true;
			trees->left = this;
		}
	}
	return trees;
}

// Function to split a given tree
struct Splits *ThreadedBST::split(int k){
	struct Splits *trees = new Splits();
	char left[] = "left.gv";
	char right[] = "right.gv";
	
	// Create a new tree using copy constructor
	ThreadedBST *clonedTBST = new ThreadedBST(this);
	// Split the newly cloned tree
	trees = clonedTBST->splitUtil(k);
	
	// Inorder traversal of the first tree
	if(trees->left != NULL){
		cout<<"\nInorder traversal of the First Tree is: ";
		trees->left->inorder();
		trees->left->printTree(left);
	}
	
	// Inorder traversal of the second tree
	if(trees->right != NULL){
		cout<<"\nInorder traversal of the Second Tree is: ";
		trees->right->inorder();
		trees->right->printTree(right);
	}
	cout<<endl;
	
	// Return both the trees
	return trees;
}

// Function to clone a tree whose reference is passed in argument and the newly cloned tree is returned
void ThreadedBST::clone(ThreadedBST * root, LListOfTNode *list){
	key = root->key;
	TNode * tmp = new TNode();
	tmp->root = this;
	list->tail->next = tmp;
	list->tail = tmp;
	if(root->leftThread == false){
		leftChild = new ThreadedBST(root->leftChild->key);
		leftThread = false;
		leftChild->clone(root->leftChild,list);
	}else{
		if(root->leftChild == NULL){
			leftChild = NULL;
			leftThread = true;
		}	
		else{
			leftChild = list->search(root->leftChild->key);
			leftThread = true;
		}
	}
	if(root->rightThread == false){
		rightChild = new ThreadedBST(root->rightChild->key);
		rightThread = false;
		rightChild->clone(root->rightChild,list);
	}else{
		if(root->rightChild == NULL){
			rightChild = NULL;
			rightThread = true;
		}	
		else{
			rightChild = list->search(root->rightChild->key);
			rightThread = true;
		}
	}
}

// Copy constructor
ThreadedBST::ThreadedBST(ThreadedBST * root){
	TNode *node = new TNode();
	LListOfTNode *list = new LListOfTNode();
	list->head = node;
	list->tail = node;
	clone(root,list);
}

// An API which is provided to do operations on a tree for ease of access
class TreeAPI{
	ThreadedBST *root;
	public:
		TreeAPI(){
			root = NULL;
		}
		void insert(int val){
			if(root == NULL)
				root = new ThreadedBST(val);
			else{
				try{
					root->insert(val);
				}catch(const char* msg){
					cerr<<"\n---------WARNING----------"<<endl;
					cerr<<"Exception caught at insert() method :: "<<msg<<endl;
				}
			}
		}
		ThreadedBST *deleteElement(int val){
			if(root != NULL){
				try{
					root = root->deleteElement(val);
					return root;
				}catch(const char* msg){
					cerr<<"\n---------WARNING----------"<<endl;
					cerr<<"Exception caught at deleteElement() method :: "<<msg<<endl;
				}
			}	
			return NULL;
		}
		
		ThreadedBST *search(int val){
			if(root != NULL)
				return root->search(val); 
			return NULL;
		}
		
		void inorder(){
			if(root == NULL)
				cout << "The Tree is empty!"<<endl;
			else{
				root->inorder();
			}
		}
		
		LinkedList * reverseInorder(){
			if(root != NULL)
				return root->reverseInorder();
			return NULL;
		}
		
		ThreadedBST *successor(int element){
			if(root == NULL)
				return NULL;
			ThreadedBST *treeNode = root->search(element);
			if(treeNode == NULL)
				return NULL;
			return root->successor(treeNode);
		}
		
		struct Splits *split(int k){
			if(root == NULL)
				return NULL;
			return root->split(k);
		}
		
		LinkedList * allElementsBetween(int k1, int k2){
			if(root == NULL)
				return NULL;
			return root->allElementsBetween(k1,k2);
		}
		
		ThreadedBST * kthElement(int k){
			if(root == NULL)
				return NULL;
			return root->kthElement(k);
		}
		
		void printTree(){
			if(root == NULL)
				cout<<"The tree is empty now. Hence it cannot be printed!"<<endl;
			else
				root->printTree();
		}
};


int main(int argc, char** argv) {
	int choice = -1;
	int element = -1, element2 = -1;
	TreeAPI *bst = new TreeAPI();
	ThreadedBST *treeNode = NULL;
	LinkedList *list = NULL;
	struct Splits *treeHalves = NULL;
	do{
		cout<<"\nThis is an implementation of Threaded Binary Search Tree"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Insert an element"<<endl;
		cout<<"2. Delete an element"<<endl;
		cout<<"3. Search for an element"<<endl;
		cout<<"4. Print Inorder Traversal"<<endl;
		cout<<"5. Print Reverse Inorder Traversal"<<endl;
		cout<<"6. Print successor"<<endl;
		cout<<"7. Split a copy of the tree into two halves"<<endl;
		cout<<"8. Find elements within a particular range"<<endl;
		cout<<"9. Find the k-th Largest element"<<endl;
		cout<<"10.Print an image of the tree"<<endl;
		cout<<"11.Insert a series of elements"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		cout<<"\n------------------OPERATION-------------------"<<endl;
		switch(choice){
			case 0:
				break;
			case 1: 
				cout<<"Please enter the element you want to insert: ";
				cin>>element;
				bst->insert(element);
				break;
			case 2:
				cout<<"Please enter the element you want to delete: ";
				cin>>element;
				bst->deleteElement(element);
				break;
			case 3:
				cout<<"Please enter the element you want to search: ";
				cin>>element;
				treeNode = bst->search(element);
				if(treeNode == NULL)
					cout<<"The element could not be found!"<<endl;
				else
					cout<<"The searched element is found!"<<endl;
				break;
			case 4:
				cout<<"The Inorder Traversal of the tree is as follows:"<<endl;
				bst->inorder();
				break;
			case 5:
				cout<<"The Reverse Inorder Traversal of the tree is as follows:"<<endl;
				list = bst->reverseInorder();
				if(list == NULL)
					cout << "The Tree is empty!"<<endl;
				else
					list->printList();
				break;
			case 6:
				cout<<"Please enter the element whose successor you want to search: ";
				cin>>element;
				treeNode = bst->successor(element);
				if(treeNode == NULL)
					cout<<"The successor could not be found"<<endl;
				else
					cout<<"The successor of element "<<element<<" is "<<treeNode->getKey()<<endl;
				break;
			case 7:
				cout<<"Please enter the value of k such that one tree will contain elements"<<endl;
				cout<<" with values <= k and another will contain elements with values > k : ";
				cin>>element;
				bst->split(element);
				break;
			case 8:
				cout<<"To find elements within a particular range enter k1 and k2: "<<endl;
				cout<<"Enter the value of k1: ";
				cin>>element;
				cout<<"Enter the value of k2: ";
				cin>>element2;
				list = bst->allElementsBetween(element,element2);
				cout<<"The elements between "<<element<<" and "<<element2<<" are: ";
				list->printList();
				break;
			case 9:
				cout<<"To find the kth largest element, enter the value of k: ";
				cin>>element;
				treeNode = bst->kthElement(element);
				if(treeNode == NULL)
					cout<<"The "<<element<<"th largest element could not be found!";
				else
					cout<<"The "<<element<<"th largest element is: "<<treeNode->getKey();
				break;
			case 10: 
				cout<<"An image of the tree can be produced by using the following command: "<<endl;
				cout<<"dot -Tpng graph.gv -o graph.png"<<endl;
				cout<<"The image will be named graph.png and will be present in the same path"<<endl;
				bst->printTree();
				break;
			case 11:
				cout<<"Enter the number of elements you want to insert: ";
				cin>>element;
				cout<<"Insert all the elements:"<<endl;
				for(int i=0;i<element;i++){
					cin>>element2;
					bst->insert(element2);
				}
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
		}
		cout<<"\n----------------------------------------------"<<endl;
	}while(choice != 0);
	return 0;
}
