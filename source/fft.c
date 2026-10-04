#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "fft.h"

// Below complex functions are implemented as such because the complex.h is not supported 

// Complex multiplication
Complex z_mult(Complex z1, Complex z2) {
    return (Complex){
        .real = (z1.real * z2.real - z1.im * z2.im),
        .im   = (z1.real * z2.im   + z1.im * z2.real)
    };
}
// Complex addition
Complex z_add(Complex z1, Complex z2) {
    return (Complex){
        .real = z1.real + z2.real,
        .im   = z1.im   + z2.im
    };
}
// Complex subtraction
Complex z_sub(Complex z1, Complex z2) {
    return (Complex){
        .real = z1.real - z2.real,
        .im   = z1.im   - z2.im
    };
}
// Complex scaling
Complex z_scale(Complex z, double s) {
    return (Complex){ .real = z.real / s, .im = z.im / s };
}


// find the smallest power of 2 greater than n
int next_pow2(int n) {      
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

// format the input by converting the int array into a Complex array
Complex * format_input(int * audio_input, int audio_size){
    int n = next_pow2(audio_size);                                   // the formatted array will have length n for ease of FFT computation
    Complex * a = malloc(n * sizeof(Complex));                       // allocate memory for the Complex array
    for(int i=0; i<n; i++) {                       
        if(i < audio_size) a[i] = (Complex){audio_input[i] >> 8, 0}; // if within audio_size, use audio data to construct Complex
        else a[i] = (Complex){0, 0};                                 // if in the extended part, use 0
    }
    return a;
}

// format output by converting the Complex array to a double array storing complex number magnitudes
double * format_result(Complex * a, int n){
    double * bins = malloc(n * sizeof(double));                      // allocate double array
    for(int i = 0; i < n; i++){
        Complex z = a[i];                         
        bins[i] = (double) 2 * ((long long) z.real * z.real + (long long) z.im * z.im) / n;  // assign the magnitude of z to associated bin
    }
    return bins;
}

void fft(Complex * a, int n, bool inverse) {
    if (n == 1)
        return;

    Complex *a0 = malloc(n/2 * sizeof(Complex));
    Complex *a1 = malloc(n/2 * sizeof(Complex));

    for (int i = 0; 2 * i < n; i++) {                      // divide data into equal-length two arrays
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, n/2, inverse);                                 // perform FFT on those arrays
    fft(a1, n/2, inverse);

    double ang = 2 * PI / n * (inverse ? -1 : 1);

    Complex w = {1, 0};
    Complex wn = {cos(ang), sin(ang)};

    for (int i = 0; 2 * i < n; i++) {                      // merge the two arrays and store the results in a
        a[i] = z_add(a0[i], z_mult(w, a1[i]));
        a[i + n/2] = z_sub(a0[i], z_mult(w, a1[i]));
        if (inverse) {
            a[i] = z_scale(a[i], 2);
            a[i + n/2] = z_scale(a[i + n/2], 2);
        }
        w = z_mult(w, wn);
    }

    free(a0);                                              // free the a0 and a1 arrays used for computation
    free(a1);
}


// An efficient version of the above FFT algorithm
void efficient_fft(Complex * a, int n, bool inverse) {
    int log_n = 0;     
    while ((1 << log_n) < n) log_n++;

    for (int i = 0; i < n; i++) {
        int reverse = 0;
        for (int j = 0; j < log_n; j++) {
            if (i & (1 << j)) 
                reverse |= 1 << (log_n - 1 - j);
        }
        if (i < reverse) {
            Complex temp = *(a + i);
            *(a + i) = *(a + reverse);
            *(a + reverse) = temp;
        }
    }

    for (int len = 2; len <= n; len <<= 1) {

        double ang = 2 * PI / len * (inverse ? -1 : 1);
        Complex wlen = (Complex) {cos(ang), sin(ang)};

        for (int i = 0; i < n; i += len) {
            Complex w = (Complex) {1, 0};

            for (int j = 0; j < len / 2; j++) {
                Complex u = a[i+j], v = z_mult(a[i+j+len/2], w);
                a[i+j] = z_add(u, v);
                a[i+j+len/2] = z_sub(u, v);
                w = z_mult(w, wlen);
            }
        }
    }

    if (inverse) {
        for(int i = 0; i < n; i++){
            a[i] = z_scale(a[i], n);
        }           
    }
}


// Uses the double * magnitude array bins to find the note with the greatest magnitude
char* find_note(double * bins, int n){
    int max_k = 1;
    for(int i = 2; i < n/2; i++){
        if(bins[i] > bins[max_k]) max_k = i;               // iterate over bins to find the greatest one
    }
    double freq = (double) max_k * f_s / n;                // compute the frequency of that bin

    int note_idx = 0;
    for(int i = 0; i < num_notes; i++){                    // iterate over frequencies[] to find the closest note frequency (frequencies defined in header)
        if(fabs(frequencies[i] - freq) < fabs(frequencies[note_idx] - freq)) note_idx = i;
    }
    return notes[note_idx];                                // return the note name (char *) of that note (notes defined in header)
}

void window(int * audio_input, int audio_size){            // Apply a windowing function to smooth signal and prevent spectral leakage
    for(int i = 0; i < audio_size; i++){
        double w = sin(PI * i / audio_size);               // The window has a sin^2 shape with audio_size as its half-period
        audio_input[i] *= w*w;
    }
}

// Function that merges all other functionality to use in the main code
const char * get_fft_result(int * audio_input, int audio_size){
    int n = next_pow2(audio_size);                         // find nect power of 2 of audio size
    window(audio_input, audio_size);                       // apply the windowing function to input to smooth the signal

    Complex * a = format_input(audio_input, audio_size);   // format input
    efficient_fft(a, n, 0);                                // perform fft to get frequency components

    double * bins = format_result(a, n);                   // get magnitudes of frequency components (bins *)
    free(a);                                               // free the Complex * array 

    const char * note = find_note(bins, n);                // analyze the bins to find the greatest one and the associated note
    free(bins);                                            // free bins *
 
    return note;                                           // return the (char *) note
}

