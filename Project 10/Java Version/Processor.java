
	/**
	 * @param 	doWhichJob 		id of the job the processor executing
	 * @param 	timeRemain 		time before the processor will be available
	 */
public class Processor {
	
	private int doWhichJob;
	private int timeRemain;
	
	public Processor() {
		this.doWhichJob = -1;
		this.timeRemain = 0;
	}
	
	public Processor(int doWhichJob, int timeRemain) {
		this.doWhichJob = doWhichJob;
		this.timeRemain = timeRemain;
	}

	public int getDoWhichJob() {
		return doWhichJob;
	}

	public void setDoWhichJob(int doWhichJob) {
		this.doWhichJob = doWhichJob;
	}

	public int getTimeRemain() {
		return timeRemain;
	}

	public void setTimeRemain(int timeRemain) {
		this.timeRemain = timeRemain;
	}
	

}
