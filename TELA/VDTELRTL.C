#include <INCVIDEO.H>
/* ok*/

INT2 VIDEO_TELA_reseta_imagem(tela,param)
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
          if ((telaaux->imagens+cont)->arquivo ==
               telaaux->imagem_ativa->arquivo &&
               (telaaux->imagens+cont)->seqdisp)
             ++numimag;

     if (numimag > 1)
        {
         INT2              cont1,ret,
                          cont2;
         VIDEO_TELASTRRFS *refresh,
                          refaux;
         BYTE             flag;

         if (VIDEO_ALLOC_MEM(refresh,numimag*sizeof(VIDEO_TELASTRRFS))
             == VD_NULO)
            {
             VIDEO_mostra_mens_erro_alloc(ALOCACAO_REFRESH_IMAGEM);
             return(TRUE);
            }

         for (cont1 = cont = 0;cont < telaaux->num_imagens;cont++)
             if ((telaaux->imagens+cont)->arquivo ==
                  telaaux->imagem_ativa->arquivo &&
                  (telaaux->imagens+cont)->seqdisp)
                {
                 (refresh+cont1)->numimag = cont;
                 (refresh+cont1)->numdisp =
                 (telaaux->imagens+cont)->seqdisp;
                 ++cont1;
                }

         flag = TRUE;
         for (cont1 = 0;cont1 < numimag && flag;cont1++)
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

         for (cont = 0;cont < numimag;cont++)
              if ((telaaux->imagens+(refresh+cont)->numimag) ==
                  telaaux->imagem_ativa)
                 {
                  if (!cont)
                      telaaux->imagem_accept = cont+1;
                    else
                      telaaux->imagem_accept = cont-1;
                  telaaux->imagem_ativa->seqdisp = 0;
                  break;
                 }
         VD_POPWIN();
         telaaux->flagtela |= VIDEO_TELA_SALVATELA;
         VIDEO_FREE_ALLOC_MEM(refresh);
        }
      else
        {
         INT2 cont,tot;

         for (tot = cont = 0;cont < telaaux->num_imagens;cont++)
             tot += ((telaaux->imagens+cont)->seqdisp != 0);

         if (tot > 1)
            telaaux->imagem_ativa->seqdisp = 0;
           else
            {
             VD_POPWIN();
             telaaux->flagtela |= VIDEO_TELA_SALVATELA;
            }
        }
    }

 imagem = telaaux->imagens+telaaux->imagem_accept;
 imagem->flagimagem |= (VIDEO_TELA_DISPIMAGEM|
                        VIDEO_TELA_DISPCAMPOS);

 (*param)->VIDEO_repdisp = TRUE;
 (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_R);

 return(TRUE);
}
