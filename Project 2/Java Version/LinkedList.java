import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class LinkedList{
	static ListNode listHead;
	
	LinkedList(){
		ListNode dummy = new ListNode("dummy", 0, null);		
	}
	
	public void constructLinkedList(File input, ListNode head) {
		char charString;
		int probability;
		
		try {
			Scanner scan = new Scanner(input);
			while(scan.hasNext()) {
				String line = scan.nextLine();
				charString = line.charAt(0);
				probability = Integer.parseInt(line.substring(2));
				ListNode newNode = new ListNode(Character.toString(charString), probability, null);
				insertNewNode(newNode, head);
			}
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void insertNewNode(ListNode newNode, ListNode head) {
		ListNode spot = findSpot(head, newNode);
		newNode.setNext(spot.getNext());
		spot.setNext(newNode);		
	}
	
	public ListNode findSpot(ListNode head, ListNode newNode) {
		ListNode spot = head;
		
		while(spot.getNext() != null && spot.getNext().getProbability() < newNode.getProbability()) {
			spot = spot.getNext();
		}
		
		return spot;		
	}
	
	public void printList(ListNode head, FileWriter output) {
		String outputString = "listHead --> ";
		ListNode node = head;
		
		while(node.getNext() != null) {
			outputString += "(\"" + node.getCharString() + "\", " + node.getProbability() + ", \"" + node.getNext().getCharString() + "\")" + " --> ";
			node = node.getNext();
		}
		
		outputString += "(\"" + node.getCharString() + "\", " + node.getProbability() + ", NULL)" + " --> NULL";
		try {
			output.write(outputString);
		}
		catch(Exception e) {
			e.printStackTrace();
		}	
	}

	public static void main(String[] args) {
		
		File inputFile = new File(args[0]);
		File outputFile = new File(args[1]);
		
		try {
			FileWriter output = new FileWriter(outputFile);
			LinkedList list = new LinkedList();
			ListNode head = new ListNode();
			list.constructLinkedList(inputFile, head);
			list.printList(head, output);
			
			output.close();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
}
