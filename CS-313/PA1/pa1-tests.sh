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

make clean
make

echo -e "\nStart testing"

expected_output="Client-side is done and exited
Server terminated"

if ./client; then
	echo -e "  ${GREEN}Passed${NC}"
	SCORE=$(($SCORE+15))
else
	echo -e "  ${RED}Failed${NC}"
fi

echo -e "\nSCORE: ${SCORE}/85\n"

# Test 2
#if ./client -p 1 -t 0.004 -e 1; then

expected_output="For person 1, at time 0.004, the value of ecg 1 is 0.68"
program_output=$(./client -p 1 -t 0.004 -e 1 2>&1)

if [[ $? -eq 0 && "$program_output" == *"$expected_output"* ]]; then
	echo -e " ${GREEN}Passed${NC}"
	SCORE=$(($SCORE+5))
else
	echo -e " ${RED}Failed${NC}"
fi
echo -e "\nSCORE: ${SCORE}/85\n"

# Test 2 part 2
./client -p 1
if diff -qwB <(head -n 1000 BIMDC/1.csv) received/x1.csv >/dev/null; then
        echo -e "  ${GREEN}Passed${NC}"
        SCORE=$(($SCORE+10))
else
        echo -e "  ${RED}Failed${NC}"
fi
echo -e "\nSCORE: ${SCORE}/85\n"

dd if=/dev/zero of=BIMDC/test.bin bs=1024k count=10
./client -f test.bin
if diff -qwB BIMDC/test.bin received/test.bin > /dev/null;then
	echo -e "  ${GREEN}Passed${NC}"
        SCORE=$(($SCORE+20))
else
        echo -e "  ${RED}Failed${NC}"
fi

rm BIMDC/test.bin received/test.bin

truncate -s 10000000 BIMDC/test.bin
./client -f test.bin
if diff -qwB BIMDC/test.bin received/test.bin > /dev/null;then
        echo -e "  ${GREEN}Passed${NC}"
        SCORE=$(($SCORE+10))
else
        echo -e "  ${RED}Failed${NC}"
fi

rm BIMDC/test.bin received/test.bin

truncate -s 100000000 BIMDC/test.bin
./client -f test.bin
if diff -qwB BIMDC/test.bin received/test.bin > /dev/null;then
        echo -e "  ${GREEN}Passed${NC}"
        SCORE=$(($SCORE+5))
else
        echo -e "  ${RED}Failed${NC}"
fi

rm BIMDC/test.bin received/test.bin

#test 4

# strace -e openat ./client -c -f 5.csv 2> trace.log
# fifo_count=$(grep -o 'fifo_' trace.log | wc -l)

count_fifos() {
    find . -name "*fifo*" -type p 2>/dev/null | wc -l
}

dd if=/dev/zero of=BIMDC/test.bin bs=1024k count=10
./client -c -f test.bin &
CLIENT_PID=$!

fifo_count=0
while kill -0 $CLIENT_PID 2>/dev/null; do
    current_count=$(count_fifos)
    if [[ $current_count -gt $max_fifo_count ]]; then
        fifo_count=$current_count
    fi
    sleep 0.05  # Very short sleep
done

wait $CLIENT_PID

if [[ $fifo_count -gt 2 ]] && diff -qwB BIMDC/test.bin received/test.bin > /dev/null;then
	echo -e "  ${GREEN}Passed${NC}"
        SCORE=$(($SCORE+15))
else
	echo -e " ${RED}Failed (no new channel detected)${NC}"
fi
echo -e "\nSCORE: ${SCORE}/85\n"
rm BIMDC/test.bin received/test.bin

#test 5
if ls fifo* data*_* *.tst *.o *.csv *.log 1>/dev/null 2>&1; then
	echo -e "  ${RED}Failed${NC}"
else
	echo -e "  ${GREEN}Passed${NC}"
        SCORE=$(($SCORE+5))
fi

echo -e "\nSCORE: ${SCORE}/85\n"
