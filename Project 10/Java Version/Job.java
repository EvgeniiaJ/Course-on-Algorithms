public class Job {
	
	/**
	 * @param	jobTime		time needed for processing the job
	 * @param	onWhichProcessor	which processor will be executing this job (0 - none)
	 * @param 	onOpen 		0 - not on Open, 1 - on open
	 */
	
	private int jobTime; 
	private int onWhichProcessor;
	private int onOpen; 	
	private int parentCounter;
	private int dependentCounter;
	
	public Job() {
		this.jobTime = 0;
		this.onWhichProcessor = -1;
		this.onOpen = 0;
		this.parentCounter = 0;
		this.dependentCounter = 0;
	}
	
	public Job(int jobTime, int onWhichProcessor, int onOpen, int parentCounter, int dependentCounter) {
		this.jobTime = jobTime;
		this.onWhichProcessor = onWhichProcessor;
		this.onOpen = onOpen;
		this.parentCounter = parentCounter;
		this.dependentCounter = dependentCounter;
	}

	public int getJobTime() {
		return jobTime;
	}
	
	public void setJobTime(int jobTime) {
		this.jobTime = jobTime;
	}
	
	public int getOnWhichProcessor() {
		return onWhichProcessor;
	}
	
	public void setOnWhichProcessor(int onWhichProcessor) {
		this.onWhichProcessor = onWhichProcessor;
	}
	
	public int getOnOpen() {
		return onOpen;
	}
	
	public void setOnOpen(int onOpen) {
		this.onOpen = onOpen;
	}
	
	public int getParentCounter() {
		return parentCounter;
	}
	
	public void setParentCounter(int parentCounter) {
		this.parentCounter = parentCounter;
	}
	
	public int getDependentCounter() {
		return dependentCounter;
	}
	
	public void setDependentCounter(int dependentCounter) {
		this.dependentCounter = dependentCounter;
	}
	

}
