#!/usr/bin/env bash
# dump.sh - recursively print each regular file with a header
# Usage: ./dump.sh [dir]
# Default dir is current directory.

dir="${1:-.}"

# Find regular files and handle filenames with spaces/newlines
find "$dir" -type f -print0 | while IFS= read -r -d '' file; do
    printf '--------- %s -----------\n' "$file"
    if [ -r "$file" ]; then
        cat -- "$file"
    else
        printf '<<< cannot read file: permission denied >>>\n'
    fi
    printf '\n\n'
done