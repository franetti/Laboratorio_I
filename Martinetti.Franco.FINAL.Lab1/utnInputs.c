#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

static int esNumerica ( char* cadena);
static int getInt ( int* pResultado);
static int esNumeroDecimal( char* cadena);
static int getFloat( float* pResultado);
static int getString( char* pResultado, int tam);
static int getStringAlnum( char* pResultado, int tam);
static int myGets(char* cadena, int longitud);
static int getStringPath( char* pResultado, int tam);

int utn_getNumero( int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int ret;
    int num;
    while (reintentos>0)
    {
        printf(mensaje);
        if (getInt(&num))
        {
            if (num<=maximo && num>=minimo)
            break ;
        }
        fflush(stdin);
        reintentos--;
        printf(mensajeError);
    }
    if (reintentos==0)
    {
        ret=0;
    }
    else
    {
        ret=1;
        *pResultado = num;
    }
    return ret;
}

static int getInt( int* pResultado)
{
    int ret=0;
    char buffer[64];
    if( myGets(buffer,64) )
    {
        if (esNumerica(buffer))
        {
            *pResultado = atoi(buffer);
            ret=1;
        }
    }
    return ret;
}

static int esNumerica( char* cadena)
{
    int i=0;
    int retorno = 1;
    if (cadena != NULL && strlen(cadena) > 0)
    {
        while (cadena[i] != '\0' )
        {
            if (cadena[i] < '0' || cadena[i] > '9' )
            {
                retorno = 0;
                break ;
            }
            i++;
        }
    }
    return retorno;
}

int utn_getNumeroConDecimales( float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
    int ret;
    float num;

    while (reintentos>0)
    {
        printf(mensaje);
        if (getFloat(&num))
        {
            if ( num>=minimo && num<=maximo )
            {
                break;
            }
        }
        fflush(stdin);
        reintentos--;
        printf(mensajeError);
    }

    if (reintentos==0)
    {
        ret=0;
    }
    else
    {
        ret=1;
        *pResultado = num;
    }

    return ret;
}

static int getFloat( float* pResultado)
{
    int ret=0;
    char buffer[64];
    if( myGets(buffer,64) )
    {
        if (esNumeroDecimal(buffer))
        {
            *pResultado = atof(buffer);
            ret=1;
        }
    }
    return ret;
}

static int esNumeroDecimal( char* cadena)
{
    int i=0;
    int contador=0;
    int retorno = 1;

    if (cadena != NULL && strlen(cadena) > 0)
    {
        while (cadena[i] != '\0' )
        {
            if(cadena[i] == '.' ){
                contador++;
            }
            if ( cadena[i] != '.' && ( cadena[i] < '0' || cadena[i] > '9' ) )
            {
                retorno = 0;
                break ;
            }
            i++;
        }

        if(contador > 1)
        {
            retorno=0;
        }
    }
    return retorno;
}

int utn_getChar( char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
    int ret=0;
    char buffer;
    if(pResultado!=NULL && mensaje != NULL && mensajeError != NULL && minimo<=maximo && reintentos >=0)
    {
        do{
            printf(mensaje);
            fflush(stdin);
            buffer = getch();
            if(buffer <= maximo && buffer>=minimo)
            {
                *pResultado = buffer;
                ret=1;
                break;
            }
            printf(mensajeError);
            reintentos--;
        }while(reintentos>=0);
    }
    return ret;
}

int utn_getTexto( char* pResultado, int tam, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int retorno;
    char buffer[tam];
    while (reintentos>0)
    {
        printf(mensaje);
        if (getString(buffer, tam))
        {
            if (strlen(buffer)>=minimo && strlen(buffer)<=maximo )
            {
                break ;
            }

        }
        fflush(stdin);
        reintentos--;
        printf(mensajeError);
    }

    if (reintentos==0)
    {
        retorno=0;
    }
    else
    {
        retorno=1;
        strcpy(pResultado, buffer);
    }

    return retorno;
}

static int getString( char* pResultado, int tam)
{
    int retorno=0;
    int i=0;
    int flag=0;
    char buffer[tam];
    if( myGets(buffer,tam) )
    {
        while(buffer[i]!='\0')
        {
            if( !isalpha(buffer[i]) )
            {
                flag=1;
                break;
            }
            i++;
        }
    }

    if(!flag)
    {
        strcpy(pResultado, buffer);
        retorno=1;
    }

    return retorno;
}

int utn_getAlfanumerico( char* pResultado, int tam, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int ret;
    char buffer[tam];
    while (reintentos>0)
    {
        printf(mensaje);
        if (getStringAlnum(buffer, tam))
        {
            if (strlen(buffer)>=minimo && strlen(buffer)<=maximo )
            break ;
        }
        fflush(stdin);
        reintentos--;
        printf(mensajeError);
    }
    if (reintentos==0)
    {
        ret=0;
    }
    else
    {
        ret=1;
        strcpy(pResultado, buffer);
    }
    return ret;
}

static int getStringAlnum( char* pResultado, int tam)
{
    int ret=0;
    int i=0;
    int flag=0;
    char buffer[tam];
    if( myGets(buffer,tam) )
    {
        while(buffer[i]!='\0')
        {
            if( !isalnum(buffer[i]) )
            {
                flag=1;
                break;
            }
            i++;
        }
    }

    if(!flag)
    {
        strcpy(pResultado, buffer);
        ret=1;
    }

    return ret;
}

static int myGets( char cadena[], int longitud)
{
    int retorno=0;
    fflush (stdin);
    if (cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
    {
        if (cadena[ strlen(cadena)-1] == '\n' )
        {
            cadena[ strlen(cadena)-1] = '\0' ;
        }
        retorno=1;
    }
    return retorno;
}


int utn_getPath( char* pResultado, int tam, char* mensaje, char* mensajeError, int maximo, int reintentos)
{
    int retorno;
    char buffer[tam];
    int minimo=5;
    while (reintentos>0)
    {
        printf(mensaje);
        if (getStringPath(buffer, tam))
        {
            if (strlen(buffer)>=minimo && strlen(buffer)<=maximo )
            {
                break ;
            }

        }
        fflush(stdin);
        reintentos--;
        printf(mensajeError);
    }

    if (reintentos==0)
    {
        retorno=0;
    }
    else
    {
        retorno=1;
        strcpy(pResultado, buffer);
    }

    return retorno;
}




static int getStringPath( char* pResultado, int tam)
{
    int retorno=0;
    int i=0;
    int flag=0;
    char buffer[tam];
    int auxLen;
    int contador=0;

    if( myGets(buffer,tam) )
    {
        while (buffer[i] != '\0' )
        {
            if(buffer[i] == '.' ){
                contador++;
            }
            if ( buffer[i] == '/' || buffer[i] == 92 || buffer[i] == ':' || buffer[i] == '*' || buffer[i]=='?' || buffer[i]=='"' || buffer[i] =='<' || buffer[i] =='>' || buffer[i] =='|' )
            {
                flag=1;
                break ;
            }
            i++;
        }

        if(contador != 1 )
        {
            flag=1;
        }
        else{
        	auxLen = strlen(buffer)-4;
        	if(buffer[auxLen]=='.')
        	{
        		i=1;
        		while(buffer[auxLen+i] != '\0'){
        			if(!isalpha(buffer[auxLen+i])){
        				flag=1;
        			}
        			i++;
        		}
        	}
        	else
        	{
        		flag=1;
        	}
        }

    }

    if(!flag)
    {
        strcpy(pResultado, buffer);
        retorno=1;
    }

    return retorno;
}

int utn_getConfirmacion( char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
    int ret=0;
        char buffer;
        if(pResultado!=NULL && mensaje != NULL && mensajeError != NULL && minimo<=maximo && reintentos >=0)
        {
            do{
                printf(mensaje);
                fflush(stdin);
                buffer = toupper(getch());
                if(buffer == toupper(maximo) || buffer==toupper(minimo))
                {
                    *pResultado = buffer;
                    ret=1;
                    break;
                }
                printf(mensajeError);
                reintentos--;
            }while(reintentos>=0);
        }
        return ret;
}



