#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "audiotool.h"

int main(int argc, char const *argv[])
{
	double* buffer;
	long buffer_size;
	WAV_HEADER wavHeader;
	WAV_DATA wavData;
	int i;
	int n=100;
	double w1,w2,s1[n],s2[n],f[n],fi[n],FR[n],FI[n];//,F[100];
	double *F = (double*) malloc(sizeof(double)*n);
	
	const double PI=2.0 * acos(0);
	buffer_size = ReadWAV_double("yes1.wav",&buffer,&wavHeader,&wavData);
	double* Fbuffer = (double*) malloc(sizeof(double)*buffer_size);
	double* Fbuffer_I = (double*) malloc(sizeof(double)*buffer_size);
	double* buffer_I = (double*) malloc(sizeof(double)*buffer_size);
	memset(buffer_I,0,buffer_size);
	//compute_dft(buffer,Fbuffer,buffer_size);
	//FFT(buffer_size,0,buffer,buffer_I,Fbuffer,Fbuffer_I);

	//for(i=0;i<buffer_size;i++){
	//	printf("[%d]=%lf\n",i,sqrt(Fbuffer[i]*Fbuffer[i]+Fbuffer_I[i]*Fbuffer_I[i]));
	//}	


	for(i=0;i<n;i++){
		w1 = PI / 5;
		w2 = PI / 10;
		s1[i]=cos(w1*i);
		s2[i]=cos(w2*i);
		f[i] = s1[i]+s2[i];
		fi[i] = 0;
	}
	//printf("[0]=%lf\n",f[0]);
	//printf("[1]=%lf\n",f[1]);
	//printf("[2]=%lf\n",f[2]);
	//printf("[3]=%lf\n",f[3]);
	//compute_dft(f, F, 100);
	//dft(f,100);
//	dft(buffer, buffer_size);
	printf("%s\n", "test");
	//void Process(int nSamples, int bInverseTransform, double pRealIn[], double pImagIn[], double pRealOut[], double pImagOut[])
	FFT(n,0,f,fi,FR,FI);
	for(i=0;i<n;i++){
		printf("[%d]=%lf\n",i,sqrt(FR[i]*FR[i]+FI[i]*FI[i]));
	}	
	cal_fft();
	return 0;
}