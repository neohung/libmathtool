#include "mathtool.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI  2.0 *acos(0)
//
void compute_dft(double inreal[], double out[], int n) {
	int k;
	double* outreal = (double*)malloc(sizeof(double)*n);
	double* outimag = (double*)malloc(sizeof(double)*n);
	for (k = 0; k < n/2; k++) {  
		double sumreal = 0;
		double sumimag = 0;
		int t;
		//angle = 0*0~0*n, 疊加起來->F[0] 
		//angle = 2*pi*(1/n)*0~2*pi*(1/n)*n, 疊加起來->F[1]
		//angle = 2*pi*(2/n)*0~2*pi*(2/n)*n, 疊加起來->F[2]
		for (t = 0; t < n; t++) { 
			double angle = 2 * PI * t * k / n;
			sumreal +=  inreal[t] * cos(angle) ;//+ inimag[t] * sin(angle);
			sumimag += -inreal[t] * sin(angle) ;//+ inimag[t] * cos(angle);
		}
		outreal[k] = sumreal;
		outimag[k] = sumimag;
		out[k] = sqrt(outreal[k]*outreal[k] + outimag[k]*outimag[k]);
		//printf("%lf,%lf,%lf\n",sumreal,sumimag,out[k]);
	}
}

//檢查是否為以2為基底的數
int IsPowerOfTwo(int number) 
{ 
	if( number < 2 ) return 0; 
	//如果是2,4,8...都會是10b,100b,1000b等等,所以x-1為01b,011b,0111b,故x為2的倍數時(x)&(x-1)=0
	if( (number & (number-1)) != 0 ) return 0; 	 
		return 1; 
}

//
int NumberOfBitsNeeded(int nSamples) 
{ 
	int i; 
	if( nSamples < 2 ) 
		return 0; 
	//6=110b,i=1(1個0),7=111b,i=0(0個0),8=1000b,i=3(3個0), 
    for ( i=0; i <= nSamples; i++ ) { 
     	if( (nSamples & (1 << (int)i)) != 0){ 
			return i; 
		}
	}  
    return 0; 
} 

//把Bit反轉
//例如ReverseBits(1, 3)即把001b 變成100b = 4
//例如ReverseBits(3, 3)即把011b 變成110b = 6
int ReverseBits(int nIndex, int nBits) 
{ 
	int i, rev; 
	for(i = 0, rev = 0; i < nBits; i++) { 
		rev = (rev << 1) | (nIndex & 1); 
		nIndex >>= 1; 
	} 
	return rev;  
} 

double Index_to_frequency(int nBaseFreq, int nSamples, int nIndex) 
{ 
	if(nIndex >= nSamples) { 
		return 0.0; 
	} else if(nIndex <= nSamples / 2) { 
		return ( (double)nIndex / (double)nSamples * nBaseFreq ); 
	} else { 
		return ( -(double)(nSamples-nIndex) / (double)nSamples * nBaseFreq ); 
	} 
} 

void FFT(int nSamples, int bInverseTransform, double pRealIn[], double pImagIn[], double pRealOut[], double pImagOut[])
{
	if(pRealIn == NULL || pRealOut == NULL || pImagOut == NULL)
		return;
	int NumBits;
	int i, j, k, n;
	int BlockSize, BlockEnd;
	double angle_numerator = 2.0 * PI;
	double tr, ti;
	if( !IsPowerOfTwo(nSamples) ){
		printf("It is not 2 of base!!!\n");
		return;
	}
	// bInverseTransform = 0 -> FFT, bInverseTransform = 1 -> IFFT
	if( bInverseTransform )
    	angle_numerator = -angle_numerator;

    //
	NumBits = NumberOfBitsNeeded(nSamples);


	for( i=0; i < nSamples; i++ ){
		//
		j = ReverseBits(i, NumBits);
		pRealOut[j] = pRealIn[i];
		pImagOut[j] = (pImagIn == NULL) ? 0.0 : pImagIn[i];
	}

	BlockEnd = 1;
	for( BlockSize = 2; BlockSize <= nSamples; BlockSize <<= 1 ){
		double delta_angle = angle_numerator / (double)BlockSize;
		double sm2 = sin( -2 * delta_angle );
		double sm1 = sin( -delta_angle );
		double cm2 = cos( -2 * delta_angle );
		double cm1 = cos( -delta_angle );
		double w = 2 * cm1;
		double ar[] = { 0, 0, 0};
        double ai[] = { 0, 0, 0 };

		for( i=0; i < nSamples; i += BlockSize ){
			ar[2] = cm2;
			ar[1] = cm1;

			ai[2] = sm2;
			ai[1] = sm1;

			for ( j=i, n=0; n < BlockEnd; j++, n++ ){
				ar[0] = w*ar[1] - ar[2];
				ar[2] = ar[1];
				ar[1] = ar[0];

				ai[0] = w*ai[1] - ai[2];
				ai[2] = ai[1];
				ai[1] = ai[0];

				k = j + BlockEnd;
				tr = ar[0]*pRealOut[k] - ai[0]*pImagOut[k];
				ti = ar[0]*pImagOut[k] + ai[0]*pRealOut[k];

				pRealOut[k] = pRealOut[j] - tr;
				pImagOut[k] = pImagOut[j] - ti;

				pRealOut[j] += tr;
				pImagOut[j] += ti;
			}
		}
		BlockEnd = BlockSize;
	}

	if( bInverseTransform ){
		double denom = (double)nSamples;
		for ( i=0; i < nSamples; i++ ){
			pRealOut[i] /= denom;
			pImagOut[i] /= denom;
		}
	}
}

void cal_fft()
{
	printf("%d\n",ReverseBits(0, 3));
	printf("%d\n",ReverseBits(1, 3));
	printf("%d\n",ReverseBits(2, 3));
	printf("%d\n",ReverseBits(3, 3));
	printf("%d\n",ReverseBits(4, 3));
	printf("%d\n",ReverseBits(5, 3));
	printf("%d\n",ReverseBits(6, 3));
	printf("%d\n",ReverseBits(7, 3));
	printf("%d\n",ReverseBits(8, 3));

}