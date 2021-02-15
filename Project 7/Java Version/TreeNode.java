public class TreeNode {

	private String charString;
	private char character;
	private int probability;
	private String code;
	private TreeNode left;
	private TreeNode right;
	private TreeNode next;

	TreeNode() {
		this.charString = "dummy";
		this.probability = 0;
		this.code = "";
		this.left = null;
		this.right = null;
		this.next = null;
	}

	TreeNode(String charString, int probability, String code, TreeNode left, TreeNode right, TreeNode next) {
		this.charString = charString;
		this.probability = probability;
		this.code = code;
		this.left = left;
		this.right = right;
		this.next = next;
	}
	
	TreeNode(char character, int probability) {
		this.charString = String.valueOf(character);
		this.character = character;
		this.probability = probability;
		this.code = "";
		this.left = null;
		this.right = null;
		this.next = null;
	}

	public String printNode(TreeNode node) {
		String str = "(\"" + node.getCharString() + "\", " + node.getProbability() + ", " + node.getCode() + ", ";

		if (node.next == null) {
			str += "NULL, ";
		} else {
			str += "\"" + node.next.getCharString() + "\", ";
		}
		if (node.left == null) {
			str += "NULL, ";
		} else {
			str += "\"" + node.left.getCharString() + "\", ";
		}
		if (node.right == null) {
			str += "NULL) --> ";
		} else {
			str += "\"" + node.right.getCharString() + "\") --> ";
		}
		return str;
	}

	public String getCharString() {
		return charString;
	}

	public void setCharString(String charString) {
		this.charString = charString;
	}
	
	public char getCharacter() {
		return character;
	}

	public void setCharacter(char character) {
		this.character = character;
	}

	public int getProbability() {
		return probability;
	}

	public void setProbability(int probability) {
		this.probability = probability;
	}

	public String getCode() {
		return code;
	}

	public void setCode(String code) {
		this.code = code;
	}

	public TreeNode getLeft() {
		return left;
	}

	public void setLeft(TreeNode left) {
		this.left = left;
	}

	public TreeNode getRight() {
		return right;
	}

	public void setRight(TreeNode right) {
		this.right = right;
	}

	public TreeNode getNext() {
		return next;
	}

	public void setNext(TreeNode next) {
		this.next = next;
	}

	public boolean hasNext() {
		return (this.getNext() != null);
	}

	public boolean hasLeft() {
		return (this.getLeft() != null);
	}

	public boolean hasRight() {
		return (this.getRight() != null);
	}

}
