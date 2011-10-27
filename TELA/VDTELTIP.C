#include <INCVIDEO.H>

INT2 VIDEO_TELA_testa_imagem_pai(tela,flagserv)
VIDEO_TELA_ENTRADA_DADOS *tela;
INT2                      flagserv;
{
 VIDEO_IMAGEMTELA *imagem,*imagwork;
 INT2              ret,imag_accept,col,
                  cont_imag;
 char             buffer[100];

 imagem = tela->imagem_ativa;

 if (flagserv == 1)
    {
     if (!VIDEO_TELA_consiste_all(tela,FALSE))
        {
         strcpy(buffer,VIDEO_PROCESSA_PAI_SUBFILE);
         if (imagem->ident)
             sprintf(&buffer[strlen(buffer)]," [%s]",imagem->ident);
         VIDEO_mostra_mens_erro(buffer,TRUE);
         return(FALSE);
        }
     return(TRUE);
    }

 if (flagserv == 2)
    {
     if (imagem->tipotela > 1)
        {
         imagem = tela->imagens + tela->imagem_accept;
		 if (imagem->flagimagem&VIDEO_TELA_STATUS)
            {
             if ((ret = CTREE_adrec(imagem->nmindsub ?
                                    CTREE_keyfil(CTREE_keynm(imagem->nmindsub)):
                                    imagem->arquivo  )) != FALSE)
                 sprintf(buffer,"ERRO INCLUSŽO HEADER %d ",ret);
               else
                 {
                  imagem->campos->VIDEO_inicial=0;
                  imagem->flagimagem |= (VIDEO_TELA_DISPCAMPOS|
                                           VIDEO_TELA_INICIMAGEM);
#ifdef DATABASE_CTREE
                  VIDEO_TELA_ajusta_posicao(imagem);
#endif
                 }
            }
           else
             if ((ret = CTREE_rewrec(imagem->nmindsub ?
                                     CTREE_keyfil(CTREE_keynm(imagem->nmindsub)):
                                     imagem->arquivo  )) != FALSE)
                 sprintf(buffer,"ERRO ALTERA€ŽO HEADER %d ",ret);

         if (ret)
            {
             if (imagem->ident)
                 sprintf(&buffer[strlen(buffer)]," [%s]",imagem->ident);
             VIDEO_mostra_mens_erro(buffer,TRUE);
             return(FALSE);
            }

         imagem->flagimagem |= VIDEO_TELA_FLAGREGALT;
        }
     return(TRUE);
    }
 

 imagem      = tela->imagem_ativa;
 imag_accept = tela->imagem_accept;

 if (flagserv == 3)
    {
     imagwork    = tela->imagens;
     cont_imag   = 0;

     if (cont_imag != tela->imagem_accept)
         do
          {
           if (CTREE_keyfil(CTREE_keynm(imagem->nmindpai)) ==
               CTREE_keyfil(CTREE_keynm(imagwork->nmindarq)))
              {
               tela->imagem_accept = cont_imag;
               tela->imagem_ativa  = imagwork;
               return(TRUE);
              }
           ++imagwork;
          }while(++cont_imag < tela->imagem_accept);
    }

 if (flagserv == 4)
    {
     imagwork    = tela->imagem_ativa;
     cont_imag   = tela->imagem_accept;

     while(++cont_imag < tela->num_imagens)
      {
       ++imagwork;
       if (CTREE_keyfil(CTREE_keynm(imagem->nmindarq)) == CTREE_keyfil(CTREE_keynm(imagwork->nmindpai)))
          {
           tela->imagem_accept = cont_imag;
           tela->imagem_ativa  = imagwork;
           return(TRUE);
          }
      }
    }

 tela->imagem_ativa  = imagem;
 tela->imagem_accept = imag_accept;

 return(FALSE);
}

