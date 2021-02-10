public class TreeNode {

	private String charString;
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

	public String printNode() {
		String str = "(\"" + this.getCharString() + "\", " + this.getProbability() + ", \"";
		if (this.hasNext()) {
			str += this.getNext().getCharString() + "\", ";
		} else {
			str += "NULL, ";
		}
		if (this.hasLeft()) {
			str += this.getLeft().getCharString() + "\", ";
		} else {
			str += "NULL, ";
		}
		if (this.hasRight()) {
			str += this.getRight().getCharString() + "\")";
		} else {
			str += "NULL)";
		}
		return str;
	}

	public String getCharString() {
		return charString;
	}

	public void setCharString(String charString) {
		this.charString = charString;
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
