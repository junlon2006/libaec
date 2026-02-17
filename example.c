#include "aec.h"
#include <stdio.h>
#include <math.h>

int main() {
    aec_t *aec = aec_init(256, 0.3f);
    if (!aec) {
        printf("Init failed\n");
        return -1;
    }
    
    int num_samples = AEC_SAMPLE_RATE * 2;
    
    for (int i = 0; i < num_samples; i++) {
        // Simulate 16-bit signals
        int16_t ref = (int16_t)(16384.0f * sinf(2.0f * 3.14159f * 440.0f * i / AEC_SAMPLE_RATE));
        int16_t echo = (int16_t)(ref * 0.3f);
        int16_t near = (int16_t)(3276.0f * sinf(2.0f * 3.14159f * 880.0f * i / AEC_SAMPLE_RATE));
        int16_t mic = echo + near;
        
        int16_t output = aec_process(aec, ref, mic);
        
        if (i % AEC_SAMPLE_RATE == 0) {
            printf("Time: %ds, Input: %d, Output: %d\n", i / AEC_SAMPLE_RATE, mic, output);
        }
    }
    
    aec_destroy(aec);
    printf("Done\n");
    return 0;
}
