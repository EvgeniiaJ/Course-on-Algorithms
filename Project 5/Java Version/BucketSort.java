import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class BucketSort {
	
	int max;
	int[] BucketArray;
		
	BucketSort(Scanner input) {
		try {

			int data;
			max = input.nextInt();

			while (input.hasNext()) {
				data = input.nextInt();
				if (data > max) {
					max = data;
				}
			}

			initArray();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void initArray() {

		BucketArray = new int[max + 1];

		for (int i = 0; i <= max; i++) {
			BucketArray[i] = 0;
		}
	}
	
	public void fillOutBuckets(Scanner input, FileWriter output) {
		int data;

		try {
			while (input.hasNext()) {
				data = input.nextInt();
				BucketArray[data]++;

				for (int i = 0; i <= max; i++) {
					output.write("bucket #" + i + " " + BucketArray[i] + "\n");
				}
				output.write("\n");
			}
			
			output.write("\n\nThe Final Result of Sorted Array:\n");
			for (int i = 0; i <= max; i++) {
				if(BucketArray[i] > 0) {
					output.write(i + " " + BucketArray[i] + "\n");
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
	
	public void printResult(FileWriter output) {
		int index = 0;
		try {
			
			output.write("Displaying sorted numbers:\n");			
			
			while(index <= max) {
				while(BucketArray[index] > 0) {
					output.write(index + " ");
					BucketArray[index]--;
				}
				index++;
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}		
	}
	
	public static void main(String[] args) {
		
		File inputFile = new File(args[0]);
		File resultFile = new File(args[1]);
		File debugFile = new File(args[2]);
		
		try {
			
			Scanner input = new Scanner(inputFile);	
			FileWriter result = new FileWriter(resultFile);
			FileWriter debug = new FileWriter(debugFile);
			
			BucketSort sort = new BucketSort(input);
			input.close();
			
			sort.initArray();
			
			input = new Scanner(inputFile);
			sort.fillOutBuckets(input, debug);
			sort.printResult(result);
			
			input.close();
			result.close();
			debug.close();
			
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
}
