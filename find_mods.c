#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to perform the Sieve of Eratosthenes
void sieve_of_eratosthenes(int max, int** primes, int* primes_count) {
    int* sieve = (int*)malloc((max + 1) * sizeof(int));
    for (int i = 2; i <= max; i++) {
        sieve[i] = 1;
    }

    for (int p = 2; p * p <= max; p++) {
        if (sieve[p]) {
            for (int i = p * p; i <= max; i += p) {
                sieve[i] = 0;
            }
        }
    }

    *primes_count = 0;
    for (int p = 2; p <= max; p++) {
        if (sieve[p]) {
            (*primes_count)++;
        }
    }

    *primes = (int*)malloc((*primes_count) * sizeof(int));
    int index = 0;
    for (int p = 2; p <= max; p++) {
        if (sieve[p]) {
            (*primes)[index++] = p;
        }
    }

    free(sieve);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <max_nth_prime>\n", argv[0]);
        return 1;
    }

    int max_nth_prime = atoi(argv[1]);
    int max_limit = max_nth_prime * 100;  // A safe upper bound for the sieve
    int* primes;
    int primes_count;

    sieve_of_eratosthenes(max_limit, &primes, &primes_count);

    if (max_nth_prime > primes_count) {
        printf("Error: Not enough primes found. Increase the sieve limit.\n");
        free(primes);
        return 1;
    }

    int* bad_mods = (int*)malloc(max_nth_prime * max_nth_prime * sizeof(int));
    int bad_mods_count = 0;

    FILE* file = fopen("bad_mods.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int nth_prime = 0; nth_prime < max_nth_prime; nth_prime++) {
        int p = primes[nth_prime];
        int* bad_k = (int*)malloc(p * sizeof(int));
        int bad_k_count = 0;

        int current_remainder = 2 % p;

        for (int k = 1; k < p; k++) {
            if (current_remainder == 1) {
                bad_k[bad_k_count++] = k;
            }
            current_remainder = (2 * current_remainder) % p;
        }

        for (int j = 0; j < bad_k_count; j++) {
            int k = bad_k[j];
            current_remainder = 2 % p;

            for (int i = 0; i < k; i++) {
                if (current_remainder == 3) {
                    fprintf(file, "(%d, %d)\n", i + 1, k);
                    bad_mods[bad_mods_count++] = i;
                    bad_mods[bad_mods_count++] = k;
                }
                current_remainder = (2 * current_remainder) % p;
            }
        }

        free(bad_k);

        if (nth_prime % (max_nth_prime / 100) == 0) {
            printf("%d percent done\n", nth_prime / (max_nth_prime / 100));
        }
    }

    fclose(file);

    free(bad_mods);
    free(primes);
    return 0;
}
