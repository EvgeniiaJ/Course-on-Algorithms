import java.io.FileWriter;
import java.io.IOException;

public class HuffmanBinaryTree {

	TreeNode root;
	TreeList list;
	String[] charCodes;

	HuffmanBinaryTree() {
		
		root = new TreeNode();
		list = new TreeList();
		charCodes = new String[256];
		
		for(int i = 0; i < 256; i++) {
			charCodes[i] = "";
		}
		
	}

	public void constructHuffmanLinkedList(int[] countArray, FileWriter output) {

		char character;
		int probability;
		
		try {
			
			output.write("\nConstructing Huffman Linked List:\n");
			for(int i = 0; i < countArray.length; i++) {
				if(countArray[i] > 0) {
					character = (char) i;
					probability = countArray[i];
					TreeNode newNode = new TreeNode(character, probability);
					list.insertNewNode(list.getListHead(), newNode);
				}
			}
			list.printList(list.getListHead(), output);
			
		}
		catch (IOException e) {
			e.printStackTrace();
		}		
	}

	public void constructHuffmanBinaryTree(TreeList list, FileWriter output) {
		
		TreeNode spot = this.list.getListHead().getNext();
		
		try {
			
			output.write("\nConstructing Huffman Binary Tree:\n");
			while (spot.getNext() != null) {
				String newCharString = spot.getCharString() + spot.getNext().getCharString();
				int newProbability = spot.getProbability() + spot.getNext().getProbability();
				TreeNode newLeft = spot;
				TreeNode newRight = spot.getNext();
				TreeNode newNode = new TreeNode(newCharString, newProbability, "", newLeft, newRight, null);
				list.insertNewNode(spot, newNode);
				spot = spot.getNext().getNext();
				root = newNode;
			}
			list.printList(list.getListHead(), output);
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}

	public boolean isLeaf(TreeNode node) {
		return (!(node.hasLeft()) && !(node.hasRight()));
	}

	public void constructCodes(TreeNode node, String code) {
		
		int index = 0;
		
		try {
			if (isLeaf(node)) {
				node.setCode(code);
				index = (int)node.getCharacter();
				
				if(node.getCode() != null) {
					charCodes[index] = node.getCode();
				}
			} else {
				constructCodes(node.getLeft(), code + "0");
				constructCodes(node.getRight(), code + "1");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void preOrderTraversal(TreeNode node, FileWriter output) {
		
		try {
			
			if(isLeaf(node)) {
				output.write(node.printNode(node));
				
			}
			else {
				output.write(node.printNode(node));
				preOrderTraversal(node.getLeft(), output);
				preOrderTraversal(node.getRight(), output);
			}
			
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}
	
	public void inOrderTraversal(TreeNode node, FileWriter output) {
		
		try {
			
			if(isLeaf(node)) {
				output.write(node.printNode(node));				
			}
			else {
				inOrderTraversal(node.getLeft(), output);
				output.write(node.printNode(node));
				inOrderTraversal(node.getRight(), output);
			}
			
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}
	
	public void postOrderTraversal(TreeNode node, FileWriter output) {
		
		try {
			
			if(isLeaf(node)) {
				output.write(node.printNode(node));				
			}
			else {
				postOrderTraversal(node.getLeft(), output);
				postOrderTraversal(node.getRight(), output);
				output.write(node.printNode(node));
			}
			
		}catch(IOException e) {
			e.printStackTrace();
		}
	}
}
