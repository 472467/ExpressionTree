#include "Node.h"

Node::Node(char* c2){
	c = new char[2];
	operatorMoved = false;
	strcpy(c, c2);
	next = NULL;
	previous = NULL;
	
}

Node::~Node(){
	delete c;
}


void Node::safeDelete(){
	if(getNext() != NULL && getPrevious() != NULL){
		
		
		getNext()->setPrevious(previous);
		getPrevious()->setNext(getNext());

		delete this;
		
	}else if(getNext() != NULL && getPrevious() == NULL){//localPrevious is NULL, means its head of NODE
		setChar((getNext())->getChar());
		if(getNext()->getNext() != NULL){//this kills the next one and takes data of its next
			setNext((getNext())->getNext());
			(getNext()->getNext())->setPrevious(this);
			delete getNext();

		}else{
			delete getNext();
			setNext(NULL);

		}
	}else if(getPrevious() != NULL && getNext() == NULL){
		getPrevious()->setNext(NULL);
		delete this;

	}else if(getPrevious() == NULL && getNext() == NULL){
		delete this;

	}

}

void Node::setChar(char* c2){
	c = c2;
	//strcpy(c, c2);
}

char* Node::getChar(){
	return c;
}

Node* Node::getPrevious(){
	return previous;
}

void Node::setPrevious(Node* p){
	previous = p;
}

Node* Node::getNext(){
	return next;
}

void Node::setNext(Node* n){
	next = n;
	
}

bool Node::getOperatorMoved(){
	return operatorMoved;
}

void Node::setOperatorMoved(bool opM){
	operatorMoved = opM;
	
}