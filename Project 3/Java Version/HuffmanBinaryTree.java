import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class HuffmanBinaryTree {

	TreeNode root;
	TreeList list;

	HuffmanBinaryTree() {
		root = new TreeNode();
	}

	public void constructHuffmanLinkedList(TreeList list, Scanner input, FileWriter output) {
		this.list = list;

		char charString;
		int probability;
		try {
			while (input.hasNext()) {
				String line = input.nextLine();
				charString = line.charAt(0);
				probability = Integer.parseInt(line.substring(2));
				TreeNode newNode = new TreeNode(Character.toString(charString), probability, "", null, null, null);
				list.insertNewNode(list.listHead, newNode);
				list.printList(list.listHead, output);
			}
			output.write("\n\n");
			input.close();
			list = this.list;
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void constructHuffmanBinaryTree(TreeList list, FileWriter output) {
		TreeNode spot = this.list.listHead.getNext();
		list.printList(this.list.listHead, output);
		while (spot.getNext() != null) {
			String newCharString = spot.getCharString() + spot.getNext().getCharString();
			int newProbability = spot.getProbability() + spot.getNext().getProbability();
			TreeNode newLeft = spot;
			TreeNode newRight = spot.getNext();
			TreeNode newNode = new TreeNode(newCharString, newProbability, "", newLeft, newRight, null);
			list.insertNewNode(spot, newNode);
			list.printList(list.listHead, output);
			spot = spot.getNext().getNext();
			root = newNode;
		}
	}

	public boolean isLeaf(TreeNode node) {
		return (!(node.hasLeft()) && !(node.hasRight()));
	}

	public void constructCodes(TreeNode node, String code, FileWriter output) {

		try {
			if (isLeaf(node)) {
				node.setCode(code);
				output.write(node.getCharString() + " " + node.getCode() + "\n");
			} else {
				constructCodes(node.getLeft(), code + "0", output);
				constructCodes(node.getRight(), code + "1", output);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void preOrderTraversal(TreeNode node, FileWriter output) {

		try {
			if (isLeaf(node)) {
				output.write(node.printNode() + "\n");
			} else {
				output.write(node.printNode() + "\n");
				preOrderTraversal(node.getLeft(), output);
				preOrderTraversal(node.getRight(), output);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void inOrderTraversal(TreeNode node, FileWriter output) {

		try {
			if (isLeaf(node)) {
				output.write(node.printNode() + "\n");
			} else {
				inOrderTraversal(node.getLeft(), output);
				output.write(node.printNode() + "\n");
				inOrderTraversal(node.getRight(), output);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public void postOrderTraversal(TreeNode node, FileWriter output) {

		try {
			if (isLeaf(node)) {
				output.write(node.printNode() + "\n");
			} else {
				postOrderTraversal(node.getLeft(), output);
				postOrderTraversal(node.getRight(), output);
				output.write(node.printNode() + "\n");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public static void main(String[] args) {

		 File inputFile = new File(args[0]);
		 File codesFile = new File(args[1]);
		 File traversalsFile = new File(args[2]);
		 File debugingFile = new File(args[3]);

		try {

			Scanner input = new Scanner(inputFile);
			FileWriter debuging = new FileWriter(debugingFile);
			FileWriter codes = new FileWriter(codesFile);
			FileWriter traversals = new FileWriter(traversalsFile);

			TreeList list = new TreeList();
			HuffmanBinaryTree tree = new HuffmanBinaryTree();

			tree.constructHuffmanLinkedList(list, input, debuging);
			tree.constructHuffmanBinaryTree(list, debuging);
			tree.constructCodes(tree.root, "", codes);
			traversals.write("Pre-Order Traversal of the Huffman Binary Tree:\n");
			tree.preOrderTraversal(tree.root, traversals);
			traversals.write("\n\nIn-Order Traversal of the Huffman Binary Tree:\n");
			tree.inOrderTraversal(tree.root, traversals);
			traversals.write("\n\nPost-Order Traversal of the Huffman Binary Tree:\n");
			tree.postOrderTraversal(tree.root, traversals);

			input.close();
			debuging.close();
			codes.close();
			traversals.close();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
