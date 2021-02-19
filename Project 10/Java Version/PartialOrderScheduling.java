import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

/**
 * @param 	nodesNumber		total number of nodes in the input graph
 * @param	processorsNumber 	the number of processors can be used
 * @param	processorsUsed		the number of processors can be used
 * @param	jobsArray		an array of jobs, the array index served as job id
 * @param	processorsArray 	an array of processors, the array, index served as Proc id
 * @param	open		node pointer, acts as the list head of the linked list with a dummy node
 * @param	adjacencyMatrix		represents the input dependency graph (1 - present, 0 - absent)
 * @param	parentCountArray	an array storing number of parents of each node
 * @param	dependentCountArray	an array storing number of dependents of each node
 * @param	onGraphtArray 		array to indicate whether a node is in //the graph
 * @param	totalJobTimes		the sum of all nodes’ job provided in inFile2
 * @param	scheduleTable		an array to record the schedule
 * @param	currentTime
 * */
public class PartialOrderScheduling {
	
	private int nodesNumber;
	private int processorsNumber;
	public int processorsUsed;
	public Job[] jobsArray;
	public Processor[] processorsArray;
	public Node open;
	public int[][] adjacencyMatrix;
	public int[] parentCountArray;
	public int[] dependentCountArray;
	public int[] onGraphArray;
	public int totalJobTimes;
	public int[][] scheduleTable;
	public int currentTime;
	
	

	public PartialOrderScheduling() {
		this.currentTime = 0;
		this.processorsUsed = 0;
		Node dummy = new Node();
		open = dummy;
	}
	
	public void initialize(Scanner input1, Scanner input2, int processorsNumber) {
		if(processorsNumber <= 0) {
			System.out.println("Should be 1 or more processors");
			System.exit(0);
		}
		else {
			this.processorsNumber = processorsNumber;
		}
				
		if(input1.hasNext()) {
			this.nodesNumber = input1.nextInt();
		}
		
		if(processorsNumber > nodesNumber) {
			processorsNumber = nodesNumber;
		}
		
		jobsArray = new Job[nodesNumber + 1];
		processorsArray = new Processor[processorsNumber + 1];
		adjacencyMatrix = new int[nodesNumber + 1][nodesNumber + 1];
		parentCountArray = new int[nodesNumber + 1];
		dependentCountArray = new int[nodesNumber + 1];
		onGraphArray = new int[nodesNumber + 1];
		
		
		for(int i = 0; i <= nodesNumber; i++) {
			Job job = new Job();
			jobsArray[i] = job;
			parentCountArray[i] = 0;
			dependentCountArray[i] = 0;
			onGraphArray[i] = 0;
			for(int j = 0; j <= nodesNumber; j++) {
				adjacencyMatrix[i][j] = 0;
			}
		}
				
		loadMatrix(input1);
		computeParentCount(adjacencyMatrix, parentCountArray);
		computeDependentCount(adjacencyMatrix, dependentCountArray);
		totalJobTimes = constructJobArray(input2, adjacencyMatrix);
		
		scheduleTable = new int[processorsNumber + 1][totalJobTimes + 1];
		for(int i = 0; i <= processorsNumber; i++) {
			Processor processor = new Processor(0, 0);
			processorsArray[i] = processor;
			for(int j = 0; j <= totalJobTimes; j++) {
				scheduleTable[i][j] = 0;
			}
		}
	}
	
	void loadOpen() {
		int orphanNode = findOrphan();
		while (orphanNode > -1) {
			if (orphanNode > 0) {
				int jobId = orphanNode;
				int jobTime = jobsArray[jobId].getJobTime();
				Node newNode = new Node(jobId, jobTime, jobsArray[jobId].getDependentCounter(), null);
				openInsert(newNode);			
			}
			orphanNode = findOrphan();
		}
	}

	public void loadMatrix(Scanner input) {
		int i, j;
		while(input.hasNext()) {
			i = input.nextInt();
			j = input.nextInt();
			adjacencyMatrix[i][j] = 1;
			onGraphArray[i] = 1;
			onGraphArray[j] = 1;
		}
	}
	
	void loadProcessorArray(int currentTime) {
		int availProc = findProcessor();
		while (availProc > 0 && open.getNext() != null && processorsUsed < processorsNumber) {
			if (availProc > 0) {
				processorsUsed++;
				Node newJob = removeFrontNode();
				int jobId = newJob.getJobId();
				int jobTime = newJob.getJobTime();
				processorsArray[availProc].setDoWhichJob(jobId);
				processorsArray[availProc].setTimeRemain(jobTime);
				putJobOnTable(availProc, currentTime, jobId, jobTime);
			}
			availProc = findProcessor();
		}
	}
	
	public void computeParentCount(int[][] matrix, int[] countArray) {
		
		for(int nodeId = 1; nodeId <= nodesNumber; nodeId++) {
			int sum = 0;
			for(int i = 1; i <= nodesNumber; i++) {
				sum += matrix[i][nodeId];
			}
			countArray[nodeId] = sum;
		}
		
	}
	
	public void computeDependentCount(int[][] matrix, int[] countArray) {
		
		for(int nodeId = 1; nodeId <= nodesNumber; nodeId++) {
			int sum = 0;
			for(int i = 1; i <= nodesNumber; i++) {
				sum += matrix[nodeId][i];
			}
			countArray[nodeId] = sum;
		}		
	}
	
	public int constructJobArray(Scanner input, int[][] matrix) {
		int totalTime = 0;
		int nodeId = 0, jobTime = 0;
		int skip = input.nextInt();
		while(input.hasNext()) {
			nodeId = input.nextInt();
			jobTime = input.nextInt();
			totalTime += jobTime;
			jobsArray[nodeId].setJobTime(jobTime);
			jobsArray[nodeId].setOnWhichProcessor(-1);
			jobsArray[nodeId].setOnOpen(0);
			jobsArray[nodeId].setParentCounter(parentCountArray[nodeId]);
			jobsArray[nodeId].setDependentCounter(dependentCountArray[nodeId]);
		}
		return totalTime;
	}
	
	public int findOrphan() {
		for(int i = 1; i <= nodesNumber; i++) {
			if(jobsArray[i].getParentCounter() <= 0 && jobsArray[i].getOnOpen() == 0 && jobsArray[i].getOnWhichProcessor() <= 0) {
				jobsArray[i].setOnOpen(1);
				return i;
			}
		}
		return -1;
	}
	
	public void openInsert(Node newNode) {
		Node spot = findSpot(newNode);
		newNode.setNext(spot.getNext());
		spot.setNext(newNode);
	}
	
	public Node findSpot(Node newNode) {
		Node spot = open;
		while(spot.getNext() != null && spot.getNext().getDependentCounter() >= newNode.getDependentCounter()) {
			spot = spot.getNext();
		}
		return spot;
	}
	
	public Node removeFrontNode() {
		Node newNode = open.getNext();
		open.setNext(open.getNext().getNext());
		newNode.setNext(null);
		return newNode;
	}
	
	public void printList(FileWriter output) {
		String str ="OPEN --> ";
		String out = "OPEN-->";

		try {
			for (Node i = open; i.getNext() != null; i = i.getNext()) {
				if (i.getNext() == null) {
					str = "NULL) --> ";
				} else {
					str = "\"" + i.getNext().getJobTime() + "\") --> ";
				}
				out += "(\"" + i.getJobId() + "\", " + i.getJobTime() + ", " + str;
			}
			out += "NULL\n";
			output.write(out);
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void printScheduleTable(FileWriter output) {
		try {
			output.write("     -0--");
			for (int i = 1; i < totalJobTimes + 1; i++) {
				output.write("-" + i + "--");
			}
			output.write("\n");
			for (int i = 1; i < processorsNumber + 1; i++) {
				output.write("P(" + i + ")|");
				for (int j = 0; j < totalJobTimes + 1; j++) {
					if (scheduleTable[i][j] == 0) {
						output.write(" - |");
					} else {
						output.write(" " + scheduleTable[i][j] + " |");
					}
				}
				output.write(" \n");
				output.write("     -");
				for (int k = 0; k <= totalJobTimes * 4; k++) {
					output.write("-");
				}
				output.write("\n");
			}
			output.write("\n");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	
	public int findProcessor() {
		for(int i = 1; i <= processorsNumber; i++) {
			if(processorsArray[i].getTimeRemain() <= 0) {
				return i;
			}
		}
		return -1;
	}
	
	public void putJobOnTable(int availableProcessor, int currentTime, int jobId, int jobTime) {
		int time = currentTime;
		int endTime = time + jobTime;
		while(time < endTime) {
			scheduleTable[availableProcessor][time] = jobId;
			time++;
		}
	}
	
	public boolean checkCycle() {
		if(open.getNext() == null && !graphIsEmpty() && jobsFinished()) {
			return true;
		}
		return false;
	}

	public boolean graphIsEmpty() {
		for(int i = 1; i <= nodesNumber; i++) {
			if(onGraphArray[i] > 0) {
				return false;
			}
		}
		return true;
	}
	
	public boolean jobsFinished() {
		for(int i = 1; i <= processorsNumber; i++) {
			if(processorsArray[i].getTimeRemain() > 0 && processorsArray[i].getDoWhichJob() > 0) {
				return false;
			}
		}
		return true;
	}
	
	public void updateProcessorTime() {
		for(int i = 1; i <= processorsNumber; i++) {
			if(processorsArray[i].getTimeRemain() > 0) {
				processorsArray[i].setTimeRemain(processorsArray[i].getTimeRemain() - 1);
			}
		}
	}
	
	public int findDoneProcessor() {
		for(int i = 1; i <= processorsNumber; i++) {
			if(processorsArray[i].getTimeRemain() <= 0 && processorsArray[i].getDoWhichJob() > 0) {
				int jobId = processorsArray[i].getDoWhichJob();
				processorsArray[i].setDoWhichJob(-1);
				processorsUsed--;
				return jobId;
			}
		}
		return -1;
	}
	
	public void deleteEdge(int jobId) {
		for(int dependent = 1; dependent <= nodesNumber; dependent++) {
			if(adjacencyMatrix[jobId][dependent] > 0) {
				parentCountArray[dependent]--;
				adjacencyMatrix[jobId][dependent] = 0;
				jobsArray[dependent].setParentCounter(jobsArray[dependent].getParentCounter() - 1);
			}
		}
	}
	
	
	public static void main(String[] args) {
//		String in1 = args[0];
//		String in2 = args[1];
//		String numOfProcs = args[2];
//		String out1 = args[3]; 
//		String out2 = args[4]; 
		
		int procUsed = 0, currentTime;
		boolean hasCycle;
		
		String inputFileName1 = args[0];
		String inputFileName2 = args[1];
		String outputFileName1 = args[2]; 
		String outputFileName2 = args[3]; 
		String numOfProcs = args[4];
		
		try {
			Scanner input1 = new Scanner(new File(inputFileName1));
			Scanner input2 = new Scanner(new File(inputFileName2));
			FileWriter output1 = new FileWriter(new File(outputFileName1));
			FileWriter output2 = new FileWriter(new File(outputFileName2));
			
			PartialOrderScheduling schedule = new PartialOrderScheduling();
			
			schedule.initialize(input1, input2, Integer.parseInt(numOfProcs));
			schedule.currentTime = 0;
			while (!schedule.graphIsEmpty()) {
				schedule.loadOpen();
				schedule.printList(output2);
				schedule.loadProcessorArray(schedule.currentTime);
				hasCycle = schedule.checkCycle();
				if (hasCycle) {
					System.out.println("There is a cycle in the graph!");
					output1.write("There is a cycle in the graph!");
					System.exit(1);
				}
				schedule.printScheduleTable(output1);
				schedule.currentTime++;
				schedule.updateProcessorTime();
				int jobId = schedule.findDoneProcessor();
				while (jobId > 0) {
					if (jobId > 0) {
						schedule.onGraphArray[jobId] = 0;
						schedule.deleteEdge(jobId);
					}
					jobId = schedule.findDoneProcessor();
				}
			}
			schedule.printScheduleTable(output1);

			input1.close();
			input2.close();
			output1.close();
			output2.close();
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
