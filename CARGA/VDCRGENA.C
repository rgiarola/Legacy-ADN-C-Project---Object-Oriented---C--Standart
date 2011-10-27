#include <INCVIDEO.H>

INT2 VIDEO_endnomearquivo(telas,num)
VIDEO_TELA_ENTRADA_DADOS *telas;
INT2                      num;
{
 INT2 cont,contimg,
     indice;

 while(num)
  {
   contimg = 0;
   do
    {
     if ((telas->imagens+contimg)->nmindarq)
        {
         if ((indice = CTREE_keynm((telas->imagens+contimg)->nmindarq))
              <= VD_NULO)
            {
             char buflocal[100];
             sprintf(buflocal,VIDEO_CARGA_mens_indice,
                               (telas->imagens+contimg)->nmindarq);
             VIDEO_mostra_mens_erro(buflocal,
                                    VIDEO_ERRO_nome_ind_arq_nao_encontrado);
             return(FALSE);
            }
         (telas->imagens+contimg)->indarq  = indice;
         (telas->imagens+contimg)->arquivo = CTREE_keyfil(indice);
        }
     if ((telas->imagens+contimg)->nmindsub)
        {
         if ((indice = CTREE_keynm((telas->imagens+contimg)->nmindsub))
              <= VD_NULO)
            {
             char buflocal[100];
             sprintf(buflocal,VIDEO_CARGA_mens_indice,
                               (telas->imagens+contimg)->nmindsub);
             VIDEO_mostra_mens_erro(buflocal,
                                    VIDEO_ERRO_nome_ind_sub_nao_encontrado);
             return(FALSE);
            }

         (telas->imagens+contimg)->indsub  = indice;
         (telas->imagens+contimg)->subfile = CTREE_keyfil(indice);
        }
     ++contimg;
    }while(contimg < telas->num_imagens);
   --num;
   ++telas;
  }
 return(TRUE);
}


