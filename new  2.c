/*            DSP-THREAD.H                            */
/*----------------------------------------------------*/
// Success and failure definitions for the thread
#define     DSP_THREAD_SUCCESS     ( ( void * ) 0 )
#define     DSP_THREAD_FAILURE     ( ( void * ) - 1 )

// DSP thread environment definition (i.e. what the dsp thread needs to 
// continue to operate)
typedef  struct  dsp_thread_env
{
    int quit;                // Thread will run as long as quit = 0
    int filter_on;			 //
    double volume;
    int done;				 // To capture when the DSP is done.
} dsp_thread_env;

// dspthread function prototypes
void * dsp_thread_start( void * envByRef );
void * ioProcessing(void *envByRef, void *apPtr);
//=========================================================================

/*            DSP-PROCESS.H                           */
/*----------------------------------------------------*/
 
#include "buffer.h"

#define     DSP_PROCESS_SUCCESS     0
#define     DSP_PROCESS_FAILURE    -1

int dspBlockProcess(short *outputBuffer, short *inputBuffer, int samples, int * filter_on, double * volume);
void initIIRBuffers();
void destroyIIRBuffers();
//=========================================================================

/*            BUFFER.H                           */
/*----------------------------------------------------*/
 #ifndef BUFFER_H
#define BUFFER_H

// This must be a power of 2, i.e. 2^N, in order for this library to work
#define BUFF_SIZE 8
#define BUFF_SIZE_MASK (BUFF_SIZE-1)

typedef struct buffer{
	//float buff[BUFF_SIZE];
	short *buff;
	unsigned int index;
}buffer;

void initBuffer(buffer* buffer);
void push(buffer* buffer,short value);
short pop(buffer* buffer);
short readn(buffer* buffer, int Xn);
void destroyBuffer(buffer* buffer);

#endif
//==============================================================================

/*            AUDIO-IO.H                           */
/*----------------------------------------------------*/

#include     <alsa/asoundlib.h>		// ALSA includes

/* Success and Failure definitions for audio functions */
#define     AUDIO_SUCCESS     0
#define     AUDIO_FAILURE     -1

//* The number of channels of the audio codec **
#define     NUM_CHANNELS     2
#define     BYTESPERFRAME    4

// Define ALSA devices
#define	SOUND_DEVICE	"plughw:0,0" // Use for line in and out

//* The sample rate of the audio codec **
#define     SAMPLE_RATE      44100

//* The gain (0-100) of the left channel **
#define     LEFT_GAIN        100

//* The gain (0-100) of the right channel **
#define     RIGHT_GAIN       100

//*  Parameters for DSP thread execution **
// Should be a power of 2, i.e. 2^n, and no less than 4096
#define     BLOCKSIZE        4096

// The levels of initialization for initMask
#define     INPUT_ALSA_INITIALIZED      0x1
#define     INPUT_BUFFER_ALLOCATED      0x2
#define     OUTPUT_ALSA_INITIALIZED     0x4
#define     OUTPUT_BUFFER_ALLOCATED     0x8


// Audio Parameter Definitions (i.e. what the dsp thread needs to 
// continue to operate)
typedef  struct  audio_params
{
	// initMask to keep track of init steps
    unsigned int initMask;
        
    // Input and output driver variables
    snd_pcm_uframes_t exact_bufsize;
    snd_pcm_t *pcm_capture_handle;
    snd_pcm_t *pcm_output_handle;
    int blksize;	// Raw input or output frame size
    int right_gain;
    int left_gain;
    int sample_rate;
    char *inputBuffer;	// Input buffer for driver to read into
    char *outputBuffer;	// Output buffer for driver to read from
    

} audio_params;

/* Function prototypes */
int audio_io_setup(void * apPtr );

int audio_io_cleanup( void * apPtr );