import java.io.File;
import java.io.IOException;
import java.util.Hashtable;
import java.util.Scanner;

public class EquationDriver {
	public static void main(String[] args) throws IOException{
		Scanner scan = new Scanner( new File (args[0]));
        String line;
        boolean debug = false;
        if(args.length > 1)
        	debug = true;
        // initialize symTab
        Hashtable<String,Integer> symbolTable = new Hashtable<String,Integer>();
        // loop through lines in input file
        while ( scan.hasNextLine()){
        	line = scan.nextLine();
        	System.out.println("next line: " + line);
        	try{
        	TokenIter tokIt = new TokenIter(line);
        	Equation nextEq = new Equation(tokIt, debug);
    		String res = nextEq.line(symbolTable);
    	    System.out.println("result: " + res);
        	} catch (ParseException PE) {
        		System.out.println("Parse Exception caught: " + PE.getMessage());
        	} catch(Exception e){
        		System.out.println("Exception caught: " + e.getMessage());
        	}
	
    		if(debug){
    			System.out.println("SYMBOL TABLE");
    			//output
    			for(String key:symbolTable.keySet()){
    				System.out.println(key+" = "+symbolTable.get(key));
    			}
    			System.out.println("END SYMBOL TABLE");
    		}
        }
	}
}
