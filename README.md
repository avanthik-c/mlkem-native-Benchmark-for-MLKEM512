# ML-KEM-512 Native Implementation Wrapper

This project provides a secure, C-based wrapper for generating Post-Quantum cryptographic keys using the formally verified `mlkem-native` library. It is specifically configured and armored for the **ML-KEM-512** parameter set.

## System Prerequisites
This project requires a Linux environment with the kernel entropy pool accessible via `<sys/random.h>`.
* `gcc`
* `make`
* `git`

## Setup & Installation

**1. Clone the repository and initialize the submodule**
```bash
git clone https://github.com/avanthik-c/mlkem-native-Benchmark-for-MLKEM512.git
cd mlkem-native-Benchmark-for-MLKEM512
```
**2. Compiling **
```bash
cd mlkem-native-Benchmark-for-MLKEM512
make clean
export CFLAGS="-DMLK_K=2"
make build
cd ..
gcc -O3 -Wall -Wextra -Wno-stringop-overflow mlkem512.c -o mlkem_benchmark \
    -DMLK_K=2 \
    -DMLK_CONFIG_NAMESPACE_PREFIX=PQCP_MLKEM_NATIVE_MLKEM512 \
    -I./mlkem-native/mlkem \
    ./mlkem-native/test/build/libmlkem512.a

```
**3. Run**
`./mlkem_benchmark`
