
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define f_s 8000
#define PI 3.1415926535


typedef struct {
    int sample_rate;
    int num_samples;
    int *samples;
    int idx;
} WAVData;




/* THIS FUNCTION IS FOR TESTING PURPOSES ONLY AND WAS WRITTEN BY CLAUDE AI */
WAVData read_wav(const char *filename) {
    WAVData result = {0};
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        perror("Failed to open file");
        return result;
    }

    // --- Read WAV header ---
    char chunk_id[4];
    int chunk_size, sample_rate, byte_rate;
    short audio_format, num_channels, block_align, bits_per_sample;
    int subchunk2_size;

    fread(chunk_id, 1, 4, f);           // "RIFF"
    fread(&chunk_size, 4, 1, f);        // file size - 8
    fread(chunk_id, 1, 4, f);           // "WAVE"
    fread(chunk_id, 1, 4, f);           // "fmt "
    fread(&chunk_size, 4, 1, f);        // 16 for PCM
    fread(&audio_format, 2, 1, f);      // 1 = PCM
    fread(&num_channels, 2, 1, f);      // 1 = mono
    fread(&sample_rate, 4, 1, f);       // e.g. 44100
    fread(&byte_rate, 4, 1, f);         // sample_rate * block_align
    fread(&block_align, 2, 1, f);       // num_channels * bits/8
    fread(&bits_per_sample, 2, 1, f);   // 16

    // Validate
    if (audio_format != 1) {
        printf("Error: only PCM WAV files are supported\n");
        fclose(f);
        return result;
    }
    if (num_channels != 1) {
        printf("Error: only mono WAV files are supported\n");
        fclose(f);
        return result;
    }
    if (bits_per_sample != 16) {
        printf("Error: only 16-bit WAV files are supported\n");
        fclose(f);
        return result;
    }

    // Some WAV files have extra bytes in the fmt chunk — skip them
    if (chunk_size > 16) {
        fseek(f, chunk_size - 16, SEEK_CUR);
    }

    // Find the "data" chunk (skip any metadata chunks like "LIST")
    char data_id[4];
    while (1) {
        if (fread(data_id, 1, 4, f) < 4) {
            printf("Error: could not find data chunk\n");
            fclose(f);
            return result;
        }
        fread(&subchunk2_size, 4, 1, f);
        if (strncmp(data_id, "data", 4) == 0) break;
        fseek(f, subchunk2_size, SEEK_CUR);  // skip non-data chunks
    }

    // --- Read samples ---
    int num_samples = subchunk2_size / sizeof(short);
    int *samples = malloc(subchunk2_size);
    if (samples == NULL) {
        printf("Error: malloc failed\n");
        fclose(f);
        return result;
    }
    fread(samples, sizeof(int), num_samples, f);
    fclose(f);

    result.sample_rate = sample_rate;
    result.num_samples = num_samples;
    result.samples = samples;
    result.idx = 0;
    return result;
}


int * get_audio_samples(WAVData * wav, int sample_count){
    int * audio_data = malloc(sample_count * sizeof(int));
    int k = 0;

    while(k < sample_count){
        if(wav->idx + k >= wav->num_samples) audio_data[k] = 0;   // fill with 0 if sample size not enough
        else audio_data[k] = wav->samples[wav->idx + k];               // copy over the data to buffer
        k++;
    }
    wav->idx += sample_count;
    return audio_data;
}



#include <complex.h>
#include <stdbool.h>

 // returns a number that is a power of two bigger than n
int next_pow2(int n);       

// formats the input to turn the type to complex double and reallocate array to size next_pow2()
double complex * format_input(int * audio_input, int audio_size);         

// formats the result to turn the type to double and scales by 1/n
double * format_result(double complex * a, int n);

// computes the fft, array a is changed to be the result
void fft(double complex * a, int n, bool inverse);

// returns the note in a string that has the biggest frequency component
char * find_note(double * bins, int n);

// Applies a Hann window to the audio input
void window(int * audio_input, int audio_size);

// USE THIS FUNCTION: does all the above steps and returns the note as a string
char * get_fft_result(int * audio_input, int audio_size);




int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./program <file.wav>\n");
        return 1;
    }

    WAVData wav = read_wav(argv[1]);
    if (wav.samples == NULL) return 1;

    printf("Sample rate: %d Hz\n", wav.sample_rate);
    printf("Num samples: %d\n", wav.num_samples);
    printf("Duration: %.2f seconds\n", (float)wav.num_samples / wav.sample_rate);

    // Print first 10 samples as a sanity check
    for (int i = 0; i < 10 && i < wav.num_samples; i++) {
        printf("sample[%d] = %d\n", i, wav.samples[i]);
    }


    /* below content is for testing AUDIO.c analyze_audio_continuous() */

    int tempo = 120;                             // tempo is BPM, beats per minute, specifically quarter notes per minute

    double duration_quarter = (double) 60/tempo;
    double duration_eighth = (double) 30/tempo;
    
    int total_samples = duration_eighth * f_s;           // the sensitivity is for now only eighth notes !!!

    while(wav.idx < wav.num_samples){
        //get the audio samples 
        int * audio_samples = get_audio_samples(&wav, total_samples);
        printf("idx: %d / %d\n", wav.idx, wav.num_samples); 
        // process the samples
        char * note = get_fft_result(audio_samples, total_samples);    // process the audio to get the note
        printf("%s\n", note);                            // print the audio (for now)
    }




    free(wav.samples);
    return 0;
}

