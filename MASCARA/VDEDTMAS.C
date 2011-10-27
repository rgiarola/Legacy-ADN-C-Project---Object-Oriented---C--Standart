#include<INCVIDEO.H>

int VIDEO_EDITA_mascara_campo(param)
VIDEO_EDITA_CAMPO *param;
{
 BYTE       ascii, scan;
 int        col  , colf,
            sai  , saida,
            posbuffer, colmouse,linmouse,
            posmasc  , fim;
 BOOLEAN    ins;
 char       *bflocal,
            *buffer_tmp,
            aux;

 if (!param->mascara || !strlen(param->mascara))
    {
//     VIDEO_mostra_mens_erro("Display Erro 1",TRUE);
     return(FALSE);
    }

 if ((colf = (param->col + strlen(param->mascara))) > VIDEO_maxcol)
    {
/*
     char buf[100];
     sprintf(buf,"Colf %d Col %d Tam %d Masc[%s]",
             colf,param->col,strlen(param->mascara),param->mascara);
     VIDEO_mostra_mens_erro(buf,TRUE);
*/
     return(FALSE);
    }

 if (VIDEO_ALLOC_MEM(bflocal,param->tamanho+2) == VIDEO_NULO)
	{
	 VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_EDITA_MASCARA);
     return(FALSE);
	}

 if (VIDEO_ALLOC_MEM(buffer_tmp,param->tamanho+2) == VIDEO_NULO)
    {
	 VIDEO_mostra_mens_erro_alloc(ALOCACAO_2_EDITA_MASCARA);
     VIDEO_FREE_ALLOC_MEM(bflocal);
     return(FALSE);
    }

 *(bflocal) = *(bflocal+1) = fim = posbuffer = posmasc = ins =  0;
 VIDEO_EDITA_mascara_posiciona(param->mascara,bflocal,param->col,
                               &col,posbuffer);

 VIDEO_tcursor(6,7);

 --colf;

 if (param->autos&VIDEO_EDITA_AUTOBLANK)
     VIDEO_CLEAR_PIC(param->col,param->col+strlen(param->mascara) - 1,
		     param->lin,param->lin,param->cor);

 if (param->autos&VIDEO_EDITA_AUTOIMP)
    {
     VIDEO_movbloco(bflocal,param->buffer,param->tamanho+1);
     fim = strlen(bflocal);
     *(bflocal + fim) = '\0';
     if (!VIDEO_display_mascara(param->col,param->lin,bflocal,
         param->mascara,param->cor,FALSE,(param->autos&VIDEO_EDITA_NAOMOSTRA)))
        {
         VIDEO_FREE_ALLOC_MEM(bflocal);
		 VIDEO_FREE_ALLOC_MEM(buffer_tmp);
         return(FALSE);
        }
    }

 posmasc = col - param->col;
 sai = TRUE;

 do
   {
    *(bflocal + fim) = '\0';

#ifdef VIDEO_DOS
    if (VIDEO_MOUSE_ativo > 0)
        VIDEO_MOUSE_habcursor();
#endif

#ifdef VIDEO_UNIX
    VIDEO_UNIX_rfresh_tela();
#endif

    (*param->pegacaracter)(col,param->lin,&ascii,&scan);

#ifdef VIDEO_DOS
    if (VIDEO_MOUSE_ativo > 0)
        VIDEO_MOUSE_deshabcursor();
#endif

    switch (ascii)
     {
      case VIDEO_NULO :
	   switch(scan)
	    {
         case ESQUERDA:if (!VIDEO_EDITA_mascara_colesq(param->mascara,
                           &posmasc,&col,&posbuffer) &&
                           (param->autos&VIDEO_EDITA_AUTOSKIP) &&
                           (VIDEO_testa_tabskip(ascii,scan,
                           param->tabskip)))
                          sai = FALSE;
                       break;

         case DIREITA :if (!VIDEO_EDITA_mascara_coldir(param->mascara,
                           &posmasc,&col,&posbuffer,fim)  &&
                           (param->autos&VIDEO_EDITA_AUTOSKIP) &&
                           (VIDEO_testa_tabskip(ascii,scan,
                           param->tabskip)))
                          sai = FALSE;
                       break;

         case DEL     :VIDEO_EDITA_mascara_delcar(param->mascara,
                       bflocal,&fim,posbuffer,param->col,param->lin,param->cor,
                       (param->autos&VIDEO_EDITA_NAOMOSTRA));
                       break;

	     case INS     :VIDEO_tcursor(((ins) ? 6 : 0),7);
                       ins = ~ins;
                       break;

         case HOME    :posbuffer = 0;
                       VIDEO_EDITA_mascara_posiciona(param->mascara,bflocal,
                                                 param->col,&col,posbuffer);
                       posmasc = col - param->col;
                       break;

         case END     :posbuffer = strlen(bflocal),
                       posbuffer = posbuffer - (posbuffer == param->tamanho);
                       VIDEO_EDITA_mascara_posiciona(param->mascara,bflocal,
                                                 param->col,&col,posbuffer);
                       posmasc = col - param->col;
                       break;

         default      :if ((param->autos&VIDEO_EDITA_AUTOSKIP) &&
                           (VIDEO_testa_tabskip(ascii,scan,
                                                param->tabskip)))
                          sai = FALSE;
	    }
		       break;
      case ESCAPE:sai = FALSE;
                  break;

      case BAKSPACE:VIDEO_EDITA_mascara_bakcar(param->mascara,bflocal,
                                        &posbuffer,&posmasc,&fim,
                                        param->col,&col,param->lin,param->cor,
                                        (param->autos&VIDEO_EDITA_NAOMOSTRA));
					break;

      case ENTER :  scan = ENTERSCAN;
                    sai = FALSE;
                    break;

      case VD_TAB   : if (param->autos&VIDEO_EDITA_AUTOSKIP)
                       if (VIDEO_testa_tabskip(ascii,scan,param->tabskip))
                        sai = FALSE;
                   break;

      default : if (VIDEO_MTTECLA(ascii,scan) == VIDEO_MTTECLA(CTRL_Y,SCAN_Y))
                   {
                    *(bflocal) = *(bflocal+1) = fim = posbuffer = posmasc = 0;
                    VIDEO_EDITA_mascara_posiciona(param->mascara,bflocal,param->col,
                                                  &col,posbuffer);
                    VIDEO_setmem(bflocal,param->tamanho,' ');
                    *(bflocal+param->tamanho) = '\0';
                    fim = strlen(bflocal);
                    *(bflocal + fim) = '\0';
                    VIDEO_display_mascara(param->col,param->lin,bflocal,
                        param->mascara,param->cor,FALSE,(param->autos&VIDEO_EDITA_NAOMOSTRA));
                    posmasc = col - param->col;
                    continue;
                   }

                switch(VIDEO_MTTECLA(ascii,scan))
                 {
                  case VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK):
                  case VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK):
                  case VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV):
                  case VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTTRV):
                       sai = FALSE;
                       continue;
                 }

                if ((param->autos&VIDEO_EDITA_AUTOSKIP) &&
                    VIDEO_testa_tabskip(ascii,scan,param->tabskip))
                   {
                    sai = FALSE;
                    break;
                   }

                if ((posbuffer == param->tamanho) ||
                    ((fim == param->tamanho) && ins))
                   {
                    if (param->autos&VIDEO_EDITA_AUTOSKIP &&
                        !(param->autos&VIDEO_EDITA_PRENCH))
                       {
                        ascii = 10;
                        scan  = ENTERSCAN;
                        sai   = FALSE;
                       }
                    break;
                   }
                strcpy(buffer_tmp,bflocal);
                if (VIDEO_EDITA_testa_caracter_na_mascara(&ascii,
                    *(param->mascara+posmasc),&aux,VIDEO_NILL(int)))
                   {
                    BOOLEAN flagedita;

                    if ((ins || (posbuffer == fim)) && (fim != param->tamanho))
                        ++fim;

                    if (ins)
                        VIDEO_copbloco(buffer_tmp+posbuffer+1,
                        buffer_tmp+posbuffer,strlen(buffer_tmp+posbuffer)+1);
                    *(buffer_tmp+posbuffer) = ascii;
                    *(buffer_tmp+fim) = '\0';
                    if (ins)
                       VIDEO_display_mascara(param->col,param->lin,buffer_tmp,
                       param->mascara,param->cor,FALSE,
                                      (param->autos&VIDEO_EDITA_NAOMOSTRA));
                     else
                      VIDEO_plotcarac(col,param->lin,(param->autos&VIDEO_EDITA_NAOMOSTRA) ?
                                                     '*' : ascii ,param->cor);

                    flagedita = FALSE;
                    if (posbuffer != (param->tamanho-1))
                       {
                        ++posbuffer;
                        VIDEO_EDITA_mascara_posiciona(param->mascara,buffer_tmp,
                                              param->col,&col,posbuffer);
                        posmasc = col - param->col;
                        flagedita = TRUE;
                       }
                    strcpy(bflocal,buffer_tmp);
                    if ( (((fim == param->tamanho) && ins) || ((fim == param->tamanho) && !flagedita)) &&
                        (param->autos&VIDEO_EDITA_AUTOSKIP) && !(param->autos&VIDEO_EDITA_PRENCH))
                       {
                        ascii = 10;
                        scan  = ENTERSCAN;
                        sai   = FALSE;
                       }
                   }
     }
  }while(sai);
 VIDEO_movbloco(param->buffer,bflocal,param->tamanho+1);
 VIDEO_FREE_ALLOC_MEM(bflocal);
 VIDEO_FREE_ALLOC_MEM(buffer_tmp);
 VIDEO_tcursor(6,7);
 return(VIDEO_MTTECLA(ascii,scan));
}

