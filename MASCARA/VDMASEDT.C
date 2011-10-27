#include<INCVIDEO.H>
int VIDEO_EDITA_mascara_campo(param)
VIDEO_EDITA_CAMPO *param;
{
 BYTE       ascii, scan;
 int        col  , colf,
            sai  , saida,
            posbuffer,
            posmasc  , fim;
 BOOLEAN    ins;
 char       *bflocal,
            *buffer_tmp,
            aux;

 if (!param->mascara || !strlen(param->mascara))
    return(FALSE);

 if ((colf = (param->col + strlen(param->mascara))) > VIDEO_maxcol)
     return (FALSE);

 if (VIDEO_ALLOC_MEM(bflocal,param->tamanho+1) == VIDEO_NULO)
     return(FALSE);

 if (VIDEO_ALLOC_MEM(buffer_tmp,param->tamanho+1) == VIDEO_NULO)
    {
     VIDEO_FREE_ALLOC_MEM(bflocal);
     return(FALSE);
    }

 *(bflocal) = *(bflocal+1) = fim = posbuffer = posmasc = ins =  0;

 VIDEO_tcursor(6,7);

 --colf;

 if (param->autos&VIDEO_EDITA_AUTOBLANK)
     VIDEO_CLEAR_PIC(col,col+strlen(param->mascara) - 1,
		     param->lin,param->lin,param->cor);

 if (param->autos&VIDEO_EDITA_AUTOIMP)
    {
     VIDEO_movbloco(bflocal,param->buffer,param->tamanho+1);
     fim = strlen(bflocal);
     *(bflocal + fim) = '\0';
     if (!VIDEO_display_mascara(param->col,param->lin,bflocal,
         param->mascara,param->cor,TRUE))
        {
         VIDEO_FREE_ALLOC_MEM(bflocal);
         return(FALSE);
        }
    }

 VIDEO_EDITA_mascara_posiciona(param->mascara,bflocal,param->col,
                               &col,posbuffer);
 posmasc = col - param->col;
 sai = TRUE;
 do
   {
    *(bflocal + fim) = '\0';
 
    (*param->pegacaracter)(col,param->lin,&ascii,&scan);

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
                       bflocal,&fim,posbuffer,param->col,param->lin,param->cor);
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
                                        param->col,&col,param->lin,param->cor);
					break;

      case CTRL_BAKSPACE:*bflocal = posbuffer = posmasc = fim = 0;
                         VIDEO_display_mascara(param->col,param->lin,
                                   bflocal,param->mascara,param->cor,TRUE);
					break;
      case ENTER :  scan = ENTERSCAN;
                    sai = FALSE;
                    break;

      case TAB   : if (param->autos&VIDEO_EDITA_AUTOSKIP)
                       if (VIDEO_testa_tabskip(ascii,scan,param->tabskip))
                        sai = FALSE;
                   break;

      default : if ((posbuffer == param->tamanho) ||
                    ((fim == param->tamanho) && ins))
                   {
                    if (param->autos&VIDEO_EDITA_AUTOSKIP)
                       {
                        ascii = ENTER;
                        scan  = ENTERSCAN;
                        sai   = FALSE;
                       }
                    break;
                   }
                strcpy(buffer_tmp,bflocal);
                if (VIDEO_MASCARA_testa_caracter_na_mascara(ascii,
                    *(param->mascara+posmasc),&aux,VIDEO_NILL(int)))
                   {
                    if (ins)
                        VIDEO_copbloco(buffer_tmp+posbuffer+1,
                        buffer_tmp+posbuffer,strlen(buffer_tmp+posbuffer)+1);
                    *(buffer_tmp+posbuffer) = ascii;
                    if (ins)
                       VIDEO_display_mascara(param->col,param->lin,buffer_tmp,
                       param->mascara,param->cor,TRUE);
                     else
                      VIDEO_plotcarac(col,param->lin,ascii,param->cor);
                    if (ins || (posbuffer == fim))
                        ++fim;
                    ++posbuffer;
                    VIDEO_EDITA_mascara_posiciona(param->mascara,buffer_tmp,
                                              param->col,&col,posbuffer);
                    posmasc = col - param->col;
                    strcpy(bflocal,buffer_tmp);
                    if ((fim == param->tamanho)          &&
                        (param->autos&VIDEO_EDITA_AUTOSKIP))
                       {
                        ascii = ENTER;
                        scan  = ENTERSCAN;
                        sai   = FALSE;
                       }
                   }
     }
  }while(sai);

 VIDEO_movbloco(param->buffer,bflocal,param->tamanho);
 VIDEO_FREE_ALLOC_MEM(bflocal);
 VIDEO_FREE_ALLOC_MEM(buffer_tmp);
 VIDEO_tcursor(6,7);
 return(VIDEO_MTTECLA(ascii,scan));
}

