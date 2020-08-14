/* Todos os trabalhos devem ter menu de operações
Funções (poe, pega, lista, conta o numero de elementos, busca um elemento(booleano) e permanencia)
em uma fila baseada em lista. permanencia(media  em segundos do tempo de permanencia do elemento na fila)
getTimeofday() */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int total_elementos;
double soma_tempo_permanencia;

typedef struct celula{
    int elemento;
    double tempo;
    struct celula *prox;
} celula;

void poe(celula **_i, int n){

    celula *novo;

    novo = malloc(sizeof(celula));
    novo->elemento = n;
    novo->prox = NULL;

    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    novo->tempo = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;

    if(*_i == NULL){
        *_i = novo;
    }else{
        celula *atual = *_i;
        while(atual->prox != NULL)
            atual = atual->prox;

        atual->prox = novo;
    }
}

void pega(celula **_i){
    celula *atual = *_i;
    int resp;

    if(*_i == NULL){
        printf("\n\tFila Vazia\n\n");
    }else{
        resp = (*_i)->elemento;
        *_i = atual->prox;
        printf("\n\tElemento Retirado: %d\n\n", resp);
    }
    free(atual);

}

void listar(celula *_i){
    celula *atual;
    atual = _i;
    printf("\tListagem dos elementos:\n\t");
    while(atual != NULL){
        printf("%d ", atual->elemento);
        atual = atual->prox;
    }
    printf("\n\n");
    free(atual);
}

int conta(celula *_i){
    int cont = 0;
    celula *atual = _i;

    while(atual != NULL){
        atual = atual->prox;
        cont++;
    }
    return cont;
    free(atual);
}

int busca(celula *_i, int n){
    celula *atual = _i;
    int cont=1;

    if(atual == NULL){
        printf("\n\tFila Vazia para Busca\n\n");
    }else{
        while(atual != NULL){
            if(atual->elemento == n){
                return 1;
            }
            atual = atual->prox;
            cont++;
        }
    }
    return 0;
}

void permanencia(celula *_i){ //DÚVIDA: TEMPO MEDIO SÓ DOS ELEMENTOS QUE SAIRAM, DE TODOS OU SÓ OS QUE ESTÃO NA FILA?
    celula *atual = _i;      //LEVAR EM CONTA O CASO QUANDO A LISTA PASSA DE UNICA PARA VAZIA.
    double t2=0, soma=0;
    float media=0;
    struct timeval tv2;

    if(atual == NULL){
        printf("\n\nLista Vazia.\n\n");
    }else{
        while(atual != NULL){
            gettimeofday(&tv2, NULL);
            t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
            soma = soma + (t2 - atual->tempo);
            atual = atual->prox;
        }
    int cont = conta(_i);
    media = soma/cont;
    printf("\nMedia de permanencia e de: %lf\n\n", media);
    }
}


int main()
{
    int opcao, elem;
    celula *lista = NULL;

    printf("\tBEM VINDO\n");
    do{
        printf(" Qual operacao deseja realizar?\n");
        printf(" 1- Adicionar elemento\n 2- Pegar e remover elemento\n");
        printf(" 3- Listar elementos\n 4- Contar elementos\n");
        printf(" 5- Buscar elemento\n 6- Permanencia de elemento\n");
        printf(" 0- Sair\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("\n\tOBRIGADO!!\n");
            break;

        case 1:
            printf("Qual elemento deseja adicionar a lista? \n");
            scanf("%d", &elem);
            poe(&lista, elem);
            break;

        case 2:
            pega(&lista);
            break;

        case 3:
            listar(lista);
            break;

        case 4:
            printf("\n\tA lista apresenta %d elementos.\n\n", conta(lista));
            break;

        case 5:
            printf("Qual elemento deseja buscar na lista? \n");
            scanf("%d", &elem);
            if(busca(lista, elem)){
                printf("\n\tO Elemento %d pesquisado esta presente na lista.\n\n", elem);
            }else{
                printf("\n\tO Elemento %d pesquisado NAO esta presente na lista.\n\n", elem);
            }
            break;

        case 6:
            //printf("Qual elemento deseja saber sua permanência? \n");
            //scanf("%d", &elem);
            permanencia(lista);
            break;
        }


    }while(opcao != 0);

    return 0;
}
