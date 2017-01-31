import java.util.Hashtable;


public class Equation {

	private boolean debug;

	private String nextToken;	
	private TokenIter itTokens;

	Tree exprTree;

	public Equation(TokenIter iter, boolean debug){
		itTokens = iter;
		this.debug = debug;
		nextTok("");
	}

	private void nextTok(String indent){
		if(itTokens.hasNext())
			nextToken = itTokens.next();
		else 
			nextToken = null;
		if(debug)
			System.out.println(indent+"next token: " + nextToken);
	}

	private void error(String errMess) throws ParseException{
		throw new ParseException(errMess);
	}

	//parses an expr containing identifiers
	public Tree line() throws ParseException{
		TreeNode root;
		Tree tree = new Tree();
		if(nextToken == null)
			error("Unexpected end of line");
		if(nextToken != null){
			root = expr("");
			tree = new Tree(root);
			}
		if(nextToken != null)
			error("end of line expected");
		return tree;
	}

	// expr = term ( "+" term )*
	private TreeNode expr(String indent) throws ParseException{
		if(debug)
			System.out.println(indent+"expr");
		TreeNode left = term(indent+" ");
		while(nextToken != null && (nextToken.equals("+") || nextToken.equals("-")) ){
			String op = nextToken;
			nextTok(indent+" ");
			TreeNode right = term(indent+" ");
			left = new TreeNode(op,left,right);
			}
		return left;
	}

	//term = factor ( "*"|"/" factor )*
	private TreeNode term(String indent) throws ParseException{
		if(debug)
			System.out.println(indent + "term");
		TreeNode left = factor(indent+" ");
		while(nextToken != null && (nextToken.equals("*") || nextToken.equals("/")) ){
			String op = nextToken;
			nextTok(indent+" ");
			TreeNode right = factor(indent+" ");
			left = new TreeNode(op,left,right);
			}
		return left;
	}

	// factor = "(" expr ")" | number 
	private TreeNode factor(String indent) throws ParseException{
		if(debug)
			System.out.println(indent + "factor");
		if(nextToken == null)
			error("Unexpected end of line");
		if(nextToken.equals("(")){
			nextTok(indent+" ");
			TreeNode left = expr(indent+" ");
			if(nextToken.equals(")") )
				nextTok(indent+" ");
			else
				error(") expected");
			return left;
			}
		else if(nextToken.matches("[0-9]*"))
			return number(indent+" ");
		else 
			return identifier(indent+" ");
	}

	//number = [0-9]*
	private TreeNode number(String indent) throws ParseException{
		if(debug)
			System.out.println(indent + "number");
		if(nextToken == null){
			error("number expected");
			return null;
			}
		if(Character.isDigit(nextToken.charAt(0))){
			String num = nextToken;
			nextTok(indent);
			return new TreeNode(num);
			}
		else {
			error("number expected");
			return null; //not a number
			}
	}

	//identifier = [A-Za-z0-9][A-Za-z0-9]*
	private TreeNode identifier(String indent) throws ParseException{
		String identifier;
		if(debug)
			System.out.println(indent + "identifier");
		if(nextToken == null){
			error("identifier expected");
			return null;
			}
		if(nextToken.matches("[A-Za-z][A-Za-z0-9]*")){
			identifier = nextToken;
			nextTok(indent);
			return new TreeNode(identifier);
			}
		else {
			error("Unexpected token: " + nextToken);	 
			return null;//not an identifier
			}
	}
	// line parses a line: lhs "=" expr
	// where lhs = identifier
	// and returns a Symbol (identifier + value) and stores it in the symbol table
	public String line(Hashtable<String,Integer> hashTable) throws ParseException{
		TreeNode root;
		Integer result;
		String lhs = nextToken;
		if(nextToken == null)
			return null;
		else {
			if(debug)
				System.out.println("line");
			//parse left hand side to obtain identifier
			if(!lhs.matches("[A-Za-z][A-Za-z0-9]*"))
				error("Identifier expected");
			nextTok("");//advance to '='
			if(nextToken == null)
				error("unexpected end of line");
			if(nextToken.equals("="))
				nextTok("");//consume '='
			else	
				error("= expected");
			// parse expression and create expression tree
			exprTree = line();//line returns expr tree created from rhs
			root = exprTree.root();//assign root for postorderEval call
			result = exprTree.postorderEval(root, "", hashTable);// evaluate expr tree
			hashTable.put(lhs, result);//insert symbol into symbolTable
			if(debug)
				System.out.println("retrieving " + lhs + ": " + hashTable.get(lhs));
			if(nextToken!=null){
				error("end of line expected");
				return null;} 
			else
				return String.valueOf(hashTable.get(lhs));
		}
	}


}