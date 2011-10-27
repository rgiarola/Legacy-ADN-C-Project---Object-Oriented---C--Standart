#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_ultimo_registro(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA *pesquisa;
 INT2                     ret;

 pesquisa = *telapesq;

 pesquisa->flagplanilha |= VIDEO_PESQUISA_DISPCAMPOS|
                           VIDEO_PESQUISA_DISPCURSOR;

 if ((ret = CTREE_find(pesquisa->indice,pesquisa->segchave,
                       FIND_ULTIMO,CT_LE_EXTRA_REPASSA)) != FALSE)
    {
     char buffer[200];
     int  arquivo;

     arquivo = CTREE_keyfil(pesquisa->indice);
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    VIDEO_PESQ_mens_accept_arqvazio,
                    (VIDEO_bufparamarq->bufdodas+arquivo)->reduzido,
                    ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,
                            ret != 101 && ret != 100         ?
                            VIDEO_ERRO_arq_planilha_vazio_ult:
                            TRUE                             );
    }

 return(TRUE);
}

