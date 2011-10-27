#include <INCVIDEO.H>

INT2 VIDEO_TELA_data_base_adm_pos(campos, param)
VIDEO_CAMPO_TELA  **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;

 if ((consiste = (*campos)->consiste) ==
      VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
     return(TRUE);

 while( consiste->tipocons )
  {
   if( consiste->tipocons==VIDEO_TELA_CONS_POSICIONA_DB &&
      consiste->objetocons.consdb)
     {
#ifdef DATABASE_CTREE
      IDE_ARQUIVOS *work_ifil;
      INT2          numero_arquivo,
                   tmpfil,ret;
      IDE_INDEX    *work_indice;
      char         *buffer_rec;

	  numero_arquivo = CTREE_keyfil(consiste->objetocons.consdb->indice);
      tmpfil         = CTREE_tmpfil(numero_arquivo);
      work_ifil      = CTREE_ifilend(numero_arquivo);
      ATIVA_BUF_EXTRA;
      buffer_rec     = CTREE_filbuf(numero_arquivo);

      if (consiste->objetocons.consdb->posicao)
         {
          unsigned long int posicao;

          posicao = DATABASE_CurrentFileOffset(tmpfil);
          if (!DATABASE_CmpFileOffset(posicao,
                                 consiste->objetocons.consdb->posicao))
             {
              DATABASE_SetRecord(tmpfil,consiste->objetocons.consdb->posicao,
                                      buffer_rec,work_ifil->dreclen);
              DATABASE_ReReadRecord(tmpfil,buffer_rec);
             }
         }

      do
       {
#else
        INT2 ret;
#endif

        if (!CTREE_find(consiste->objetocons.consdb->indice,
                       consiste->objetocons.consdb->segchave,
                       FIND_PROXIMO, CT_LE_EXTRA_REPASSA ))
           {
            if (consiste->objetocons.consdb->transpdados)
                CTREE_cpydoda(consiste->objetocons.consdb->transpdados);

            (*param)->VIDEO_inicial = (*campos)->objeto_num -
            PTR_CAST(VIDEO_CAMPO_TELA,(*param)->VIDEO_campos)->objeto_num;
#ifdef DATABASE_CTREE
            consiste->objetocons.consdb->posicao =
                                 DATABASE_CurrentFileOffset(tmpfil);
#endif
            return(FALSE);
           }

#ifdef DATABASE_CTREE
        work_indice = work_ifil->ix + (consiste->objetocons.consdb->indice
                         - numero_arquivo -1);

        if (!(DW(work_indice->user)&VIDEO_FLAG_INDICE_ATIVADO))
           {
            DW(work_indice->user) |= VIDEO_FLAG_INDICE_ATIVADO;
            if (consiste->objetocons.consdb->posicao)
                CTREE_find(consiste->objetocons.consdb->indice,
                           consiste->objetocons.consdb->segchave,
                           FIND_IGUAL, CT_LE_EXTRA);
              else
                break;
            continue;
           }
         break;
       }while(TRUE);
#endif
      (*param)->VIDEO_repdisp = TRUE;
      (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_PGUP);
      return( TRUE );
     }
   ++consiste;
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
 VD_gtxy(1,5);
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
