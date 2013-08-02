#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dspProcess.h"

#define PI 3.14
#define FS 8000
#define F 1000
//#define SINE_TBL 8
#define SINE_TBL 3
#define SQRE_TBL 32
#define TRIA_TBL 6
#define SAWT_TBL 17

//short sine_vals[SINE_TBL] = {0, 11583, 16384, 11583, 0, -11583, -16384, -11583};
short sine_vals[SINE_TBL] = {0, 30000, -30000};
short square_vals[SQRE_TBL] = {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 
				16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 
				-16384, -16384, -16384, -16384, -16384, -16384, -16384, -16384,
				-16384, -16384, -16384, -16384, -16384, -16384, -16384, -16384};
short trian_vals[TRIA_TBL] = {-13500, 13500, -13500, -13500, 13500, -13500};
short sawto_vals[SAWT_TBL] = {0, 512, 1024, 1536, 2048, 2560, 3072, 3584, 4096, 4608, 5120, 5632, 6144, 6656, 7168, 7680, 8192};

// core dsp block processing
int dspBlockProcess(short *outputBuffer, short *inputBuffer, int samples, int * filter_on, double * volume){
	int index = 0;
	int i;
	if(*filter_on == 0) {
		for (i=0; i < samples; i+=2){			
			outputBuffer[i] = 0;
			outputBuffer[i+1] = 0;
		}
	}
	else if(*filter_on == 1) {
		for (i=0; i < samples; i+=2){			
			//Left Channel (Red)			
			outputBuffer[i] = (*volume)*sine_vals[index%SINE_TBL];
			//Right Channel (White)			
			outputBuffer[i+1] = (*volume)*sine_vals[index%SINE_TBL];
			index++;
		}
	}
	else if(*filter_on == 2) {
		for (i=0; i < samples; i+=2){			
			outputBuffer[i] = (*volume)*square_vals[index%SQRE_TBL];
			outputBuffer[i+1] = (*volume)*square_vals[index%SQRE_TBL];
			index++;
		}
	}
	else if(*filter_on == 3) {
		for (i=0; i < samples; i+=2){			
			outputBuffer[i] = (*volume)*trian_vals[index%TRIA_TBL];
			outputBuffer[i+1] = (*volume)*trian_vals[index%TRIA_TBL];
			index++;
		}
	}
	else if(*filter_on == 4) {
		for (i=0; i < samples; i+=2){			
			outputBuffer[i] = (*volume)*sawto_vals[index%SAWT_TBL];
			outputBuffer[i+1] = (*volume)*sawto_vals[index%SAWT_TBL];
			index++;
		}
	}
	return DSP_PROCESS_SUCCESS;
}
