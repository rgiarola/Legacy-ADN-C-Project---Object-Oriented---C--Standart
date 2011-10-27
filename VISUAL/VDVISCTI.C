#include <INCVIDEO.H>


INT2 VIDEO_VISUAL_impressao_arquivo(ctrlvisual)
VIDEO_VISUAL_CONTROLE *ctrlvisual;
{
 int                      arquivo,copias,desc,ret,
                          regua,cont = 0,tcol,col,impressora;
 char                     *buffer;
 DWORD                    tamanho,lido,total,totlido,pagini,
                          pagfim,posicao,posfim,totimp;
 VIDEO_TABCRGTELA         *strtelacrg;
 VIDEO_IMAGEMTELA         *imagem;
 VIDEO_TELA_ENTRADA_DADOS *telaedit;
 BYTE                     ascii,scan;

 if (!ctrlvisual->linhaaux)
	return(FALSE);

 if (ctrlvisual->desc <= 0)
	 return(FALSE);

/*****************************************************************************
                          EXECUTA TELA DE CONTROLE DE COPIAS
*****************************************************************************/

 if (VIDEO_CRG_display_imagem(&VIDEO_VISUAL_imagem_impressao,1,2) !=
     VD_MTTECLA(VD_NULO,ALT_O))
	 return(FALSE);

 arquivo = ctrlvisual->desc;
 tamanho = filelength(arquivo);

/*****************************************************************************
                            CARREGA TELA DE FUNDO
*****************************************************************************/
 if (!VIDEO_CRG_carrega_objeto(&VIDEO_VISUAL_imagem_spool,1))
    {
     char buffer[100];
     sprintf(buffer,VIDEO_VISUAL_mens_carga_tela_apr,
                    VIDEO_VISUAL_imagem_spool.sistcrg,
                    VIDEO_VISUAL_imagem_spool.telacrg);
     VIDEO_mostra_mens_erro(buffer,TRUE);
	 return(FALSE);
    }

/*****************************************************************************
                            PREPARA TELA DE FUNDO
*****************************************************************************/
 if (!VIDEO_CRG_prepara_tela(&VIDEO_VISUAL_imagem_spool))
    {
     char buffer[100];
     sprintf(buffer,VIDEO_VISUAL_mens_prep_tela_apr,
                    VIDEO_VISUAL_imagem_spool.sistcrg,
                    VIDEO_VISUAL_imagem_spool.telacrg);
     VIDEO_mostra_mens_erro(buffer,TRUE);
     VIDEO_CRG_libera_tela(&VIDEO_VISUAL_imagem_spool);
	 return(FALSE);
    }

/*****************************************************************************
                            DISPLAY TELA DE FUNDO
*****************************************************************************/
 memcpy(VD_GETEND(BDISP_texto3,char),ctrlvisual->nomevisual,35);
 *(VD_GETEND(BDISP_texto3,char)+35) = 0;

 strtelacrg         = PTR_CAST(VIDEO_TABCRGTELA,VIDEO_VISUAL_imagem_spool.strtelacrg);
 telaedit           = strtelacrg->telasai;
 telaedit->flagtela = FALSE;
 imagem             = strtelacrg->telasai->imagens;

 tcol = (imagem->colf-2)-(imagem->coli+2)+1;

 impressora = 0;
 /*
   Logica Original
 switch(VD_GETBUF(BREL_selec3,char))
  {
   case 'S':++impressora;
   case '3':++impressora;
   case '2':++impressora;
   case '1':++impressora;
  }
 */

/*
 Quando eu Passei para BC4x foi necessario, por‚m ao ativar Modo HUGE,
 parou de funcionar ...
  */
 switch(VD_GETBUF(BREL_selec3,char))
  {
   case '3':++impressora;   // 3
   case '2':++impressora;   // 2
   case 'P':                // 1
   case '1':++impressora;   // 1
  }

/*****************************************************************************
                            LOOP DE COPIAS
*****************************************************************************/
 VIDEO_VISUAL_flag_int  = FALSE;
 // printf ("\npasso 1");getch();

 pagini = L(VD_GETBUF(BREL_selec7,WORD) - 1) * L(VD_GETBUF(BREL_selec6,BYTE));
 pagfim = L(VD_GETBUF(BREL_selec8,WORD)) * L(VD_GETBUF(BREL_selec6,BYTE));

 if (ctrlvisual->lido < pagini || pagfim < pagini)
    {
     VIDEO_CRG_libera_tela(&VIDEO_VISUAL_imagem_spool);
	 return(FALSE);
    }

 posicao = pagini;
 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_lseek(ctrlvisual->descindex,posicao*sizeof(DWORD),VIDEO_INI_ARQ);
 VIDEO_read(ctrlvisual->descindex,&posicao,sizeof(DWORD));

 if (pagfim > ctrlvisual->lido)
    posfim = tamanho;
  else
    {
     posfim = pagfim;
     VIDEO_lseek(ctrlvisual->descindex,posfim*sizeof(DWORD),VIDEO_INI_ARQ);
     VIDEO_read(ctrlvisual->descindex,&posfim,sizeof(DWORD));
    }

 for (copias = 0;copias < VD_GETBUF(BREL_selec1,DWORD);copias++)
     {
      totlido = posicao;
      totimp = posfim - posicao + 1;
      VD_GETBUF(BREL_selec4,BYTE) = copias+1;

      imagem->flagimagem = VIDEO_TELA_DISPIMAGEM|
                           VIDEO_TELA_DISPCAMPOS|VIDEO_TELA_FLAGRESETDISPLAY;
      VIDEO_NUCLEO_servidor_mspas(strtelacrg->nutelasai);

      buffer  = ctrlvisual->linhaaux;
      VIDEO_VISUAL_flag_erro = FALSE;
      VIDEO_lseek(arquivo,posicao,VIDEO_INI_ARQ);

      // printf ("\npasso 2");getch();
      if (VIDEO_VISUAL_flag_erro)
         {
          strcpy(buffer,VIDEO_IMPRESS_erro_impressora);
          if (VIDEO_mostra_mens_erro(buffer,FALSE) ==
              VD_MTTECLA(ESCAPE,ESCAPESCAN))
              break;
          --copias;
          continue;
         }

      VD_CLEAR_PIC(imagem->coli+2,imagem->colf-2,
                   imagem->linf-1,imagem->linf-1,
                   VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));

      if (VD_GETBUF(BREL_selec2,char) == 'S')
         {
          VIDEO_mostra_mens_erro(VIDEO_VISUAL_prepare_impress,TRUE);
         }

      total = 0;

      do
       {
        // printf ("\npasso 3");getch();
        VIDEO_VISUAL_flag_erro = FALSE;

        buffer  = ctrlvisual->linhaaux;

        lido = VIDEO_read(arquivo,buffer,4096);

        if (VIDEO_VISUAL_flag_erro)
           {
            sprintf(buffer,VIDEO_VISUAL_erro_leitura,ctrlvisual->nomevisual);
            if (VIDEO_mostra_mens_erro(buffer,FALSE) ==
                VD_MTTECLA(ESCAPE,ESCAPESCAN))
               {
                total = tamanho+1;
                copias = VD_GETBUF(BREL_selec1,DWORD) + 1;
                break;
               }
            continue;
           }

        if (lido <= 0)
            break;

/*
        if (impressora == 4)
           {
            int totgrv;

            totgrv = min(lido,(posfim-(totlido+1)));
           }
*/

        for (cont = 0;cont < lido && (++totlido <= posfim);cont++)
            {
             VIDEO_VISUAL_flag_erro = FALSE;
             // printf ("\npasso 4 - ‚ aqui ...");getch();

             ret = VIDEO_IMPRESS_envia(*buffer,impressora);

             // printf ("\npasso 5 - Passou?...");getch();

             // Por ele Est  Testando os B11 e B13?
             if (ret&(B08|B11|B13) || !(ret&B12))
                {
                 ret = VIDEO_mostra_mens_erro(
                        VIDEO_IMPRESS_erro_impressora,FALSE);
                 --cont;
                 --totlido;
                }
              else
                {
                 ++total;
                 if ((col = I(D(D(total)*D(tcol))/D(totimp)) + (imagem->coli+2) - 1) <
                    imagem->coli)
                    col = imagem->coli+2;

                 if (col > (imagem->colf - 2))
                    col = (imagem->coli -2) + tcol-1;

                 if ((col == ((imagem->coli -2) + tcol-1)) &&
                     total < (tamanho-1))
                    --col;

                 VIDEO_horizontal(imagem->coli+2,col,imagem->linf-1,'²',
                                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
                 ++buffer;
                 ret = FALSE;
                }

             if (VD_getkey(&ascii,&scan) && !ret)
                 ret = VD_MTTECLA(ascii,scan);

             if (ret == VD_MTTECLA(ESCAPE,ESCAPESCAN))
                 if (VD_telaconf(30,10,VIDEO_VISUAL_cancela_impress,
                       VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL)) == TRUE)
                    {
                     total = tamanho+1;
                     copias = VD_GETBUF(BREL_selec1,DWORD) + 1;
                     break;
                    }
            }

       }while(total <= tamanho && totlido <= posfim); // Arquivo

     } // Copias

 VIDEO_VISUAL_flag_int	= TRUE;
 VIDEO_VISUAL_flag_erro = FALSE;

 VIDEO_CRG_libera_tela(&VIDEO_VISUAL_imagem_spool);
 return(TRUE);
}


