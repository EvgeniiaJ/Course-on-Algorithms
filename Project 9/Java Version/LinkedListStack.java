import java.io.FileWriter;
import java.io.IOException;

public class LinkedListStack {
	private ListNode top;
	
	LinkedListStack(){
		this.top = null;
	}

	public ListNode getTop() {
		return top;
	}

	public void setTop(ListNode top) {
		this.top = top;
	}
	
	public void push(ListNode newNode) {
		newNode.setNext(top);
		top = newNode;
	}
	
	public ListNode pop() {
		if(top == null) {
			return null;
		}
		else {
			ListNode remove = top;
			top = top.getNext();
			remove.setNext(null);
			return remove;
		}
	} 
	
	public boolean isEmpty() {
		return (top == null);
	}
	
	public void printStack(ListNode top, FileWriter output) {
		String str = "Top --> ";
		ListNode node = top;
		try {
			for(node = top; node.getNext() != null; node = node.getNext()) {
				str += "(" + node.getData() + ", "+ node.getNext().getData() + ") --> ";
			}
			str += "(" + node.getData() + ", NULL) --> NULL\n\n";
			output.write(str);
		}
		catch(IOException e) {
			e.printStackTrace();
		}
		
	}
	
	
	
}
