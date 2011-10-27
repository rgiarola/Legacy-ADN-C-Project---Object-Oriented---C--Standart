#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_letra(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *menu = *campos;
 char            **tabela = menu->opcoes,letra= C(menu->opselec);
 int             cont,numcol,numpag,col,lin;

 menu->opselec = 0;
 if (menu->numop > 1)
    {
     cont = menu->opsel == (menu->numop-1) ? 0 : menu->opsel+1;
     tabela += cont;
     do
      {
       if ((**tabela&~B05) == (letra&~B05))
          {
           lin = menu->lin;
           col = menu->col;

           VIDEO_setatrib(col ,col+menu->tamdispop-1,
                          lin ,lin,menu->cor_opcao);

           menu->colatu = (cont/menu->numlin);
           menu->opsel  = cont;
           menu->lin = menu->lini+(cont%menu->numlin);
           menu->flagdispop = TRUE;

           if ((cont >= menu->opini) &&
               (cont < (menu->opini+((menu->numpag+1)*(menu->numlin)))))
			  {
               menu->colpag = (cont-menu->opini)/menu->numlin;
               menu->col = menu->coli + (menu->colpag * menu->tamcol);
               numcol = cont == (menu->numop-1) ? 0 : cont+1;
               tabela = menu->opcoes + numcol;
               while((**tabela&~B05) != (letra&~B05) && (cont != numcol))
                {
                 if (++numcol == menu->numop)
                    {
                     numcol = 0;
                     tabela = menu->opcoes;
                    }
                  else
                    ++tabela;
                }

               if (numcol == cont)
                  {
                   (*param)->VIDEO_repdisp = TRUE;
                   (*param)->VIDEO_servrec = VD_MTTECLA(ENTER,ENTERSCAN);
                  }
			  }
            else
              {
               menu->flagdispcol = TRUE;
               if (cont > menu->opini)
                  {
                   menu->opini  = ((menu->colatu+1)-(menu->numpag+1))*menu->numlin;
                   menu->colpag = menu->numpag;
                   menu->col    = menu->coli + (menu->colpag * menu->tamcol);
                  }
                 else
                  {
                   menu->opini  = menu->colatu*menu->numlin;
                   menu->colpag = 0;
                   menu->col    = menu->coli;
                  }
              }
           break;
          }

       if (cont == menu->opsel)
           break;

       if (++cont == menu->numop)
          {
           tabela = menu->opcoes;
           cont = 0;
          }
        else
          ++tabela;
      }while(TRUE);
	}

 return(TRUE);
}




