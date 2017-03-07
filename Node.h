#pragma warning
#ifndef NODE_H
#define NODE_H

#include <string.h>
#include <iostream>

class Node
{
	private:
		char* c;
		bool operatorMoved;
		Node* next;
		Node* previous;
	public:
		Node(char*);
		~Node();
		void setChar(char*);
		char* getChar();
		Node* getNext();
		void setNext(Node*);
		Node* getPrevious();
		void setPrevious(Node*);
		void safeDelete();
		void setOperatorMoved(bool);
		bool getOperatorMoved();
};
#endif

