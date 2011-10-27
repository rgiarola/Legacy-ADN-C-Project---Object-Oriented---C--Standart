#include <INCVIDEO.H>

VIDEO_FUNCAO VIDEO_CRG_tabfunc[] = {
               VIDEO_CRG_end_cons_obrigatorio,VIDEO_CRG_end_cons_menu,
               VIDEO_CRG_end_cons_faixa,      VIDEO_CRG_end_cons_consdb,
               VIDEO_CRG_end_cons_consdb,     VIDEO_CRG_end_cons_consdb,
               VIDEO_CRG_end_cons_busca,      VIDEO_CRG_end_cons_user_func,
               VIDEO_CRG_end_cons_manutencao};

INT2 VIDEO_CRG_endereca_campos(campo,numcampos,strtelacrg)
VIDEO_CAMPO_TELA *campo;
INT2              numcampos;
VIDEO_TABCRGTELA *strtelacrg;
{
 char                     *buffercrg;
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 INT2                      cont,
                          ret;

 buffercrg = PTR_CAST(char,strtelacrg);
 cont = 0;
 do
  {
   campo->editacampo = VIDEO_TELA_edita_campo;

   campo->dodacampo  = W(campo->dodacampo) + buffercrg;

   campo->tabskip	 = VIDEO_tabskip_default;

   campo->mascara    = (W(campo->mascara) != W(0XFFFE))  ?
                        W(campo->mascara) + buffercrg  :
                        VIDEO_NILL(char);

   campo->user_func = (W(campo->user_func) != W(0XFFFE)) ?
                      W(campo->user_func)+buffercrg   :
                      VIDEO_NILL(char);

   if (W(campo->consiste) != W(0XFFFE))
      {
       consiste = campo->consiste = W(campo->consiste) + strtelacrg->conssai;
       while(consiste->tipocons)
        {
         if (consiste->tipocons > 0 && consiste->tipocons < 10)
             VIDEO_CRG_tabfunc[consiste->tipocons-1].funcao(
                               consiste,strtelacrg);
          else
             if (consiste->tipocons > 11 || consiste->tipocons < 1)
                {
                 char buffer[200];
                 sprintf(buffer,VIDEO_CARGA_mens_funccons,consiste->tipocons);
                 VIDEO_mostra_mens_erro(buffer,
                                        VIDEO_ERRO_end_consistencia_campo);
                 return(FALSE);
                }
              else
                {
                 if (consiste->tipocons == B(11))
                    consiste->objetocons.old_buffer = VD_NULO;
                }

         ++consiste;
        }
      }
    else
      campo->consiste = VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA);

   ++campo;
  }while(++cont < numcampos);

 return(TRUE);
}
