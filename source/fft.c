#include <complex.h>
#include <stdbool.h>
#include <math.h>
#define PI 3.14159


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
}




