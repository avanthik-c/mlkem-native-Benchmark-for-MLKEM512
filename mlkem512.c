#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/random.h> 

#include <mlkem_native.h>

#define MLKEM512_PK_BYTES 800
#define MLKEM512_SK_BYTES 1632

// ---------------------------------------------------------
// Entropy Source: MUST return int (0 on success)
// ---------------------------------------------------------
int randombytes(uint8_t *out, size_t outlen) {
    ssize_t ret = getrandom(out, outlen, 0);
    if (ret < 0 || (size_t)ret != outlen) {
        fprintf(stderr, "Fatal error: randombytes failed to gather kernel entropy.\n");
        return -1; // Tell the ML-KEM library the RNG failed
    }
    return 0; // Success! The missing link.
}

int main(void) {
    uint8_t pk[MLKEM512_PK_BYTES] = {0};
    uint8_t sk[MLKEM512_SK_BYTES] = {0};

    printf("Starting natively optimized ML-KEM-512 Key Generation...\n");

    clock_t start = clock();
    
    // Generate the keypair
    int result = crypto_kem_keypair(pk, sk);
    
    clock_t end = clock();

    if (result != 0) {
        printf("Error: Key generation failed with code %d.\n", result);
        return EXIT_FAILURE;
    }

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n--- ML-KEM-512 Keys ---\n");
    
    printf("Public Key :\n ");
    for (int i = 0; i < MLKEM512_PK_BYTES; i++) {
        printf("%02x", pk[i]);
    }
    
    printf("\nSecret Key: \n");
    for (int i = 0; i < MLKEM512_SK_BYTES; i++) {
        printf("%02x", sk[i]);
    }

    printf("\n\n--- Performance ---\n");
    printf("Time taken: %f seconds\n", time_taken);

    // Secure wipe
    volatile uint8_t *p = (volatile uint8_t *)sk;
    for (size_t i = 0; i < MLKEM512_SK_BYTES; i++) {
        p[i] = 0;
    }

    return EXIT_SUCCESS;
}
