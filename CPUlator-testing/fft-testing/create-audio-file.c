
#include <stdio.h>

void create_frequency_file(double frequency, double volume, double duration){
    
    FILE *fptr;
    fptr = fopen("audio-data.txt", "w");

    double t_sample = 125.0 / 1000000.0;
    double half_period_samples = ((1.0 / frequency / 2.0) / t_sample);

    if (half_period_samples < 1) half_period_samples = 1;

    int total_samples = (int)(duration / t_sample);

    char str[30];                   
    sprintf(str, "%d", total_samples);
    fprintf(fptr, "%s", str);
    fprintf(fptr, ",\n");

    int counter = 0;
    int sign = 1;
    int samples_written = 0;

    while (samples_written < total_samples) {
        sprintf(str, "%d", (int)(sign * volume));
        fprintf(fptr, "%s", str);
        fprintf(fptr, ", ");
        counter++;
        samples_written++;
        if (counter >= half_period_samples) {
            sign = -sign;
            counter = 0;
        }
    }

    // Close the file
    fclose(fptr);
}


int main(){
    int frequency = 256;
    create_frequency_file(frequency, 20, 0.1);
    printf("Input frequency: %d\n", frequency);
}