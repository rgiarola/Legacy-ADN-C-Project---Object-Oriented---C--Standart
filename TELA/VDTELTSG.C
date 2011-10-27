#include <INCVIDEO.H>

INT2 VIDEO_TELA_compara_segconst(VIDEO_SEG_CHAVE *seg,
                                 VIDEO_SEG_CHAVE *segsub);

INT2 VIDEO_TELA_testa_segconst_sub(imagem)
VIDEO_IMAGEMTELA *imagem;
{
 VIDEO_SEG_CHAVE *seg,
                 *segsub;
 seg     = imagem->segchave;
 segsub  = imagem->segsub;
 return(VIDEO_TELA_compara_segconst(seg,segsub));
}


INT2 VIDEO_TELA_compara_segconst(seg,segsub)
VIDEO_SEG_CHAVE *seg,*segsub;
{
 IDE_DODA *doda;
 char     *pointer;

 if (!segsub)
     return(4);

 while(seg->pointer)
  {
   if (seg->tipo == CT_SEG_CAMPO_CONST || seg->tipo == CT_SEG_CONST)
      {
       if (seg->tipo == CT_SEG_CAMPO_CONST)
          {
           if ((doda = CTREE_dodaend(seg->pointer)) == VD_NULO)
              {
               char buffer[200];
               sprintf(buffer,VIDEO_CARGA_mens_end_dodatela,seg->pointer);
               VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_doda_sub_nao_encontrado);
               return(2);
              }
           pointer = doda->fadr;
          }
        else
          pointer = seg->pointer;

       if (memcmp(pointer,segsub->pointer,seg->tamanho))
           return(3);
      }
   ++segsub;
   ++seg;
  }
 return(FALSE);
}

