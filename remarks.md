# Best abuse of proof of work

## TL;DR

This program is not a program that *implements* a blockchain.
This program **IS** a blockchain.

## What it does

Compile and run `prog.c`. It outputs a new, valid C program to stdout.
That program contains one more block in its chain. Compile and run *that*
output, and you get another generation with yet another block. Each
generation verifies the entire chain before extending it.

```
$ cc -o gen0 prog.c && ./gen0 > gen1.c
$ cc -o gen1 gen1.c && ./gen1 > gen2.c
$ cc -o gen2 gen2.c && ./gen2 > gen3.c
```

The source code of each generation differs in exactly one place: the
string `B`, which holds the blockchain data. Everything else is
identical -- the quine template, the hash function, the miner, the
verifier. Only the ledger grows.

Tamper with any past generation's chain data and the program refuses
to extend:

```
$ sed 's/\(B="[^"]*\)a/\1b/' gen2.c > corrupt.c
$ cc -o corrupt corrupt.c && ./corrupt > /dev/null
$ echo $?
1
```

## How it works

The program is a **quine** -- it can reconstruct its own source code from
an internal template. But instead of simply printing itself (like a
traditional quine), it:

1. **Reconstructs its own source** using a tilde-escape encoded template
   string `Q` and the chain data string `B`.

2. **Verifies the chain** by replaying history. For each block K in `B`,
   it reconstructs what generation K-1 looked like (same `Q`, but `B`
   containing only the first K-1 blocks). It hashes that reconstruction
   and checks the stored hash. It also verifies the proof-of-work.

3. **Hashes its own source** using FNV-1a with a Murmur-style finalizer.

4. **Mines a new block** by finding a nonce where
   `combine(source_hash, nonce)` has 20 leading zero bits. This takes
   roughly 1 million iterations (~100ms on modern hardware).

5. **Emits the next generation** -- the same program but with `B`
   extended by one block: `HASH:NONCE|`.

### The quine mechanism

`Q` stores the entire program as a string with custom escape sequences:

- `~1` is replaced with `B`'s value (the chain data)
- `~2` is replaced with `Q`'s own raw content (self-reference)
- `~q` produces `"`, `~b` produces `\`, `~n` produces newline
- `~~` produces a literal `~`

Since `Q` is stored as printable ASCII (no C escape sequences), its
in-memory representation IS its source representation. When the emit
function encounters `~2`, it outputs `Q` verbatim -- exactly what must
appear between the quotes of `char*Q="..."` in the next generation.

### The hash function

FNV-1a (32-bit) with a Murmur3-style finalizer for better avalanche
properties:

```
h = 0x811C9DC5
for each byte: h = (byte ^ h) * 0x1000193
h ^= h >> 16; h *= 0x45d9f3b; h ^= h >> 16
```

### Chain verification

This is the key insight that makes verification possible: to check block
K, we need generation K-1's source. But generation K-1 is just `Q`
(which never changes) with the first K-1 blocks of `B` (a prefix of our
current `B`). So we can reconstruct any previous generation without
storing it.

### Proof of work

The combination function mixes the source hash with a candidate nonce:

```
c = source_hash ^ (nonce * 0x9E3779B9)  // golden ratio
c ^= c >> 16; c *= 0x45d9f3b; c ^= c >> 16
```

The nonce is accepted when `c & 0xFFFFF == 0` (20 zero bits).

## The visual layout

The source code flows in a diamond wave pattern, evoking the links of a
chain. The indentation uses only whitespace (which is free under IOCCC
Rule 2b sizing), so the visual layout costs zero net bytes.

## Obfuscation techniques

1. **The quine itself** -- the program contains a string that encodes the
   program that contains the string that encodes...

2. **Numeric character codes** -- `126` instead of `'~'`, `49` instead of
   `'1'`, `113` instead of `'q'`. The emit function reads like a stream
   of meaningless numbers.

3. **Ternary chains** -- the escape decoder is a single nested ternary
   expression: `*q==110?10:*q==113?34:*q==98?92:*q==126?126:*q==116?9:*q`

4. **Dual-mode function** -- `e()` writes to either a buffer or stdout
   depending on whether its third argument is NULL, making it serve
   double duty as both a source reconstructor and an output emitter.

5. **Self-referential verification** -- the program hashes a
   reconstruction of itself to verify blocks. The hash of the program
   depends on Q, which encodes the hash function, which computes
   the hash.

6. **Blockchain-as-format-string** -- the chain data in `B` looks like
   random hex noise (`e820ed67:7d5ef|0b42e083:117636|`), but each
   segment is a cryptographic commitment to a previous generation's
   exact source code.

## Limits

The chain has a natural maximum length. Each block adds ~16 bytes to `B`,
and the IOCCC gross size limit is 4993 bytes. After roughly 130
generations, the program exceeds the limit and can no longer be submitted
to the IOCCC -- though it still compiles and runs fine.

Like Bitcoin's block size debate, but settled by the contest rules.

## Building

```
make
```

## Running the demo

```
make try
```

This runs 5 generations, verifies the quine property, and demonstrates
tamper detection.

## Compatibility

- Compiles cleanly with gcc and clang (one `-Wunused-but-set-variable`
  warning for the block counter `k`)
- gcc and clang produce bit-identical output
- Tested on macOS (Darwin) and Linux
- Requires only `<stdio.h>` and `<string.h>`
