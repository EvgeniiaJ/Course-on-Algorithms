public class LinkedListQueue {

	private ListNode head;
	private ListNode tail;
	public ListNode dummy;

	LinkedListQueue() {
		dummy = new ListNode();
		this.head = dummy;
		this.tail = dummy;
	}

	public ListNode getHead() {
		return head;
	}

	public void setHead(ListNode head) {
		this.head = head;
	}

	public ListNode getTail() {
		return tail;
	}

	public void setTail(ListNode tail) {
		this.tail = tail;
	}

	public boolean isEmpty(LinkedListQueue queue) {
		return ((queue.getHead() == dummy && queue.getTail() == dummy) || (queue.getHead() == null));
	}

	public void addTail(LinkedListQueue queue, ListNode node) {
		node.setNext(null);
		if (queue.isEmpty(queue)) {
			queue.setHead(node);
			queue.setTail(node);
		} else {
			queue.getTail().setNext(node);
			queue.setTail(node);
		}
	}

	public ListNode deleteHead(LinkedListQueue queue) {
		ListNode node = null;
		if (!queue.isEmpty(queue)) {
			node = queue.getHead();
			queue.setHead(node.getNext());
		}
		return node;
	}

	public String printQueue(int index) {
		String str = "";
		if (!this.isEmpty(this)) {
			ListNode node = this.getHead();
			str += "Front(" + index + ") --> ";
			while (node.getNext() != null) {
				str += "(" + node.getData() + ", " + node.getNext().getData() + ") --> ";
				node = node.getNext();
			}
			str += "(" + node.getData() + ", NULL) --> NULL\n";
			str += "Tail(" + index + ") --> (" + node.getData() + ", NULL) --> NULL\n";
		}
		return str;
	}
}
