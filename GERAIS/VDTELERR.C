/* ============================================================================
   EXIBE TELA DE STATUS DE ERRO.
   PARAMETROS:
   xi       - Coluna Referencia Inicial.
   yi       - Linha Referencia Inicial.
   mens     - Mensagem de Exibicao.
   cor      - Cor da IMAGEM.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 VD_telaerr(xi,yi,mens,cor)
INT2   xi,yi;
char *mens;
INT2   cor;
{
 INT2 xf,
     yf,
     tam_mens;
 BYTE ascii,scan;

 tam_mens = strlen( mens );
 xf = xi+tam_mens+3;
 if (xf>79)
    xf+=(80-xf);

 if (yi>20)
    yi=20;
 yf = yi+4;

 VD_PUSHWIN(xi, xf+1, yi, yf+1);
 VD_quadro( xi,xf,yi,yf, ' ',cor);
 VIDEO_box_simples(xi,xf,yi,yf,cor);

 VIDEO_setatrib(xf+1, xf+1, yi+1, yf,       /* Sombra Vertical.*/
                VD_FORMATO(VD_PRETO,VD_NORMAL,VD_BLANK,VD_BRIL) );
 VIDEO_setatrib(xi+1, xf+1, yf+1, yf+1,     /* Sombra Horizontal.*/
                VD_FORMATO(VD_PRETO,VD_NORMAL,VD_BLANK,VD_BRIL) );

 VD_tprt_l(xi+2,yi+2,mens,cor);

 VIDEO_getkbd(&ascii,&scan);

 VD_POPWIN();

 return(FALSE);
}

