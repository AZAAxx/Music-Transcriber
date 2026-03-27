#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926535

void create_frequency_file(double frequency, double amplitude, double duration){
    
    FILE *fptr;
    fptr = fopen("audio-data.txt", "w");

    double t_sample = 125.0 / 1000000.0;
    double period = 1 / frequency;

    double N = period / t_sample;  // this is the number of samples in a period, NOT an integer

    int total_samples = (int)(duration / t_sample);

    char str[30];                   
    sprintf(str, "%d", total_samples);
    fprintf(fptr, "%s", str);
    fprintf(fptr, ",\n");

    int k = 0;

    // x[n] = A * sin(2PI/N * k)

    while (k < total_samples) {
        int voltage = amplitude * sin(2 * PI * k / N);
        sprintf(str, "%d", voltage);
        fprintf(fptr, "%s", str);
        fprintf(fptr, ", ");
        k++;
    }

    fclose(fptr);     // Close the file
}


int main(int argc, char *argv[]) {    
    int frequency = atoi(argv[1]);
    create_frequency_file(frequency, 1<<30 , 0.25);
    printf("Input frequency: %d\n", frequency);
}