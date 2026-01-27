#!/bin/bash

SIZES=(1M 2M 5M 10M 20M 50M 100M 200M 500M 1G 2G 5G 10G)

#echo "Size | Time (s)"
printf "%-10s | %-10s\n" "Size" "Time (s)"
printf "%-10s-+-%-10s\n" "----------" "----------" 

for SIZE in "${SIZES[@]}"; do	
	FILE="BIMDC/test_${SIZE}.bin"
	truncate -s $SIZE "$FILE"
	
	/usr/bin/time -f "%e" -o time.log ./client -f "test_${SIZE}.bin" > /dev/null 2>&1
	RUNTIME=$(cat time.log)
	#echo "$SIZE | $RUNTIME"
	printf "%-10s | %-10s\n" "$SIZE" "$RUNTIME"
	
	if ! diff -q "$FILE" "received/test_${SIZE}.bin" > /dev/null; then
		echo "Error: mismatch detected in test for $SIZE"
	fi
	
	rm -f "received/test_${SIZE}.bin"
done

rm -f time.log
	
