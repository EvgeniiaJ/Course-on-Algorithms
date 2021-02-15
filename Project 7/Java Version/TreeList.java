import java.io.FileWriter;

public class TreeList {

	private TreeNode listHead;

	TreeList() {
		this.listHead = new TreeNode();
	}
	
	public TreeNode getListHead() {
		return listHead;
	}
	
	public void setListHead(TreeNode listHead) {
		this.listHead = listHead;
	}

	public void insertNewNode(TreeNode head, TreeNode newNode) {
		TreeNode spot = findSpot(head, newNode);
		insert(spot, newNode);
	}

	public TreeNode findSpot(TreeNode head, TreeNode newNode) {
		TreeNode spot = head;
		while (spot.getNext() != null && spot.getNext().getProbability() < newNode.getProbability()) {
			spot = spot.getNext();
		}
		return spot;
	}

	public void insert(TreeNode spot, TreeNode newNode) {
		newNode.setNext(spot.getNext());
		spot.setNext(newNode);
	}

	public void printList(TreeNode head, FileWriter output) {
		
		String str = "listHead --> ";
		
		try {
			
			for(TreeNode node = head; node.getNext() != null; node = node.getNext()) {
				str += node.printNode(node);
			}
			str += "NULL\n";
			output.write(str);

		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}
