#include <INCVIDEO.H>

INT2 VIDEO_TELA_monta_buffer_mascara(campoedit,buffer_binario,tipo,cor)
VIDEO_EDITA_CAMPO *campoedit;
char			  *buffer_binario;
INT2               tipo;
BYTE			  cor;
{
 char   *buffer_aux;
 INT2    ret,
        tamaux;
 BYTE   ascii,scan;

 if (VIDEO_ALLOC_MEM(buffer_aux,campoedit->tamanho+50) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_MONTA_MASCARA_1);
     return(FALSE);
    }

 switch(tipo)
  {
   case VIDEO_CAMPO_BYTE:
		ultoa(DW(CBYTE(buffer_binario)),campoedit->buffer,10);
		break;

   case VIDEO_CAMPO_WORD:
		ultoa(DW(CWORD(buffer_binario)),campoedit->buffer,10);
		break;

   case VIDEO_CAMPO_DWORD:
		ultoa(CDWORD(buffer_binario),campoedit->buffer,10);
		break;

   case VIDEO_CAMPO_SHINT:
		itoa(I(CCHAR(buffer_binario)),campoedit->buffer,10);
		break;

   case VIDEO_CAMPO_INT:
		itoa(CINT(buffer_binario),campoedit->buffer,10);
		break;

   case VIDEO_CAMPO_LONG:
		ltoa(CLONG(buffer_binario),campoedit->buffer,10);
		break;

   case VIDEO_CAMPO_DOUBLE:
        sprintf(campoedit->buffer,VIDEO_TELA_mascara_mont_double,CDOUBLE(buffer_binario));
		break;

   case VIDEO_CAMPO_FLOAT:
        sprintf(campoedit->buffer,VIDEO_TELA_mascara_mont_double,CFLOAT(buffer_binario));
		break;

   case VIDEO_CAMPO_TIME:
        VIDEO_TELA_horaout(buffer_binario,campoedit->buffer,
                           campoedit->mascara);
		break;

   case VIDEO_CAMPO_DATA:
        VIDEO_TELA_dateout(buffer_binario,campoedit->buffer,
                           campoedit->mascara);
        break;

   case VIDEO_CAMPO_CARACTER:
        *campoedit->buffer = *buffer_binario;
        *(campoedit->buffer + 1) = '\0';
        break;

   case VIDEO_CAMPO_STRING:
        VIDEO_movbloco(campoedit->buffer,buffer_binario,
					   campoedit->tamanho);
		*(campoedit->buffer + campoedit->tamanho) = '\0';
		break;

   default : VIDEO_mostra_mens_erro(VIDEO_TELA_tipo_campo_invalido,
                                    VIDEO_ERRO_tipo_campo_inval_mma);
			 VIDEO_FREE_ALLOC_MEM(buffer_aux);
			 return(FALSE);
  }

  *(buffer_aux+campoedit->tamanho) = '\0';

 if (campoedit->autos&VIDEO_EDITA_VALOR)
    {
     VIDEO_monta_mascara(campoedit->buffer,campoedit->mascara,buffer_aux,
                         VIDEO_EDITA_LIMPMASC&campoedit->autos ? ' ' : 0,
                         (campoedit->autos&VIDEO_EDITA_NAOMOSTRA));
     VIDEO_tprt_l(campoedit->col,campoedit->lin,buffer_aux,cor);
    }
  else
    {
     if (campoedit->tipo)
        {
         char *buffer_loc;

         if ((atof(campoedit->buffer) == 0.00) &&
              campoedit->autos&VIDEO_EDITA_EDTMASC && tipo != VIDEO_CAMPO_TIME)
            *campoedit->buffer = '\0';

         if (VIDEO_ALLOC_MEM(buffer_loc,campoedit->tamanho+1) == VD_NULO)
            {
             VIDEO_mostra_mens_erro_alloc(ALOCACAO_MONTA_MASCARA_2);
             return(FALSE);
            }
         strcpy(buffer_loc,campoedit->buffer);
         VIDEO_setmem(campoedit->buffer,campoedit->tamanho,' ');
         strcpy(campoedit->buffer+(campoedit->tamanho-strlen(buffer_loc)),
                buffer_loc);
         VIDEO_FREE_ALLOC_MEM(buffer_loc);
        }

     VIDEO_display_mascara(campoedit->col,campoedit->lin,campoedit->buffer,
          campoedit->mascara,cor, FALSE,(campoedit->autos&VIDEO_EDITA_NAOMOSTRA));
    }

 VIDEO_FREE_ALLOC_MEM(buffer_aux);
 return(TRUE);
}



VIDEO_TELA_dateout(bfdata,bfedit,mascara)
DATET *bfdata;
char  *bfedit,
      *mascara;
{
 char  buffer[3][5],
       *ptrdest[3],
       *ptrbfteste;
 INT2   posdiabf,   posmesbf,
       posanobf,   contseq,
       tamano  ;
 COUNT dia     ,   mes,
       ano     ,   sem;

 if (CDATET(bfdata))
    dateout( CDATET(bfdata), &ano,   &mes, &dia, &sem);
  else
    dia = mes = ano = 0;

 for (tamano = 0;tamano < 3;tamano++)
     strcpy(buffer[tamano],VIDEO_texto_mascara_BB);

 ptrbfteste = bfedit;
 posdiabf   = posmesbf = posanobf = -1;
 tamano     = contseq  = 0;

 while(*mascara)
  {
   switch(*mascara)
    {
     char *aux;
     case 'D':
     case 'd':if (posdiabf == -1)
                 {
                  char bufferaux[10];
                  posdiabf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  sprintf(bufferaux,"%02d",dia);
                  VIDEO_movbloco(ptrbfteste,bufferaux,2);
                 }
              ++ptrbfteste;
              break;
     case 'M':
     case 'm':if (posmesbf == -1)
                 {
                  char bufferaux[10];
                  posmesbf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  sprintf(bufferaux,"%02d",mes);
                  VIDEO_movbloco(ptrbfteste,bufferaux,2);
                 }
              ++ptrbfteste;
              break;

     case 'A':
     case 'a':if (!tamano)
                 {
                  aux = mascara;
                  while(*aux == 'a' || *aux == 'A')
                   {
                    ++tamano;
                    ++aux;
                   }
                 }
              if (posanobf == -1)
                 {
                  char bufferaux[10],
                       bufferaux2[10];
                  posanobf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  sprintf(bufferaux2,"%%0%dd",tamano);
                  /* Tratamento Anterior

                  sprintf(bufferaux,bufferaux2,
                         ( (tamano==2)&&(ano!=0) ? (ano-1900) : ano) );

                   */

                  if (tamano==2 && ano!=0)
                     {
                      if (ano<2000)
                         sprintf(bufferaux,bufferaux2,ano-1900);
                       else
                         sprintf(bufferaux,bufferaux2,ano-2000);
                     }
                   else
                    sprintf (bufferaux,bufferaux2,ano); // Sem Convers„o (FULL)

                  VIDEO_movbloco(ptrbfteste,bufferaux,tamano);
                 }
	      ++ptrbfteste;
    }
   ++mascara;
  }
 *ptrbfteste = '\0';

 return(0);
}

VIDEO_TELA_horaout(bfhora,bfedit,mascara)
DWORD *bfhora;
char  *bfedit,
      *mascara;
{
 char  buffer[3][5],
       *ptrdest[3],
       *ptrbfteste;
 INT2   poshorabf, posminbf,
        possegbf , cont   ,
       hora     ,   min,
       seg     ,   contseg = 0;

 if (CDWORD(bfhora))
    VIDEO_timeout(CDWORD(bfhora),&hora,&min,&seg);
  else
    hora = min = seg = 0;

 for (cont = 0;cont < 3;cont++)
     strcpy(buffer[cont],VIDEO_texto_mascara_BB);

 ptrbfteste = bfedit;
 poshorabf  = posminbf = possegbf = -1;

 while(*mascara)
  {
   switch(*mascara)
    {
     char *aux;
     case 'h':if (poshorabf == -1)
                 {
                  char bufferaux[10];
                  poshorabf = contseg;
                  ptrdest[contseg++] = ptrbfteste;
                  sprintf(bufferaux,"%02d",hora);
                  VIDEO_movbloco(ptrbfteste,bufferaux,2);
                 }
              ++ptrbfteste;
              break;
     case 'm':if (posminbf == -1)
                 {
                  char bufferaux[10];
                  posminbf = contseg;
                  ptrdest[contseg++] = ptrbfteste;
                  sprintf(bufferaux,"%02d",min);
                  VIDEO_movbloco(ptrbfteste,bufferaux,2);
                 }
              ++ptrbfteste;
              break;

     case 's':if (possegbf == -1)
                 {
                  char bufferaux[10];
                  possegbf = contseg;
                  ptrdest[contseg++] = ptrbfteste;
                  sprintf(bufferaux,"%02d",seg);
                  VIDEO_movbloco(ptrbfteste,bufferaux,cont);
                 }
	      ++ptrbfteste;
	      break;
    }
   ++mascara;
  }
 *ptrbfteste = '\0';

 return(0);
}



