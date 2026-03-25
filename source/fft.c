#include <complex.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159



int next_pow2(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}



double complex * format_input(double * audio_input, int audio_size){
    // copy the array A into array a of size 2^exp = n
    int n = next_pow2(audio_size);                             
    double complex * a = malloc(n * sizeof(double complex));
    for(int i=0; i<n; i++) {
        if(i < audio_size) a[i] = CMPLX(audio_input[i], 0);
        else a[i] = 0;
    }
    return a;
}



double * format_result(complex double * a, int n){
    double * result = malloc(n * sizeof(double));
    for(int i = 0; i < n; i++) {
        result[i] = (double) cabs(a[i]);
        result[i] = result[i]/n;                 // scaling
    }
    return result;
}


// Main source: https://cp-algorithms.com/algebra/fft.html
void fft(double complex * a, int n, bool inverse) {
    if (n == 1)
        return;


    double complex *a0 = malloc(n/2 * sizeof(double complex));
    double complex *a1 = malloc(n/2 * sizeof(double complex));

    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, n/2, inverse);
    fft(a1, n/2, inverse);

    double ang = 2 * PI / n * (inverse ? -1 : 1);

    double complex w = CMPLX(1, 0);
    double complex wn = CMPLX(cos(ang), sin(ang));

    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (inverse) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }

    free(a0);
    free(a1);
}



double * get_fft_result(double* audio_input, int audio_size){
    int n = next_pow2(audio_size);

    complex double * a = format_input(audio_input, audio_size);
    fft(a, n, 0);
    double * result = format_result(a, n);

    free(a);

    return result;
}


