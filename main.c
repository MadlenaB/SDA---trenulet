#include "tren.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *in = fopen("tema1.in","r");
    FILE *out = fopen("tema1.out","w");
    if(in == NULL){
        printf("File inexistent\n");
        return 1;
    }
    int numarOperatii = 0;
    fscanf(in, "%d\n", &numarOperatii);
    TTren *tren = InitT();
    TCoadaOp *coadaOp = InitQ();

    char op[200];
    char val[10];
    for (int i = 0; i < numarOperatii; i++) {
        fscanf(in, "%s", op);
        if(strcmp(op, "EXECUTE") == 0){
            EXECUTE(tren, coadaOp, out);
        } else if(strcmp(op, "SHOW_CURRENT") == 0){
             SHOW_CURRENT(tren, out);
        } else if(strcmp(op, "SHOW") == 0){
             SHOW(tren, out);
        } else if(strcmp(op, "SWITCH") == 0){
             SWITCH(coadaOp);
        }
        else{
            if(strcmp(op, "MOVE_RIGHT") == 0 || strcmp(op, "MOVE_LEFT") == 0 || strcmp(op, "CLEAR_CELL") == 0
                || strcmp(op, "CLEAR_ALL") == 0){
                    val[0] = '\0';
                    IntrQ(coadaOp, op, val);
                }
            else{
                fscanf(in, "%s\n", val);
                IntrQ(coadaOp, op, val); /*Introducem in coada operatiile din fisier*/
            }
            
        }
        //AfisareQ(coadaOp);
    }
    DistrQ(&coadaOp);
    DistrugeTren(&tren);
    fclose(in);
    fclose(out);
return 0;
}
