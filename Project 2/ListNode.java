
public class ListNode {

	private String charString;
	private int probability;
	private ListNode next;
	
	ListNode(){
		charString = "dummy";
		this.probability = 0;
		this.next = null;
	}
	
	ListNode(String charString, int probability, ListNode next){
		this.charString = charString;
		this.probability = probability;
		this.next = next;
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

	public ListNode getNext() {
		return next;
	}

	public void setNext(ListNode next) {
		this.next = next;
	}
	
	public String toString() {
		String str = "( " + this.getCharString() + ", " + this.getProbability() + ", " + this.getNext() + ")";
		return str;
		
	}
	
}
