/*
Modificar o algoritmo de Ford-Fulkerson ou o algoritmo DMKM,
de modo a encontrar o fluxo máximo
entre múltiplas fontes e múltiplos escoadouros.
USAR Listas Encadeadas
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct lista{
    int v_id;
    struct lista *next;
    struct lista *prov;
}lista;

typedef struct Aresta{
    int id_origem;
    int id_destino;
    int capacidade;
    int fluxoAtual;
    struct Aresta *next;
    struct Aresta *prev;
}Aresta;

typedef  struct Vertice{
    int v_id;
    int pred;
    int fluxo;
    int fonte; // booleano
    int esc;  //  booleano
    struct Aresta *headAresta;
    struct Vertice *next;
    struct Vertice *prev;
}Vertice;

void insere_lista(lista **L, int v){
    lista *novo = malloc(sizeof(lista));
    novo->v_id = v;
    novo->next = NULL;

    if(*L == NULL){
        (*L)=novo;
    }else{
        lista *percorreLista = *L;
        while(percorreLista->next !=NULL)
        {
            percorreLista = percorreLista->next;
        }
        percorreLista->next = novo;
    }
}

void imprime_lista(lista *L){
    while(L != NULL){
        printf("%d ", L->v_id);
        L = L->next;
    }
}

void remove_lista(lista **L){
    lista *aux = *L;
    *L = (*L)->next;
    free(aux);
}

void InsereVertice(Vertice **list, int v){
    Vertice *novo = malloc(sizeof(Vertice));
    novo->v_id = v;
    novo->next = NULL;
    novo->pred = 0;
    novo->fluxo =0;
    novo->prev = NULL;
    novo->headAresta = NULL;
    novo->fonte = 0;
    novo->esc = 0;

    if(*list == NULL)
    {
        (*list)=novo;
    }else
    {
        Vertice *percorreLista = *list;
        while(percorreLista->next !=NULL)
        {
            percorreLista = percorreLista->next;
        }
        percorreLista->next = novo;
        novo->prev = percorreLista;
    }
}

void InsereAresta(Aresta **list, int o, int v, int capacidade){
    Aresta *nova = malloc(sizeof(Aresta));
    nova->capacidade = capacidade;
    nova->fluxoAtual = 0;
    nova->id_origem = o;
    nova->id_destino = v;
    nova->next = NULL;
    nova->prev = NULL;


    if(*list == NULL)
    {
        (*list)=nova;
    }else
    {
        Aresta *percorreLista = *list;
        while(percorreLista->next !=NULL)
        {
            percorreLista = percorreLista->next;
        }
        percorreLista->next = nova;
        nova->prev = percorreLista;
    }

}

Vertice* BuscaVertice(Vertice *list, int id){
    Vertice *procurado = list;

    while(procurado != NULL && procurado->v_id != abs(id)){

        procurado = procurado->next;
    }
    if(procurado == NULL)
        printf("\nVertice nao esta presente no Grafo.\n");

    return procurado;
}

Aresta* BuscaAresta(Aresta *list, int v){
    Aresta *procurada = list;

    while(procurada != NULL  && procurada->id_destino != abs(v) ){
        procurada = procurada->next;
    }
    if(procurada == NULL)
        printf("\nAresta nao esta presente no Grafo.\n");
    return procurada;
}

void RemoveVertice(Vertice **list, int v_id){
    Vertice *procurado = BuscaVertice(*list,v_id);
    if(procurado->prev != NULL)
    {
        procurado->prev->next = procurado->next;
    }else
    {
        (*list) = procurado->next;
    }
    if(procurado->next!=NULL)
    {
        procurado->next->prev = procurado->prev;
    }
}

void RemoveAresta(Aresta **list, int id){
    Aresta *procurada = BuscaAresta(*list,id);
    //printf("\nRemoveu a aresta %d para %d, com capacidade %d", procurada->id_origem, procurada->id_destino,procurada->capacidade);
    if(procurada->prev != NULL)
    {
        procurada->prev->next = procurada->next;
    }else
    {
        (*list) = procurada->next;
    }
    if(procurada->next!=NULL)
    {
        procurada->next->prev = procurada->prev;
    }
}

void ImprimeAresta(Aresta *list){
    while(list != NULL){
        printf(" |%d , %d , %d| ", list->id_destino, list->capacidade, list->fluxoAtual);
        list = list->next;
    }
}

void ImprimeVertice(Vertice *list){
    while(list != NULL){
        printf("%d ", list->v_id);
        list = list->next;
    }
}

void ImprimeGrafo(Vertice *G){
    while(G != NULL){
        printf("%d ", G->v_id);
        ImprimeAresta(G->headAresta);
        G = G->next;
        printf("\n");
    }
}

void InsereFonte(Vertice **G, int *fontes, int Nf){
    Vertice *F = NULL;
    for(int i=0; i<Nf; i++){
        F = BuscaVertice(*G, *(fontes + i));
        F->fluxo = INT_MAX;
        F->fonte = 1;
    }
}

void InsereEscoadouro(Vertice **G, int *esc, int Ne){
    Vertice *E = NULL;
    for(int i=0; i<Ne; i++){
        E = BuscaVertice(*G, *(esc + i));
        E->esc = 1;
    }
}

void CopiaGrafo(Vertice **GL, Vertice *G){
    Aresta *percorreAresta = NULL;
    while(G != NULL){
        InsereVertice(GL, G->v_id);
        Vertice *temp = BuscaVertice(*GL, G->v_id);
        (temp)->pred = G->pred;
        (temp)->fluxo = G->fluxo;
        (temp)->fonte = G->fonte;
        (temp)->esc = G->esc;
        percorreAresta = G->headAresta;
        while(percorreAresta!=NULL)
        {
            InsereAresta(&(temp->headAresta),percorreAresta->id_origem,percorreAresta->id_destino,percorreAresta->capacidade);
            percorreAresta=percorreAresta->next;
        }
        G = G->next;
    }
}

int BuscaFonte(Vertice *GL){
    while(GL->fonte == 0 && GL != NULL){
        GL = GL->next;
    }
    if(GL == NULL){
        printf("\nNao ha fontes!!\n");
        return -1;
    }
    return GL->v_id;
}

int BuscaEscoadouro(Vertice *GL){
    while(GL->esc == 0 && GL != NULL){
        GL = GL->next;
    }
    if(GL == NULL){
        printf("\nNao ha escoadouros!!\n");
        return -1;
    }
    return GL->v_id;
}

int BuscaEscoadouroRotulado(Vertice *GL){
    while(GL->esc == 0 && GL != NULL){ //Procuro escoadouro dentre todos os vértices em G-linha
        GL = GL->next;
    }
    if(GL == NULL){
        printf("\nNao ha escoadouros!!\n");
        return 0;
    }else if(GL->pred!=0) //Confere rotulação do escoadouro
    {
        return GL->v_id;
    }else{
        return 0;
    }
    return 0;
}

int min(int a, int b){
    if(a <= b){
        return a;
    }else{
        return b;
    }
}

void InsereFluxo(Aresta **A, int v){
    (*A)->fluxoAtual = v;
}

void AnalisaFluxo(Vertice **GL, lista **L){
    Vertice *V_atual, *proxV;
    Aresta *percorre_aresta;
    V_atual = BuscaVertice((*GL), (*L)->v_id); //Busca em G_linha o vértice de id na primeira posição da Lista L.
    percorre_aresta = V_atual->headAresta;

    while(percorre_aresta != NULL){
        proxV = BuscaVertice(*GL,percorre_aresta->id_destino); //Busca ponteiro em G_linha do próximo vértice (destino) da aresta Percorre_Aresta

        if(proxV->pred == 0 && (percorre_aresta->fluxoAtual < percorre_aresta->capacidade)&& proxV->fonte!=1) //Confere se o vértice proxV já foi rotulado (existe predecessor)
        {                                                                                                     //e se não é fonte e se há capacidade para o fluxo atual
            proxV->pred = V_atual->v_id;    // ProxV recebe como predecessor o vértice V_atual.
            int f_min = min(V_atual->fluxo, percorre_aresta->capacidade - percorre_aresta->fluxoAtual);     //fmin = minimo entre o fluxo que chega no vértice e o quanto ainda pode ser enviado
            proxV->fluxo += f_min;      //Incrementa o fluxo no vertice proxV
            insere_lista(L, percorre_aresta->id_destino);       //Inserir o ID de proxV em L.
        }
        if(proxV->pred == 0 && (percorre_aresta->fluxoAtual > 0 && proxV->fonte!=1)){   // Confere se não está rotulado, se não é fonte e se a aresta tem fluxo
            proxV->pred = (-1)*V_atual->v_id;   // Predecessor é negativo, pois a aresta está saturada e o seu sentido original é inverso ao que está em G-linha
            int f_min = min(V_atual->fluxo, percorre_aresta->fluxoAtual); //fmin = minimo entre o fluxo que chega no vértice e o fluxo atual
            proxV->fluxo += f_min; //Incrementa o fluxo no vertice proxV
            insere_lista(L, percorre_aresta->id_destino); //Inserir o ID de proxV em L.
        }
        //ImprimeVertice(*L);
        //printf("\n");
        percorre_aresta=percorre_aresta->next;
    }
    //printf("\n");
    //ImprimeGrafo(*GL);
}

Vertice *AvaliaCaminho(Vertice **G, Vertice *GL, int esc){
    Vertice *P_linha = BuscaVertice(GL,esc); //P_linha recebe o vertice escoadouro, e fará o caminho inverso até a fonte
    Vertice *caminho = NULL;

    int fluxoFinal = P_linha->fluxo; //fluxo final é o que será agregado no Grafo G original.

    while(P_linha->pred !=0)
    {
        InsereVertice(&caminho,P_linha->v_id); //criando caminho de volta
        if(P_linha->esc!=0)
        {
            Vertice *V = BuscaVertice(caminho,P_linha->v_id);
            V->esc = P_linha->esc;
        }
        if(P_linha->pred>=0)
        {
            Vertice *Predecessor = BuscaVertice(*G,P_linha->pred);  //Predecessor no Grafo original G
            Aresta *A = BuscaAresta(Predecessor->headAresta,P_linha->v_id); //Aresta com origem no predecessor e destino em P_linha
            A->fluxoAtual = A->fluxoAtual + fluxoFinal; // Incrementa o fluxo atual da aresta A no grafo G.
        }else
        {   //Caso o predecessor seja negativo
            Vertice *Predecessor = BuscaVertice(*G,P_linha->v_id); //Busca no grafo G o próprio P_linha, que vai ser a origem da aresta no grafo original (sentido invertido da aresta)
            Aresta *A = BuscaAresta(Predecessor->headAresta,abs(P_linha->pred)); // Predecessor de P_linha é o destino da Aresta A
            A->fluxoAtual = A->fluxoAtual - fluxoFinal; //Retira Fluxo da aresta A no grafo G.
        }
        P_linha =  BuscaVertice(GL,P_linha->pred); //Retornando o caminho em GL, a partir dos predecessores.
    }
    InsereVertice(&caminho,P_linha->v_id);
   // printf("\n Grafo original fica:\n");
    //ImprimeGrafo(*G);
    return caminho;
}

int Existe_aresta(Vertice *V, int id_dest){
    Aresta *auxA = V->headAresta;
    while(auxA != NULL){
        if(auxA->id_destino == id_dest)
            return 1;
        auxA = auxA->next;
    }
    return 0;
}

void ResetGrafo(Vertice **list){
    Vertice *percorreVertices = *list;
    while(percorreVertices!=NULL)
    {
        percorreVertices->pred = 0;
        if(percorreVertices->fluxo!= INT_MAX)
        {
            percorreVertices->fluxo =0;
        }
        percorreVertices=percorreVertices->next;
    }
}

void Cria_aresta_contraria(Vertice *Grafo, Vertice **G_linha, Vertice *caminho){
    Vertice *P = BuscaVertice(caminho,BuscaEscoadouro(caminho)); //Caminho ta na ordem inversa (7,..1).
    while(P->next!=NULL)
    {
        P = P->next; //Percorre até o último elemento de "Caminho", que seria a fonte do Grafo.
    }
    //não posso percorrer G, percorrer caminho P'
    while(P->prev != NULL){     //Enquanto nao chega no primeiro elemento da Lista Caminho
        Vertice *G = BuscaVertice(Grafo,P->v_id);   //Vertice atual em G
        Vertice *auxV = BuscaVertice(*G_linha,P->v_id);  //Vertice atual em G_linha
        Vertice *proxV_G = BuscaVertice(Grafo,P->prev->v_id); //Proximo vertice do caminho em G
        Vertice *proxV= BuscaVertice(*G_linha,P->prev->v_id); //Proximo vertice do caminho em G_linha

        if(proxV->pred>=0)
        {
            Aresta *auxAG = BuscaAresta(G->headAresta,P->prev->v_id); //Busca aresta em G cujo destino é o ID do próximo vértice do caminho
            if(auxAG != NULL)
            {
                Aresta *auxAGL = BuscaAresta(auxV->headAresta,auxAG->id_destino); //Cria aresta em G_linha cujo destino é o ID do próximo vértice do caminho (identico a auxAG).
                if(auxAG->fluxoAtual > 0 && auxAG->fluxoAtual < auxAG->capacidade )
                {
                    if(Existe_aresta(proxV, auxAG->id_origem)){ //Se ja existe essa aresta contrária, nao precisa criar outra, só atualizar os valores
                        Aresta *A = BuscaAresta(proxV->headAresta,auxAG->id_origem);
                        A->capacidade = auxAG->fluxoAtual;
                        auxAGL->capacidade = auxAG->capacidade - auxAG->fluxoAtual;
                        InsereFluxo(&A,auxAG->fluxoAtual);
                        auxAGL->fluxoAtual = 0;
                    }else{                                      //Se não existir essa aresta contrária, devemos criar e atualizar seu fluxo
                        InsereAresta(&proxV->headAresta, auxAG->id_destino, auxAG->id_origem, auxAG->fluxoAtual);

                        if((auxAG->capacidade) - (auxAG->fluxoAtual) > 0){          //Verifica se há capacidade para atualizar o fluxo
                            auxAGL->capacidade = (auxAG->capacidade) - (auxAG->fluxoAtual);
                            Aresta *A = BuscaAresta(proxV->headAresta,auxV->v_id);
                            InsereFluxo(&A,auxAG->fluxoAtual);
                            auxAGL->fluxoAtual = 0;
                        }else{                               //Se a capacidade máxima for atingida, removemos as arestas e criamos apenas uma no sentido contrario com a capacidade total.
                            RemoveAresta(&proxV->headAresta, auxV->v_id);
                            InsereAresta(&proxV->headAresta, proxV->v_id, auxV->v_id, auxAG->capacidade);
                            Aresta *A = BuscaAresta(proxV->headAresta,auxV->v_id);
                            InsereFluxo(&A,auxAG->fluxoAtual);
                            RemoveAresta(&auxV->headAresta,auxAG->id_destino);
                        }

                    }
                }

                if(auxAG->fluxoAtual >= auxAG->capacidade) //Saturação
                {
                    if(!(Existe_aresta(proxV, auxAG->id_origem))) //Se não existe aresta no sentido contrário, ele cria e remove a aresta original
                    {
                        InsereAresta(&proxV->headAresta, proxV->v_id, auxV->v_id, auxAG->capacidade);
                        Aresta *A = BuscaAresta(proxV->headAresta, auxV->v_id);
                        InsereFluxo(&A, auxAG->fluxoAtual);
                        RemoveAresta(&auxV->headAresta, auxAG->id_destino);
                    }else
                    {                                       // Se já existe, ele busca essa aresta, atualiza os valores e remove a aresta original
                        Aresta *A = BuscaAresta(proxV->headAresta,auxV->v_id);
                        InsereFluxo(&A,auxAG->fluxoAtual);
                        RemoveAresta(&auxV->headAresta,auxAG->id_destino);
                        A->capacidade = A->fluxoAtual;
                    }
                }
            }
        }else{      // Caso o predecessor seja negativo
            Aresta *auxAG = BuscaAresta(proxV_G->headAresta,P->v_id); //Busca em G a aresta que leva ao vértice atual P_linha
            if(auxAG != NULL)
            {
                Aresta *auxAGL = BuscaAresta(proxV->headAresta,auxAG->id_destino);  //Busca em G_linha a mesma aresta de auxAG
                if(auxAG->fluxoAtual > 0 && auxAG->fluxoAtual < auxAG->capacidade )
                {
                    Vertice *proxV = BuscaVertice(*G_linha, auxAG->id_destino); //busca em G_linha o vértice de destino da aresta auxAG
                    if(Existe_aresta(proxV, auxAG->id_origem)){  //Se ja existe essa aresta, nao precisa criar outra, só atualizar os valores
                        Aresta *A = BuscaAresta(proxV->headAresta,auxAG->id_origem);
                        auxAGL->capacidade = auxAG->capacidade + auxAG->fluxoAtual;
                        InsereFluxo(&A,auxAG->fluxoAtual);
                        auxAGL->fluxoAtual = 0;     //reseta o fluxo na aresta de G_linha
                    }else{              //Se não existir essa aresta contrária, devemos criar e atualizar seu fluxo
                        InsereAresta(&proxV->headAresta, auxAG->id_destino, auxAG->id_origem, auxAG->fluxoAtual);
                        if((auxAG->capacidade) - (auxAG->fluxoAtual) > 0){  //Verifica se há capacidade para atualizar o fluxo
                            auxAGL->capacidade = (auxAG->capacidade) - (auxAG->fluxoAtual);
                            Aresta *A = BuscaAresta(proxV->headAresta,proxV_G->v_id);
                            InsereFluxo(&A,auxAG->fluxoAtual);
                            auxAGL->fluxoAtual = 0;     //reseta o fluxo na aresta de G_linha
                        }else{
                            RemoveAresta(&proxV_G->headAresta,proxV->v_id);
                            InsereAresta(&proxV->headAresta,proxV->v_id,proxV_G->v_id,auxAG->capacidade);
                            Aresta *A = BuscaAresta(proxV->headAresta,proxV_G->v_id);
                            InsereFluxo(&A,auxAG->fluxoAtual);
                            RemoveAresta(&proxV_G->headAresta,auxAG->id_destino);
                        }

                    }
                }
                if(auxAG->fluxoAtual >= 0) // Caso que contempla o ato de retirar fluxo de um nó
                {
                    if(Existe_aresta(auxV, auxAG->id_origem)) //Se existe aresta no sentido, somente atualiza valores
                    {
                        Aresta *A = BuscaAresta(auxV->headAresta,auxAG->id_origem);
                        InsereFluxo(&A,auxAG->fluxoAtual);
                        if(auxAG->fluxoAtual==0)
                        {
                            RemoveAresta(&auxV->headAresta,auxAG->id_origem); //Remove a aresta contrária
                        }
                        //Em G', aumentar a capacidade da aresta padrão, ja q foi retirado fluxo
                        A = BuscaAresta(proxV->headAresta,auxAG->id_destino);
                        A->capacidade = auxAG->capacidade - auxAG->fluxoAtual;
                    }
                }
            }
        }
        auxV = auxV->next;
        P = P->prev;
    }
    //printf("\n Glinha e:\n");
    //ImprimeGrafo(*G_linha);
}

void FordFulkerson(Vertice *Grafo){
    Vertice *G_linha = NULL;
    lista *L = NULL;
    CopiaGrafo(&G_linha, Grafo);
    insere_lista(&L, BuscaFonte(G_linha)); //Inicializa a lista L com o ID da Fonte

    while(L != NULL)
    {
        AnalisaFluxo(&G_linha, &L);
        remove_lista(&L);

        if(BuscaEscoadouroRotulado(G_linha) > 0)
        {
            Vertice *Caminho = AvaliaCaminho(&Grafo,G_linha, BuscaEscoadouroRotulado(G_linha)); //Retomando caminho inverso atualizando fluxo em G.
            L = NULL;   //Reseta lista L
            insere_lista(&L, BuscaFonte(G_linha));  //Inicializa a lista L com o ID da Fonte
            Cria_aresta_contraria(Grafo, &G_linha,Caminho);   //Atualiza/Cria em G_linha as arestas que contem fluxo atual em G
            ResetGrafo(&G_linha);   //Volta os fluxos para 0 para começar uma nova tentativa de caminho
        }
    }
    return;
}

int conta_fluxo(Vertice *Grafo){
    int cont=0;
    Vertice *auxV = BuscaVertice(Grafo, BuscaFonte(Grafo));
    Aresta *auxA = auxV->headAresta;
    while(auxA != NULL){    // Contar o Fluxo atual de todas as arestas da Fonte do Grafo G.
        cont += auxA->fluxoAtual;
        auxA=auxA->next;
    }
    return cont;
}

void Reduz_fontes(int *fontes, Vertice **V, int i){
    Vertice *F1 = BuscaVertice(*V, *fontes); //F1 Recebe sempre a primeira fonte
    Vertice *F2 = BuscaVertice(*V, *(fontes+i)); // F2 Recebe sempre as fontes seguintes (2, 3, 4...)
    Aresta *aux = F1->headAresta;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = F2->headAresta; //Imenda as arestas de F2 no final da lista de arestas F1
    (F2->headAresta)->prev = aux;
    (F2->prev)->next = F2->next;
    (F2->next)->prev = F2->prev;
}

void Reduz_escoadouros(int *esc, Vertice **G, int i){
    Vertice *E1 = BuscaVertice(*G, *esc); //E1 Recebe sempre o primeiro escoador
    Vertice *E2 = BuscaVertice(*G, *(esc+i)); // E2 Recebe sempre os escoadouros seguintes (2, 3, 4...)
    Vertice *auxV = *G;
    Aresta *auxA;

    while(auxV != NULL){    //Percorre todo o grafo, mudando o destino das arestas de demais escoadouros para E1
        auxA = auxV->headAresta;
        while(auxA != NULL){
            if(auxA->id_destino == E2->v_id){
                auxA->id_destino = E1->v_id;    // Aresta passa a apontar para o Escoardouro 1 ao invés dos demais
            }
            auxA = auxA->next;
        }
        auxV = auxV->next;
    }
    RemoveVertice(&E2, E2->v_id);   //Remove os escoadouros desnecessários
}

void soma_aresta_repetida(Vertice **G){
    Vertice *auxV = *G;
    Aresta *Atual;
    Aresta *Percorre_Aresta, *aux;
    while(auxV != NULL){        //Percorrer Todos os nós do Grafo
        Atual = (auxV)->headAresta;
        while(Atual != NULL){       // Para cada aresta de tal vértice compara todos o "id_destino" das próximas arestas com a atual
            Percorre_Aresta = Atual->next;
            if(Atual->id_origem!=auxV->v_id)
            {
                Atual->id_origem = auxV->v_id;
            }
            while(Percorre_Aresta != NULL){
                if(Percorre_Aresta->id_destino == Atual->id_destino){
                    Atual->capacidade += Percorre_Aresta->capacidade;   // Somar a capacidade das arestas de um mesmo vértice e com destinos repetidos
                    aux = Percorre_Aresta;
                    RemoveAresta(&Percorre_Aresta, Atual->id_destino); // Remove arestas de um mesmo vértice com destinos repetidos, deixando apenas 1.
                    Percorre_Aresta = Percorre_Aresta->next;
                    free(aux);
                }else{
                    Percorre_Aresta = Percorre_Aresta->next;
                }
            }
        Atual = Atual->next;
        }
    auxV = auxV->next;
    }
}

int main()
{
    FILE *arq = NULL;
    int Nv=0, Na=0, Nf=0, Ne=0;

    arq = fopen("grafo3.txt","r");

    if(arq == NULL)
    {
        printf("Arquivo Vazio");
    }else
    {
        fscanf(arq, "%d %d %d", &Nv, &Na, &Nf);

        if(Nv<= 0 || Na <=0 || Nf <= 0){
            printf("\nGrafo Invalido!");
            return 0;
        }

        int *vertices_fontes = malloc(Nf*sizeof(int));
        for(int i=0; i<Nf; i++)
            fscanf(arq, "%d", (vertices_fontes + i));

        fscanf(arq, "%d", &Ne);

         if(Ne<= 0){
            printf("\nGrafo Invalido!");
            return 0;
        }

        int *vertices_esc = malloc(Ne*sizeof(int));
        for(int i=0; i<Ne; i++)
            fscanf(arq, "%d", (vertices_esc + i));

        Vertice *Grafo = NULL;
        for(int i=1; i<=Nv; i++)
            InsereVertice(&Grafo, i);

        for(int i=1; i<=Na; i++){
            int o, d, c;
            fscanf(arq, "%d %d %d", &o, &d, &c);
            Vertice *aux = BuscaVertice(Grafo, o);
            InsereAresta(&aux->headAresta, o, d, c);
        }
        fclose(arq);

        InsereFonte(&Grafo, vertices_fontes, Nf); //Indicar no Grafo o(s) nó(s) que é(são) Fonte(s)
        InsereEscoadouro(&Grafo, vertices_esc, Ne); //Indicar no Grafo o(s) nó(s) que é(são) Escoadouro(s)

        printf("Grafo Inicial: \n"); //Grafo Lido do arquivo texto
        ImprimeGrafo(Grafo);

        if(Nf > 1) // Se tiver mais de 1 fonte
            for(int i=1; i<Nf; i++)
                Reduz_fontes(vertices_fontes, &Grafo, i); // Reduz o problema para apenas 1 fonte

        if(Ne > 1) // Se tiver mais de 1 escoadouro
            for(int i=1; i<Ne; i++)
                Reduz_escoadouros(vertices_esc, &Grafo, i);  //Reduz o problema para apenas 1 escoadouro

        soma_aresta_repetida(&Grafo); // Processa arestas de um vértice que possuem um mesmo destino

        free(vertices_fontes); // Libera memória, pois a informação já está contemplada na estrutura
        free(vertices_esc);    // Libera memória, pois a informação já está contemplada na estrutura

        printf("Grafo com fontes e escoadouros reduzidos: \n");
        ImprimeGrafo(Grafo);

        FordFulkerson(Grafo);

        //Resposta Final:
        printf("\n\nPortanto, o fluxo maximo e: %d \n", conta_fluxo(Grafo)); // Função Conta_Fluxo conta o fluxo máximo do grafo
        printf("\nGrafo G Final: \n");
        ImprimeGrafo(Grafo);
    }
    return 0;
}
