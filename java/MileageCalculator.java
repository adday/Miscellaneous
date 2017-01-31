/****************************************************************************************
								Author: Alexander Day
 * This is a program to calculate the driving cost on a trip. It prompts the user for
 * input of the driving distance, the miles per gallon of the vehicle, and the price 
 * per gallon of fuel. It then performs a calculation of the driving cost. It outputs 
 * the cost of the trip with the price shown to two decimal places.
 ****************************************************************************************/

import java.util.Scanner;

public class MileageCalculator {

	public static void main(String[] args) {
	Scanner input = new Scanner(System.in);//Creates new Scanner object
	
	double drivingDistance;
	double milesPerGallon;
	double pricePerGallon;
	double drivingCost;
	
	System.out.print("Enter the driving distance: ");
	drivingDistance = input.nextDouble();//Stores number of miles driving
	
	System.out.print("Enter the miles per gallon: ");
	milesPerGallon = input.nextDouble();//Stores miles per gallon of vehicle
	
	System.out.print("Enter price per gallon: ");
	pricePerGallon = input.nextDouble();//Stores price per gallon for trip
	
	drivingCost = drivingDistance / milesPerGallon * pricePerGallon;//Computes the cost of the trip
	System.out.println("The cost of driving is $" + Math.floor(drivingCost*100) / 100);//Outputs the cost of the trip rounded to two decimal places
	}

}
