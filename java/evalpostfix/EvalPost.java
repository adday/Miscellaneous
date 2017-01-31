import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;




public class EvalPost {

	/**
	 * @param args: input-file-name debug-option 
	 * @throws FileNotFoundException 
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args) throws FileNotFoundException{
		// get filename from agrs[0]
		// if a second argument exists debug is true, else false
		// create scanner that reads from file named in args[0]
		// and calls Postfix with each line
        Scanner scan = new Scanner(new File (args[0]));
        String line;
        System.out.println("Reading from file: "  +  args[0] + "\n");
        boolean debug = false;
        if(args.length > 1)
        	debug = true;
        // loop through lines in input file
        while ( scan.hasNextLine()){
        	line = scan.nextLine();
        	System.out.println("next line: " + line);
        	Postfix p = new Postfix(line, debug);
        	System.out.println("result: " + p.eval()+ "\n");
        }	

	}

}