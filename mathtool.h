#pragma once

extern void dft(double* xR, int N);
extern void degree_add( double *pcos_a , double* psin_a, double cos_b, double sin_b);
//extern void compute_dft(double inreal[], double outreal[], double outimag[], int n);
extern void compute_dft(double inreal[], double out[], int n);
extern void cal_fft();
extern void FFT(int nSamples, int bInverseTransform, double pRealIn[], double pImagIn[], double pRealOut[], double pImagOut[]);

//extern void degree_add( double& cos_a , double& sin_a, double cos_b, double sin_b);
