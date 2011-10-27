
VIDEO_FUNCAO VIDEO_DISPLAY_tabfunc[] = {
               VIDEO_DISPLAY_cons_obrigatorio,VIDEO_DISPLAY_cons_menu,
               VIDEO_DISPLAY_cons_faixa,      VIDEO_DISPLAY_cons_valkey,
               VIDEO_DISPLAY_cons_dupkey,     VIDEO_DISPLAY_cons_posiciona,
               VIDEO_DISPLAY_cons_busca,      VIDEO_DISPLAY_cons_user_func,
               VIDEO_DISPLAY_cons_manutencao};

int VIDEO_DISPLAY_endereca_campos(campo,numcampos,strtelacrg)
VIDEO_CAMPO_TELA *campo;
int              numcampos;
VIDEO_TABCRGTELA *strtelacrg;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 int                      cont,
                          ret;

 cont = 0;
 do
  {
   printf("CAMPO %2d TAMDODA %2d DODA %s \n",cont,
           strlen(campo->dodacampo),campo->dodacampo);

   if (campo->mascara)
	  {
       printf("CAMPO %2d TAMMASC %2d MASC %s \n",cont,
               strlen(campo->mascara),campo->mascara);

	  }
	else
	  {
       printf("CAMPO %2d SEM MASCARA \n",cont);

	  }

   if (campo->user_func)
	  {
       printf("CAMPO %2d TAMMASC %2d MASC %s \n",cont,
               strlen(campo->user_func),campo->user_func);

	  }
	else
	  {
       printf("CAMPO %2d SEM USERFUNC \n",cont);

	  }

   if (campo->consiste)
      {
       consiste = campo->consiste;
       while(consiste->tipocons)
        {
         if (consiste->tipocons < 10 || consiste->tipocons > 0)
            {
             if (!VIDEO_DISPLAY_tabfunc[consiste->tipocons-1].funcao(consiste,strtelacrg))
                 return(FALSE);
            }
          else
            {
             printf("ERRO FUNCCONS %d",consiste->tipocons);
             return(FALSE);
            }
         ++consiste;
        }
      }
    else
      campo->consiste = VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA);

   ++campo;
  }while(++cont < numcampos);

 return(TRUE);
}
