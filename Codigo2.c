#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 5
#define NOMBRE_MAXIMO 30


char nombres[MAX_PRODUCTOS][NOMBRE_MAXIMO];
int tiempo[MAX_PRODUCTOS], recursos[MAX_PRODUCTOS], demanda[MAX_PRODUCTOS];
int total_productos = 0;


void buscarProducto(const char *nombre, int *encontrado, int *indice) {
    *encontrado = 0; 
    for (int i = 0; i < total_productos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            *encontrado = 1;
            *indice = i;
            return; 
        }
    }
}


void agregarProducto() {
    if (total_productos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos.\n");
        return;
    }
    printf("Ingrese el nombre del producto: ");
    scanf(" %[^\n]", nombres[total_productos]);
    printf("Ingrese el tiempo por unidad: ");
    scanf("%d", &tiempo[total_productos]);
    printf("Ingrese los recursos por unidad: ");
    scanf("%d", &recursos[total_productos]);
    printf("Ingrese la cantidad demandada: ");
    scanf("%d", &demanda[total_productos]);
    total_productos++;
}


void editarProducto() {
    char nombre[NOMBRE_MAXIMO];
    int encontrado, indice;

    printf("Ingrese el nombre del producto a editar: ");
    scanf(" %[^\n]", nombre);
    buscarProducto(nombre, &encontrado, &indice);

    if (!encontrado) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Editar datos del producto '%s':\n", nombres[indice]);
    printf("Nuevo nombre (dejar en blanco para no cambiar): ");
    char nuevoNombre[NOMBRE_MAXIMO];
    scanf(" %[^\n]", nuevoNombre);
    if (strlen(nuevoNombre) > 0) {
        strcpy(nombres[indice], nuevoNombre);
    }
    printf("Nuevo tiempo por unidad: ");
    scanf("%d", &tiempo[indice]);
    printf("Nuevos recursos por unidad: ");
    scanf("%d", &recursos[indice]);
    printf("Nueva demanda: ");
    scanf("%d", &demanda[indice]);
}


void eliminarProducto() {
    char nombre[NOMBRE_MAXIMO];
    int encontrado, indice;

    printf("Ingrese el nombre del producto a eliminar: ");
    scanf(" %[^\n]", nombre);
    buscarProducto(nombre, &encontrado, &indice);

    if (!encontrado) {
        printf("Producto no encontrado.\n");
        return;
    }

   
    for (int i = indice; i < total_productos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        tiempo[i] = tiempo[i + 1];
        recursos[i] = recursos[i + 1];
        demanda[i] = demanda[i + 1];
    }
    total_productos--;
    printf("Producto eliminado.\n");
}


void mostrarProductos() {
    if (total_productos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("\nLista de productos:\n");
    for (int i = 0; i < total_productos; i++) {
        printf("%d. Nombre: %s, Tiempo/Unidad: %d, Recursos/Unidad: %d, Demanda: %d\n",
               i + 1, nombres[i], tiempo[i], recursos[i], demanda[i]);
    }
}


void calcularProduccion(int tiempo_disponible, int recursos_disponibles) {
    int tiempo_total = 0, recursos_totales = 0;
    for (int i = 0; i < total_productos; i++) {
        tiempo_total += tiempo[i] * demanda[i];
        recursos_totales += recursos[i] * demanda[i];
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
    int tiempo_disponible, recursos_disponibles, opcion;

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