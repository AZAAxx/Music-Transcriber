#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "fft.h"


// NEXT STEP: Use less dynamic memory allocation, either by optimizing array usage, 
// writing iterative FFT, or using one array for all a, a0, a1 memory





Complex z_mult(Complex z1, Complex z2) {
    return (Complex){
        .real = (z1.real * z2.real) - (z1.im * z2.im),
        .im   = (z1.real * z2.im)   + (z1.im * z2.real)
    };
}

Complex z_add(Complex z1, Complex z2) {
    return (Complex){
        .real = z1.real + z2.real,
        .im   = z1.im   + z2.im
    };
}

Complex z_sub(Complex z1, Complex z2) {
    return (Complex){
        .real = z1.real - z2.real,
        .im   = z1.im   - z2.im
    };
}

Complex z_scale(Complex z, double s) {
    return (Complex){ .real = z.real / s, .im = z.im / s };
}



int next_pow2(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}


Complex * format_input(int * audio_input, int audio_size){
    // copy the array A into array a of size 2^exp = n
    int n = next_pow2(audio_size);                             
    Complex * a = malloc(n * sizeof(Complex));
    for(int i=0; i<n; i++) {
        if(i < audio_size) a[i] = (Complex){audio_input[i], 0};
        else a[i] = (Complex){0, 0};
    }
    return a;
}



double * format_result(Complex * a, int n){
    double * bins = malloc(n * sizeof(double));
    for(int i = 0; i < n; i++){
        Complex z = a[i];
        bins[i] = (double) 2 * (z.real * z.real + z.im * z.im) / n;
    }
    return bins;
}





// Main source: https://cp-algorithms.com/algebra/fft.html
void fft(Complex * a, int n, bool inverse) {
    if (n == 1)
        return;


    Complex *a0 = malloc(n/2 * sizeof(Complex));
    Complex *a1 = malloc(n/2 * sizeof(Complex));

    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, n/2, inverse);
    fft(a1, n/2, inverse);

    double ang = 2 * PI / n * (inverse ? -1 : 1);

    Complex w = {1, 0};
    Complex wn = {cos(ang), sin(ang)};

    for (int i = 0; 2 * i < n; i++) {
        //a[i] = a0[i] + w * a1[i];
        a[i] = z_add(a0[i], z_mult(w, a1[i]));
        //a[i + n/2] = a0[i] - w * a1[i];
        a[i + n/2] = z_sub(a0[i], z_mult(w, a1[i]));
        if (inverse) {
            a[i] = z_scale(a[i], 2);                // scaling divides by the number
            a[i + n/2] = z_scale(a[i + n/2], 2);
        }
        w = z_mult(w, wn);
    }

    free(a0);
    free(a1);
}




void efficient_fft(Complex * a, int n, bool inverse) {
    int log_n = 0;     
    while ((1 << log_n) < n) log_n++;

    for (int i = 0; i < n; i++) {
        int reverse = 0;
        for (int i = 0; i < log_n; i++) {
            if (i & (1 << i)) 
                reverse |= 1 << (log_n - 1 - i);
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
            a[i] = z_scale(a[i], n);   //scaling
        }           
    }
}





char* find_note(double * bins, int n){
    int max_k = 1;                      // skip bin 0, which is the DC value
    for(int i = 0; i < n/2; i++){
        if(bins[i] > bins[max_k]) max_k = i;
    }
    double freq = (double) max_k * f_s / n;

    // iterate through frequency array to find the closest frequency
    int note_idx = 0;
    for(int i = 0; i < num_notes; i++){
        if(fabs(frequencies[i] - freq) < fabs(frequencies[note_idx] - freq)) note_idx = i;
    }
    return notes[note_idx];
}




// Applies a Hann window to the audio input
void window(int * audio_input, int audio_size){
    for(int i = 0; i < audio_size; i++){
        double w = sin(PI * i / audio_size);
        audio_input[i] *= w*w;
    }
}





char * get_fft_result(int * audio_input, int audio_size){
    //window(audio_input, audio_size);

    int n = next_pow2(audio_size);

    Complex * a = format_input(audio_input, audio_size);
    fft(a, n, 0);

    double * bins = format_result(a, n);
    free(a);

    char * note = find_note(bins, n);
    free(bins);
    
    return note;
}
