#include <INCVIDEO.H>
 
INT2     VIDEO_testa_nome_funcao();

VD_VOID VIDEO_scheduler_funcao();

INT2 VIDEO_organiza_tabela_de_funcoes()
{
 VIDEO_TABFUNCAO *tabfuncuser;
 INT2             cont,contfunc;

 if (!VIDEO_tabfuncuser[1].nomefunc)
     return(TRUE);

 tabfuncuser = VIDEO_tabfuncuser;
 VIDEO_numtabfuncuser = 0;

 do
  {
   ++VIDEO_numtabfuncuser;
  }while((++tabfuncuser)->nomefunc);

 if (VIDEO_numtabfuncuser < 3)
	return(TRUE);

 --VIDEO_numtabfuncuser;

 for (cont = 0;cont < 10;cont++)
     {
      VIDEO_quick_sort(0,VIDEO_numtabfuncuser-1,sizeof(VIDEO_TABFUNCAO),
                   sizeof(VIDEO_TABFUNCAO),0,
				   VIDEO_testa_nome_funcao,VIDEO_scheduler_funcao,
                   (BYTE *) &VIDEO_tabfuncuser[1]);

      tabfuncuser = &VIDEO_tabfuncuser[1];

      for (contfunc = 0;contfunc < VIDEO_numtabfuncuser;contfunc++,tabfuncuser++)
		   if ((contfunc + 1) < VIDEO_numtabfuncuser)
               if (strcmp(tabfuncuser->nomefunc,
						 (tabfuncuser+1)->nomefunc) > 0)
				  if (cont == 9)
					  return(FALSE);
					else
					  break;

	  if (cont == VIDEO_numtabfuncuser)
		 break;
	 }

 return(TRUE);
}

INT2 VIDEO_testa_nome_funcao(destino,origem,tamanho)
VIDEO_TABFUNCAO *destino,
				*origem;
INT2             tamanho;
{
 return(strcmp(destino->nomefunc,origem->nomefunc));
}

VD_VOID VIDEO_scheduler_funcao(destino,origem)
VIDEO_TABFUNCAO *destino,
				*origem;
{
 VIDEO_TABFUNCAO funcao;
 funcao = *origem;
 *origem = *destino;
 *destino = funcao;
}
