#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "Genericas.h"
#include "LinkedList.h"
#include "Paises.h"
#include "parser.h"


/*
        1. Cargar datos desde consola        (data.csv)
        2. Imprimir lista                    (listar)
        3. Generar estadisticas              (random)
        4. Filtrar por paises exitosos       (ll_filter)
        5. Filtrar por paises en el horno    (ll_filter)
        6. Ordenar por nivel de vacunacion   (ll_sort)
        7. Mostrar mas castigados            (listar)
        8. Salir
*/


int main()
{
    LinkedList* lista = ll_newLinkedList(); //Lista paises Gral

    LinkedList* listaResultado = NULL;
    LinkedList* listaExitosos = NULL;
    LinkedList* listaAlHorno = NULL;


    srand(time(NULL));   //random

    int flag = 0;       // flag archivo data.csv
    int flag2 = 0;      // flag Estadistica generada
    char buffer = 'n';   //entrada usuario


    do
    {
        switch( menu())
        {
            system("cls");

        case 1:

            if(!loadFromtText(lista,&flag))
            {
                printf("\nError al cargar los datos!\n");
            }
            else
            {
                printf("\nDatos cargados. Ya puede imprimirlos.\n");
            }

            break;

        case 2:

            if(flag)
            {
                mostrarListaPaises(lista);
            }
            else
            {
                printf("\nPrimero debe cargar la lista!\n");
            }

            break;


        case 3:

            if(flag)
            {
                listaResultado = ll_map(lista,cargarRandom);
                system("pause");
                mostrarListaPaises(listaResultado);
                system("pause");
                flag2 = 1;
            }
            else
            {
                printf("\nPrimero debe cargar la lista![opcion 1]\n");
            }

            break;


        case 4:

            if(flag2)
            {
                // LLamo a ll_filter le paso mi lista original y la condicion de filtro y ll_filter me retorna la nueva lista que la asigno a 'listaExitosos'
                listaExitosos = ll_filter(lista, filtrarPaisExitoso);

                if(listaExitosos != NULL)
                {
                    // Si pudo generar la nueva lista la guardo en un nuevo archivo
                    saveAsText("PaisesExitosos.csv", listaExitosos);
                    printf("\n Se genero la lista 'PaisesExitosos.csv'!\n");
                }
                else
                {
                    printf("\n No se puedo generar la lista 'Lista Paises Exitosos'!\n");
                }
            }
            else
            {
                printf("\nPrimero debe generar una estadistica [opcion 3]!\n");
            }

            break;


        case 5:

            if(flag2)
            {
                // LLamo a ll_filter le paso mi lista original y la condicion de filtro y ll_filter me retorna la nueva lista que la asigno a 'listaAlHorno'
                listaAlHorno = ll_filter(lista, filtrarPaisAlHorno);

                if(listaAlHorno != NULL)
                {
                    // Si pudo generar la nueva lista la guardo en un nuevo archivo
                    saveAsText("PaisesAlHorno.csv", listaAlHorno);
                    printf("\n Se genero la lista 'PaisesAlHorno.csv'!\n");
                }
                else
                {
                    printf("\n No se puedo generar la lista 'PaisesAlHorno.csv'!.\n");
                }
            }
            else
            {
                printf("\nPrimero debe generar una estadistica [opcion 3]!\n");
            }

            break;

        case 6:
            if(flag2)
            {
                switch(menuSort())
                {
                    case 1:
                    ll_sort(lista,ordenarPorDosisTotales,1);
                    printf("\nLista Ordenada!. Puede imprimirla!.\n");
                    break;

                    case 2:
                    ll_sort(lista,ordenarPorDosisUno,1);
                    printf("\nLista Ordenada!. Puede imprimirla!.\n");
                    break;

                    case 3:
                    ll_sort(lista,ordenarPorDosisDos,1);
                    printf("\nLista Ordenada!. Puede imprimirla!.\n");
                    break;

                    case 4:
                    ll_sort(lista,ordenarSinVacuna,1);
                    printf("\nLista Ordenada!. Puede imprimirla!.\n");
                    break;

                }
            }
            else
            {
                printf("\nPrimero debe generar una estadistica [opcion 3]!\n");
            }

            break;

        case 7:
            if(flag2)
            {
                mostrarPaisMasCastigado(lista);
                system("pause");
                mostrarPaisMasCastigado(lista);
            }
            else
            {
                printf("\nPrimero debe generar una estadistica [opcion 3]!\n");
            }
            break;

        case 8:

            printf("\nConfirma Salida? [s/n]:\n");
            fflush(stdin);
            scanf("%c",&buffer);

            break;

        }
        printf("\n\n");
        system("pause");
    }
    while( buffer == 'n' );


    return 0;
}
