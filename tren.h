#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Structura unui vagon*/
typedef struct Vagon {
    char info;
    struct Vagon *urm;
    struct Vagon *pre;
} TVagon;

/*Structura unui tren*/
typedef struct Tren {
    TVagon* s; /* s - santinela */
    TVagon* mecanic; /* adresa mecanicului din trenulet*/
} TTren;

typedef struct Op{
    char op[200]; /*--array pentru stocarea denumirilor de operatii--*/
    char val[10]; /*--valoarea pe care o trimitem eventual in functii--*/
}TOp; /*--Structura care ne va stoca operatiile din fisier--*/

typedef struct ListaOp{
    TOp operation;
    struct ListaOp *pre;
    struct ListaOp *urm;
} TListaOp; /*--Lista dublu inlantuita care va stoca toate operatiile in coada--*/

typedef struct CoadaOp{
    struct ListaOp *inc;
    struct ListaOp *sf;
} TCoadaOp; /*--Coada care va stoca toate operatiile din fisier--*/

TCoadaOp* InitQ();
TTren* InitT();
int IntrQ(TCoadaOp *coadaOp, char *op, char *val);
void MOVE_LEFT(TTren *tren);
int MOVE_RIGHT(TTren *tren);
void WRITE(TTren *tren, char val);
void CLEAR_CELL(TTren *tren);
void CLEAR_ALL(TTren *tren);
void INSERT_LEFT(TTren *tren, FILE *out, char val);
void INSERT_RIGHT(TTren *tren, char val);
void SEARCH(TTren *tren, FILE *out, char *string);
void SEARCH_LEFT(TTren *tren, FILE *out, char *string);
void SEARCH_RIGHT(TTren *tren, FILE *out, char *string);
void SHOW_CURRENT(TTren *tren, FILE *out);
void SHOW(TTren *tren, FILE *out);
void SWITCH(TCoadaOp *coadaOp);
void EXECUTE(TTren *tren, TCoadaOp *coadaOp, FILE *out);
void DistrQ(TCoadaOp **coadaOp);
void DistrugeTren(TTren *tren);
