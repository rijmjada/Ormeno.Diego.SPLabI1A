#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Paises.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = (LinkedList*) malloc(sizeof(LinkedList)); // Pido espacion en memoria para mi estructura de tipo LinkedList y la guardo en el puntero "this"

    if(this != NULL)
    {
        this->pFirstNode = NULL;
        this->size = 0;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNodo = NULL;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        pNodo = this->pFirstNode;

        while(nodeIndex > 0)
        {
            pNodo = pNodo->pNextNode;
            nodeIndex--;
        }
    }
    return pNodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* nuevoNodo = NULL;
    Node* ptPrevNode = NULL;

    if( this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        nuevoNodo = (Node*)malloc(sizeof(Node));

        if(nuevoNodo != NULL)
        {
            nuevoNodo->pElement = pElement;
            nuevoNodo->pNextNode = getNode(this,nodeIndex);

            if(nodeIndex == 0)
            {
                this->pFirstNode = nuevoNodo;
            }
            else
            {
                // Lo mismo de abajo (getNode(this,nodeIndex-1))->pNextNode = nuevoNodo;
                ptPrevNode = getNode(this,nodeIndex-1);
                ptPrevNode->pNextNode = nuevoNodo;
            }

            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(!addNode(this,ll_len(this),pElement))
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Retorna un puntero al elemento que se encuentra en el índice especificado. Verificando que el
puntero this sea distinto de NULL y que index sea positivo e inferior al tamaño del array. Si la
verificación falla la función retorna (NULL) y si tiene éxito retorna el elemento.
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;

    if(this != NULL && index >=0 && index <ll_len(this))
    {
        returnAux = (getNode(this,index))->pElement;
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* aux;
    if(this != NULL && index >= 0 && index <ll_len(this))
    {
        aux = getNode(this,index);

        if(aux != NULL)
        {
            aux->pElement = pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* nod_Borrar = NULL;
    Node* nod_Anterior = NULL;

    if( this != NULL && index >=0 && index < ll_len(this))
    {
        nod_Borrar = getNode(this,index);

        if(index == 0)
        {
            this->pFirstNode = nod_Borrar->pNextNode;
        }
        else
        {
            nod_Anterior = getNode(this,index-1);
            nod_Anterior->pNextNode = nod_Borrar->pNextNode;
        }

        free(nod_Borrar);
        nod_Borrar = NULL;
        this-> size--;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            ll_remove(this,i);
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        ll_clear(this); // llamo a clear para previo a borrar mi LinkedList, eliminar sus Nodos
        free(this);     // libero el espacio en memoria dinamica q ocupaba this
        this = NULL;    // hago q el puntero "this" apunte a null
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* auxComparacion; //Nodo auxiliar

    if(this != NULL)
    {
        for(int i=0; i<ll_len(this); i++) // Recorro el linked list
        {
            auxComparacion = getNode(this,i); // Mientras recorro con el for voy copiando cada nodo en mi aux para lineas abajo hacer la comparacion

            if(auxComparacion->pElement == pElement) // Hago la comparacion entre mi aux y el elemento pasado por referencia
            {
                returnAux = i;  // Si hay coincidencia retorno el indice donde fue encontrado
                break;  // Rompo el ciclo de iteracion
            }
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    void* ret;

    if(this != NULL)
    {
        ret = this->pFirstNode; // Ret guarda el primero nodo O un NULL

        if(ret != NULL)
        {
            returnAux = 0;
        }
        else
        {
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this!=NULL && index>=0 && index<=len)
    {
        addNode(this,index,pElement);
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* auxStructNodo = NULL;

    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
        auxStructNodo = getNode(this,index);

        if(auxStructNodo != NULL)
        {
            returnAux = auxStructNodo->pElement;
            ll_remove(this,index);
        }
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(ll_indexOf(this,pElement) != -1)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    Node* auxiliar;

    if( this != NULL && this2 != NULL)
    {
        returnAux = 0; // Este return aca es por si me pasan una lista indice 0

        for(int i=0; i<ll_len(this2); i++) // Recorro la lista "this2"
        {
            auxiliar = getNode(this2,i); // En cada vuelta del for voy copiando/pisando los nodos en mi auxiliar para mas abajo comparar

            if(ll_contains(this,auxiliar->pElement) == 1) // Funcion que me retorna 1 si encuentra el elemento pasado como parametro en "this1"
            {
                returnAux = 1;
            }
            else
            {
                returnAux = 0;
                break; // Si entro al else ya NO estan todos los elementos por ende rompo el bucle para no pisar el dato en caso q vuelva encontrar una coincidencia
            }
        }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    int len = ll_len(this);
    Node* auxNode = NULL;
    int iClone = 0; // Indice de mi nueva lista
    void* pElement;

    if(this!=NULL && from >= 0 && from < len && to > from && to <= len)
    {
        cloneArray =  ll_newLinkedList(); // Creo la nueva lista y la guardo en el puntero
        if(cloneArray != NULL)
        {
            for(int i=0; i<len; i++) // Recorro this y si cumple con los parametro debajo detallados voy copiando los nodos y agregando en mi nueva lista
            {
                if( i >= from || i <= to )
                {
                    auxNode = getNode(this,i);
                    pElement = auxNode->pElement;
                    addNode(cloneArray,iClone,pElement);
                    iClone++; // Aumento en +1 el indice de la lista 'cloneArray'
                }
            }
        }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int len = ll_len(this);

    if( this != NULL)
    {
        cloneArray = ll_subList(this,len-len,len);
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int len = ll_len(this);
    void* pAux;

    if( this!=NULL && pFunc != NULL )
    {
        for(int i=0; i<len-1; i++)
        {
            for(int j=i+1; j<len; j++)
            {
                if((pFunc(ll_get(this,i), ll_get(this,j)) >0        && order == 1) ||
                        (pFunc(ll_get(this,i), ll_get(this,j)) <0   && order == 0))
                {
                    pAux = ll_get(this,i);
                    ll_set(this,i, ll_get(this,j));
                    ll_set(this,j,pAux);

                    returnAux = 0;
                }
            }
        }
    }

    return returnAux;
}


/** \brief Devuelve un nuevo LinkedList cargado con los elementos que pasan la funcion (filtro)
 * \param this LinkedList* puntero de lista a filtrar
 * \param pFunc (*pFunc) Puntero a la funcion filtra
 * \return int Retorna   NULL: si el puntero a la listas es NULL o Si el puntero a funcion es NULL
 *                     o retorna puntero a nueva LinkedList nuevo puntero a LinkedList
 */
LinkedList* ll_filter(LinkedList* this,int (*pFunc)(void*))
{
    LinkedList* listToFilter = NULL; // LinkedList Auxiliar
    int len = ll_len(this); // tamaño de la lista
    void* auxElement = NULL; //Puntero al elemento a comparar


    if( this != NULL && pFunc != NULL )
    {
// LLamo a ll_newLinkedList para crear la nueva lista y pasarle el puntero a 'listToFilter'
        listToFilter = ll_newLinkedList();

        if( listToFilter != NULL )// Si'listToFilter' es diferente de NULL
        {
            for(int i=0; i<len; i++)//Recorro la lista 'this'
            {
                auxElement = ll_get(this,i); // Copio cada elemento de la lista

                if( pFunc(auxElement) == 1 ) // LLamo a pFunc para comparar y filtrar los datos
                {
                    if( ll_add(listToFilter,auxElement) != 0 ) // ll_add Retorna 0 si logra completar su funcion, por eso lo niego
                    {
                        ll_deleteLinkedList(listToFilter); // Si fallo borro el linkedList
                        listToFilter = NULL;
                        break;
                    }
                }
            }
        }
    }

    return listToFilter;
}


LinkedList* ll_map(LinkedList* this, void*(*pFunc)(void* pElement))
{
    int len = ll_len(this);
    void* aux = NULL;

    if( this != NULL && pFunc != NULL )
    {
        for(int i=0; i<len; i++)
        {
            aux = ll_get(this, i);

            if( aux != NULL )
            {
                aux = pFunc(aux);
            }
            else
            {
                printf("Algo salio mal al asignar datos a los campos\n");
                system("pause");
                destroyPais(aux);
                break;
            }
        }
    }
    return this;
}
