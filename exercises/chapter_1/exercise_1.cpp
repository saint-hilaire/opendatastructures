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
void dumpStack(stack<string> &theStack)
{
	while(!theStack.empty()) {
		cout << theStack.top() << '\n';
		theStack.pop();
	}
}
void dumpIntStack(stack<int> &theStack)
{
	while(!theStack.empty()) {
		cout << theStack.top() << '\n';
		theStack.pop();
	}
}
/*
 * Helper function used in onePoint8.
 * Takes a reference to a queue, and outputs each element
 * front to back, popping elements along the way, until the queue is empty.
 * */
void dumpQueue(queue<string> &theQueue) {
	while(!theQueue.empty()){
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
void onePoint1()
{
	stack<string> myStack;
	while(getline(inputFile, line)) {
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
void onePoint2()
{
	stack<string> myStack;
	int count = 0;
	while(getline(inputFile, line)) {
		++ count;
		myStack.push(line);
		if(count >= 50) {
			dumpStack(myStack);			
			count = 0;
		}
		if(myStack.size() > 50) {
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
void onePoint3()
{
	queue<string> myQueue;
	int count = 0;
	while(getline(inputFile, line)) {
		if(count <= 42)
			++ count;
		myQueue.push(line);
		if(count > 42) {
			if(myQueue.back() == "")
				cout << myQueue.front() << '\n';
			myQueue.pop();
		}
		if(myQueue.size() > 43)
			cout << "Doing it wrong!\n";
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
void onePoint4()
{
	unordered_set<string> mySet;
	while(getline(inputFile, line)) {
		if(mySet.count(line) == 0)
			cout << line << '\n';
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
void onePoint5()
{
	unordered_set<string> mySet;
	while(getline(inputFile, line)) {

		if(mySet.count(line))
			cout << line << '\n';

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
struct strcomp
{
	bool operator() (const string &left, const string &right) const
	{
		const size_t length_left = left.length();
		const size_t length_right = right.length();
		// If the lengths are the same, fall back to the default ordering
		// If you didn't do this, you would turn {0, ..., 999} into {0, 10, 100}.
		if(length_left == length_right)
			return left < right;
		// Otherwise, sort by length
		else
			return length_left < length_right;
	}
}; 
void onePoint6()
{
	set<string, strcomp> mySet;
	// set<string> mySet;
	
	while(getline(inputFile, line)) {
		mySet.insert(line);
	}
	set<string>::iterator itr;
	for(itr = mySet.begin(); itr != mySet.end(); ++itr) {
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
struct strcomp2
{
	bool operator() (const string &left, const string &right) const
	{
		const size_t length_left = left.length();
		const size_t length_right = right.length();
		// If the lengths are the same, fall back to the default ordering
		// If you didn't do this, you would turn {0, ..., 999} into {0, 10, 100}.
		if(length_left == length_right)
			return left > right;
		// Otherwise, sort by length
		else
			return length_left > length_right;
	}
}; 
void onePoint7()
{
	priority_queue<string, vector<string>, strcomp2> myQueue;

	while(getline(inputFile, line))
		myQueue.push(line);

	while(!myQueue.empty()) {
		cout << myQueue.top() << '\n';
		myQueue.pop();
	}
}

/*
 * Read the entire input one line at a time and then output the even numbered lines 
 * (starting with the first line, line 0) followed by the odd-numbered lines.
 * */
int onePoint8()
{
	queue<string> evenQueue;
	queue<string> oddQueue;
	int evenOrOdd = -1;
	while(getline(inputFile, line)) {
		if(evenOrOdd == -1)
			evenQueue.push(line);
		else if(evenOrOdd == 1)
			oddQueue.push(line);
		else
			return 1;
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
void onePoint9()
{
	vector<string> myVector;
	while(getline(inputFile, line)) {
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

/*
 * A matched string is a sequence of {, }, (, ), [, and ] characters that are properly matched. 
 * For example, ``{{()[]}}'' is a matched string, but this ``{{()]}'' is not, 
 * since the second { is matched with a ]. Show how to use a stack so that, 
 * given a string of length $ \mathtt{n}$, you can determine if it is a matched 
 * string in O(n) time.
 * */
bool closing_closes_opening(char &opening, char &closing)
{
	switch(opening) {
		case '{':
			return closing == '}';
		case '(':
			return closing == ')';
		case '[':
			return closing == ']';
		case '<':
			return closing == '>';
		default:
			return false;
	}
	
}
bool three_matched_string(char *str)
{
	// Could have used a mapping, but we want to implement this only
	// with a stack, so we use this and the above helper function.
	stack<char> myStack;
	bool ok = false;
	for(char c = *str; c; c = *++str) {
		switch(c) {
			case '{':
			case '(':
			case '[':
			case '<':
				ok = true;
				myStack.push(c);
				break;
			default:
				if(myStack.size() > 0 && closing_closes_opening(myStack.top(), c))
					myStack.pop();
				else
					myStack.push(c);
				break;
		}
	}
	return ok && myStack.size() == 0;
}

/*
 * Suppose you have a Stack, that supports only the push(x) and pop() operations. 
 * Show how, using only a FIFO Queue, q, you can reverse the order of all elements in s.
 * */
stack<int> four_reverse_stack_with_queue(stack<int> theStack)
{
	queue<int> theQueue;
	int elem;
	while(! theStack.empty()) {
		elem = theStack.top();
		theQueue.push(elem);
		theStack.pop();
	}

	while(! theQueue.empty()) {
		elem = theQueue.front();
		theStack.push(elem);
		theQueue.pop();
	}
	return theStack;
}

/*
 * Using a USet, implement a Bag. A Bag is like a USet -- it supports the add(x), remove(x) and find(x) methods--but 
 * it allows duplicate elements to be stored. The find(x) operation in a Bag returns some element (if any) that is equal 
 * to x. In addition, a Bag supports the findAll(x) operation that returns a list of all elements in the Bag that 
 * are equal to x.
 * */

typedef tuple<string, int> collection;
typedef set<collection> bag;
typedef bag::iterator bag_iterator;
class Bag
{
	private:
		bag _bag;
	public:
		bag getBag() {
			return _bag;
		}
		void add(string value)
		{
			bag_iterator itr = find(value);
			if(itr == _bag.end()) {
				collection new_coll(value, 1);
				_bag.insert(new_coll);
			} else {
				collection coll = *itr;
				get<1>(coll) ++;
				_bag.insert(coll);
				_bag.erase(itr);
			}
		}
		void remove(string value)
		{
			bag_iterator itr = find(value);
			if(itr != _bag.end()) {
				collection coll = *itr;
				if(get<1>(coll) > 1) {
					get<1>(coll) --;
					_bag.insert(coll);
				}
				_bag.erase(itr);
			}
		}
		void dumpAll()
		{
			bag_iterator itr;
			for(itr = _bag.begin(); itr != _bag.end(); ++itr) {
				cout << get<0>(*itr) << ": " << get<1>(*itr) << "\n";
			}
		}
		bool hasElem(string value)
		{
			bool has = false;
			for (bag_iterator itr = _bag.begin(); itr != _bag.end(); ++itr) {
				if(get<0>(*itr).compare(value) == 0) {
					has = true;
				}
			}
			return has;
		}
		bag_iterator find(string value)
		{
			bag_iterator itr;
			for(itr = _bag.begin(); itr != _bag.end(); ++itr) {
				collection coll = *itr;
				if(get<0>(coll).compare(value) == 0) {
					return itr;
				}
			}
			return _bag.end();
		}
		collection findAll(string value)
		{
			bag_iterator itr = find(value);
			if(itr == _bag.end()) {
				collection coll("", 0);
				return coll;
			} else {
				return *itr;
			}
		}
};

void doFive()
{
	Bag myBag;
	char userIn;
	string element;
	bool goOn = true;
	collection coll;
	bag_iterator itr;
	while(goOn) {
		cout << "This is your bag:\n";
		myBag.dumpAll();
		cout << "Choose an action:\n";
		cout << "a: Add an element\n";
		cout << "r: Remove an element\n";
		cout << "f: Find an element\n";
		cout << "F: Find all elements\n";
		cout << "x: Quit\n";
		cin >> userIn;
		switch(userIn) {
			case 'a':
				cout << "Enter a value: ";
				cin >> element;
				myBag.add(element);
				break;
			case 'r':
				cout << "Enter a value: ";
				cin >> element;
				myBag.remove(element);
				break;
			case 'f':
				cout << "Enter a value: ";
				cin >> element;
				if(myBag.hasElem(element)) {
					cout << "Found it!\n";
				} else {
					cout << "Didn't find it!\n";
				}
				break;
			case 'F':
				cout << "Enter a value: ";
				cin >> element;
				coll = myBag.findAll(element);
				cout << get<0>(coll) << ": " << get<1>(coll) << '\n';
				break;
			case 'x':
				goOn = false;
				break;
			default:
				break;
		}
	}
}


	
void makeFile()
{
	ofstream outputFile(fileName);
	for (int i = 0; i < 1000000; ++i) {
		outputFile << i << '\n';
	}
	outputFile.close();
}

int main(int argc, char ** argv)
{
	string myArg = argv[1];
	if(myArg == "1")
		onePoint1();
	else if(myArg == "2")
		onePoint2();
	else if(myArg == "3")
		onePoint3();
	else if(myArg == "4")
		onePoint4();
	else if(myArg == "5")
		onePoint5();
	else if(myArg == "6")
		onePoint6();
	else if(myArg == "7")
		onePoint7();
	else if(myArg == "8")
		onePoint8();
	else if(myArg == "9")
		onePoint9();
	else if(myArg == "three") {
		if(three_matched_string(argv[2])) {
			cout << "That's a matched string." << '\n';
		} else {
			cout << "That's not a matched string." << '\n';
		}
	} else if(myArg == "four") {
		stack<int> theStack;
		// TODO: Implement support for comma-separated values passed as CLI args.
		for(int i = 0; i < 10; ++i) {
			theStack.push(i);
		}
		stack<int> reversedStack = four_reverse_stack_with_queue(theStack);
		cout << "The stack: \n";
		// TODO: Improve dumpStack() so it doesn't require strings, so we don't
		//       have to use this special dumpIntStack();
		dumpIntStack(theStack);
		cout << "The reversed stack: \n";
		dumpIntStack(reversedStack);
	} else if(myArg == "five")
		doFive();
	else if(myArg == "make_file")
		makeFile();
	else
		cout << "Please enter a valid argument.\n";
	return 0;
}
