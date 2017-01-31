/*********************************************************************************************************************************																				Author: Alexander Day
 * 
 * This program accepts the input of integers from the user to build two 3x3 arrays. These arrays are then analyzed using
 * six different methods. The methods perform the following: checks if the matrices are identical, counts how many entries are identical, 
 * counts how many entries are on the diagonals are identical, compute an average of all entries, display the odd entries in each matrix
 * in matrix form, and checks to see if the matrices include only numbers between 1<x<=10. The results of these operations are displayed
 * to the user. The program runs continuously until ended by the user allowing for continuous input.
 * ******************************************************************************************************************************/

import java.text.DecimalFormat;
import java.util.Scanner;

public class n00627606 {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);

		int[][] array1 = new int[3][3];
		int[][] array2 = new int[3][3];
      
      while(true){
		System.out.println("Enter 9 integer values to be stored in the first matrix:");
		//Stores user input integers into the first matrix
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)
				array1[i][j] = input.nextInt();
		}

		System.out.println("Enter 9 integer values to be stored in the second matrix:");
		//Stores user input integers into the second matrix
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)
				array2[i][j] = input.nextInt();
		}

		//Utilizes method "equals" to determine if the matrices are identical-the result is output to the display
		if(Strict.equals(array1,array2) == true)
			System.out.println("\nThe matrices are identical\n");
		else
			System.out.println("\nThe matrices are not identical\n"); 

		//Utilizes method "howmany" to count how many entries are identical-the result is output to the display
		System.out.println("There are " + Strict.howmany(array1, array2) + " entries that are identical\n");

		//Utilizes method "diagonal" to count how many entries are identical-the result is output to the display
		System.out.println("There are " + Strict.diagonal(array1, array2) + " entries that are identical on the diagonal\n");

		//Utilizes method "average" to compute the average of all entries in the matrices-the result is output to the display
		System.out.println("The average of all the entries from the two matrices is: " + Strict.average(array1, array2) + "\n");

		//Utilizes method "display" to display all odd entries in each matrix
		System.out.println("The odd entries in the two matrices are: ");
		Strict.display(array1, array2);

		//Utilizes method "silly" to determine if the matrices contain only numbers 1<x<=10-the result is output to the display
		if(Strict.silly(array1,array2) == true)
			System.out.println("\n\nThe matrices contain only numbers satisfying 1 < x <= 10\n");
		else
			System.out.println("\n\nThe matrices do not contain only numbers from 1 < x <= 10\n");
      }
	}
}

class Strict{//Class contains methods to check two 3x3 matrices

	public static boolean equals(int[][] m1, int[][] m2){//Determines if the matrices are identical
		//Loops through all entries in the matrices
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(m1[i][j] == m2[i][j])
					continue;//Continues checking entries while they are identical
				else
					return false;//Returns false if two entries are not identical
		return true;//Returns true when all entries have been checked and none of them differ
	}

	public static int  howmany(int[][] m1, int[][] m2){//Counts how many entries are identical
		int count = 0;//Local variable to count the number of identical entries
		//Loops through all entries in the matrices
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(m1[i][j] == m2[i][j])
					count++;//Count incremented by 1 when entries are identical
		return count;//Returns integer value stored in count
	}

	public static int diagonal(int[][] m1, int[][] m2){//Counts how many entries on the diagonal are identical
		int count = 0;//Local variable to count the number of identical entries
		//Loops through only diagonal entries
		for(int i=0;i<3;i++)
			if(m1[i][i] == m2[i][i])
				count++;//Count incremented by 1 when entries are identical
		return count;//Returns integer value stored in count
	}

	public static double  average(int[][] m1,int[][] m2){//Computes average of all values in the two matrices
		DecimalFormat df = new DecimalFormat("#.00");//Format used for return value
		double sum = 0;//Local variable to keep a running sum
		//Loops through all entries in the matrices
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				sum+=m1[i][j]+m2[i][j];//Adds the ij-entries from both matrices to sum
		String temp = df.format(sum/18.0);//Divides the sum by 18 (the total number of entries) and stores it to two decimal places
		double average = Double.parseDouble(temp);//Parses string obtained in last line to a double and stores in average
		return average;//Returns value stored in average
	}

	public static void display(int[][] m1, int[][] m2){//Displays the odd entries in the matrices in matrix form
		//Loops through first matrix
		for(int i=0;i<3;i++){
			System.out.println();//Advances to the next line after each row
			for(int j=0;j<3;j++)
				if(m1[i][j]%2 == 1)//Checks if entry is odd
					System.out.print(m1[i][j]+ " ");//Entry is displayed in the matrix when it is odd
				else
					System.out.print("  ");//An empty space is displayed in the matrix when its entry is even
		}

		System.out.println();//Skips a line before next matrix is to be displayed

		//Loops through second matrix
		for(int i=0;i<3;i++){
			System.out.println();//Advances to the next line after each row
			for(int j=0;j<3;j++)
				if(m2[i][j]%2 == 1)//Checks if entry is odd
					System.out.print(m2[i][j]+ " ");//Entry is displayed in the matrix when it is odd
				else
					System.out.print("  ");//An empty space is displayed in the matrix when its entry is even
		}
	}

	public static boolean silly(int[][] m1, int[][] m2){//Checks if the two matrices contain only numbers 1<x<=10
		for(int i=0;i<3;i++)//Loops through all entries in both matrices
			for(int j=0;j<3;j++)
            if(m1[i][j] < 2 || m1[i][j] > 10 || m2[i][j] < 2 || m2[i][j] > 10)//Executed when an entry is found not satisfying 1<x<=10
               return false;
      return true;//Returns true when all entries have been verified to be >1 and <=10
     	}
}




