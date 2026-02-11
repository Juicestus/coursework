#!/bin/bash

# Find and display contents of .h, .cc, .ini, and .proto files
find . -type f \( -name "*.h" -o -name "*.cc" -o -name "*.ini" -o -name "*.proto" \) | sort | while read file; do
    echo "-- $file --"
    cat "$file"
    echo ""
done > dump.txt