#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stack>
#include <queue>
#include <unordered_set>
#include <set>
#include <vector>
#include <list>

using namespace std;
const string fileName = "text";
ifstream inputFile(fileName);
string line;

/*
 * Helper function used in onePoint1 and onePoint2.
 * Takes a reference to a stack, and outputs each element
 * top to bottom, popping elements along the way, until the stack is empty.
 * */
void dumpStack(stack<string> &theStack){
	while(! theStack.empty() ){
		cout << theStack.top() << '\n';
		theStack.pop();
	}
}
/*
 * Helper function used in onePoint8.
 * Takes a reference to a queue, and outputs each element
 * front to back, popping elements along the way, until the queue is empty.
 * */
void dumpQueue(queue<string> &theQueue){
	while(! theQueue.empty() ){
		cout << theQueue.front() << '\n';
		theQueue.pop();
	}
}

/*
 * Read the input one line at a time and then write the lines out in reverse order, 
 * so that the last input line is printed first, then the second last input line, and so on.
 *
 *
 *
 * Using LIFO stack to accomplish this.
 * */
void onePoint1(){
	stack<string> myStack;
	while(getline(inputFile, line)){
		myStack.push(line);
	}
	
	dumpStack(myStack);
}


/*
Read the first 50 lines of input and then write them out in reverse order. 
Read the next 50 lines and then write them out in reverse order. 
Do this until there are no more lines left to read, at which point any remaining lines should be output in reverse order.

In other words, your output will start with the 50th line, then the 49th, then the 48th, 
and so on down to the first line. This will be followed by the 100th line, 
followed by the 99th, and so on down to the 51st line. And so on.

Your code should never have to store more than 50 lines at any given time. 
 *
 *
 *
 * Also using LIFO stack to accomplish this. Using counter variable to keep track of size. Every time
 * it reaches 50, dump the stack top to bottom (see helper function) and continue.
 * */
void onePoint2(){
	stack<string> myStack;
	int count = 0;
	while(getline(inputFile, line)){
		++ count;
		myStack.push(line);
		if(count >= 50){
			dumpStack(myStack);			
			count = 0;
		}
		if(myStack.size() > 50){
			cout << "Doing it wrong!\n";
		}
	}
}


/*
 * Read the input one line at a time. At any point after reading the first 42 lines, 
 * if some line is blank (i.e., a string of length 0), then output the line that occured 
 * 42 lines prior to that one. For example, if Line 242 is blank, then your program should 
 * output line 200. This program should be implemented so that it never stores 
 * more than 43 lines of the input at any given time.
 *
 *
 *
 * Using queue to accomplish this.
 * Use count variable to keep track of size. Once it exceeds 42, do the following:
 *   - Keep track of front and back values, as specified in assignment, and output the lines as
 *     according to requirements.
 *   - Pop values from the front of queue regardless, to keep the size under 43 at all times.
 * */
void onePoint3(){
	queue<string> myQueue;
	int count = 0;
	while(getline(inputFile, line)){
		if(count <= 42){
			++ count;
		}
		myQueue.push(line);
		if(count > 42){
			if(myQueue.back() == ""){
				cout << myQueue.front() << '\n';
			}
			myQueue.pop();
		}
		if(myQueue.size() > 43){
			cout << "Doing it wrong!\n";
		}
	}
}


/*
 * Read the input one line at a time and write each line to the output if it is 
 * not a duplicate of some previous input line. Take special care so that a file 
 * with a lot of duplicate lines does not use more memory than what is 
 * required for the number of unique lines.
 *
 *
 *
 * Using set to accomplish this.
 * */
void onePoint4(){
	unordered_set<string> mySet;
	while(getline(inputFile, line)){
		if(mySet.count(line) == 0){
			cout << line << '\n';
		}
		mySet.insert(line);
	}
}

/*
 * Read the input one line at a time and write each line to the output only if 
 * you have already read this line before. (The end result is that you remove the 
 * first occurrence of each line.) Take special care so that a file with a lot of 
 * duplicate lines does not use more memory than what is required for the number of unique lines.
 *
 *
 *
 * Using set to accomplish this.
 * */
void onePoint5(){
	unordered_set<string> mySet;
	while(getline(inputFile, line)){
		if(mySet.count(line)){
			cout << line << '\n';
		}
		mySet.insert(line);
	}
}

/*
 * Read the entire input one line at a time. Then output all lines sorted by length, with the 
 * shortest lines first. In the case where two lines have the same length, resolve their order 
 * using the usual ``sorted order.'' Duplicate lines should be printed only once.
 * */


/*
 * Overriding the set comparison functor with this 
 * */
struct strcomp {
	bool operator() (const string &left, const string &right) const{
		const size_t length_left = left.length();
		const size_t length_right = right.length();
		// If the lengths are the same, fall back to the default ordering
		// If you didn't do this, you would turn {0, ..., 999} into {0, 10, 100}.
		if(length_left == length_right){
			return left < right;
		// Otherwise, sort by length
		}else{
			return length_left < length_right;
		}
	}
}; 
void onePoint6(){
	set<string, strcomp> mySet;
	// set<string> mySet;
	
	while(getline(inputFile, line)){
		mySet.insert(line);
	}
	set<string>::iterator itr;
	for(itr = mySet.begin(); itr != mySet.end(); ++itr){
		cout << *itr << '\n';
	}
}


/*
 * Do the same as the previous question except that duplicate lines should be printed 
 * the same number of times that they appear in the input. 
 * */


/*
 * Reimplementing the comparison functor because of the confusing switch around between
 * back and forth in queues. Just switched the '<' to '>'.
 * */
struct strcomp2 {
	bool operator() (const string &left, const string &right) const{
		const size_t length_left = left.length();
		const size_t length_right = right.length();
		// If the lengths are the same, fall back to the default ordering
		// If you didn't do this, you would turn {0, ..., 999} into {0, 10, 100}.
		if(length_left == length_right){
			return left > right;
		// Otherwise, sort by length
		}else{
			return length_left > length_right;
		}
	}
}; 
void onePoint7(){
	priority_queue<string, vector<string>, strcomp2> myQueue;
	while(getline(inputFile, line)){
		myQueue.push(line);
	}
	while(!myQueue.empty()){
		cout << myQueue.top() << '\n';
		myQueue.pop();
	}
}

/*
 * Read the entire input one line at a time and then output the even numbered lines 
 * (starting with the first line, line 0) followed by the odd-numbered lines.
 * */
int onePoint8() {
	queue<string> evenQueue;
	queue<string> oddQueue;
	int evenOrOdd = -1;
	while(getline(inputFile, line)) {
		if(evenOrOdd == -1) {
			evenQueue.push(line);
		}else if(evenOrOdd == 1) {
			oddQueue.push(line);
		}else {
			return 1;
		}
		evenOrOdd *= -1;
	}
	dumpQueue(evenQueue);
	dumpQueue(oddQueue);
	return 0;
}

/*
 * Read the entire input one line at a time and randomly permute the lines before outputting them. 
 * To be clear: You should not modify the contents of any line. Instead, the same collection of lines should be printed, but in a random order.  
 * * */
void onePoint9() {
	vector<string> myVector;
	while(getline(inputFile, line) ) {
		myVector.push_back(line);
	}
	int vec_size = myVector.size();
	int index;
	vector<string>::const_iterator base_itr = myVector.cbegin();
	string randomLine;
	/* TODO: This has really bad performance. */
	for(int i = vec_size - 1; i >= 0; --i) {
		index = i == 0 ? 0 : rand() % i;
		randomLine = myVector[index];
		myVector.erase(base_itr + index);
		cout << randomLine << ", current position (going backwards): " << i << '\n';
	}
}

void makeFile(){
	ofstream outputFile(fileName);
	for (int i = 0; i < 1000000; ++i) {
		outputFile << i << '\n';
	}
	outputFile.close();
}
int main(int argc, char ** argv){
	string myArg = argv[1];
	if(myArg == "1"){
		onePoint1();
	}else if(myArg == "2"){
		onePoint2();
	}else if(myArg == "3"){
		onePoint3();
	}else if(myArg == "4"){
		onePoint4();
	}else if(myArg == "5"){
		onePoint5();
	}else if(myArg == "6"){
		onePoint6();
	}else if(myArg == "7"){
		onePoint7();
	}else if(myArg == "8"){
		onePoint8();
	}else if(myArg == "9"){
		onePoint9();
	}else if(myArg == "make_file"){
		makeFile();
	}
	else{
		cout << "Please enter a valid argument.\n";
	}
	return 0;
}
