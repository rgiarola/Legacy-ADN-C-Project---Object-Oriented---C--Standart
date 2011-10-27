#include <INCVIDEO.H>

char *VIDEO_VISAO_indexa_texto(visual)
VIDEO_VISUAL_CONTROLE *visual;
{
 int     cont,ret,tamlin;
 char    *buffer ,*linha,
         *arquivo,*testa,*lini;
 DWORD   numlin = 0,lido = 0,posicao= 0;
 BOOLEAN flag,flagdsp,arqtmp,flagfim;

 flagfim = FALSE;

 if (!visual->arqtmp)
    {
     if (VIDEO_ALLOC_MEM(arquivo,VD_MAX_TMP_NOME+2) == VD_NULO)
        return(VIDEO_NILL(char));
    }
  else
    {
	 VIDEO_VISUAL_flag_erro = FALSE;
     VIDEO_VISUAL_flag_int  = FALSE;
     if (visual->descindex > -1)
        {
         VIDEO_close(visual->descindex);
         VIDEO_unlink(visual->arqtmp);
        }
     visual->descindex = -1;
     arquivo = visual->arqtmp;
    }

 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_VISUAL_flag_int  = FALSE;

 cont = 0;
 do
  {
   DATABASE_GetTempFileName(arquivo,VD_MAX_TMP_NOME);
   if ((visual->descindex = VIDEO_cria(arquivo)) < 0 ||
       VIDEO_VISUAL_flag_erro)
      if (++cont < 10)
         continue;
   break;
  }while(TRUE);
 
 if (cont == 10)
    {
     if (!visual->arqtmp)
         VIDEO_FREE_ALLOC_MEM(arquivo);

     VIDEO_VISUAL_flag_int  = TRUE;
	 VIDEO_VISUAL_flag_erro = FALSE;
     visual->descindex = -1;
     return(VIDEO_NILL(char));
    }

 flag = flagdsp = FALSE;
 do
  {
   if (flag && flag != 1)
      {
       VIDEO_close(visual->descindex);
       VIDEO_unlink(arquivo);
       if (!visual->arqtmp)
           VIDEO_FREE_ALLOC_MEM(arquivo);
       VIDEO_VISUAL_flag_int  = TRUE;
       VIDEO_VISUAL_flag_erro = FALSE;
       visual->descindex = -1;
       if (flag == 2)
		   VIDEO_mostra_mens_erro(VIDEO_VISUAL_erro_linha,TRUE);
	   return(VIDEO_NILL(char));
      }

   linha = visual->linhaaux;
   VIDEO_setmem(linha,4096,0);

   VIDEO_lseek(visual->desc,posicao,VIDEO_INI_ARQ);
   if (VIDEO_VISUAL_flag_erro)
      {
       flag = 3;
       continue;
      }

   if ((lido = VIDEO_read(visual->desc,linha,4095)) <= VD_NULO || flagfim)
      {
       if (!numlin || VIDEO_VISUAL_flag_erro)
          {
           VIDEO_close(visual->descindex);
           VIDEO_unlink(arquivo);
           visual->descindex = -1;
           if (!visual->arqtmp)
               VIDEO_FREE_ALLOC_MEM(arquivo);
           VIDEO_VISUAL_flag_int  = TRUE;
           VIDEO_VISUAL_flag_erro = FALSE;
           return(VIDEO_NILL(char));
		  }
       VIDEO_VISUAL_flag_int  = TRUE;
       VIDEO_VISUAL_flag_erro = FALSE;
       return(arquivo);
	  }

   flagfim = (lido < 4095);
   do
	{
     for (cont = 0;cont <= visual->numlin;cont++,numlin++)
         {
          lini = linha;
          do
		   {
            flag = FALSE;
            if (*linha == C(10))
			   {
                if (++linha >= (visual->linhaaux+4094))
				   {
                    flag = 1;
					break;
				   }
				continue;
			   }

            if ((buffer = strchr(linha,C(13))) == VD_NULO)
			   {
                if ((lido - (VIDEO_FP_OFF(linha)-
                             VIDEO_FP_OFF(visual->linhaaux))) > VIDEO_VISUAL_MAX_COL)
                   flag = 2;
                 else
                   flag = 1;
				break;
			   }
/*
            if (buffer == linha)
			   {
                if (++linha >= (visual->linhaaux+4094))
				   {
                    flag = 1;
					break;
				   }
				continue;
			   }
*/
            if ((buffer+1) >= (visual->linhaaux+4094))
               {
                flag = 1;
                break;
               }

            if (flagdsp)
               {
                flagdsp = FALSE;
                linha = buffer+1;
                if (linha >= (visual->linhaaux+4094))
				   {
                    flag = 1;
					break;
				   }
				continue;
			   }

            if (*(buffer+1) != C(10) && (cont || visual->lido))
                flagdsp = TRUE;

             break;
		   }while(TRUE);

          if (!flag)
			 {
              *buffer = 0;
              visual->linha[cont] = CAST_CHAR(visual->pos_ini +
                                    (VIDEO_FP_OFF(linha)-
                                     VIDEO_FP_OFF(visual->linhaaux)));

              if ((VIDEO_FP_OFF(buffer)-VIDEO_FP_OFF(linha)) > VIDEO_VISUAL_MAX_COL)
                 {
                  VIDEO_close(visual->descindex);
                  VIDEO_unlink(arquivo);
                  if (!visual->arqtmp)
                      VIDEO_FREE_ALLOC_MEM(arquivo);
                  VIDEO_VISUAL_flag_int  = TRUE;
                  VIDEO_VISUAL_flag_erro = FALSE;
                  visual->descindex = -1;
                  VIDEO_mostra_mens_erro(VIDEO_VISUAL_erro_linha,TRUE);
                  return(VIDEO_NILL(char));
                 }

              if (*(buffer+1) != C(10))
                  linha = buffer + 1;
                else
                  linha = buffer + 2;

              lini = linha;
			 }
		   else
			  break;
		 }

     VIDEO_write(visual->descindex,&visual->linha[0],sizeof(char *)* (cont));
     if (VIDEO_VISUAL_flag_erro)
        {
         flag = 2;
         continue;
        }

     visual->lido += cont;
    }while(!flag);

   posicao += (VIDEO_FP_OFF(lini) -
               VIDEO_FP_OFF(visual->linhaaux));

   visual->pos_ini = posicao;
  }while(TRUE);
}

