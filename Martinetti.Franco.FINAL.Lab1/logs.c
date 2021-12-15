#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "logs.h"
#include "utnInputs.h"

eLog* log_new()
{
    eLog* log = (eLog*) malloc(sizeof(eLog));
    if( log != NULL){
        strcpy(log->date, " ");
        strcpy(log->time, " ");
        strcpy(log->serviceName, " ");
        log->gravedad=0;
        strcpy(log->msg, " ");
    }
    return log;
}

eLog* log_newParametros(char *pDate,char* pTime,char* pServicename, int gravedad , char* pMsg)
{
	eLog* log = log_new();
    if( log != NULL){
        if( !( log_setDate(log,pDate) &&
        	   log_setTime(log,pTime) &&
               log_setServiceName(log,pServicename) &&
			   log_setGravedad(log, gravedad) &&
               log_setMsg(log, pMsg)))
        {
            printf("Los parametros de la nueva estructura son invalidos son invalidos\n");
            free(log);
            log = NULL;
        }
    }
    return log;
}

int log_destroylog(eLog* plog)
{
    int status = 0;
    if(plog != NULL){
        free(plog);
        status=1;
    }
    return status;
}

int log_setDate(eLog* this,char* pDate)
{
    int status= 0 ;
    if( this != NULL && pDate!= NULL && strlen(pDate)>=1 && strlen(pDate)<11){
        strcpy(this->date, pDate);
        status=1;
    }
    return status;
}


int log_getDate(eLog* log, char* pDate)
{
    int status = 0;
    if( log!= NULL && pDate !=NULL){
        strcpy(pDate, log->date);
        status=1;
    }
    else{
    	printf("Error al recuperar el date\n");
    }
    return status;
}


int log_setTime(eLog* this,char* pTime)
{
    int status= 0 ;
    if( this != NULL && pTime!= NULL && strlen(pTime)>=1 && strlen(pTime)<6){
        strcpy(this->time, pTime);
        status=1;
    }
    return status;
}


int log_getTime(eLog* log, char* pTime){
    int status = 0;
    if( log!= NULL && pTime !=NULL){
        strcpy(pTime, log->time);
        status=1;
    }
    else{
    	printf("Error al recuperar el time\n");
    }
    return status;
}


int log_setServiceName(eLog* this,char* pServicename)
{
    int status= 0 ;
    if( this != NULL && pServicename!= NULL && strlen(pServicename)>=1 && strlen(pServicename)<65){
        strcpy(this->serviceName, pServicename);
        status=1;
    }
    return status;
}


int log_getServiceName(eLog* log, char* pServicename){
    int status = 0;
    if( log!= NULL && pServicename !=NULL){
        strcpy(pServicename, log->serviceName);
        status=1;
    }
    else{
    	printf("Error al recuperar el domicilio \n");
    }
    return status;
}

int log_setGravedad(eLog* this,int gravedad)
{
    int status= 0 ;
    if( this != NULL && gravedad > 0){
    	this->gravedad=gravedad;
        status=1;
    }
    return status;
}

int log_getGravedad(eLog* log, int* pGravedad){
    int status = 0;
    if( log!= NULL && pGravedad !=NULL){
        *(pGravedad) = log->gravedad;
        status=1;
    }
    else{
    	printf("Error al recuperar el rubro\n");
    }
    return status;
}

int log_setMsg(eLog* this,char* pMsg)
{
    int status= 0 ;
    if( this != NULL && pMsg!= NULL && strlen(pMsg)>=1 && strlen(pMsg)<65){
        strcpy(this->msg, pMsg);
        status=1;
    }
    return status;
}


int log_getMsg(eLog* log, char* pMsg){
    int status = 0;
    if( log!= NULL && pMsg !=NULL){
        strcpy(pMsg, log->msg);
        status=1;
    }
    else{
    	printf("Error al recuperar el domicilio \n");
    }
    return status;
}


int log_listlogs(LinkedList* lista)
{
    int status = 1;
    eLog* auxlog=NULL;
    if ( lista != NULL )
    {
        system("cls");
        printf("                                                           *** Lista de logs ***                                               \n");
        printf("-------------------------------------------------------------------------------------------------------------------------------\n");
        printf(" Date          Time            Service name                                                    Gravedad      Mensaje    \n");
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");

        if(ll_len(lista)>0){
            for (int i = 0; i < ll_len(lista); i++){
                auxlog=(eLog*)ll_get(lista,i);
                if(auxlog==NULL)
                {
                    printf("NULL\n");
                    status=0;
                }
                else
                {
                    log_showlog(auxlog);
                }

            }
            auxlog=NULL;
        }
        else{
            printf("Error. La lista esta vacia\n");
        }

    }
    return status;
}

void log_showlog(eLog* log)
{
	char auxDate[11];
	char auxTime[6];
	char auxService[65];
	int auxGravedad;
	char auxMsg[65];

	if(log==NULL){
		printf("No se pudo mostrar la pelicula\n");
	}
	else
	{
		if( (log_getDate(log, auxDate) && log_getTime(log, auxTime) && log_getServiceName(log, auxService) && log_getGravedad(log, &auxGravedad) && log_getMsg(log, auxMsg)) )
		{
            printf(" %-11s     %-6s     %-64s       %d    %-64s  \n",  auxDate, auxTime, auxService, auxGravedad, auxMsg );
		}
		else
		{
			printf("No se pudo recuperar los datos del eempleado para mostrar \n");
		}
	}
}

int log_filterWarnings(void* element)
{
    int status=0;

    if(element!=NULL){
        eLog* aux = (eLog*) element;

        if(aux->gravedad == 3){
            status=1;
        }

        if( aux->gravedad > 3 && aux->gravedad <=7){
            printf(" %-11s     %-6s     %-64s     %-64s   %d      \n",  aux->date, aux->time, aux->serviceName, aux->msg, aux->gravedad );
        }

    }
    return status;
}

int log_filterErrors(void* element)
{
    int status=0;

    if(element!=NULL){
        eLog* aux = (eLog*) element;
        if(aux->gravedad > 7){
            status=1;
        }
    }
    return status;
}

int log_showStats(LinkedList* lista)
{
    int status=0;
    int stats[4]={0,0,0,0};
    eLog* aux;

    if(lista!=NULL){
        if(ll_len(lista)>0)
        {
            for(int i=0; i<ll_len(lista);i++){
                aux = ll_get(lista, i);
                if(aux->gravedad < 3){
                    stats[0]++;
                }
                if(aux->gravedad == 3){
                    stats[1]++;
                }
                if(aux->gravedad > 3 && aux->gravedad <= 7 ){
                    stats[2]++;
                }
                if(aux->gravedad > 7){
                    stats[3]++;
                }
            }

            printf("Cantidad de fallos gravedad < 3: %d\n", stats[0]);
            printf("Cantidad de fallos gravedad == 3: %d\n", stats[1]);
            printf("Cantidad de fallos gravedad > 3 && gravedad <= 7: %d\n", stats[2]);
            printf("Cantidad de fallos gravedad >7: %d\n", stats[3]);
            status=1;
        }
        else{
            printf("la lista esta vacia. No se puede calcular las estadisticas. \n");
        }

    }

    return status;

}
