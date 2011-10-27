#include <INCVIDEO.H>

INT2 VIDEO_TELA_editdata(campoedit,param)
VIDEO_EDITA_CAMPO *campoedit;
VIDEO_NUCLEO_SERV *param;
{
 char mascara[5],
      buffer[3][5],
      *ptrdest[3],
      *ptrbuffer,
      *ptrmasc,
      *ptrbfteste,
      *mascteste;

 INT2     posmasc[3], posdia,
         posmes,     posano,
         posdiabf,   posmesbf,
         posanobf,   contmasc,
         posinicio,  posfim,
         contseq,    tamcampo,
         tamano,     ret;
 BOOLEAN flags ,     flagdia,
         flagmes,    flagano;

 strcpy(mascara,VIDEO_texto_mascara_ZZ);
 for (tamcampo = 0;tamcampo < 3;tamcampo++)
     strcpy(buffer[tamcampo],VIDEO_texto_mascara_BB);

 mascteste = ptrmasc =  campoedit->mascara;
 ptrbfteste = ptrbuffer = campoedit->buffer;
 campoedit->mascara =  mascara;
 posinicio = posdia = posmes = posano =
 posdiabf = posmesbf = posanobf = -1;
 tamano = contmasc = contseq = 0;
 flagdia = flagmes = flagano = 1;
 if (atol(ptrbuffer) == 0)
    VIDEO_setmem(ptrbuffer,campoedit->tamanho,' ');

 while(*mascteste)
  {
   switch(*mascteste)
    {
     char *aux;
     case 'D':
     case 'd':if (posinicio == -1)
                  posinicio = contmasc;
              if (posdia == -1)
                 {
                  flagdia <<= contseq;
                  posdiabf = contseq;
                  ptrdest[contseq] = ptrbfteste;
                  posfim = posmasc[contseq++] = posdia = contmasc;
                  VIDEO_movbloco(buffer[posdiabf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;

     case 'M':
     case 'm':if (posinicio == -1)
                  posinicio = contmasc;
              if (posmes == -1)
                 {
                  flagmes <<= contseq;
                  ptrdest[contseq] = ptrbfteste;
                  posmesbf = contseq;
                  posfim = posmasc[contseq++] = posmes = contmasc;
                  VIDEO_movbloco(buffer[posmesbf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;

     case 'A':
     case 'a':if (posinicio == -1)
                  posinicio = contmasc;
              if (!tamano)
                 {
                  aux = mascteste;
                  while(*aux == 'a' || *aux == 'A')
                   {
                    ++tamano;
                    ++aux;
                   }
                 }
              if (posano == -1)
                 {
                  flagano <<= contseq;
                  posanobf = contseq;
                  ptrdest[contseq] = ptrbfteste;
                  posfim = posmasc[contseq++] = posano = contmasc;
				  VIDEO_movbloco(buffer[posanobf],ptrbfteste,tamano);
                 }
              ++ptrbfteste;
              break;
    }
   ++contmasc;
   ++mascteste;
  }

 if (posinicio == -1)
     return(FALSE);

 VIDEO_setatrib(campoedit->col,campoedit->col + strlen(ptrmasc) - 1,
                campoedit->lin,campoedit->lin,campoedit->cor);

 contmasc = 0;
 contseq = campoedit->col;
 tamcampo = campoedit->tamanho;
 do
  {
   INT2 dia,
       mes,
       ano;

   campoedit->buffer  = buffer[contmasc];
   campoedit->mascara = mascara;
   mascara[2]         = '\0';
   campoedit->tamanho = 2;
   campoedit->col     = contseq + posmasc[contmasc];

   if (posmasc[contmasc] == posano)
      {
       campoedit->tamanho = tamano;
       VIDEO_setmem(mascara,tamano,'Z');
       mascara[tamano]    = '\0';
      }

   ret = VIDEO_EDITA_mascara_campo(campoedit);

   campoedit->buffer  = ptrbuffer;
   campoedit->tamanho = tamcampo;
   campoedit->mascara = ptrmasc;
   campoedit->col     = contseq;

   if (posdiabf > -1)
      {
       VIDEO_movbloco(ptrdest[posdiabf],buffer[posdiabf],2);
       dia = atoi(buffer[posdiabf]);
      }
    else
      dia = -1;

   if (posmes > -1)
      {
       mes = atoi(buffer[posmesbf]);
       VIDEO_movbloco(ptrdest[posmesbf],buffer[posmesbf],2);
      }
    else
      mes = -1;

   if (posanobf > -1)
      {
       ano = atoi(buffer[posanobf]);
       VIDEO_movbloco(ptrdest[posanobf],buffer[posanobf],tamano);
      }
    else
      ano = -1;

   *(ptrbuffer + tamcampo) = '\0';

   flags = FALSE;

   if (dia > -1)
       if (dia > 31 || !dia)
          flags = flagdia;

   if (mes > -1)
      {
       if (dia > -1)
          switch(mes)
           {
            INT2 aux;
            case 4:
            case 6:
            case 9:
            case 11:if (dia > 30)
                       flags |= flagdia;
                    break;

            case 2 :if (ano > -1)
                       {
                        aux = !(ano%4) + 28;
                        if (dia > aux)
                           flags |= flagdia;
                       }
                     else
                       if (dia > 28)
                          flags |= flagdia;
                    break;

            case 0 :flags |= flagmes;
                    break;
           }
        if (mes > 12)
            flags |= flagmes;
      }

   /* Bug do Milˆnio
   if (!ano)
       flags |= flagano;
    */

   if ((ano > -1) && (dia > -1) && (mes == 2))
      {
       INT2 aux;
       aux = !(ano%4) + 28;
       if (dia > aux)
           flags |= flagano;
      }

   switch(ret)
    {
     case VD_MTTECLA(VD_NULO,ESQUERDA):if (posmasc[contmasc] == posinicio)
                                          {
                                           if (flags)
                                               VIDEO_setmem(ptrbuffer,tamcampo,' ');
                                           return(ret);
                                          }
                                       --contmasc;
                                       break;

     case VD_MTTECLA(10,ENTERSCAN)    :if (flags&(1<<contmasc))
                                            continue;

     case VD_MTTECLA(VD_NULO,DIREITA) :if (posmasc[contmasc] == posfim)
                                          {
                                           if (flags)
                                               VIDEO_setmem(ptrbuffer,tamcampo,' ');
                                           return(ret);
                                          }
                                       ++contmasc;
                                       break;
     default:if (flags)
                 VIDEO_setmem(ptrbuffer,tamcampo,' ');
             return(ret);
    }
  }while(TRUE);
}

INT2 VIDEO_TELA_edithora(campoedit,param)
VIDEO_EDITA_CAMPO *campoedit;
VIDEO_NUCLEO_SERV *param;
{
 char mascara[5],
      buffer[3][3],
      *ptrdest[3],
      *ptrbuffer,
      *ptrmasc,
      *ptrbfteste,
      *mascteste;

 INT2    posmasc[3], poshora,
         posmin,     posseg,
         poshorabf,  posminbf,
         possegbf,   contmasc,
         posinicio,  posfim,
         contseq,    tamcampo,
         tamseg,     ret;
 BOOLEAN flags ,     flaghora,
         flagmin,    flagseg;

 strcpy(mascara,VIDEO_texto_mascara_ZZ);

 for (tamcampo = 0;tamcampo < 3;tamcampo++)
     strcpy(buffer[tamcampo],VIDEO_texto_mascara_BB);

 mascteste = ptrmasc =  campoedit->mascara;
 ptrbfteste = ptrbuffer = campoedit->buffer;
 campoedit->mascara =  mascara;
 posinicio = poshora = posmin = posseg =
 poshorabf = posminbf = possegbf = -1;
 tamseg = contmasc = contseq = 0;
 flaghora = flagmin = flagseg = 1;

 if (atol(ptrbuffer) == 0)
    VIDEO_setmem(ptrbuffer,campoedit->tamanho,' ');

 while(*mascteste)
  {
   switch(*mascteste)
    {
     char *aux;
     case 'h':if (posinicio == -1)
                  posinicio = contmasc;
              if (poshora == -1)
                 {
                  flaghora <<= contseq;
                  poshorabf = contseq;
                  ptrdest[contseq] = ptrbfteste;
                  posfim = posmasc[contseq++] = poshora = contmasc;
                  VIDEO_movbloco(buffer[poshorabf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;

     case 'm':if (posinicio == -1)
                  posinicio = contmasc;
              if (posmin == -1)
                 {
                  flagmin <<= contseq;
                  ptrdest[contseq] = ptrbfteste;
                  posminbf = contseq;
                  posfim = posmasc[contseq++] = posmin = contmasc;
                  VIDEO_movbloco(buffer[posminbf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;

     case 's':if (posinicio == -1)
                  posinicio = contmasc;
              if (posseg == -1)
                 {
                  flagseg <<= contseq;
                  ptrdest[contseq] = ptrbfteste;
                  possegbf = contseq;
                  posfim = posmasc[contseq++] = posseg = contmasc;
                  VIDEO_movbloco(buffer[possegbf],ptrbfteste,2);
                 }
              ++ptrbfteste;
              break;
    }
   ++contmasc;
   ++mascteste;
  }

 if (posinicio == -1)
     return(FALSE);

 VIDEO_setatrib(campoedit->col,campoedit->col + strlen(ptrmasc) - 1,
                campoedit->lin,campoedit->lin,campoedit->cor);

 contmasc = 0;
 contseq = campoedit->col;
 tamcampo = campoedit->tamanho;
 do
  {
   INT2 hora,
       min,
       seg;

   campoedit->buffer  = buffer[contmasc];
   campoedit->mascara = mascara;
   mascara[2]         = '\0';
   campoedit->tamanho = 2;
   campoedit->col     = contseq + posmasc[contmasc];

   ret = VIDEO_EDITA_mascara_campo(campoedit);

   campoedit->buffer  = ptrbuffer;
   campoedit->tamanho = tamcampo;
   campoedit->mascara = ptrmasc;
   campoedit->col     = contseq;

   if (poshorabf > -1)
      {
       VIDEO_movbloco(ptrdest[poshorabf],buffer[poshorabf],2);
       hora = atoi(buffer[poshorabf]);
      }
    else
      hora = -1;

   if (posminbf > -1)
      {
       min = atoi(buffer[posminbf]);
       VIDEO_movbloco(ptrdest[posminbf],buffer[posminbf],2);
      }
    else
      min = -1;

   if (possegbf > -1)
      {
       seg = atoi(buffer[possegbf]);
       VIDEO_movbloco(ptrdest[possegbf],buffer[possegbf],2);
      }
    else
      seg = -1;

   *(ptrbuffer + tamcampo) = '\0';

   flags = FALSE;

   if (hora > -1)
       if (hora > 23)
          flags = flaghora;

   if (min > -1)
       if (min > 59)
         flags |= flagmin;

   if (seg > -1)
      if (seg > 59)
          flags |= flagseg;

   switch(ret)
    {
     case VD_MTTECLA(VD_NULO,ESQUERDA):if (posmasc[contmasc] == posinicio)
                                          {
                                           if (flags)
                                               VIDEO_setmem(ptrbuffer,tamcampo,' ');
                                           return(ret);
                                          }
                                       --contmasc;
                                       break;

     case VD_MTTECLA(10,ENTERSCAN)    :if (flags&(1<<contmasc))
                                            continue;

     case VD_MTTECLA(VD_NULO,DIREITA) :if (posmasc[contmasc] == posfim)
                                          {
                                           if (flags)
                                               VIDEO_setmem(ptrbuffer,tamcampo,' ');
                                           return(ret);
                                          }
                                       ++contmasc;
                                       break;
     default:if (flags)
                 VIDEO_setmem(ptrbuffer,tamcampo,' ');
             return(ret);
    }
   }while(TRUE);
}


