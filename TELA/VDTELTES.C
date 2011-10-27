#include <INCVIDEO.H>

INT2 VIDEO_TELA_data_base_exsub(tela,imagem,servico)
VIDEO_TELA_ENTRADA_DADOS *tela;
VIDEO_IMAGEMTELA         *imagem;
INT2                      servico;
{
 VIDEO_IMAGEMTELA *imagpesq;
 INT2              ret,flagseg,indice,contimag;
 static INT2       cont = 0;

 if (tela->imagem_accept < (tela->num_imagens-1))
    {
     for (imagpesq = imagem + 1,contimag = tela->imagem_accept+1;
                           contimag < tela->num_imagens;contimag++,imagpesq++)
         if (imagpesq->nmindpai &&
              (CTREE_keyfil(CTREE_keynm(imagpesq->nmindpai)) ==
               CTREE_keyfil(CTREE_keynm(imagem->nmindarq))))
            {
             ++tela->imagem_accept;
             ++cont;                        

             indice = CTREE_keynm(imagpesq->nmindarq);

             if (servico)
                 VIDEO_TELA_data_base_exsub(tela,imagpesq,servico);
               else
                 {
                  if (imagem->transpdados)
                      CTREE_cpydoda(imagem->transpdados);

                  if (imagpesq->transpdados)
                      CTREE_cpydoda(imagpesq->transpdados);

                  if (contimag < (tela->num_imagens-1))
                     if (!CTREE_find(indice,imagpesq->segchave,
                                     FIND_PRIMEIRO,CT_LE_EXTRA_REPASSA))
                        do
                         {
                          if (imagem->transpdados)
                              CTREE_cpydoda(imagem->transpdados);

                          if (imagpesq->transpdados)
                              CTREE_cpydoda(imagpesq->transpdados);

                          VIDEO_TELA_data_base_exsub(tela,imagpesq,servico);

                         }while(!CTREE_find(indice,imagpesq->segchave,FIND_PROXIMO,
                                            CT_LE_EXTRA_REPASSA));

                  if (imagem->transpdados)
                      CTREE_cpydoda(imagem->transpdados);

                  if (imagpesq->transpdados)
                      CTREE_cpydoda(imagpesq->transpdados);

                  if ((ret = CTREE_dlall(indice,imagpesq->segchave,
                                         VD_NULO)) != 101)
                     {
                      char buffer[100];
					  sprintf(buffer,CTREE_MENS_mens_padrao_err,
									 VIDEO_TELA_mens_delsub,
									 (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(CTREE_keynm(imagem->nmindarq)))->reduzido,
									 ret,isam_err);
					  VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_del_arq_sub_tes);
                      return(FALSE);
                     }

                  imagpesq->flagimagem            |=
                            (VIDEO_TELA_STATUS    |
                             VIDEO_TELA_DISPCAMPOS|
							 VIDEO_TELA_DISPIMAGEM|
							 VIDEO_TELA_FLAGRESETDISPLAY);
                 }
             --tela->imagem_accept;
             --cont;
            }

     if (!servico)
        return(TRUE);
    }

  flagseg = !VIDEO_TELA_testa_segconst_sub(imagem);

  if ((imagem->segsub && flagseg) || (!servico && cont))
     {
      if ((ret = CTREE_dlall(CTREE_keynm(imagem->nmindarq),imagem->segchave,
                             VD_NULO)) != 101)
         {
          char buffer[100];
		  sprintf(buffer,CTREE_MENS_mens_padrao_err,
						 VIDEO_TELA_mens_delsub,
						 (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(CTREE_keynm(imagem->nmindarq)))->reduzido,
						 ret,isam_err);
		  VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_del_arq_sub_tes);
          return(FALSE);
         }

      imagem->flagimagem            |=
              (VIDEO_TELA_STATUS    |
               VIDEO_TELA_DISPCAMPOS|
               VIDEO_TELA_DISPIMAGEM);

      imagem->flagimagem &= ~VIDEO_TELA_FLAGREGALT;
     }


  if (servico && imagem->segsub && flagseg)
     {
      if ((ret = CTREE_copy(CTREE_keynm(imagem->nmindarq),
                        CTREE_keynm(imagem->nmindsub),
             imagem->segsub,FALSE,VD_NULO)) != 101)
         {
          char buffer[100];
		  sprintf(buffer,CTREE_MENS_mens_padrao_err,
						 VIDEO_TELA_mens_copysub,
						 (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(CTREE_keynm(imagem->nmindarq)))->reduzido,
						 ret,isam_err);
		  VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_copy_arq_sub_tes);
          return(FALSE);
         }

      if (cont)
         {
          imagem->seqdisp = 0;
          imagpesq = tela->imagem_ativa;
          tela->imagem_ativa = imagem;
          VIDEO_TELA_libera_subfile(tela,TRUE);
          tela->imagem_ativa = imagpesq;
         }
     }

 return(TRUE);
}

/*
displayseg(seg)
VIDEO_SEG_CHAVE *seg;
{
 IDE_DODA        *doda;
 INT2 col,lin;

 col = 1;
 lin = 3;
 VD_PUSHWIN(1,80,1,25);

 VD_gtxy(col,lin);
 while(seg->pointer)
  {
   switch(seg->tipo)
      {
       case CT_SEG_CONST      :printf("CT_SEG_CONST      %d\n",seg->tamanho);break;
       case CT_SEG_CAMPO_CONST:printf("CT_SEG_CAMPO_CONST%d\n",seg->tamanho);break;
       case CT_SEG_CAMPO      :printf("CT_SEG_CAMPO      %d\n",seg->tamanho);break;
       default                :printf("TIPO INVALIDO     %d\n",seg->tamanho);break;
      }

   if (seg->tipo != CT_SEG_CONST)
       if ((doda = CTREE_dodaend(seg->pointer)) != VD_NULO)
           switch(I(doda->ftype))
            {
             case I(CT_CHARU ):
             case I(CT_CHAR  ):printf("%20s CT_CHARU  %c\n",seg->pointer,*doda->fadr);break;

             case I(CT_INT2U ):printf("%20s CT_INT2U  %6u\n",seg->pointer,CWORD(doda->fadr));break;
             case I(CT_INT2  ):printf("%20s CT_INT2   %6d\n",seg->pointer,CINT(doda->fadr));break;

             case I(CT_INT4U ):printf("%20s CT_INT4U  %10lu\n",seg->pointer,CLONG(doda->fadr));break;
             case I(CT_INT4  ):printf("%20s CT_INT4   %10ld\n",seg->pointer,CLONG(doda->fadr));break;

             case I(CT_SFLOAT):printf("%20s CT_SFLOAT %15.0f\n",seg->pointer,CFLOAT(doda->fadr));break;
             case I(CT_DFLOAT):printf("%20s CT_DFLOAT %15.0f\n",seg->pointer,CDOUBLE(doda->fadr));break;

             case I(CT_DATE  ):printf("%20s CT_DATE   %10u\n",seg->pointer,CLONG(doda->fadr));break;
             case I(CT_TIME  ):printf("%20s CT_TIME   %10u\n",seg->pointer,CLONG(doda->fadr));break;

             case I(0        ):printf("%20s 0         %s\n",seg->pointer,doda->fadr);break;

             default        :printf("NAO DEFINIO INTERNAMENTE %s %d\n",seg->pointer,doda->ftype);
            }
          else
            printf("DODA NAO ENCONTRADO %s\n",seg->pointer);
        else
          printf("DODA CONSTANTE %s\n",seg->pointer);
   ++seg;
  }
 getch();
 VD_POPWIN();
}
*/
