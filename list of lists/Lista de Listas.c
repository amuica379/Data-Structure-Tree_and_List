#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Aluno: Guilherme Carvalho Caria
  Horário: Terças e Quintas (18:30 - 20:20)
  Número de Matrícula: 201515417
  */

typedef struct nodeCidade{
    char cidade[100];
    char estado[50];
    int populacao;
    double pibPerCapita;
    float idh;
    struct nodeCidade *proxCidadeEstado;
    struct nodeCidade *proxCidadeIdh;
    struct nodeCidade *proxCidadeTemp;
}nodeCidade;

typedef struct nodeEstado{
    char nome[50];
    int numeroDeMunicipios;
    int populacao;
    double pibPerCapita;
    float idh;
    struct nodeEstado *proxEstado;
    struct nodeCidade *primeiraCidade;
    struct nodeEstado *proxEstadoTemp;
}nodeEstado;

typedef struct lista{
    nodeEstado *primeiroEstado;
    nodeCidade *menorIdh;
    nodeCidade *listaTemp;
    nodeEstado *listaEstadoTemp;
}lista;

void insere_lista_idh(lista *lista, nodeCidade *cidade){
    nodeCidade *aux= lista->menorIdh;
    nodeCidade *temp= lista->menorIdh;
    if(cidade->idh < lista->menorIdh->idh || cidade->idh == lista->menorIdh->idh ){
        cidade->proxCidadeIdh= lista->menorIdh;
        lista->menorIdh= cidade;
        return;
    }
    while(aux!=NULL){
        if(cidade->idh > aux->idh){
            if(aux->proxCidadeIdh == NULL){
                aux->proxCidadeIdh= cidade;
                break;
            }
            else{
                temp= aux;
                aux= aux->proxCidadeIdh;
            }
        }
        if(cidade->idh < aux->idh){
            cidade->proxCidadeIdh= aux;
            temp->proxCidadeIdh= cidade;
            break;
        }
        if(cidade->idh == aux->idh){
            if(aux->proxCidadeIdh == NULL){
                aux->proxCidadeIdh= cidade;
                break;
            }
            else{
                cidade->proxCidadeIdh= aux;
                temp->proxCidadeIdh= cidade;
                break;
            }
        }
    }
}

void insere_lista_pibMAIOR(lista *lista, nodeCidade *cidade){
    nodeCidade *aux= lista->listaTemp;
    nodeCidade *temp= lista->listaTemp;
    if(aux == NULL){
      lista->listaTemp= cidade;
      return;
    }//lista vazia
    if(cidade->pibPerCapita > lista->listaTemp->pibPerCapita || cidade->pibPerCapita == lista->listaTemp->pibPerCapita ){
        cidade->proxCidadeTemp= lista->listaTemp;
        lista->listaTemp= cidade;
        return;
    }
    while(aux!=NULL){
        if(cidade->pibPerCapita < aux->pibPerCapita){
            if(aux->proxCidadeTemp == NULL){
                aux->proxCidadeTemp= cidade;
                break;
            }
            else{
                temp= aux;
                aux= aux->proxCidadeTemp;
            }
        }
        if(cidade->pibPerCapita > aux->pibPerCapita){
            cidade->proxCidadeTemp= aux;
            temp->proxCidadeTemp= cidade;
            break;
        }
        if(cidade->pibPerCapita == aux->pibPerCapita){
            if(aux->proxCidadeTemp == NULL){
                aux->proxCidadeTemp= cidade;
                break;
            }
            else{
                cidade->proxCidadeTemp= aux;
                temp->proxCidadeTemp= cidade;
                break;
            }
        }
    }
}

void insere_lista_pibMENOR(lista *lista, nodeCidade *cidade){
    nodeCidade *aux= lista->listaTemp;
    nodeCidade *temp= lista->listaTemp;
    if(aux == NULL){
      lista->listaTemp= cidade;
      return;
    }//lista vazia
    if(cidade->pibPerCapita < lista->listaTemp->pibPerCapita || cidade->pibPerCapita == lista->listaTemp->pibPerCapita ){
        cidade->proxCidadeTemp= lista->listaTemp;
        lista->listaTemp= cidade;
        return;
    }
    while(aux!=NULL){
        if(cidade->pibPerCapita > aux->pibPerCapita){
            if(aux->proxCidadeTemp == NULL){
                aux->proxCidadeTemp= cidade;
                break;
            }
            else{
                temp= aux;
                aux= aux->proxCidadeTemp;
            }
        }
        if(cidade->pibPerCapita < aux->pibPerCapita){
            cidade->proxCidadeTemp= aux;
            temp->proxCidadeTemp= cidade;
            break;
        }
        if(cidade->pibPerCapita == aux->pibPerCapita){
            if(aux->proxCidadeTemp == NULL){
                aux->proxCidadeTemp= cidade;
                break;
            }
            else{
                cidade->proxCidadeTemp= aux;
                temp->proxCidadeTemp= cidade;
                break;
            }
        }
    }
}

void insere_lista_idh_estado_MAIOR(lista *lista, nodeEstado *estado){
    nodeEstado *aux= lista->listaEstadoTemp;
    nodeEstado *temp= lista->listaEstadoTemp;
    if(aux == NULL){
      lista->listaEstadoTemp= estado;
      return;
    }//lista vazia
    if(estado->idh > lista->listaEstadoTemp->idh || estado->idh == lista->listaEstadoTemp->idh ){
        estado->proxEstadoTemp= lista->listaEstadoTemp;
        lista->listaEstadoTemp= estado;
        return;
    }
    while(aux!=NULL){
        if(estado->idh < aux->idh){
            if(aux->proxEstadoTemp == NULL){
                aux->proxEstadoTemp= estado;
                break;
            }
            else{
                temp= aux;
                aux= aux->proxEstadoTemp;
            }
        }
        if(estado->idh > aux->idh){
            estado->proxEstadoTemp= aux;
            temp->proxEstadoTemp= estado;
            break;
        }
        if(estado->idh == aux->idh){
            if(aux->proxEstadoTemp == NULL){
                aux->proxEstadoTemp= estado;
                break;
            }
            else{
                estado->proxEstadoTemp= aux;
                temp->proxEstadoTemp= estado;
                break;
            }
        }
    }
}


void insere_lista_populacaoMAIOR(lista *lista, nodeCidade *cidade){
    nodeCidade *aux= lista->listaTemp;
    nodeCidade *temp= lista->listaTemp;
    if(aux == NULL){
      lista->listaTemp= cidade;
      return;
    }//lista vazia
    if(cidade->populacao > lista->listaTemp->populacao || cidade->populacao == lista->listaTemp->populacao ){
        cidade->proxCidadeTemp= lista->listaTemp;
        lista->listaTemp= cidade;
        return;
    }
    while(aux!=NULL){
        if(cidade->populacao < aux->populacao){
            if(aux->proxCidadeTemp == NULL){
                aux->proxCidadeTemp= cidade;
                break;
            }
            else{
                temp= aux;
                aux= aux->proxCidadeTemp;
            }
        }
        if(cidade->populacao > aux->populacao){
            cidade->proxCidadeTemp= aux;
            temp->proxCidadeTemp= cidade;
            break;
        }
        if(cidade->populacao == aux->populacao){
            if(aux->proxCidadeTemp == NULL){
                aux->proxCidadeTemp= cidade;
                break;
            }
            else{
                cidade->proxCidadeTemp= aux;
                temp->proxCidadeTemp= cidade;
                break;
            }
        }
    }
}

void inserir(lista *lista){
    FILE *f;
    f= fopen("data.csv", "r");
    char *field;
    char aux[50];
    char buff[200];
    char cidade[100];
    char estado[50];
    int populacao;
    double pibPerCapita;
    float idh;
    fgets(buff, 200, (FILE*)f);//Skip Linha 1
    while(fgets(buff, 200, (FILE*)f) != NULL){
        field= strtok(buff, ";");
        strcpy(cidade, field);
        field= strtok(NULL, ";");
        strcpy(estado, field);
        field= strtok(NULL, ";");
        populacao= atoi(field);
        field= strtok(NULL, ";");
        pibPerCapita= atof(field);
        field= strtok(NULL, ";");
        idh= atof(field); //Neste ponto tenho uma cidade salva
        if(lista->primeiroEstado== NULL){ //Lista Vazia
            nodeEstado *novoEstado= (nodeEstado*)malloc(sizeof(nodeEstado));
            strcpy(novoEstado->nome, estado);//Não farei os cálculos dos estados ainda.
            novoEstado->proxEstado= NULL;
            novoEstado->primeiraCidade= NULL;
            novoEstado->proxEstadoTemp= NULL;
            lista->primeiroEstado=novoEstado;
            nodeCidade *novoCidade=(nodeCidade*)malloc(sizeof(nodeCidade));
            strcpy(novoCidade->cidade, cidade);
            strcpy(novoCidade->estado, estado);
            novoCidade->populacao= populacao;
            novoCidade->pibPerCapita= pibPerCapita;
            novoCidade->idh= idh;
            novoCidade->proxCidadeIdh= NULL;
            novoCidade->proxCidadeTemp= NULL;
            novoCidade->proxCidadeEstado= NULL;
            novoEstado->primeiraCidade= novoCidade;
            lista->menorIdh= novoCidade;
        }
        else{ //Lista não vazia
            nodeEstado *aux= lista->primeiroEstado;
            while(1){
                int compare= strcmp(aux->nome, estado);
                if(compare == 0)
                    break;
                else{
                    if(aux->proxEstado == NULL){
                        nodeEstado *novoEstado= (nodeEstado*)malloc(sizeof(nodeEstado));
                        strcpy(novoEstado->nome, estado);
                        novoEstado->proxEstado= NULL;
                        novoEstado->primeiraCidade= NULL;
                        novoEstado->proxEstadoTemp= NULL;
                        aux->proxEstado= novoEstado;
                        aux=aux->proxEstado;
                        break;
                    }
                    else
                        aux= aux->proxEstado;
                }
            }
            if(aux->primeiraCidade != NULL){
                nodeCidade *temp= aux->primeiraCidade;
                while(1){
                    if(temp->proxCidadeEstado == NULL){
                        nodeCidade *novaCidade = (nodeCidade*)malloc(sizeof(nodeCidade));
                        strcpy(novaCidade->cidade, cidade);
                        strcpy(novaCidade->estado, estado);
                        novaCidade->populacao= populacao;
                        novaCidade->pibPerCapita= pibPerCapita;
                        novaCidade->idh= idh;
                        novaCidade->proxCidadeEstado= NULL;
                        novaCidade->proxCidadeIdh=NULL;
                        novaCidade->proxCidadeTemp= NULL;
                        temp->proxCidadeEstado= novaCidade;
                        insere_lista_idh(lista, novaCidade);
                        break;
                    }
                    else
                        temp= temp->proxCidadeEstado;
                }
            }
            else{
                nodeCidade *novaCidade = (nodeCidade*)malloc(sizeof(nodeCidade));
                strcpy(novaCidade->cidade, cidade);
                strcpy(novaCidade->estado, estado);
                novaCidade->populacao= populacao;
                novaCidade->pibPerCapita= pibPerCapita;
                novaCidade->idh= idh;
                novaCidade->proxCidadeEstado= NULL;
                novaCidade->proxCidadeIdh=NULL;
                novaCidade->proxCidadeTemp= NULL;
                aux->primeiraCidade= novaCidade;
                insere_lista_idh(lista, novaCidade);
            }
        }
    }
    fclose(f);
}


void busca_cidade(lista *lista){
    char cidadeBusca[100];
    gets(cidadeBusca);
    nodeEstado *temp= lista->primeiroEstado;
    nodeCidade *aux;
    int i;
    for(i=1; i<=27; i++){
        aux= temp->primeiraCidade;
        while(aux != NULL){
            int compare= strcmp(aux->cidade, cidadeBusca);
            if(compare == 0){
                printf("nome: %s\n", aux->cidade);
                printf("estado: %s\n", aux->estado);
                printf("populacao: %d\n", aux->populacao);
                printf("pib per capita: %f\n", aux->pibPerCapita);
                printf("idh: %f\n", aux->idh);
                printf("\n");
                aux=aux->proxCidadeEstado;
            }
            else
                aux=aux->proxCidadeEstado;
        }
        if(temp->proxEstado != NULL)
            temp= temp->proxEstado;
        else
            break;
    }
}


void busca_estado(lista *lista){
    char estadoBusca[100];
    gets(estadoBusca);
    nodeEstado *temp= lista->primeiroEstado;
    int i;
    for(i=1; i<=27; i++){
            int compare= strcmp(temp->nome, estadoBusca);
            if(compare == 0){
                printf("estado: %s\n", temp->nome);
                printf("numero de municipios: %d\n", temp->numeroDeMunicipios);
                printf("populacao: %d\n", temp->populacao);
                printf("pib per capita: %f\n", temp->pibPerCapita);
                printf("idh: %f\n", temp->idh);
                printf("\n");
                return;
            }
            else
                if(temp->proxEstado != NULL)
                    temp= temp->proxEstado;
    }
}

nodeCidade* encontraMenorIdh(lista *lista){
    nodeCidade *menorIdh;
    nodeCidade *aux;
    nodeEstado *temp= lista->primeiroEstado;
    int i;
    menorIdh= temp->primeiraCidade;
        for(i=1; i<=27; i++){
            aux= temp->primeiraCidade;
            while(aux != NULL){
                if(aux->idh < menorIdh->idh)
                    menorIdh= aux;
                aux= aux->proxCidadeEstado;
            }
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
        return menorIdh;
}

nodeCidade* encontraMaiorIdh(lista *lista){
    nodeCidade *maiorIdh;
    nodeCidade *aux;
    nodeEstado *temp= lista->primeiroEstado;
    int i;
    maiorIdh= temp->primeiraCidade;
        for(i=1; i<=27; i++){
            aux= temp->primeiraCidade;
            while(aux != NULL){
                if(aux->idh > maiorIdh->idh)
                    maiorIdh= aux;
                aux= aux->proxCidadeEstado;
            }
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
        return maiorIdh;
}


void listagem_idh(lista *lista){
    nodeCidade *aux= lista->menorIdh;
    while(aux != NULL){
        printf("IDH: %f\n", aux->idh);
        aux= aux->proxCidadeIdh;
    }
}

void calculaDadosDosEstados(lista *lista){
    nodeCidade *aux;
    nodeEstado *temp= lista->primeiroEstado;
    int i;
        for(i=1; i<=27; i++){
            int numeroMunicipios=0;
            int populacao=0;
            double pibPerCapita=0;
            float idh=0;
            aux= temp->primeiraCidade;
            while(aux != NULL){
                numeroMunicipios++;
                populacao= populacao + aux->populacao;
                pibPerCapita= pibPerCapita + aux->pibPerCapita;
                idh= idh + aux->idh;
                aux= aux->proxCidadeEstado;
            }
            temp->numeroDeMunicipios= numeroMunicipios;
            temp->populacao= populacao;
            temp->idh= (idh/numeroMunicipios);
            temp->pibPerCapita= (pibPerCapita/numeroMunicipios);
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
}

nodeEstado *encontraMaiorIdhEstadual(lista *lista){
    nodeEstado *temp= lista->primeiroEstado;
    nodeEstado *maior;
    maior= temp;
    while(temp != NULL){
        if(temp->idh > maior->idh){
            maior= temp;
        }
        temp= temp->proxEstado;
    }
}

void rankingEstadosIdh(lista *lista){
    nodeEstado *temp= lista->primeiroEstado;

}

void listagem_pibPerCapita_Decrescente(lista *lista){
    nodeCidade *aux;
    nodeEstado *temp= lista->primeiroEstado;
    int i;
        for(i=1; i<=27; i++){
            aux= temp->primeiraCidade;
            while(aux != NULL){
                insere_lista_pibMAIOR(lista, aux);
                aux= aux->proxCidadeEstado;
            }
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
    aux= lista->listaTemp;
    for(i=0; i<10; i++){
        printf("nome: %s\n", aux->cidade);
        printf("estado: %s\n", aux->estado);
        printf("populacao: %d\n", aux->populacao);
        printf("pib per capita: %f\n", aux->pibPerCapita);
        printf("idh: %f\n", aux->idh);
        printf("\n");
        aux= aux->proxCidadeTemp;
    }
}

void listagem_populacao_Decrescente(lista *lista){
    nodeCidade *aux;
    nodeEstado *temp= lista->primeiroEstado;
    int i;
        for(i=1; i<=27; i++){
            aux= temp->primeiraCidade;
            while(aux != NULL){
                insere_lista_populacaoMAIOR(lista, aux);
                aux= aux->proxCidadeEstado;
            }
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
    aux= lista->listaTemp;
    for(i=0; i<10; i++){
        printf("nome: %s\n", aux->cidade);
        printf("estado: %s\n", aux->estado);
        printf("populacao: %d\n", aux->populacao);
        printf("pib per capita: %f\n", aux->pibPerCapita);
        printf("idh: %f\n", aux->idh);
        printf("\n");
        aux= aux->proxCidadeTemp;
    }
}

void listagem_pibPerCapita_Crescente(lista *lista){
    nodeCidade *aux;
    nodeEstado *temp= lista->primeiroEstado;
    int i;
        for(i=1; i<=27; i++){
            aux= temp->primeiraCidade;
            while(aux != NULL){
                insere_lista_pibMENOR(lista, aux);
                aux= aux->proxCidadeEstado;
            }
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
    aux= lista->listaTemp;
    for(i=0; i<10; i++){
        printf("nome: %s\n", aux->cidade);
        printf("estado: %s\n", aux->estado);
        printf("populacao: %d\n", aux->populacao);
        printf("pib per capita: %f\n", aux->pibPerCapita);
        printf("idh: %f\n", aux->idh);
        printf("\n");
        aux= aux->proxCidadeTemp;
    }
}

void listagem_estado_idh_Crescente(lista *lista){
    nodeEstado *temp= lista->primeiroEstado;
    int i;
        for(i=1; i<=27; i++){
                insere_lista_idh_estado_MAIOR(lista, temp);
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
    temp= lista->listaEstadoTemp;
    for(i=0; i<27; i++){
        printf("estado: %s\n", temp->nome);
        printf("numero de municipios: %d\n", temp->numeroDeMunicipios);
        printf("populacao: %d\n", temp->populacao);
        printf("pib per capita: %f\n", temp->pibPerCapita);
        printf("idh: %f\n", temp->idh);
        printf("\n");
        temp= temp->proxEstadoTemp;
    }
}

void limpezaCidades(lista *lista){
    nodeCidade *aux;
    nodeEstado *temp= lista->primeiroEstado;
    int i;
        for(i=1; i<=27; i++){
            aux= temp->primeiraCidade;
            while(aux != NULL){
                aux->proxCidadeTemp= NULL;
                aux= aux->proxCidadeEstado;
            }
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
}

void limpezaEstados(lista *lista){
    nodeEstado *temp= lista->primeiroEstado;
    int i;
        for(i=1; i<=27; i++){
            temp->proxEstadoTemp= NULL;
            if(temp->proxEstado != NULL)
                temp= temp->proxEstado;
            else
                break;
        }
}



void inicializa(lista *lista){
    lista-> primeiroEstado= NULL;
    lista-> menorIdh= NULL;
    lista-> listaTemp= NULL;
    lista-> listaEstadoTemp= NULL;
}




int main(){
    lista *lista1= (lista*)malloc(sizeof(lista));
    inicializa(lista1);
    inserir(lista1);
    calculaDadosDosEstados(lista1);
    char control;
    while(1){
        control= '\0';
        scanf("%c", &control);
        getchar();
        if(control == 'q')
            break;
        if(control == 'c')
            busca_cidade(lista1);
        if(control == 'e')
            busca_estado(lista1);
        if(control == 'a'){
            listagem_pibPerCapita_Decrescente(lista1);
            limpezaCidades(lista1);
            lista1->listaTemp= NULL;
        }
        if(control == 'p'){
            listagem_populacao_Decrescente(lista1);
            limpezaCidades(lista1);
            lista1->listaTemp= NULL;
        }
        if(control == 'z'){
            listagem_pibPerCapita_Crescente(lista1);
            limpezaCidades(lista1);
            lista1->listaTemp= NULL;
        }
        if(control == 't'){
            listagem_estado_idh_Crescente(lista1);
            limpezaEstados(lista1);
            lista1->listaEstadoTemp= NULL;
        }
        if(control == 'l')
            listagem_idh(lista1);

    }

    return 0;
}

