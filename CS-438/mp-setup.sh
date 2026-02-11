#!/usr/bin/env bash
set -euo pipefail

# CSCE 438 MP1 setup for Ubuntu 24.04 (Noble Numbat)
# Installs build tools + protobuf + gRPC (C++) + grpc_cpp_plugin + Abseil + glog.

echo "=== MP1 dependency setup (Ubuntu 24.04) ==="

# Basic OS sanity check (non-fatal)
if [[ -f /etc/os-release ]]; then
  . /etc/os-release
  echo "Detected: ${PRETTY_NAME:-unknown}"
  if [[ "${ID:-}" != "ubuntu" ]]; then
    echo "WARNING: This script is intended for Ubuntu. Continuing anyway..."
  fi
  if [[ "${VERSION_CODENAME:-}" != "noble" ]]; then
    echo "WARNING: Expected Ubuntu 24.04 (Noble Numbat). Continuing anyway..."
  fi
fi

echo "[1/3] Updating apt index..."
sudo apt-get update -y

echo "[2/3] Installing packages..."
sudo apt-get install -y --no-install-recommends \
  make \
  cmake \
  build-essential \
  pkg-config \
  protobuf-compiler \
  libprotobuf-dev \
  libgrpc++-dev \
  protobuf-compiler-grpc 
  

# Optional: clean up downloaded package lists (keeps VM smaller)
sudo apt-get clean

sudo rm -rf glog
git clone https://github.com/google/glog.git
cd glog
cmake -S . -B build -G "Unix Makefiles"
cmake --build build
sudo cmake --build build --target install
cd ..
sudo rm -rf glog
sudo ln -s /usr/local/lib/libglog.so.3 /usr/lib/libglog.so.3

echo "[3/3] Verifying tools..."
fail=0
for cmd in g++ make pkg-config protoc grpc_cpp_plugin; do
  if command -v "$cmd" >/dev/null 2>&1; then
    echo "OK: $cmd -> $(command -v "$cmd")"
  else
    echo "MISSING: $cmd"
    fail=1
  fi
done

echo
echo "Versions:"
protoc --version || true
grpc_cpp_plugin --version 2>/dev/null || true
g++ --version | head -n 1 || true

if [[ "$fail" -ne 0 ]]; then
  echo
  echo "ERROR: Some required tools are missing."
  echo "Please check your network/apt sources and re-run this script."
  exit 1
fi

echo
echo "All dependencies installed."
echo "Next steps:"
echo "  cd mp1_skeleton"
echo "  make clean && make -j4"



