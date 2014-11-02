#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "audiotool.h"

#define M_PI   3.14159265358979323846

int WAVInfo(const char* filename)
{
 FILE *fp=NULL;
 WAV_HEADER wavHeader;
 WAV_DATA wavData;
    fp=fopen(filename,"rb");
    if (fp == NULL){
      printf("fail to open %s\n", filename);
      return 0;
    }
    unsigned short cbSize;
    fread(&wavHeader,sizeof(WAV_HEADER),1,fp); 
    if (wavHeader.Subchunk1Size==18){
      fread(&cbSize,1,2,fp);
    }
    fread(&wavData,sizeof(WAV_DATA),1,fp);
    if (wavHeader.AudioFormat == 1){
      printf("Audio Type is PCM\n");

    }
    if (wavHeader.NumOfChan == 1){
      printf("Audio Channel is Mono\n");
    }else if (wavHeader.NumOfChan == 2){
      printf("Audio Channel is Sterio\n");
    }
    printf("Audio SamplesPerSec is %dHz\n",wavHeader.SamplesPerSec);
    printf("wavHeader.bitsPerSample=%d\n",wavHeader.bitsPerSample);
    
  fclose(fp);
}

long ReadWAV_float(const char* filename,float** pbuffer_float, WAV_HEADER* pwavHeader, WAV_DATA* pwavData)
{
  long wavedata_buffer_size = -1;
  short* buffer_short;
  int i;
  wavedata_buffer_size = ReadWAV_short(filename, &buffer_short, pwavHeader, pwavData);  
  float *temp_buffer = (float*)malloc(sizeof(float)*wavedata_buffer_size);
  for (i=0;i< wavedata_buffer_size; i++){
    temp_buffer[i] = (float)buffer_short[i]/32768.0;
  }
  *pbuffer_float = temp_buffer;
  free(buffer_short);
  return wavedata_buffer_size;
}

long ReadWAV_double(const char* filename,double** pbuffer_float, WAV_HEADER* pwavHeader, WAV_DATA* pwavData)
{
  long wavedata_buffer_size = -1;
  short* buffer_short;
  int i;
  wavedata_buffer_size = ReadWAV_short(filename, &buffer_short, pwavHeader, pwavData);  
  double *temp_buffer = (double*)malloc(sizeof(double)*wavedata_buffer_size);
  for (i=0;i< wavedata_buffer_size; i++){
    temp_buffer[i] = (double)buffer_short[i]/32768.0;
  }
  *pbuffer_float = temp_buffer;
  free(buffer_short);
  return wavedata_buffer_size;
}

long ReadWAV_short(const char* filename,short** pbuffer, WAV_HEADER* pwavHeader, WAV_DATA* pwavData)
{
    int i;
    long wavedata_buffer_size = -1;
  	FILE *fp=NULL;
    fp=fopen(filename,"rb");
    if (fp == NULL){
      printf("fail to open %s\n", filename);
      return 0;
    }
    unsigned short cbSize;
    fread(pwavHeader,sizeof(WAV_HEADER),1,fp); 
    if (pwavHeader->Subchunk1Size==18){
      fread(&cbSize,1,2,fp);
    }
    fread(pwavData,sizeof(WAV_DATA),1,fp);
    short *wavedata_buffer;
    short *temp_buffer = (short*)malloc(pwavData->Subchunk2Size);
    fread((void*)temp_buffer, pwavData->Subchunk2Size, (size_t)1, fp);
    short *ori_temp_buffer = temp_buffer;
    short *ori_wavedata_buffer;
    if (pwavHeader->NumOfChan == 1){
      wavedata_buffer = temp_buffer;
      *pbuffer = wavedata_buffer;
       wavedata_buffer_size = pwavData->Subchunk2Size ;
    }else if (pwavHeader->NumOfChan == 2){
      wavedata_buffer = (short*)malloc(pwavData->Subchunk2Size/2);
      ori_wavedata_buffer  = wavedata_buffer;
      *pbuffer = wavedata_buffer;  
      wavedata_buffer_size = pwavData->Subchunk2Size/2/sizeof(short);
      memset(wavedata_buffer,0,wavedata_buffer_size);
      // each sample has 16bit, sample size = pwavedata_buffer_size/2
      for (i=0;i< wavedata_buffer_size; i++){
        memcpy(wavedata_buffer, temp_buffer, 2);
        //because wavedata_buffer++ equal +2 so i < pwavedata_buffer_size/sizeof(short)
        wavedata_buffer++;
        temp_buffer+=2;
      }
    }else{
       wavedata_buffer_size = -1;
       *pbuffer = NULL;
    }
    
    fclose(fp);
    return wavedata_buffer_size;
}


