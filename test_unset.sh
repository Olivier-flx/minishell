#!/bin/bash

echo "=== TEST 1: Sin argumentos ==="
./test_unset
echo "Exit code: $?"

echo "=== TEST 2: Eliminar PATH ==="
export PATH_BACKUP=$PATH
./test_unset PATH
echo "Exit code: $?"
env | grep PATH

echo "=== TEST 3: Nombre inválido ==="
./test_unset "VAR*INVALIDA"
echo "Exit code: $?"