#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_mover(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *work;
 INT2 coli,colf,lini,linf,col,lin;

 work = (*campos);

 lini = work->lini;
 linf = work->linf;
 coli = work->coli;
 colf = work->coli+(work->numpag+1)*work->tamcol - 2;
 col = work->col;
 lin = work->lin;

 if (work->flagmoldura == 2)
    {
     --coli;
     ++colf;
     --lini;
     ++linf;
     VD_plotcarac((colf+coli)/2,lini,24,work->cor_moldura);
     VD_plotcarac((colf+coli)/2,linf,25,work->cor_moldura);
     VD_plotcarac(coli,(lini+linf)/2,27,work->cor_moldura);
     VD_plotcarac(colf,(lini+linf)/2,26,work->cor_moldura);
    }

 VD_movequadro(&coli,&colf,&lini,&linf,&col,&lin,TRUE,work->cor_sombra,
                      &VD_getkbd);

 work->colf = coli + work->colf - work->coli;
 work->coli = coli;
 work->lini = lini;
 work->linf = linf;
 work->col = col;
 work->lin = lin;

 if (work->flagmoldura == 2)
    {
     VD_box(coli,colf,lini,linf,work->cor_moldura,work->tipomoldura,
				work->caracmoldura);
     ++work->lini;
     --work->linf;
     ++work->coli;
     ++work->colf;
    }
 return(TRUE);
}

