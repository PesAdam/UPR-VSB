#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "=== Spustam automatizovane testy pre UPR projekt ==="

# 1. kompilacia projektu
echo "[INIT] Kompilujem projekt..."
make -s clean
make -s
if [ $? -ne 0 ]; then
    echo -e "${RED}[CHYBA] Kompilacia zlyhala!${NC}"
    exit 1
fi
echo -e "${GREEN}[OK] Kompilacia uspesna${NC}"
echo ""

# 2. testovanie
FAILED_TESTS=0
TOTAL_TESTS=0   

for test_dir in tests/*/; do
    test_name=$(basename "$test_dir")
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo ">>> Testujem: $test_name"
    
    # definicia suborovx
    matches="$test_dir/matches.txt"
    players="$test_dir/players.txt"
    expected="$test_dir/expected_output.html"
    actual="$test_dir/actual_output.html"
    error_log="$test_dir/error.log"
    
    # spustenie programu
    # ./lol-stats <matches> <players> <output>
    ./lol-stats "$matches" "$players" "$actual" > /dev/null 2> "$error_log"
    EXIT_CODE=$?
    
    # detekcia ci ocakavame uspech alebo zlyhanie
    if [ -f "$expected" ]; then
        if [ $EXIT_CODE -ne 0 ]; then
            echo -e "${RED}[FAIL] Program spadol alebo vratil chybu (kod $EXIT_CODE).${NC}"
            cat "$error_log"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            # ponechame error log pre analyzu
        else
            # porovnanie vystupu
            diff -q "$expected" "$actual" > /dev/null
            if [ $? -eq 0 ]; then
                echo -e "${GREEN}[PASS] Vystup je spravny.${NC}"
                # upratanie pri uspechu
                rm -f "$actual" "$error_log"
            else
                echo -e "${RED}[FAIL] Vystup HTML sa nezhoduje s ocakavanim!${NC}"
                echo "Rozdiel (diff):"
                diff "$expected" "$actual" | head -n 5
                echo "Vystup programu ulozeny v: $actual"
                FAILED_TESTS=$((FAILED_TESTS + 1))
                rm -f "$error_log"
            fi
        fi
    else
        # nevalidny vsstup - ocakavame chybu
        # ak nie je expected_output.html
        if [ $EXIT_CODE -ne 0 ]; then
            echo -e "${GREEN}[PASS] Program spravne detekoval chybu.${NC}"
            # vymazeme pri uspechu aby nevznikal zbytocny bordel
            rm -f "$actual" "$error_log"
        else
            echo -e "${RED}[FAIL] Program mal skoncit chybou, ale skoncil uspesne (0).${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            # ponechame vystup pre analyzu
        fi
    fi
    
    echo "---------------------------------------------------"
done

echo ""
if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}Vsetky testy ($TOTAL_TESTS) presli uspesne!${NC}"
    exit 0
else
    echo -e "${RED}Pocet zlyhanych testov: $FAILED_TESTS z $TOTAL_TESTS${NC}"
    exit 1
fi
