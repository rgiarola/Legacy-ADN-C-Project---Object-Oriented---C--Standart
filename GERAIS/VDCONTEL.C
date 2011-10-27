#define VIDEO_MENU_CONFIRMA

/* ============================================================================
   EXIBE TELA DE STATUS DE ERRO.
   PARAMETROS:
   xi       - Coluna Referencia Inicial.
   yi       - Linha Referencia Inicial.
   mens     - Mensagem de Exibicao.
   cor      - Cor da IMAGEM.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 VD_telaconfirma(xi,yi,mens,cor,tipo)
INT2     xi,yi;
char    *mens;
INT2     cor;
INT2    tipo;
{
 INT2            xf,yf,ret,
                 tam_mens;
 BYTE            ascii,scan;
#ifdef VIDEO_UNIX
 INT2            old_flag_video;
#endif
 VIDEO_INFO_MENU *menudisp;
 INT2            cont;

 tam_mens = strlen( mens );
 xf = xi+tam_mens+3;

 if (xf>79)
    xf+=(80-xf);

 if (yi>20)
    yi=20;

 yf = yi+4+2;

#ifdef VIDEO_UNIX
 old_flag_video = VIDEO_UNIX_flag_video;
 VIDEO_UNIX_flag_video &= ~VIDEO_UNIX_AUTO_REFRESH;
#endif

VD_PUSHWIN(xi, xf+1, yi, yf+1);
 VD_quadro( xi,xf,yi,yf, ' ',cor);

 VIDEO_box_simples(xi,xf,yi,yf,cor);

 VIDEO_setatrib(xf+1, xf+1, yi+1, yf,       /* Sombra Vertical.*/
                VD_FORMATO(VD_PRETO,VD_NORMAL,VD_BLANK,VD_BRIL) );

 VIDEO_setatrib(xi+1, xf+1, yf+1, yf+1,     /* Sombra Horizontal.*/
                VD_FORMATO(VD_PRETO,VD_NORMAL,VD_BLANK,VD_BRIL));

 VD_tprt_l(xi+2,yi+2,mens,cor);

#ifdef VIDEO_UNIX
           VIDEO_UNIX_refresh_tela();
#endif

#ifdef VIDEO_MENU_CONFIRMA
 VIDEO_HELP_menu_padrao.sistcrg = VIDEO_PROJ_MENU_SIM_NAO_PADRAO,
 VIDEO_HELP_menu_padrao.telacrg = VIDEO_SIST_MENU_SIM_NAO_PADRAO;

 if (VIDEO_CRG_executa_menu_carrega(&VIDEO_HELP_menu_padrao))
    {
     int coli,lini;

     menudisp =
     PTR_CAST(VIDEO_INFO_MENU,(PTR_CAST(char,VIDEO_HELP_menu_padrao.strtelacrg)+sizeof(VIDEO_NUCLEO_SERV)));
     cont = (menudisp->coli+(menudisp->numpag+1)*menudisp->tamcol- 1 - menudisp->coli);
     if ((coli = (((xf-xi+1) - cont) / 2)) < 0)
         coli = 0;

     cont = (menudisp->colf-menudisp->coli);
     menudisp->coli  = menudisp->col  = xi + coli;
     menudisp->colf  = menudisp->coli + cont;

     ret = menudisp->linf - menudisp->lini;
     menudisp->lin   = menudisp->lini = yi+4;
     menudisp->linf  = menudisp->lin + ret;

     if (tipo)
        {
         ret = menudisp->numop % menudisp->numlin;
         menudisp->colatu = (menudisp->numop / menudisp->numlin) - (ret == 0);
         ret = ret ? --ret : menudisp->numlin - 1;
         menudisp->lin = menudisp->lini + ret;
         menudisp->opsel = menudisp->numop - 1;
         menudisp->col = menudisp->coli + menudisp->tamcol * menudisp->numpag;
         menudisp->colpag = menudisp->numpag;
        }

     ret = VIDEO_CRG_dispara_menu(&VIDEO_HELP_menu_padrao,TRUE,TRUE,TRUE);
     VD_POPWIN();
     VIDEO_CRG_libera_tela(&VIDEO_HELP_menu_padrao);
    }

 if (isam_err)
#endif
    {
     INT2 lin,col;

     VIDEO_mensagem_default.mensagem = VIDEO_mensagem_confirma;
     col = VIDEO_mensagem_default.col;
     VIDEO_mensagem_default.col =
     (xf-xi+1-strlen(VIDEO_mensagem_default.mensagem))/2 + xi;
     lin = VIDEO_mensagem_default.lin;
     VIDEO_mensagem_default.lin = yf - 2;


     ret = VIDEO_TELA_display_confirma(&VIDEO_mensagem_default);
     if (ret == 'S')
        ret = 1;
     if (ret == 'N')
        ret = 2;
     if (ret == 27)
        ret = 0;

     VIDEO_mensagem_default.col = col;
     VIDEO_mensagem_default.lin = lin;
    }

 VD_POPWIN();

#ifdef VIDEO_UNIX
           VIDEO_UNIX_flag_video = old_flag_video;
           VIDEO_UNIX_refresh_tela();
#endif

 return(ret);
}

