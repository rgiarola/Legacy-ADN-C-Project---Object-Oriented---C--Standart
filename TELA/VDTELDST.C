#include <INCVIDEO.H>

VD_VOID VIDEO_TELA_desativa_status(imagem)
VIDEO_IMAGEMTELA *imagem;
{
 if ((imagem->linf-1) != imagem->lini)
    {
     if (imagem->tipotela < 6)
         VIDEO_setatrib(imagem->coli , imagem->colf,
                        imagem->linf,imagem->linf,
                        VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_PRETO,VD_BRIL));

     VIDEO_horizontal(imagem->colf-7,imagem->colf-1,imagem->lini,
                    VIDEO_pega_caracter(imagem->colf-6,imagem->lini),
                    VIDEO_pega_atributo(imagem->colf-5,imagem->lini));
    }

 imagem->flagimagem &= ~VIDEO_TELA_FLAGALTERSUB;
}

