import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class CharacterCount {
	
	public static void countCharacters(FileReader input, int[] charCounts) {
		
		int index;
		
		try {
			
			while ((index = input.read()) != -1) {
				for (int i = 0; i < charCounts.length; i++) {
					if (index == i) {
						charCounts[i]++;
					}
				}
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void printArray(int[] charCounts, FileWriter output) {
		
		try {
			
			for(int i = 33; i < charCounts.length; i++) {
				if(charCounts[i] > 0) {
					output.write((char)i + " " + charCounts[i] + "\n");
				}
			}
			
		}
		catch(IOException e) {
			e.printStackTrace();
		}		
	}

	public static void main(String[] args) {
		
		File inputFile = new File(args[0]);
		File outputFile = new File(args[1]);
		
		try {
			
			FileReader input = new FileReader(inputFile);
			FileWriter output = new FileWriter(outputFile);
			
			int maxCharNumber = 256;
			int[] charCounts = new int[maxCharNumber];
			
			for(int i = 0; i < maxCharNumber; i++) {
				charCounts[i] = 0;
			}
			
			countCharacters(input, charCounts);
			printArray(charCounts, output);
			
			input.close();
			output.close();
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}
}
