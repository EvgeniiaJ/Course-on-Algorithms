import java.io.FileWriter;

public class TreeList {

	TreeNode listHead;

	TreeList() {
		listHead = new TreeNode();
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
		TreeNode node = head;
		String str = "";
		try {
			for (node = head; node.getNext() != null; node = node.getNext()) {
				str += node.printNode() + " --> ";
			}
			str += "(\"" + node.getCharString() + "\", " + node.getProbability() + ", NULL, NULL, NULL) --> NULL\n";
			output.write(str);

		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}
