#!/usr/bin/env bash
# ============================================================
# setup.sh — Environment setup for PA2 (Aggie Shell)
# ============================================================

apt-get update -y
apt-get install -y jq g++ make strace gawk grep coreutils valgrind
echo "Environment setup complete."
