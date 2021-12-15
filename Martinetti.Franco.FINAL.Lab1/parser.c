#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "logs.h"


/** \brief Parsea los datos los datos de la ruta indicada por el usuario(modo texto).
 *
 * \param pfile File*
 * \param pLista LinkedList*
 * \return int
 *
 */

int parser_FromText(FILE* pFile , LinkedList* pLista)
{
	int status=0;
	int leido;
	char buffer[5][200];
	eLog* aux = NULL;

	if(pFile!=NULL && pLista!=NULL)
	{
		do{
			leido = fscanf(pFile,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
			if(leido<5){
				break;
			}
			aux = log_newParametros(buffer[0],buffer[1],buffer[2],atoi(buffer[3]),buffer[4]);
			if(aux!=NULL){
				if(ll_add(pLista, aux)==-1)
				{
					printf("Error al leer alguno de los datos desde eel archivo.\n");
					status=-1;
					break;
				}
				aux=NULL;
                status=1;
			}
		}while(!feof(pFile));
	}
	else
	{
		printf("No se pudo parsear los datos\n");
	}

    return status;
}

