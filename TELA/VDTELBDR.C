#include <INCVIDEO.H>

VD_VOID VIDEO_TELA_busca_dadosrelacional(campo,controle)
VIDEO_CAMPO_TELA *campo;
WORD              controle;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_CAMPO_CONSISTENCIA *consiste_valkey;
 double                   valor_teste;
 INT2                      flagtipo,retorno,
                          tmpfil,arquivo,
                          ret,indice;
 unsigned long int        posvalkey;
 IDE_ARQUIVOS			  *work_ifil;
 char                     *buffer,
                          *buffer_rec;

 if ((consiste = campo->consiste) == VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
    return;

 flagtipo = TRUE;
 switch(campo->tipo)
  {
   case VIDEO_CAMPO_BYTE:
        valor_teste = D(CBYTE(campo->buffer_binario));
        break;
   case VIDEO_CAMPO_WORD:
        valor_teste = D(CWORD(campo->buffer_binario));
        break;
   case VIDEO_CAMPO_DWORD:
        valor_teste = D(CDWORD(campo->buffer_binario));
        break;
   case VIDEO_CAMPO_SHINT:
        valor_teste = D(CCHAR(campo->buffer_binario));
        break;
   case VIDEO_CAMPO_INT:
        valor_teste = D(CINT(campo->buffer_binario));
        break;
   case VIDEO_CAMPO_LONG:
        valor_teste = D(CLONG(campo->buffer_binario));
        break;
   case VIDEO_CAMPO_DOUBLE:
        valor_teste = CDOUBLE(campo->buffer_binario);
        break;
   case VIDEO_CAMPO_DATA:
        valor_teste = D(CDWORD(campo->buffer_binario));
        break;
   case VIDEO_CAMPO_STRING:
        flagtipo = FALSE;
        break;
   case VIDEO_CAMPO_CARACTER:
        flagtipo = 2;
        break;
  }

 do
  {
   retorno = FALSE;

   if (consiste->tipocons == VIDEO_TELA_VALKEY)
      {
       switch(flagtipo)
        {
         char *buffer;

         case TRUE: if (valor_teste==0.00)
                        retorno=TRUE;
                     break;

         case FALSE:buffer=campo->buffer_binario;
                    while( *buffer && *buffer == ' ' )
                      ++buffer;
                    retorno=!(*buffer);
                    break;

         case     2:retorno = (*campo->buffer_binario==' ' ||
                               *campo->buffer_binario=='0' ||
                               !(*campo->buffer_binario) );
                    break;
        }

       if (retorno)
          {
           VIDEO_inic_transp(consiste->objetocons.consdb->transpdados);
           ++consiste;
           continue;
          }

       if (consiste->objetocons.consdb)
          {
           indice = consiste->objetocons.consdb->indice;

           if (!CTREE_find(indice,consiste->objetocons.consdb->segchave,
                        FIND_IGUAL, CT_LE_DADOS))
              {
               if (consiste->objetocons.consdb->transpdados)
                   CTREE_cpydoda(consiste->objetocons.consdb->transpdados);

#ifdef DATABASE_CTREE
               consiste_valkey = campo->consiste;

               arquivo = CTREE_keyfil(indice);
               tmpfil  = CTREE_tmpfil(arquivo);

               while(consiste_valkey->tipocons)
                {
                 if ((consiste_valkey->tipocons == VIDEO_TELA_CONS_POSICIONA_DB) &&
                     (CTREE_keyfil(consiste_valkey->objetocons.consdb->indice) ==
                      arquivo))
                     {
                      consiste_valkey->objetocons.consdb->posicao =
                      DATABASE_CurrentFileOffset(tmpfil);
                      break;
                     }
                 ++consiste_valkey;
                }
#endif
              }
            else
              VIDEO_inic_transp(consiste->objetocons.consdb->transpdados);
          }
      }
   ++consiste;
  }while(consiste->tipocons);
}

