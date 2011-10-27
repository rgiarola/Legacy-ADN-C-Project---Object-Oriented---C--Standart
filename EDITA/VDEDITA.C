#include <INCVIDEO.H>

INT2 VIDEO_EDITA_campo(param,nucleo)
VIDEO_EDITA_CAMPO *param;
VIDEO_NUCLEO_SERV *nucleo;
{
 BYTE       ascii, scan;
 INT2        col = (param->col),
            sai = TRUE,
            saida, colf, pos, fim,
            colmouse,linmouse;
 BOOLEAN    ins,autoins,oldins;
 char       *bflocal,*buffer_tmp;
#ifdef VIDEO_UNIX
 INT2         old_flag_video;
#endif

#if defined(__VIDEO_DIM_TELA_CARGA_PARAMETROS)
 if (((colf = (param->col + param->tamanho)) -1) >
                          VIDEO_dim_tela_parametros->VIDEO_maxcol)
#else
 if (((colf = ((param->col) + (param->tamanho)))-1) > VD_maxcol)
#endif
     return (FALSE);

 if (VIDEO_ALLOC_MEM(bflocal,param->tamanho+1) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_EDITA_CAMPO);
     return(FALSE);
    }

 if (VIDEO_ALLOC_MEM(buffer_tmp,param->tamanho+1) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_2_EDITA_CAMPO);
     VIDEO_FREE_ALLOC_MEM(bflocal);
     return(FALSE);
    }

 *(bflocal) = *(bflocal+1) = fim = pos = ins =  autoins = 0;

 VD_tcursor(6,7);

 --colf;

 if (param->autos&VIDEO_EDITA_AUTOBLANK)
    if (param->mascara)
        VIDEO_CLEAR_PIC(col,col+strlen(param->mascara) - 1,
                         param->lin,param->lin,param->cor);
      else
        VIDEO_CLEAR_PIC(col,colf,param->lin,param->lin,param->cor);

 if (param->autos&VIDEO_EDITA_AUTOIMP)
    {
	 *(param->buffer+param->tamanho) = '\0';
     if (param->autos&VIDEO_EDITA_NAOMOSTRA)
         if (strlen(param->buffer))
            VIDEO_horizontal(param->col,param->col+strlen(param->buffer)-1,param->lin,'*',param->cor);
          else
            VIDEO_horizontal(param->col,param->col+1,param->lin,' ',param->cor);
       else
         VD_tprt_l(param->col,param->lin,param->buffer,param->cor);
	 fim = strlen(param->buffer);
	 VIDEO_movbloco(bflocal,param->buffer,param->tamanho +1);
    }

#ifdef VIDEO_DOS
 VIDEO_MOUSE_getpos(&colmouse,&linmouse);
 VIDEO_MOUSE_setpos(colmouse,linmouse);
 if (VIDEO_MOUSE_ativo > 0)
     VIDEO_MOUSE_habcursor();
#endif

#ifdef VIDEO_UNIX
     old_flag_video = VIDEO_UNIX_flag_video;
     VIDEO_UNIX_flag_video |= VIDEO_UNIX_AUTO_REFRESH
     VIDEO_UNIX_refresh_tela();
#endif

 do
   {
    *(bflocal + fim) = '\0';

#ifdef VIDEO_DOS
    if (VIDEO_MOUSE_ativo)
        VIDEO_MOUSE_habcursor();
#endif

    (*param->pegacaracter)(col,param->lin,&ascii,&scan);

#ifdef VIDEO_DOS
    if (VIDEO_MOUSE_ativo)
        VIDEO_MOUSE_deshabcursor();
#endif

    switch (ascii)
     {
      BOOLEAN     edita;

      case 0    : switch(scan)
                   {
					case ESQUERDA : if (col == param->col)
                                       {
                                        if (param->autos&
                                                       VIDEO_EDITA_AUTOSKIP)
                                            if (VIDEO_testa_tabskip(ascii,
                                                      scan,param->tabskip))
                                               {
                                                sai = FALSE;
                                                break;
                                               }
                                       }
                                     else
                                       {
                                        --col;
                                        --pos;
                                       }
                                    break;

                    case DIREITA  : if ((pos == fim) || (col == colf))
                                       {
                                        if (param->autos&
                                                       VIDEO_EDITA_AUTOSKIP)
                                           if (VIDEO_testa_tabskip(ascii,
                                                     scan,param->tabskip))
                                              {
                                               sai = FALSE;
                                               break;
                                              }
                                       }
                                     else
                                       {
                                        ++col;
                                        ++pos;
                                       }
                                    break;

                    case DEL      : if (pos != fim)
                                       {
                                        strcpy(bflocal+pos,bflocal+pos+1);
										VD_tprt_l(param->col+fim-1,
                                                  param->lin,VIDEO_espaco_branco,
												  param->cor);
                                        if (param->autos&VIDEO_EDITA_NAOMOSTRA)
                                            if (strlen(param->buffer))
                                                VIDEO_horizontal(param->col,param->col+
                                                          +strlen(bflocal)-1,param->lin,'*',param->cor);
                                              else
                                                VIDEO_horizontal(param->col,param->col+1,
                                                      param->lin,' ',param->cor);
                                        else
                                          VD_tprt_l(col,param->lin,
												  bflocal+pos,param->cor);
                                        --fim;
                                       }

                                    break;

                    case INS      : if (ins)
                                       VD_tcursor(6,7);
                                      else
                                       VD_tcursor(0,7);
                                    ins = ~ins;
                                    break;

                    case HOME     : pos = 0;
									col = param->col;
                                    break;

                    case NULL     : break;

					case END	  : col = param->col + fim -
												(fim == param->tamanho);
									pos = fim - (fim == param->tamanho);
                                    break;

                    default       : if (param->autos&VIDEO_EDITA_AUTOSKIP)
                                        if (VIDEO_testa_tabskip(ascii,scan,
                                                            param->tabskip))
                                           sai = FALSE;

                   }
                  break;

      case BAKSPACE:if (pos)
					   {
						if (pos != fim)
							strcpy(bflocal+pos-1,bflocal+pos);
                        VD_tprt_l(param->col + --fim,param->lin,VIDEO_espaco_branco,
								  param->cor);
						*(bflocal + fim) = '\0';
						--col;
						--pos;
                        if (param->autos&VIDEO_EDITA_NAOMOSTRA)
                           if (strlen(bflocal))
                              VIDEO_horizontal(param->col,param->col+
                                          strlen(bflocal)-1,
                                          param->lin,'*',param->cor);
                           else
                              VIDEO_horizontal(param->col,param->col+1,
                                          param->lin,' ',param->cor);
                         else
                          VD_tprt_l(param->col,param->lin,bflocal,param->cor);
					   }
					break;

    case ENTER :  scan = ENTERSCAN;
                  sai = FALSE;
                  break;

    case ESCAPE:  scan = ESCAPESCAN;
                  sai = FALSE;
                  break;

    case VD_TAB   : if (param->autos&VIDEO_EDITA_AUTOSKIP)
                        if (VIDEO_testa_tabskip(ascii,scan,param->tabskip))
                            sai = FALSE;
                 break;

    default : if (VIDEO_MTTECLA(ascii,scan) == VIDEO_MTTECLA(CTRL_Y,SCAN_Y))
                 {
                  *(bflocal) = *(bflocal+1) = fim = pos = ins =  0;
                  VD_tcursor(6,7);
                  col = param->col;
/*
                  if (param->mascara)
                      VIDEO_CLEAR_PIC(col,col+strlen(param->mascara) - 1,
                                       param->lin,param->lin,param->cor);
                    else
*/
                      VIDEO_CLEAR_PIC(col,colf,param->lin,param->lin,param->cor);
                  break;
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

                            strcpy(buffer_tmp,bflocal);
              if ((pos == param->tamanho) || ((fim == param->tamanho) && ins))
                 {
                  if (param->autos&VIDEO_EDITA_AUTOSKIP)
					 {
					  ascii = ENTER;
					  scan = ENTERSCAN;
                      sai = FALSE;
					 }
				  break;
                 }

              if (VIDEO_testa_tabskip(ascii,scan,param->tabskip) &&
                 (param->autos&VIDEO_EDITA_AUTOSKIP))
                 {
                  sai = FALSE;
                  break;
                 }

              strcpy(buffer_tmp,bflocal);
              if ((pos == param->tamanho) || ((fim == param->tamanho) && ins))
                 {
                  if ((param->autos&VIDEO_EDITA_AUTOSKIP) &&
                      !(param->autos&VIDEO_EDITA_PRENCH))
					 {
                      ascii = 10;
					  scan = ENTERSCAN;
                      sai = FALSE;
					 }
				  break;
                 }


              edita = TRUE;
              autoins = FALSE;
			  if (param->tipo)
                 {
                  if ((ascii >= '0' && ascii <= '9') || ascii == '.' ||
                       ascii == '+' || ascii == '-')
                     if (*(bflocal + pos) == '.' && ascii != '.' && !ins)
                        {
                         oldins = ins;
                         ins = ~ins;
                         autoins = TRUE;
                        }

                  if (!VIDEO_EDITA_campo_testanum(bflocal,ascii,pos,ins,
                                  param->autos,fim))
                  edita = FALSE;
                 }

              if (edita)
                 {
/*
                  VD_gtxy(1,1);
                  printf("INS %04X POS %6u FIM %6u",ins,pos,fim);
*/
                  if (ins && (pos < fim))
                     {
                      char  *buf2;
					  if (VIDEO_ALLOC_MEM(buf2,fim+1) == VD_NULO)
						 {
						  ascii = scan = VD_NULO;
						  sai = FALSE;
                          break;
						 }
                      strcpy(buf2,bflocal+pos);
                      strcpy(bflocal+pos+1,buf2);
					  VIDEO_FREE_ALLOC_MEM(buf2);
                     }
                  *(bflocal + fim + 1) = '\0';
                  *(bflocal + pos) = ascii;

                  edita = TRUE;

/*                  if (param->tipo && (param->autos&VIDEO_EDITA_EDPONTO))*/
/*                      edita = VIDEO_EDITA_campo_testaponto(bflocal,*/
/*                                                 param->decimais);*/
                  if (edita && param->tipo)
                      edita = VIDEO_EDITA_testa_sinalponto(bflocal,param->autos,
                                          param->tamanho,param->decimais);
                  if (edita)
                      if (param->autos&VIDEO_EDITA_NAOMOSTRA)
                         if (strlen(bflocal))
                            VIDEO_horizontal(param->col,param->col+strlen(bflocal)-1,
                                         param->lin,'*',param->cor);
                         else
                            VIDEO_horizontal(param->col,param->col+1,
                                         param->lin,' ',param->cor);
                      else
                        VD_tprt_l(param->col,param->lin,bflocal,param->cor);
                     else
                      {
                       strcpy(bflocal,buffer_tmp);
                       break;
                      }

                  if ((col == colf) && (param->autos&VIDEO_EDITA_AUTOSKIP) &&
                      !(param->autos&VIDEO_EDITA_PRENCH))
                     {
                      ascii = 10;
					  scan = ENTERSCAN;
                      sai = FALSE;
                      break;
                     }
                  fim = ins ? ++fim : ((pos == fim) ? ++fim : fim);
                  ++col;
                  ++pos;
                 }
     }

   if (autoins)
       ins = oldins;

   autoins = FALSE;
  }while(sai);

 VIDEO_movbloco(param->buffer,bflocal,param->tamanho+1);
 VIDEO_FREE_ALLOC_MEM(bflocal);
 VIDEO_FREE_ALLOC_MEM(buffer_tmp);

#ifdef VIDEO_UNIX
 VIDEO_UNIX_flag_video = old_flag_video;
#endif

 VD_tcursor(6,7);
 return(VIDEO_MTTECLA(ascii,scan));
}


