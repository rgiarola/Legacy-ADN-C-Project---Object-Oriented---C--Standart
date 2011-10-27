#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_atributos(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *work;

 work = (*campos);

 VIDEO_alteracor_pict(work->coli,work->colf,work->lini,work->linf,
		      work->col,work->lin,3,work->numpag,
		      &work->cor_opcao  ,&work->cor_selecao,
		      &work->cor_moldura,&work->cor_sombra,
                      VD_getkbd);
 return(TRUE);
}

