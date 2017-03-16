#include "Node.h"
#include "treeNode.h"
#include <iostream>
#include <fstream> 
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;

void shiftHead(Node*&, Node*);
Node* convertToPostfix(Node*);
void printNode(Node*, Node*, char*&, int);
void stringToStack(Node*, char*);
void bumpDown(Node*);
bool isNumber(char);
bool isOperator(char);
bool checkPrecedence(char, char);
void printHead(Node*);
void createExpressionTree(char*);

void expressionInfix(TreeNode*);
void expressionPrefix(TreeNode*);
void expressionPostfix(TreeNode*);

void bumpStack(TreeNode**&, TreeNode*);
void removeTop(TreeNode**&, TreeNode*&);
void print2dTreeNode(TreeNode**);
void visualizeTree(TreeNode*);
char* directionsToBalancedNode(int, int, char*&);


int main(){
	
	Node* stack = new Node("dank");
	cout << "Input an expression in infix notation.\n";
	cout << "Seperate characters with a space for ideal output:\n";
	char* input= new char[50];//"5 + ((1 + 2) * 4) - 3";//////correct -> 5 1 2 + 4 * + 3 −
	cin.getline(input, 50);
	
	stringToStack(stack, input);
	
	Node* current = stack;
	
	convertToPostfix(stack);//create expression tree called from inside printNode lol
}
void stringToStack(Node* head, char* string){
	int counter = 0;
	Node* current = NULL;
	while(string[counter] != '\0'){
		
		if(current != NULL){
			char c = string[counter];
			char* c2 = new char[2];
			strcpy(c2, &c);
			c2[1] = '\0';
			Node* n = new Node(c2);
			
			n->setPrevious(current);
						
			current->setNext(n);
			current = n;
			
		}else{
			char c = string[counter];
			char* c2 = new char[2];
			strcpy(c2, &c);
			c2[1] = '\0';
			head->setChar(c2);// = new Node(c);
			
			current = head;
		}
		
		counter++;
		
	}
	
	
}



void createExpressionTree(char* postfixNotation){//creates expression tree after the input is converted to postfix, runs through printNode rofl
	TreeNode** treeStack = new TreeNode*[30];
	for(int x = 0; x < 30; x++){
		treeStack[x] = new TreeNode(NULL, "null");
	}
	
	int count = 0;
	int arrayPos = 0;
	int currentLength = 0;
	char** seperatedChars = new char*[100];
	for(int x = 0; x < 30; x++){
		seperatedChars[x] = new char[4];
		seperatedChars[x][0] = '\0';
	}
	
	while(postfixNotation[count] != '\0'){//seperates Chars in here into 2d array
		char c = postfixNotation[count];
		
		if(c == ' '){
			seperatedChars[arrayPos][currentLength + 1] = '\0';
			if(strcmp(seperatedChars[arrayPos], "") == 0){
				arrayPos--;
			}
			arrayPos++;
			currentLength = 0;
			
		}else if(isOperator(c)){
			if(seperatedChars[arrayPos][0] != '\0'){
				
				seperatedChars[arrayPos][currentLength + 1] = '\0';
				arrayPos++;
				currentLength = 0;
				
			}
			
			seperatedChars[arrayPos][currentLength] = c;
			seperatedChars[arrayPos][currentLength + 1] = '\0';
			//arrayPos++;
			currentLength = 0;
			
		}else if(isNumber(c)){//digit
			seperatedChars[arrayPos][currentLength] = c;
			seperatedChars[arrayPos][currentLength + 1] = '\0';
			currentLength++;
		}
		
		count ++;
	}


	for(int x = 0; x < arrayPos + 1; x++){//stack constructed here
		
		if(!isOperator(seperatedChars[x][0])){
			
			char* c2 = new char[4];
			strcpy(c2, seperatedChars[x]);
			
			TreeNode* tempNode = new TreeNode(NULL, c2);
			bumpStack(treeStack, tempNode);
			
		}else{
			
			char* c2 = new char[4];
			strcpy(c2, seperatedChars[x]);
			
			TreeNode* tempNode = new TreeNode(NULL, c2);
			
			TreeNode* tempNode2;
			removeTop(treeStack, tempNode2);
			
			TreeNode* tempNode3;
			removeTop(treeStack, tempNode3);//removes top of stack and places it in tempNode3
			
			tempNode->setLeft(tempNode3);
			tempNode->setRight(tempNode2);
			
			tempNode3->setParent(tempNode);
			tempNode2->setParent(tempNode);
			bumpStack(treeStack, tempNode);
		}
		
	}

	cout << "\n\nInput which format you want you thing in, (1 == infix, 2 == prefix, 3 == postfix) " << endl;	
	
	char* input = new char[2];
	cin.getline(input, 2);
	if(input[0] == '1'){
		expressionInfix(treeStack[0]);
	}else if(input[0] == '2'){
		expressionPrefix(treeStack[0]);
	}else{
		cout << "test" << endl;
		expressionPostfix(treeStack[0]);
	}
	
}

void expressionInfix(TreeNode* expressionTree) {//recursive 
	if ((expressionTree != NULL)) {
		
		expressionInfix(expressionTree->getLeft());
		if(strcmp(expressionTree->getChar(), "null") != 0){
			cout << expressionTree->getChar() << " ";
		}
		expressionInfix(expressionTree->getRight());
	}
}

void print2dTreeNode(TreeNode** stack){
	int count = 0;
	while(count < 30){
		expressionPostfix(stack[count]);//defaults to print in postfix
		cout << "\n";
		
		if(stack[count]->getChar() == "null"){
			break;
		}
		count++;
	}
}

void expressionPostfix(TreeNode* expressionTree) {//recursive 
	if ((expressionTree != NULL)) {
		
		expressionPostfix(expressionTree->getLeft());
		expressionPostfix(expressionTree->getRight());
		if(strcmp(expressionTree->getChar(), "null") != 0){
			cout << expressionTree->getChar() << " ";
		}
		
	}
}

void expressionPrefix(TreeNode* expressionTree) {//recursive 
	if ((expressionTree != NULL)) {
		
		if(strcmp(expressionTree->getChar(), "null") != 0){
			cout << expressionTree->getChar() << " ";
		}
		expressionPrefix(expressionTree->getLeft());
		expressionPrefix(expressionTree->getRight());
	}
}

void bumpStack(TreeNode**& stack, TreeNode* newTree){//bumps stack pretty shittely, the classic break to get out of a while loop
	int count = 0;
	TreeNode* lastMove = NULL;
	while(true){
		//cout << "Count = " << count << " : " << stack[count + 1]->getChar() << endl;
		if(stack[count + 1]->getChar() == "null"){
			if(lastMove != NULL){
				TreeNode* tNode = stack[count + 1];
				stack[count + 1] = lastMove;
				lastMove = tNode;
			}else{
				lastMove = stack[count + 1];
				stack[count + 1] = stack[count];
			}
				
			break;
		}
		if(lastMove != NULL){
			TreeNode* tNode = stack[count + 1];
			stack[count + 1] = lastMove;
			lastMove = tNode;
		}else{
			lastMove = stack[count + 1];
			stack[count + 1] = stack[count];
		}
		

		count++;
		if(count == 29){
			//break;
			cout << "Fatal Error: bumpstack" << endl;
			exit(420);
		}
	}
	
	stack[0] = newTree;
}

void removeTop(TreeNode**& stack, TreeNode*& fromTop){//fromtop should be null, removes top of stack pretty shittely
	int count = 0;
	
	
	fromTop = stack[0];

	while(true){//same as bump but backwards
		stack[count] = stack[count+1];
		
		if(stack[count]->getChar() == "null"){
			stack[count+1]->setChar("null");
			break;
		}
		//cout << stack[count]->getChar() << endl;
		count++;
		if(count == 29){
			cout << "Fatal Error: remove top" << endl;
			exit(421);
		}
	}
	
}

void printNode(Node* sourceNode, Node* currentNode, char*& postfixNotation, int count){//prints node thr
	if((currentNode)->getPrevious() == NULL) {//if the currentNode is the first node in the list
		try{//this runs to prevent an error when list is empty, probably never fails here
			//cout << currentNode->getChar();
			
			char* c2 = currentNode->getChar();
			postfixNotation[count] = c2[0];
			count++;
			
			if(sourceNode->getNext() != NULL){
				currentNode = sourceNode->getNext();
				printNode(sourceNode, currentNode, postfixNotation, count);
			}
			
		}catch (const exception& e){
			cout << "StudentList is empty.";
		}

	}else{
		//cout << currentNode->getChar();

		char* c2 = currentNode->getChar();
		postfixNotation[count] = c2[0];
		count++;
		
		if(currentNode->getNext() != NULL){
			currentNode = currentNode->getNext();
			printNode(sourceNode, currentNode, postfixNotation, count);
			
		}else{//end of printing, runs the expression tree rofl
			
			postfixNotation[count + 1] = '\0';
			cout << "Postfix: " << postfixNotation << endl;
			createExpressionTree(postfixNotation);
			
			cout << endl;
		}
	}
	
	
	
}


Node* convertToPostfix(Node* head){//from last assignment, converts a node to postfix
	cout << "\n\n";
	Node* tCurrent = head;
	Node* outputQ = new Node(" ");
	Node* operatorQ = new Node(" ");
	
	
	while(tCurrent != NULL){//figures out many numbers an operator should move down
		char* cPoint = (tCurrent)->getChar();
		char c = cPoint[0];
		
		if(isNumber(c)){//if operand than put to output queue

			outputQ->setNext(tCurrent);
			Node* newCurrent = tCurrent->getNext();
			tCurrent->setPrevious(outputQ);
			tCurrent->setNext(NULL);
			tCurrent = newCurrent;
			outputQ = outputQ->getNext();
		}else if(isOperator(c)){

			char* cXPoint = (operatorQ)->getChar();
			char cX = cXPoint[0];
			
			if(cX == ' ' || cX == '('){//FINE

				operatorQ->setNext(tCurrent);
				Node* newCurrent = tCurrent->getNext();
				tCurrent->setPrevious(operatorQ);
				tCurrent->setNext(NULL);
				tCurrent = newCurrent;
				operatorQ = operatorQ->getNext();
				
				
			}else if(checkPrecedence(cX, c)){//if the incoming has higher precendence than the one on the operatorQueue
				cout << c << endl;
				cout << cX << endl;
				operatorQ->setNext(tCurrent);//FINE
				Node* newCurrent = tCurrent->getNext();
				tCurrent->setPrevious(operatorQ);
				tCurrent->setNext(NULL);
				tCurrent = newCurrent;
				operatorQ = operatorQ->getNext();
				
			}else if(!checkPrecedence(cX, c)){//if it has lower or the same operator as one on the queue

				int co = 0;
				while(!checkPrecedence(cX, c)){
					if(operatorQ->getPrevious() != NULL){
						outputQ->setNext(operatorQ);//swaps top of operator stack onto output stack
						Node* previousOperator = operatorQ->getPrevious();
						operatorQ->setPrevious(outputQ);
						operatorQ->setNext(NULL);
						outputQ = outputQ->getNext();
						operatorQ = previousOperator;//moves top of operator stack onto output stack
					}else{
						break;
					}
					if(operatorQ == NULL){
						break;
					}
					//co++;
					//cout << co;
					cXPoint = operatorQ->getChar();
					cX = cXPoint[0];
					
				}
				cout << tCurrent->getChar();
				operatorQ->setNext(tCurrent);
				Node* newCurrent = tCurrent->getNext();
				tCurrent->setPrevious(operatorQ);
				tCurrent->setNext(NULL);
				tCurrent = newCurrent;
				operatorQ = operatorQ->getNext();
				
			}
		}else if(c == '('){//if left parentheses shove into operator queue

			operatorQ->setNext(tCurrent);
			Node* newCurrent = tCurrent->getNext();
			tCurrent->setPrevious(operatorQ);
			tCurrent->setNext(NULL);
			tCurrent = newCurrent;
			operatorQ = operatorQ->getNext();
			
		}else if(c == ')'){//
 
			tCurrent = tCurrent->getNext();
			char* opTemp = operatorQ->getChar();
			char opChar = opTemp[0];
			int co = 0;
			
			while(opChar != '('){//place operators on output until u find the left parentheses
				if(operatorQ->getPrevious() != NULL){
					Node* previousOp = operatorQ->getPrevious();
					outputQ->setNext(operatorQ);
					operatorQ->setPrevious(outputQ);
					operatorQ->setNext(NULL);
					outputQ = outputQ->getNext();
					operatorQ= previousOp;
				}else{
					break;
				}
				opTemp = operatorQ->getChar();
				opChar = opTemp[0];
				
				//co++;
				//cout << co;
				
			}
			Node* o = operatorQ->getPrevious();
			//operatorQ->safeDelete();//removes right parentheses
			operatorQ = o;
		}else if(c == ' ' ){

			outputQ->setNext(tCurrent);
			Node* newCurrent = tCurrent->getNext();
			tCurrent->setPrevious(outputQ);
			tCurrent->setNext(NULL);
			tCurrent = newCurrent;
			outputQ = outputQ->getNext();
			
		}
		//printHead(operatorQ);
		//printHead(operatorQ);
	}
	char* opTemp = operatorQ->getChar();
	char opChar = opTemp[0];

	
	while(isOperator(opChar)){
		Node* previousOp = operatorQ->getPrevious();
		outputQ->setNext(operatorQ);
		operatorQ->setPrevious(outputQ);
		operatorQ->setNext(NULL);
		outputQ = outputQ->getNext();
		operatorQ= previousOp;
		if(operatorQ == NULL){
			break;
		}
		
		opTemp = operatorQ->getChar();
		opChar = opTemp[0];
		
		
	}
	

	printHead(outputQ);
	return NULL;
}

void printHead(Node* current){//prints the head of node, goes upwards to the most parenting parent
	int count = 0;
	while(current->getPrevious() != NULL){
		count++;
		current = current->getPrevious();
	}
	cout << count << " below current." << endl;//good to know how many is the boy
	Node* tCurrent = current;
	
	char* postfixNotation = new char[10000];
	count = 0;
	printNode(current, tCurrent, postfixNotation, count);
}

void visualizeTree(TreeNode* head){
	int currentDepth = 0;
	int depthProgression = 1;
	TreeNode* tCurrent = head;

	while(tCurrent != NULL){
		
		if(currentDepth == 0){
			cout << "0: " ;
			cout << tCurrent->getChar() << " || ";
		}else{
			char* directions;
			directionsToBalancedNode(currentDepth, depthProgression, directions);//sets direction
			int count = 0;
			while(directions[count] != '\0'){//adds newNode to the most balanced spot by following the directions provided
				if(directions[count] == 'L'){
					if(tCurrent->getLeft() != NULL){
						tCurrent = tCurrent->getLeft();
					}else{
						tCurrent = NULL;
						break;
					}
					
				}else{
					if(tCurrent->getRight() != NULL){
						tCurrent = tCurrent->getRight();
					}else{
						tCurrent = NULL;
						break;
					}
				}

				count++;
			}
			
			if(tCurrent == NULL){
				break;
			}else{
				if(depthProgression == 1){
					cout << currentDepth << ": ";
				}
				
				cout << tCurrent->getChar() << " || ";
			}
			
		}
		
		depthProgression++;
		if(depthProgression > pow(2, currentDepth)){//designates where the most balanced spot on the tree to add next
			depthProgression = 1;
			currentDepth++;
			cout << "\n";
		}
		if(tCurrent != NULL){
			tCurrent = head;
		}
	}
	
	cout << "\n\n";
}

char* directionsToBalancedNode(int currentDepth, int depthProgression, char*& directions){//this gives directions to next balanced node in the heap
	directions = new char[currentDepth + 1];
	
	for(int x  = currentDepth; x > 0; x--){//builds upwards from the designated location
		if(depthProgression % 2 ==  0){
			directions[x - 1] = 'R';
		}else{
			directions[x - 1] = 'L';
		}
		int newProgression = 1;
		int tProgression =  depthProgression;// 2
		bool running = true;
		
		while(running){
			tProgression =  tProgression -2;
			if(tProgression > 0){
				//cout << tProgression << "TProg"<< endl;
				newProgression++;
			}else{
				//cout << newProgression << endl;
				running = false;
			}
		}
		depthProgression = newProgression;
	}
	directions[currentDepth] = '\0';
	
	return directions;
}

bool checkPrecedence(char o1, char o2){//left associative, checks if first operator has higher precedence than second
//false on equavelence
	if(o1 == '^'){
		if(o2 == '^'){
			return false;
		}else if(o2 == '*'){
			return false;
		}else if(o2 == '/'){
			return false;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '*'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return false;
		}else if(o2 == '/'){
			return false;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '/'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return true;
		}else if(o2 == '/'){
			return false;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '+'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return true;
		}else if(o2 == '/'){
			return true;
		}else if(o2 == '+'){
			return false;
		}else if(o2 == '-'){
			return false;
		}
	}else if(o1 == '-'){
		if(o2 == '^'){
			return true;
		}else if(o2 == '*'){
			return true;
		}else if(o2 == '/'){
			return true;
		}else if(o2 == '+'){
			return true;
		}else if(o2 == '-'){
			return false;
		}
	}
	
	return NULL;
}

bool isNumber(char c){
	if(c == '0'){
		return true;
	}else if(c == '1'){
		return true;
	}else if(c == '2'){
		return true;
	}else if(c == '3'){
		return true;
	}else if(c == '4'){
		return true;
	}else if(c == '5'){
		return true;
	}else if(c == '6'){
		return true;
	}else if(c == '7'){
		return true;
	}else if(c == '8'){
		return true;
	}else if(c == '9'){
		return true;
	}
	return false;
}

bool isOperator(char c){
	if(c == '-'){
		return true;
	}else if(c == '+'){
		return true;
	}else if(c == '/'){
		return true;
	}else if(c == '*'){
		return true;
	}else if(c == '^'){
		return true;
	}
	
	return false;
		
}

void bumpDown(Node* test){
	if(test->getNext() == NULL){

	}else{
		Node* next = test->getNext();
		char* nextChar = next->getChar();
		bool nextBool = next->getOperatorMoved();
		
		next->setChar(test->getChar());
		next->setOperatorMoved(test->getOperatorMoved());
		
		test->setChar(nextChar);
		test->setOperatorMoved(nextBool);

	}
	
}

void shiftHead(Node*& oldHead, Node* newHead){//works
	newHead->setNext(oldHead->getNext());
	newHead->setPrevious(NULL);
	delete oldHead->getChar();
	oldHead = newHead;
}