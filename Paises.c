#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


#include "Genericas.h"
#include "LinkedList.h"
#include "LinkedList.h"
#include "parser.h"
#include "Paises.h"



//-------------------------------------------------[ Crear/Eliminar ]-------------------------------------------------//

ePais* newPais()
{
    ePais* newPais= (ePais*) malloc(sizeof(ePais));
    if(newPais!=NULL)
    {
        pais_setId(newPais,0);
        pais_setNombre(newPais," ");
        pais_setPrimeraDosis(newPais,0);
        pais_setSegundaDosis(newPais,0);
        pais_setSinVacunar(newPais,0);

    }
    return newPais;
}

ePais* newPaisParam(char* strId, char* strNombre, char* strDosis1, char* strDosis2, char* strSinVacunar)
{
    ePais* auxPais = newPais();
    if(auxPais!=NULL)
    {
        if(!(pais_setId(auxPais, atoi(strId)) &&
                pais_setNombre(auxPais, strNombre) &&
                pais_setPrimeraDosis(auxPais, atoi(strDosis1)) &&
                pais_setSegundaDosis(auxPais, atoi(strDosis2)) &&
                pais_setSinVacunar(auxPais, atoi(strSinVacunar)) ))

        {
            destroyPais(auxPais);
        }
    }

    return auxPais;
}

int destroyPais(ePais* pais)
{
    int retorno = 0;
    if( pais != NULL )
    {
        free(pais);

        retorno = 1;
    }
    return retorno;
}



//-----------------------------------------------[ Setters ]-----------------------------------------------//


int pais_setId(ePais* pais, int idRef)
{
    int retorno=0;

    if( pais != NULL && idRef > 0 )
    {
        pais->id = idRef;
        retorno=1;
    }

    return retorno;
}

int pais_setNombre(ePais* pais, char* pNombre)
{
    int retorno=0;

    if( pais!=NULL && pNombre!=NULL && (strlen(pNombre) > 3 || strlen(pNombre) < 30) )
    {
        strcpy(pais->nombre, pNombre);
        retorno=1;
    }

    return retorno;
}

int pais_setPrimeraDosis(ePais* pais, int dosis1Ref)
{
    int retorno=0;

    if( pais != NULL && dosis1Ref >=0 )
    {
        pais->vac1Dosis = dosis1Ref;
        retorno=1;
    }

    return retorno;
}

int pais_setSegundaDosis(ePais* pais, int dosis2Ref)
{
    int retorno=0;

    if( pais != NULL && dosis2Ref >= 0)
    {
        pais->vac2Dosis = dosis2Ref;
        retorno=1;
    }

    return retorno;
}

int pais_setSinVacunar(ePais* pais, int sinVacunarRef)
{
    int retorno=0;

    if(pais!=NULL && sinVacunarRef >= 0)
    {
        pais->sinVacunar = sinVacunarRef;
        retorno=1;
    }

    return retorno;
}


//-----------------------------------------------[ Getters ]-----------------------------------------------//


int pais_getId(ePais* pais, int* pId)
{
    int retorno = 0;

    if( pais != NULL && pId != NULL)
    {
        *pId = pais->id;
        retorno=1;
    }

    return retorno;
}

int pais_getNombre(ePais* pais, char* pNombre)
{
    int retorno = 0;

    if( pais != NULL && pNombre != NULL )
    {
        strcpy(pNombre, pais->nombre);
        retorno = 1;
    }

    return retorno;
}

int pais_getPrimeraDosis(ePais* pais, int* pVac1Dosis)
{
    int retorno = 0;

    if( pais != NULL && pVac1Dosis != NULL)
    {
        *pVac1Dosis = pais->vac1Dosis;
        retorno = 1;
    }

    return retorno;
}

int pais_getSegundaDosis(ePais* pais, int* pVac2Dosis)
{
    int retorno=0;

    if( pais != NULL && pVac2Dosis != NULL)
    {
        *pVac2Dosis = pais->vac2Dosis;
        retorno=1;
    }

    return retorno;
}

int pais_getSinVacunar(ePais* pais, int* pSinVacunar)
{
    int retorno=0;

    if( pais != NULL && pSinVacunar != NULL)
    {
        *pSinVacunar = pais->sinVacunar;
        retorno=1;
    }

    return retorno;
}


//-----------------------------------------------[ Imprimir por Pantalla ]-----------------------------------------------//

int menu()
{
    int opcion;

    system("cls");

    printf("Menu\n");
    printf("---------------------------\n");
    printf("1. Cargar datos desde archivo\n");
    printf("2. Imprimir lista\n");
    printf("3. Generar estadisticas\n");
    printf("4. Filtrar por paises exitosos\n");
    printf("5. Filtrar por paises en el horno\n");
    printf("6. Ordenar por nivel de vacunacion\n");
    printf("7. Mostrar mas castigados\n");
    printf("8. Salir\n\n\n");

    getInt(&opcion, "Ingrese opcion: \n", "\nError, Ingrese opcion: \n", 1, 8, 3);

    return opcion;
}

int mostrarListaPaises(LinkedList* lista)
{
    int retorno=0;
    int len = ll_len(lista);

    if(lista!=NULL)
    {
        printf("*************************************************************\n");
        printf(" Id                Nombre    \tDosis-1   Dosis-2  S/Vacuna  \n");
        printf("*************************************************************\n\n");;



        for(int i=0; i<len; i++)
        {
            mostrarUnPais( (ePais*) ll_get(lista,i));
            retorno=1;
        }
    }
    return retorno;
}

int mostrarUnPais(ePais* unPais)
{
    int retorno=0;
    int id;
    char nombre[30];
    int dosis1;
    int dosis2;
    int sinVacunar;

    if(unPais!=NULL)
    {
        if( pais_getId(unPais, &id) &&
                pais_getNombre(unPais, nombre) &&
                pais_getPrimeraDosis(unPais, &dosis1) &&
                pais_getSegundaDosis(unPais, &dosis2) &&
                pais_getSinVacunar(unPais, &sinVacunar))
        {
            printf("%3d  %20s      %4d      %4d       %4d  \n", id, nombre, dosis1, dosis2, sinVacunar);
            retorno=1;
        }
    }
    return retorno;
}

int menuSort()
{
    int buffer;

    system("cls");
    printf("\n**Menur Orden**");
    printf("\n1) Dosis Totales.");
    printf("\n2) Primera Dosis.");
    printf("\n3) Segunda Dosis.");
    printf("\n4) Sin Vacunar Dosis.");
    getInt(&buffer,"","\nDato invalido!\n",1,4,5);

    return buffer;
}

int menuTypeSort()
{
    int buffer;

    system("cls");
    printf("\n**Menur Orden**");
    printf("\n1) Ascendente.");
    printf("\n2) Descendente.");
    getInt(&buffer,"","\nDato invalido!\n",1,2,5);

    return buffer;
}


//-----------------------------------------------[ Ordenamiento / Filtrado ]-----------------------------------------------//


void* cargarRandom(void* pais)
{
    int dosis1, dosis2, sinVacuna;

    if( pais != NULL )
    {
//Genero valores random
        dosis1 = numeroRandom(1,60);
        dosis2 = numeroRandom(1,40);
        sinVacuna = 100 - (dosis1 + dosis2);

// Asigno los valores Al pais con los setters
        if(!(pais_setPrimeraDosis(pais,dosis1)
                && pais_setSegundaDosis(pais, dosis2)
                && pais_setSinVacunar(pais, sinVacuna)))
        {
            printf("\n***Error al cargar datos!.***\n");
        }
    }
    return pais;
}



int numeroRandom(int min,int max)
{
    int numero;
    numero = rand() % (max - min + 1) + min;// Devuelve siempre los mismos numeros aleatorios

    return numero;
}


int filtrarPaisExitoso(void* pais)
{
    int retorno = 0;
    int dosis1;
    int dosis2;
    int sinVacunar;
    int porcentaje;

    if( pais != NULL )
    {
        if(  pais_getPrimeraDosis(pais,&dosis1)
                &&pais_getSegundaDosis(pais, &dosis2)
                && pais_getSinVacunar(pais,&sinVacunar))
        {
            porcentaje = (sinVacunar*0.30);
            if( dosis1+dosis2 > porcentaje )
            {
                retorno = 1;
            }
        }
    }
    return retorno;
}

int filtrarPaisAlHorno(void* pais)
{
    int retorno = 0;
    int sinVacunar;
    int dosis1;
    int dosis2;

    if( pais != NULL )
    {
// Tomo dosis 1, dosis 2 y cantidad sin vacunar
        if( (pais_getPrimeraDosis(pais, &dosis1) && pais_getSegundaDosis(pais, &dosis2) && pais_getSinVacunar(pais, &sinVacunar)) )
        {
// Si la cantidad de gente sin vacunar es Mayor a los vacunados
            if( sinVacunar > (dosis1+dosis2) )
            {
                retorno = 1;
            }
        }
    }

    return retorno;
}

int ordenarPorDosisUno(void* a, void* b)
{
    int retorno;

    if(a != NULL && b != NULL)
    {
        ePais* NodoAux1 = (ePais*) a;
        ePais* NodoAux2 = (ePais*) b;

        if( NodoAux1->vac1Dosis > NodoAux2->vac1Dosis )
        {
            retorno = -1;
        }
        else if( NodoAux1->vac1Dosis  < NodoAux2->vac1Dosis )
        {
            retorno = 1;
        }
        else // Si son iguales
        {
            retorno = 0;
        }
    }

    return retorno;
}


int ordenarPorDosisDos(void* a, void* b)
{
    int retorno;

    if(a != NULL && b != NULL)
    {
        ePais* NodoAux1 = (ePais*) a;
        ePais* NodoAux2 = (ePais*) b;

        if( NodoAux1->vac2Dosis > NodoAux2->vac2Dosis )
        {
            retorno = -1;
        }
        else if( NodoAux1->vac2Dosis < NodoAux2->vac2Dosis )
        {
            retorno = 1;
        }
        else // Si son iguales
        {
            retorno = 0;
        }
    }

    return retorno;
}


int ordenarSinVacuna(void* a, void* b)
{
    int retorno;

    if(a != NULL && b != NULL)
    {
        ePais* NodoAux1 = (ePais*) a;
        ePais* NodoAux2 = (ePais*) b;

        if( NodoAux1->sinVacunar > NodoAux2->sinVacunar )
        {
            retorno = -1;
        }
        else if( NodoAux1->sinVacunar < NodoAux2->sinVacunar )
        {
            retorno = 1;
        }
        else // Si son iguales
        {
            retorno = 0;
        }
    }

    return retorno;
}

int ordenarPorDosisTotales(void* a, void* b)
{

    int retorno;
    int pais1;
    int pais2;

    if(a != NULL && b != NULL)
    {
        ePais* NodoAux1 = (ePais*) a;
        ePais* NodoAux2 = (ePais*) b;

        pais1 = NodoAux1->vac1Dosis + NodoAux1->vac2Dosis;
        pais2 = NodoAux2->vac1Dosis + NodoAux2->vac2Dosis;

        if( pais1 > pais2 )
        {
            retorno = -1;
        }
        else if( pais1 < pais2 )
        {
            retorno = 1;
        }
        else // Si son iguales
        {
            retorno = 0;
        }
    }

    return retorno;
}

int mostrarPaisMasCastigado(LinkedList* lista)
{
    int retorno = 0;
    int len = ll_len(lista);
    int sinVacunar;
    int mayor;

    if(lista != NULL)
    {
        ePais* auxPais = NULL;

        for(int i=0; i<len; i++)
        {
            auxPais = ll_get(lista, i);

            pais_getSinVacunar(auxPais, &sinVacunar);

            if( i == 0 || sinVacunar > mayor )
            {
                mayor = sinVacunar;
                retorno = 1;
            }
        }


        system("cls");
        printf("\nPais Mas Castigado\n");
        printf("\nId            Pais     Dosis1 Dosis2  S/Vacuna\n");

        for(int i=0; i<len; i++)
        {
            auxPais= (ePais*) ll_get(lista, i);
            pais_getSinVacunar(auxPais, &sinVacunar);

            if( sinVacunar == mayor )
            {
                mostrarUnPais(auxPais);
            }
        }
    }
    return retorno;
}

