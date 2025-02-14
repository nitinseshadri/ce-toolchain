#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/util.h>

#include "f64_fma_LUT.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

size_t run_test(void) {
    typedef struct { long double x; long double y; long double z; } input_t;
    typedef long double output_t;

    const size_t length = ARRAY_LENGTH(f64_fma_LUT_input);
    const input_t  *input  = (const input_t* )((const void*)f64_fma_LUT_input );
    const output_t *output = (const output_t*)((const void*)f64_fma_LUT_output);

    for (size_t i = 0; i < length; i++) {
        long double result = fmal(input[i].x, input[i].y, input[i].z);
        if (result != output[i]) {
            return i;
        }
    }

    /* passed all */
    return SIZE_MAX;
}

int main(void) {
    os_ClrHome();
    size_t fail_index = run_test();
    if (fail_index == SIZE_MAX) {
        printf("All tests passed");
    } else {
        printf("Failed test: %zu", fail_index);
    }

    while (!os_GetCSC());

    return 0;
}
