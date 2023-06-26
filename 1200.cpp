#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct n
{
    char num;
    struct n *esq, *dir;
};

typedef struct n No;

void insere(No *Pai, int elem){
    No*tmp;
    No *novo = (No*) malloc(sizeof(No));
    tmp = Pai;
    novo->num = elem;
    novo->esq = NULL;
    novo->dir = NULL;
    while(tmp!=NULL){
        //printf("oi\n");
        if(elem > (int)(tmp->num)){
            if(tmp->dir != NULL) tmp = tmp->dir;else break;
        }else
        {
            if(tmp->esq != NULL) tmp = tmp->esq;else break;
        }
    }
    if(elem< (int)(tmp->num)) tmp->esq = novo;else
        tmp -> dir = novo;
    //printf("ELEM: %d\n", elem);
}

void printe_pre(No *Pai, int c){
    if(Pai!=NULL){
        if(c>0) printf(" %c", Pai->num); else if(c==0) printf("%c", Pai->num);
        c++;
        printe_pre(Pai->esq, c);
        printe_pre(Pai->dir, c);
    }
}

int printe_in(No *Pai, int c){
    if(Pai!=NULL){
        c+=printe_in(Pai->esq, c);
        //printf("oi %d\n", c);
        if(c==1) c++;
        if(c>0) printf(" %c", Pai->num); else if(c==0) printf("%c", Pai->num);
        c++;
        //printf("\noioi %d\n", c);
        c+=printe_in(Pai->dir, c);
        return c;
    }
}

int printe_pos(No *Pai, int c){
    if(Pai!=NULL){
        c+=printe_pos(Pai->esq, c);
        c+=printe_pos(Pai->dir, c);
        if(c>0) printf(" %c", Pai->num); else if(c==0) printf("%c", Pai->num);
        return c+1;
    }
}

int busca(No *Pai, char elem){
    int a, b;
    if(Pai!=NULL){
        a = busca(Pai->esq, elem);
        if((Pai->num)==elem) return 1;
        b = busca(Pai->dir, elem);
        if(a!=1&&b!=1) return 0;else return 1;
    }
}

main()
{
    No *Pai = (No*) malloc(sizeof(No));
    Pai->esq = NULL;
    Pai->dir = NULL;
    Pai->num = 0;
    char aux, op, str[10], el;
    int x, y, z, c;
    int i;
    c=0;
    while(gets(str)!=NULL){
        z = strlen(str);
        if(z==3) i = 0;else i = 1;
        if(i==0){
            aux = str[0];
            el = str[2];
            if(aux=='I') {
                if(c>0)insere(Pai, (int)el);
                else Pai->num = el;// insere na raiz da arvore
                c=1;
            }else
            if(aux=='P')
            {
                if(Pai->num!=0){
                    y = busca(Pai, el);
                    if(y==1) printf("%c existe\n", el);else printf("%c nao existe\n", el);
                }else printf("%c nao existe\n", el);/*aqui seria para caso a operação 'P' aparecesse 
                                                              na primeira linha, mas isso nunca acontece então nao faz diferença*/
            }
        }else
        {
            if(Pai->num!=0){
                if(strcmp(str, "INFIXA")==0) printe_in(Pai, 0);else
                if(strcmp(str, "PREFIXA")==0) printe_pre(Pai, 0);else
                if(strcmp(str, "POSFIXA")==0) printe_pos(Pai, 0);
                //printf(", ,");
                printf("\n");
            }
        }
        strcpy(str, ""); //"zera" a string
    }
    //printf("\n");
}
