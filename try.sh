#!/usr/bin/env bash
#
# try.sh - see remarks.md

set -e

CC="${CC:-cc}"
CFLAGS="${CFLAGS:--std=gnu17 -O2 -Wall -Wextra -pedantic}"

rm -f gen[0-9]* corrupt corrupt.c

cp prog.c gen0.c
$CC $CFLAGS -o gen0 gen0.c -Wno-unused-but-set-variable 2>/dev/null

echo "=== MINING THE CHAIN ==="
echo ""

for i in 0 1 2 3 4; do
    next=$((i + 1))
    echo -n "Block ${i}: "
    ./gen${i} > gen${next}.c
    B=$(grep -o 'char\*B="[^"]*"' gen${next}.c | sed 's/char\*B="//;s/"$//')
    # Show only the latest block
    latest=$(echo "$B" | tr '|' '\n' | tail -2 | head -1)
    echo "$latest"
    $CC $CFLAGS -o gen${next} gen${next}.c -Wno-unused-but-set-variable 2>/dev/null
done

echo ""
echo "=== FULL CHAIN (gen5.c) ==="
B=$(grep -o 'char\*B="[^"]*"' gen5.c | sed 's/char\*B="//;s/"$//')
echo "$B" | tr '|' '\n' | grep -n . | sed 's/^/  Block /' | sed 's/:1:/ 0: /' | sed 's/:\([0-9]\):/\1: /'

echo ""
echo "=== QUINE CHECK ==="
PASS=0
for i in 1 2 3 4 5; do
    diff -q <(sed 's/char\*B="[^"]*"/char*B=""/' gen${i}.c) \
            <(sed 's/char\*B="[^"]*"/char*B=""/' gen0.c) > /dev/null 2>&1 && PASS=$((PASS+1))
done
echo "  ${PASS}/5 generations are identical (except chain data)"

echo ""
echo "=== TAMPER TEST ==="
sed 's/\(char\*B="[^"]*\)a/\1b/' gen3.c > corrupt.c
$CC $CFLAGS -o corrupt corrupt.c -Wno-unused-but-set-variable 2>/dev/null
echo -n "  Corrupted gen3.c, running: "
if ./corrupt > /dev/null 2>&1; then
    echo "accepted (ERROR)"
else
    echo "rejected (exit $?)"
fi

rm -f gen[0-9]* corrupt corrupt.c
