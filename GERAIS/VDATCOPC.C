#include <INCVIDEO.H>

INT2  VIDEO_alteracor_pict(coli,colf,lini,linf,col,lin,flagtipo,numcol,
			 cor_opcoes,cor_selecao,
			 cor_moldura,cor_sombra,funcserv)
INT2    coli, colf,
       lini, linf,
       col ,lin ,
       flagtipo ,numcol;
BYTE   *cor_opcoes,
       *cor_selecao,
       *cor_moldura,
       *cor_sombra;
INT2    (*funcserv)(BYTE *ascii,BYTE *scan);
{
 BYTE    corfrente[4],
         corfundo[4],
         atribfundo[4],
	     atribfrente[4],
	     ascii,scan;
 INT2     opsel,
	     ret, cont, aux;

 static WORD tabskip[] = {VD_MTTECLA(ESCAPE,ESCAPESCAN),
                          VD_MTTECLA(VD_NULO,F1),
                          VD_MTTECLA(VD_NULO,F2),
                          VD_MTTECLA(VD_NULO,F3),
                          VD_MTTECLA(VD_NULO,F4),
                          VD_MTTECLA(45,74),
                          VD_MTTECLA(43,78),
                          VD_MTTECLA(VD_NULO,PGUP),
                          VD_MTTECLA(VD_NULO,PGDN),
                          VD_MTTECLA(VD_NULO,SOBE),
                          VD_MTTECLA(VD_NULO,DESCE),
                          VD_MTTECLA(VD_NULO,HOME),
                          VD_MTTECLA(VD_NULO,END),
                          VD_NULO};
#ifdef VIDEO_UNIX
 INT2                      old_flag_video;
#endif
 VIDEO_restaura_param_cor(&atribfundo[0],&corfundo[0],&atribfrente[0],&corfrente[0],*(cor_opcoes));
 VIDEO_restaura_param_cor(&atribfundo[1],&corfundo[1],&atribfrente[1],&corfrente[1],*(cor_selecao));
 VIDEO_restaura_param_cor(&atribfundo[2],&corfundo[2],&atribfrente[2],&corfrente[2],*(cor_moldura));
 VIDEO_restaura_param_cor(&atribfundo[3],&corfundo[3],&atribfrente[3],&corfrente[3],*(cor_sombra));

 opsel = 0;

#ifdef VIDEO_UNIX
     old_flag_video = VIDEO_UNIX_flag_video;
     VIDEO_UNIX_flag_video |= VIDEO_UNIX_AUTO_REFRESH;
     VIDEO_UNIX_refresh_tela();
#endif

 do
  {
   ascii = scan = 0;
   do
    {
     (*funcserv)(&ascii,&scan);
    }while((ret = VIDEO_testa_tabskip(ascii,scan,tabskip)) == FALSE);
   --ret;
   switch(ret)
    {
     case 1:
     case 2:
     case 3:
     case 4: switch(flagtipo)
	      {
	       case 0: if (ret > 1)
			  continue;
	       case 1:
	       case 2: if (ret > 2)
			  continue;
	      }
	     opsel = ret - 1;
	     break;
     case 5: corfrente[opsel] = corfrente[opsel] == 7 ? 0:
				++corfrente[opsel];
	     break;
     case 6: corfrente[opsel] = !corfrente[opsel] ? 7 :
				--corfrente[opsel];
	     break;
     case 7: atribfrente[opsel] = VIDEO_NORMAL;
	     break;
     case 8: atribfrente[opsel] = VIDEO_BRIL;
	     break;
     case 9: corfundo[opsel] = corfundo[opsel] == 7 ? 0 :
			       ++corfundo[opsel];
	     break;
     case 10: corfundo[opsel] = !corfundo[opsel] ? 7 :
				--corfundo[opsel];
	     break;
     case 11: atribfundo[opsel] = VIDEO_NORMAL;
	     break;
     case 12: atribfundo[opsel] = VIDEO_INTER;
	     break;
     case 0:*(cor_opcoes)  = VIDEO_FORMATO(corfundo[0],atribfundo[0],
					   corfrente[0],atribfrente[0]);
	    *(cor_selecao) = VIDEO_FORMATO(corfundo[1],atribfundo[1],
					   corfrente[1],atribfrente[1]);
	    *(cor_moldura) = VIDEO_FORMATO(corfundo[2],atribfundo[2],
					   corfrente[2],atribfrente[2]);
	    *(cor_sombra)  = VIDEO_FORMATO(corfundo[3],atribfundo[3],
					   corfrente[3],atribfrente[3]);
	    return(TRUE);
    }

   switch(flagtipo)
    {
     case 1: VIDEO_setatrib(coli,colf,lini,linf,VIDEO_FORMATO(
			    corfundo[opsel],atribfundo[opsel],
			    corfrente[opsel],atribfrente[opsel]));
	     break;

     case 0: if (ret > 4)
		 VIDEO_setatrib(coli,colf,lini,linf,
				VIDEO_FORMATO(corfundo[0],atribfundo[0],
					      corfrente[0],atribfrente[0]));
	     break;

     case 3: if (ret > 4)
		{
		 aux = (colf-coli+1)*(numcol+1) + numcol;
		 VD_setatrib(coli-1,coli+aux,lini-1,lini-1,
			    VIDEO_FORMATO(corfundo[2],atribfundo[2],
					  corfrente[2],atribfrente[2]));
		 VD_setatrib(coli-1,coli+aux,linf+1,linf+1,
			    VIDEO_FORMATO(corfundo[2],atribfundo[2],
					  corfrente[2],atribfrente[2]));
		 VD_setatrib(coli-1,coli-1,lini,linf,
			    VIDEO_FORMATO(corfundo[2],atribfundo[2],
					  corfrente[2],atribfrente[2]));
		 VD_setatrib(coli+aux,coli+aux,lini,linf,
			    VIDEO_FORMATO(corfundo[2],atribfundo[2],
					  corfrente[2],atribfrente[2]));
		 VD_setatrib(coli+aux+1,coli+aux+1,lini,linf+2,
			    VIDEO_FORMATO(corfundo[3],atribfundo[3],
					  corfrente[3],atribfrente[3]));
		 VD_setatrib(coli,coli+aux,linf+2,linf+2,
			    VIDEO_FORMATO(corfundo[3],atribfundo[3],
					  corfrente[3],atribfrente[3]));
		 aux = (colf-coli+2);
		 for (cont = 1;cont <= numcol;cont++)
		     VD_setatrib(coli-1+aux*cont,coli-1+aux*cont,lini,linf,
			    VIDEO_FORMATO(corfundo[2],atribfundo[2],
					  corfrente[2],atribfrente[2]));
		}

     case 2: if (ret > 4)
		{
		 aux = (colf-coli+2);
		 for (cont = 0;cont <= numcol;cont++)
		      VD_setatrib(coli+aux*cont,colf+aux*cont,
			lini,linf,VIDEO_FORMATO(corfundo[0],atribfundo[0],
						corfrente[0],atribfrente[0]));
		 VD_setatrib(col,col+aux-2,lin,lin,
			     VIDEO_FORMATO(corfundo[1],atribfundo[1],
					   corfrente[1],atribfrente[1]));
		}
    }

#ifdef VIDEO_UNIX
     VIDEO_UNIX_refresh_tela();
#endif

  }while(TRUE);

#ifdef VIDEO_UNIX
     VIDEO_UNIX_flag_video = old_flag_video;
#endif
}
