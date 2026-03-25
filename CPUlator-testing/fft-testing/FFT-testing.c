#include <complex.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159
#define f_s 8000




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
    double * bins = malloc(n * sizeof(double));
    for(int i = 0; i < n; i++)
        bins[i] = (double) 2 * cabs(a[i]) / n;
    return bins;
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





// NEXT STEP: Use less dynamic memory allocation, either by optimizing array usage, writing iterative FFT, or using one array for all a, a0, a1 memory




int main(){

    // get the audio input
    FILE *audio_file = fopen("audio-data.txt", "r");  // open the file
    if (audio_file == NULL) {
        perror("Unable to open audio file");
        return 1;
    }
    double N;
    fscanf(audio_file, "%lf,", &N);

    double* audio_input = malloc(N * sizeof(double));
    int i = 0;
    while (fscanf(audio_file, "%lf,", &audio_input[i]) == 1) i++;
    fclose(audio_file);




    FILE *fptr = fopen("FFT-result.txt", "w");
    if (fptr == NULL) {
        perror("Unable to open result file");
        return 1;
    }

    char str[30];                                    // Buffer to hold the string
    int n = next_pow2(N);

    double * bins = get_fft_result(audio_input, N);

    for(int i=0; i < n-1; i++){
        sprintf(str, "%f", bins[i]);
        fprintf(fptr, "%s", str);
        fprintf(fptr, ", ");
    }
    sprintf(str, "%f", bins[n-1]);                   // print the last one outside the loop for formatting reasons
    fprintf(fptr, "%s", str);

    fclose(fptr);
}