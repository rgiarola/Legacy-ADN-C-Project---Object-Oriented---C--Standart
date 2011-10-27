#include <INCVIDEO.H>

INT2 VIDEO_endnomeindice(campos,num)
VIDEO_CAMPO_TELA *campos;
INT2              num;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_PESQUISA_PLANILHA  *planilha;
 VIDEO_CONSDB             *consdb;

 while(num)
  {
   if ((consiste = campos->consiste) !=
             VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
       while(consiste->tipocons)
        {
         switch(consiste->tipocons)
          {
           case VIDEO_TELA_CONS_POSICIONA_DB:
           case VIDEO_TELA_VALKEY:
           case VIDEO_TELA_DUPKEY:consdb = consiste->objetocons.consdb;
                if (consdb->nomeindice)
                   {
                    if ((consdb->indice = CTREE_keynm(consdb->nomeindice)) < 0)
                       {
                        char buflocal[100];
                        sprintf(buflocal,VIDEO_CARGA_mens_indice,
                                         consdb->nomeindice);
                        VIDEO_mostra_mens_erro(buflocal,
                                               VIDEO_ERRO_nome_ind_cons_nao_encontrado);
                        return(FALSE);
                       }
                   }
                break;

           case VIDEO_TELA_CONS_BUSCA_DB:
                planilha = consiste->objetocons.planilha;
                if (planilha->nomeindice)
                   {
                    if ((planilha->indice = CTREE_keynm(planilha->nomeindice)) < 0)
                       {
                        char buflocal[100];
                        sprintf(buflocal,VIDEO_CARGA_mens_indice,
                                         planilha->nomeindice);
                        VIDEO_mostra_mens_erro(buflocal,
                                               VIDEO_ERRO_nome_ind_plan_nao_encontrado);
                        return(FALSE);
                       }
                   }
                break;
          }
         ++consiste;
        }
   --num;
   ++campos;
  }
 return(TRUE);
}


