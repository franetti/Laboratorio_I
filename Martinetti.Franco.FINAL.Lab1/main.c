#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"


int main()
{

    int skip=0;
    LinkedList* lista = ll_newLinkedList();

    do{
        switch(controller_showMenu())
        {
            case 1:
                controller_loadFromText(lista);
                break;
            case 2:
                controller_filter(lista);
            	break;
            case 3:
                controller_stats(lista);
                break;
            case 4:
                controller_list(lista);
                break;
            case 5:
            	printf("Adios!\n");
            	skip=1;
                break;
            default:
            	printf("Opcion incorrecta.\n");
            	break;
        }
    }while(!skip);

    return 0;
}
