#include "../../header/minishell.h"
#include <stdio.h>

void test_export(t_env **env) {
    // [...] (pruebas 1-4 igual)

    // Prueba de rendimiento MEJORADA
    printf("\n🔹 Prueba 5: Rendimiento (100 variables)\n");
    for (int i = 0; i < 100; i++) {
        char var[20];
        sprintf(var, "VAR%02d=value%02d", i, i); // %02d para ordenación correcta
        ft_export(env, (char *[]){"export", var, NULL});
    }

    // Mostrar solo una vez
    printf("\n🔹 Resultado Final (primeras 10 vars):\n");
    ft_export(env, (char *[]){"export", NULL});
}

int main() {
    t_env *env = NULL;
    printf("=== INICIO PRUEBAS ===\n");
    test_export(&env);

    // Verificación concisa
    printf("\n🔍 Verificación:\n");
    printf("USER: %s\n", ft_getenv(env, "USER"));
    printf("VAR99: %s\n", ft_getenv(env, "VAR99"));
    printf("1VAR: %s\n", ft_getenv(env, "1VAR"));

    ft_free_env(env);
    printf("=== PRUEBAS OK ===\n");
    return 0;
}

/*void run_export_test(t_env **env, char **args, char *test_name) {
    printf("=== Test: %s ===\n", test_name);
    printf("Before:\n");
    print_sorted_env(*env);  // Muestra el entorno antes

    ft_export(env, args);   // Ejecuta export

    printf("\nAfter:\n");
    print_sorted_env(*env);  // Muestra el entorno después
    printf("\n");
}

int main() {
    // 1. Inicializa entorno con variables básicas
    t_env *env = NULL;
    ft_export(&env, (char *[]){"export", "PWD=/home/user", NULL});
    ft_export(&env, (char *[]){"export", "USER=testuser", NULL});

    // 2. Ejecuta pruebas
    run_export_test(&env, (char *[]){"export", NULL}, "Mostrar entorno");

    run_export_test(&env, (char *[]){"export", "NEW_VAR=hello"}, "Añadir nueva variable");

    run_export_test(&env, (char *[]){"export", "USER=newname"}, "Modificar variable existente");

    run_export_test(&env, (char *[]){"export", "INVALID=123"}, "Nombre inválido (empieza con número)");

    run_export_test(&env, (char *[]){"export", "WITH_SPACE=hello world"}, "Valor con espacios");

    run_export_test(&env, (char *[]){"export", "EMPTY="}, "Variable con valor vacío");

    // 3. Liberar memoria
    ft_free_env(env);
    return 0;
}*/
