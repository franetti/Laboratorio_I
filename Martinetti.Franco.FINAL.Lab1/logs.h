#ifndef log_H_INCLUDED
#define log_H_INCLUDED

struct{
    char date[11];
    char time[6];
    char serviceName[65];
    int gravedad;
    char msg[65];
}typedef eLog;


#endif // log_H_INCLUDED
eLog* log_new(void);
eLog* log_newParametros(char *pDate,char* pTime,char* pServicename, int gravedad , char* pMsg);
int log_destroylog(eLog* plog);
int log_setDate(eLog* this,char* pDate);
int log_getDate(eLog* log, char* pDate);
int log_setTime(eLog* this,char* pTime);
int log_getTime(eLog* log, char* pTime);
int log_setServiceName(eLog* this,char* pServicename);
int log_getServiceName(eLog* log, char* pServicename);
int log_setGravedad(eLog* this,int gravedad);
int log_getGravedad(eLog* log, int* pGravedad);
int log_setMsg(eLog* this,char* pMsg);
int log_getMsg(eLog* log, char* pMsg);

int log_listlogs(LinkedList* lista);
void log_showlog(eLog* log);
int log_filterWarnings(void* element);
int log_filterErrors(void* element);
int log_showStats(LinkedList* lista);

