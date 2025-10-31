#!/usr/bin/env bash

# function to clean up files and make executables
remake () {
    # echo -e "\ old files and making executables"
    make -s clean
    make -s >/dev/null 2>&1
}


echo -e "To remove colour from tests, set COLOUR to 1 in sh file\n"
COLOUR=0
if [[ COLOUR -eq 0 ]]; then
    ORANGE='\033[0;33m'
    GREEN='\033[0;32m'
    RED='\033[0;31m'
    NC='\033[0m'
else
    ORANGE='\033[0m'
    GREEN='\033[0m'
    RED='\033[0m'
    NC='\033[0m'
fi

SCORE=5

# if you made it here then it compiled lol
echo -e "\nStart testing"
echo -e "\nTesting :: Compilation\n"
echo -e "  ${GREEN}Test One Passed${NC}"

remake
echo -e "\nTesting :: Memory Leakage\n"
if ./MasterChef -i test-files/NoDep.csv 2>/dev/null 1>/dev/null; then
    echo -e "  ${GREEN}Test Two Passed${NC}"
    SCORE=$(($SCORE+5))
else
    echo -e "  ${RED}Failed${NC}"
fi

remake
echo -e "\nTesting :: Output without Dependencies \n"
./MasterChef -i test-files/NoDep.csv > test-files/cmd.txt 2>/dev/null
if diff -q test-files/cmd.txt test-files/no_dep_output.txt 2>/dev/null; then
    echo -e "  ${GREEN}Test Three Passed${NC}"
    SCORE=$(($SCORE+16))
else
    echo -e "  ${RED}Failed${NC}"
fi

# this includes a 0 length test case
remake
echo -e "\nTesting :: Output with Dependencies \n"
./MasterChef -i test-files/RecipeInput.csv > test-files/cmd.txt 2>/dev/null
if diff -q test-files/cmd.txt test-files/pate_output.txt 2>/dev/null; then
    echo -e "  ${GREEN}Test Four Passed${NC}"
    SCORE=$(($SCORE+17))
else
    echo -e "  ${RED}Failed${NC}"
fi

remake
echo -e "\nTesting :: Use of Timers \n"
strace -o trace.txt ./MasterChef -i test-files/NoDep.csv >out1.txt 2>/dev/null
if [ $(grep 'rt_sigaction(SIGRT_2' trace.txt | wc -l) -gt 0 ]; then
    echo -e "  ${GREEN}Test Five Passed${NC}"
    SCORE=$(($SCORE+24))
else
    echo -e "  ${RED}Incorrect use of signals${NC}"
fi

# remake
echo -e "\nTesting :: Use of Signals \n"
# strace -o trace.txt ./MasterChef -i test-files/NoDep.csv >out2.txt 2>/dev/null
if [ $(grep 'rt_sigaction(SIGUSR1' trace.txt | wc -l) -gt 0 ]; then
    echo -e "  ${GREEN}Test Six Passed${NC}"
    SCORE=$(($SCORE+33))
else
    echo -e "  ${RED}Incorrect use of signals${NC}"
fi

# print score and delete executable
echo -e "\nSCORE: ${SCORE}/100\n"
make -s clean

echo "$SCORE" > score.txt

exit 0
