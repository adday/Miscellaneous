import java.util.ArrayList;

public class Stack implements StackIF {

    // This class implements the provided Stack Interface StackIF

    // Use opStack to push and pop operators
    private ArrayList<String> opStack;
	
    // debug controls debug reporting 
    private boolean debug;
    
    // intialize opStack and debug
    public Stack(boolean debug){
    	this.debug = debug;
    	opStack = new ArrayList<String>();
    }

    public static void main(String[] args) throws StackException{
    	Stack s = new Stack(false);
    	s.pop();
    }
    
    	// add String op to top of stack
		// In debug mode print "push: " + pushed value
        public void push(String op){
        	if(debug)
        		System.out.println("push: " + op);
        	opStack.add(op);
        }//end push
		
		// remove and return item from top of stack
        // In debug mode print "pop: " + popped value
		// throw Stack Exception "popping from empty stack!"  when stack empty
		public String pop() throws StackException{
			if (!opStack.isEmpty()){
				if (debug)
					System.out.println("pop: " + opStack.get(opStack.size()-1));
				return opStack.remove(opStack.size()-1);}//end if
			else{
				throw new StackException("popping from empty stack!");
				}//end else
		}//end pop
		
		// return, but do not remove, item from top of stack
		// throw Stack Exception "peeking empty stack!" when stack empty
		public String peek() throws StackException{
			if(!opStack.isEmpty())
				return opStack.get(opStack.size()-1);
			else
				throw new StackException("peeking empty stack!");
		}
		
		// return true if stack empty, false otherwise
		public boolean isEmpty(){
			return opStack.isEmpty();
		}

}
