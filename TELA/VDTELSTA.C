#include <INCVIDEO.H>
/* ok*/

VD_VOID VIDEO_TELA_seta_alteracao(tela)
VIDEO_TELA_ENTRADA_DADOS *tela;
{
 VIDEO_IMAGEMTELA *imagem;
 INT2              cont;

 imagem = tela->imagens+tela->imagem_accept;

 if (imagem->tipotela < 5 && imagem->tipotela > 1)
    {
     imagem->flagimagem &= ~VIDEO_TELA_STATUS;

     if ((imagem->linf-1) != imagem->lini)
        {
         VD_tprt_l(imagem->coli,imagem->linf,VIDEO_texto_inclusao,
                                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
         VD_plotcarac(imagem->coli,imagem->linf,'I',
                                 VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
         VD_tprt_l(imagem->coli+10,imagem->linf,VIDEO_texto_atualiza,
                                     VD_FORMATO(VD_VERDE,VD_NORMAL,VD_BLANK,VD_BRIL));
        }

     imagem = tela->imagens;

     for (cont = 0;cont < tela->num_imagens;cont++,imagem++)
          if (imagem->arquivo == tela->imagem_ativa->arquivo)
             {
              imagem->flagimagem &= ~VIDEO_TELA_STATUS;
              imagem->flagimagem |= VIDEO_TELA_DISPCAMPOS;
             }
    }
}

