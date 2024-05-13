linkedListType.h :

#ifndef H_LinkedListType
#define H_LinkedListType
#include <iostream>
using namespace std;

template <class Type>
class nodeType {
public:
	Type info;
	nodeType<Type> *link;

	nodeType() {
		this -> link = NULL;
	}
};

template <class Type>
class linkedListType {
public:
	linkedListType() {
		first = last = NULL;
		count = 0;
	}

	~linkedListType() {
		initializeList();
 	}

 	void initializeList() {
 		while (first) {
			nodeType<Type> *save = first;
			first = first -> link;
			delete save;
		}
		first = last = NULL;
 	}

 	void print() {
 		nodeType<Type> *current = first;

 		while (current) {
 			cout << current -> info << " ";
 			current = current -> link;
 		}
 		cout << "\n";
 	}

	nodeType<Type> *first;
	nodeType<Type> *last;
	int count;
	
};

#endif
unorderedLinkedList.h :

#ifndef H_UnorderedLinkedList
#define H_UnorderedLinkedList
#include"linkedListType.h"


//***********************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement the basic
// properties of an unordered linked list. This class is
// derived from the class linkedListType.
//***********************************************************
template < class Type >
class unorderedLinkedList : public linkedListType < Type > {
public:
	bool search(const Type& searchItem) const;
	//Function to determine whether searchItem is in the list.
	//Postcondition: Returns true if searchItem is in the list,
	// otherwise the value false is returned.
	void insertfirst(const Type& newItem);
	//Function to insert newItem at the beginning of the list.
	//Postcondition: this->first points to the new list, newItem is
	// inserted at the beginning of the list, this->last points to
	// the this->last node, and this->count is incremented by 1.
	//
	void insertlast(const Type& newItem);
	//Function to insert newItem at the end of the list.
	//Postcondition: this->first points to the new list, newItem is
	// inserted at the end of the list, this->last points to the
	// this->last node, and this->count is incremented by 1.
	void deleteNode(const Type& deleteItem);
	//Function to delete deleteItem from the list.
	//Postcondition: If found, the node containing deleteItem

	// is deleted from the list. this->first points to the this->first
	// node, this->last points to the this->last node of the updated
	// list, and this->count is decremented by 1.

	void changeByConstant(const char &opr, const Type& constant);

	void checkEach2();

	void duplicateORremove(int pos);

	void split(const Type& item, unorderedLinkedList& L1, unorderedLinkedList& L2);
};

template < class Type >
bool unorderedLinkedList < Type > ::
search(const Type& searchItem) const {
	nodeType < Type >* current; //pointer to traverse the list
	bool found = false;
	current = this->first; //set current to point to the this->first
	//node in the list
	while (current != NULL && !found) //search the list
		if (current->info == searchItem) //searchItem is found
			found = true;
		else
			current = current->link; //make current point to
	//the next node
	return found;
} //end search

template < class Type >
void unorderedLinkedList < Type > ::insertfirst(const Type& newItem) {
	nodeType < Type >* newNode; //pointer to create the new node
	newNode = new nodeType < Type >; //create the new node
	newNode->info = newItem; //store the new item in the node
	newNode->link = this->first; //insert newNode before this->first
	this->first = newNode; //make this->first point to the actual this->first node
	this->count++; //increment this->count
	if (this->last == NULL) //if the list was empty, newNode is also
		//the this->last node in the list
		this->last = newNode;
} //end insertthis->first

template < class Type >
void unorderedLinkedList < Type > ::insertlast(const Type& newItem) {
	nodeType < Type >* newNode; //pointer to create the new node
	newNode = new nodeType < Type >; //create the new node
	newNode->info = newItem; //store the new item in the node
	newNode->link = NULL; //set the link field of newNode to NULL
	if (this->first == NULL) //if the list is empty, newNode is
	//both the this->first and this->last node
		{
		this->first = newNode;
		this->last = newNode;
		this->count++; //increment this->count
	}
	else //the list is not empty, insert newNode after this->last
	{
		this->last->link = newNode; //insert newNode after this->last
		this->last = newNode; //make this->last point to the actual
		//this->last node in the list
		this->count++; //increment this->count
	}
} //end insertthis->last

template < class Type >
void unorderedLinkedList < Type > ::deleteNode(const Type& deleteItem) {
	nodeType < Type >* current; //pointer to traverse the list
	nodeType < Type >* trailCurrent; //pointer just before current
	bool found;
	if (this->first == NULL) //Case 1; the list is empty.
		cout << "Cannot delete from an empty list." <<
		endl;
	else {
		if (this->first->info == deleteItem) //Case 2
		{
			current = this->first;
			this->first = this->first->link;
			this->count--;
			if (this->first == NULL) //the list has only one node
				this->last = NULL;
			delete current;
		}
		else //search the list for the node with the given info
		{
			found = false;
			trailCurrent = this->first; //set trailCurrent to point
			//to the this->first node
			current = this->first->link; //set current to point to
			//the second node
			while (current != NULL && !found) {
				if (current->info != deleteItem) {
					trailCurrent = current;
					current = current->link;
				}
				else
					found = true;
			} //end while
			if (found) //Case 3; if found, delete the node
			{
				trailCurrent->link = current->link;
				this->count--;
				if (this->last == current) //node to be deleted was the
					//this->last node
					this->last = trailCurrent; //update the value of this->last
				delete current; //delete the node from the list
			}
			else
				cout << "The item to be deleted is not in " <<
				"the list." << endl;
		} //end else
	} //end else
} //end deleteNode

template < class Type >
void unorderedLinkedList < Type > ::changeByConstant(const char &opr, const Type& constant) {
	nodeType<Type> *current = this -> first;
	if (opr == '+') {
		while (current) {
			current -> info += constant;
			current = current -> link;
		}
	}
	else if (opr == '-') {
		while (current) {
			current -> info -= constant;
			current = current -> link;
		}
	}
	else
		cout << "Unsupported operation!\n";
}

template < class Type >
void unorderedLinkedList < Type > ::checkEach2() {
	nodeType<Type> *current = this -> first;

	while (current && current -> link) {
		if (current -> info > current -> link -> info)
			current -> info -= current -> link -> info;
		else
			current -> link -> info -= current -> info;

		current = current -> link -> link;
	}
}

template < class Type >
void unorderedLinkedList < Type > ::duplicateORremove(int pos) {

	while (this -> count && pos--) {
		deleteNode(this -> first -> info);
	}

	if (this -> count == 0)
		return;
	else {
		nodeType<Type> *current = this -> first -> link;
	
		while (current) {
			nodeType<Type> *newNode = new nodeType<Type>();
			newNode -> info = current -> info;
			newNode -> link = current -> link;
			current -> link = newNode;
			current = current -> link -> link;
		}
	}
}

template < class Type >
void unorderedLinkedList < Type > ::split(const Type& item, unorderedLinkedList& L1, unorderedLinkedList& L2) {
	nodeType<Type> *current = this -> first;

	while (current) {
		if (current -> info < item)
			L1.insertlast(current -> info);
		else
			L2.insertlast(current -> info);

		current = current -> link;
	}
}

#endif
memberlinkedlist.cpp :

#include <iostream>
#include <string>
#include <cassert>
#include "unorderedLinkedList.h"
using namespace std;

int main()
{
	unorderedLinkedList <int> L,L1,L2;
	L.insertlast(2);
	L.insertlast(1);
	L.insertlast(3);
	L.insertlast(4);
	L.insertlast(5);
	L.insertlast(3);
	L.insertlast(0);

	cout << "List L before L.changeByConstant(\'+\', 3) contains:" << endl;
	L.print();
	L.changeByConstant('+', 3);
	cout << "List L after L.changeByConstant(\'+\', 3) contains:" << endl;
	L.print();

	L.initializeList();
	L.insertlast(2);
	L.insertlast(1);
	L.insertlast(3);
	L.insertlast(4);
	L.insertlast(5);
	L.insertlast(3);
	L.insertlast(0);
	cout << "List L before L.changeByConstant(\'-\', 3) contains:" << endl;
	L.print();
	L.changeByConstant('-', 3);
	cout << "List L after L.changeByConstant(\'-\', 3) contains:" << endl;
	L.print();


	L.initializeList();
	L.insertlast(2);
	L.insertlast(1);
	L.insertlast(3);
	L.insertlast(4);
	L.insertlast(5);
	L.insertlast(3);
	L.insertlast(0);
	cout << "List L before L.checkEach2() contains:" << endl;
	L.print();
	L.checkEach2();
	cout << "List L after L.checkEach2() contains:" << endl;
	L.print();

	L.initializeList();
	L.insertlast(5);
	L.insertlast(3);
	L.insertlast(10);
	L.insertlast(3);
	L.insertlast(6);
	L.insertlast(4);
	L.insertlast(3);
	cout << "List L before L.checkEach2() contains:" << endl;
	L.print();
	L.checkEach2();
	cout << "List L after L.checkEach2() contains:" << endl;
	L.print();


	L.initializeList();
	L.insertlast(12);
	L.insertlast(11);
	L.insertlast(13);
	L.insertlast(14);
	L.insertlast(15);
	L.insertlast(13);
	L.insertlast(10);
	cout << "List L before L.duplicateORremove(3) contains:" << endl;
	L.print();
	L.duplicateORremove(3);
	cout << "List L after L.duplicateORremove(3) contains:" << endl;
	L.print();


	L.initializeList();
	L.insertlast(2);
	L.insertlast(1);
	L.insertlast(3);
	L.insertlast(4);
	L.insertlast(5);
	L.insertlast(3);
	L.insertlast(0);
	cout << "List L before L.split(3,L1,L2) contains:" << endl;
	L.print();
	L.split(3,L1,L2);
	cout << "List L after L.split(3,L1,L2) contains:" << endl;
	L.print();
	cout << "List L1 after L.split(3,L1,L2) contains:" << endl;
	L1.print();
	cout << "List L2 after L.split(3,L1,L2) contains:" << endl;
	L2.print();
	return 0;
}
