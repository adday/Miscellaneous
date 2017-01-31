import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;


public class ArrayHeapSort {

	private int[] A;
	private boolean islc;
	
	public ArrayHeapSort(int[] A){
		this.A = A;
		buildHeap();
	}

	private int getLeftChild(int i){
		return A[2*i+1];
	}
	
	private int getRightChild(int i){
		return A[2*(i+1)];
	}
	
	private int max(int i, int lc, int rc){
		if(A[i] > lc && A[i] > rc)
			return A[i];
		else if(lc > rc){
			islc = true;
			return lc;}
		else{
			islc = false;
			return rc;}
	}
	
	private void heapify(int i, int size){
	// left and right subtrees are already heaps
	// need to bubble element i in place top down
		int max;
		int temp;
		if(size > 0){
			max = max(i,getLeftChild(i),getRightChild(i));
			if(max>A[i]){//swap
				temp = A[i];
				A[i] = max;
			if(islc){
				A[2*i+1] = temp;
				i = 2*i+1;}
			else{
				A[2*(i+1)] = temp;
				i = 2*(i+1);
				}
			}
		try{heapify(i,size-1);}
		catch(Exception e){}
		}
	}


	// implement the buildHeap algorithm described in the lecture notes 
	private void buildHeap(){
		for(int i=(A.length-2)/2; i>=0; i-- )
			heapify(i,A.length);
	}

	// implement the in place heapSort algorithm described in the lecture notes
	public void heapSort(){
	for(int i = A.length-1; i>0;i--){
			int temp = A[i];
			A[i] = A[0];
			A[0] = temp;
			heapify(0,i-1);
		}
	}
	
	// return the heap content
	public String toString(){
		return Arrays.toString(A);
	}

	public static void main(String[] args) throws FileNotFoundException{
		// scanner for input file
		Scanner scan = new Scanner( new File (args[0]));
		// first int in input: number of ints to sort following 
		int n = Integer.parseInt(scan.next());
		int[] A = new int[n];
		for(int i = 0; i<n; i++)
			A[i] = Integer.parseInt(scan.next());
		System.out.println("    in: " + Arrays.toString(A));
		ArrayHeapSort ahs = new ArrayHeapSort(A);
		System.out.println("  heap: " + ahs);
		ahs.heapSort();
		System.out.println("sorted: " + ahs);
	}
}
