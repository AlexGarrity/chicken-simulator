/**
    A short program to fairly optimally solve a maths problem
    https://www.youtube.com/watch?v=NzhXipwiz_E

    In a barn, 100 chicks sit peacefully in a circle. Suddenly, each chick
    randomly pecks the chick immediately to its left or right. What is the
    expected number of unpecked chicks?
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


/**   XORSHIFT128   **/
/** (Thanks George) **/
/**   (Also Wiki)   **/
struct xorshift128_state {
  uint32_t a, b, c, d;
};

struct xorshift128_state g_xorshiftState;

/* The state array must be initialized to not be all zero */
uint32_t xorshift128(struct xorshift128_state *state)
{
	/* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
	uint32_t t = state->d;

	uint32_t const s = state->a;
	state->d = state->c;
	state->c = state->b;
	state->b = s;

	t ^= t << 11;
	t ^= t >> 8;
	return state->a = t ^ s ^ (s >> 19);
}


/** CHICKEN SIMULATOR **/

const size_t CHICKEN_COUNT = 1E2; // 100
const size_t TRIALS_TO_RUN = 1E5; // 100K

inline void simulate_pecking(bool *chickens) {
    // Generate a whole bunch of bools very quickly
    bool values[CHICKEN_COUNT];
    for (size_t i = 0; i < CHICKEN_COUNT; i += sizeof(uint32_t)) {
        uint32_t r = xorshift128(&g_xorshiftState);
        for (size_t j = 0; j < sizeof(int); ++j) {
            values[i + j] = (bool) r >> j;
        }
    }

    // Check for pecks
    for (size_t i = 0; i < CHICKEN_COUNT; ++i) {
        bool left = values[i];
        // Leave the branch predictor to figure this mess out
        if (left) {
            if (i == 0) {
                chickens[CHICKEN_COUNT - 1] = true;
            }
            else {
                chickens[i - 1] = true;
            }
        }
        else {
            chickens[i % CHICKEN_COUNT] = true;
        }
    }
}

inline double calculate_pecking_rate(bool *arr) {
    // Add all the probabilities together, divide by the number of them
    size_t total = 0;
    for (size_t i = 0; i < CHICKEN_COUNT; ++i) {
        if (arr[i])
            total+=1;
    }
    return (double) total / (double) CHICKEN_COUNT;
}

int main() {
    double total = 0.0f;

    // Initialise xorshift state
    g_xorshiftState.a = rand();
    g_xorshiftState.b = rand();
    g_xorshiftState.c = rand();
    g_xorshiftState.d = rand();

    // Create some chickens
    bool *chickens = malloc(sizeof(bool) * CHICKEN_COUNT);

    // Run all the trials
    for (size_t i = 1; i <= TRIALS_TO_RUN; ++i) {
        // Optional - I like it
        if (i % 1000 == 0) {
            printf("Iteration %lu\n", i);
            printf("Pecking rate is %.6f\n", total / (double)i);
        }
        // Zero the chickens
        memset(chickens, 0, CHICKEN_COUNT);
        simulate_pecking(chickens);
        total += calculate_pecking_rate(chickens);
    }

    // Destroy some chickens
    free(chickens);

    printf("\nCalculated pecking rate for %lu iterations, %lu chickens per iteration\n", TRIALS_TO_RUN, CHICKEN_COUNT);
    printf("Pecking rate is %.6f\n", total / (double) TRIALS_TO_RUN);
}
