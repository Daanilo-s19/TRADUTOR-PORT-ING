#include "TRADUTOR.h"

//////////////////////MENU DO SWITCH///////////////////////////////
int menu()
{
    int n;
    do
    {
       printf("INFORME UMA OPCAO ABAIXO: ");
       printf("\n [0]SAIR\n [1]ABRIR TEXTO\n [2]INSERIR PALAVRA\n [3]MOSTRAR DADOS \n ");
       printf("[4]TRADUZIR TEXTO\n [5]PALAVRAS QUE INICIAM COM DETERMINADA LETRA\n ~~>");
       scanf("%d", &n);
       printf("\n\n");
    }while(n<0 || n>9);
    getchar();
    return n;

}
//////////////////////LEITURA /////////////////////////////////////
void leitura(char *port)
{
    char eng[TAM], SEP[2]={'-'};
    FILE *fp;

    if((fp=fopen("DICIONARIO.txt", "a"))==NULL)
    {
          printf("NAO FOI POSSIVEL SALVAR NO ARQUIVO.");
          exit(0);
    }

   	if(strlen(port)==0){  //CASO A STRING NAO POSSUA CONTEUDO, COMO NO CASE 2
        printf("\n\n PALAVRA EM PORTUGUES\n~~>");
        scanf("%s",port);
	}
    printf("\n\n TRADUCAO DA PALAVRA [ %s] \n", port);
    scanf("%s",eng);
    strcat(port,SEP);
    strcat(port,eng);
    my_tolower(port);         // SE O TEXTO ESTIVER MAIUSCULO PASSA PARA MINUSCULO
    fprintf(fp,"%s\n", port); // SALVA A PALAVRA JÁ MINUSCULA NO DICIONÁRIO
    fclose(fp);

}
//////////////////////INSERIR PALAVRA//////////////////////////////
arvore* inserir_palavra(arvore *raiz, char *port)
{
    if(raiz==NULL)
    {
        raiz=(arvore*)malloc(sizeof(arvore));
        if(raiz==NULL)
            exit(1);
        strcpy((raiz->pt),port);
        raiz->esq=NULL;
        raiz->dir=NULL;
        //printf("RAIZ\n");
        return raiz;
    }

    if(strcmp(raiz->pt,port)>0){
        //printf("ESQUERDA %s < %s\n", port, raiz->pt);
        raiz->esq=inserir_palavra(raiz->esq,port);
    }

    else if(strcmp(raiz->pt,port)<0){
          // printf("DIREITA %s > %s\n", port, raiz->pt);
           raiz->dir=inserir_palavra(raiz->dir,port); }
    else
        printf("PALVRA REPETIDA\n");

    return raiz;

}
//////////////////////ABRIR ARVORE/////////////////////////////////
arvore* abrir_arvore(arvore **raiz)
{
    FILE *fp;
    char port[TAM];
    if((fp=fopen("DICIONARIO.txt","r"))==NULL)
    {
        printf(" NAO FOI POSSIVEL ABRIR ARQUIVO\n");
        exit(1);
    }

    while(!feof(fp))
    {

       fscanf(fp,"%s",port);

        if((*raiz)==NULL)
            *raiz=inserir_palavra(*raiz, port);
        else
            inserir_palavra(*raiz, port);

    }

    fclose(fp);
    return *raiz;
}
//////////////////////ABRIR ARQUIVO////////////////////////////////
void abrir_frase(char *txt)
{
    FILE *fp;
    if((fp=fopen("FRASE.txt","r"))==NULL)
    {
        printf(" NAO FOI POSSIVEL ABRIR ARQUIVO\n");
        exit(1);
    }
    while(!feof(fp))
    {
        fgets(txt, TAM, fp);
        my_tolower(txt);         // SE O TEXTO ESTIVER MAIUSCULO PASSA PARA MINUSCULO
        printf("%s", txt);
    }
    fclose(fp);
}
///////////////////////VERIFICADOR/////////////////////////////////
char * verifica(arvore *raiz, char *txt)
{
    int i;
    char s[TAM];
    if(raiz == NULL){
       printf ("PALAVRA NAO ENCONTRADA\n\n");
        return NULL;
    }

	strcpy(s, raiz->pt);
	i = my_strtok(raiz->pt, '-');                        // DEVOLVE A POSIÇAO DO LIMITADOR "-"
	s[i] = '\0';                                         // ATRIBUI '\0' NA POSIÇÃO ENCONTRADA E COMPARA ATÉ \0

    if(strcmp(txt, s)>0)
        return verifica(raiz->dir, txt);
    else if (strcmp(txt, s)<0)
        return verifica(raiz->esq,txt);
    return(raiz->pt+i+1);                               // RETORNA A TRADUCAO ENCONTRADA +  A POSICAO DO DELIMITADOR + APÓS O DELIMITADOR
}
//////////////////////MOSTRAR DADOS////////////////////////////////
void mostrar_dados(arvore *raiz)
{
    if(raiz==NULL) return;
    mostrar_dados(raiz->esq);
    printf("%s\n",raiz->pt);
    mostrar_dados(raiz->dir);
}
///////////////////////TRADUCAO///////////////////////////////////
int traducao(arvore* raiz, char *txt)
{
    int cont=0;
    char sinal;
	char *aux;
	FILE *fp;

    if((fp=fopen("FRASE.txt", "r"))==NULL)
    {
        printf(" NAO FOI POSSIVEL ABRIR ARQUIVO\n");
        exit(1);
    }
    while(fscanf(fp, "%s",txt) != EOF)      // ABRE O ARQUIVO LENDO PALAVRA POR PALAVRA
    {

        cont++;                              //CONTA O TOTAL DE PALAVRAS LIDAS

        sinal=pontuacao(txt);               //RETIRA A PONTUAÇÃO DA STRING E ATRIBUE A SINAL
        my_tolower(txt);                   // SE A PALAVRA ESTIVER MAIUSCULO PASSA PARA MINUSCULO
        aux = verifica(raiz, txt);        // VERIFICA E COMPARA A PALAVRA NA ARVORE
        if(aux == NULL)
        {                                //SE A PALAVRA EM PORT NAO ESTIVER PEDE A TRADUCAO E A INSERE NO DICIONARIO E NA ARVORE
            leitura(txt);
            inserir_palavra(raiz, txt);

        }
        if(aux!=NULL)
        {
            printf("%s", aux);     // MOSTRA A TRADUCAO CORRESPONDENTE A PALAVRA LIDA DO ARQUIVO
            printf("%c ", sinal); // MOSTRA A PONTUAÇÃO QUE ACOMPANHAVA A STRING
        }
    }
    printf("\n");
    fclose(fp);

    return cont;

}
///////////////////////////////MY STRTOK/////////////////////////
int my_strtok(char* s, char c)
{
    int i;
    for(i=0; i<strlen(s);i++)
    {
        if(s[i] == c)
        {
            return i;
        }
    }
    return -1;
}
//////////////////////MY TOLOWER/////////////////////////////////
int my_tolower(char *s)
{
    int i;
    for(i=0;i<strlen(s); i++)
    {
      s[i]=tolower(s[i]);

    }
    return *s;
}
//////////////////////Buscar palavras que comece com determinada letra /////////////////////////////////
int buscar_letra(arvore* raiz, char*letra, int i)
{
    my_tolower(letra);                   // SE A LETRA ESTIVER MAIUSCULO PASSA PARA MINUSCULO
    if(raiz==NULL) return NULL;

	if(strncmp(raiz->pt, letra,1)==0) // COMPARA APENAS O PRIMEIRO CARACTERE DA STRING
      {
          printf("%s\n",raiz->pt);
          i++;
      }

    if(strcmp(raiz->pt, letra)>0)
      i+=buscar_letra(raiz->esq, letra,  i);
    else if(strcmp(raiz->pt,letra)<0)
            i+=buscar_letra(raiz->dir, letra,  i);

    return i;

}
//////////////////PONTUAÇÃO///////////////////////////////////
int pontuacao(char *txt)
{
    int i;
    char s='\0';

    if(ispunct(txt[0])!=0)
    {
        s=txt[0];
        txt[0]=' ';
        for(i=0; i<strlen(txt);i++)
            txt[i]=txt[i+1];
        printf("%c",s);
    }

    s='\0';                            // CASO HAJA PONTUACAO NO INICIO DA PALAVRA NAO DEVOVLER NO FIM SE NAO TIVER
    for(i=0;i<strlen(txt);i++)
    {
        if(ispunct(txt[i])!=0)
        {
            s=txt[i];
            txt[i]='\0';
        }
    }
    return s;
}

