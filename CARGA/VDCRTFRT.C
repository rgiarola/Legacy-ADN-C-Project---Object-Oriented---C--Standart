#include <INCVIDEO.H>

INT2 VIDEO_CRG_libera_tela(tela)
VIDEO_ESTMANUT *tela;
{
 VIDEO_TABCRGTELA *strtelacrg;
 VIDEO_IMAGEMTELA *imagem;
 int			  cont,contcampo;
 VIDEO_CAMPO_TELA *campos;
 VIDEO_CTRL_CARGA *aux,*posterior,*anterior,*delet;

 if (tela->strtelacrg)
    {
     if (tela->tela)
        {
         strtelacrg = PTR_CAST(VIDEO_TABCRGTELA,tela->strtelacrg);
         imagem = strtelacrg->imagemsai;

         for (cont = 0,imagem = strtelacrg->imagemsai;
                                cont < strtelacrg->contimagemsai;cont++,imagem++)
              if (imagem->campos)
                  for (contcampo = 0,
                       campos = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos)
                      ;contcampo < imagem->campos->VIDEO_numcampos;contcampo++,campos++)
                       if (campos->consiste->tipocons == VIDEO_TELA_CONS_OLD_BUFFER)
                           if (campos->consiste->objetocons.old_buffer)
                               VIDEO_FREE_ALLOC_MEM(campos->consiste->objetocons.old_buffer);
        }

     aux = delet = VIDEO_ctrl_carga;
     while(delet)
      {
       if (delet->atual == tela)
           break;
       if (delet->posterior)
           delet = posterior;
         else
           break;
      }

     if (delet->atual == tela)
        {
         posterior = delet->posterior;
         anterior  = delet->anterior;
         
         if (anterior)
            {
             anterior->posterior = posterior;
             aux = anterior;
            }

         if (posterior)
            {
             posterior->anterior = anterior;
             aux = posterior;
            }

         if (posterior || anterior)
             VIDEO_FREE_ALLOC_MEM(delet);

         VIDEO_ctrl_carga = aux;
        }
      else
         VIDEO_mostra_mens_erro(VIDEO_MENS_erro_ctrl_carga,VIDEO_ERRO_controle_carga);

     VIDEO_free_alloc_parametros(tela->strtelacrg);
     tela->strtelacrg   =
     tela->tela         = VIDEO_NILL(VD_VOID);
     VIDEO_imagem_atual = VD_NULO;
     VIDEO_tela_atual   = VD_NULO;
     VIDEO_cons_atual   = VD_NULO;
     VIDEO_campo_atual  = VD_NULO;
     VIDEO_doda_campo   = VD_NULO;
     return(TRUE);
    }

 return(FALSE);
}
