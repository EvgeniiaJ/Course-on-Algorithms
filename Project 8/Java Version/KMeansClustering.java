import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class KMeansClustering {
	
	private int numRows;
	private int numCols;
	private int numberOfPoints;
	private int changeCounter;
	private int kClusters;	
	
	public int[][] imageArray;	
	public Point[] pointSet;
	public Point[] kCentroids;
	
	KMeansClustering(Scanner input, int kClusters){
		
		if(input.hasNext()) {
			this.numRows = input.nextInt();
		}
		if(input.hasNext()) {
			this.numCols = input.nextInt();
		}
		if(input.hasNext()) {
			this.numberOfPoints = input.nextInt();
		}
		
		this.kClusters = kClusters;
		this.changeCounter = 0;
		initArrays();
	}
	
	public void initArrays() {
		
		imageArray = new int[numRows][numCols];
		
		for(int i = 0; i < numRows; i++) {
			for(int j = 0; j < numCols; j++) {
				imageArray[i][j] = 0;
			}
		}
		
		pointSet = new Point[numberOfPoints];
		
		for (int i = 0; i < numberOfPoints; i++) {
			pointSet[i] = new Point(0.0, 0.0, 0, 99999.0);
		}
		
		kCentroids = new Point[kClusters+1];
		
		for (int i = 0; i <= kClusters; i++) {
			kCentroids[i] = new Point(0.0, 0.0, 0, 0.0);
		}		
	}
	
	public void loadPointSet(Scanner input, Point[] pointSet) {
		int index = 0;
		int x, y;
		while (input.hasNext()) {
			x = input.nextInt();
			y = input.nextInt();
			pointSet[index].setXCoordinate((double) x);
			pointSet[index].setYCoordinate((double) y);
			index++;			
		}
		
	}
	
	public void assignLabel(Point[] pointSet, int kNumber) {
		int front = 0;
		int back = numberOfPoints - 1;
		int label = 1;
		
		while(front <= back) {
			if(label > kNumber) {
				label = 1;
			}
//			pointSet[front].setLabel(label);
//			front++;
//			label++;
//			if(label > kNumber) {
//				label = 1;
//			}
//			pointSet[back].setLabel(label);
//			back--;
//			label++;
//			if(label > kNumber) {
//				label = 1;
//			}
			
			else if(label == kNumber) {
				
				pointSet[front].setLabel(label);
				front++;
				label++;
				pointSet[back].setLabel(1);
				back--;				
			}
			else {
				pointSet[front].setLabel(label);
				front++;
				label++;
				pointSet[back].setLabel(label);
				back--;	
				label++;
			}
		}
	}	
	
	public void kMeansClustering(FileWriter output, Point[] pointSet, int kNumber) {
		
		int iteration = 0;
		assignLabel(pointSet, kNumber);
		changeCounter = 0;
		
		while(true) {// (changeCounter <= 2) {
			pointImageConversion(pointSet, imageArray);
			printImage(imageArray, output, iteration);
			changeCounter = 0;
			computeCentroids(pointSet, kCentroids);
			int index = 0;
			while(index < numberOfPoints) {
				distanceMinLabel(pointSet[index], kCentroids);
				index++;
			}
			if(changeCounter == 0) {break;}
			iteration++;
		}
		
	}
	
	public void computeCentroids(Point[] pointSet, Point[] kCenstroids) {
		
		double[] sumOfX = new double[kClusters + 1];
		double[] sumOfY = new double[kClusters + 1];
		double[] totalPoints = new double[kClusters + 1];
		
		for(int i = 0; i <= kClusters; i++) {
			sumOfX[i] = 0.0;
			sumOfY[i] = 0.0;
			totalPoints[i] = 0.0;
		}
		
		int index = 0;
		int label = 0;
		
		while(index < numberOfPoints) {
			label = pointSet[index].getLabel();
			sumOfX[label] += pointSet[index].getXCoordinate();
			sumOfY[label] += pointSet[index].getYCoordinate();
			totalPoints[label]++;
			index++;
		}
		
		label = 1;
		
		while(label <= kClusters) {
			kCentroids[label].setXCoordinate(sumOfX[label] / totalPoints[label]);
			kCentroids[label].setYCoordinate(sumOfY[label] / totalPoints[label]);
			label++;
		}		
	}
	
	public void distanceMinLabel(Point point, Point[] kCenstroids) {
		double minDistance = 99999.0;
		int minLabel = 0;
		int label = 1;
		while(label <= kClusters) {
			double distance = computeDistance(point, kCentroids[label]);
			if (distance < minDistance) {
				minDistance = distance;
				minLabel = label;
			}
			label++;
		}

		if(minDistance < point.getDistance()) {
			point.setDistance(minDistance);
			point.setLabel(minLabel);
			changeCounter++;
		}
	}
	
	public double computeDistance(Point point, Point kPoint) {
		double xDistance = Math.pow(kPoint.getXCoordinate() - point.getXCoordinate(), 2);
		double yDistance = Math.pow(kPoint.getYCoordinate() - point.getYCoordinate(), 2);
		double distance = Math.sqrt(xDistance + yDistance);
		return distance;
	}
	
	public void pointImageConversion(Point[] pointSet, int[][] imageArray) {
		
		for(int i = 0; i < numberOfPoints; i++) {
			int x = (int)pointSet[i].getXCoordinate();
			int y = (int)pointSet[i].getYCoordinate();
			imageArray[x][y] = pointSet[i].getLabel();
		}
		
	}
	
	public void printImage(int[][] imageArray, FileWriter output, int iteration) {
		try {
			output.write("\t\tResult of Iteration #" + iteration+"\n");
			for(int i = 0; i < imageArray.length; i++) {
				for(int j = 0; j < imageArray[0].length; j++) {
					if(imageArray[i][j] > 0) {
						output.write(imageArray[i][j] + " ");
					}
					else {
						output.write(" ");
					}
				}
				output.write("\n");
			}
			output.write("\n\n");
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args) {
		String inputFileName = args[0];
		String outputFileName = args[1];
		int kValue;
		
		try {
			Scanner input = new Scanner(new File(inputFileName));
			FileWriter output = new FileWriter(new File(outputFileName));
			
			System.out.print("Enter a value for k (number of clusters to split data points into): ");
			Scanner k = new Scanner(System.in);
			kValue = k.nextInt();
			
			output.write("\t\t\tK Means Clustering with " + kValue + " clusters:\n");
			
			KMeansClustering clustering = new KMeansClustering(input, kValue);
			clustering.loadPointSet(input, clustering.pointSet);
			clustering.kMeansClustering(output, clustering.pointSet, kValue);
			
			input.close();
			output.close();			
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}

}
