import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class RadixSort {
	int tableSize;
	int data;
	int currentTable;
	int previousTable;
	int maxDigit;
	int offset;
	int currentDigit;
	int currentQueue;
	LinkedListStack stack;
	LinkedListQueue[][] hashTable;

	RadixSort(Scanner input) {
		int minNumber = 0;
		int maxNumber = 0;

		while (input.hasNext()) {
			this.data = input.nextInt();
			if (data < minNumber) {
				minNumber = data;
			}
			if (data > maxNumber) {
				maxNumber = data;
			}
		}
		offset = Math.abs(minNumber);
		maxNumber += offset;
		maxDigit = getMaxDigit(maxNumber);
		tableSize = 10;
		hashTable = new LinkedListQueue[2][tableSize];
		init();
	}

	public void init() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < tableSize; j++) {
				hashTable[i][j] = new LinkedListQueue();
			}
		}
	}

	public int getMaxDigit(int maximum) {
		int max = maximum;
		int counter = 0;
		while (max > 0) {
			max /= 10;
			counter++;
		}
		return counter;
	}

	public void loadStack(Scanner input, FileWriter output) {
		this.stack = new LinkedListStack();
		while (input.hasNext()) {
			data = input.nextInt();
			data += offset;
			ListNode newNode = new ListNode(data);
			stack.push(newNode);
		}
		stack.printStack(stack.getTop(), output);
	}

	public void dumpStack(ListNode top, int currentDigit, int currentTable, FileWriter output) {
		ListNode node;
		int digit, hashIndex;
		while (!stack.isEmpty()) {
			node = stack.pop();
			digit = getDigit(node, currentDigit);
			hashIndex = digit;
			hashTable[currentTable][hashIndex].addTail(hashTable[currentTable][hashIndex], node);
		}
		printTable(hashTable[currentTable], output);
	}

	public int getDigit(ListNode node, int currentDigit) {
		int digit = node.getData();
		while (currentDigit > 0) {
			digit /= 10;
			currentDigit--;
		}
		digit %= 10;
		return digit;
	}

	void printTable(LinkedListQueue[] table, FileWriter output) {
		try {
			int index = 0;
			String str = "";
			while (index < tableSize) {
				if (!(table[index].isEmpty(table[index]))) {
					str += table[index].printQueue(index);
				}
				index++;
			}
			str += "\n";
			output.write(str);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	void printSortResult(LinkedListQueue[] hashTable, FileWriter output) {
		int index = 0;
		ListNode spot = hashTable[index].getHead();
		try {
			output.write("Sorted Data:\n");
			while (index < tableSize) {
				while (spot != null) {
					if (spot != null) {
						data = spot.getData();
						output.write(data + " ");
						spot = spot.getNext();
					}
				}
				index++;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	void subtractOffset() {
		currentTable = previousTable;
		ListNode node = hashTable[currentTable][0].getHead();
		while (node != null) {
			int newData = node.getData() - offset;
			node.setData(newData);
			node = node.getNext();
		}
	}

	void Sorting(FileWriter output1, FileWriter output2) {
		ListNode node;
		int digit, hashIndex, temp;
		currentDigit = 0;
		currentTable = 0;
		dumpStack(stack.getTop(), currentDigit, currentTable, output2);
		currentDigit++;
		currentTable = 1;
		previousTable = 0;
		currentQueue = 0;

		while (currentDigit <= maxDigit) {
			while (currentQueue < tableSize) {
				while (!hashTable[previousTable][currentQueue].isEmpty(hashTable[previousTable][currentQueue])) {
					node = hashTable[previousTable][currentQueue].deleteHead(hashTable[previousTable][currentQueue]);
					digit = getDigit(node, currentDigit);
					hashIndex = digit;
					hashTable[currentTable][hashIndex].addTail(hashTable[currentTable][hashIndex], node);
				}
				currentQueue++;
			}
			printTable(hashTable[currentTable], output2);

			temp = currentTable;
			currentTable = previousTable;
			previousTable = temp;
			currentQueue = 0;
			currentDigit++;
		}
		subtractOffset();
		printSortResult(hashTable[currentTable], output1);
	}

	public static void main(String[] args) {

		String inputFileName = args[0];
		String output1FileName = args[1];
		String output2FileName = args[2];

		try {
			Scanner input = new Scanner(new File(inputFileName));
			FileWriter output1 = new FileWriter(new File(output1FileName));
			FileWriter output2 = new FileWriter(new File(output2FileName));

			RadixSort sorting = new RadixSort(input);
			input.close();

			Scanner input1 = new Scanner(new File(inputFileName));

			sorting.loadStack(input1, output2);

			sorting.Sorting(output1, output2);

			input1.close();
			output1.close();
			output2.close();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
