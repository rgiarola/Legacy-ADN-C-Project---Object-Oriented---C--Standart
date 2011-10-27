#include <INCVIDEO.H>

VD_VOID VIDEO_TELA_libera_subfile(tela,flagtela)
VIDEO_TELA_ENTRADA_DADOS *tela;
INT2                      flagtela;
{
 INT2              cont,
                  flagsub;
 VIDEO_SEG_CHAVE  *segaux;
 VIDEO_IMAGEMTELA *imagem;


 for (cont = 0;cont < tela->num_imagens;cont++)
	 {
      flagsub = FALSE;

      if (flagtela)
         imagem = tela->imagem_ativa;
       else
         imagem = tela->imagens+cont;

      imagem->flagimagem &= ~VIDEO_TELA_STATSUBFILE;

      if (imagem->segsub)
         {
          segaux = imagem->segsub;
          while(segaux->pointer)
           {
            if (segaux->tipo == CT_SEG_CONST)
                VIDEO_FREE_ALLOC_MEM(segaux->pointer);
            ++segaux;
           }
          VIDEO_FREE_ALLOC_MEM(imagem->segsub);
          imagem->segsub = VD_NULO;
          flagsub = TRUE;
         }


      if (flagsub && ((cont = CTREE_deltmp(imagem->arquivo)) != FALSE))
         {
          char buffer[100];
          sprintf(buffer,CTREE_MENS_mens_padrao_err,
						 VIDEO_TELA_mens_deltmp,
						 (VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
						 cont,isam_err);
		  VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_del_arq_tmp);
		 }

      imagem->flagimagem &= ~VIDEO_TELA_FLAGREGALT;
      if (flagtela)
         return;
     }
}

