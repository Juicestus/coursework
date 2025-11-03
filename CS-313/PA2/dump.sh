#!/usr/bin/env bash
set -euo pipefail

# Dump each file in the current directory (top-level) and every file under test-files/
# Format:
# ---------- {relative file path} ----------
# {file contents}

files=()

# top-level files in current directory
while IFS= read -r -d '' f; do
    files+=("$f")
done < <(find . -maxdepth 1 -type f -print0)

# recursively include files from test-files if it exists
if [ -d "test-files" ]; then
    while IFS= read -r -d '' f; do
        files+=("$f")
    done < <(find "test-files" -type f -print0)
fi

for f in "${files[@]}"; do
    rel="${f#./}"
    printf '%s\n' "---------- $rel ----------"
    cat -- "$f" || true
    printf '\n'
done