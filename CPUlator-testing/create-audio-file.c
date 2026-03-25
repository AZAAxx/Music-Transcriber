
#include <stdio.h>

void create_frequency_file(double frequency, double volume, double duration){
    
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen("CPUlator-testing/audio-data.txt", "w");

    // Write some text to the file
    fprintf(fptr, "Audio data:\n");


    double t_sample = 125.0 / 1000000.0;

    int half_period_samples = (int)((1.0 / frequency / 2.0) / t_sample);

    if (half_period_samples < 1) half_period_samples = 1;

    int total_samples = (int)(duration / t_sample);

    fprintf(fptr, "Total samples:\n");
    char str[10];                                    // Buffer to hold the string
    sprintf(str, "%d", (int)(total_samples));
    fprintf(fptr, str);
    fprintf(fptr, "\n");

    int counter = 0;
    int sign = 1;
    int samples_written = 0;

    while (samples_written < total_samples) {
        
        str[10];                                     // Buffer to hold the string
        sprintf(str, "%d", (int)(sign * volume));
        fprintf(fptr, str);
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
    create_frequency_file(2000, 20, 0.1);
}