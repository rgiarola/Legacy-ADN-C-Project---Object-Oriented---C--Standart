#include <INCVIDEO.H>

VD_VOID VIDEO_swap_tratadores(tratadores,tabserv,modo,servico)
VIDEO_SWAP_TRATADOR_SERVICO *tratadores;
VIDEO_TABSERV				*tabserv;
INT2                         modo,
                            *servico;
{
 VIDEO_SWAP_TRATADOR_SERVICO *trat;
 VIDEO_TABSERV               *tabservicos;
 INT2                         *servnucleo,
                             servtrat;
 trat = tratadores;
 while(trat->servico)
  {
   if (servico)
      {
       if (!(*servico))
          return;

       trat = tratadores;
       while((trat->servico != *servico) && trat->servico)
           ++trat;

       ++servico;
       if (!trat->servico)
          {
           trat = tratadores;
           continue;
          }
      }

   servnucleo  = (INT2 *) TRUE;
   tabservicos = tabserv;

   while(servnucleo && tabservicos->VIDEO_servico)
	{
     servnucleo = tabservicos->VIDEO_servico;
     servtrat   = trat->servico;
     while(servnucleo && *servnucleo)
	  {
       if (servtrat == *servnucleo)
          {
           tabservicos->VIDEO_funcao =  modo ? trat->VIDEO_tratador_nucleo :
                                           trat->VIDEO_tratador_usuario;
           servnucleo = VD_NULO;
           break;
          }
       ++servnucleo;
	  }
     ++tabservicos;
	}
   ++trat;
  }
}


