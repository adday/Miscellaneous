/*************************************************************************************************************
                                                          Author: Alexander Day
*
* This program calculates the sums in two series. It accepts a user input of an integer. This input is used as
* the last denominator in each series. The result is output to the user as a single sentence containing the
* sum found in each series displayed with 8 digits after the decimal. This program continues to run and prompt
* for user input continuously until it is ended manually. 
**************************************************************************************************************/
import java.text.DecimalFormat;
import java.util.Scanner;


public class n00627606 {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int lastDenom;//last denominator
		double ans1;//answer to first series summation
		double ans2;//answer to second series summation
		DecimalFormat df = new DecimalFormat("#.00000000");//used to display values to 8 decimal places
		
		while(true){//keeps program running as to allow for continuous user input
			System.out.println("This program finds the sums in two series.");
			System.out.print("Enter an integer value for the final denominator in each summation: ");
			lastDenom = input.nextInt();//scans next integer and stores the value

			ans1 = firstSeries(lastDenom);//assigns summation result of first series to ans1
			ans2 = secondSeries(lastDenom);//assigns summation result of second series to ans2

			System.out.println("The result of the first summation is " + df.format(ans1) + " and the result of the second "
					+ "summation is " + df.format(ans2));//outputs the results formatted to 8 decimal places
		}
	}

	public static double firstSeries(int n){//method to find the sum of first series
		double result=0;//initialize variable to store result
		for(int i=1; (2*i+1) <= n; i++)//loops until i equals the value of last denominator 
			result += (double)(2*i-1) / (2*i+1);//keeps a running sum of the series
		return result;//returns result of the first summation and ends method
	}

	public static double secondSeries(int n){//method to find the sum of second series
		double result=0;//initialize variable to store result
		for(int i=1; (2*i-1) <= n; i++)//loops until i equals the value of last denominator
			result += (double)(4 * (Math.pow(-1,(i+1)) / (2*i-1)));//keps a running sum of the series
		return result;//returns result of the first summation and ends method
	}
}



