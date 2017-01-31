public class In2Post {

        // This class implements the infix to postfix translation

	// Use expQueu to create the postfix expression
	// enque at the end of the queue
	// deque at the front of the queue
	private Queue expQueue;

	// opStack maintains operators
	private Stack opStack;

	// when scanning a next Token, put it in nextToken
	private String nextToken;

	// scLine is the scanner that gets the input line in the constructor
	private TokenIter tokIt;

	public In2Post(String line, boolean debug){
		tokIt = new TokenIter(line);
		opStack  = new Stack(debug);
		expQueue = new Queue(debug);
	}
        // Convert infix to a String postfix, using expQueue and opStack.
	
	public String convertIn2Post() throws StackException, QueueException{
		if(!tokIt.hasNext())//line is empty
			return " ";
		while(tokIt.hasNext()){
			nextToken = tokIt.next();
			
			if(nextToken.matches("[0-9]+")){//immediately enqueue
				expQueue.enqueue(nextToken);}
			
			else if(nextToken.matches("[(]"))//immediately push
				opStack.push(nextToken);
			
			else if(nextToken.matches("[)]")){//pop all operators until (
		    	while(!opStack.peek().matches("[(]"))
		    		expQueue.enqueue(opStack.pop());
		    	opStack.pop();}
			
			else if(nextToken.matches("[+|-]")){//nextToken is + or -
				if(opStack.isEmpty())//if stack is empty push
					opStack.push(nextToken);
				else{//stack not empty
					while(!opStack.isEmpty() && opStack.peek().matches("[+|-|*|/]"))//equal operators: pop-enqueue
						expQueue.enqueue(opStack.pop());
					opStack.push(nextToken);//push onto stack when all equal operators are off
					}}//end nextToken is + or -
			
			else if(nextToken.matches("[*|/]")){//if nextToken is * or /
				if(opStack.isEmpty())//if stack is empty push
					opStack.push(nextToken);
				else{//stack not empty
					while(opStack.peek().matches("[+|-|*|/]"));//equal or lower operators: pop-enqueue
						expQueue.enqueue(opStack.pop());
					opStack.push(nextToken);//push onto stack when all equal operators are off
				}}//end nextToken = * or /
			
		}//end while: no more tokens to scan
		
		while(!opStack.isEmpty())//enqueue remaining operators
			expQueue.enqueue(opStack.pop());
		//dequeue all and build string
		String postfix = new String(expQueue.dequeue());
		while(expQueue.size() != 0)
			postfix = postfix + " " + expQueue.dequeue();
		return postfix;
     }//end convertIn2Post


	public static void main(String[] args) throws StackException, QueueException{
		// exercise with increasingly complex expressions
		boolean db = false;
		In2Post ex1 = new In2Post("1", db);
		System.out.println(ex1.convertIn2Post());
		In2Post ex2 = new In2Post("1+2", db);
	}
}
