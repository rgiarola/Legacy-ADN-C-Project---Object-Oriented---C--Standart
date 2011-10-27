#include <INCVIDEO.H>

VIDEO_TELA_monta_buffer_entrada(campoedit,campo,buffer)
VIDEO_EDITA_CAMPO *campoedit;
VIDEO_CAMPO_TELA  *campo;
char              *buffer;
{
 char   *buffer_aux;
 INT2    ret,
        tamaux;
 double doubleaux;
 BYTE   ascii,scan;

 if (VIDEO_ALLOC_MEM(buffer_aux,campoedit->tamanho+50) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_MONTA_ENTRADA);
     return(FALSE);
    }

 VIDEO_setmem(buffer_aux,campoedit->tamanho+50,0);

 if (campoedit->autos&VIDEO_EDITA_AUTOIMP)
    {
     switch(campo->tipo)
      {
       case VIDEO_CAMPO_BYTE:
            ultoa(DW(CBYTE(campo->buffer_binario)),buffer_aux,10);
            break;

       case VIDEO_CAMPO_WORD:
            ultoa(DW(CWORD(campo->buffer_binario)),buffer_aux,10);
            break;

       case VIDEO_CAMPO_DWORD:
            ultoa(CDWORD(campo->buffer_binario),buffer_aux,10);
            break;

       case VIDEO_CAMPO_SHINT:
            itoa(I(CCHAR(campo->buffer_binario)),buffer_aux,10);
            break;

       case VIDEO_CAMPO_INT:
            itoa(CINT(campo->buffer_binario),buffer_aux,10);
            break;

       case VIDEO_CAMPO_LONG:
            ltoa(CLONG(campo->buffer_binario),buffer_aux,10);
            break;

       case VIDEO_CAMPO_FLOAT:
            sprintf(buffer_aux,VIDEO_TELA_mascara_mont_double,
                               CFLOAT(campo->buffer_binario));
            break;

       case VIDEO_CAMPO_DOUBLE:
            sprintf(buffer_aux,VIDEO_TELA_mascara_mont_double,
                               CDOUBLE(campo->buffer_binario));
            break;

       case VIDEO_CAMPO_DATA:
            VIDEO_TELA_dateout(campo->buffer_binario,buffer_aux,
                               campoedit->mascara);
            break;

       case VIDEO_CAMPO_TIME:
            VIDEO_TELA_horaout(campo->buffer_binario,buffer_aux,
                               campoedit->mascara);
            break;

       case VIDEO_CAMPO_CARACTER:
            *buffer_aux = *campo->buffer_binario;
            *(buffer_aux + 1) = '\0';
            break;

       case VIDEO_CAMPO_STRING:
            VIDEO_movbloco(buffer_aux,campo->buffer_binario,
                           campoedit->tamanho);
            *(buffer_aux + campoedit->tamanho) = '\0';
            break;

       default :VIDEO_mostra_mens_erro(VIDEO_TELA_tipo_campo_invalido,
                                       VIDEO_ERRO_tipo_campo_inval_men);
                VIDEO_FREE_ALLOC_MEM(buffer_aux);
                return(FALSE);
      }

     if (campoedit->tipo == VIDEO_EDITA_NUMERO)
        {
         if (campoedit->decimais && *buffer_aux)
             VIDEO_TELA_coloca_ponto(buffer_aux,campoedit->decimais);
           else
              if ((strlen(buffer_aux) == 1) && (*buffer_aux == '0') &&
                  campoedit->autos&VIDEO_EDITA_EDTMASC)
                  *buffer_aux = '\0';
        }
    }

 if ((tamaux = strlen(buffer_aux)) > campoedit->tamanho)
     VIDEO_copbloco(buffer_aux,buffer_aux+tamaux-campoedit->tamanho,
                                         campoedit->tamanho+1);
 strcpy(buffer,buffer_aux);
 VIDEO_FREE_ALLOC_MEM(buffer_aux);
 return(TRUE);
}





