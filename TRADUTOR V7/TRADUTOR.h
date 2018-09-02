#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>
#define TAM 100

typedef struct arvore
{
    char pt[TAM];
    struct arvore *esq, *dir;
}arvore;

int menu();// FUNÇÃO PARA O MENU
void abrir_frase(char *);// ABRIR FRASE DO ARQUIVO
arvore* abrir_arvore(arvore **);// ABRIR ARVORE DO ARQUIVO
arvore* inserir_palavra(arvore *, char *);//MONTAR ARVORE P/ TRADUCAO
char* verifica(arvore *, char *); // VERIFICA SE A PALAVRA ESTÁ NA ARVORE
void leitura(char *);// LEITURA DA STRING E SALVAR NO DICIONÁRIO
void mostrar_dados(arvore *);// MOSTRAR DADOS E-R-D
int traducao(arvore*, char *); //TRADUCAO DO TEXTO PORT P/ INGLES
int my_strtok(char*, char); // TRATA A STRING BUSCANDO O TEXTO EM PORT E PRINTANDO EM INGLES
int my_tolower(char *s); // PASSA O TEXTO DE MAIUSCULO P/ MINUSCULO TRATANDO A SENSIBILIDADE DA LINGUAGEM
int buscar_letra(arvore*,char *,int );//Buscar palavras que comece com determinada letra
int pontuacao(char *); // TRATAMENTO DE CARACTERES DE PONTUAÇÃO

