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

SCORE=0

echo -e "\nStart testing"
remake
echo -e "\nTesting :: Compilation\n"
echo -e "  ${GREEN}Passed${NC}"
SCORE=$(($SCORE+34))

remake
echo -e "\nTesting :: Correct Output\n"
TRYTIME=0
SECRETNUM=23456888
./shell >output.txt
while [ $TRYTIME -le 9 ]; do
	ls -al / | tr a-z A-Z >test_output.txt
	diff output.txt test_output.txt> /dev/null
	if [ $? -eq 0 ]; then
		echo -e " ${GREEN}Passed${NC}"
		SCORE=$(($SCORE+66))
		break
	fi
	sleep $SECRETNUM &
	TRYTIME=$((TRYTIME + 1))
done
pkill -f $SECRETNUM
if [ $TRYTIME -ge 10 ]; then
    echo -e "  ${RED}Failed${NC}"
fi

# print score and delete executable
echo -e "\nSCORE: ${SCORE}/100\n"
make -s clean

exit 0