#ifndef UTNINPUTS__H_INCLUDED
#define UTNINPUTS__H_INCLUDED



#endif // UTNINPUTS__H_INCLUDED

int utn_getNumero( int* pResultado, char* mensaje,char* mensajeError, int minimo,int maximo, int reintentos);
int utn_getNumeroConDecimales( float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getChar( char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);
int utn_getTexto( char* pResultado, int tam, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getAlfanumerico( char* pResultado, int tam, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getPath( char* pResultado, int tam, char* mensaje, char* mensajeError, int maximo, int reintentos);
int utn_getConfirmacion( char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);
