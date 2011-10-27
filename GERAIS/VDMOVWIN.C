#include <INCVIDEO.H>

INT2 VIDEO_mvwindow(coli,colf,lini,linf,numcol,numlin,vetor,cor)
INT2  coli,  colf,
     lini,  linf,
     numcol,numlin,
     vetor;
BYTE cor;
{
 VD_VOID *buffer;

    if (VIDEO_ALLOC_MEM(buffer,(linf-lini+1)*(colf-coli+1)*2) == VD_NULO)
       return(FALSE);

    VIDEO_opertela(coli,colf,lini,linf,buffer,
                  ((vetor&VIDEO_OPER_QUADRO)?VIDEO_LEITURA:VIDEO_LERATRIB));

    if ((vetor&VIDEO_MOVE) && (vetor&VIDEO_OPER_QUADRO))
        VIDEO_CLEAR_PIC(coli,colf,lini,linf,cor);

    if (vetor & VIDEO_MV_ESQUERDA)
       {
        coli -= numcol,
        colf -= numcol;
       }

    if (vetor & VIDEO_MV_DIREITA)
       {
        coli += numcol,
        colf += numcol;
       }

    if (vetor & VIDEO_MV_CIMA)
       {
        lini -= numlin,
        linf -= numlin;
       }

    if (vetor & VIDEO_MV_BAIXO)
       {
        lini += numlin,
        linf += numlin;
       }
    VIDEO_opertela(coli,colf,lini,linf,buffer,
                  (vetor&VIDEO_OPER_QUADRO)?VIDEO_GRAVACAO:VIDEO_GRVATRIB);
#ifdef VIDEO_UNIX
    VIDEO_UNIX_refresh_tela();
#endif
 VIDEO_FREE_ALLOC_MEM(buffer);
 return(TRUE);
}

