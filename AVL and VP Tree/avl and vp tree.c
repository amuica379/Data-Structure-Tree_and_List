#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a)>(b)?(a):(b))


int rotAVL;
int rotVP;

//Aluno: Guilherme Carvalho Caria

typedef struct tipoAVL{
    int chave;
    int altura;
    struct tipoAVL *dir;
    struct tipoAVL *esq;
}nodeAVL;

typedef struct tipoVP{
    int chave;
    int cor; // 1= vermelho, 0= preto, -1= double black;
    struct tipoVP *dir;
    struct tipoVP *esq;
    struct tipoVP *pai;
}nodeVP;

typedef struct tipoFL{
    nodeAVL *pAVL;
    nodeVP *pVP;
    struct tipoFL *prox;
}nodeQ;

nodeAVL *rootAVL;
nodeVP *rootVP;
nodeQ *rootQ;

void inicializa(){
    rootAVL=NULL;
    rootVP=NULL;
    rootQ=NULL;
}

void read(int *qtd_chaves, int **assign, int* safety){
    int *input= malloc(sizeof(int)*(*qtd_chaves));
    FILE *fpointer;
    fpointer = fopen("incluir.txt", "r");
    int c=0;
    int numeros_no_arquivo=0;
    while(!feof(fpointer)){
        if(c>=(*qtd_chaves))
            break;
        fscanf(fpointer, "%d", &input[c]);
        c++;
        numeros_no_arquivo++;
    }
    fclose(fpointer);
    (*assign)=input;
    *safety= numeros_no_arquivo;
}

void Rread(int **assign, int *safety){
    FILE *fpointer;
    FILE *fptr;
    fpointer = fopen("remover.txt", "r");
    int numeros_no_arquivo=0;
    int aux=0;
    int lixo;
    while(!feof(fpointer)){
        fscanf(fpointer, "%d", &lixo);
        numeros_no_arquivo++;
    }
    fclose(fpointer);
    fptr = fopen("remover.txt", "r");
    int *input= malloc(sizeof(int)*(numeros_no_arquivo));
    while(!feof(fptr)){
        fscanf(fptr, "%d", &input[aux]);
        if(aux==numeros_no_arquivo)
            break;
        aux++;
    }
    fclose(fptr);
    (*assign)=input;
    *safety= numeros_no_arquivo;
}

void Eread(int **assign, int *safety){
    FILE *fpointer;
    FILE *fptr;
    fpointer = fopen("experimento.txt", "r");
    int numeros_no_arquivo=0;
    int aux=0;
    int lixo;
    while(!feof(fpointer)){
        fscanf(fpointer, "%d", &lixo);
        numeros_no_arquivo++;
    }
    fclose(fpointer);
    fptr = fopen("experimento.txt", "r");
    int *input= malloc(sizeof(int)*(numeros_no_arquivo));
    while(!feof(fptr)){
        fscanf(fptr, "%d", &input[aux]);
        if(aux==numeros_no_arquivo)
            break;
        aux++;
    }
    fclose(fptr);
    (*assign)=input;
    *safety= numeros_no_arquivo;
}

nodeAVL* novoAVL(key){
    nodeAVL *temp= malloc(sizeof(nodeAVL));
    temp->chave= key;
    temp->esq=temp->dir=NULL;
    temp->altura= 0;
    return temp;
}

nodeAVL* rotacao_dir(nodeAVL *nor){
    nodeAVL *aux= nor->esq;
    nor->esq= aux->dir;
    aux->dir=nor;
    nor->altura= MAX(qual_altura(nor->esq), qual_altura(nor->dir))+1;
    aux->altura= MAX(qual_altura(aux->esq), qual_altura(aux->dir))+1;
    rotAVL++;
    return aux;
}

nodeAVL* rotacao_esq(nodeAVL *nor){
    nodeAVL *aux= nor->dir;
    nor->dir= aux->esq;
    aux->esq= nor;
    nor->altura=MAX(qual_altura(nor->esq), qual_altura(nor->dir))+1;
    aux->altura=MAX(qual_altura(aux->esq), qual_altura(aux->dir))+1;
    rotAVL++;
    return aux;
}

int AlturaNo_calc(nodeAVL *root, int Rkey){
    int levels=0;
    nodeAVL *aux= root;
    while(1){
        if(aux==NULL){
            break;
        }
        else
            if(Rkey<aux->chave){
                aux= aux->esq;
                levels++;
                continue;
            }
            if(Rkey>aux->chave){
                aux= aux->dir;
                levels++;
                continue;
            }
            if(Rkey==aux->chave){
                aux->altura= levels;
                break;
            }
    }
    return levels;
}

int altura_arvore_VP(nodeVP *root){
    if(root==NULL)
        return -1;
    int altura_esq= altura_arvore_VP(root->esq);
    int altura_dir= altura_arvore_VP(root->dir);
    return MAX(altura_esq, altura_dir)+1;
}

int qual_altura(nodeAVL *x){
    if(x==NULL)
        return-1;
    else
        return x->altura;
}

int fator_balanceamento(nodeAVL *node){
    if(node==NULL)
        return 0;
    return (qual_altura(node->esq))-(qual_altura(node->dir));
}

nodeAVL* find_smaller(nodeAVL *root){
    nodeAVL* aux= root;
    while(aux->esq!=NULL){
        aux=aux->esq;
    }
    return aux;
}

nodeVP* find_smaller_VP(nodeVP *root){
    nodeVP* aux= root;
    while(aux->esq!=NULL){
        aux=aux->esq;
    }
    return aux;
}

nodeAVL* remove_AVL(nodeAVL *root, int Rkey){
    if(root==NULL)
        return root;
    else
        if(Rkey<root->chave)
            root->esq=remove_AVL(root->esq, Rkey);
        else
            if(Rkey>root->chave)
                root->dir=remove_AVL(root->dir, Rkey);
        else
            if(Rkey==root->chave){
                if(root->esq==NULL && root->dir==NULL){
                    free(root);
                    root= NULL;
                    return root;
                }
                else
                    if(root->esq==NULL){
                        nodeAVL *aux= root;
                        root=root->dir;
                        free(aux);
                        return root;
                    }
                    else
                        if(root->dir==NULL){
                            nodeAVL *aux=root;
                            root=root->esq;
                            free(aux);
                            return root;
                        }
                    else{
                        nodeAVL *aux= find_smaller(root->dir);
                        root->chave= aux->chave;
                        root->dir=remove_AVL(root->dir, aux->chave);
                    }
            }
    if(root==NULL)
        return root;
    root->altura=MAX(qual_altura(root->esq),qual_altura(root->dir))+1;
    int FB= fator_balanceamento(root);
    int FB_child;
        if(FB==2){
            FB_child= fator_balanceamento(root->esq);
            if(FB_child==-1){
                root->esq=rotacao_esq(root->esq);
                root=rotacao_dir(root);
            }
            else
                root=rotacao_dir(root);
        }
        if(FB==-2){
            FB_child= fator_balanceamento(root->dir);
            if(FB_child==-1)
                root=rotacao_esq(root);
            else
            if(FB_child==1){
                    root->dir= rotacao_dir(root->dir);
                    root=rotacao_esq(root);
            }
        }
    return root;
}

nodeAVL* insere_AVL(nodeAVL *root, int Rkey){
        if(root==NULL){
            root= novoAVL(Rkey);
        }
            if(Rkey<root->chave)
                root->esq= insere_AVL(root->esq, Rkey);

            else
                if(Rkey>root->chave)
                    root->dir= insere_AVL(root->dir, Rkey);
                else
                    return root;
        root->altura= MAX(qual_altura(root->esq), qual_altura(root->dir))+1;
        int FB= fator_balanceamento(root);
        int FB_child;
        if(FB==2){
            FB_child= fator_balanceamento(root->esq);
            if(FB_child==-1){
                root->esq=rotacao_esq(root->esq);
                root=rotacao_dir(root);
            }
            else
                root=rotacao_dir(root);
        }
        if(FB==-2){
            FB_child= fator_balanceamento(root->dir);
            if(FB_child==-1)
                root=rotacao_esq(root);
            else
            if(FB_child==1){
                    root->dir= rotacao_dir(root->dir);
                    root=rotacao_esq(root);
            }
        }
        return root;
    }

void empilha_AVL(nodeAVL *emp){
    nodeQ *aux=rootQ;
    if(rootQ==NULL){
        rootQ=malloc(sizeof(nodeQ));
        rootQ->pAVL=emp;
        rootQ->prox=NULL;
        aux=rootQ;
    }
    else{
        while(aux->prox){
            aux=aux->prox;
        }
    }
    aux->prox=malloc(sizeof(nodeQ));
    aux=aux->prox;
    aux->pAVL=emp;
    aux->prox=NULL;
}

nodeQ* desempilha(nodeQ *rootQ){
    nodeQ *aux=rootQ;
    if(aux==NULL)
        return;
    else
     rootQ=rootQ->prox;
     free(aux);
     return rootQ;
}

void imprime_nivel_AVL(nodeAVL *root){
    printf("Arvore AVL impressa por nivel (Chave, Altura): \n");
    if(root==NULL)
        return;
    nodeAVL *aux=root;
    int node_count_current_level=1;
    int node_count_next_level=0;
    while(1){
        printf("(%d, %d) ", aux->chave, aux->altura);
        node_count_current_level--;
        if(aux!=NULL){
            if(aux->esq!=NULL){
                empilha_AVL(aux->esq);
                node_count_next_level++;
            }
            if(aux->dir!=NULL){
                empilha_AVL(aux->dir);
                node_count_next_level++;
            }
        }
        if(node_count_current_level==0){
            printf("\n");
            node_count_current_level= node_count_next_level;
            node_count_next_level=0;
        }
       rootQ=desempilha(rootQ);
       if(rootQ==NULL)
        break;
        aux=rootQ->pAVL;
    }
}

nodeVP* novoVP(nodeVP *novo){
    nodeVP *temp= malloc(sizeof(nodeVP));
    temp->cor= 1;
    temp->pai= NULL;
    temp->dir=temp->esq= NULL;
    return temp;
}

void rotacao_esqVP(nodeVP *root, nodeVP *novo){
    nodeVP *aux = novo->dir;
    novo->dir=aux->esq;
    if(novo->dir!= NULL)
        novo->dir->pai=novo;
    aux->pai=novo->pai;
    if(novo->pai==NULL)
        rootVP=aux;
    else
        if(novo==novo->pai->esq)
            novo->pai->esq=aux;
    else
        novo->pai->dir=aux;
    aux->esq=novo;
    novo->pai=aux;
    rotVP++;
}

void rotacao_dirVP(nodeVP *root, nodeVP *novo){
    nodeVP *aux= novo->esq;
    novo->esq=aux->dir;
    if(novo->esq!=NULL)
        novo->esq->pai=novo;
    aux->pai=novo->pai;
    if(novo->pai==NULL)
        rootVP=aux;
    else
        if(novo==novo->pai->esq)
            novo->pai->esq=aux;
    else
        novo->pai->dir=aux;
    aux->dir= novo;
    novo->pai=aux;
    rotVP++;
}

nodeVP* insere_VP_BST(nodeVP *root, nodeVP *novo){
    if(root==NULL){
            return novo;
        }
            if(novo->chave<root->chave){
                root->esq= insere_VP_BST(root->esq, novo);
                root->esq->pai=root;
            }
            else
                if(novo->chave>root->chave){
                    root->dir= insere_VP_BST(root->dir, novo);
                    root->dir->pai=root;
                }
    return root;
}

void consertaVP(nodeVP *root, nodeVP *novo){
    while((novo!= rootVP) && (novo->pai->cor == 1) && (novo->cor!=0)){
        nodeVP *pai= novo->pai;
        nodeVP *avo= novo->pai->pai;
        if(novo->pai == avo->esq){
            nodeVP *tio= avo->dir;
            if(tio!=NULL && tio->cor==1){
                pai->cor=0;
                tio->cor=0;
                avo->cor=1;
                novo= avo;
            }
            else{
                if(novo ==  pai->dir){
                    rotacao_esqVP(root, pai);
                    novo=pai;
                    pai=novo->pai;
                }
                rotacao_dirVP(root, avo);
                int colorAUX= pai->cor;
                pai->cor=avo->cor;
                avo->cor=colorAUX;
                novo=novo->pai;
            }
        }
        else{
                nodeVP *tio= avo->esq;
                if(tio!=NULL && tio->cor==1){
                    pai->cor=0;
                    tio->cor=0;
                    avo->cor=1;
                    novo=avo;
                }
                else{
                    if(novo == pai->esq){
                        rotacao_dirVP(root, pai);
                        novo=pai;
                        pai=novo->pai;
                    }
                    rotacao_esqVP(root, avo);
                    int colorTEMP=pai->cor;
                    pai->cor=avo->cor;
                    avo->cor=colorTEMP;
                    novo=pai;
                }
            }
        }
    rootVP->cor= 0;
    }

void empilha_VP(nodeVP *emp){
    nodeQ *aux=rootQ;
    if(rootQ==NULL){
        rootQ=malloc(sizeof(nodeQ));
        rootQ->pVP=emp;
        rootQ->prox=NULL;
        aux=rootQ;
    }
    else{
        while(aux->prox){
            aux=aux->prox;
        }
    }
    aux->prox=malloc(sizeof(nodeQ));
    aux=aux->prox;
    aux->pVP=emp;
    aux->prox=NULL;
}

void imprime_nivel_VP(nodeVP *root){
    printf("Arvore Vermelho-Preto impressa por nivel (Chave, Cor):\n");
    if(root==NULL)
        return;
    nodeVP *aux=root;
    int node_count_current_level=1;
    int node_count_next_level=0;
    while(1){
        if(aux->cor==1)
            printf("(%d, V) ", aux->chave);
        if(aux->cor==0)
            printf("(%d, P) ", aux->chave);
        node_count_current_level--;
        if(aux!=NULL){
            if(aux->esq!=NULL){
                empilha_VP(aux->esq);
                node_count_next_level++;
            }
            if(aux->dir!=NULL){
                empilha_VP(aux->dir);
                node_count_next_level++;
            }
        }
        if(node_count_current_level==0){
            printf("\n");
            node_count_current_level= node_count_next_level;
            node_count_next_level=0;
        }
       rootQ=desempilha(rootQ);
       if(rootQ==NULL)
        break;
        aux=rootQ->pVP;
    }
}

void inserirVP(int Rkey){
    nodeVP *novo=novoVP(novo);
    novo->chave= Rkey;
    rootVP= insere_VP_BST(rootVP, novo);
    consertaVP(rootVP, novo);
}

/*nodeVP* remove_VP_BST(nodeVP *root, int Rkey){    //Incompleto
    if(root==NULL)
        return root;
    else
        if(Rkey<root->chave)
            root->esq=remove_VP_BST(root->esq, Rkey);
        else
            if(Rkey>root->chave)
                root->dir=remove_VP_BST(root->dir, Rkey);
        else
            if(Rkey==root->chave){
                if(root->esq==NULL && root->dir==NULL){
                        if(root->pai!=NULL){
                            if((root->cor=0 && root->pai->cor==1)){
                                root->pai->cor==0;
                            }
                        }
                    free(root);
                    root= NULL;
                    return root;
                }
                else
                    if(root->esq==NULL){
                        nodeVP *aux= root;
                        root->dir->pai=root->pai;
                        root=root->dir;
                        free(aux);
                        return root;
                    }
                    else
                        if(root->dir==NULL){
                            nodeVP *aux=root;
                            root->esq->pai=root->pai;
                            root=root->esq;
                            free(aux);
                            return root;
                        }
                    else{
                        nodeVP *aux= find_smaller_VP(root->dir);
                        root->chave= aux->chave;
                        root->dir=remove_VP_BST(root->dir, aux->chave);
                    }
            }
    return root;
}

void consertaVP_del(nodeVP *root){    //Incompleto

}

void remove_VP(int Rkey){     //Incompleto
    if(rootVP==NULL)
        return;
    rootVP=remove_VP_BST(rootVP, Rkey);
    consertaVP_del(rootVP);
}*/

void free_AVL_tree(nodeAVL *root){
    if(root==NULL)
        return;
    free_AVL_tree(root->esq);
    free_AVL_tree(root->dir);
    free(root);
}

void free_VP_tree(nodeVP *root){
    if(root==NULL)
        return;
    free_VP_tree(root->esq);
    free_VP_tree(root->dir);
    free(root);
}

void experimento(nodeAVL *rootA, nodeVP *rootV){
    rotAVL= 0;
    rotVP= 0;
    int *vetchavesE;
    int safety;
    Eread(&vetchavesE, &safety);
    int i;
    if(rootAVL!=NULL){
                free_AVL_tree(rootAVL);
                if(rootVP!=NULL){
                    free_VP_tree(rootVP);
                    inicializa();
                }
            }
    for(i=0; i<safety; i++){
        rootAVL= insere_AVL(rootAVL, vetchavesE[i]);
        inserirVP(vetchavesE[i]);
    }
    int alturaVP= altura_arvore_VP(rootVP);
    printf("Experimento na arvore AVL (Altura, numero de rotacoes)\n");
    printf("(%d, %d)\n", rootAVL->altura, rotAVL);
    printf("Experimento na arvore Vermelho preto (Altura, numero de rotacoes)\n");
    printf("(%d, %d)\n", alturaVP, rotVP);

}


    char op;
int main(){
    inicializa();
    int n;
    int safety;
    int Rsafety;
    int *rotAVL, *rotVP;
    printf("OBS: 'F' finaliza o programa\n");
    while(1){
        scanf("%c", &op);
        if(op=='I'){
            if(rootAVL!=NULL){
                free_AVL_tree(rootAVL);
                if(rootVP!=NULL){
                    free_VP_tree(rootVP);
                    inicializa();
                }
            }
            scanf("%d", &n);
            int *vetchaves;
            read(&n, &vetchaves, &safety);
            int i;
            for(i=0; i<safety; i++){
                rootAVL= insere_AVL(rootAVL, vetchaves[i]);
                inserirVP(vetchaves[i]);
            }
        }
        if(op=='R'){
            int *vetchavesR;
            Rread(&vetchavesR, &safety);
            int j;
            for(j=0; j<safety; j++){
                remove_AVL(rootAVL, vetchavesR[j]);
                //remove_VP(rootVP); Incompleto
            }
        }
        if(op=='P'){
            imprime_nivel_AVL(rootAVL);
            printf("\n");
            imprime_nivel_VP(rootVP);
        }
        if(op=='E'){
            experimento(rootAVL, rootVP);
        }
        if(op=='F')
            break;
    }
    return 0;
}
