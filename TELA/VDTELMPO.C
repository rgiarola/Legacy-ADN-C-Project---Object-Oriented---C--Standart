#include <INCVIDEO.H>

INT2 VIDEO_TELA_mouse_posiciona(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_CAMPO_TELA    *campos,
                     *anterior;
 INT2                 numcampos,cont,
                     repdisp  ,servrec;
 VIDEO_IMAGEMTELA    *imagem;

 repdisp    = FALSE;
 servrec    = (*param)->VIDEO_servrec;
 imagem     = (*tela)->imagem_ativa;
 campos     = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos);
 anterior   = VIDEO_NILL(VIDEO_CAMPO_TELA);
 numcampos  = imagem->campos->VIDEO_numcampos;

     if (VIDEO_MOUSE_linha_atual == imagem->linf)
        if (imagem->tipotela > 1)
           {
            if (imagem->tipotela < 6)
               {
                if ((VIDEO_MOUSE_coluna_atual >= imagem->coli)     &&
                    (VIDEO_MOUSE_coluna_atual <= (imagem->coli+7)))
                    {
                     repdisp = TRUE;
                     servrec = VIDEO_MTTECLA(VD_NULO,ALT_I);
                    }

                if ((VIDEO_MOUSE_coluna_atual >= (imagem->coli+20)) &&
                    (VIDEO_MOUSE_coluna_atual <= (imagem->coli+27)))
                    {
                     repdisp = TRUE;
                     servrec = VIDEO_MTTECLA(VD_NULO,ALT_E);
                    }

                if ((VIDEO_MOUSE_coluna_atual >= (imagem->colf-10)) &&
                    (VIDEO_MOUSE_coluna_atual <= (imagem->colf-6)))
                    {
                     repdisp = TRUE;
                     servrec = VIDEO_MTTECLA(VD_NULO,ALT_S);
                    }

				if ((VIDEO_MOUSE_coluna_atual >= (imagem->colf-17)) &&
					(VIDEO_MOUSE_coluna_atual <= (imagem->colf-12)) &&
					((imagem->tipotela == 3) || (imagem->tipotela == 4)))
				   {
					repdisp = TRUE;
					servrec = VIDEO_MTTECLA(VD_NULO,ALT_O);
				   }
			   }

			if ((VIDEO_MOUSE_coluna_atual == (imagem->colf-4)) ||
                (VIDEO_MOUSE_coluna_atual == (imagem->colf-3)))
                {
                 repdisp = TRUE;
                 servrec = VIDEO_MTTECLA(VD_NULO,ALT_MENOS);
                }

            if ((VIDEO_MOUSE_coluna_atual == (imagem->colf-1)) ||
                (VIDEO_MOUSE_coluna_atual == imagem->colf))
                {
                 repdisp = TRUE;
                 servrec = VIDEO_MTTECLA(VD_NULO,ALT_MAIS);
                }
           }
         else
		   {
			if ((VIDEO_MOUSE_coluna_atual == (imagem->colf-4)) ||
                (VIDEO_MOUSE_coluna_atual == (imagem->colf-3)))
                {
                 repdisp = TRUE;
                 servrec = VIDEO_MTTECLA(VD_NULO,ALT_MENOS);
                }

            if ((VIDEO_MOUSE_coluna_atual == (imagem->colf-1)) ||
                (VIDEO_MOUSE_coluna_atual == imagem->colf))
                {
                 repdisp = TRUE;
                 servrec = VIDEO_MTTECLA(VD_NULO,ALT_MAIS);
                }
			if (imagem->tipotela < 6)
				if ((VIDEO_MOUSE_coluna_atual >= (imagem->colf-11)) &&
					(VIDEO_MOUSE_coluna_atual <= (imagem->colf-6)))
				   {
					repdisp = TRUE;
					servrec = VIDEO_MTTECLA(VD_NULO,ALT_O);
				   }
		   }

 if (VIDEO_MOUSE_linha_atual == imagem->lini)
     if ((VIDEO_MOUSE_coluna_atual >= (imagem->colf-5))     &&
         (VIDEO_MOUSE_coluna_atual <= (imagem->colf-1)))
          {
           repdisp = TRUE;
           servrec = VIDEO_MTTECLA(ESCAPE,ESCAPESCAN);
          }

 for (cont = 0;cont < numcampos;cont++,campos++)
     if (campos->lin >= VIDEO_MOUSE_linha_atual)
        {
         if (campos->lin > VIDEO_MOUSE_linha_atual)
             if (!cont)
                 break;
         do
          {
           if (campos->col >= VIDEO_MOUSE_coluna_atual)
              {
               if (anterior && (campos->col > VIDEO_MOUSE_coluna_atual))
                  --cont;
               imagem->campos->VIDEO_inicial = cont;
               break;
              }
            else
              if ((cont < numcampos) &&
                  ((campos+1)->lin != VIDEO_MOUSE_linha_atual))
                 {
                  imagem->campos->VIDEO_inicial = cont;
                  break;
                 }

           anterior = campos;
           ++cont;
           ++campos;
           if ((campos->lin != VIDEO_MOUSE_linha_atual) ||
               (cont == numcampos))
              {
               imagem->campos->VIDEO_inicial = --cont;
               break;
              }
          }while(TRUE);
         break;
        }

 (*param)->VIDEO_repdisp = repdisp;
 (*param)->VIDEO_servrec = servrec;

 return(TRUE);
}

