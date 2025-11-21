#!/usr/bin/env bash

echo -e "To remove colour from tests, set COLOUR to 1 in sh file\n"
COLOUR=0
if [[ $COLOUR -eq 0 ]]; then
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
MAX_SCORE=100

# ============================================================
# 0. Compilation
# ============================================================
echo -e "${ORANGE}Compiling source...${NC}\n"
make clean >/dev/null 2>&1
make >/dev/null 2>&1

if [[ -f "./pool-test" ]]; then
    echo -e " ${GREEN}Compilation succeeded${NC}"
else
    echo -e " ${RED}Compilation failed${NC}"
    echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"
    exit 1
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 1. Basic Task Submission (10 pts)
# ============================================================
echo -e "${ORANGE}[Test 1] SubmitTask() adds tasks to queue${NC}"
./pool-test > test-out1.txt 2>&1
if grep -q "Added task" test-out1.txt; then
    echo -e " ${GREEN}Passed${NC}"
    SCORE=$((SCORE+10))
else
    echo -e " ${RED}Failed${NC}"
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 2. Task Execution (15 pts)
# ============================================================
echo -e "${ORANGE}[Test 2] Threads start and finish tasks${NC}"
if grep -q "Started task" test-out1.txt && grep -q "Finished task" test-out1.txt; then
    echo -e " ${GREEN}Passed${NC}"
    SCORE=$((SCORE+15))
else
    echo -e " ${RED}Failed${NC}"
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 3. Stop() Behavior (15 pts)
# ============================================================
echo -e "${ORANGE}[Test 3] Stop() cleanly terminates threads${NC}"
if grep -q "Called Stop()" test-out1.txt && grep -q "Stopping thread" test-out1.txt; then
    echo -e " ${GREEN}Passed${NC}"
    SCORE=$((SCORE+15))
else
    echo -e " ${RED}Failed${NC}"
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 4. Multiple Tasks Concurrently (20 pts, with debug)
# ============================================================
echo -e "${ORANGE}[Test 4] Handles multiple concurrent tasks${NC}"
if [[ ! -f test-out1.txt ]]; then
    echo -e " ${RED}No test output found (test-out1.txt missing)${NC}"
    echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"
    exit 1
fi
count=$(grep -c "Started task" test-out1.txt || true)
if [[ $count -ge 3 ]]; then
    echo -e " ${GREEN}Passed${NC}"
    SCORE=$((SCORE+20))
else
    echo -e " ${RED}Failed${NC}"
    echo -e "${ORANGE}--- Debug info for concurrency test ---${NC}"
    echo -e "Found only ${count} 'Started task' lines."
    echo -e "Here are the actual start lines (showing first 10):"
    grep "Started task" test-out1.txt | head -10 || true
    echo -e "\nIf all these lines come from the same thread ID,"
    echo -e "your pool isn't running tasks concurrently."
    echo -e "--------------------------------------${NC}"
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 5. Submitting After Stop (10 pts)
# ============================================================
echo -e "${ORANGE}[Test 5] Submitting after Stop() prevented${NC}"
if grep -q "Cannot added task to queue" test-out1.txt; then
    echo -e " ${GREEN}Passed${NC}"
    SCORE=$((SCORE+10))
else
    echo -e " ${RED}Failed${NC}"
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 6. Memory / Leak Test (15 pts)
# ============================================================
echo -e "${ORANGE}[Test 6] Memory errors (ASAN)${NC}"
if ./pool-test 2>&1 | grep -q "ERROR"; then
    echo -e " ${RED}Failed (memory errors detected)${NC}"
    echo -e "${ORANGE}--- ASAN output snippet ---${NC}"
    ./pool-test 2>&1 | grep -A5 -m1 "ERROR" || true
    echo -e "${ORANGE}--------------------------------------${NC}"
else
    echo -e " ${GREEN}Passed${NC}"
    SCORE=$((SCORE+15))
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 7. remove_task() Correctness (15 pts)
# ============================================================
echo -e "${ORANGE}[Test 7] remove_task() removes from queue${NC}"
if grep -q "Finished task" test-out1.txt; then
    echo -e " ${GREEN}Passed${NC}"
    SCORE=$((SCORE+15))
else
    echo -e " ${RED}Failed${NC}"
fi
echo -e "\nSCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# Final
# ============================================================
echo -e "${ORANGE}Final Score: ${SCORE}/${MAX_SCORE}${NC}\n"
if [[ $SCORE -eq $MAX_SCORE ]]; then
    echo -e "${GREEN}All tests passed!${NC}"
else
    echo -e "${ORANGE}Some tests failed. Review output above.${NC}"
fi
