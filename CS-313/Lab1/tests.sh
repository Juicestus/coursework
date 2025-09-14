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
if make; then 
    echo -e "  ${GREEN}Passed${NC}"
    SCORE=$(($SCORE+34))
else
    echo -e "  ${RED}Failed${NC}"
fi

remake
echo -e "\nTesting :: Correct Output\n"
./buggy > out.txt
if  grep 2 out.txt && grep 4 out.txt; then
    echo -e "  ${GREEN}Passed${NC}"
    SCORE=$(($SCORE+33))
else
    echo -e "  ${RED}Failed${NC}"
fi

echo -e "\nTesting :: Testing memory leaks\n"
g++ -fsanitize=address,undefined buggy buggy.cpp
if  ./buggy; then 
    echo -e "  ${GREEN}Passed${NC}"
    SCORE=$(($SCORE+33))
else
    echo -e "  ${RED}Failed${NC}"
fi
# print score and delete executable
echo -e "\nSCORE: ${SCORE}/100\n"
make -s clean

exit 0
