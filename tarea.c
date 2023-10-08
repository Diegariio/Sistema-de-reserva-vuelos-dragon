//DIEGO ANTONIO VARGAS GOMEZ 21012009-2
//MILLARAY THIARE ATENEA ZAMBRANO SANTANA 21.196.585-1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
// declaracion estructuras
typedef struct reserva_vuelo
{
    int numero_reserva;
    char nombre_aventurero[20];
    char destino[50];

} reserva;

typedef struct arbol
{
    reserva x;
    struct arbol *izq;
    struct arbol *der;

} arbol;

// declaracion de funciones
arbol *crear_arbol(int numero_reserva, char nombre_aventurero[], char destino[]);
arbol *insertar(arbol *raiz, int numero_reserva, char nombre_aventurero[], char destino[]);
void inorden(arbol *raiz);
arbol *buscar_reserva(arbol *raiz, int numero_reserva);
void mostrar_por_destino(arbol *raiz, char destino[]);
arbol *encontrar_sucesor_inorden(arbol *raiz);
arbol *eliminar(arbol *raiz, int numero_reserva);
void bienvenida();
int menu();
void realizar_reserva();
void cancelar_reserva();
void buscar_por_reserva();
void buscar_por_destino();
void reservas_ordenadas();
void salir();
void treefree(arbol *rarbol);

int main()
{
    // declaracion de variables
    arbol *raiz = NULL;

    int numero_reserva;
    char nombre_aventurero[20];
    int opcion;
    int i;
    char destinoelegido[50];
    int numero_reserva_que_busca;
    int opcion_d = 0;
    arbol *se_encontro;
    char destino[8][50];
    strncpy(destino[0], "Monte del Fuego", sizeof(destino[0]) - 1);
    destino[0][sizeof(destino[0]) - 1] = '\0';
    strncpy(destino[1], "Valle de las Nubes", sizeof(destino[1]) - 1);
    destino[1][sizeof(destino[1]) - 1] = '\0';
    strncpy(destino[2], "Bosque de Escamas", sizeof(destino[2]) - 1);
    destino[2][sizeof(destino[2]) - 1] = '\0';
    strncpy(destino[3], "Desierto de Dragones", sizeof(destino[3]) - 1);
    destino[3][sizeof(destino[3]) - 1] = '\0';
    strncpy(destino[4], "Ciudad de Dracoria", sizeof(destino[4]) - 1);
    destino[4][sizeof(destino[4]) - 1] = '\0';
    strncpy(destino[5], "Islas del Aliento", sizeof(destino[5]) - 1);
    destino[5][sizeof(destino[5]) - 1] = '\0';
    strncpy(destino[6], "Cueva de las Sombras", sizeof(destino[6]) - 1);
    destino[6][sizeof(destino[6]) - 1] = '\0';
    // muestreo de bienvenida
    bienvenida();
    printf("\n\n");
    system("pause");
    do
    {
        // muestreo de menu
        system("cls");
        opcion = menu();
        switch (opcion)
        {
        case 1: // esta opcion permite al aventurero reservar un vuelo con un destino especifico
        {

            system("cls");

            do
            {
                printf("Ingrese datos del aventurero: \n");
                printf("\nNumero de reserva:\n");
                scanf("%d", &numero_reserva);
                se_encontro = buscar_reserva(raiz, numero_reserva);
                if (se_encontro != NULL)
                {
                    system("cls");
                    printf("Numero de reserva ya existente, escoga otro\n\n");
                }
            } while (se_encontro != NULL);

            fflush(stdin);
            printf("Nombre del Aventurero:\n");
            fgets(nombre_aventurero, sizeof(nombre_aventurero), stdin);
            nombre_aventurero[strcspn(nombre_aventurero, "\n")] = '\0';
            do
            {
                printf("\nDestinos Disponibles:\n\n "); // aqui estan los destinos disponibles

                for (i = 0; i < 7; i++)
                {
                    printf("%d. %s\n", i + 1, destino[i]);
                }
                // el usuario elije un destino
                printf("\nIngrese destino segun su numero: ");
                scanf("%d", &opcion_d);
                if (opcion_d < 1 || opcion_d > 7)
                {
                    system("cls");
                    printf("Opcion no valida, reintente\n\n");
                }
            } while (opcion_d < 1 || opcion_d > 7);

            strcpy(destinoelegido, destino[opcion_d - 1]);
            printf("\nEl destino elegido es: %s\n", destinoelegido);
            raiz = insertar(raiz, numero_reserva, nombre_aventurero, destinoelegido);
            printf("Su reserva ha sido un exito!!\n");

            switch (opcion_d)
            {
            case 1:
            {
                printf("Su vuelo a monte del fuego sale hoy a las 12:00HRS.\n\n");
            }
            break;
            case 2:
            {
                printf("Su vuelo a valle de las nubes sale hoy a las 15:00HRS\n\n");
            }
            break;
            case 3:
            {
                printf("Su vuelo a bosque de escamas sale hoy a las 21:00HRS\n\n");
            }
            break;
            case 4:
            {
                printf("Su vuelo a desierto de dragones sale hoy a las 16:00HRS\n\n");
            }
            break;
            case 5:
            {
                printf("Su vuelo a ciudad de dracoria sale hoy a las 17:00HRS\n\n");
            }
            break;
            case 6:
            {
                printf("Su vuelo a islas del aliento sale hoy a las 21:30HRS\n\n");
            }
            break;
            case 7:
            {
                printf("Su vuelo a cueva de las sombras sale hoy a las 13:00HRS\n\n");
            }
            break;
            }
            system("pause");
        }
        break;
        case 2: // cancelar reserva
        {
            system("cls");
            printf("Proporciona el numero de reserva del vuelo a eliminar: ");
            scanf("%d", &numero_reserva_que_busca);

            raiz = eliminar(raiz, numero_reserva_que_busca);

            printf("Reserva eliminada con exito.\n\n");
            system("pause");
        }
        break;
        case 3: // mostrar una reserva por numero de reserva
        {
            system("cls");
            printf("Proporciona porfavor el numero de reserva del vuelo: ");
            scanf("%d", &numero_reserva_que_busca);
            se_encontro = buscar_reserva(raiz, numero_reserva_que_busca);
            if (se_encontro != NULL)
            {

                printf("\nAventurero!! Tu reserva ha sido encontrada:\n\n");
                printf("Nombre aventurero:%s, Reino de destino:%s\n", se_encontro->x.nombre_aventurero, se_encontro->x.destino);
            }
            else
            {
                printf("Querido aventurero, su reserva %d no ha sido encontrada.\n\n", numero_reserva_que_busca);
            }
            printf("\n");
            system("pause");
        }
        break;

        case 4: // mostrar reservas por destino
        {
            system("cls");
            do
            {
                printf("Destinos Disponibles:\n\n "); // aqui estan los destinos disponibles
                for (i = 0; i < 7; i++)
                {
                    printf("%d. %s\n", i + 1, destino[i]);
                }
                // el usuario elije un destino

                printf("\n \n Elige destino a consultar reservas:\n\n");

                scanf("%d", &opcion_d);
                if (opcion_d < 1 || opcion_d > 7)
                {
                    system("cls");
                    printf("Opcion invalida, reintente\n\n");
                }
            } while (opcion_d < 1 || opcion_d > 7);

            strncpy(destinoelegido, destino[opcion_d - 1], sizeof(destino[0]) - 1);
            destinoelegido[sizeof(destino[0]) - 1] = '\0';

            printf("Reservas con destino a %s:\n\n", destinoelegido);
            mostrar_por_destino(raiz, destinoelegido);
            printf("\n");
            system("pause");
        }
        break;
        case 5: // mostrar reservas ordenadas
        {
            system("cls");
            printf("Estas son las reservas ordenadas:\n\n");
            inorden(raiz);
            printf("\n");
            system("pause");
        }
        break;
        case 6: // salir
        {
            treefree(raiz);
            opcion = 6;
        }
        break;
        }

    } while (opcion != 6);

    return 0;
}

int menu()
{
    int opcion = 1;
    int operacion = 0;
    char auxiliar;
    realizar_reserva();
    do
    {
        auxiliar = _getch();
        // casos de movimiento A D
        if ((int)auxiliar == 65 || (int)auxiliar == 97)
        {
            opcion--;
        }
        if ((int)auxiliar == 68 || (int)auxiliar == 100)
        {
            opcion++;
        }
        // caso ENTER
        if ((int)auxiliar == 13)
        {
            operacion = opcion;
        }
        // casos fuera de limite
        if (opcion == 0)
        {
            opcion = 6;
        }
        if (opcion == 7)
        {
            opcion = 1;
        }
        // muestreo de menu
        switch (opcion)
        {
        case 1:
        {
            realizar_reserva();
        }

        break;
        case 2:
        {
            cancelar_reserva();
        }

        break;
        case 3:
        {
            buscar_por_reserva();
        }

        break;
        case 4:
        {
            buscar_por_destino();
        }

        break;
        case 5:
        {
            reservas_ordenadas();
        }

        break;
        case 6:
        {
            salir();
        }
        break;
        }
    } while ((int)auxiliar != 13);
    return operacion;
}

void bienvenida()
{
    system("cls");
    FILE *menu;
    char caracter;

    menu = fopen("bienvenida.txt", "r");

    if (menu == NULL)
    {
        printf(" \nerror de apertura del archivo.txt\n");
    }
    else
    {
        // EOF end of file evalua el final del archivo
        while ((caracter = fgetc(menu)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    printf("\n\n");
    fclose(menu);
}

void realizar_reserva()
{
    system("cls");
    FILE *menu;
    char caracter;

    menu = fopen("realizar_reserva.txt", "r");

    if (menu == NULL)
    {
        printf(" \nerror de apertura del archivo.txt\n");
    }
    else
    {
        // EOF end of file evalua el final del archivo
        while ((caracter = fgetc(menu)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    printf("\n\n");
    fclose(menu);
}

void cancelar_reserva()
{
    system("cls");
    FILE *menu;
    char caracter;

    menu = fopen("cancelar_reserva.txt", "r");

    if (menu == NULL)
    {
        printf(" \nerror de apertura del archivo.txt\n");
    }
    else
    {
        // EOF end of file evalua el final del archivo
        while ((caracter = fgetc(menu)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    printf("\n\n");
    fclose(menu);
}

void buscar_por_reserva()
{
    system("cls");
    FILE *menu;
    char caracter;

    menu = fopen("buscar_por_reserva.txt", "r");

    if (menu == NULL)
    {
        printf(" \nerror de apertura del archivo.txt\n");
    }
    else
    {
        // EOF end of file evalua el final del archivo
        while ((caracter = fgetc(menu)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    printf("\n\n");
    fclose(menu);
}

void buscar_por_destino()
{
    system("cls");
    FILE *menu;
    char caracter;

    menu = fopen("buscar_por_destino.txt", "r");

    if (menu == NULL)
    {
        printf(" \nerror de apertura del archivo.txt\n");
    }
    else
    {
        // EOF end of file evalua el final del archivo
        while ((caracter = fgetc(menu)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    printf("\n\n");
    fclose(menu);
}

void reservas_ordenadas()
{
    system("cls");
    FILE *menu;
    char caracter;

    menu = fopen("reservas_ordenadas.txt", "r");

    if (menu == NULL)
    {
        printf(" \nerror de apertura del archivo.txt\n");
    }
    else
    {
        // EOF end of file evalua el final del archivo
        while ((caracter = fgetc(menu)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    printf("\n\n");
    fclose(menu);
}

void salir()
{
    system("cls");
    FILE *menu;
    char caracter;

    menu = fopen("salir.txt", "r");

    if (menu == NULL)
    {
        printf(" \nerror de apertura del archivo.txt\n");
    }
    else
    {
        // EOF end of file evalua el final del archivo
        while ((caracter = fgetc(menu)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    printf("\n\n");
    fclose(menu);
}
// crea un nodo en la posicion correspondiente en el arbol
arbol *crear_arbol(int numero_reserva, char nombre_aventurero[], char destino[])
{
    arbol *nuevo = (arbol *)malloc(sizeof(arbol));
    nuevo->x.numero_reserva = numero_reserva;
    strcpy(nuevo->x.nombre_aventurero, nombre_aventurero);
    strcpy(nuevo->x.destino, destino);
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// función para insertar mas datos al arbol
// se insertaran los datos que estan en la estrucura del nodo
arbol *insertar(arbol *raiz, int numero_reserva, char nombre_aventurero[], char destino[])
{
    if (raiz == NULL)
    {
        return crear_arbol(numero_reserva, nombre_aventurero, destino);
    }
    if (numero_reserva < raiz->x.numero_reserva)
    {
        raiz->izq = insertar(raiz->izq, numero_reserva, nombre_aventurero, destino);
    }
    else if (numero_reserva > raiz->x.numero_reserva)
    {
        raiz->der = insertar(raiz->der, numero_reserva, nombre_aventurero, destino);
    }
    else
    {
        return raiz;
    }
}

void inorden(arbol *raiz)
{
    if (raiz != NULL)
    {
        inorden(raiz->izq);
        printf("Numero de reserva: %d, Nombre del aventurero: %s, Reino al que se dirige: %s \n", raiz->x.numero_reserva, raiz->x.nombre_aventurero, raiz->x.destino);
        inorden(raiz->der);
    }
}

// buscar reseva
// Si el numero de reserva buscado es menor que el numero de reserva en el nodo actual,
// se realiza la busqueda en el subarbol izquierdo, si no
//  e realiza la busqueda en el subarbol derecho
arbol *buscar_reserva(arbol *raiz, int numero_reserva)
{
    if (raiz == NULL || raiz->x.numero_reserva == numero_reserva)
    {

        return raiz;
    }
    if (numero_reserva < raiz->x.numero_reserva)
    {
        return buscar_reserva(raiz->izq, numero_reserva);
    }
    else
    {
        return buscar_reserva(raiz->der, numero_reserva);
    }
}

void mostrar_por_destino(arbol *raiz, char destino[])
{
    int bandera = 0;
    if (raiz != NULL)
    {
        mostrar_por_destino(raiz->izq, destino);
        if (strcmp(raiz->x.destino, destino) == 0)
        {
            printf("Numero de reserva: %d, Nombre del aventurero: %s, destino: %s\n", raiz->x.numero_reserva, raiz->x.nombre_aventurero, raiz->x.destino);
            bandera = 1;
        }
        mostrar_por_destino(raiz->der, destino);
    }
    if (bandera = 0)
    {
        printf("\n No se ha encontrado ninguna reserva con ese destino\n\n");
    }
}

arbol *encontrar_sucesor_inorden(arbol *raiz)
{
    arbol *actual = raiz;
    while (actual->izq != NULL)
    {
        actual = actual->izq;
    }
    return actual;
}

arbol *eliminar(arbol *raiz, int numero_reserva)
{
    if (raiz == NULL)
    {
        printf("La reserva buscada, no existe!");
        return raiz;
    }

    if (numero_reserva < raiz->x.numero_reserva)
    {
        raiz->izq = eliminar(raiz->izq, numero_reserva);
    }
    else if (numero_reserva > raiz->x.numero_reserva)
    {
        raiz->der = eliminar(raiz->der, numero_reserva);
    }
    else
    {
        if (raiz->izq == NULL) // no tiene hijos o solo uno
        {
            arbol *aux = raiz->der;
            free(raiz);
            return aux;
        }
        else if (raiz->der == NULL)
        {
            arbol *aux = raiz->izq;
            free(raiz);
            return aux;
        }

        arbol *sucesor = encontrar_sucesor_inorden(raiz->der);
        raiz->x = sucesor->x;
        raiz->der = eliminar(raiz->der, sucesor->x.numero_reserva);
    }
    return raiz;
}

void treefree(arbol *rarbol)
{
    if (rarbol != NULL)
    {
        treefree(rarbol->izq);
        treefree(rarbol->der);
        free(rarbol);
    }
}