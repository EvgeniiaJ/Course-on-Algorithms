public class Node {
	
	private int jobId;
	private int jobTime;
	private int dependentCounter;
	private Node next;
	
	public Node() {
		this.jobId = 0;
		this.jobTime = 0;
		this.dependentCounter = 0;
		this.next = null;
	}
	
	public Node(int jobId, int jobTime, int dependentCounter, Node next) {
		this.jobId = jobId;
		this.jobTime = jobTime;
		this.dependentCounter = dependentCounter;
		this.next = next;
	}

	public int getJobId() {
		return jobId;
	}

	public void setJobId(int jobId) {
		this.jobId = jobId;
	}

	public int getJobTime() {
		return jobTime;
	}

	public void setJobTime(int jobTime) {
		this.jobTime = jobTime;
	}

	public int getDependentCounter() {
		return dependentCounter;
	}

	public void setDependentCounter(int dependentCounter) {
		this.dependentCounter = dependentCounter;
	}

	public Node getNext() {
		return next;
	}

	public void setNext(Node next) {
		this.next = next;
	}
}
