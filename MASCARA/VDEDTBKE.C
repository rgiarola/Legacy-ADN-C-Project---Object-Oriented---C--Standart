#include<INCVIDEO.H>

VD_VOID VIDEO_EDITA_mascara_bakcar(mascara,bflocal,posbuffer,posmascara,
                                   fim,coli,col,lin,cor,flagmostra)
char    *mascara,
        *bflocal;
INT2     *posbuffer,*posmascara,
        *fim      ,coli       ,
        *col      ,lin        ;
BYTE    cor;
WORD    flagmostra;
{
 INT2 tam;
 if (!*posbuffer)
    return;
 tam = strlen(bflocal+*posbuffer)+1;
 VIDEO_copbloco(bflocal+(*posbuffer)-1,bflocal+(*posbuffer),tam);
 VIDEO_display_mascara(coli,lin,bflocal,mascara,cor,TRUE,flagmostra);
 VIDEO_EDITA_mascara_posiciona(mascara,bflocal,coli,col,*posbuffer-1);
 --*posbuffer;
 --*fim;
 *posmascara = *col - coli;
}

