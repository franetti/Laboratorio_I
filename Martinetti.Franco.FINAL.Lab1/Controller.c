#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "LinkedList.h"
#include "Controller.h"
#include "parser.h"
#include "logs.h"
#include "utnInputs.h"

int controller_showMenu(void)
{
	fflush(stdin);
	int opcion;
	printf("\nBienvenido. Por favor seleccione una opcion:\n");
	printf("--------------------------------------------\n");
	printf( "1. Leer Log.\n"
		    "2. Procesar Informacion.\n"
		    "3. Mostrar Estadisticas\n"
		    "4. Imprimir logs\n"
			"5. Salir\n");
	scanf("%d", &opcion);
    return opcion;
}

int controller_loadFromText( LinkedList* pLista)
{
	int status = 0;
	char path[30];
	char confirma;
	int validacion;

	system("cls");

    do{
        validacion = utn_getPath(path, 30,"Ingrese nombre y extension del archivo a cargar: \n", "Ruta invalida. Vuelva a ingresar\n", 30, 1 );
    }while(!validacion);

	if(pLista!=NULL && path!=NULL)
	{
		FILE* file = fopen(path, "r");
		if(file!=NULL)
		{
			if(ll_len(pLista)>0)
			{
				fflush(stdin);
				printf("CUIDADO!. Se sobreescribiran los logs  ya cargadas actualmente\n");
				do{
                    validacion = utn_getConfirmacion(&confirma, "Desea continuar ? (S/N) \n", "Error. ingrese una opcion valida\n", 'n', 's', 1);
				}while(!validacion);

				if(confirma =='S')
				{
					if(!ll_clear(pLista))
					{
						if(parser_FromText(file, pLista)==1)
						{
							printf("Se cargo el archivo %s con exito!\n", path);
							status = 1;
						}
					}
					else{
                        printf("Error al reemplazar los valores en la lista\n");
					}
				}
				else
				{
					printf("Carga cancelada por el usuario\n");
				}
			}
			else
			{
				if(parser_FromText(file, pLista))
				{
					printf("Se cargo el archivo %s con exito!\n", path);
					status = 1;
				}
			}
		}
		else
		{
			printf("ERROR. El archivo %s no existe \n", path);
		}
		fclose(file);
	}

	return status;
}

int controller_list(LinkedList* pLista){

    int status=0;

    if(pLista!=NULL)
    {
        if(log_listlogs(pLista)){
            status=1;
        }
        else{
            printf("Error al intentar listar lso datos\n");
        }
    }
    return status;
}

int controller_filter(LinkedList* pLista){

    int status=0;
    LinkedList* aux;

    if(pLista!=NULL ){
        if( ll_len(pLista)>0){
            system("cls");
            printf("                                                           *** Lista de logs ***                                               \n");
            printf("-------------------------------------------------------------------------------------------------------------------------------\n");
            printf(" Date          Time            Service name                                                    Mensaje                              Gravedad    \n");
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            aux =  ll_filter(pLista, log_filterWarnings);
            if(aux!=NULL){
                if(controller_saveAsText(aux,"warnings.txt")){
                    printf("Se genero un archivo con los warnings \n");
                    status=1;
                }
            }
            aux=NULL;

            aux = ll_filter(pLista, log_filterErrors);
            if(aux!=NULL){
                if(controller_saveAsText(aux,"errors.txt")){
                    printf("Se genero un archivo con los errors \n");
                    status=1;
                }
            }
            aux=NULL;
        }
        else{
            printf("Error.La lista esta vacia.\n");
        }

    }


    return status;
}


int controller_stats(LinkedList* lista)
{
    int status=0;

    if(lista!=NULL)
    {
        if(log_showStats(lista))
        {
            printf("Se calcularon las estadisticas exitosamente\n");
        }
        else{
            printf("Error al calcular las estadisticas\n");
        }
    }
    return status;
}


int controller_saveAsText( LinkedList* lista, char* path)
{
	int status=0;
	int escrito;
    char confirma;
    int flag=0;
	int validacion;

	FILE* file = NULL;
    eLog* auxLog=NULL;

     /*
    do{
        validacion = utn_getPath(path, 30,"Ingrese nombre y extension del archivo donde se guardarn los datos: \n", "Ruta invalida. Vuelva a ingresar\n", 30, 1 );
    }while(!validacion);*/

    if( lista!=NULL && path!=NULL)
	{
		file = fopen(path,"r");
        if(file!=NULL)
		{
            fflush(stdin);
            printf("CUIDADO!. Se sobreescribira el archivo %s\n", path);
            do{
                validacion = utn_getConfirmacion(&confirma, "Desea continuar ? (S/N) \n", "Error. ingrese una opcion valida\n", 'n', 's', 1);
            }while(!validacion);
            fclose(file);

            if(confirma=='S')
            {
                file = fopen(path,"w");
                if(file!=NULL)
                {
                    for(int i=0;i < ll_len(lista);i++)
                    {
                        auxLog = (eLog*) ll_get(lista, i);
                        if(auxLog!=NULL)
                        {
                            escrito = fprintf(file, "%s;%s;%s;%d;%s\n", auxLog->date, auxLog->time, auxLog->serviceName, auxLog->gravedad, auxLog->msg);
                            if(escrito<5)
                            {
                                printf("Error al intentar escribir en el archivo");
                                flag=1;
                                break;
                            }
                        }

                    }
                    status=1;
                    auxLog=NULL;
                }
                else
                {
                    printf("No se pudo sobreescribir el archivo mapeado.csv");
                    flag=1;
                }
                fclose(file);
            }
            else
            {
                printf("Exportacion cncelada por el usuario\n");
                flag=1;
            }
		}
		else
		{
            fclose(file);
            file = fopen(path,"w");
            if(file!=NULL)
            {
                for(int i=0;i < ll_len(lista);i++)
                {
                    auxLog = (eLog*) ll_get(lista, i);
                    if(auxLog!=NULL)
                    {
                        escrito = fprintf(file, "%s;%s;%s;%s;%d\n", auxLog->date, auxLog->time, auxLog->serviceName, auxLog->msg, auxLog->gravedad);
                        if(escrito<5)
                        {
                            printf("Error al intentar escribir en el archivo %s\n", path);
                            flag=1;
                            break;
                        }
                    }

                }
                status=1;
                auxLog=NULL;
            }
            else
            {
                printf("No se pudo crear el archivo mapeado.csv");
                flag=1;
            }
            fclose(file);
		}

	}

	if(!flag){
        printf("\nSe exporto el archivo con exito!\n");
	}

    return status;
}


