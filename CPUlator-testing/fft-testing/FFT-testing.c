#include <complex.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define f_s 8000
#define PI 3.1415926535




// Frequencies (Hz)
double frequencies[] = {
    // C0 - B0
    16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87,

    // C1 - B1
    32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74,

    // C2 - B2
    65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98.00, 103.83, 110.00, 116.54, 123.47,

    // C3 - B3
    130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,

    // C4 - B4
    261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,

    // C5 - B5
    523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77,

    // C6 - B6
    1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760.00, 1864.66, 1975.53,

    // C7 - B7
    2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 3951.07,

    // C8 - B8
    4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040.00, 7458.62, 7902.13
};



// Note names
char *notes[] = {
    // C0 - B0
    "C0","C#0","D0","D#0","E0","F0","F#0","G0","G#0","A0","A#0","B0",

    // C1 - B1
    "C1","C#1","D1","D#1","E1","F1","F#1","G1","G#1","A1","A#1","B1",

    // C2 - B2
    "C2","C#2","D2","D#2","E2","F2","F#2","G2","G#2","A2","A#2","B2",

    // C3 - B3
    "C3","C#3","D3","D#3","E3","F3","F#3","G3","G#3","A3","A#3","B3",

    // C4 - B4
    "C4","C#4","D4","D#4","E4","F4","F#4","G4","G#4","A4","A#4","B4",

    // C5 - B5
    "C5","C#5","D5","D#5","E5","F5","F#5","G5","G#5","A5","A#5","B5",

    // C6 - B6
    "C6","C#6","D6","D#6","E6","F6","F#6","G6","G#6","A6","A#6","B6",

    // C7 - B7
    "C7","C#7","D7","D#7","E7","F7","F#7","G7","G#7","A7","A#7","B7",

    // C8 - B8
    "C8","C#8","D8","D#8","E8","F8","F#8","G8","G#8","A8","A#8","B8"
};


int num_notes = sizeof(frequencies) / sizeof(frequencies[0]);






int next_pow2(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}


double complex * format_input(int * audio_input, int audio_size){
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



void swap(double complex * a, double complex * b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}


void efficient_fft(double complex * a, int n, bool inverse) {
    int log_n = 0;     
    while ((1 << log_n) < n) log_n++;

    for (int i = 0; i < n; i++) {
        int reverse = 0;
        for (int i = 0; i < log_n; i++) {
            if (i & (1 << i)) 
                reverse |= 1 << (log_n - 1 - i);
        }
        if (i < reverse) swap(a+i, a+reverse);
    }

    for (int len = 2; len <= n; len <<= 1) {

        double ang = 2 * PI / len * (inverse ? -1 : 1);
        double complex wlen = CMPLX(cos(ang), sin(ang));

        for (int i = 0; i < n; i += len) {
            double complex w = CMPLX(1, 0);

            for (int j = 0; j < len / 2; j++) {
                double complex u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (inverse) {
        for(int i = 0; i < n; i++){
            a[i] /= n;    //scaling
        }           
    }
}





char* find_note(double * bins, int n){
    int max_k = 1;                      // skip bin 0, which is the DC value
    for(int i = 0; i < n/2; i++){
        if(bins[i] > bins[max_k]) max_k = i;
    }
    double freq = (double) max_k * f_s / n;
    
    printf("Found frequency: %.2lf   ", freq);

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
    window(audio_input, audio_size);

    int n = next_pow2(audio_size);

    complex double * a = format_input(audio_input, audio_size);
    efficient_fft(a, n, 0);

    double * bins = format_result(a, n);
    free(a);

    char * note = find_note(bins, n);
    free(bins);

    return note;
}







int main(){

    // get input from file, ONLY FOR TESTING
    FILE *audio_file = fopen("audio-data.txt", "r");  // open the file
    if (audio_file == NULL) {
        perror("Unable to open audio file");
        return 1;
    }
    int N;
    fscanf(audio_file, "%d,", &N);

    int * audio_input = malloc(N * sizeof(int));
    int i = 0;
    while (fscanf(audio_file, "%d,", &audio_input[i]) == 1) i++;
    fclose(audio_file);


    // THE FUNCTIONAL CODE
    char * note = get_fft_result(audio_input, N);
    printf("%s\n", note);
    // END OF THE FUNCTIONAL CODE


    // Write output to file, ONLY FOR TESTING 
    FILE *fptr = fopen("FFT-result.txt", "w");
    if (fptr == NULL) {
        perror("Unable to open result file");
        return 1;
    }

    complex double * a = format_input(audio_input, N);
    int n = next_pow2(N);
    fft(a, n, 0);
    double * bins = format_result(a, n);

    free(a);

    char str[30];  
    for(int i=0; i < n-1; i++){
        sprintf(str, "%lf", bins[i]);
        fprintf(fptr, "%s", str);
        fprintf(fptr, ", ");
    }
    sprintf(str, "%lf", bins[n-1]);     // print the last one outside the loop for formatting reasons
    fprintf(fptr, "%s", str);

    fclose(fptr);
}






/*
double * format_result(complex double * a, int n){
    double * bins = malloc(n * sizeof(double));            

    for(int i = 0; i < n/2; i++) {         // can ignore greate half due to symmetry
        bins[i] = (double) cabs(a[i])/n;   // scaling 
    }

    double * result = malloc(f_s * sizeof(double));   // f_s/2 is the max detectable frequency

    for(int i = 0; i < n/2; i++){
        int freq = (int)round((double) i * f_s / n);
        if (freq < f_s) result[freq] = bins[i];
    }
    free(bins);
    return result;
}
*/






