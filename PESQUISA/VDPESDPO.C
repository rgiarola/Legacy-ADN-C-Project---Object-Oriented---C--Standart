#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_display_campos_posterior(pesquisa,param)
VIDEO_PESQUISA_PLANILHA *pesquisa;
VIDEO_NUCLEO_SERV       *param;
{
 VIDEO_CAMPO_TELA         *linhacampos,
                          *campos;
 INT2                      numcampos,lini  ,
                          linf   ,indice   ,tamanho,
                          contlin,contcampo,arquivo,
                          tmpfil ,lininic;
 VIDEO_TELA_ENTRADA_DADOS *telacampos;
 VIDEO_IMAGEMTELA         *imagem;
 DWORD                    posicao = 0L;
 char                     *buffer;

 telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela);
 imagem   = telacampos->imagens;

 lini    = imagem->lini + 3;
 linf    = imagem->linf - 2;
 indice  = pesquisa->indice;
 arquivo = CTREE_keyfil(indice);
 tamanho = CTREE_ifilend(arquivo)->dreclen;
 tmpfil  = CTREE_tmpfil(arquivo);
 
 numcampos   = imagem->campos->VIDEO_numcampos;
 linhacampos = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos);

 for (contlin = lini;contlin <= linf;contlin++)
     {
      if (pesquisa->flagplanilha&VIDEO_PESQUISA_INICDISP)
         {
          pesquisa->flagplanilha &= ~(VIDEO_PESQUISA_INICDISP);
          if (VIDEO_ALLOC_MEM(buffer,tamanho) == VD_NULO)
             {
              VIDEO_mostra_mens_erro_alloc(ALOCACAO_BUFFER_PESQ);
             }
           else
             {
              pesquisa->flagplanilha |= VIDEO_PESQUISA_FLAGPROC;
              posicao = DATABASE_CurrentFileOffset(tmpfil);
              lininic = lini;
              ATIVA_BUF_DADOS;
              VIDEO_movbloco(buffer,CTREE_filbuf(arquivo),tamanho);
             }
         }

      for (campos = linhacampos,contcampo = 0;contcampo < numcampos;
                                            contcampo++,campos++)
           campos->lin = contlin;

      VIDEO_TELA_display_campos(linhacampos,numcampos,imagem->campos,
                                VIDEO_FLAGVALIDA_CAMPO |
                                VIDEO_FLAGUSER_CAMPO   |
                                VIDEO_TELA_FLAGRESETDISPLAY);

      pesquisa->linatual = contlin;

      if (contlin != linf)
         if (CTREE_find(indice,pesquisa->segchave,
                        FIND_PROXIMO,CT_LE_EXTRA_REPASSA))
			{
             VIDEO_TELA_display_campos(linhacampos,numcampos,
                                       imagem->campos,
                                       VIDEO_FLAGVALIDA_CAMPO|
                                       VIDEO_FLAGUSER_CAMPO  |
                                       VIDEO_TELA_FLAGRESETDISPLAY);
             break;
			}
     }

 if (pesquisa->flagplanilha&VIDEO_PESQUISA_FLAGPROC)
    {
     pesquisa->flagplanilha &= ~(VIDEO_PESQUISA_FLAGPROC);
     if (posicao)
		{
		 pesquisa->linatual = lininic;
		 for (campos = linhacampos,contcampo = 0;contcampo < numcampos;
											   contcampo++,campos++)
			  campos->lin = lininic;
		 DATABASE_SetRecord(tmpfil,posicao,buffer,tamanho);
         ATIVA_BUF_DADOS;
         DATABASE_ReReadRecord(tmpfil,CTREE_filbuf(arquivo));

#ifdef CTREE_MULTI_USER
         VIDEO_movbloco(CTREE_filbuf(arquivo)+2*tamanho,
                        CTREE_filbuf(arquivo),tamanho);
#endif
		}
	 VIDEO_FREE_ALLOC_MEM(buffer);
    }

 return(TRUE);
}



/*
display(segchave)
VIDEO_SEG_CHAVE *segchave;
{
 IDE_DODA *doda;
 char     bftipo[10],
          buffer[150];

 VD_PUSHWIN(1,80,1,25);
 VD_gtxy(1,1);
 while(segchave->pointer)
  {
   printf("%20s %d %d ",segchave->pointer,segchave->tipo,segchave->tamanho);
   doda = CTREE_dodaend(segchave->pointer);
   switch(doda->ftype)
    {
     case CT_BOOL  : 
     case CT_CHAR  :
     case CT_CHARU :printf("%c %5u",W(CCHAR(doda->fadr)));
                    break;

     case CT_INT2  :printf("%5d",CINT(doda->fadr));
                    break;

     case CT_INT2U :printf("%5u",CWORD(doda->fadr));
                    break;

     case CT_INT4  :printf("%12ld",CLONG(doda->fadr));
                    break;

     case CT_INT4U :printf("%12lu",CDWORD(doda->fadr));
                    break;

     case CT_SFLOAT:printf("%8f",CFLOAT(doda->fadr));
                    break;

     case CT_DFLOAT:printf("%16u",CDOUBLE(doda->fadr));
                    break;

     case 0        :printf("%s",doda->fadr);
                    break;

    }
   printf("\n");
   ++segchave;
  }
 getch();
 VD_POPWIN();
}
*/
