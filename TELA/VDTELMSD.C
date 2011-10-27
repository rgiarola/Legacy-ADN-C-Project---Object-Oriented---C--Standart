#include <INCVIDEO.H>

INT2 VIDEO_TELA_monta_buffer_saida(campoedit,campo,buffer)
VIDEO_EDITA_CAMPO *campoedit;
VIDEO_CAMPO_TELA  *campo;
char              *buffer;
{
 char   *aux,
        *buffer_aux,
        *ptrwork;
 INT2    tamaux,
        decimais;
 double doubleaux;

 if (VIDEO_ALLOC_MEM(buffer_aux,campoedit->tamanho+50) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_MONTA_SAIDA);
     return(FALSE);
    }

 if (campoedit->tipo)
    {
     aux = campoedit->buffer;
     while(*aux)
      {
       if (*aux == ' ')
          *aux = '0';
       ++aux;
      }
    }

 decimais = 0;
 if (campoedit->tipo && campoedit->decimais)
    {
     decimais = campoedit->decimais;
     doubleaux = 1;
     while(decimais--)
           doubleaux *= 10.0;
     sprintf(buffer_aux,VIDEO_TELA_mascara_mont_double,
                        (atof(buffer) * doubleaux));
     ptrwork = buffer_aux;
    }
  else
    ptrwork = buffer;

 tamaux = strlen(ptrwork) + (decimais!=0);

 if (tamaux > campoedit->tamanho)
     VIDEO_copbloco(ptrwork,ptrwork+tamaux-campoedit->tamanho,
                                         campoedit->tamanho+1);
 switch(campo->tipo)
  {
   case VIDEO_CAMPO_BYTE:
        CBYTE(campo->buffer_binario)  = B(atoi(ptrwork));
        break;

   case VIDEO_CAMPO_WORD:
        CWORD(campo->buffer_binario)  = W(atol(ptrwork));
        break;

   case VIDEO_CAMPO_DWORD:
        CDWORD(campo->buffer_binario) = DW(strtoul(ptrwork,&aux,10));
        break;

   case VIDEO_CAMPO_SHINT:
        CCHAR(campo->buffer_binario)  = C(atoi(ptrwork));
        break;

   case VIDEO_CAMPO_INT:
        CINT(campo->buffer_binario)   = I(atoi(ptrwork));
        break;

   case VIDEO_CAMPO_LONG:
        CLONG(campo->buffer_binario)  = atol(ptrwork);
        break;

   case VIDEO_CAMPO_FLOAT:
        CFLOAT(campo->buffer_binario) = atof(ptrwork);
        break;

   case VIDEO_CAMPO_DOUBLE:
        CDOUBLE(campo->buffer_binario) = atof(ptrwork);
        break;

   case VIDEO_CAMPO_TIME:
        VIDEO_TELA_horain((DWORD *) campo->buffer_binario,
                                    ptrwork,campoedit->mascara);
        break;

   case VIDEO_CAMPO_DATA:
        VIDEO_TELA_datein((DATET *) campo->buffer_binario,
                             ptrwork,campoedit->mascara);
        break;

   case VIDEO_CAMPO_CARACTER:
        if (*ptrwork == ' ')
            *ptrwork = '\0';
        *campo->buffer_binario = *ptrwork;
        break;

   case VIDEO_CAMPO_STRING:
        if ((aux = strchr(ptrwork,' ')) != VD_NULO)
           if (aux == ptrwork)
              {
               while(*++aux == ' ');
               if (*aux)
                   VIDEO_copbloco(ptrwork,aux,strlen(aux)+1);
                else
                   *ptrwork = '\0';
              }
        tamaux = strlen(ptrwork);
        aux = ptrwork + tamaux - (tamaux > 0);
        while(*aux == ' ' && aux != ptrwork)
             --aux;
        *(aux + 1) = '\0';
        tamaux = strlen(ptrwork);
        VIDEO_setmem(campo->buffer_binario,campoedit->tamanho+1,0);
        strcpy(campo->buffer_binario,ptrwork);
        break;
  }

 VIDEO_FREE_ALLOC_MEM(buffer_aux);
 return(TRUE);
}


VIDEO_TELA_datein(bfdata,bfedit,mascara)
DATET *bfdata;
char  *bfedit,
      *mascara;
{
 char  buffer[3][5],
       *ptrdest[3],
       *ptrbfteste;
 COUNT posdiabf,   posmesbf,
       posanobf,   contseq,
       tamano  ,   dia,
       mes     ,   ano,
       flag_ano=FALSE;

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
                  posdiabf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  VIDEO_movbloco(buffer[posdiabf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;
     case 'M':
     case 'm':if (posmesbf == -1)
                 {
                  posmesbf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  VIDEO_movbloco(buffer[posmesbf],ptrbfteste,2);
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
                  posanobf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  VIDEO_movbloco(buffer[posanobf],ptrbfteste,tamano);
                  if(tamano==2) flag_ano=TRUE;
                 }
              ++ptrbfteste;
              break;
    }
   ++mascara;
  }

 dia = posdiabf > -1 ? atoi(buffer[posdiabf])      : 1;
 mes = posmesbf > -1 ? atoi(buffer[posmesbf])      : 1;
 ano = posanobf > -1 ? atoi(buffer[posanobf])      : 1;

 /* L¢gica com Bug Ano 00
 if ( flag_ano && (ano!=0) )
    {
     // Trata Bug do Milˆnio
     if (ano < 40)
        ano += 2000;    // S‚culo 21
      else
        ano += 1900;    // S‚culo 20
    }
  */

 if ( flag_ano )
    {
     // Trata Bug do Milˆnio
     if (ano < 40)
        ano += 2000;    // S‚culo 21
      else
        ano += 1900;    // S‚culo 20
    }

 CDATET(bfdata) = datein(ano, mes, dia);

 return(0);
}

VIDEO_TELA_horain(bfhora,bfedit,mascara)
long  *bfhora;
char  *bfedit,
      *mascara;
{
 char  buffer[3][5],
       *ptrdest[3],
       *ptrbfteste;
 COUNT poshorabf, posminbf,
       possegbf , contseq ,
       cont;

 for (cont = 0;cont < 3;cont++)
     strcpy(buffer[cont],VIDEO_texto_mascara_BB);

 ptrbfteste = bfedit;
 poshorabf  = posminbf = possegbf = -1;
 cont       = contseq  = 0;

 while(*mascara)
  {
   switch(*mascara)
    {
     char *aux;
     case 'h':if (poshorabf == -1)
                 {
                  poshorabf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  VIDEO_movbloco(buffer[poshorabf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;

     case 'm':if (posminbf == -1)
                 {
                  posminbf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  VIDEO_movbloco(buffer[posminbf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;

     case 's':if (possegbf == -1)
                 {
                  possegbf = contseq;
                  ptrdest[contseq++] = ptrbfteste;
                  VIDEO_movbloco(buffer[possegbf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;
    }
   ++mascara;
  }

 CDWORD(bfhora) = VIDEO_timein(poshorabf > -1 ? atoi(buffer[poshorabf]): 0,
                               posminbf  > -1 ? atoi(buffer[posminbf]) : 0,
                               possegbf  > -1 ? atoi(buffer[possegbf]) : 0);
 return(0);
}


