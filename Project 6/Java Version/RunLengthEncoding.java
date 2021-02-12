import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class RunLengthEncoding {
	
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int numRuns;
	int whichMethod;
	String nameEncodeFile;
	String nameDecodeFile;
	
	RunLengthEncoding(Scanner input, int whichMethod){
		
			if(input.hasNext()) {
				numRows = input.nextInt();
			}
			if(input.hasNext()) {
				numCols = input.nextInt();
			}
			if(input.hasNext()) {
				minVal = input.nextInt();
			}
			if(input.hasNext()) {
				maxVal = input.nextInt();
			}
			this.whichMethod = whichMethod;				
	}
	
	public void encodeMethod1(Scanner input, FileWriter output) {
		
		int row = 0;
		int col = 0;
		int length = 0;
		int currentVal = -1;
		int nextVal = -1;
		
		try {
			output.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n" + whichMethod + "\n");
			
			while (row < numRows) {
				col = 0;
				length = 0;
				currentVal = input.nextInt();
				output.write(row + " " + col + " " + currentVal + " ");
				length++;
				
				while (col < numCols-1) {
					col++;
					nextVal = input.nextInt();
					
					if(nextVal == currentVal) {
						length++;
					}
					else {
						output.write(length + "\n");
						currentVal = nextVal;
						length = 1;
						output.write(row + " " + col + " " + currentVal + " ");
					}
				}
				
				output.write(length + "\n");
				numRuns++;
				row++;
			}
			
			input.close();
			output.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	public void decodeMethod1(Scanner input, FileWriter output) {
		int row;
		int col;
		int value;
		int length;
		
		try {
			if (input.hasNext()) {
				numRows = input.nextInt();
			}

			if (input.hasNext()) {
				numCols = input.nextInt();
			}

			if (input.hasNext()) {
				minVal = input.nextInt();
			}

			if (input.hasNext()) {
				maxVal = input.nextInt();
			}
			
			if (input.hasNext()) {
				whichMethod = input.nextInt();
			}
			
			output.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n");
			int[][] decodeArray = new int[numRows][numCols];
			
			initArray(decodeArray, numRows, numCols);
			
			while(input.hasNext()) {
				row = input.nextInt();
				col = input.nextInt();
				value = input.nextInt();
				length = input.nextInt();
				
				while(length > 0) {
					decodeArray[row][col] = value;
					col++;
					length--;
				}
			}
			printDecodedImage(decodeArray, output);
			

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void printDecodedImage(int[][] array, FileWriter output) {
		try {
			for(int i = 0; i < array.length; i++) {
				for(int j = 0; j < array[0].length; j++) {
					output.write(array[i][j] + " ");
				}
				output.write("\n");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	public void initArray(int[][] array, int rows, int cols) {
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				array[i][j] = 0;
			}
		}
	}
	
	public static void main(String[] args) {
		int whichMethod = 1;
		
		String inputFileString = args[0];
		String encodedFileString = inputFileString.substring(0, inputFileString.lastIndexOf('.')) + "_EncodeMethod" + whichMethod + ".txt";
		String decodedFileString = encodedFileString.substring(0, encodedFileString.lastIndexOf('.')) + "_Decoded.txt";
		File inputFile = new File(inputFileString);
		File encodedFile = new File(encodedFileString);
		File decodedFile = new File(decodedFileString);		
		
		try {
			
			Scanner input = new Scanner(inputFile);
			FileWriter encodedOutput = new FileWriter(encodedFile);
			FileWriter decodedOutput = new FileWriter(decodedFile);
			
			RunLengthEncoding encoding = new RunLengthEncoding(input, whichMethod);
			encoding.encodeMethod1(input, encodedOutput);
			input.close();
			encodedOutput.close();
			Scanner encoded = new Scanner(encodedFile);
			encoding.decodeMethod1(encoded, decodedOutput);
			
			encoded.close();
			decodedOutput.close();
			
		}
		catch (IOException e) {
			e.printStackTrace();
		}		
	}
}
