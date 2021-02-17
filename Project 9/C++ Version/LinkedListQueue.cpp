#include "LinkedListQueue.h"

LinkedListQueue::LinkedListQueue() {
	this->dummy = new ListNode();
	this->head = dummy;
	this->tail = dummy;
}

ListNode* LinkedListQueue::getHead() {
	return head;
}

void LinkedListQueue::setHead(ListNode* head) {
	this->head = head;
}

ListNode* LinkedListQueue::getTail() {
	return tail;
}

void LinkedListQueue::setTail(ListNode* tail) {
	this->tail = tail;
}

bool LinkedListQueue::isEmpty(LinkedListQueue queue) {
	return ((queue.getHead() == dummy && queue.getTail() == dummy) || (queue.getHead() == NULL));
}

bool LinkedListQueue::isEmpty(LinkedListQueue* queue) {
	return ((queue->getHead() == dummy && queue->getTail() == dummy) || (queue->getHead() == NULL));
}

void LinkedListQueue::addTail(LinkedListQueue* queue, ListNode* node) {
	node->setNext(NULL);
	if (queue->isEmpty(queue)) {
		queue->setHead(node);
		queue->setTail(node);
	}
	else {
		queue->getTail()->setNext(node);
		queue->setTail(node);
	}
}

ListNode* LinkedListQueue::deleteHead(LinkedListQueue* queue) {
	ListNode* node = NULL;
	if (!queue->isEmpty(queue)) {
		node = queue->getHead();
		queue->setHead(node->getNext());
	}
	return node;
}

string LinkedListQueue::printQueue(int index) {
	string str = "";
	if (!(this->isEmpty(this))) {
		ListNode* node = this->getHead();
		str.append("Front(" + to_string(index));
		str.append(") --> ");
		while (node->getNext() != NULL) {
			str.append("(" + to_string(node->getData()));
			str.append(", " + to_string(node->getNext()->getData()));
			str.append(") --> ");
			node = node->getNext();
		}
		str.append("(" + to_string(node->getData()));
		str.append(", NULL) --> NULL\n");
		str.append("Tail(" + to_string(index));
		str.append(") --> (" +to_string(node->getData()));
		str.append(", NULL) --> NULL\n");
	}
	return str;
}