#include <INCVIDEO.H>

INT2 VIDEO_TELA_display_imagem(VIDEO_TELA_ENTRADA_DADOS *tela);

INT2 VIDEO_TELA_accept_tela_1(VIDEO_TELA_ENTRADA_DADOS **telanucleo,
                              VIDEO_NUCLEO_SERV        **nucleo);
INT2 VIDEO_TELA_accept_tela_2(VIDEO_TELA_ENTRADA_DADOS **telanucleo,
                              VIDEO_NUCLEO_SERV        **nucleo);


INT2 VIDEO_TELA_monta_subfile(VIDEO_IMAGEMTELA *imagem,
                             INT2              flagseg,
                             VIDEO_TELA_ENTRADA_DADOS *telaedit);

INT2 VIDEO_TELA_accept_tela(telaedit,param)
VIDEO_TELA_ENTRADA_DADOS *telaedit;
VIDEO_NUCLEO_SERV        *param;
{
 VIDEO_TELA_accept_tela_1(&telaedit,&param);
 VIDEO_TELA_accept_tela_2(&telaedit,&param);

 return(TRUE);
}

INT2 VIDEO_TELA_accept_tela_1(telanucleo,nucleo)
VIDEO_TELA_ENTRADA_DADOS **telanucleo;
VIDEO_NUCLEO_SERV        **nucleo;
{
 VIDEO_TELA_ENTRADA_DADOS *telaedit;
 VIDEO_NUCLEO_SERV        *param;
 VIDEO_IMAGEMTELA         *imagem,*imagteste;
 INT2                     ret,cont;
 VIDEO_TABFUNCAO          *tabfuncuser;

 telaedit = *telanucleo;
 param    = *nucleo;

 VD_tcursor(0X20,0X20);

 VIDEO_imagem_atual = telaedit->imagem_ativa = imagem =
                      telaedit->imagens+telaedit->imagem_accept;

 if (imagem->transpdados)
     CTREE_cpydoda(imagem->transpdados);

 /* Localiza User FUNCTION (Se Alguma).*/
 if (imagem->userfunc)
    tabfuncuser = VIDEO_funcao_tabfuncuser(imagem->userfunc);

 /* Seta a linha de para esta Imagem mensagem.*/

 if (imagem->nmindsub)
    {
     INT2 flagseg;

     flagseg = 1;

     if (imagem->flagimagem&VIDEO_TELA_STATSUBFILE)
        flagseg = VIDEO_TELA_testa_segconst_sub(imagem);

     if (flagseg)
        {
         if (!VIDEO_TELA_monta_subfile(imagem,flagseg,telaedit))
            {
             if (!telaedit->imagem_accept)
                 param->VIDEO_servrec =  VD_MTTECLA(ESCAPE,ESCAPE);
              else
                {
                 imagem->seqdisp = 0;
                 param->VIDEO_servrec =  VD_MTTECLA(VD_NULO,ALT_R);
                }
             return(TRUE);
            }
         imagem->flagimagem |= VIDEO_TELA_INICIMAGEM;
        }
     imagem->indarq  = CTREE_keynm(imagem->nmindsub);
    }
  else
    imagem->indarq  = CTREE_keynm(imagem->nmindarq);

 imagem->arquivo = CTREE_keyfil(imagem->indarq);

 if (imagem->transpdados)
     CTREE_cpydoda(imagem->transpdados);

 if (imagem->flagimagem&VIDEO_TELA_INICIMAGEM && imagem->tipotela>1 &&
    imagem->tipotela < 6)
    {
	 if ((ret = CTREE_inbuf(imagem->arquivo)) != FALSE)
        {
         char buffer[200];
		 sprintf(buffer,CTREE_MENS_mens_padrao_err,
						VIDEO_mens_reg_nao_enc,
						(VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
						ret,isam_err);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_inic_buffer_tela);

         param->VIDEO_servrec = VD_MTTECLA(ESCAPE,ESCAPE);
         return(FALSE);
        }
     imagem->flagimagem &= ~VIDEO_TELA_INICIMAGEM;
    }

 if (imagem->transpdados)
     CTREE_cpydoda(imagem->transpdados);

 if (imagem->flagimagem&VIDEO_TELA_FDISPANT && imagem->userfunc )
     if (!tabfuncuser || !tabfuncuser->userfunc)
		{
         char buffer[200];
         sprintf(buffer,VIDEO_funcao_nao_enc,imagem->userfunc);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_nao_encontrada);
		}
	  else
/*
        (tabfuncuser->userfunc)(&imagem,VIDEO_TELA_FDISPANT,&param);
*/
        if ((tabfuncuser->userfunc)(&imagem,VIDEO_TELA_FDISPANT,&param))
           imagem->flagimagem |= VIDEO_TELA_DISPCAMPOS;

 param->VIDEO_servrec = VD_MTTECLA(ESCAPE,ESCAPE);

 if (telaedit->flagtela&VIDEO_TELA_SALVATELA)
    {
     if (telaedit->num_imagens > 1)
         VD_PUSHWIN( 1,80, 1,25);
      else
         VD_PUSHWIN(imagem->coli,
                    imagem->colf<VIDEO_MAXCOL && imagem->sombra ?
                                   imagem->colf+1 : imagem->colf,
                    imagem->lini,
                    imagem->linf<VIDEO_MAXLIN && imagem->sombra ?
                                    imagem->linf+1 : imagem->linf);
     telaedit->flagtela &= ~VIDEO_TELA_SALVATELA;
    }

 VIDEO_mensagem_default.lin = imagem->linf-1 == imagem->lini ?
                              imagem->linf : imagem->linf-1;
 VIDEO_mensagem_default.col = imagem->coli+1;

 if (imagem->flagimagem&VIDEO_TELA_DISPIMAGEM)
    {
     imagem->flagimagem &= ~VIDEO_TELA_DISPIMAGEM;
     imagem->seqdisp = ++telaedit->seqdisp;

     if (!VIDEO_TELA_display_imagem(telaedit))
        return(FALSE);

     if (imagem->linf-1 != imagem->lini)
        {
         if( imagem->colf<VIDEO_MAXCOL && imagem->sombra )
            VIDEO_setatrib(imagem->colf+1, imagem->colf+1,
                           imagem->lini+1, imagem->linf+1,
                           imagem->sombra);

         /* Mostra Sombra Horizontal.*/
         if( imagem->linf<VIDEO_MAXLIN && imagem->sombra )
            VIDEO_setatrib(imagem->coli+1, imagem->colf,
                           imagem->linf+1, imagem->linf+1,
                           imagem->sombra);

         if (imagem->tipotela < 6)
            {
             if (imagem->tipotela < 5)
                 if (imagem->tipotela > 1)
                    {
                     VD_tprt_l(imagem->colf-10,imagem->linf,VIDEO_texto_salva,
                                      VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
                     VD_plotcarac(imagem->colf-10,imagem->linf,'S',
                                     VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
                     VD_tprt_l   (imagem->coli+21,imagem->linf,VIDEO_texto_exclusao,
                                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK ,VD_BRIL));
                     VD_plotcarac(imagem->coli+20,imagem->linf,'E',
                                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));

                     if (imagem->flagimagem&VIDEO_TELA_STATUS)
                        {
                         VD_tprt_l(imagem->coli,imagem->linf,VIDEO_texto_inclusao,
                                             VD_FORMATO(VD_VERDE,VD_NORMAL,VD_BLANK,VD_BRIL));
                         VD_plotcarac(imagem->coli,imagem->linf,'I',
                                          VD_FORMATO(VD_VERDE,VD_NORMAL,VD_MARROM,VD_NORMAL));
                         VD_tprt_l(imagem->coli+10,imagem->linf,VIDEO_texto_atualiza,
                                          VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
                        }
                      else
                        {
                         VD_tprt_l(imagem->coli,imagem->linf,VIDEO_texto_inclusao,
                                                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
                         VD_plotcarac(imagem->coli,imagem->linf,'I',
                                                 VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
                         VD_tprt_l(imagem->coli+10,imagem->linf,VIDEO_texto_atualiza,
                                                     VD_FORMATO(VD_VERDE,VD_NORMAL,VD_BLANK,VD_BRIL));
                        }
                    }

             if ((imagem->tipotela == 0) || (imagem->tipotela == 1))
                {
                 VD_tprt_l(imagem->colf-11,imagem->linf,VIDEO_texto_ok,
                                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
                 VD_plotcarac(imagem->colf-9,imagem->linf,'O',
                                 VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
                }

             if ((imagem->tipotela == 3) || (imagem->tipotela == 4))
                {
                 VD_tprt_l(imagem->colf-17,imagem->linf,VIDEO_texto_ok,
                                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
                 VD_plotcarac(imagem->colf-15,imagem->linf,'O',
                                 VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
                }
            }

         if (imagem->tipotela < 8)
            {
             VD_tprt_l(imagem->colf-5,imagem->lini,VIDEO_TELA_bottom_termina,
                 VIDEO_pega_atributo(imagem->colf-5,imagem->lini));
             VD_plotcarac(imagem->colf-3,imagem->lini,'þ',
                 VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
            }
        }

     imagem->flagimagem &= ~VIDEO_TELA_FLAGALTERSUB;
    }

 param->VIDEO_servrec = FALSE;

 if (imagem->flagimagem&VIDEO_TELA_DISPCAMPOS)
    {
     VIDEO_TELA_display_campos(PTR_CAST(VIDEO_CAMPO_TELA,
                 imagem->campos->VIDEO_campos),
                 imagem->campos->VIDEO_numcampos,
                 imagem->campos, VIDEO_FLAGVALIDA_CAMPO |
                                 VIDEO_FLAGUSER_CAMPO   |
                                 VIDEO_FLAGOFFSET_CAMPO |
                                 (imagem->flagimagem&VIDEO_TELA_FLAGRESETDISPLAY)
                                 );
     imagem->flagimagem &= ~(VIDEO_TELA_DISPCAMPOS|VIDEO_TELA_FLAGRESETDISPLAY);
    }

 for (cont = 0,imagteste = telaedit->imagens;
      !(imagem->flagimagem&VIDEO_TELA_FLAGALTERSUB) &&
      cont < telaedit->num_imagens;cont++,imagteste++)
      if (imagteste->segsub && (imagteste->flagimagem&VIDEO_TELA_FLAGREGALT))
          {
          VD_plotcarac(imagem->colf-7,imagem->lini,'',
          VIDEO_INTER|VIDEO_pega_atributo(imagem->colf-7,imagem->lini));
          imagem->flagimagem |= VIDEO_TELA_FLAGALTERSUB;
          break;
         }

 if (imagem->flagimagem&VIDEO_TELA_ACCEPTCAMPOS)
    {
     if (imagem->campos)
        {
         if (((param->VIDEO_servrec =
                     VIDEO_NUCLEO_servidor_mspas(imagem->campos)) ==
               I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK))) ||
              (param->VIDEO_servrec == I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV))))
             VIDEO_TELA_mouse_posiciona(&telaedit,&param);
        }
      else
        {
         param->VIDEO_servrec = VIDEO_MTTECLA(VD_NULO,ALT_R);
         imagem->seqdisp = 0;
        }
    }
  else
     param->VIDEO_servrec = VIDEO_MTTECLA(ESCAPE  ,ESCAPESCAN);

 return(TRUE);
}


INT2 VIDEO_TELA_accept_tela_2(telanucleo,nucleo)
VIDEO_TELA_ENTRADA_DADOS **telanucleo;
VIDEO_NUCLEO_SERV        **nucleo;
{
 VIDEO_TELA_ENTRADA_DADOS *telaedit;
 VIDEO_NUCLEO_SERV        *param;
 VIDEO_IMAGEMTELA         *imagem,*imagteste;
 INT2                     ret,cont;
 VIDEO_TABFUNCAO          *tabfuncuser;

 telaedit = *telanucleo;
 param    = *nucleo;

 VD_tcursor(0X20,0X20);

 telaedit->imagem_ativa = imagem =
                       telaedit->imagens+telaedit->imagem_accept;

 if (imagem->userfunc)
    tabfuncuser = VIDEO_funcao_tabfuncuser(imagem->userfunc);

 if (imagem->flagimagem&VIDEO_TELA_FDISPPOS && imagem->userfunc )
	 if (!tabfuncuser || !tabfuncuser->userfunc)
		{
         char buffer[200];
         sprintf(buffer,VIDEO_funcao_nao_enc,imagem->userfunc);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_nao_encontrada);
		}
	  else
/*
        (tabfuncuser->userfunc)(&imagem,VIDEO_TELA_FDISPPOS,&param);
*/
        if((tabfuncuser->userfunc)(&imagem,VIDEO_TELA_FDISPPOS,&param))
          imagem->flagimagem |= VIDEO_TELA_DISPCAMPOS;

 if (imagem->transpdados)
     CTREE_cpydoda(imagem->transpdados);

 VD_tcursor(0X20,0X20);

 return(TRUE);
}

INT2 VIDEO_TELA_monta_subfile(imagem,flagseg,telaedit)
VIDEO_IMAGEMTELA         *imagem;
INT2                      flagseg;
VIDEO_TELA_ENTRADA_DADOS *telaedit;
{
 INT2            tam ,numseg,numconst,
                 cont,ret   ,
                 flagconst  ;
 char            buffer[100],
                 *pointer   ;
 VIDEO_SEG_CHAVE *seg,*segaux;
 IDE_DODA        *doda;
 IDE_ARQUIVOS    *ifilarq;

 tam     = CTREE_keynm(imagem->nmindsub);
 tam     = CTREE_keyfil(tam);
 ifilarq = CTREE_ifilend(tam);

 seg = imagem->segchave;
 numconst = flagconst = numseg = 0;

 while(seg->pointer)
  {
   if (seg->tipo != CT_SEG_CAMPO)
      {
       flagconst = FALSE;
       if (seg->tipo == CT_SEG_CAMPO_CONST)
          {
           if ((doda = CTREE_dodaend(seg->pointer)) == VD_NULO)
              {
               sprintf(buffer,VIDEO_TELA_mens_doda,seg->pointer);
			   VIDEO_mostra_mens_erro(buffer,
									  VIDEO_ERRO_doda_tela_nao_encontrado);
               return(FALSE);
              }
           pointer = doda->fadr;
          }
        else
          pointer = seg->pointer;

       tam = seg->tamanho;
       if (!flagconst)
           do
            {
             if (*pointer++)
                {
                 flagconst = TRUE;
                 break;
                }
            }while(--tam);
       ++numconst;
      }
   ++numseg;
   ++seg;
  }

 if (!numconst)
    {
	 VIDEO_mostra_mens_erro(VIDEO_TELA_mens_sub_segconst,
							VIDEO_ERRO_segconst_tela_nao_def);
     return(FALSE);
    }

 if (!flagconst)
    {
     VIDEO_mostra_mens_erro(imagem->mensagem,TRUE);
     return(FALSE);
    }

 if (flagseg > 1)
     VIDEO_TELA_libera_subfile(telaedit,TRUE);

 if ((ret = CTREE_temp(ifilarq)) != FALSE)
    {
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
					VIDEO_TELA_mens_cria_tmp,
					(VIDEO_bufparamarq->bufdodas+ifilarq->dfilno)->reduzido,
					ret,isam_err);
	 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_cria_tmp_tela);
     return(FALSE);
    }

 ++numseg;
 if (VIDEO_ALLOC_MEM(imagem->segsub,
                     sizeof(VIDEO_SEG_CHAVE)*numseg) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELA_1_CRIA_SUBF);
     CTREE_deltmp(ifilarq->dfilno);
     return(FALSE);
    }

 segaux = imagem->segsub;
 seg = imagem->segchave;
 VIDEO_movbloco(segaux,seg,sizeof(VIDEO_SEG_CHAVE)*numseg);

 while(seg->pointer)
  {
   if (seg->tipo != CT_SEG_CAMPO)
      {
       if (VIDEO_ALLOC_MEM(segaux->pointer,seg->tamanho) == VD_NULO)
          {
           VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELA_2_CRIA_SUBF);
           segaux->pointer = VIDEO_NILL(char);
           segaux = imagem->segsub;
           while(segaux->pointer)
            {
             if (segaux->tipo == CT_SEG_CONST)
                 VIDEO_FREE_ALLOC_MEM(segaux->pointer);
             ++segaux;
            }
           VIDEO_FREE_ALLOC_MEM(imagem->segsub);
           imagem->segsub = VD_NULO;
           CTREE_deltmp(ifilarq->dfilno);
           return(FALSE);
          }

       if (seg->tipo == CT_SEG_CONST)
           VIDEO_movbloco(segaux->pointer,seg->pointer,seg->tamanho);
         else
           VIDEO_movbloco(segaux->pointer,
                          CTREE_dodaend(seg->pointer)->fadr,seg->tamanho);
       segaux->tipo    = CT_SEG_CONST;
       segaux->tamanho = seg->tamanho;
      }
    else
      segaux->pointer = seg->pointer;

   ++segaux;
   ++seg;
  }

 strcpy(buffer,VIDEO_CONF_PROCESSA_SUBFILE);
 sprintf(&buffer[strlen(buffer)]," [%s] [ ]",(imagem->ident) ? imagem->ident  :
                                          " TELA");
 VD_telprocessa(buffer,VIDEO_COR_EXC_REGISTRO);

 if ((ret = CTREE_copy(CTREE_keynm(imagem->nmindsub),
            CTREE_keynm(imagem->nmindarq),
            imagem->segsub,FALSE,VIDEO_cont_proc_tela)) != 101)
    {
	 sprintf(buffer,CTREE_MENS_mens_padrao_err,
					VIDEO_TELA_mens_copysub,
					(VIDEO_bufparamarq->bufdodas+CTREE_keyfil(CTREE_keynm(imagem->nmindarq)))->reduzido,
					ret,isam_err);
	 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_copy_arq_sub_act);
     segaux = imagem->segsub;
     while(segaux->pointer)
      {
       if (segaux->tipo == CT_SEG_CONST)
           VIDEO_FREE_ALLOC_MEM(segaux->pointer);
       ++segaux;
      }
     VIDEO_FREE_ALLOC_MEM(imagem->segsub);

     CTREE_deltmp(ifilarq->dfilno);
     imagem->segsub = VD_NULO;

     VD_POPWIN();
     return(FALSE);
    }

 VD_POPWIN();
 imagem->flagimagem |= (VIDEO_TELA_STATSUBFILE |
                        VIDEO_TELA_STATUS      |
                        VIDEO_TELA_DISPCAMPOS  |
                        VIDEO_TELA_DISPIMAGEM  );

 imagem->flagimagem &= ~VIDEO_TELA_FLAGREGALT;


 return(TRUE);
}

/*
display(segchave)
VIDEO_SEG_CHAVE *segchave;
{
 IDE_DODA *doda;
 char     bftipo[10],
          buffer[50];

 VD_PUSHWIN(1,80,1,25);
 VD_gtxy(1,1);
 while(segchave->pointer)
  {
   printf("%20s %d %d ",segchave->pointer,segchave->tipo,segchave->tamanho);
   doda = CTREE_dodaend(segchave->pointer);
   switch(doda->ftype)
    {
     case CT_BOOL  : 
     case CT_CHAR  :
     case CT_CHARU :printf("%c ",W(CCHAR(doda->fadr)));
                    break;

     case CT_INT2  :printf("%5d",CINT(doda->fadr));
                    break;

     case CT_INT2U :printf("%5u",CWORD(doda->fadr));
                    break;

     case CT_INT4  :printf("%12ld",CLONG(doda->fadr));
                    break;

     case CT_INT4U :printf("%12lu",CDWORD(doda->fadr));
                    break;

     case CT_SFLOAT:printf("%8f",CFLOAT(doda->fadr));
                    break;

     case CT_DFLOAT:printf("%16u",CDOUBLE(doda->fadr));
                    break;

     case 0        :printf("%s",doda->fadr);
                    break;

    }
   printf("\n");
   ++segchave;
  }
 getch();
 VD_POPWIN();
}
*/

INT2 VIDEO_TELA_display_imagem(tela)
VIDEO_TELA_ENTRADA_DADOS *tela;
{
 VIDEO_ESTMANUT   imagem;
 VIDEO_IMAGEMTELA *imagem_disp;
 int            ret;

 imagem.sistcrg = tela->tela->sistcrg;
 imagem.telacrg = tela->tela->telacrg;

 if (!VIDEO_CRG_carrega_objeto(&imagem,tela->imagem_accept+100))
    {
     char buffer[200],bufaux[100];
     sprintf(buffer,VIDEO_TELA_mens_carga_imagem,
                     CDWORD(&imagem.telacrg) > 1000L ? imagem.telacrg :
                     ltoa(CDWORD(&imagem.telacrg),bufaux,10),imagem.sistcrg,
					 isam_err);
	 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_display_imagem_fundo);
     return(FALSE);
    }

 imagem_disp = tela->imagens+tela->imagem_accept;

 if (VIDEO_tabela_cor_de_frente && VIDEO_tabela_cor_de_fundo)
    {
     char *buffer;
     INT2  cont_lin,numlins ,
          tamanho ,cont_pos;

     buffer = imagem.strtelacrg;

     for (cont_lin = 0,numlins = imagem_disp->linf-imagem_disp->lini+1;
                       cont_lin < numlins;cont_lin++)
         for (cont_pos = 1,tamanho = (imagem_disp->colf-imagem_disp->coli+1)*2;
                       cont_pos <  tamanho;cont_pos += 2)
              *(buffer+(cont_lin)*tamanho+cont_pos) =
                VIDEO_monta_cor(*(buffer+(cont_lin)*tamanho+cont_pos));
    }

 VIDEO_grvtela(imagem_disp->coli,imagem_disp->colf,
               imagem_disp->lini,imagem_disp->linf,imagem.strtelacrg);

 VIDEO_CRG_libera_tela(&imagem);
 return(TRUE);
}

