import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class ExternalFileMergeSort {

	public void sort(Scanner input1, Scanner input2, FileWriter output) {

		try {

			int num1 = input1.nextInt();
			int num2 = input2.nextInt();

			do {
				if (num1 < num2) {
					output.write(num1 + "\n");
					num1 = input1.nextInt();
				} else {
					output.write(num2 + "\n");
					num2 = input2.nextInt();
				}
			} while (input1.hasNext() || input2.hasNext());

			if (input1.hasNext()) {
				while (input1.hasNext()) {
					num1 = input1.nextInt();
					output.write(num1 + "\n");
				}
			}

			if (input2.hasNext()) {
				while (input2.hasNext()) {
					num2 = input2.nextInt();
					output.write(num2 + "\n");
				}
			}

			if (num1 < num2) {
				output.write(num1 + "\n");
				output.write(num2 + "\n");
			}

			else {
				output.write(num2 + "\n");
				output.write(num1 + "\n");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	public static void main(String[] args) {

		
		File inputFile1 = new File(args[0]); 
		File inputFile2 = new File(args[1]);
		File outputFile = new File(args[2]);
		

		try {

			Scanner input1 = new Scanner(inputFile1);
			Scanner input2 = new Scanner(inputFile2);
			FileWriter output = new FileWriter(outputFile);

			ExternalFileMergeSort object = new ExternalFileMergeSort();
			object.sort(input1, input2, output);

			input1.close();
			input2.close();
			output.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
