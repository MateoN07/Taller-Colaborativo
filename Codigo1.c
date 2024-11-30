#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 5
#define NOMBRE_MAXIMO 30


char nombres[MAX_PRODUCTOS][NOMBRE_MAXIMO];
int tiempo_por_unidad[MAX_PRODUCTOS];
int recursos_por_unidad[MAX_PRODUCTOS];
int demanda[MAX_PRODUCTOS];
int cantidad_productos = 0;

void mostrarProductos() {
    printf("\nLista de productos:\n");
    for (int i = 0; i < cantidad_productos; i++) {
        printf("%d. Nombre: %s, Tiempo/Unidad: %d, Recursos/Unidad: %d, Demanda: %d\n",
               i + 1, nombres[i], tiempo_por_unidad[i], recursos_por_unidad[i], demanda[i]);
    }
}

void agregarProducto() {
    if (cantidad_productos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos.\n");
        return;
    }
    printf("Ingrese el nombre del producto: ");
    scanf(" %[^\n]", nombres[cantidad_productos]);
    printf("Ingrese el tiempo de fabricación por unidad: ");
    scanf("%d", &tiempo_por_unidad[cantidad_productos]);
    printf("Ingrese los recursos necesarios por unidad: ");
    scanf("%d", &recursos_por_unidad[cantidad_productos]);
    printf("Ingrese la cantidad demandada: ");
    scanf("%d", &demanda[cantidad_productos]);
    cantidad_productos++;
}

void editarProducto() {
    char nombre[NOMBRE_MAXIMO];
    printf("Ingrese el nombre del producto que desea editar: ");
    scanf(" %[^\n]", nombre);
    for (int i = 0; i < cantidad_productos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            printf("Editar datos del producto '%s':\n", nombre);
            printf("Nuevo nombre (dejar en blanco para no cambiar): ");
            char nuevoNombre[NOMBRE_MAXIMO];
            scanf(" %[^\n]", nuevoNombre);
            if (strlen(nuevoNombre) > 0) {
                strcpy(nombres[i], nuevoNombre);
            }
            printf("Nuevo tiempo de fabricación por unidad: ");
            scanf("%d", &tiempo_por_unidad[i]);
            printf("Nuevos recursos necesarios por unidad: ");
            scanf("%d", &recursos_por_unidad[i]);
            printf("Nueva cantidad demandada: ");
            scanf("%d", &demanda[i]);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    char nombre[NOMBRE_MAXIMO];
    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf(" %[^\n]", nombre);
    for (int i = 0; i < cantidad_productos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            for (int j = i; j < cantidad_productos - 1; j++) {
                strcpy(nombres[j], nombres[j + 1]);
                tiempo_por_unidad[j] = tiempo_por_unidad[j + 1];
                recursos_por_unidad[j] = recursos_por_unidad[j + 1];
                demanda[j] = demanda[j + 1];
            }
            cantidad_productos--;
            printf("Producto eliminado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void calcularProduccion(int tiempo_disponible, int recursos_disponibles) {
    int tiempo_total = 0, recursos_totales = 0;
    for (int i = 0; i < cantidad_productos; i++) {
        tiempo_total += tiempo_por_unidad[i] * demanda[i];
        recursos_totales += recursos_por_unidad[i] * demanda[i];
    }
    printf("\nTiempo total de fabricación: %d\n", tiempo_total);
    printf("Recursos totales necesarios: %d\n", recursos_totales);
    if (tiempo_total <= tiempo_disponible && recursos_totales <= recursos_disponibles) {
        printf("Es posible cumplir con la demanda.\n");
    } else {
        printf("No es posible cumplir con la demanda.\n");
    }
}

int main() {
    int tiempo_disponible, recursos_disponibles;
    int opcion;

    printf("Ingrese el tiempo de producción disponible: ");
    scanf("%d", &tiempo_disponible);
    printf("Ingrese los recursos disponibles: ");
    scanf("%d", &recursos_disponibles);

    do {
        printf("\nMenú:\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Calcular producción\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                mostrarProductos();
                break;
            case 5:
                calcularProduccion(tiempo_disponible, recursos_disponibles);
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 6);

    return 0;
}