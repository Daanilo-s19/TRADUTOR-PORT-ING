#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "TRADUTOR.h"

int main()
{

    setlocale(LC_ALL,"portuguese");
    arvore *raiz=NULL;
    int x, cont;
    char txt[TAM],port[TAM];

    //abrir_arvore(&raiz); // J� INICIA O PROGRAMA MONTANDO A ARVORE COM AS PALAVRAS DO DICION�RIO
	while(1)
	{
	    system ("cls");
        x = menu();
        system ("cls");
	    switch(x)
	    {
            case 0:
                exit(1);
                break;
	        case 1:
                abrir_frase(txt);
                system("pause");
	            break;
            case 2:
                strcpy(port,"\0"); //DEIXA A STRING VAZIA QUANDO HOUVER INSERCAO SUCESSIVAS DE PALAVRAS
                leitura(port);
                if(raiz==NULL)
                    raiz=inserir_palavra(raiz, port);
                else
                    inserir_palavra(raiz, port);

                system ("pause");
                break;
            case 3:
                mostrar_dados(raiz);
                system("pause");
                break;
            case 4:
                printf("_____________________________<TEXTO  EM  PORTUGU�S>______________________________\n");
                abrir_frase(txt);
                printf("\n\n_______________________________<TEXTO  EM  INGL�S>______________________________\n\n");
            	cont=traducao(raiz,txt);
                printf("\n\n_______________________________<QUATIDADE DE PALAVRAS>______________________________\n\n");
            	printf("                                         %i    \n\n",cont);
            	system ("pause");
            	break;
            case 5:
            	printf("DIGITE A LETRA QUE DESEJA BUSCAR \n~~>");
            	gets(port);
            	printf("____________________________<PORTUGUÊS - INGLES>________________________________\n");
            	if(buscar_letra(raiz,port,0)==0)
                    printf(" NAO EXISTE PALAVRA NO DICION�RIO QUE INICIE COM [%s]\n",port);
            	system("pause");
            	break;
            default:
                printf(" OPCAO INVALIDA\n");
                system ("pause");
                break;
	    }
    }
}
