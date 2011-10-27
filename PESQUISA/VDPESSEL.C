#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_seleciona_registro(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA *pesquisa;
 IDE_ARQUIVOS            *workifil;
 INT2                     arquivo,ret,tmpfil;
 char                    *buffer;

 pesquisa = *telapesq;


 if (~(VIDEO_PESQUISA_INICIALIZA&pesquisa->flagplanilha))
     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_ATIVADA;

 VIDEO_PESQUISA_termina(telapesq,param);

 arquivo = CTREE_keyfil(pesquisa->indice);

 ATIVA_BUF_DADOS;
 buffer = CTREE_filbuf(arquivo);

 if ((ret = DATABASE_ReReadRecord(CTREE_tmpfil(arquivo),buffer)) != FALSE)
    {
     char buf[100];
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    VIDEO_PESQ_mens_rereadrecord,
                    (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(pesquisa->indice))->reduzido,
                    ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_rereadrec_planilha);
    }
 
 if (pesquisa->flagplanilha&VIDEO_PESQUISA_POPWIN)
    VD_POPWIN();

 if (pesquisa->buffer_pesq)
    VIDEO_FREE_ALLOC_MEM(pesquisa->buffer_pesq);

 if (pesquisa->tela)
     VIDEO_CRG_libera_tela(pesquisa->tela);

 pesquisa->buffer_pesq = VD_NULO;

 return(FALSE);
}


