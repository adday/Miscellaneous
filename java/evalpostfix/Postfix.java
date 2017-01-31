import java.util.ArrayList;
import java.util.Scanner;


public class Postfix {

    // use evalStack for the evaluation of the postfix expression in line
	// implement evalStack with the pop and push methods
	private ArrayList<Integer> evalStack = new ArrayList<Integer>();
	
	// when scanning a next Token, put it in nextToken
	private String nextToken;
	
	// scLine is the scanner that gets the input line
	private Scanner scLine;
	
	// debug is used to report progress
	private boolean debug;
	
	/* constructor
	 * set instance variable debug
	 * create new scanner with String line and assign to scLine
	*/
	public Postfix(String line, boolean debug){
		this.debug = debug;
		scLine = new Scanner(line);
	}//end constructor

	/*
	 * push Integer i on evalStack
	 * In debug mode print "push: " + pushed value
	 */
	private void push(Integer i){
		if(debug){
			System.out.println("push: " + i);
		}
		evalStack.add(i);
	}//end push()
	
	/*
	 * pop Integer from evalStack
	 * If evalStack empty, return null
	 * In debug mode print "pop: " + popped value
	 */
	private Integer pop(){
		if (!evalStack.isEmpty()){
			if (debug)
				System.out.println("pop: " + evalStack.get(evalStack.size()-1));
			return evalStack.remove(evalStack.size()-1);}//end if
		else{
			if (debug)
				System.out.println("pop: null");
			return null;}//end else
	}//end pop()
	
	
	/*
	 * evaluate the postfix expression in scLine
	 * when encountering an Integer, push it on the evalStack
	 * when encountering an operator, 
	 *    pop two values off the evalStack (right, then left)
	 *    perform the operation, and push the result on the evalStack
	 * at the end of the expression,
	 *    pop the result off the stack and return it 
	 *    
	 * scLine either contains an empty line, or a valid postfix expression     
	 */
	public Integer eval(){
		Integer result;
		Integer rightTerm;
		Integer leftTerm;
		while(scLine.hasNext()){
			nextToken = scLine.next();
		    if(nextToken.equals("+") | nextToken.equals("-") | nextToken.equals("*") | nextToken.equals("/")){
		    	rightTerm =  pop();
		    	leftTerm = pop();
		        if(nextToken.equals("+"))
		        	result = leftTerm + rightTerm;
		        else if(nextToken.equals("-"))
		        	result = leftTerm - rightTerm;
		        else if(nextToken.equals("*"))
		        	result = leftTerm * rightTerm;
		        else if(nextToken.equals("/"))
		        	result = leftTerm / rightTerm;
		        else result = null;
		        push(result);
		    }//end if
		    else{
		    	push(Integer.parseInt(nextToken));
		    }//end else
		}//end while
		return pop();
	}//end eval()
	
}//end Postfix.java