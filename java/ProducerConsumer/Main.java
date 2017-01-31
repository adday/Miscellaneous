public class Main {

	static void Usage(){
		System.out.println(	"Usage:\t\tjava Main arg1 arg2 arg3\n" +
							"\t\tArguments are positive integers:\n" +
							"\t\targ1: size of the BoundedBuffer, BI\n" +
							"\t\targ2: number of items to produce, NI\n" +
							"\t\targ3: max wait time, MW \n");
				}//end Usage()

	public static void main(String[] args) {

		if(args.length<3){Usage();return;}
		int BI,NI,MW;//declare here to place these variables is scope of main
		//check for valid input
		try{ 
		BI = Integer.parseInt(args[0]);
		NI = Integer.parseInt(args[1]);
		MW = Integer.parseInt(args[2]);
		if(BI<0 || NI<0 || MW<0 || (BI==0&&NI!=0)){Usage();return;}
		}catch(Exception e){Usage();return;}

		BoundedBuffer buf = new BoundedBuffer(BI);

		//single producer process
		Producer producer = new Producer(buf,NI,MW,false);
		producer.run();

		//single consumer process
		Consumer consumer = new Consumer(buf,NI,MW,false);
		consumer.run();

		//two producer processes and one consumer process
		Thread thr3 = new Thread(new Producer(buf,NI,MW,true));
		Thread thr4 = new Thread(new Producer(buf,NI,MW,true));
		Thread thr5 = new Thread(new Consumer(buf,2*NI,MW,true));
		thr3.start();
		thr4.start();
		thr5.start();
		try{thr3.join();thr4.join();thr5.join();}catch(Exception e){Usage();return;}
	
	}//end main()

}//end Main.java

