#include <INCVIDEO.H>

INT2 VIDEO_TELA_selec_tela_posterior(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_TELA_ENTRADA_DADOS *telaaux;
 VIDEO_IMAGEMTELA         *imagem;
 INT2                      cont,accept;

 telaaux = *tela;
 accept  = telaaux->imagem_accept;

 if (telaaux->imagem_accept < (telaaux->num_imagens - 1))
    {
	 ++telaaux->imagem_accept;
     if (telaaux->num_imagens > 1)
        {
         INT2 numimag,cont;

         for (numimag = cont = 0;cont < telaaux->num_imagens;cont++)
              if ((telaaux->imagens+cont)->arquivo ==
                   telaaux->imagem_ativa->arquivo &&
                  (telaaux->imagens+cont)->seqdisp)
                 ++numimag;

         if (numimag)
            {
             INT2              cont1,ret,
                              cont2;
             VIDEO_TELASTRRFS *refresh,
                              refaux;
             BYTE             flag;

             if (VIDEO_ALLOC_MEM(refresh,numimag*sizeof(VIDEO_TELASTRRFS))
                 == VD_NULO)
                {
                 VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELA_POSTERIOR);
                 return(TRUE);
                }

             telaaux = *tela;
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
                       if ((refresh+cont1)->numdisp <
                           (refresh+cont2)->numdisp)
                          {
                           refaux           = *(refresh+cont1);
                           *(refresh+cont1) = *(refresh+cont2);
                           *(refresh+cont2) = refaux;
                           flag = TRUE;
                          }
                 }

             (telaaux->imagens+telaaux->imagem_accept)->flagimagem |=
             ((telaaux->imagem_ativa->flagimagem&VIDEO_TELA_STATUS));
             VIDEO_FREE_ALLOC_MEM(refresh);
            }

         if ((telaaux->imagens+telaaux->imagem_accept)->arquivo ==
              telaaux->imagem_ativa->arquivo)
              if (telaaux->imagem_ativa->flagimagem&VIDEO_TELA_INICIMAGEM)
                 (telaaux->imagens+telaaux->imagem_accept)->flagimagem |=
                 (VIDEO_TELA_INICIMAGEM);
                else
                 (telaaux->imagens+telaaux->imagem_accept)->flagimagem &=
                 ~VIDEO_TELA_INICIMAGEM;

         (telaaux->imagens+telaaux->imagem_accept)->flagimagem    |=
                                            (VIDEO_TELA_DISPIMAGEM|
											 VIDEO_TELA_DISPCAMPOS|
											 VIDEO_TELA_FLAGRESETDISPLAY);

         if (accept != telaaux->imagem_accept)
             VIDEO_TELA_desativa_status(telaaux->imagens+accept);

		}
    }
 return(TRUE);
}

