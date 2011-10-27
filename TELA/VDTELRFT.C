#include <INCVIDEO.H>

INT2 VIDEO_TELA_refresh_tela(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_TELA_ENTRADA_DADOS *telaaux;
 VIDEO_IMAGEMTELA         *imagem;

 telaaux = *tela;

 if (telaaux->num_imagens > 1)
    {
     INT2 numimag,cont;

     for (numimag = cont = 0;cont < telaaux->num_imagens;cont++)
         if ((telaaux->imagens+cont)->seqdisp)
             ++numimag;

     if (numimag > 1)
        {
         INT2              cont1,cont2,
                          ret;
         BYTE             flag;
         VIDEO_TELASTRRFS *refresh,
                          refaux;

         if (VIDEO_ALLOC_MEM(refresh,numimag*sizeof(VIDEO_TELASTRRFS))
             == VD_NULO)
            {
             VIDEO_mostra_mens_erro_alloc(ALOCACAO_REFRESH_TOTAL);
             return(TRUE);
            }

         for (cont1 = cont = 0;cont < telaaux->num_imagens;cont++)
             if ((telaaux->imagens+cont)->seqdisp)
                {
                 (refresh+cont1)->numimag = cont;
                 (refresh+cont1)->numdisp =
                 (telaaux->imagens+cont)->seqdisp;
                 ++cont1;
                }

         flag = TRUE;
         for (cont1 = 0;(cont1 < numimag) && flag;cont1++)
             {
              flag = FALSE;
              for (cont2 = cont1 + 1;cont < numimag;cont2++)
                   if ((refresh+cont1)->numdisp >
                       (refresh+cont2)->numdisp)
                      {
                       refaux           = *(refresh+cont1);
                       *(refresh+cont1) = *(refresh+cont2);
                       *(refresh+cont2) = refaux;
                       flag = TRUE;
                      }
             }

         ret = telaaux->imagem_accept;
         for (cont = 0;cont < numimag;cont++)
             {
              telaaux->imagem_accept = (refresh+cont)->numimag;
              imagem = telaaux->imagens+telaaux->imagem_accept;
              imagem->flagimagem &= ~VIDEO_TELA_ACCEPTCAMPOS;
              imagem->flagimagem |= (VIDEO_TELA_DISPIMAGEM|
                                     VIDEO_TELA_DISPCAMPOS|
                                     VIDEO_TELA_FLAGRESETDISPLAY);
              VIDEO_TELA_accept_tela(*tela,*param);
              VIDEO_TELA_desativa_status(imagem);
              imagem->flagimagem |= VIDEO_TELA_ACCEPTCAMPOS;
             }
         telaaux->imagem_accept = ret;

         VIDEO_FREE_ALLOC_MEM(refresh);
        }
      else
        {
         INT2 cont;

         for (cont = 0;cont < telaaux->num_imagens;cont++)
             if ((telaaux->imagens+cont)->seqdisp)
                telaaux->imagem_accept = cont;
         VD_POPWIN();
         telaaux->flagtela |= VIDEO_TELA_SALVATELA;
        }
    }

 imagem = telaaux->imagens+telaaux->imagem_accept;
 imagem->flagimagem |= (VIDEO_TELA_DISPIMAGEM|
                        VIDEO_TELA_DISPCAMPOS|
                        VIDEO_TELA_FLAGRESETDISPLAY);
 return(TRUE);
}
