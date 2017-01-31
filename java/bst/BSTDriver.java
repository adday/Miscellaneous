
public class BSTDriver {
	public static void main(String[] args) throws BSTException{
		Symbol s1 = new Symbol("a", 1);
		Symbol s2 = new Symbol("b", 2);
		Symbol s3 = new Symbol("c", 3);
		Symbol s4 = new Symbol("d", 4);
		Symbol s5 = new Symbol("e", 5);
		
		BST symbolTable = new BST();
		symbolTable.insertItem(s3);
		symbolTable.insertItem(s1);
		symbolTable.insertItem(s2);
		symbolTable.insertItem(s4);
		symbolTable.insertItem(s5);
		
		System.out.println("symbolTable:");
		symbolTable.preorderTraverse();

		
		System.out.println("symbolTable retrievals");
		System.out.println("key a: " + symbolTable.retrieveItem("a"));
		System.out.println("key c: " + symbolTable.retrieveItem("c"));
		System.out.println("key e: " + symbolTable.retrieveItem("e"));
		System.out.println("key f: " + symbolTable.retrieveItem("f"));
	}
}
