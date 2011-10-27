#include <INCVIDEO.H>

INT2 VIDEO_CRG_prepara_tela(tela)
VIDEO_ESTMANUT *tela;
{
 VIDEO_TABCRGTELA *strtelacrg;
 VIDEO_IMAGEMTELA *imagem;
 INT2              cont,contcampo;
 VIDEO_CAMPO_TELA *campos;

 if (!VIDEO_CRG_endereca_tela(tela->strtelacrg))
    return(FALSE);

 strtelacrg = PTR_CAST(VIDEO_TABCRGTELA,tela->strtelacrg);

 strtelacrg->telasai->seqdisp       = 0;
 strtelacrg->telasai->imagem_accept = 0;
 VIDEO_tela_atual = tela->tela      =
                    PTR_CAST(VIDEO_TABCRGTELA,strtelacrg)->telasai;

 VIDEO_imagem_atual = imagem = strtelacrg->imagemsai;

 if (!VIDEO_endnomearquivo(strtelacrg->telasai,1))
    {
     char buffer[200];
     if (CDWORD(&tela->telacrg) > 1000L)
         sprintf(buffer,VIDEO_CARGA_mens_end_nomearq,
                        tela->sistcrg,tela->telacrg);
       else
        {
         char numtela[10];
         ultoa(CDWORD(&tela->telacrg),numtela,10);
         sprintf(buffer,VIDEO_CARGA_mens_end_nomearq,
                        tela->sistcrg,numtela);
        }
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_end_arquivo_tela);
     return(FALSE);
    }


 if (strtelacrg->contcampossai)
     for (cont = 0;cont < strtelacrg->contimagemsai;cont++)
         {
          if (!VIDEO_enddodatela(
               PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos),
               imagem->campos->VIDEO_numcampos))
             {
              char buffer[200];
              if (CDWORD(&tela->telacrg) > 999)
                  sprintf(buffer,VIDEO_CARGA_mens_end_campos,
                                 tela->sistcrg,tela->telacrg);
                else
                 {
                  char numtela[10];
                  ultoa(CDWORD(&tela->telacrg),numtela,10);
                  sprintf(buffer,VIDEO_CARGA_mens_end_campos,
                                 tela->sistcrg,numtela);
                 }
              VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_end_doda_tela);
              return(FALSE);
             }

          if (!VIDEO_endnomeindice(
               PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos),
               imagem->campos->VIDEO_numcampos))
             {
              char buffer[200];
              sprintf(buffer,VIDEO_CARGA_mens_end_indice,cont);
              VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_end_ind_tela);
              return(FALSE);
             }

          imagem->flagimagem |= (VIDEO_TELA_DISPIMAGEM   |
                                 VIDEO_TELA_DISPCAMPOS   |
                                 VIDEO_TELA_STATUS       |
                                 VIDEO_TELA_INICIMAGEM   |
                                 VIDEO_TELA_ACCEPTCAMPOS );
          imagem->seqdisp = 0;
          imagem->indarq  = CTREE_keynm(imagem->nmindarq);
          imagem->arquivo = CTREE_keyfil(imagem->indarq);
          ++imagem;
         }

 strtelacrg->telasai->flagtela      = VIDEO_TELA_SALVATELA |
                                      VIDEO_TELA_FLAGPOPWIN;
 strtelacrg->telasai->tela = tela;

 for (cont = 0,imagem = strtelacrg->imagemsai;
                        cont < strtelacrg->contimagemsai;cont++,imagem++)
     if (imagem->campos)
         for (contcampo = 0,
              campos = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos)
             ;contcampo < imagem->campos->VIDEO_numcampos;contcampo++,campos++)
              if (campos->consiste->tipocons == VIDEO_TELA_CONS_OLD_BUFFER)
                 {
                  int  tamanho = sizeof(int)+sizeof(BOOLEAN);
                  char *buffer;

                  switch(campos->tipo)
                   {
                    case VIDEO_CAMPO_BYTE:
                    case VIDEO_CAMPO_SHINT:
                    case VIDEO_CAMPO_CARACTER:
                         tamanho += sizeof(char);
                         break;

                    case VIDEO_CAMPO_WORD:
                    case VIDEO_CAMPO_INT:
                         tamanho += sizeof(int);
                         break;

                    case VIDEO_CAMPO_DWORD:
                    case VIDEO_CAMPO_LONG:
                    case VIDEO_CAMPO_FLOAT:
                    case VIDEO_CAMPO_TIME:
                    case VIDEO_CAMPO_DATA:
                         tamanho += sizeof(long);
                         break;

                    case VIDEO_CAMPO_DOUBLE:
                         tamanho += sizeof(double);
                         break;

                    case VIDEO_CAMPO_STRING:
                         tamanho += (CTREE_dodaend(campos->dodacampo)->flen+1);
                   }

                  if (VIDEO_ALLOC_MEM(buffer,tamanho) == VD_NULO)
                     {
                      VIDEO_mostra_mens_erro_alloc(ALOCACAO_PREP_TEL);
                      return(FALSE);
                     }

                  VIDEO_setmem(buffer+sizeof(int),tamanho-sizeof(int),0);
                  CINT(buffer) = tamanho - (sizeof(int)+sizeof(BOOLEAN));

                  campos->consiste->objetocons.old_buffer = buffer;
                 }

 imagem = strtelacrg->imagemsai;

 if (imagem->campos->VIDEO_numcampos)
    {
     VIDEO_campo_atual = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos);
     VIDEO_cons_atual = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos)->consiste;
     VIDEO_doda_campo = VIDEO_campo_atual->dodacampo;
    }
  else
    {
     VIDEO_campo_atual = VD_NULO;
     VIDEO_cons_atual = VD_NULO;
     VIDEO_doda_campo  = VD_NULO;
    }

  return(TRUE);
}




