#include <INCVIDEO.H>
/* ============================================================================
                   Visualizacao de HELP e Arquivo Texto
                                Lib Visual
                               Tech C 1994
   ============================================================================ */

VD_VOID VIDEO_VISUAL_mostra_linha_scrow(VIDEO_VISUAL_CONTROLE *visual);

VD_VOID VIDEO_VISUAL_dispara_visual(nomevisual,nomerelat,flagtipo,
									telavisual,visualaux,flagimpressao)
char           *nomevisual,
               *nomerelat;
BOOLEAN        flagtipo;
VIDEO_ESTMANUT *telavisual;
INT2           (*visualaux)(),
               flagimpressao;
{
 INT2                     indice , ret ,
                          arquivo, cont;
 WORD                     tamanho, desc;
 VIDEO_VISUAL_CONTROLE    *visual = VD_NULO;
 char                     **linha,titulo[100],
                          nomearq[61],
                          *bufferaux,*contvar;
 VIDEO_NUCLEO_SERV        nucleo;
 VIDEO_TABCRGTELA         *strtelacrg;
 VIDEO_IMAGEMTELA         *imagem;
 VIDEO_TELA_ENTRADA_DADOS *telaedit;
 static BOOLEAN           flagvisual = FALSE;

 if (flagvisual && !flagtipo)
    return;

 disable();
 ++flagvisual;
 enable();

 if (!VIDEO_VISUAL_salva_variaveis(&contvar))
    {
     disable();
     --flagvisual;
     enable();
     return;
    }

 strcpy(titulo,VIDEO_montagem_path);
 titulo[0] = 'A' + getdisk();
 getcurdir(0, titulo+3);
 strcpy(VD_GETEND(BDISP_texto1,char),titulo);
 strcpy(VD_GETEND(BDISP_texto2,char),"*.OUT");


/*****************************************************************************
                           VISUALIZACAO DE HELP
*****************************************************************************/
 if (flagtipo)
    {
     ATIVA_BUF_DADOS;

     indice  = CTREE_keynm(VIDEO_HELP_indice_help);
     arquivo = CTREE_keyfil(indice);

     CTREE_inbuf(arquivo);
     strcpy(VD_GETEND(VIDEO_HELP_nome_help,char),nomevisual);

     if ((ret = CTREE_find(indice,VD_NULO,FIND_IGUAL,CT_LE_DADOS)) != FALSE)
        {
         char bufaux[100];
         if (ret != 101)
            {
             sprintf(bufaux,VIDEO_HELP_ler_help,
                            nomevisual,ret,indice,arquivo);
             VIDEO_mostra_mens_erro(bufaux,TRUE);
            }
          else
            {
             sprintf(bufaux,VIDEO_HELP_naodef,nomevisual);
             VIDEO_mostra_mens_erro(bufaux,TRUE);
            }
         disable();
         --flagvisual;
         VIDEO_VISUAL_restaura_variaveis(&contvar);
         enable();
         return;
        }

     tamanho = VD_GETBUF(VIDEO_HELP_tamanho_help,WORD);

     if (VIDEO_ALLOC_MEM(visual,tamanho) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUAL_1);
         disable();
         --flagvisual;
         enable();
         VIDEO_VISUAL_restaura_variaveis(&contvar);
         return;
        }

     if ((ret = CTREE_rdvlen(arquivo,CAST_CHAR(visual),tamanho)) != FALSE)
        {
         char bufaux[100];
         sprintf(bufaux,VIDEO_HELP_extencao_help,ret,indice,arquivo);
         VIDEO_mostra_mens_erro(bufaux,TRUE);
         VIDEO_FREE_ALLOC_MEM(visual);
         disable();
         --flagvisual;
         enable();
         VIDEO_VISUAL_restaura_variaveis(&contvar);
         return;
        }

     linha = &visual->linha[0];
     visual->titulo = W(visual->titulo) + CAST_CHAR(visual) +
                                      (visual->numlin * sizeof(char **));

     for (cont = 0;cont < visual->numlin;cont++,linha++)
         *linha = W(*linha) + CAST_CHAR(visual) + (visual->numlin * sizeof(char **));

     visual->linhaaux = VD_NULO;
     visual->flags = FALSE;
    }
  else
    {
/*****************************************************************************
                             VISUALIZACAO DE ARQUIVO
*****************************************************************************/
     if (VIDEO_ALLOC_MEM(visual,sizeof(VIDEO_VISUAL_CONTROLE)+26 * sizeof(char *)) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUAL_1);
         VD_POPWIN();
         close(desc);
         disable();
         --flagvisual;
         enable();
         VIDEO_VISUAL_restaura_variaveis(&contvar);
         return;
        }

     VIDEO_setmem(visual,sizeof(VIDEO_VISUAL_CONTROLE)+26 * sizeof(char *),0);

     if (VIDEO_ALLOC_MEM(visual->linhaaux,4096) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUAL_2);
         VIDEO_FREE_ALLOC_MEM(visual);
         VD_POPWIN();
         close(desc);
         disable();
         --flagvisual;
         enable();
         VIDEO_VISUAL_restaura_variaveis(&contvar);
         return;
        }

     titulo[0] = ' ';
     titulo[1] = 0;
     strcat(titulo,nomerelat);
     visual->titulo  = titulo;
     visual->flags   = FALSE;
     visual->refcol  = 0;
     visual->pos_ini = visual->lido = 0;
    }

/*****************************************************************************
                              CARREGA TELA DE FUNDO
*****************************************************************************/
 if (!VIDEO_CRG_carrega_objeto(telavisual,1))
    {
     char buffer[100];
     sprintf(buffer,VIDEO_VISUAL_mens_carga_tela_apr,
                    telavisual->sistcrg,telavisual->telacrg);
     VIDEO_mostra_mens_erro(buffer,TRUE);
     if (visual->linhaaux)
         VIDEO_FREE_ALLOC_MEM(visual->linhaaux);
     VIDEO_FREE_ALLOC_MEM(visual);
     disable();
     --flagvisual;
     enable();
     VIDEO_VISUAL_restaura_variaveis(&contvar);
     return;
    }


 strcpy(VD_GETEND(BDISP_texto3,char),VIDEO_VISUAL_modo_visual);
 if (!VIDEO_CRG_prepara_tela(telavisual))
    {
     char buffer[100];
     sprintf(buffer,VIDEO_VISUAL_mens_prep_tela_apr,
                    telavisual->sistcrg,telavisual->telacrg);
     VIDEO_mostra_mens_erro(buffer,TRUE);
     VIDEO_CRG_libera_tela(telavisual);
     if (visual->linhaaux)
         VIDEO_FREE_ALLOC_MEM(visual->linhaaux);
     VIDEO_FREE_ALLOC_MEM(visual);
     VIDEO_VISUAL_restaura_variaveis(&contvar);
     disable();
     --flagvisual;
     enable();
     return;
    }

/*****************************************************************************
                            PREPARA TELA DE FUNDO
*****************************************************************************/
  strtelacrg         = PTR_CAST(VIDEO_TABCRGTELA,telavisual->strtelacrg);
  telaedit           = strtelacrg->telasai;
  telaedit->flagtela = VIDEO_TELA_SALVATELA;
  imagem             = strtelacrg->telasai->imagens;
  imagem->flagimagem = VIDEO_TELA_DISPIMAGEM;

  if (!flagtipo)
      imagem->flagimagem |= VIDEO_TELA_DISPCAMPOS;

  VIDEO_NUCLEO_servidor_mspas(strtelacrg->nutelasai);

  if (!flagtipo)
     {
      VIDEO_setatrib(imagem->coli, imagem->colf,
                     imagem->linf, imagem->linf,
                     VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));

      VIDEO_setatrib(imagem->coli, imagem->colf-15,
                     imagem->linf, imagem->linf,
                     VD_FORMATO(VD_VERMELHO,VD_INTER,VD_BLANK,VD_BRIL));
     }


/*****************************************************************************
							  INICIALIZA COORDENADAS
*****************************************************************************/
 visual->coli           = imagem->coli+1;
 visual->colf           = imagem->colf-1;
 visual->lini           = imagem->lini+1;
 visual->linf           = imagem->linf-4;

 if (!flagtipo)
     visual->numlin = visual->linf - visual->lini + 2;
    else
      visual->linf += 2;


 visual->lintela        = visual->lini;
 visual->linvisual      = 0;
 visual->refcol         = 0;
 visual->visual_opcoes	= visualaux;
 visual->accept_visual  = VIDEO_VISUAL_accept_visual;
 visual->telavisual     = telavisual;

 visual->flags |= (VIDEO_VISUAL_DISPLAY_PROMPT|VIDEO_VISUAL_SALVA_FUNDO|
                   VIDEO_VISUAL_DISPLAY_PAGINA);

 if (flagtipo)
     VD_tprt_l(visual->coli+2,visual->lini-1,visual->titulo,0);
 --visual->numlin;

/*****************************************************************************
                           LIBERA TELA DE FUNDO
*****************************************************************************/
 VIDEO_CRG_libera_tela(telavisual);

/*****************************************************************************
                        CARREGA ARQUIVO OU DISPLAY MENU
*****************************************************************************/
 if (!flagtipo)
    {
     char buffer[100];
	 int  col;
     vtclose();
     vtclose();
     vtclose();

	 VIDEO_VISUAL_flag_erro = FALSE;
     VIDEO_VISUAL_flag_int  = TRUE;
	 VIDEO_VISUAL_velha_int24 = getvect(0X24);
     setvect(0X24,VIDEO_VISUAL_nova_int24);

     if (!nomevisual)
		{
         if (!VISUAL_menu_arquivos(nomearq))
			{
			 VD_POPWIN();
			 VIDEO_FREE_ALLOC_MEM(visual->linhaaux);
			 VIDEO_FREE_ALLOC_MEM(visual);
             disable();
             --flagvisual;
             enable();
             setvect(0X24,VIDEO_VISUAL_velha_int24);
             VIDEO_VISUAL_restaura_variaveis(&contvar);
			 return;
			}
        }
      else
         strcpy(nomearq,nomevisual);

     nomevisual = nomearq;
     VIDEO_VISUAL_flag_int  = FALSE;
	 if ((desc = VIDEO_open_io(nomevisual)) < 0 ||
		  VIDEO_VISUAL_flag_erro)
        {
         char bufaux[100];
         setvect(0X24,VIDEO_VISUAL_velha_int24);
         sprintf(bufaux,VIDEO_VISUAL_mens_arquivo_visual,nomevisual);
         VIDEO_mostra_mens_erro(bufaux,TRUE);
         VD_POPWIN();
         VIDEO_FREE_ALLOC_MEM(visual->linhaaux);
         VIDEO_FREE_ALLOC_MEM(visual);
         VIDEO_VISUAL_restaura_variaveis(&contvar);
         disable();
         --flagvisual;
         enable();
         return;
        }

     if (VIDEO_lockfile(desc,0L,VIDEO_filelength(desc)) < 0 ||
		 VIDEO_VISUAL_flag_erro)
        {
         char bufaux[100];
         setvect(0X24,VIDEO_VISUAL_velha_int24);
         sprintf(bufaux,VIDEO_VISUAL_mens_arquivo_visual,nomevisual);
         VIDEO_mostra_mens_erro(bufaux,TRUE);
         VD_POPWIN();
         VIDEO_FREE_ALLOC_MEM(visual->linhaaux);
         VIDEO_FREE_ALLOC_MEM(visual);
         VIDEO_close(desc);
         VIDEO_VISUAL_restaura_variaveis(&contvar);
         disable();
         --flagvisual;
         enable();
         return;
        }

     visual->desc = desc;

     strcpy(buffer,titulo);
     strcat(buffer,nomevisual);
     strcat(buffer," ");

     col = (((visual->colf+1)-(visual->coli-1)+1) - strlen(buffer))/2;
	 if (col < 0)
		{
         buffer[((visual->colf+1)-(visual->coli-1))] = 0;
		 col = 0;
		}
     col += (visual->coli-1);
     VD_tprt_l(col,visual->linf+2,buffer,0);
     VIDEO_VISUAL_flag_int  = TRUE;
    }

/*****************************************************************************
                               PREPARA NUCLEO
*****************************************************************************/
 nucleo.VIDEO_campos    = PTR_CAST(VIDEO_TAB_FUNC,visual);
 nucleo.VIDEO_numcampos = 1;
 nucleo.VIDEO_tamcampo  = sizeof(VIDEO_VISUAL_CONTROLE);
 nucleo.VIDEO_inicial	= 0;
 nucleo.VIDEO_tabserv   = VIDEO_VISUAL_tabserv_navegacao;
 nucleo.VIDEO_servrec   = FALSE;
 nucleo.VIDEO_repdisp   = FALSE;


/*****************************************************************************
                                INDEXA ARQUIVO TEXTO
*****************************************************************************/
 if (!flagtipo && (visual->arqtmp = VIDEO_VISAO_indexa_texto(visual)) == VD_NULO)
	{
	 char bufaux[100];
     setvect(0X24,VIDEO_VISUAL_velha_int24);
     sprintf(bufaux,VIDEO_VISUAL_mens_arquivo_visual,nomevisual);
	 VIDEO_mostra_mens_erro(bufaux,TRUE);
	 VD_POPWIN();
	 VIDEO_FREE_ALLOC_MEM(visual->linhaaux);
	 VIDEO_FREE_ALLOC_MEM(visual);

     setvect(0X24,VIDEO_VISUAL_nova_int24);
     VIDEO_VISUAL_flag_int  = FALSE;

     if (VIDEO_unlockfile(desc,0L,VIDEO_filelength(desc)) < 0)
		{
         sprintf(bufaux,VIDEO_VISUAL_mens_arquivo_visual,nomevisual);
         VIDEO_mostra_mens_erro(bufaux,TRUE);
		}

     VIDEO_close(desc);
     disable();
     --flagvisual;
     enable();
     setvect(0X24,VIDEO_VISUAL_velha_int24);
     VIDEO_VISUAL_restaura_variaveis(&contvar);
	 return;
	}

 visual->pos_ini = 0L;

 if (!flagtipo && (visual->numlin > visual->lido))
     visual->numlin = visual->lido;

 if (!flagtipo)
    {
     VIDEO_VISUAL_carrega_pagina(visual,-1);
     visual->pos_ini = 0L;
     visual->nomevisual = nomevisual;
     VIDEO_VISUAL_mostra_linha_scrow(visual);
    }

/*****************************************************************************
                           CHAMA NUCLEO VISUALIZACAO
*****************************************************************************/
 if (flagimpressao)
	 VIDEO_VISUAL_impressao_arquivo(visual);
   else
	 VIDEO_NUCLEO_servidor_mspas(&nucleo);

 if (visual->linhaaux)
    {
     VIDEO_VISUAL_flag_int  = FALSE;

     if (visual->desc > 0)
        {
         if (VIDEO_unlockfile(visual->desc,0L,VIDEO_filelength(visual->desc)) < 0
            || VIDEO_VISUAL_flag_erro)
            {
             char buffer[100];
             sprintf(buffer,VIDEO_VISUAL_mens_arquivo_visual,nomevisual);
             VIDEO_mostra_mens_erro(buffer,TRUE);
            }

         VIDEO_close(visual->desc);
        }

     if (visual->descindex > 0)
        {
         VIDEO_close(visual->descindex);
         VIDEO_unlink(visual->arqtmp);
         VIDEO_FREE_ALLOC_MEM(visual->arqtmp);
        }

     VIDEO_FREE_ALLOC_MEM(visual->linhaaux);
     setvect(0X24,VIDEO_VISUAL_velha_int24);
    }

 VIDEO_FREE_ALLOC_MEM(visual);

 VD_POPWIN();

 VIDEO_VISUAL_restaura_variaveis(&contvar);

 --flagvisual;

#ifdef VIDEO_UNIX
 VIDEO_UNIX_refresh_tela();
#endif
}

INT2 VIDEO_VISUAL_salva_variaveis(buffer)
char **buffer;
{
 char *bufaloc;

 if (VIDEO_ALLOC_MEM(*buffer,36*3+sizeof(DWORD)*5+sizeof(BYTE)*2) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUAL_5);
     return(FALSE);
    }

 bufaloc = *buffer;
 VIDEO_movbloco(bufaloc,VD_GETEND(BDISP_texto1,char),36);

 bufaloc += 36;
 VIDEO_movbloco(bufaloc,VD_GETEND(BDISP_texto2,char),36);

 bufaloc += 36;
 VIDEO_movbloco(bufaloc,VD_GETEND(BDISP_texto3,char),36);

 bufaloc += 36;
 VIDEO_movbloco(bufaloc,VD_GETEND(BREL_selec1,char),sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(bufaloc,VD_GETEND(BREL_selec2,char),sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(bufaloc,VD_GETEND(BREL_selec3,char),sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(bufaloc,VD_GETEND(BREL_selec4,char),sizeof(BYTE));

 bufaloc += 1;
 VIDEO_movbloco(bufaloc,VD_GETEND(BREL_selec6,char),sizeof(BYTE));

 bufaloc += 1;
 VIDEO_movbloco(bufaloc,VD_GETEND(BREL_selec7,char),sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(bufaloc,VD_GETEND(BREL_selec8,char),sizeof(DWORD));

 // Alterado Rog‚rio
 // VD_GETBUF(BREL_selec6,BYTE) = 66;
 VD_GETBUF(BREL_selec6,BYTE) = B(VD_GETBUF("DISP_pag",WORD)-1);

 VD_GETBUF(BREL_selec7,WORD) = 1;

 VD_GETBUF(BREL_selec8,WORD) = 999;

 VD_GETBUF(BREL_selec1,DWORD) = 1;

 VD_GETBUF(BREL_selec2,char)  = 'S';

 VD_GETBUF(BREL_selec3,char)  = 'P';
 
 return(TRUE);
}

VD_VOID VIDEO_VISUAL_restaura_variaveis(buffer)
char **buffer;
{
 char *bufaloc;

 bufaloc = *buffer;
 VIDEO_movbloco(VD_GETEND(BDISP_texto1,char),bufaloc,36);

 bufaloc += 36;
 VIDEO_movbloco(VD_GETEND(BDISP_texto2,char),bufaloc,36);

 bufaloc += 36;
 VIDEO_movbloco(VD_GETEND(BDISP_texto3,char),bufaloc,36);

 bufaloc += 36;
 VIDEO_movbloco(VD_GETEND(BREL_selec1,char) ,bufaloc,sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(VD_GETEND(BREL_selec2,char) ,bufaloc,sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(VD_GETEND(BREL_selec3,char) ,bufaloc,sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(VD_GETEND(BREL_selec4,char) ,bufaloc,sizeof(BYTE));

 bufaloc += 1;
 VIDEO_movbloco(VD_GETEND(BREL_selec6,char),bufaloc,sizeof(BYTE));

 bufaloc += 1;
 VIDEO_movbloco(VD_GETEND(BREL_selec7,char),bufaloc,sizeof(DWORD));

 bufaloc += 4;
 VIDEO_movbloco(VD_GETEND(BREL_selec8,char),bufaloc,sizeof(DWORD));

 VIDEO_FREE_ALLOC_MEM(*buffer);
}

VD_VOID VIDEO_VISUAL_mostra_linha_scrow(visual)
VIDEO_VISUAL_CONTROLE *visual;
{
 DWORD  linatual,numlin,col,
        lin,colatual,numcol;
 char buffer[50];


 VIDEO_horizontal(visual->coli+1,visual->colf-1,visual->linf+1,
                  VIDEO_ARVORE_CARACBAR,
                  VD_FORMATO(VD_AZULTURQ,VD_NORMAL, VD_BLANK,   VD_NORMAL));

 VIDEO_vertical(visual->lini+1,visual->linf-1,visual->colf+1,
                VIDEO_ARVORE_CARACBAR,
                VD_FORMATO(VD_AZULTURQ,VD_NORMAL, VD_BLANK,   VD_NORMAL));

 linatual = visual->pos_ini + visual->linvisual;

 numlin   = visual->linf-visual->lini+1-2;
 if ((lin = I(D(D(linatual) * D(numlin) / D(visual->lido)))
               -1 + visual->lini+1) < (visual->lini+1))
     lin = (visual->lini+1);
   else
     if (lin > (visual->linf-1))
         lin = (visual->linf-1);

 if (!linatual)
     lin = (visual->lini+1);

 if (++linatual == visual->lido)
     lin = (visual->linf-1);

 VIDEO_plotcarac(visual->colf+1,lin,
                 VIDEO_ARVORE_CARACSCROW,
                 VD_FORMATO(VD_VERMELHO, VD_NORMAL, VD_VERMELHO,VD_NORMAL));

 colatual = visual->refcol;
 numcol   = visual->colf-visual->coli+1-2;
 if ((col = I(D(D(colatual) * D(numcol) / D(VIDEO_VISUAL_MAX_COL))) -1 + visual->coli+1)
              < (visual->coli+1))
     col = (visual->coli+1);
   else
     if (col > (visual->colf-1))
         col = (visual->linf-1);

 if (!colatual)
     col = (visual->coli+1);

 if (colatual >= (VIDEO_VISUAL_MAX_COL-1))
     col = (visual->colf-1);

 VIDEO_plotcarac(col,visual->linf+1,VIDEO_ARVORE_CARACSCROW,
                 VD_FORMATO(VD_VERMELHO, VD_NORMAL, VD_VERMELHO,VD_NORMAL));

 sprintf(buffer,"%4ld/%ld",L(linatual+I(VD_GETBUF(BREL_selec6,BYTE) - 1))/
                           L(VD_GETBUF(BREL_selec6,BYTE)),
                           L(visual->lido+I(VD_GETBUF(BREL_selec6,BYTE))-1)/
                           L(VD_GETBUF(BREL_selec6,BYTE)));
 VD_tprt_l(visual->colf-30,visual->lini-1,buffer,0);

 if ((lin = linatual%L(VD_GETBUF(BREL_selec6,BYTE))) == 0)
    lin = VD_GETBUF(BREL_selec6,BYTE);

 sprintf(buffer,"%2d",lin);
 VD_tprt_l(visual->colf-10,visual->lini-1,buffer,0);
}
