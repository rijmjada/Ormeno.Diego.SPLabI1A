#ifndef PAISES_H_INCLUDED
#define PAISES_H_INCLUDED


typedef struct{

    int id;
    char nombre[30];
    int vac1Dosis;
    int vac2Dosis;
    int sinVacunar;

}ePais;

//-----------------------------------------------------[ Crear/Eliminar ]-----------------------------------------------------------//

ePais* newPais();
ePais* newPaisParam(char* strId, char* strNombre, char* strVac1Dosis, char* strVac2Dosis, char* strSinVacunar);
int destroyPais(ePais* pais);

//----------------------------------------------------------[ Setters ]-------------------------------------------------------------//

int pais_setId(ePais* pais, int id);
int pais_setNombre(ePais* pais, char* pNombre);
int pais_setPrimeraDosis(ePais* pais, int vac1Dosis);
int pais_setSegundaDosis(ePais* pais, int vac2Dosis);
int pais_setSinVacunar(ePais* pais, int sinVacunar);

//------------------------------------------------------------[ Getters ]------------------------------------------------------------//

int pais_getId(ePais* pais, int* pId);
int pais_getNombre(ePais* pais, char* pNombre);
int pais_getPrimeraDosis(ePais* pais, int* pVac1Dosis);
int pais_getSegundaDosis(ePais* pais, int* pVac2Dosis);
int pais_getSinVacunar(ePais* pais, int* pSinVacunar);

//-------------------------------------------------------------[ Print ]-----------------------------------------------------------------//

int menu();
int mostrarListaPaises(LinkedList* lista);
int mostrarUnPais(ePais* unPais);
int menuSort();
int menuTypeSort();

//---------------------------------------------------------[ Ordenamiento / Filtrado ]---------------------------------------------------------//


void* cargarRandom(void* pais);
int numeroRandom(int min,int max);
int filtrarPaisExitoso(void* pais);
int filtrarPaisAlHorno(void* pais);
int ordenarPorDosisTotales(void* a, void* b);
int ordenarPorDosisUno(void* a, void* b);
int ordenarPorDosisDos(void* a, void* b);
int ordenarSinVacuna(void* a, void* b);
int mostrarPaisMasCastigado(LinkedList* lista);

#endif // PAISES_H_INCLUDED
