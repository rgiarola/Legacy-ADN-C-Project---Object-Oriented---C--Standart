#include<INCVIDEO.H>

VD_VOID VIDEO_EDITA_mascara_delcar(mascara,bflocal,fim,pos,col,lin,cor,flagmostra)
char    *mascara,
        *bflocal;
INT2     *fim,pos,
        col ,lin;
BYTE    cor;
WORD    flagmostra;
{
 INT2 tam;
 if ((tam = strlen(bflocal+pos)) == 0)
    return;
 VIDEO_copbloco(bflocal+pos,bflocal+pos+1,tam);
 VIDEO_display_mascara(col,lin,bflocal,mascara,cor,TRUE,flagmostra);
 --*fim;
}

