#include "aec.h"
#include <stdlib.h>

#define INT16_TO_FLOAT(x) ((x) / 32768.0f)
#define FLOAT_TO_INT16(x) ((int16_t)((x) * 32768.0f))

aec_t* aec_init(int filter_len, float mu) {
    aec_t *aec = (aec_t*)malloc(sizeof(aec_t));
    if (!aec) return NULL;
    
    aec->filter_len = filter_len;
    aec->mu = mu;
    aec->pos = 0;
    
    aec->w = (float*)calloc(filter_len, sizeof(float));
    aec->x = (float*)calloc(filter_len, sizeof(float));
    
    if (!aec->w || !aec->x) {
        free(aec->w);
        free(aec->x);
        free(aec);
        return NULL;
    }
    
    return aec;
}

int16_t aec_process(aec_t *aec, int16_t ref, int16_t mic) {
    float ref_f = INT16_TO_FLOAT(ref);
    float mic_f = INT16_TO_FLOAT(mic);
    
    // Update reference signal buffer
    aec->x[aec->pos] = ref_f;
    
    // Estimate echo signal
    float y = 0.0f;
    for (int i = 0; i < aec->filter_len; i++) {
        int idx = (aec->pos - i + aec->filter_len) % aec->filter_len;
        y += aec->w[i] * aec->x[idx];
    }
    
    // Calculate error signal
    float e = mic_f - y;
    
    // Calculate reference signal power
    float power = 1e-6f;
    for (int i = 0; i < aec->filter_len; i++) {
        power += aec->x[i] * aec->x[i];
    }
    
    // Update filter coefficients (NLMS algorithm)
    float step = aec->mu / power;
    for (int i = 0; i < aec->filter_len; i++) {
        int idx = (aec->pos - i + aec->filter_len) % aec->filter_len;
        aec->w[i] += step * e * aec->x[idx];
    }
    
    // Update position
    aec->pos = (aec->pos + 1) % aec->filter_len;
    
    return FLOAT_TO_INT16(e);
}

void aec_destroy(aec_t *aec) {
    if (aec) {
        free(aec->w);
        free(aec->x);
        free(aec);
    }
}
