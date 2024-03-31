#include <stdio.h>
#include <stdlib.h>

/*Structura unui vagon*/
typedef struct celula{
    char info;
    struct celula *urm;
    struct celula *pre;
}TCelula, *Tlista;

/*Structura unui tren*/
typedef struct tren{
    TLista s; /* s - santinela */
    TLista mecanic; /* adresa mecanicului din trenulet*/
}TTren;

typedef struct coada {
    TLista inc; /*adresa primei celule*/
    TLista sf; /*adresa ultimei celule*/
}TCoada;

TTren* InitT();
TCoada* InitQ ();   
