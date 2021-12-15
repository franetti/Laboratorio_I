#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


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
    LinkedList* this= NULL;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if( this != NULL ){
        this->size=0; // limpio los campos del LL para que no tenga basura
        this->pFirstNode = NULL; // limpio los campos del LL para que no tenga basura
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this) // vendria a ser un getter del campo size de la LL
{
    int returnAux = -1;
    if( this != NULL){
        returnAux=this->size;
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
    Node* pNode = NULL;
    if( this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this) ){
            pNode = this->pFirstNode;
            while(nodeIndex>0 ){
                pNode=pNode->pNextNode;
                nodeIndex--;
            }
    }
    return pNode;
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
    Node* newNode = NULL;
    Node* previousNode = NULL;

    if( this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this) )
    { // <= ll_len porque puede agregarlo al ultimo indic e.
        newNode = (Node*) malloc(sizeof(Node));
        if(newNode != NULL){
            newNode->pElement = pElement;
            newNode->pNextNode=NULL;
            if(nodeIndex==0){
                newNode->pNextNode = this->pFirstNode;
                this->pFirstNode = newNode;
            }
            else{
                previousNode = getNode(this,nodeIndex-1);
                newNode->pNextNode=previousNode->pNextNode; // si era el ultimo nodo, va a apuntar a NULLL. Y esta bien.
                previousNode->pNextNode=newNode;
            }
            this->size++;
            returnAux=0;
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
    return addNode(this, ll_len(this), pElement); //---> devuelvo -1,0
}

/** \brief Retorna un puntero al elemento que se encuentra en el indice especificado.
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
    Node* aux = NULL;
    aux=getNode(this,index);
    if(aux!=NULL){
        returnAux=aux->pElement;
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
    int returnAux=-1;
    Node* aux = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        aux = getNode(this, index);
        if(aux!=NULL){
            aux->pElement = pElement; // el pElement al que apuntaba anteriormente podria setearlo con free(pElement).Pero teniendo e cuenta que otro puntero pude guardar la misma direccion lo dejo com esta.
            returnAux=0;
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
    Node* aux= NULL;

    if(this != NULL && index >=0 && index < ll_len(this)){
            if(index==0){
                this->pFirstNode = this->pFirstNode->pNextNode;
            }
            else{
                aux = getNode(this, index-1);
                if(aux!=NULL){
                    aux->pNextNode=aux->pNextNode->pNextNode;
                }
            }
            this->size--;
            returnAux=0;
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
    if(this!=NULL){
        while(ll_len(this)){
            ll_remove(this,0);
        }
        returnAux=0;
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
    returnAux = ll_clear(this);
    if(!returnAux){
        free(this);
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
    int returnAux=-1;

    if(this!=NULL){
        int tam=ll_len(this);
        for(int i=0;i<tam;i++){
            if(pElement==ll_get(this,i)){
                returnAux=i;
                break;
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
    if(this!=NULL){
        returnAux=0;
        if(ll_len(this) == 0){
            returnAux=1;
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
    return addNode(this, index, pElement);
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
    returnAux= ll_get(this,index);
    ll_remove(this,index);

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
    if(this!=NULL){
        returnAux=0;
        if(ll_indexOf(this,pElement) >= 0){
            returnAux=1;
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

    if(this!=NULL && this2 !=NULL){
        returnAux=1;
        int tam = ll_len(this2);
        for(int i=0; i<tam ; i++)
        {
            if(!ll_contains(this, ll_get(this2,i))){
                returnAux=0;
                break;
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

    if(this != NULL && from >= 0 && to <=ll_len(this) && to > from){
        cloneArray = ll_newLinkedList();
        if(cloneArray != NULL){
            for(int i=from ; i< to ; i++){
                ll_add(cloneArray,ll_get(this,i));
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
    return ll_subList(this,0,ll_len(this));
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;
    int tam;
    void* aux;

    if( this!=NULL && pFunc !=NULL && order <=1 && order >= 0 ){
        tam = ll_len(this);
        for(int i =0; i<tam - 1 ; i++){
            for(int j=i+1 ; j<tam ; j++){
                if((pFunc(ll_get(this,i),ll_get(this,j)) > 0 && order) ||
                   (pFunc(ll_get(this,i),ll_get(this,j)) <0 && !order)){
                    aux = ll_get(this,i);
                    ll_set(this,i,ll_get(this,j));
                    ll_set(this,j, aux);

                }
            }
        }
        returnAux=0;
    }
    return returnAux;

}

LinkedList* ll_filter(LinkedList* this, int(*pFunc)(void*))
{
    LinkedList* filterList=NULL;
    void* elemento=NULL;
    int tam;

    if(this != NULL && pFunc !=NULL)
    {
        filterList = ll_newLinkedList();
        if(filterList!=NULL){
            tam=ll_len(this);
            for(int i=0; i<tam ;i++){
                elemento=ll_get(this,i);
                if(pFunc(elemento)){
                    ll_add(filterList,elemento);
                }
            }
        }
    }

    return filterList;
}

LinkedList* ll_map (LinkedList* this, void*(*pFunc) (void*)){

    LinkedList* mapList = NULL;
    void* elemento=NULL;
    int tam;

    if(this != NULL && pFunc !=NULL)
    {
        mapList = ll_newLinkedList();
        if(mapList!=NULL){
            tam=ll_len(this);
            for(int i=0; i<tam ;i++){
                elemento=ll_get(this,i);
                if(elemento!=NULL){
                    ll_add(mapList, pFunc(elemento));
                }
            }
        }
    }

    return mapList;
}

int ll_count(LinkedList* this, int (*fn)(void* element)){

    int acc=0;
    int tam;
    void* element = NULL;

    if(this!=NULL && fn !=NULL)
    {
        tam=ll_len(this);
        if(tam>0)
        {
            for(int i=0; i<tam ;i++){
                element=ll_get(this,i);
                if(element!=NULL){
                    acc+= fn(element);
                }
            }
        }
    }

    return acc;
}
