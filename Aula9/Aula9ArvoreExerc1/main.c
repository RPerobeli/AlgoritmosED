#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Celula
{
    char *nome;
    int tel;
    struct Celula *esq;
    struct Celula *dir;
}Celula;

int inserir(Celula **r, char *_nome, int telefone)
{


        if(*r==NULL)
        {
            *r = malloc(sizeof(Celula));
            (*r)->nome = malloc(10*sizeof(char));
            strcpy((*r)->nome,_nome);
            (*r)->esq = NULL;
            (*r)->dir = NULL;
            (*r)->tel = telefone;
            return 0;

        }else if(strcmp((*r)->nome, _nome)==0)
        {
            printf("Nome Repetido\n");
            return 1;
        }else if (strcmp((*r)->nome,_nome)<0)
        {
            inserir(&((*r)->dir),_nome,telefone);
        }else
        {
            inserir(&((*r)->esq),_nome,telefone);
        }

}
int busca(Celula *r, char *_nome)
{
    if(r == NULL)
    {
        return -1;
    }else if(strcmp(r->nome,_nome)==0)
    {
        printf("Nome consta na lista");
        return r->tel;
    }else if (strcmp(r->nome,_nome)<0)
    {
        busca(r->dir,_nome);
    }else
    {
        busca(r->esq,_nome);
    }

}

int main()
{
//    Desenvolva uma implementação  para manipulação de uma Árvore Binária. As informações armazenadas em cada nó da lista são nome
//    (char*) e telefone (int). Inclua os seguintes métodos:

//    a) inserir(nome,telefone)  -> retorna 0 se inserir com sucesso. retorna 1 se não puder inserir (por repetição do nome);
//    Um novo nó (NN) é inserido de acordo com a ordem alfabética nos nomes. NN será incluído no galho esquerdo de um nó (NC)
//    se seu nome precede o nome em NC. NN será inserido no galho direito de NC se seu nome suceder o nome em NC.

//    b) buscar(nome)  -> retorna telefone ou -1, caso não encontre o nome. Considere em sua busca que os nomes estão ordenados na árvore.
//    Obs: ambos os métodos possuem uma solução algorítmica elegante aplicando recursividade!!
    Celula *raiz  = NULL;

    char *nome;
    nome = malloc(10*sizeof(char));
    int opcao=-1, num, ret=0;

       printf("\tMENU");
       while(opcao != 0){
           printf("\n1-Inserir cadastro \n2- Buscar cadastro. \n0- SAIR. \n\nOpcao:");
           scanf("%d", &opcao);
           switch(opcao){
               case 0: break;
               case 1:
                   printf("\nNome: ");
                   scanf("%s", nome);
                   printf("\nTelefone: ");
                   scanf("%d", &num);
                   ret = inserir(&raiz, nome, num);
                   if(ret == 0){
                       printf("\n%d - Cadastro Inserido com Sucesso\n", ret);
                       }else{
                           printf("\n%d - Erro.\n", ret);
                       }

                       break;

                   case 2:
                       printf("\nPor quem deseja buscar? ");
                       scanf("%s", nome);
                       ret = busca(raiz, nome);
                       if(ret != -1){
                           printf("\nTelefone de \"%s\" e': %d. \n", nome, ret);
                       }else{
                           printf("\n(ERRO Nome nao encontrado.\n");
                       }
                       break;
                   default:
                       printf("\nOpcao Invalida.\n");
                       break;

               }
           }

    return 0;
}
