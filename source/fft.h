#ifndef __FFT__
#define __FFT__


float* FFT(float audio[]);           //Fast Fourier Transform function

char** get_notes(float*);            //gets the results of the FFT and returns a string array of played notes. Ex. C7, A2, G5


#endif