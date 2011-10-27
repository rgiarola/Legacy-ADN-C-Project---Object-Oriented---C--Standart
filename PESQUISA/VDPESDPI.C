#include <INCVIDEO.H>

VD_VOID VIDEO_PESQUISA_display_imagem(pesquisa,param)
VIDEO_PESQUISA_PLANILHA *pesquisa;
VIDEO_NUCLEO_SERV       *param;
{
 VIDEO_TELA_ENTRADA_DADOS *telacampos;
 VIDEO_IMAGEMTELA         *imagem;
 char                     buffer[100];

 telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela);
 imagem     = telacampos->imagens;

 VIDEO_TELA_display_imagem(telacampos);

 if (imagem->sombra)
    {
     VIDEO_setatrib(imagem->colf+1, imagem->colf+1,
                    imagem->lini+1, imagem->linf+1,
                    imagem->sombra);
     VIDEO_setatrib(imagem->coli+1, imagem->colf+1,
                    imagem->linf+1, imagem->linf+1,
                    imagem->sombra);
    }

 if (pesquisa->flagplanilha&VIDEO_PESQUISA_MANUTENCAO)
    {
     VIDEO_CAMPO_CONSISTENCIA *consiste;

     if ((consiste = PTR_CAST(VIDEO_CAMPO_TELA,
                     imagem->campos->VIDEO_campos)->consiste) != VD_NULO)
         while(consiste->tipocons)
          {
           if (consiste->tipocons == VIDEO_TELA_CONS_MANUT)
               break;
           ++consiste;
          }

     if (consiste && !consiste->tipocons)
        pesquisa->flagplanilha &= (~VIDEO_PESQUISA_MANUTENCAO);
      else
        {
         VD_tprt_l(imagem->colf-9,imagem->linf,VIDEO_texto_manutencao,
                             VD_FORMATO(VD_VERDE,VD_NORMAL,VD_BLANK,VD_BRIL));
         VD_plotcarac(imagem->colf-9,imagem->linf,'M',
                        VD_FORMATO(VD_VERDE,VD_NORMAL,VD_VERMELHO,VD_NORMAL));
        }
    }

 sprintf(buffer,"[ %d/%d ]",param->VIDEO_inicial+1,param->VIDEO_numcampos);

 VD_tprt_l(imagem->colf-7,imagem->linf-1,buffer,0);
}

