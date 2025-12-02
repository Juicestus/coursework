#!/usr/bin/env bash

if ! command -v strace 2>&1 >/dev/null
then
    echo "strace not found. Please install strace"
    exit 1
fi

if ! command -v awk 2>&1 >/dev/null
then
    echo "awk not found. Please install awk"
    exit 1
fi

ORANGE='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "\nStart testing"
echo -e "\nTesting :: Compilation\n"
make clean -sj
make -sj
if [ $? -eq 0 ]; then
        echo -e "       ${GREEN}Compilation Test Passed${NC}"
        SCORE=$(($SCORE+10))
else
        echo -e "  ${RED}Failed${NC}"
        exit 0 
fi

echo -e "\nTesting :: Correct Output for Sections 1 and 3\n"
CORRECT_VALUE=$(awk '{ sum += $1 } END { print sum }' ./test-files/2000.csv)
if [ `./Teller -i ./test-files/2000.csv 2>/dev/null | grep -a -- "${CORRECT_VALUE}" | wc -l` -ge 2 ] 
then
        echo -e "       ${GREEN}Test Two Passed${NC}"
        SCORE=$(($SCORE+33))
else
        echo -e "       ${RED}Failed${NC}"
fi

echo -e "\nTesting :: Use of Threads\n"
strace -o out.trace ./Teller -i ./test-files/2000.csv 2>&1 >/dev/null
if cat out.trace | grep -a "clone" | grep -qaF "CLONE_THREAD"; then
        echo -e "       ${GREEN}Test Three Passed${NC}"
        SCORE=$(($SCORE+24))
else
        echo -e "       ${RED}Failed${NC}"
fi

echo -e "\nTesting :: Safe Data Access\n"
NUM_VALS=$(for i in $(seq 1 100); do ./Teller -i ./test-files/2000.csv  | tail -n 1; done | cut -d' ' -f11 | sort | uniq | wc -l)
if [ ${NUM_VALS} -eq 1 ];
then
        echo -e "       ${GREEN}Test Four Passed${NC}"
        SCORE=$(($SCORE+33))
else
        echo -e "       ${RED}Failed${NC}"
fi

make clean -sj

echo ""
echo ""
echo -e "${ORANGE}====================================${NC}"
echo -e "Net Score: ${GREEN}$SCORE/100.0${NC}"
echo -e "${ORANGE}====================================${NC}"
echo ""
