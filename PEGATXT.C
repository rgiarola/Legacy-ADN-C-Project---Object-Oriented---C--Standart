#include <INCVIDEO.H>
#define  ESTOQ_PADRAO_MENSS_BUF
#include "..\PADROES.H"
#include "..\STRUCT.H"
#include "..\EXTERNAS.H"

pegatexto(pos_coli,pos_colf,pos_lini,pos_linf,cor)
int *pos_coli, *pos_colf,
    *pos_lini, *pos_linf;
BYTE cor;    
{
 BYTE flag_pos,
      ascii,
      scan;
 char buffer[100];
 int  coli, colf, lini, linf;
 VIDEO_EDITA_CAMPO linha;
 

 coli = *(pos_coli);
 colf = *(pos_colf);
 lini = *(pos_lini);
 linf = *(pos_linf);

 flag_pos = FALSE;      
 
 do
  {
   if (flag_pos)
      {
       VIDEO_PUSHWIN(coli,colf,lini,lini);
       VIDEO_horizontal(coli,colf,lini,'T',cor);
       VIDEO_PUSHWIN(1,50,24,24);
       sprintf(buffer,"COLI %2d COLF %2d LIN %2d TAM %2d",coli,colf,lini,colf-coli+1);
       VIDEO_tprt_l(1,24,buffer,cor);
       VIDEO_getkbd(&ascii,&scan);
       VIDEO_POPWIN();
       VIDEO_POPWIN();
      }
    else
      {
       VIDEO_gtxy(coli,lini);
       VIDEO_PUSHWIN(1,50,24,24);
       sprintf(buffer,"COLI %2d LINI %2d",coli,lini);
       VIDEO_tprt_l(1,24,buffer,cor);
       VIDEO_getkbd(&ascii,&scan);
       VIDEO_POPWIN();
      }  
 
   switch(scan)
    {
     case SOBE :if (!flag_pos)
                    if (lini > 1)
                       --lini;
                 break;       

     case DESCE: if (!flag_pos)
                    if (lini < 24)
                       ++lini;
                  break;       

     case ESQUERDA: if (flag_pos)
                       {
                        if (coli < colf)
                            --colf;
                       }      
                     else
                       if (coli > 1)
                          --coli;
                 break;       

     case DIREITA: if (flag_pos)
                      {
                       if (colf < 80 )
                           ++colf;
                      } 
                     else
                       if (coli < 80)
                          ++coli;
                 break;       

     case ENTERSCAN:if (flag_pos)
		       {
			int ret;
			VD_PUSHWIN(coli,colf,lini,lini);
			linha.col        = coli;
			linha.lin        = lini;
			linha.cor        = cor;
                        linha.buffer     = buffer;
                        linha.tabskip    = VIDEO_NILL(BYTE);
			linha.pegacaracter = VD_lepos;
			linha.autos      =  VIDEO_EDITA_AUTOBLANK;
                        linha.tamanho = colf - coli + 1;
			linha.tipo    = VIDEO_EDITA_STRING;
			linha.mascara = VIDEO_NILL(char);
			if (VIDEO_EDITA_campo(&linha,VD_NILL(VIDEO_NUCLEO_SERV)) == VD_MTTECLA(ESCAPE,ESCAPESCAN))
			   VD_POPWIN();
			 else
			   VD_FREEWIN();
			return;
		       }
		    flag_pos = TRUE;
		    colf = coli;
		    linf = lini;
		    break;

     case 1:return;                 
    };
  }while(TRUE);
}
