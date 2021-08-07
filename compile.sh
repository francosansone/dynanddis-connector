#!/bin/bash
set -e

POWER_DEVS_DIR=$HOME/powerdevs/atomics/tpfinal
MODELICA_DIR=/opt/modelica

cd "$( dirname "${BASH_SOURCE[0]}" )"

## creating directories
echo "[1/3] Creating directories"

mkdir -p $POWER_DEVS_DIR
sudo mkdir -p $MODELICA_DIR
sudo chown -R $USER:$USER $MODELICA_DIR

echo "[1/3] Done"

echo "[2/3] Compiling"

gcc -Wall -c OMEdit/flib.c -o $MODELICA_DIR/flib

echo "[2/3] Done"

echo "[3/3] Installing"

cp PowerDEVS/atomics/fromfile.* $POWER_DEVS_DIR

echo "[3/3] Done"

echo "Finished"
