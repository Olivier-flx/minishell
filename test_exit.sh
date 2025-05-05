#!/bin/bash

# Función para ejecutar una prueba
run_test() 
{
    echo -e "\n\033[1;36m$1\033[0m"
    ./test_exit $2
    echo "Exit code: $?"
}

# Caso 1: Sin argumentos
run_test "Caso 1: Sin argumentos" ""

# Caso 2: Número válido (42)
run_test "Caso 2: Número válido (42)" "42"

# Caso 3: Número negativo (-1)
run_test "Caso 3: Número negativo (-1)" "-1"

# Caso 4: Demasiados argumentos (1 2)
run_test "Caso 4: Demasiados argumentos (1 2)" "1 2"

# Caso 5: Argumento no numérico (abc)
run_test "Caso 5: Argumento no numérico (abc)" "abc"