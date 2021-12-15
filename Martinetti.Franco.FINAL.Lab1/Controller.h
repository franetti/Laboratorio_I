#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

int controller_showMenu(void);
int controller_showMenuInformes(void);
int controller_loadFromText( LinkedList* pLista);
int controller_saveAsText( LinkedList* lista, char* path);
int controller_list(LinkedList* pLista);
int controller_filter(LinkedList* pLista);
int controller_stats(LinkedList* lista);


