import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class HuffmanEncodeDecode {
	
	int[] charCountsArray;	
	
	HuffmanEncodeDecode(){
		charCountsArray = new int[256];
		for(int i = 0; i < 256; i++) {
			charCountsArray[i] = 0;
		}
	}
	
	public void computeCharCounts(Scanner input, int[] countArray) {
		
		while (input.hasNext()) {
			String line = input.nextLine();
			for (int i = 0; i < line.length(); i++) {
				charCountsArray[line.charAt(i)]++;
			}
		}
	}
	
	public void printCountArray(FileWriter output) {
		
		try {
			for(int i = 0; i < 256; i++) {
				if(charCountsArray[i] > 0) {
					output.write((char)i + " " + charCountsArray[i] + "\n");
				}
			}
			
		}catch(IOException e) {
			e.printStackTrace();
		}
		
	}
	
	public static void Encode(HuffmanBinaryTree tree, Scanner input, FileWriter output) {
		char inputCharacter;
		int index;
		String code = null;
		
		try {
			while(input.hasNext()) {
				String line = input.nextLine();
				for(int i = 0; i < line.length(); i++) {
					inputCharacter = line.charAt(i);
					index = (int) inputCharacter;
					code = tree.charCodes[index];
					output.write(code);
					output.flush();
				}
			}
			
		}catch(IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void Decode(HuffmanBinaryTree tree, Scanner input, FileWriter output, TreeNode treeRoot) {
		char oneBit;
		TreeNode spot = treeRoot;
		
		try {
			while(input.hasNext()) {
				String line = input.nextLine();
				for(int i = 0; i < line.length(); i++) {
					if(tree.isLeaf(spot)) {
						output.write(spot.getCharacter());
						spot = treeRoot;
					}
					oneBit = line.charAt(i);
					if(oneBit == '0') {
						spot = spot.getLeft();
					}
					else if(oneBit == '1') {
						spot = spot.getRight();
					}
					else {
						System.out.println("Error! The compressed file is damaged.");
						System.exit(1);
					}
				}
			}
			if(!input.hasNext() && !tree.isLeaf(spot)) {
				System.out.println("Error! The compressed file is damaged.");
			}
			
		}catch(IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void userInterface(HuffmanBinaryTree tree) {
		String originalFileName, compressedFileName, decompressedFileName;
		char yesNo = ' ';
		while(true) {
			
			System.out.print("Enter 'Y' to comress file, or 'N' to exit the program: ");
			Scanner user = new Scanner(System.in);
			if(user.hasNext()) {
				yesNo = Character.toUpperCase(user.next().charAt(0));
			}
			if(yesNo == 'N') {
				System.out.println("Exiting the program");
				System.exit(1);
			}
			if(yesNo == 'Y') {
				try {
					System.out.println("Enter file name to be compresses (including extension):");
					Scanner fileName = new Scanner(System.in);
					originalFileName = fileName.nextLine();
					compressedFileName = originalFileName.substring(0, originalFileName.lastIndexOf('.')) + "_Compressed.txt";
					decompressedFileName = originalFileName.substring(0, originalFileName.lastIndexOf('.')) + "_Decompressed.txt";					
					
					Scanner originalFile = new Scanner(new File(originalFileName));
					FileWriter compressedFile = new FileWriter(new File(compressedFileName));
					FileWriter decompressedFile = new FileWriter(new File(decompressedFileName));
					
					Encode(tree, originalFile, compressedFile);
					
					System.out.println("File is compressed");
					compressedFile.close();
					
					Scanner alreadyCompressedFile = new Scanner(new File(compressedFileName));
					Decode(tree, alreadyCompressedFile, decompressedFile, tree.root);
					
					originalFile.close();
					alreadyCompressedFile.close();
					decompressedFile.close();
				}
				catch(IOException e) {
					e.printStackTrace();
				}
			}
		}
		
	}

	public static void main(String[] args) {
		
		String inputFileString = args[0];
		String debugFileString = inputFileString.substring(0, inputFileString.lastIndexOf('.')) + "_Debug.txt";
		
		File inputFile = new File(inputFileString);
		File debugFile = new File(debugFileString);
		
		try {
			Scanner input = new Scanner(inputFile);
			FileWriter debug = new FileWriter(debugFile);
			HuffmanEncodeDecode encodeDecode = new HuffmanEncodeDecode();
			encodeDecode.computeCharCounts(input, encodeDecode.charCountsArray);
			encodeDecode.printCountArray(debug);
			input.close();
			
			HuffmanBinaryTree tree = new HuffmanBinaryTree();
			tree.constructHuffmanLinkedList(encodeDecode.charCountsArray, debug);
			tree.constructHuffmanBinaryTree(tree.list, debug);
			tree.constructCodes(tree.root, "");
			debug.write("\nOutput with codes:\n");
			tree.list.printList(tree.list.getListHead(), debug);

			debug.write("\nTraversals:\n");
			debug.write("Pre-Order Traversal:\n");
			tree.preOrderTraversal(tree.root, debug);
			debug.write("\n\nIn-Order Traversal:\n");
			tree.inOrderTraversal(tree.root, debug);
			debug.write("\n\nPost-Order Traversal:\n");
			tree.postOrderTraversal(tree.root, debug);
			
			userInterface(tree);			
			
			debug.close();
		}catch(IOException e) {
			e.printStackTrace();
		}
	}
}
