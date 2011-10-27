#include <INCVIDEO.H>

INT2 VIDEO_mostra_opcoes(work)
VIDEO_INFO_MENU *work;
{
 char **op;
 INT2  cont   , lin,
      contcol, col;

 VD_CLEAR_PIC(work->coli,work->coli + (work->tamcol) *  (work->numpag + 1) - 2,
 work->lini,work->linf,work->cor_opcao);

 for (cont = contcol = 0;contcol <= work->numpag && cont < work->numop;
      contcol++)
     {
      cont = work->opini + contcol * work->numlin;
      col  = work->coli  + contcol * work->tamcol;
      lin  = work->lini;

      if (work->flagmoldura == 2 && contcol <= work->numpag && contcol)
         {
          INT2  aux;
          aux = (work->tamcol-work->colf+work->coli-1);
          if (aux)
             {
#if defined(__VIDEO_BOX_CARGA_PARAMETROS)
              VD_vertical(lin,work->linf,col-aux/2-1,
                *(&VIDEO_box_parametros->VIDEO_conec_col_dupla+
                  work->tipomoldura), work->cor_moldura);
#else
              VD_vertical(lin,work->linf,col-aux/2-1,
                *(&VIDEO_conec_col_dupla+work->tipomoldura),
                work->cor_moldura);
#endif
             }
         }

      op   = &work->opcoes[cont];
      while(lin <= work->linf && cont++ < work->numop)
           VD_tprt_l(col,lin++,*op++,work->cor_opcao);
     }
 return(TRUE);
}
