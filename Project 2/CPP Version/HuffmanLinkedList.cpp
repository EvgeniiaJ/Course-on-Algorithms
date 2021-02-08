#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class ListNode {
	string charString;
	int probability;
	ListNode* next;

public:
	ListNode() : charString(""), probability(0), next(NULL) {}

	ListNode(string charString, int probability, ListNode* next) : charString(charString), probability(probability), next(next) {}

	string getCharString() {
		return charString;
	}

	int getProbability() {
		return probability;
	}

	ListNode* getNext() {
		return next;
	}

	void setNext(ListNode* next) {
		this->next = next;
	}

	string toString() {
		string str = "(\"" + this->charString +"\", " + to_string(this->probability) + ", \"" + this->next->charString + "\")";
		return str;
	}
};

struct LinkedList {
	ListNode* listHead;

	LinkedList() {
		listHead = new ListNode("dummy", 0, NULL);
	}

	void constructLinkedList(ifstream& input, ofstream& output, ListNode* head) {
		string charString;
		int probability;

		try {
			while (!input.eof()) {
				input >> charString >> probability;
				ListNode* newNode = new ListNode(charString, probability, NULL);
				insertNewNode(newNode);
				printList(output);
			}
		}
		catch (exception const& e) {
			cout << "There is an error: " << e.what() << endl;
		}
	}

	ListNode* findSpot(ListNode* head, ListNode* newNode) {
		ListNode* spot = listHead;
		while (spot->getNext() != NULL && spot->getNext()->getProbability() < newNode->getProbability()) {
			spot = spot->getNext();
		}
		return spot;
	}

	void insertNewNode(ListNode* newNode) {
		ListNode* spot = findSpot(listHead, newNode);
		newNode->setNext(spot->getNext());
		spot->setNext(newNode);
	}

	void printList(ofstream& output) {
		string out = "listHead --> ";
		ListNode* i = listHead;
		try {
			for (i = listHead; i->getNext() != NULL; i = i->getNext()) {
				if (i->getNext() == NULL) {
					out += (i->getNext()->toString() + " --> ");
				}
				out += (i->toString() + " --> ");
			}

			out += "(\"" + i->getCharString() + "\", " + to_string(i->getProbability()) + ", NULL) --> NULL\n";

			output << out;
		}
		catch (exception const& e) {
			cout << "There is an error: " << e.what() << endl;
		}
	}
};

int main(int argc, char** argv) {

	ifstream input;
	ofstream output;
	try {
		input.open(argv[1]);
		output.open(argv[2]);

		LinkedList* head = new LinkedList();
		head->constructLinkedList(input, output, head->listHead);
		output << "\n\nFinal Result:\n";
		head->printList(output);

		input.close();
		output.close();
	}
	catch (exception const& e) {
		cout << "There is an error: " << e.what() << endl;
	}
	
	return 0;
}