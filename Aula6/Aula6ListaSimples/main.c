#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cadastro
{
    int telefone;
    char* nome;
    //char nome[20];
    struct Cadastro *next;

}Cadastro;

//Cadastro *inicio; // inicio da lista

int InsereCadastro(Cadastro **inicio)
{
    char nome_input[20];
    Cadastro *cadastroAtual = malloc(sizeof(Cadastro));
    printf("\nQual o nome que deseja cadastrar?");
    scanf("%s", nome_input);
    cadastroAtual->nome = malloc(20*sizeof(char));
    strcpy(cadastroAtual->nome,nome_input);
    printf("\nQual o telefone??");
    scanf("%d", &cadastroAtual->telefone);
    cadastroAtual->next = NULL;

    if(*inicio == NULL)
    {
        *inicio = cadastroAtual;
    }else
    {
        Cadastro *percorreLista = *inicio;
        while(percorreLista->next!= NULL)
        {
            if(strcmp(cadastroAtual->nome,percorreLista->nome)==0)
            {
            printf("\n Nome repetido");
                return 1;
            }
            percorreLista = percorreLista->next;
        }
        percorreLista->next = cadastroAtual;
    }
    return 0;
}

int BuscaCadastrado(Cadastro **inicio)
{
    Cadastro *percorreLista = *inicio;
    char nomeProcurado[20];
    int tel = 0;
    printf("\nInsira o nome do cadastrado: ");
    scanf("%s" , nomeProcurado);

    while(strcmp(percorreLista->nome,nomeProcurado)!=0 && percorreLista->next != NULL)
    {
        percorreLista = percorreLista->next;
    }
    tel = percorreLista->telefone;
    return tel;
}

int main()
{
//    Desenvolva uma implementação  para manipulação de uma lista simples. As informações armazenadas em cada nó da lista são nome (char*) e telefone (int). Inclua os seguintes métodos:
//    a) inserir(nome,telefone)  -> retorna 0 se inserir com sucesso. retorna 1 se não puder inserir (por repetição do nome);
//    b) buscar(nome)    -> retorna telefone ou -1, caso não encontre o nome.
    int continuar = 1;
    int operacao = 0;

    int cadastroConcluido;
    int telefone;

    Cadastro *inicio; // inicio da lista
    inicio = NULL;

    while(continuar)
    {
        printf("Deseja fazer qual operacao?");
        printf("\n1 - Inserir Cadastro");
        printf("\n2 - Buscar Telefone Cadastrado\n");
        scanf("%d", &operacao);

        switch(operacao)
        {
        case(0):
        {
        printf("\nerro");
        break;
        }
        case(1):
        {
            cadastroConcluido = InsereCadastro(&inicio);
            if(!cadastroConcluido)
            {
                printf("\ncadastro ok");
            }
            break;
        }
        case(2):
        {
            telefone = BuscaCadastrado(&inicio);
            printf("\nTelefone = %d" , telefone);
        }
        }
        printf("\nDeseja Continuar? sim = 1, nao = 0\n");
        scanf("%d", &continuar);
    }
    return 0;
}
