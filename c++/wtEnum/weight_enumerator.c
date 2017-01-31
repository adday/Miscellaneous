// weight_enumerator.c
//
//  lab 1 in MATH460
// Alexander Day
// 830 523 317


#include <iostream>

using namespace std;

void unrank(int rk, int *v, int len);
void multiply(int *v, int *M, int *w, int k, int n);
int weight(int *w, int n);

int main(int argc, char **argv)
{
	//INT t0 = os_ticks();
	int verbose_level = 2;
	int i, j;
	int n = 12;     // length of the code
	int k = 4;      // dimension of the code
	int q = 2;
	int N;          // number of codewords
	int rk, wt;
	int M[] = {
                1,1,1,1,1,1,1,1,1,0,0,0,
                1,1,1,1,0,0,0,0,0,1,0,0,
                1,1,1,0,1,0,0,0,0,0,1,0,
                1,1,0,1,1,0,0,0,0,0,0,1
		};      // generator matrix
	int *v;         // message word
	int *w;         // codeword
	int *weights;   // weight enumerator

	// we allocate the arrays:
	v = new int[k];
	w = new int[n];
	weights = new int[n + 1];

	// we initialize the array with zeros:
	for (i = 0; i <= n; i++) {
		weights[i] = 0;
		}

	// we compute N = 2^k:
	N = 1;
	for (i = 0; i < k; i++) {
		N *= q;
		}
	
	// we loop over all message words.

	for (rk = 0; rk < N; rk++) {

		// create the message by unranking the integer rk:
		unrank( rk,v, N);		

		// we form the linear combination by multiplying v from the left to the matrix M.
		// this yields the codeword w.
		multiply( v, M, w, k, n);

		// compute the weight of the codeword:
		wt = weight(w, n);

		// print the rank, the message vector, the corresponding codeword and the weight:		
		cout << rk << " : ";
		for (i = 0; i < k; i++) 
			cout << v[i];
			cout << " : ";
		for (i = 0; i < n; i++) 
			cout << w[i];
			cout << " : " << wt << endl;
		
		// update the table of weights:
		weights[wt]++;
		}

	cout << "weight enumerator:" << endl;
	for (i = 0; i <= n; i++) {
		cout << i << " : " << weights[i] << endl;
		}
}

void unrank(int rk, int *v, int l)
// maps the integers from 0 to 2^l-1 to the vectors
// (0,...,0), (1,...,0), ... , (1,...,1), the binary representation
// in reverse lexicographic order.
{
	int i, a;
	for (i = 0; i < l; i++) {
		a = rk % 2;
		v[i] = a;
		rk -= a;
		rk >>= 1;
		}
}

void multiply(int *v, int *M, int *w, int k, int n)
// input: row vector v[k], matrix M[k * n], k, n
// output w[n]
{
	for(int i=0;i<n;i++){
		w[i] = 0;
		for(int j=0;j<k;j++){
			w[i] += v[j] * M[j*n+i];
			} 
		w[i] = w[i] % 2;
		}
}

int weight(int *v, int n)
// input: v[n], 
// output: the number of nonzero entries of v
{
	int wt = 0;
	for(int i=0;i<n;i++)
		if(v[i] != 0) wt++;	
	return wt;
}


