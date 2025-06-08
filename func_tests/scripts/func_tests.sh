#!/bin/bash

echo -e "\n\e[34mtesting...\e[0m\n"

neg_fail=0
pos_fail=0
neg_counter=$(find ../data/ -name 'neg*in.txt' | wc -l)
pos_counter=$(find ../data/ -name 'pos*in.txt' | wc -l)

test=1
while [ $test -le "$pos_counter" ]; do
    if [ $test -le 9 ]; then
        pos_input="../data/pos_0${test}_in.txt"
        pos_output="../data/pos_0${test}_out.txt"
        pos_short="pos_0${test}_in.txt"
    else
        pos_input="../data/pos_${test}_in.txt"
        pos_output="../data/pos_0${test}_out.txt"
        pos_short="pos_{test}_in.txt"
    fi 
      
    if ./pos_case.sh $pos_input $pos_output; then
        test=$((test + 1))
        echo -e "POS TEST $pos_short: \e[32mCORRECT\e[0m"
    else
        pos_fail=$((pos_fail + 1))
        echo -e "POS TEST $pos_short: \e[31mFAIL\e[0m"
        test=$((test + 1))
    fi
done

echo -e "\e[34mPositive tests: correct $((pos_counter - pos_fail)) of $pos_counter\e[0m\n"

test=1
while [ $test -le "$neg_counter" ]; do
    if [ $test -le 9 ]; then
        neg_input="../data/neg_0${test}_in.txt"
        neg_short="neg_0${test}_in.txt"
    else
        neg_input="../data/neg_${test}_in.txt"
        neg_short="neg_${test}_in.txt"
    fi
    
    ./neg_case.sh $neg_input
    if [ $? -eq 0 ]; then
        test=$((test + 1))
        echo -e "NEG TEST $neg_short: \e[32mCORRECT\e[0m"
    else
        neg_fail=$((neg_fail + 1))
        echo -e "NEG TEST $neg_short: \e[31mFAIL\e[0m"
        test=$((test + 1))
    fi
done
        
echo -e "\e[34mNegative tests: correct $((neg_counter - neg_fail)) of $neg_counter\e[0m"

failed_tests=$((pos_fail + neg_fail))
if [ "$failed_tests" -gt 0 ]; then
    echo -e "\n\e[31mTesting failed\e[0m\n"
    exit "$failed_tests"
fi

echo -e "\n\e[32mTesting was successfully passed\e[0m\n"
exit 0
