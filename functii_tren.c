/*--- Functiile implementate pentru UPDATE, SEARCH, QUERY AND EXECUTE----*/
#include "tren.h"

TVagon* AlocaCelula(char x){
    /*Functia care aloca o celula de tip TVagon*/
    TVagon* aux = (TVagon*)malloc(sizeof(TVagon));
    if(!aux) return NULL;
    aux->info = x;
    aux->urm = NULL;
    aux->pre = NULL;
    return aux;
}
TListaOp* AlocaOp(char *op, char *val){
    /*Functia care aloca o celula de tip TListaOp*/
    TListaOp* aux = (TListaOp*)malloc(sizeof(TListaOp));
    if(!aux) return NULL;
    /*Copiem sirurile de caractere pentru operatie si valori in valorile efective din structuri*/
    strcpy(aux->operation.op, op);
    strcpy(aux->operation.val, val);
    aux->pre = NULL;
    aux->urm = NULL;
    return aux;
}

TCoadaOp *InitQ(){
    /*Functia de initializare a cozii in care stocam operatiile*/
    TCoadaOp *coadaOp;
    coadaOp = (TCoadaOp*)malloc(sizeof(TCoadaOp));
    if(!coadaOp) return NULL;
    coadaOp->inc = NULL;
    coadaOp->sf = NULL;
    return coadaOp;
}

TTren *InitT(){
    /*Functia de initializare a Trenului si creeaza structura - |#| */
    TTren *tren;
    tren = (TTren*)malloc(sizeof(TTren));
    if(!tren) return NULL;
    tren->s = (TVagon*)malloc(sizeof(TVagon));
    if(!tren->s) {
        free(tren);
        return NULL;
    }
    TVagon* aux = AlocaCelula('#');
    if(!aux){
        free(tren->s);
        free(tren);
        return NULL;
    }

    tren->s->urm = aux;
    tren->s->pre = aux;
    aux->pre = tren->s;
    aux->urm = tren->s;
    tren->mecanic = aux;
    return tren;
}

void MOVE_LEFT(TTren *tren){
    /*Functia muta mecanicul in vagonasul din stanga*/
    if(tren && tren->mecanic){  
        if(tren->mecanic == tren->s->urm){ /*Verificam daca mecanicul se afla in primul vagon*/
            tren->mecanic = tren->s->pre; /*Daca mecanicul se afla in primul vagon atunci se muta in ultimul*/
        }
        else{
            /*In caz contrar, mecanicul va trece pe pozitia precedenta*/
            tren->mecanic = tren->mecanic->pre; 
        }
    }
}

int MOVE_RIGHT(TTren *tren){
    /*eroare la cuplare - return 0
      cuplare cu succes - return 1*/
    /*Functia creeaza un nou vagonas la dreopta si il muta pe macanic in acelasi vagonas*/
    if(tren && tren->mecanic){
        if(tren->mecanic == tren->s->pre){
            TVagon *aux = AlocaCelula('#');
            if(!aux) return 0;
            aux->urm = tren->s;
            aux->pre = tren->mecanic;
            tren->mecanic->urm = aux;
            tren->s->pre = aux;
            tren->mecanic = aux;
            return 1;
        }
        else{
            tren->mecanic = tren->mecanic->urm;
            return 1;
        }
    } else return 0;
}

void WRITE(TTren *tren, char val){
    if(tren && tren->mecanic){
        tren->mecanic->info = val;
    }
}

void CLEAR_CELL(TTren *tren){
    /*Functia elibereaza vagonasul in care se afla mecanicul*/
    if(tren && tren->mecanic){
        TVagon *aux;
        aux = tren->mecanic;
        /*Verificam daca trenul are un singur vagon*/
        if(aux->urm == tren->s && aux->pre == tren->s){
            free(aux);
            TVagon *aux = AlocaCelula('#');
            if(!aux) return;
            tren->s->urm = aux;
            tren->s->pre = aux;
            aux->urm = tren->s;
            aux->pre = tren->s;
            tren->mecanic = aux;
        }
        /*In caz contrar vom actualiza memoria si vom elibera aux*/
        else{
            aux->pre->urm = aux->urm;
            aux->urm->pre = aux->pre;
            /*Verificam daca in stanga se afla santinela- in caz afirmtiv mutam mecanicul in ultimul vagon*/
            if(aux->pre == tren->s){
                tren->mecanic = tren->s->pre;
            } else tren->mecanic = aux->pre;
            free(aux);
        }
    }
    else return;
}

void CLEAR_ALL(TTren *tren){
    /*Functia care va elibera vagoanele din tren si va initializa un tren nou*/
    if(tren){
        TVagon* p = tren->s->urm;
        TVagon* aux;
        while(p!=tren->s){
            aux = p;
            p = p->urm;
            free(aux);
        }
        aux = AlocaCelula('#');
        if(!aux) return;
        tren->s->urm = aux;
        tren->s->pre = aux;
        aux->urm = tren->s;
        aux->pre = tren->s;
        tren->mecanic = aux;
    }
    else return;
}

void INSERT_LEFT(TTren *tren, FILE *out, char val){
    /*Functia de inserare la stanga*/
    if(tren && tren->mecanic){
        if(tren->mecanic == tren->s->urm){
            fprintf(out, "ERROR\n");
        }else {
            TVagon* aux = AlocaCelula(val);
            if(!aux) return;
            aux->urm = tren->mecanic;
            aux->pre = tren->mecanic->pre;
            tren->mecanic->pre->urm = aux;
            tren->mecanic->pre = aux;
            tren->mecanic = aux;
        }
    }
}

void INSERT_RIGHT(TTren *tren, char val){
    /*Functia de inserare la dreapta*/
    if(tren && tren->mecanic) {
        TVagon* aux = AlocaCelula(val);
        if(!aux) return;
        //Daca mecanicul se afla in ultimul vagon 
        if(tren->mecanic->urm == tren->s){
            aux->pre = tren->mecanic;
            aux->urm = tren->s;
            tren->mecanic->urm = aux;
            tren->s->pre = aux;
            tren->mecanic = aux;
        }
        else{
            aux->pre = tren->mecanic;
            aux->urm = tren->mecanic->urm;
            tren->mecanic->urm->pre = aux;
            tren->mecanic->urm = aux;
            tren->mecanic = aux;
        }
    }
    else return;
}

void SEARCH(TTren *tren, FILE *out, char *string){
    if(tren && tren->mecanic){
        TVagon *aux = tren->mecanic; 
        TVagon *inc;
        int i, k;
        k = strlen(string);
        i = 0;
        do{
            if(aux->info == string[i]){
                /*cand i = 0, deci ne aflam la inceputul sirului si il memorizam intr-o variabila inc*/
                if(i == 0){
                    inc = aux;
                }
                i++;
                
                if(i == k){
                    tren->mecanic = inc; /*mecanicul se va afla la inceputul sirului in caz ca a fost gasit sirul*/
                    return;
                }
            } else {
                i = 0; /* Daca sirul nu a fost gasit si lista nu a fost parcursa complet atunci i va devine din nou 0
                          pentru a parcurge inca o data sirul*/
                /*Verificam daca celula aux curenta nu coincide cu caracterul sirului si setam inceputul 
                  la aux si incrementam i pentru a trece la urmatoarea celula*/
                if(aux->info == string[i]){
                    inc = aux;
                    i++;
                } else inc = NULL; /*Resetam inceputul sirului gasit la NULL*/

            }
            aux = aux->urm; /*Avansam la urmatoarea celula pornind cu t->mecanic pana ne intoarcem inapoi*/
            /*Daca aux este santinela trenului atunci trebuie sa trecem la urmatorul vagon*/
            if (aux == tren->s){
                aux = tren->s->urm;
            }
        }while(aux != tren->mecanic);
        fprintf(out, "ERROR\n");
    }
    else return;
}

void SEARCH_LEFT(TTren *tren, FILE *out, char *string){
    printf("Funcția SEARCH a primit șirul: '%s'\n", string);
    if(tren && tren->mecanic){
        TVagon *aux = tren->mecanic; /*Pornim cautarea de la vagonul cu mecanic*/
        int k = strlen(string);
        int i = 0; 
        /*Facem search la stanga prin trenulet pana ajungem la santinela*/
        do{
            if(aux->info == string[i]){
                i++;
                /*Daca i va ajunge la valoarea lungimii string-ului mecanicul va puncta la inceputul secventei
                    aux va ajunge la sfarsitul ciclului si va indica pozitia mecanicului*/
                if(i == k){
                    tren->mecanic = aux;
                    return;
                }
            } else {
                /*Daca nu gasim sirul si nu am parcurs pana la intalnirea santinele il resetam pe i*/
                i = 0;
            }
            aux = aux->pre;
        } while(aux != tren->s);
        fprintf(out, "ERROR\n");
    } else return;
}

void SEARCH_RIGHT(TTren *tren, FILE *out, char *string){
    if(tren && tren->mecanic){
        TVagon *aux = tren->mecanic; /*Setam aux la vagonul unde era mecanicul*/
        int k = strlen(string);
        int i = 0;
        /*Facem search la dreapta prin trenulet pana ajungem la santinela*/
        do{
            if(aux->info == string[i]){
                i++;
                if(i == k){
                    /*Daca i va ajunge la valoarea lungimii string-ului mecanicul va puncta la inceputul secventei
                    aux va ajunge la sfarsitul ciclului si va indica pozitia mecanicului*/
                    tren->mecanic = aux;
                    return;
                }
            }else{
                i = 0;
            }
            aux = aux->urm;
        }while(aux != tren->s);
        fprintf(out, "ERROR\n");
    } else return;
}

void SHOW_CURRENT(TTren *tren, FILE *out){
    /*Functia SHOW CURRENT ne va afisa caracterul din vagonul mecanicului*/
    if(tren && tren->mecanic){
        fprintf(out,"%c\n", tren->mecanic->info);
    }
    else return;
}

void SHOW(TTren *tren, FILE *out){
    if(tren && tren->mecanic){
        TVagon *aux;
        for(aux = tren->s->urm; aux != tren->s; aux = aux->urm){
            if(aux == tren->mecanic){ /*Daca ajungem la vagonul cu mecanic vom afisa |info|*/
                fprintf(out, "|%c|",tren->mecanic->info);
            } else {
                fprintf(out, "%c", aux->info);
            }
        }
        fprintf(out,"\n");
    }
}

int IntrQ(TCoadaOp *coadaOp, char *op, char *val){
    /*Functia IntrQ va intoarce 1 in cazul unei introduceri reusite si 0 in caz de esec*/
    TListaOp *aux = AlocaOp(op, val);
    if(!coadaOp ->inc && !coadaOp->sf){
        aux->pre = NULL;
        aux->urm = NULL;
        coadaOp->inc = aux;
        coadaOp->sf = aux;
    } else {
        aux->pre = coadaOp->sf;
        coadaOp->sf->urm = aux;
        coadaOp->sf = aux;
    }
    return 1;
}

void SWITCH(TCoadaOp *coadaOp){
    /*Functia SWITCH ne va inversa operatiile din coada*/
    if(coadaOp->inc && coadaOp->sf && coadaOp->inc != coadaOp->sf){
        TListaOp *aux = coadaOp->inc;
        TListaOp *p = NULL;

        /*Pentru a inversa coada inversam, initial, inceputul cu sfarsitul cozii folosind o variabila p*/
        p = coadaOp->inc;
        coadaOp->inc = coadaOp->sf;
        coadaOp->sf = p;

        while(aux != NULL){
            p = aux->urm; /*Initial p va indica spre urmatorul element al cozii de la fostul inceput al cozii*/
            aux->urm = aux->pre; /*Inversam cu locul elementul urmator cu cel precedent*/
            aux->pre = p; 
            aux = p;
        }
    }
}

void EXECUTE(TTren *tren, TCoadaOp *coadaOp, FILE *out){
    /*Daca intalnim comanda EXECUTE atunci executam pe rand operatiile din coada*/
    /*Odata ce am executat operatiunea, o eliminam din coada*/
    if(!coadaOp->inc && !coadaOp->sf) return;
    TListaOp *aux = coadaOp->inc; /*Extragem inceputul cozii */
    coadaOp->inc = coadaOp->inc->urm; /*Setam inceputul la urmatoarea celula*/
    if(coadaOp->inc == NULL){
        /*In caz ca coada devine NULA*/
        coadaOp->sf = NULL;
    } else{
        coadaOp->inc->pre = NULL;
    }

    if(strcmp(aux->operation.op, "MOVE_LEFT") == 0){
        MOVE_LEFT(tren);
    } else if(strcmp(aux->operation.op, "MOVE_RIGHT") == 0){
        MOVE_RIGHT(tren);
    } else if(strcmp(aux->operation.op, "WRITE") == 0){
        WRITE(tren, *aux->operation.val);
    } else if(strcmp(aux->operation.op, "CLEAR_CELL") == 0){
        CLEAR_CELL(tren);
    } else if(strcmp(aux->operation.op, "CLEAR_ALL") == 0){
        CLEAR_ALL(tren);
    } else if(strcmp(aux->operation.op, "INSERT_LEFT") == 0){
        INSERT_LEFT(tren, out, *aux->operation.val);
    } else if(strcmp(aux->operation.op, "INSERT_RIGHT") == 0){
        INSERT_RIGHT(tren, *aux->operation.val);
    } else if(strcmp(aux->operation.op, "SEARCH") == 0){
        SEARCH(tren, out, aux->operation.val);
    } else if(strcmp(aux->operation.op, "SEARCH_LEFT") == 0){
        SEARCH_LEFT(tren, out, aux->operation.val);
    } else if(strcmp(aux->operation.op, "SEARCH_RIGHT") == 0){
        SEARCH_RIGHT(tren, out, aux->operation.val);
    }
    free(aux);
}

void DistrQ(TCoadaOp **coadaOp) /* distrugem coada */
{
  (*coadaOp)->inc = NULL;
  (*coadaOp)->sf = NULL;
  free(*coadaOp);
}

void DistrugeTren(TTren **tren){
    /*Verificam daca trenul este NULL*/
    if(*tren == NULL) return;
    TVagon *aux = (*tren)->s->urm;
    TVagon *p;
    while(aux != (*tren)->s){
        p = aux->urm;
        free(aux);
        aux = p;
    }
    free((*tren)->s);
    free(*tren);
}
