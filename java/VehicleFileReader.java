/************************************************************************************************************************************
                                                             Author: Alexander Day
*
* This program reads a file and fills an array with vehicle objects. The vehicle objects can be either a car, an american car, a 
* foreign car, a bicycle, or a truck. The program then runs methods to do the following: print vehicle count, print all vehicles, 
* print all vehicles sorted by email address, print all bicycles and trucks, and print all vehicles with an phone number in area 
* code 987.The program can read a file that is formatted appropriately according to specified program guidelines. The array can hold
* a maximum of 200 vehicles
*************************************************************************************************************************************/

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class VehicleFileReader {
	public static void main(String[] args) throws FileNotFoundException {
		Scanner reader = new Scanner(new File(args[0]));//Scanner to read file containing vehicle records
		Vehicle[] vehicles = new Vehicle[200];//Array to hold vehicle objects
		String type;//Variable to hold type of vehicle (first line in vehicle record file for each new record)
		int count = 0;//Counts the number of vehicles processed into the array
		
      if(reader.hasNext() == false){//If the file is empty ends program
         System.out.println("File not found.");
			System.exit(0);
         }
      
		for(int i=0;i<200;i++) {//Loops through a maximum of 200 records
        
         if(reader.hasNext() == false)//Exits loop when no more files to read
             break;
             
         type = reader.next();//Stores the next vehicle type
			reader.nextLine();//Advances reader to the next line
         
         //The following if-else construct sorts through and assigns vehicles based on their type using appropriate class with parameters         
			if(type.equals("vehicle")){
				vehicles[i] = new Vehicle(reader.nextLine(), reader.nextLine(),reader.nextLine(), reader.nextLine());
				count++;
			}
			else if(type.equals("car")){
				vehicles[i] = new Car(reader.nextLine(), reader.nextLine(),reader.nextLine(), reader.nextLine(), Boolean.parseBoolean(reader.nextLine()), reader.nextLine());			
				count++;
			}
			else if(type.equals("american")){
				vehicles[i] = new AmericanCar(reader.nextLine(), reader.nextLine(),reader.nextLine(), reader.nextLine(), Boolean.parseBoolean(reader.nextLine()), reader.nextLine(), Boolean.parseBoolean(reader.nextLine()), Boolean.parseBoolean(reader.nextLine()));
				count++;
			}

			else if(type.equals("foreign")){
				vehicles[i] = new ForeignCar(reader.nextLine(), reader.nextLine(), reader.nextLine(), reader.nextLine(), Boolean.parseBoolean(reader.nextLine()), reader.nextLine(), reader.nextLine(), reader.nextFloat());
				count++;
			}

			else if(type.equals("bicycle")){
				vehicles[i] = new Bicycle(reader.nextLine(), reader.nextLine(), reader.nextLine(), reader.nextLine(), reader.nextInt());
				count++;
			}

			else if(type.equals("truck")){
				vehicles[i] = new Truck(reader.nextLine(), reader.nextLine(), reader.nextLine(), reader.nextLine(), reader.nextFloat(), reader.nextFloat(), reader.next());
				count++;
			}
		}

		reader.close();//Closes resource
		
		numberOfRecords(count);//Prints the number of records
		printAll(vehicles);//Prints all records
		sort(vehicles);//Prints records sorted by email address
		bicyclesAndTrucks(vehicles);//Prints bicycles and trucks
		areacode987(vehicles);//Prints records with phone numbers having area code 987
	}

	public static void printAll(Vehicle[] vehicles){//Method to print all records
		System.out.println("LIST OF ALL RECORDS:\n");
		for(int i=0;i<200;i++)
			try{
				System.out.println(vehicles[i].toString());
			}
		catch(NullPointerException e){//Ends printing when array is out of records
			break;
		}
	}

	public static void sort(Vehicle[] vehicles){//Method to sort all records by email address
		System.out.println("SORTED BY EMAIL ADDRESS:\n");
		for(int i=1;i<200;i++){
			try{
         //Uses insertion sort algorithm
				int k;
				for(k= i-1; k>=0 && (vehicles[i].getemail()).compareTo(vehicles[i].getemail()) > 0 ;k--){
					vehicles[k+1] = vehicles[k];
				}
				vehicles[k+1] = vehicles[i];
			}
			catch(NullPointerException e){//Ends sorting when array is out of records
				break;
			}
		}
      //Prints records
		for(int i=0;i<200;i++)
			try{
				System.out.println(vehicles[i].toString());
			}
		catch(NullPointerException e){//Ends printing when array is out of records
			break;
		}
	}

	public static void numberOfRecords(int count){//Method to print the number of records
		System.out.println("THERE ARE " + count + " RECORDS STORED.\n");
	}

	public static void bicyclesAndTrucks(Vehicle[] vehicles){//Method to print bicycles and trucks
		System.out.println("BICYCLES AND TRUCKS:\n");
		for(int i=0;i<200;i++)
			try{
				if(vehicles[i].isbicycle() || vehicles[i].istruck())//True when either a truck or bicycle
					System.out.println(vehicles[i].toString());
			}
		catch(NullPointerException e){//Ends searcing when out of records to check
			break;
		}
	}

	public static void areacode987(Vehicle[] vehicles){//Method to print records with a phone number having area code 987
		int areacode;//Variable to store area code
		System.out.println("RECORDS IN AREA CODE 987:\n");
		for(int i=0;i<200;i++){
			try{
				areacode = Integer.parseInt((vehicles[i].getphoneNum()).substring(1,4));//Parses area code from phone number
				if(areacode == 987)
					System.out.println(vehicles[i].toString());//Prints when area code = 987
			}
			catch(NullPointerException e){//Ends searching when out of records to check
				break;
			}
		}
	}
}

class Vehicle{//Vehicle class is parent to Car, AmericanCar, ForeignCar, Bicycle, Truck
   //Properties of Vehicle
   protected String owner;
	protected String address;
	protected String phoneNum;
	protected String email;

	public Vehicle(){

	}

   //Constructor for Vehicle
	public Vehicle(String owner, String address, String phoneNum, String email){
   	//Assigns parameters to appropriate property
      this.owner = owner;
		this.address = address;
		this.phoneNum = phoneNum;
		this.email = email;
	}

	public String toString(){//Method to output information in Vehicle
		return (owner + "\n" + address + "\n" + phoneNum + "\n" + email + "\n");
	}

   //Getters
	public String getowner(){
		return owner;
	}

	public String getaddress(){
		return address;
	}

	public String getphoneNum(){
		return phoneNum;
	}

	public String getemail(){
		return email;
	}

   //Setters
	public void setowner(String owner){
		this.owner = owner;
	}

	public void setaddress(String address){
		this.address = address;
	}

	public void setphoneNum(String phoneNum){
		this.phoneNum = phoneNum;
	}

	public void setemail(String email){
		this.email = email;
	}

   //Methods used by method to print bicycle and truck records
	public boolean isbicycle(){
		return false;
	}

	public boolean istruck(){
		return false;
	}

}

class Car extends Vehicle{//Car class is parent to AmericanCar, ForeignCar
   //Properties of Car
   protected boolean convertible;
	protected String color;

	public Car(){
		super();
	}

   //Constructor for Car
	public Car(String owner, String address, String phoneNum, String email, boolean convertible, String color){
		super(owner, address, phoneNum, email);
		this.convertible = convertible;
		this.color = color;
	}

	public String toString(){//Method to output information in vehicle record
		return (owner + "\n" + address + "\n" + phoneNum + "\n" + email + "\n" + Boolean.toString(convertible) + "\n" + color + "\n");

	}

   //Getters
	public boolean getconvertible(){
		return convertible;
	}

	public String color(){
		return color;
	}
   
   //Setters
	public void setconvertible(boolean convertible){
		this.convertible = convertible;
	}

	public void setcolor(String color){
		this.color = color;
	}
}

class AmericanCar extends Car{
   //Properties of AmericanCar
	private boolean detroit;
	private boolean union;

	public AmericanCar(){
		super();
	}

   //Constructor for AmericanCar
	public AmericanCar(String owner, String address, String phoneNum, String email,boolean convertible, String color, boolean detroit, boolean union){
		super(owner,address,phoneNum, email, convertible, color);
		this.detroit = detroit;
		this.union = union;

	}

	public String toString(){//Method to output information in vehicle record
		return (owner + "\n" + address + "\n" + phoneNum + "\n" + email + "\n" + Boolean.toString(convertible) + "\n" + color + "\n" + Boolean.toString(detroit) + "\n" + Boolean.toString(union) + "\n");

	}

   //Getters
	public boolean getdetroit(){
		return detroit;
	}

	public boolean getunion(){
		return union;
	}

   //Setters
	public void setdetroit(boolean detroit){
		this.detroit = detroit;
	}

	public void setunion(boolean union){
		this.union = union;
	}
}

class ForeignCar extends Car{
   //Properties of ForeignCar
	private String country;
	private float duty;

	public ForeignCar(){
		super();
	}

   //Constructor for ForeignCar
	public ForeignCar(String owner,String address,String phoneNum,String email,boolean convertible,String color,String country, float duty){
		super(owner,address,phoneNum, email, convertible, color);
		this.country = country;
		this.duty = duty;

	}

	public String toString(){//Method to output information in vehicle record
		return (owner + "\n" + address + "\n" + phoneNum + "\n" + email + "\n" + Boolean.toString(convertible) + "\n" + color + "\n" + country + "\n" + Float.toString(duty) + "\n");
	}

   //Getters
	public String getcountry(){
		return country;
	}

	public float getduty(){
		return duty;
	}

   //Setters
	public void setcountry(String country){
		this.country = country;
	}

	public void setduty(float duty){
		this.duty = duty;
	}
}

class Bicycle extends Vehicle{
   //Properties of Bicycle
	private int speeds;

	public Bicycle(){
		super();
	}

   //Constructor for Bicycle
	public Bicycle(String owner, String address, String phoneNum, String email, int speeds){
		super(owner,address,phoneNum, email);
		this.speeds = speeds;
	}

	public String toString(){//Method to output information in vehicle record
		return (owner + "\n" + address + "\n" + phoneNum + "\n" + email + "\n" + speeds + "\n");
	}

   //Getters
	public int getspeeds(){
		return speeds;
	}

   //Setters
	public void setspeeds(int speeds){
		this.speeds = speeds;
	}

   //Method used by method to print bicycle and truck records
	public boolean isbicycle(){
		return true;
	}
}

class Truck extends Vehicle{
   //Properties of Truck
	private float tons;//Weight of truck in tons
	private float cost;//Cost of truck
	private String date;//Date of purchase

	public Truck(){
		super();
	}

   //Constructor for Truck
	public Truck(String owner, String address, String phoneNum, String email, float tons, float cost, String date){
		super(owner,address,phoneNum, email);
		this.tons = tons;
		this.cost = cost;
		this.date = date;
	}

	public String toString(){//Method to output information in vehicle record
		return (owner + "\n" + address + "\n" + phoneNum + "\n" + email + "\n" + Float.toString(tons) + "\n" + Float.toString(cost) + "\n" + date + "\n");
	}

   //Getters
	public float gettons(){
		return tons;
	}

	public float getcost(){
		return cost;
	}

	public String getdate(){
		return date;
	}

   //Setters
	public void settons(float tons){
		this.tons = tons;
	}

	public void setcost(float cost){
		this.cost = cost;
	}

	public void setdate(String date){
		this.date = date;
	}

   //Method used by method to print bicycle and truck records
	public boolean istruck(){
		return true;
	}
}

