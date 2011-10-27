#include <INCVIDEO.H>

INT2 VIDEO_MENU_pega_selecao(work,param)
VIDEO_INFO_MENU   *work;
VIDEO_NUCLEO_SERV *param;
{
 BYTE ascii, scan;
 int  flagtravado,timetrav,timeout;


 param->VIDEO_servrec = FALSE;

 VD_tcursor(0X20,0X20);

 if (work->flagmoldura == TRUE)
    {
     INT2 aux;

     if ((work->coli > 1) && (work->colf < 79) &&
         (work->lini > 1) && (work->linf < 24))
         {
          INT2 colf,tamesc;
          char buffer[41];
          colf = work->coli+(work->numpag+1)*work->tamcol - 1;

          VD_PUSHWIN(work->coli-1,colf + 1,work->lini-1,work->linf+2);
          VD_setatrib(work->coli,colf + 1,
                      work->lini,work->linf+2,work->cor_sombra);
          VD_box(work->coli-1,colf,
                 work->lini-1,work->linf+1,
                 work->cor_moldura,I(work->tipomoldura),
                 work->caracmoldura);

          if ((aux = (colf-work->coli+1)) > 4)
             {
              INT2 coli;

              coli = colf - 4 - (aux > 5);

              VD_tprt_l(coli,work->lini-1,VIDEO_MENU_bottom_termina,0);
              VD_plotcarac(coli+2,work->lini-1,'þ',
                           VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
              tamesc = 5;
             }
           else
             {
              INT2 coli;

              coli = colf - 2 - (aux > 3);

              VD_tprt_l(coli,work->lini-1,VIDEO_MENU_bottom_termina_menor,0);
              VD_plotcarac(coli+1,work->lini-1,'þ',
                           VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
              tamesc = 3;
             }

          work->flagmoldura = 2;

          if (work->titulo)
             {
              if ((aux = (colf-1) - work->coli + 1 - tamesc) < 0)
                 aux = 0;
              memcpy(buffer,work->titulo,20);
              buffer[20] = 0;
              if (strlen(buffer) > aux)
                  buffer[aux] = 0;

              VD_tprt_l(work->coli,work->lini-1,buffer,0);
             }
         }
       else
         VD_PUSHWIN(work->coli,work->coli+(work->numpag+1)*work->tamcol-2,
                    work->lini,work->linf);

/*
     aux = (work->tamcol-work->colf+work->coli-1);
     aux = aux >= 0 ? aux : 0;
     aux -= (aux / 2 + 1);
     work->tamdispop = work->colf - work->coli + aux + 1;
*/
/*     VD_tprt_l(work->coli,work->lini,work->titulo,0);*/
    }

 if (work->flagdispcol)
    {
     VIDEO_mostra_opcoes(work);
     work->flagdispcol = FALSE;
    }

 if (work->flagdispop)
    {
     VIDEO_setatrib(work->col,work->col+work->tamdispop-1,work->lin,work->lin,
                    work->cor_selecao);
     work->flagdispop = FALSE;
    }

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo > 0)
    {
     VIDEO_MOUSE_habcursor();
     flagtravado = VIDEO_MOUSE_flagtravado;
     timetrav    = VIDEO_MOUSE_timetrav;
     timeout     = VIDEO_MOUSE_timeout;
     VIDEO_MOUSE_flagtravado = TRUE;
     VIDEO_MOUSE_timetrav = 2;
     VIDEO_MOUSE_timeout  = 20;
    }
#endif

#ifdef VIDEO_UNIX
 VIDEO_UNIX_refresh_tela();
#endif

 (*work->funcserv)(&ascii,&scan);

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo > 0)
    {
     VIDEO_MOUSE_deshabcursor();
     VIDEO_MOUSE_flagtravado = flagtravado;
     VIDEO_MOUSE_timetrav    = timetrav   ;
     VIDEO_MOUSE_timeout     = timeout    ;
    }
#endif

 if (!VIDEO_testa_tabskip(ascii,scan,VIDEO_tabskip_default))
    {
     work->opselec = W(ascii);
     scan  = ascii = LETRA_MENU;
    }

 param->VIDEO_servrec = VD_MTTECLA(ascii,scan);

 return(TRUE);
}


