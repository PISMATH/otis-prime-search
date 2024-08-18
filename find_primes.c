#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define MAX_LINE_LENGTH 50

// Function to read bad mods from the file
int read_bad_mods(const char* filename, int** bad_mods, int* bad_mods_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s!\n", filename);
        return -1;
    }

    *bad_mods_count = 0;
    int rem, modulus;
    while (fscanf(file, "(%d, %d)\n", &rem, &modulus) != EOF) {
        (*bad_mods_count)++;
    }

    rewind(file);
    *bad_mods = (int*)malloc((*bad_mods_count) * 2 * sizeof(int));

    int index = 0;
    while (fscanf(file, "(%d, %d)\n", &rem, &modulus) != EOF) {
        (*bad_mods)[index++] = rem;
        (*bad_mods)[index++] = modulus;
    }

    fclose(file);
    return 0;
}

// Optimized function to check if p = 2^k - 3 is prime
int is_otis_prime(int k) {
    mpz_t p, base, exponent, result;
    mpz_init(p);
    mpz_init(base);
    mpz_init(exponent);
    mpz_init(result);

    // Calculate p = 2^k - 3
    mpz_ui_pow_ui(p, 2, k);
    mpz_sub_ui(p, p, 3);

    // Calculate base = 2
    mpz_set_ui(base, 2);

    // Calculate exponent = 2^(k-1)
    mpz_ui_pow_ui(exponent, 2, k - 1);

    // Calculate result = base^exponent mod p
    mpz_powm(result, base, exponent, p);

    // Check if result == p - 1 (which is -4 mod p)
    mpz_add_ui(result, result, 4);

    int is_prime = mpz_cmp(result, p) == 0;

    // Clear memory
    mpz_clear(p);
    mpz_clear(base);
    mpz_clear(exponent);
    mpz_clear(result);

    return is_prime;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <max_prime_size>\n", argv[0]);
        return 1;
    }

    int max_prime_size = atoi(argv[1]);
    const char* filename = "bad_mods.txt";
    int* bad_mods;
    int bad_mods_count;

    if (read_bad_mods(filename, &bad_mods, &bad_mods_count) != 0) {
        return 1;
    }

    printf("Starting search with %d bad mods to use\n", bad_mods_count);

    int num_otis_primes = 7; // Because the mods rule out the first 7 otis primes
    int failed_prime_tests = 0;

    for (int i = 1; i < max_prime_size; i++) {
        int skip = 0;
        for (int j = 0; j < bad_mods_count; j += 2) {
            int rem = bad_mods[j];
            int modulus = bad_mods[j + 1];
            if (skip || i % modulus == rem) {
                skip = 1;
                break;
            }
        }
        if (skip) {
            continue;
        }

        if (is_otis_prime(i)) {
            printf("%d\n", i);
            num_otis_primes += 1;
        } else {
            failed_prime_tests += 1;
        }
    }

    free(bad_mods);

    printf("Finished search with %d otis primes found\n", num_otis_primes);
    printf("%d prime tests done\n", num_otis_primes + failed_prime_tests);
    printf("%.4f%% of prime tests resulted in an otis prime\n", 
           num_otis_primes * 100.0 / (num_otis_primes + failed_prime_tests));
    printf("The bad mods made an estimated %.4f%% improvement in speed\n",
           max_prime_size * 100.0 / (num_otis_primes + failed_prime_tests));

    return 0;
}
