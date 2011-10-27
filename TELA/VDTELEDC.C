#include <INCVIDEO.H>

INT2 VIDEO_TELA_editdata(VIDEO_EDITA_CAMPO *campoedit,VIDEO_NUCLEO_SERV *param);
INT2 VIDEO_TELA_edithora(VIDEO_EDITA_CAMPO *campoedit,VIDEO_NUCLEO_SERV *param);

INT2 VIDEO_TELA_edita_campo(campo,param)
VIDEO_CAMPO_TELA  *campo;
VIDEO_NUCLEO_SERV *param;
{
 VIDEO_EDITA_CAMPO        campoedit;
 char                     *buffer,
                          buffer_aux[200],*old_buffer;
 INT2                      ret,
                          tamaux;
 double                   doubleaux;
 VIDEO_TABFUNCAO          *tabfuncuser;
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 BOOLEAN                  editcampo = TRUE;

 //static char *ptralloc = VD_NULO;

 VIDEO_campo_atual = campo;
 VIDEO_cons_atual  = campo->consiste;
 VIDEO_doda_campo  = campo->dodacampo;

 if (campo->user_func)
	{
     tabfuncuser = VIDEO_funcao_tabfuncuser(campo->user_func);

     if (campo->flag_disparo&VIDEO_TELA_FDISPANT)
		 if (!tabfuncuser || !tabfuncuser->userfunc)
            {
             char buffer[200];
             sprintf(buffer,VIDEO_funcao_nao_enc,campo->user_func);
			 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_nao_encontrada);
            }
         else
/*
           (tabfuncuser->userfunc)(campo,VIDEO_TELA_FDISPANT,param);
*/
           if ((tabfuncuser->userfunc)(campo,VIDEO_TELA_FDISPANT,param))
              {
               VIDEO_TELA_display_campos(
                        PTR_CAST(VIDEO_CAMPO_TELA,param->VIDEO_campos),
                        param->VIDEO_numcampos,
                        param,VIDEO_FLAGVALIDA_CAMPO);
              }
    }

/*========================================================================
  SE CAMPO PROTEGIDO E NAO AUTERADO NAO EXECUTA ROTINA DE MONTAGEM DE CAMPO
======================================================================== */
 if (((consiste = campo->consiste) != VD_NULO) &&
      (consiste->tipocons == VIDEO_TELA_CONS_OLD_BUFFER))
     old_buffer = consiste->objetocons.old_buffer;
  else
     old_buffer = VD_NULO;

 if (campo->status&VIDEO_EDITA_PROTEGIDO)
    {
     editcampo = FALSE;
     if (!(campo->status&VIDEO_EDITA_NAOMOSTRA))
        {
         if (old_buffer)
             if (!CCHAR((old_buffer+sizeof(int))) ||
                 memcmp(campo->buffer_binario,
                        old_buffer+sizeof(int)+sizeof(char),
                        CINT(old_buffer)))
                 editcampo = TRUE;
               else
                 CCHAR((old_buffer+sizeof(int))) = TRUE;
              else
                editcampo = TRUE;
        }

     switch(I(param->VIDEO_servrec))
      {
       case I(VD_MTTECLA(VD_NULO,CTRL_END)):
            param->VIDEO_servrec = VD_MTTECLA(VD_NULO,ESQUERDA);
            break;

       case I(VD_MTTECLA(VD_NULO,CTRL_HOME)):
       case I(VIDEO_MTTECLA(VD_NULO ,ESCAPESCAN)):
       case I(VIDEO_MTTECLA(ESCAPE  ,ESCAPESCAN)):
       case I(VIDEO_MTTECLA(VD_NULO ,ALT_S)):
       case I(VIDEO_MTTECLA(VD_NULO ,ALT_O)):
       case I(VIDEO_MTTECLA(VD_NULO ,ALT_E)):
       case I(VIDEO_MTTECLA(VD_NULO ,ALT_I)):
       case I(VIDEO_MTTECLA(ENTER   ,ENTERSCAN)):
       case I(VIDEO_MTTECLA(CTRL_ENT,ENTERSCAN)):
       case I(VIDEO_MTTECLA(VD_NULO ,ALT_MENOS)):
       case I(VIDEO_MTTECLA(VD_NULO ,ALT_MAIS)):
       case I(VIDEO_MTTECLA(VD_NULO ,DESCE)):
       case I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK)):
       case I(VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK)):
       case I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV)):
       case I(VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTTRV)):
       case I(0):param->VIDEO_servrec = VD_MTTECLA(VD_NULO,DIREITA);
            break;

       case I(VIDEO_MTTECLA(VD_NULO ,SOBE)):
            param->VIDEO_servrec = VD_MTTECLA(VD_NULO,ESQUERDA);
      }

    }

 if (editcampo)
    {
     if (VIDEO_ALLOC_MEM(buffer,campo->tamanho+1) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_EDITA_CAMPO_1);
         param->VIDEO_servrec = VIDEO_MTTECLA(VD_NULO,DIREITA);
         return(FALSE);
        }

     campoedit.pegacaracter = VD_lepos;
     campoedit.col      = campo->col;
     campoedit.lin      = campo->lin;
     campoedit.tamanho  = campo->tamanho;
     campoedit.tipo     = ((campo->tipo != VIDEO_CAMPO_STRING) &&
                           (campo->tipo != VIDEO_CAMPO_CARACTER));
     campoedit.tabskip  = campo->tabskip;
     campoedit.buffer   = buffer;
     campoedit.cor      = campo->entrada;
     campoedit.mascara  = (campo->mascara)                     ?
                    VIDEO_EDITA_expande_mascara(campo->mascara):
                    VIDEO_NILL(char);
     campoedit.decimais = campo->decimais;

     campoedit.autos =
     (campo->autos&VIDEO_EDITA_AUTOSKIP)                         |
     ((campoedit.decimais ? campo->autos&VIDEO_EDITA_EDPONTO : 0)|
     (campo->autos&VIDEO_EDITA_LZEROS)                           |
     (campo->autos&VIDEO_EDITA_LSPACE)                           |
     (campo->autos&VIDEO_EDITA_AUTOIMP)                          |
     (campo->autos&VIDEO_EDITA_SINALMAIS)                        |
     (campo->autos&VIDEO_EDITA_SINALMENOS)                       |
     (campo->autos&VIDEO_EDITA_AUTOBLANK)                        |
     (campo->autos&VIDEO_EDITA_LIMPMASC)                         |
     (campo->autos&VIDEO_EDITA_VALOR)                            |
     (campo->autos&VIDEO_EDITA_EDTMASC)                          |
     (campo->autos&VIDEO_EDITA_PRENCH)                           |
     (campo->status&VIDEO_EDITA_NAOMOSTRA))                      ;

     *buffer = '\0';

     if (strlen(campoedit.mascara) && !(campo->status&VIDEO_EDITA_NAOTROCA))
        VIDEO_CLEAR_PIC(campoedit.col,campoedit.col+strlen(campoedit.mascara) - 1,
                         campoedit.lin,campoedit.lin,campo->saida);

     if (!VIDEO_TELA_monta_buffer_entrada(&campoedit,campo,buffer))
        {
         VIDEO_FREE_ALLOC_MEM(buffer);
         if (campoedit.mascara)
            {
             VIDEO_free_alloc_parametros(campoedit.mascara);
             param->VIDEO_servrec = VIDEO_MTTECLA(VD_NULO,DIREITA);
             return(FALSE);
            }
        }

     if (campoedit.tipo && (campoedit.autos&VIDEO_EDITA_EDTMASC))
        {
         char *buffer_aux;
         if (VIDEO_ALLOC_MEM(buffer_aux,campoedit.tamanho+1) == VD_NULO)
            {
             VIDEO_mostra_mens_erro_alloc(ALOCACAO_EDITA_CAMPO_2);
             VIDEO_FREE_ALLOC_MEM(buffer);
             if (campoedit.mascara)
                 VIDEO_free_alloc_parametros(campoedit.mascara);
             param->VIDEO_servrec = VIDEO_MTTECLA(VD_NULO,DIREITA);
             return(FALSE);
            }

         strcpy(buffer_aux,buffer);
         VIDEO_setmem(buffer,campoedit.tamanho,' ');
         strcpy(buffer+(campoedit.tamanho-strlen(buffer_aux)),buffer_aux);
         VIDEO_FREE_ALLOC_MEM(buffer_aux);
        }

     if (!(campo->status&VIDEO_EDITA_PROTEGIDO))
        {
         VIDEO_MOUSE_flagtravado = TRUE;
         VIDEO_MOUSE_timetrav    = FALSE;

         if (campo->status&VIDEO_EDITA_NAOTROCA)
            {
             BYTE ascii,scan;
             INT2  tamanho;

             VD_tcursor(6,7);

             tamanho = strlen(campoedit.mascara);
             if (!tamanho)
                tamanho = campo->tamanho;
             VIDEO_setatrib(campoedit.col,campoedit.col+tamanho-1,
                            campoedit.lin,campoedit.lin,campo->entrada);
             do
              {
               if (VIDEO_MOUSE_ativo)
                   VIDEO_MOUSE_habcursor();

               VD_lepos(campo->col,campo->lin,&ascii,&scan);

               if (VIDEO_MOUSE_ativo)
                   VIDEO_MOUSE_deshabcursor();

               ret = !VIDEO_testa_tabskip(ascii,scan,campo->tabskip);

               switch(I(VIDEO_MTTECLA(ascii,scan)))
                {
                 case I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK)):
                 case I(VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK)):
                 case I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV)):
                 case I(VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTTRV)):
                      ret = FALSE;
                      break;
                }
              }while(ret);

             ret = VIDEO_MTTECLA(ascii,scan);
             VIDEO_setatrib(campoedit.col,campoedit.col+tamanho-1,
                            campoedit.lin,campoedit.lin,campo->saida);
            }
          else
            {
             if ((campo->tipo == VIDEO_CAMPO_DATA) ||
                 (campo->tipo == VIDEO_CAMPO_TIME))
                VIDEO_TELA_monta_buffer_mascara(&campoedit,
                             campo->buffer_binario,campo->tipo,campo->entrada);

             if (campo->tipo == VIDEO_CAMPO_DATA)
                 ret = VIDEO_TELA_editdata(&campoedit,param);
               else
                 if (campo->tipo == VIDEO_CAMPO_TIME)
                     ret = VIDEO_TELA_edithora(&campoedit,param);
                  else
                    ret = (campoedit.autos&VIDEO_EDITA_EDTMASC)  ?
                           VIDEO_EDITA_mascara_campo(&campoedit) :
                           VIDEO_EDITA_campo(&campoedit,param);
             if (!ret)
                {
                 VIDEO_mostra_mens_erro(VIDEO_erro_edicao_campo,
                                        VIDEO_ERRO_edicao_de_linha);
                 VIDEO_FREE_ALLOC_MEM(buffer);
                 if (campoedit.mascara)
                     VIDEO_free_alloc_parametros(campoedit.mascara);
                 param->VIDEO_servrec = VIDEO_MTTECLA(VD_NULO,DIREITA);
                 return(FALSE);
                }
            }

         param->VIDEO_servrec = ret;

         (*VIDEO_TELA_tabserv_navegacao[0].VIDEO_funcao)(&campo,&param);

         VIDEO_MOUSE_flagtravado = FALSE;
        }

     VIDEO_TELA_monta_buffer_saida(&campoedit,campo,buffer);

     if (campoedit.mascara)
        VIDEO_TELA_monta_buffer_mascara(&campoedit,
           campo->buffer_binario,campo->tipo,
           campo->saida);
      else
       {
        VIDEO_CLEAR_PIC(campoedit.col,campoedit.col+campoedit.tamanho-1,
                 campoedit.lin,campoedit.lin,campo->saida);
        if (campo->status&VIDEO_EDITA_NAOMOSTRA)
           {
            if ((ret = strlen(buffer)) > 0)
                VIDEO_horizontal(campoedit.col,campoedit.col+ ret - 1,
                                 campoedit.lin,'*',campo->saida);
           }
         else
           VD_tprt_l(campoedit.col,campoedit.lin,buffer,campo->saida);
       }

	 if (campoedit.mascara)
        VIDEO_free_alloc_parametros(campoedit.mascara);

     VIDEO_FREE_ALLOC_MEM(buffer);
	}

 if (campo->flag_disparo&VIDEO_TELA_FDISPPOS && campo->user_func)
    {
     if (!tabfuncuser || !tabfuncuser->userfunc)
        {
         char   buffer[200];
         sprintf(buffer,VIDEO_funcao_nao_enc,campo->user_func);
         VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_nao_encontrada);
        }
      else
/*
        (tabfuncuser->userfunc)(campo,VIDEO_TELA_FDISPPOS,param);
*/
        if ((tabfuncuser->userfunc)(campo,VIDEO_TELA_FDISPPOS,param))
           {
            VIDEO_TELA_display_campos(
                     PTR_CAST(VIDEO_CAMPO_TELA,param->VIDEO_campos),
                     param->VIDEO_numcampos,
                     param,VIDEO_FLAGVALIDA_CAMPO);
           }
    }

 if (old_buffer)
    {
     VIDEO_movbloco(old_buffer+sizeof(int)+sizeof(char),campo->buffer_binario,
                    CINT(old_buffer));
     CCHAR(old_buffer+sizeof(int)) = TRUE;
    }

/*
 VD_gtxy(1,1);
 printf("%04X",param->VIDEO_servrec);
*/
 return(TRUE);
}

INT2 VIDEO_TELA_editdata(campoedit,param)
VIDEO_EDITA_CAMPO *campoedit;
VIDEO_NUCLEO_SERV *param;
{
 char mascara[5],
      buffer[3][6],
      *ptrdest[3],
      *ptrbuffer,
      *ptrmasc,
      *ptrbfteste,
      *mascteste;

 INT2    posmasc[3], posdia,
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
   switch(I(*mascteste))
    {
     char *aux;

     case I('D'):
     case I('d'):if (posinicio == -1)
                  posinicio = contmasc;
              if (posdia == -1)
                 {
                  flagdia <<= contseq;
                  posdiabf = contseq;
                  ptrdest[contseq] = ptrbfteste;
                  posfim = posmasc[contseq++] = posdia = contmasc;
                  VIDEO_movbloco(buffer[posdiabf],ptrbfteste,2);
                  *(buffer[posdiabf]+2) = 0;
                 }
              ++ptrbfteste;
              break;

     case I('M'):
     case I('m'):if (posinicio == -1)
                  posinicio = contmasc;
              if (posmes == -1)
                 {
                  flagmes <<= contseq;
                  ptrdest[contseq] = ptrbfteste;
                  posmesbf = contseq;
                  posfim = posmasc[contseq++] = posmes = contmasc;
                  VIDEO_movbloco(buffer[posmesbf],ptrbfteste,2);
                  *(buffer[posmesbf]+2) = 0;
                 }
              ++ptrbfteste;
              break;

     case I('A'):
     case I('a'):if (posinicio == -1)
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
                  *(buffer[posanobf]+tamano) = 0;
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
          switch(I(mes))
           {
            INT2 aux;
            case I(4):
            case I(6):
            case I(9):
            case I(11):if (dia > 30)
                       flags |= flagdia;
                    break;

            case I(2 ):if (ano > -1)
                       {
                        aux = !(ano%4) + 28;
                        if (dia > aux)
                           flags |= flagdia;
                       }
                     else
                       if (dia > 28)
                          flags |= flagdia;
                    break;

            case I(0 ):flags |= flagmes;
                    break;
           }
        if (mes > 12)
            flags |= flagmes;
      }

   /*
      Bug do Milˆnio ...
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

   switch(I(ret))
    {
     case I(VD_MTTECLA(VD_NULO,ESQUERDA)):if (posmasc[contmasc] == posinicio)
                                          {
                                           if (flags)
                                               VIDEO_setmem(ptrbuffer,tamcampo,' ');
                                           return(ret);
                                          }
                                       --contmasc;
                                       break;

     case I(VD_MTTECLA(10,ENTERSCAN)    ):if (flags&(1<<contmasc))
                                            continue;

     case I(VD_MTTECLA(VD_NULO,DIREITA) ):if (posmasc[contmasc] == posfim)
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
         contseq,    tamcampo,ret;
 BOOLEAN flags ,     flaghora,
         flagmin,    flagseg;

 strcpy(mascara,VIDEO_texto_mascara_ZZ);
 for (tamcampo = 0;tamcampo < 3;tamcampo++)
     strcpy(buffer[tamcampo],VIDEO_texto_mascara_BB);

 mascteste = ptrmasc =  campoedit->mascara;
 ptrbfteste = ptrbuffer = campoedit->buffer;
 campoedit->mascara =  mascara;
 contmasc = contseq = 0;
 posinicio = poshora = posmin = posseg =
 poshorabf = posminbf = possegbf = -1;
 flaghora = flagmin = flagseg = 1;

/*
 if (atol(ptrbuffer) == 0)
    VIDEO_setmem(ptrbuffer,campoedit->tamanho,' ');
*/

 while(*mascteste)
  {
/*-----------------------------------------------------------------------------
   VD_gtxy(1,6);
   printf("[%4d][%4d]",contseq,contmasc);
   getch();
-----------------------------------------------------------------------------*/
   switch(I(*mascteste))
    {
     char *aux;
     case I('h'):if (posinicio == -1)
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

     case I('m'):if (posinicio == -1)
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

     case I('s'):if (posinicio == -1)
                  posinicio = contmasc;
              if (posseg == -1)
                 {
                  flagseg <<= contseq;
                  possegbf = contseq;
                  ptrdest[contseq] = ptrbfteste;
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
    {
     VIDEO_mostra_mens_erro("Erro Posicao 1",TRUE);
     return(FALSE);
    }

 VIDEO_setatrib(campoedit->col,campoedit->col + strlen(ptrmasc) - 1,
                campoedit->lin,campoedit->lin,campoedit->cor);

 contmasc = 0;
 contseq = campoedit->col;
 tamcampo = campoedit->tamanho;
/*-----------------------------------------------------------------------------
 VD_gtxy(1,1);
 printf("[%4d]=[%4d + %4d] [%2d]",contseq + posmasc[contmasc],contseq,posmasc[contmasc],contmasc);

 for (ret = 0;ret < 3;ret++)
     {
      VD_gtxy(1,3+ret);
      printf("Pos [%5u]",posmasc[ret]);
     }
-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------
   VD_gtxy(1,2);
   printf("[%4d]=[%4d + %4d] [%2d]",contseq + posmasc[contmasc],contseq,posmasc[contmasc],contmasc);
-----------------------------------------------------------------------------*/

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

   switch(I(ret))
    {
     case I(VD_MTTECLA(VD_NULO,ESQUERDA)):if (posmasc[contmasc] == posinicio)
                                          {
                                           if (flags)
                                               VIDEO_setmem(ptrbuffer,tamcampo,' ');
                                           return(ret);
                                          }
                                       --contmasc;
                                       break;

     case I(VD_MTTECLA(10,ENTERSCAN)    ):if (flags&(1<<contmasc))
                                            continue;

     case I(VD_MTTECLA(VD_NULO,DIREITA) ):if (posmasc[contmasc] == posfim)
                                          {
                                           if (flags)
                                               VIDEO_setmem(ptrbuffer,tamcampo,' ');
                                           return(ret);
                                          }
                                       ++contmasc;
                                       break;
     case  0:VIDEO_mostra_mens_erro("Erro Posicao 2",TRUE);

     default:if (flags)
                 VIDEO_setmem(ptrbuffer,tamcampo,' ');
             return(ret);
    }
   }while(TRUE);
}

