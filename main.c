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
    printf("%d\n", numarOperatii);
    TTren *tren = InitT();
    TCoadaOp *coadaOp = InitQ();

    char op[200];
    char val[10];
    for (int i = 0; i < numarOperatii; i++) {
        fscanf(in, "%s", op);
        printf("%s\n", op);
        if(strcmp(op, "SHOW_CURRENT") == 0){
             SHOW_CURRENT(tren, out);
        }else if(strcmp(op, "SHOW") == 0){
             SHOW(tren, out);
        }else if(strcmp(op, "SWITCH") == 0){
             SWITCH(coadaOp);
        }
        else if(strcmp(op, "EXECUTE") != 0){
            strcpy(val, "");
            fscanf(in, " %s\n", val);
            printf("Valoarea este:%s\n", val);
            IntrQ(coadaOp, op, val); /*Introducem in coada operatiile din fisier*/
        }
        if (strcmp(op, "EXECUTE") == 0) {
            EXECUTE(tren, coadaOp, out);
        }
    }
    //AfisareQ(coadaOp);
    //DistrQ(&coadaOp);
    fclose(in);
    fclose(out);
return 0;
}
