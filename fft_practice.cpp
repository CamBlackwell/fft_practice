#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
using Complex = complex<double>; //complex number
using CArray = vector<Complex>; //complex array

const double PI = acos(-1);

void fft(CArray &x) {
	const size_t N = x.size();
	if (N <= 1) return; //if array is a single poly, return;
	


	//Bit reversal so it reverses to normal after
	
	size_t j = 0; //bit reversed counter start 
	for (size_t i=1; i < N; i++){ //for all elements in the polynomial O(N)
		size_t bit = N >> 1; //get half of N

		while (j & bit) { //while current bit is 1

			j ^= bit; //flip the bit to 0
			bit >>= 1; //go to next bit 
		}

		j ^= bit; //flip final bit
			
		if (i < j) {
			swap(x[i], x[j]);
		}

	} 


	//Iterative FFT
	for (size_t len = 2; len <= N; len <<=1) { //start with pairs then ^2, stop when len is double in size
		double angle = -2 * PI / len; //complex angle for function
		complex wlen(cos(angle), sin(angle)); //this is the complex function for e
		for (size_t i = 0; i < N; i += len) { //each pair, iterate 2 
			Complex w(1); //initialise complex mover to 1
			for (size_t j = 0; j < len / 2; j++) { //work on each pair
				Complex u = x[i + j]; //first element
				Complex v = x[i + j + len/2] * w; //twiddle factor (second element

				x[i+j] = u + v; //first (evens)
				x[i+j+ len/2] = u - v; //odds
				w *= wlen; //iterate complex forwards
			}
		}
	}
}

int main() {
	const size_t N = 1024; //ammount of buffers
	CArray signal(N);

	for (size_t i=0; i < N; i++) {
			signal[i] = Complex(sin(2 * PI * 50 * i / N) + 0.5 * sin(2 * PI * 120 * i / N), 0);
	} //sample, sum of 2 sines

	fft(signal);

	for (size_t i = 0; i < N; i++) {
		cout << abs(signal[i]) << endl;
	}

	return 0;
}