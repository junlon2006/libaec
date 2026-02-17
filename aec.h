#ifndef AEC_H
#define AEC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AEC_SAMPLE_RATE 16000
#define AEC_CHANNELS 1

typedef struct {
    float *w;           // Adaptive filter coefficients
    float *x;           // Reference signal buffer
    int filter_len;     // Filter length
    int pos;            // Current position
    float mu;           // Step size factor
} aec_t;

// Initialize AEC (filter_len: 128-512, mu: 0.1-0.5)
aec_t* aec_init(int filter_len, float mu);

// Process 16-bit samples (ref: reference signal, mic: microphone signal)
int16_t aec_process(aec_t *aec, int16_t ref, int16_t mic);

// Destroy AEC instance
void aec_destroy(aec_t *aec);

#ifdef __cplusplus
}
#endif

#endif
