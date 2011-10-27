#include <INCVIDEO.H>
/* nao ok*/

INT2 VIDEO_TELA_consiste_all(tela,fseta_imag)
VIDEO_TELA_ENTRADA_DADOS *tela;
INT2                      fseta_imag;
{
 VIDEO_CAMPO_TELA  *campo;
 VIDEO_CAMPO_TELA  *campos;
 INT2              contimagem,contcampos,
                   numcampos,cont;
 VIDEO_IMAGEMTELA  *imagem;

 imagem = tela->imagens;

 contimagem = 0;
 do
  {
   if (imagem->arquivo == tela->imagem_ativa->arquivo)
      {
       campos     = PTR_CAST(VIDEO_CAMPO_TELA,
                    imagem->campos->VIDEO_campos);
       numcampos  = imagem->campos->VIDEO_numcampos;
       contcampos = 0;
       do
        {
         campo = campos + contcampos;
         imagem->campos->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_S);
         if (VIDEO_TELA_consiste_camp_imagem(&campo,fseta_imag,
                                                    &(imagem->campos)))
            {
             if (fseta_imag)
                {
                 tela->imagem_accept   = contimagem;
                 imagem->campos->VIDEO_inicial = contcampos;
                 (tela->imagens+tela->imagem_accept)->flagimagem    |=
                                                   (VIDEO_TELA_DISPIMAGEM|
                                                    VIDEO_TELA_DISPCAMPOS|
                                              VIDEO_TELA_FLAGRESETDISPLAY);
                 if ((tela->imagens+tela->imagem_accept)->arquivo ==
                      tela->imagem_ativa->arquivo)
                      if (tela->imagem_ativa->flagimagem&VIDEO_TELA_INICIMAGEM)
                         (tela->imagens+tela->imagem_accept)->flagimagem |=
                         VIDEO_TELA_INICIMAGEM;
                        else
                         (tela->imagens+tela->imagem_accept)->flagimagem &=
                         ~VIDEO_TELA_INICIMAGEM;
                }
             return(FALSE);
            }
         ++contcampos;
        }while(contcampos < numcampos);
      }
   ++contimagem;
   ++imagem;
  }while(contimagem < tela->num_imagens);
 return(TRUE);
}
