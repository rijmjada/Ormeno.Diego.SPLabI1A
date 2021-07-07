#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Paises.h"
#include "parser.h"

#define ERROR -1
#define ALLOK 1

int loadFromtText(LinkedList* lista, int* flag)
{
    int retorno = 0;
    char buffer[20];

    if( buffer!=NULL && lista != NULL && (*flag == 0))
    {
        system("cls");
        printf("Ingrese path del archivo [ej: 'vacunas.csv']: \n");
        scanf("%s", buffer);

        FILE* bufferFile = fopen(buffer, "r");

        if( bufferFile != NULL )
        {
            if( parser_FromTxt(bufferFile, lista) )
            {
                retorno=1;
                *flag=1;
            }
        }

        fclose(bufferFile);
    }

    return retorno;
}


int parser_FromTxt(FILE* pFile, LinkedList* lista){
    int retorno=0;
    char buffer[5][128];

    if( pFile != NULL && lista != NULL )
    {
        ePais* bufferPais = NULL;//

//Escaneo
        fscanf(pFile, "%[^,], %[^,], %[^,], %[^,], %[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

        do
        {
            if( fscanf(pFile, "%[^,], %[^,], %[^,], %[^,], %[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]) == 5 )
            {
//Asigno
                bufferPais = newPaisParam(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

                if(bufferPais != NULL)
                {
                    ll_add(lista, bufferPais);
                    retorno=1;
                }
                else
                {
                    destroyPais(bufferPais);
                }
            }
            else
            {
                printf("Hubo un problema al leer los datos desde el archivo\n");
            }

        }
        while(!feof(pFile));
    }
    return retorno;
}


int saveAsText(char* path, LinkedList* lista){
    int id, dosis1, dosis2, sinVacunar, len, retorno = 0;
    char nombrePais[24];

    ePais* bufferPais = NULL;

    if( path != NULL && lista != NULL)
    {

        len = ll_len(lista); // Leo el tamaño de la lista y lo guardo en len

        FILE* bufferF = fopen(path, "w"); // Abro archivo

        if( bufferF != NULL )
        {
            fprintf(bufferF, "Id, Pais, Primera Dosis, Segunda Dosis, Sin Vacunar\n");

            for(int i=0; i<len; i++)
            {
                bufferPais = (ePais*) ll_get(lista, i); // tomo el elemento en cada 'posicion'

                if( bufferPais != NULL)
                {
                    if( (pais_getId(bufferPais, &id) &&
                            pais_getNombre(bufferPais, nombrePais) &&
                            pais_getPrimeraDosis(bufferPais, &dosis1) &&
                            pais_getSegundaDosis(bufferPais, &dosis2) &&
                            pais_getSinVacunar(bufferPais, &sinVacunar) ) )
                    {

                        if(fprintf(bufferF, "%d, %s, %d, %d, %d\n", id, nombrePais, dosis1, dosis2, sinVacunar) < 5 )
                        {
                            printf("\nError al salvar datos\n");
                            destroyPais(bufferPais);
                            break;
                        }
                        else
                        {
                            bufferPais = NULL;
                            retorno = 1;
                        }
                    }
                }
            }
            fclose(bufferF);
        }
        else
        {
            printf("No se pudo abrir el archivo '%s'\n", path);
        }
    }

    return retorno;
}

