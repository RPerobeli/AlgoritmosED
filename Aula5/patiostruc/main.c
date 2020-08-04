#include "stdio.h"
#include "string.h"

typedef struct {
	char material[10];
	int quantidade;
} posicao;

struct {
	posicao p[4][4];
	posicao totais[7];
} patio;

int valida(char *m){
    int i;
	for (i=0;i<7;i++)
		if(!strcmp(m,patio.totais[i].material))
			return 1;
	return 0;
}

int pega_total(){
    char mat[10];
    int t;
	printf("Informe o material: ");
	scanf("%s",mat);
	if (valida(mat))
        for(t=0;t<7;t++)
			if(!strcmp(patio.totais[t].material,mat))
				return patio.totais[t].quantidade;
	return 0;
};

int incluir(){
    int t;
   	int l,c;
    printf("Informe: linha,coluna >");
	scanf("%d,%d",&l,&c);
	if (l<0 || l>3){
		puts("Erro no numero de linhas\n");
		return 1;
	}
	if (c<0 ||c>3){
		puts("Erro no numero de colunas\n");
		return 1;
	}
	puts("Entre com o material: ");
	scanf("%s",patio.p[l][c].material);
	puts("Entre com a quantidade: ");
	scanf("%d",&(patio.p[l][c].quantidade));
		for(t=0;t<7;t++)
			if(!strcmp(patio.totais[t].material,patio.p[l][c].material))
				patio.totais[t].quantidade += patio.p[l][c].quantidade;
	return 0;
};

void disponiveis(){
    int i;
    printf("Materiais disponiveis\n");
    for (i=0;i<7;i++)
        printf("%s ",patio.totais[i].material);
};

void inicia(){
    int i,j;
	// inicializacao dos totais
    strcpy(patio.totais[0].material,"areia");
    strcpy(patio.totais[1].material,"cimento");
    strcpy(patio.totais[2].material,"pedra");
    strcpy(patio.totais[3].material,"telha");
    strcpy(patio.totais[4].material,"tijolo");
    strcpy(patio.totais[5].material,"madeira");
    strcpy(patio.totais[6].material,"ferro");
    patio.totais[0].quantidade=0;
    patio.totais[1].quantidade=0;
    patio.totais[2].quantidade=0;
    patio.totais[3].quantidade=0;
    patio.totais[4].quantidade=0;
    patio.totais[5].quantidade=0;
    patio.totais[6].quantidade=0;
	// inicializacao do patio
	for (i=0;i<4;i++)
		for (j=0;j<4;j++){
			strcpy(patio.p[i][j].material,"nada");
			patio.p[i][j].quantidade=0;
		};
};

int main(int argc, char* argv[])
{
    inicia();
	int opcao=1,i;
	while(opcao!=0){
		printf("\n\n1-Informar material\n2-Total geral\n");
		printf("3-Listar materiais\n4-Total individual\n0-Fim\n>");
		scanf("%d",&opcao);
		switch(opcao){
		case 1:
			incluir();
			break;
		case 2:
			for(i=0;i<7;i++)
				printf("Material: %s = %d \n",patio.totais[i].material,patio.totais[i].quantidade);
			break;
		case 3:
			disponiveis();
			break;
		case 4:
			printf("Total:%d\n",pega_total());
			break;
		default:;
		} //switch
	} // while
	return 0;
}
//---------------------------------------------------------------------------
