#include <INCVIDEO.H>

INT2 VIDEO_TELA_data_base_preg(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste,*cons;
 VIDEO_IMAGEMTELA         *imagem,*imagens;
 VIDEO_CAMPO_TELA         *campo,*campos;
 INT2                      cont_campos,
                          cont_imagens;

 imagem  = (*tela)->imagem_ativa;

 campo   = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos) +
           imagem->campos->VIDEO_inicial;

 imagem->flagimagem |= VIDEO_TELA_DISPCAMPOS;

 if ((consiste = campo->consiste) == VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
    return(TRUE);

     while(consiste->tipocons)
      {
       if (consiste->tipocons==VIDEO_TELA_CONS_POSICIONA_DB)
          {
           if (consiste->objetocons.consdb)
              {
               if (imagem->arquivo ==
                          CTREE_keyfil(consiste->objetocons.consdb->indice))
                  {
#ifdef DATABASE_CTREE
                   for (imagens = (*tela)->imagens,
                        cont_imagens = 0;cont_imagens < (*tela)->num_imagens;
                        cont_imagens++,imagens++)
                        for (campos = PTR_CAST(VIDEO_CAMPO_TELA,imagens->campos->VIDEO_campos),
                             cont_campos = 0;cont_campos < imagens->campos->VIDEO_numcampos;
                             cont_campos++,campos++)
                            if ((cons = campos->consiste) !=
                                 VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
                                while(cons->tipocons)
                                 {
                                  if (cons->tipocons            ==
                                       VIDEO_TELA_CONS_POSICIONA_DB)
                                     {
                                      if (imagem->arquivo ==
                                          CTREE_keyfil(cons->objetocons.consdb->indice))
                                          cons->objetocons.consdb->posicao =
                                          consiste->objetocons.consdb->posicao;
                                      break;
                                     }
                                  ++cons;
                                 }
#endif
                   VIDEO_TELA_seta_alteracao(*tela);
                  }
               break;
              }
           return(TRUE);
          }
       ++consiste;
      }
 return(TRUE);
}

