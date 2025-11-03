#!/usr/bin/env bash

# function to clean up files and make executables
remake () {
    #echo -e "\nCleaning old files and making executables"
    make -s clean
    make -s >/dev/null 2>&1
}

SCORE=0
MAX_SCORE=75

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


echo -e "${YELLOW}Starting Aggie Shell rubric-aligned tests (with diagnostics)...${NC}\n"
remake

# ============================================================
# 1. Echo (5 pts)
# ============================================================
echo "[Test 1] echo"
echo -e "\nTesting :: echo \"Hello world | Life is Good > Great $\"\n"
cat ./test-files/test_echo_double.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_echo_double.txt)
if ./shell < ./test-files/cmd.txt 2>/dev/null | grep -qF -- "${RES}"; then
    echo -e "  ${GREEN}Test One Passed${NC}"
    SCORE=$((SCORE + 5))
else
    echo -e "  ${RED}Failed${NC}"
fi
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 2. Simple Commands (10 pts)
# ============================================================
echo "[Test 2] simple commands with arguments"
echo -e "\nTesting :: ls\n"
cat ./test-files/test_ls.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_ls.txt)
if ./shell < ./test-files/cmd.txt 2>/dev/null | grep -qF -- "${RES}"; then
    echo -e "  ${GREEN}Test Two Passed${NC}"
else
    echo -e "  ${RED}Failed${NC}"
fi


echo -e "\nTesting :: ls -l /usr/bin\n"
cat ./test-files/test_ls_l_usr_bin.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_ls_l_usr_bin.txt)
if ./shell < ./test-files/cmd.txt 2>/dev/null | grep -qF -- "${RES}"; then
    echo -e "  ${GREEN}Test Three Passed${NC}"
else
    echo -e "  ${RED}Failed${NC}"
fi

echo -e "\nTesting :: ls -l -a\n"
cat ./test-files/test_ls_l_a.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_ls_l_a.txt)
if ./shell < ./test-files/cmd.txt 2>/dev/null | grep -qF -- "${RES}"; then
    echo -e "  ${GREEN}Test Four Passed${NC}"
else
    echo -e "  ${RED}Failed${NC}"
fi

echo -e "\nTesting :: ps aux\n"
cat ./test-files/test_ps_aux.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_ps_aux.txt)
if ./shell < ./test-files/cmd.txt 2>/dev/null | grep -qF -- "${RES}"; then
    echo -e "  ${GREEN}Test Five Passed${NC}"
    SCORE=$((SCORE + 10))
else
    echo -e "  ${RED}Failed${NC}"
fi
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 3. Input/Output Redirection (15 pts)
# ============================================================
echo "[Test 3] input/output redirection"
echo -e "\nTesting :: ps aux > a; grep /init < a; grep /init < a > b\n"
cat ./test-files/test_input_output_redirection.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_input_output_redirection.txt)
rm -f a b
./shell < ./test-files/cmd.txt >temp 2>/dev/null
if grep -qF -- "${RES}" temp; then
    if [ -f a ] && [ -f b ] && grep -qF -- "${RES}" b; then
        echo -e "  ${GREEN}Test Six Passed${NC}"
        SCORE=$((SCORE + 15))
    else
        echo -e "  ${RED}Failed file creation${NC}"
    fi
else
    echo -e "  ${RED}Failed final output${NC}"
fi
rm temp
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 4. Single Pipe (8 pts)
# ============================================================
echo "[Test 4] single pipe"
echo -e "\nTesting :: ls -l | grep \"shell.cpp\"\n"
cat ./test-files/test_single_pipe.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_single_pipe.txt)
NOTRES=$(ls -l | grep "Tokenizer.cpp")
strace -e trace=execve -f -o out.trace ./shell < ./test-files/cmd.txt >temp 2>/dev/null
LS=$(which ls)
GREP=$(which grep)
if grep -q "execve(\"${LS}\"" out.trace && grep -q "execve(\"${GREP}\"" out.trace && grep -qF -- "${RES}" temp && ! grep -qFw -- "${NOTRES}" temp; then
    echo -e "  ${GREEN}Test Seven Passed${NC}"
    SCORE=$((SCORE + 8))
else
    echo -e "  ${RED}Failed${NC}"
fi
rm temp
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 5. Multiple Pipes (6 pts)
# ============================================================
echo "[Test 5] multiple pipes"
echo -e "\nTesting :: ps aux | awk ""'""/usr/{print \$1}""'"" | sort -r\n"
cat ./test-files/test_multiple_pipes_A.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_multiple_pipes_A.txt)
ARR=($RES)
echo "${RES}" >cnt.txt
CNT=$(grep -oF -- "${ARR[0]}" cnt.txt | wc -l)
strace -e trace=execve -f -o out.trace ./shell < ./test-files/cmd.txt >temp 2>/dev/null
PS=$(which ps)
AWK=$(which awk)
SORT=$(which sort)
if grep -q "execve(\"${PS}\"" out.trace && grep -q "execve(\"${AWK}\"" out.trace && grep -q "execve(\"${SORT}\"" out.trace && grep -qF -- "${RES}" temp && [ $(grep -oFw -- "${ARR[0]}" temp | wc -l) -le $((${CNT}+3)) ]; then
    echo -e "  ${GREEN}Test Eight Passed${NC}"
    SCORE=$((SCORE + 6))
else
    echo -e "  ${RED}Failed${NC}"
fi
rm cnt.txt temp
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 6. Multiple Pipes + I/O Redirection (15 pts)
# ============================================================
echo -e "\nTesting :: Multiple Pipes & Redirection\n"
cat ./test-files/test_multiple_pipes_redirection.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
RES=$(. ./test-files/test_multiple_pipes_redirection.txt)
echo "${RES}" >cnt.txt
CNT=$(grep -oF -- "${RES}" cnt.txt | wc -l)

COUNT=$(./shell < ./test-files/cmd.txt 2>/dev/null | grep -oF -- "${RES}" | wc -l)

if { [ $COUNT -eq $CNT ] || [ $COUNT -eq $((CNT - 1)) ] || [ $COUNT -eq $((CNT + 1)) ]; } && [ -f test.txt ] && [ -f output.txt ]; then
    echo -e "  ${GREEN}Test Nine Passed${NC}"
    SCORE=$((SCORE + 15))
else
    echo -e "  ${RED}Failed${NC}"
fi
rm -f cnt.txt test.txt output.txt
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 7. Background Processes (5 pts)
# ============================================================
echo "[Test 7] background processes"
START=$(date +%s)
./shell <<< "sleep 3 &; sleep 2; exit" >/dev/null 2>&1
END=$(date +%s)
if (( END - START < 3 )); then
    echo -e "${GREEN}background process did not block the shell${NC}"
    SCORE=$((SCORE + 5))
else
  echo -e "${RED}sleep command blocked instead of running in background${NC}"
fi
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 8. Directory Processing (6 pts)
# ============================================================
remake
echo -e "\nTesting :: cd ../../\n"
cat ./test-files/test_cd_A.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
DIR=$(. ./test-files/test_cd_A.txt)
./shell < ./test-files/cmd.txt >temp 2>/dev/null
if [ $(grep -oF -- "${DIR}" temp | wc -l) -ge 3 ] && [ $(grep -oF -- "${DIR}/" temp | wc -l) -le 1 ]; then
    echo -e "  ${GREEN}Test Ten Passed${NC}"
else
    echo -e "  ${RED}Failed${NC}"
fi
rm temp

remake
echo -e "\nTesting :: cd -\n"
cat ./test-files/test_cd_B.txt ./test-files/test_exit.txt > ./test-files/cmd.txt
TEMPDIR=$(cd /home && pwd)
DIR=$(. ./test-files/test_cd_B.txt | head -n 1)
./shell < ./test-files/cmd.txt >temp 2>/dev/null
if [ $(grep -oF -- "${DIR}" temp | wc -l) -ge 3 ] && ( [ $(grep -oF -- "${TEMPDIR}" temp | wc -l) -le 1 ] || ( grep -qF -- "${TEMPDIR}/" <<< "$DIR" && [ $(grep -oF -- "${TEMPDIR}" temp | wc -l) -gt $(grep -oF -- "${DIR}" temp | wc -l) ] ) ); then
    echo -e "  ${GREEN}Test Eleven Passed${NC}"
    SCORE=$((SCORE + 6))
else
    echo -e "  ${RED}Failed${NC}"
fi
rm temp
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# ============================================================
# 9. User Prompt (5 pts)
# ============================================================
echo "[Test 9] user prompt"
PROMPT_OUT=$(echo "exit" | ./shell 2>/dev/null)

EXPECTED_PATTERN="$(whoami).*$(date +%b)"
ALT_PATTERN="$(date +%b).*$(whoami)"

if echo "$PROMPT_OUT" | grep -Eq "$EXPECTED_PATTERN" || \
   echo "$PROMPT_OUT" | grep -Eq "$ALT_PATTERN"; then
   echo -e "  ${GREEN}prompt displayed username and date${NC}"
   SCORE=$((SCORE + 5))
else
   echo -e "  ${RED}prompt missing username/date or not printed correctly${NC}"
fi
echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"

# Cleanup
# rm -f input.txt result.txt
# echo -e "Current SCORE: ${SCORE}/${MAX_SCORE}\n"


exit 0
