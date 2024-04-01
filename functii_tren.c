/*--- Functiile implementate pentru UPDATE, SEARCH, QUERY AND EXECUTE----*/
#include "tren.h"

TLista AlocaCelula(char x){
    TLista aux = (TLista)malloc(sizeof(TCelula));
    if(!aux) = return NULL;
    aux->info = x;
    aux->urma = NULL;
    return aux;
}
TTren* InitT(){
    TTren *t; /* t - va fi trenuletul nostru - o lista circulara dubla inlantuita */
    t = (TTren*)malloc(sizeof(TTren));
    if( !t ) return NULL;  
    TLista *s = (TLista)malloc(sizeof(TLista));
    if( !s ) return NULL;
    TLista aux = AlocaCelula(#);
    t->s->info = 0;
    t->s->urm = aux;
    t->s->pre = aux;
    aux->urm = t->s;
    aux->pre = t->s;
    t->mecanic = t->s;
    return t;
}

TCoada* InitQ(){
    TCoada *c;
    c = (TCoada*)malloc(sizeof(TCoada));
    c->inc = NULL;
    c->sf = NULL;
    return c; 
}

//int InsertOperationQue(Tcoada *c, )
//void MOVE_LEFT(TTrain t, TCoada c )
