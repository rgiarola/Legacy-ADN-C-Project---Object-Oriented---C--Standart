/* ============================================================================
   Usa especial forma de inicializacao do VIDEO,
   para entradas de telas.

   VD_inictel       () - Simple Abertura
   VD_inictel_trans () - Abertura Sofistica

   ============================================================================ */
#include <INCVIDEO.H>

INT2 VD_inictel( x1, x2, y1, y2,cor )
INT2 x1,    /* Coordenadas.*/
    x2,
    y1,
    y2,
    cor;   /* Cor de Fundo.*/
{
 INT2 ax1,
     ax2,
     ay1,
     ay2,
     centrox,
     centroy;


 centrox = (x2-x1)/2;
 centroy = (y2-y1)/2;
 ax1 = centrox-1;
 ax2 = centrox+1;
 ay1 = centroy-1;
 ay2 = centroy+1;

 /* Verifica possibilidade de FUNCIONAMENTO.*/
 if (ax1<x1 || ax2>x2 ||
     ay1<y1 || ay2>y2 )
    return( FALSE );


 while( ax1>x1 || ax2<x2 ||
        ay1>y1 || ay2<y2 )
   {
     if (ay1>y1)
        {
         ay1 -= 12;
         if (ay1<y1)
            ay1 = y1;
        }

     if (ay2<y2)
        {
         ay2 += 12;
         if (ay2>y2)
            ay2 = y2;
         }

     if (ax1>x1)
        {
         ax1 -= 3;
         if (ax1<x1)
            ax1=x1;
        }

     if (ax2<x2)
        {
         ax2 += 3;
         if (ax2>x2)
            ax2=x2;
        }

     // VIDEO_box_simples(ax1, ax2, ay1, ay2,7);
     VD_quadro( ax1, ax2, ay1, ay2, 177,cor);
   }

 /*VD_quadro( x1, x2, y1, y2, ' ',cor);*/

#ifdef VIDEO_UNIX
           VIDEO_UNIX_refresh_tela();
#endif

 return(TRUE);
}

/* ----------------------------------------------------------------------------
   Inicializa Tela com Transa‡„o
   Modo: 01-L¢gica Fecha
         02-L¢gica Abre
   Veloz:Velocidade de retardo em milisegundos.
   ---------------------------------------------------------------------------- */
INT2 VD_inictel_trans(Modo, Veloz, Coli, Colf, Lini, Linf,
                      CaracLimpa, CorLimpa, CaracFundo, CorFundo)
INT2 Modo      ,
     Veloz     ,
     Coli      ,
     Colf      ,
     Lini      ,
     Linf      ;
BYTE CaracLimpa;
INT2 CorLimpa  ;
BYTE CaracFundo;
INT2 CorFundo  ;
{
 double
      tamanho_coluna,
	  tamanho_linha ,
	  tamanho_maior ,
      desloca_colaux,
      desloca_linaux;

 INT2 contador,
      desloca_coluna,
      desloca_linha ,
      primeira_vez  = TRUE,
      final_coluna  = FALSE,
      final_linha   = FALSE,
      final_acertos = 0,

      aux_coli,
      aux_colf,
      aux_lini,
      aux_linf;



 // C lculo para Deslocamento Proporcional de Linhas e Colunas
 tamanho_coluna = Colf-Coli+1;
 tamanho_linha  = Linf-Lini+1;

 if (tamanho_coluna >= tamanho_linha)
    tamanho_maior = tamanho_coluna;
  else
    tamanho_maior = tamanho_linha;


 if (tamanho_coluna>=tamanho_linha)
	{
     desloca_colaux = 1./D(tamanho_linha / tamanho_maior);
     desloca_linaux = 1; // O menor
	}
  else
	{
     desloca_linaux = 1./D(tamanho_coluna/ tamanho_maior);
     desloca_colaux = 1; // O menor
	}

 // Arredonda Valores
 desloca_linha  = I(desloca_linaux+0.51);
 desloca_coluna = I(desloca_colaux+0.51);
 if (Modo==1)
    {   // Modo Fecha
     aux_coli = Coli;
     aux_colf = Colf;
     aux_lini = Lini;
     aux_linf = Linf;
    }
  else
    {   // Modo Abre
     aux_coli = Coli;
     aux_colf = Coli+desloca_coluna;
     aux_lini = Linf-desloca_linha ;
     aux_linf = Linf;
    }


 while (1)
	{
	 if (!primeira_vez)
		{
         if (Modo==1)
            {// L¢gica Fecha
             // L¢gica Tampa Espa‡os na Coluna
             for (contador=0;contador<desloca_coluna;contador++)
                {
                 VIDEO_vertical (aux_lini-desloca_linha,aux_linf,
                                 aux_colf+desloca_coluna-contador,
                                 CaracFundo,CorFundo);
                 if (final_coluna)
                    break;
                }

             // L¢gica Tampa Espa‡os na Linha
             for (contador=0;contador<desloca_linha;contador++)
                {
                 VIDEO_horizontal(aux_coli,aux_colf+desloca_coluna,
                                  aux_lini-desloca_linha+contador,
                                  CaracFundo,CorFundo);
                 if (final_linha)
                    break;
                }
            }
          else
            {// L¢gica Abre
             // L¢gica Tampa Espa‡os na Coluna
             for (contador=0;contador<=desloca_coluna;contador++)
                 VIDEO_box_car  (aux_coli,aux_colf-desloca_coluna+contador,
                                 aux_lini+desloca_linha,aux_linf,
                                 CorFundo,CaracFundo);

             // L¢gica Tampa Espa‡os na Linha
             for (contador=0;contador<=desloca_linha;contador++)
                 VIDEO_box_car  (aux_coli,aux_colf-desloca_coluna,
                                 aux_lini+desloca_linha-contador,aux_linf,
                                 CorFundo,CaracFundo);
            }
         delay (I(Veloz/2));
        }

     // Apaga o restante e sai
     if ((final_linha && final_coluna) || (final_acertos>(4*Modo)))
        {
         VD_quadro (Coli, Colf, Lini, Linf,CaracFundo,CorFundo);
         break;
        }

     VIDEO_box_car(aux_coli,aux_colf,aux_lini,aux_linf,CorLimpa,CaracLimpa);
     delay (I(Veloz/2));

     /* -----------------------------------------------------------------------

                         Deslocamento das Linhas e Colunas

        ----------------------------------------------------------------------- */
     if (Modo==1)
        {   // Abre
         if (aux_coli<aux_colf && ((aux_colf-aux_coli)>desloca_coluna))
            aux_colf -= desloca_coluna;
          else
            {
             final_coluna = TRUE;
             ++final_acertos;       // N£mero de Ajustes de Coordenadas Max
            }


         if (aux_lini<aux_linf && ((aux_linf-aux_lini)>desloca_linha))
            aux_lini += desloca_linha ;
          else
            {
             final_linha  = TRUE;
             ++final_acertos;       // N£mero de Ajustes de Coordenadas Max
            }
        }
      else
        {   // Fecha
         if (aux_colf<=Colf && ((Colf-aux_colf)>=desloca_coluna))
            aux_colf += desloca_coluna;
          else
            {
             final_coluna = TRUE;
             ++final_acertos;       // N£mero de Ajustes de Coordenadas Max
            }

         if (aux_lini>=Lini && ((aux_lini-Lini)>=desloca_linha))
            aux_lini -= desloca_linha ;
          else
            {
             final_linha  = TRUE;
             ++final_acertos;       // N£mero de Ajustes de Coordenadas Max
            }
        }

     primeira_vez = FALSE;
    }

 return(TRUE);
}

