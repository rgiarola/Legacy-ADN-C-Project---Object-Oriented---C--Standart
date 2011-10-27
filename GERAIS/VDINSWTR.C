#include <INCVIDEO.H>

VD_VOID VIDEO_inic_tab_swap_tratadores(tratadores,tabserv)
VIDEO_SWAP_TRATADOR_SERVICO *tratadores;
VIDEO_TABSERV				*tabserv;
{
 INT2 *servnucleo,servtrat;

 while(tratadores->servico)
  {
   servnucleo = (INT2 *) TRUE;
   while(servnucleo && tabserv->VIDEO_servico)
	{
     servnucleo = tabserv->VIDEO_servico;
     servtrat = tratadores->servico;
     while(servnucleo && *servnucleo)
	  {
       if (servtrat == *servnucleo)
          {
           tratadores->VIDEO_tratador_nucleo = tabserv->VIDEO_funcao;
           servnucleo = VD_NULO;
           break;
          }
       ++servnucleo;
	  }
	 ++tabserv;
	}
   ++tratadores;
  }
}

