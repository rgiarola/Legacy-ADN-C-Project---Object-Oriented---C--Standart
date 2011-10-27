#include <INCVIDEO.H>

INT2 VIDEO_CRG_carrega_objeto(objeto,tipo)
VIDEO_ESTMANUT *objeto;
INT2            tipo;
{
#ifdef DATABASE_GRI
 VD_VOID         *strtelacrg;
 INT2             tamreg,indice,arquivo,
                 ret;
 char            buffer[200],
                 *bufreg;
 IDE_DODA        *doda;
 DWORD           posicao;

 ATIVA_BUF_DADOS;

 indice  = CTREE_keynm(VIDEO_CARGA_indice_carga);
 arquivo = CTREE_keyfil(indice);
 CTREE_inbuf(arquivo);

 strcpy(VD_GETEND(VIDEO_CARGA_CRG_objeto,char),objeto->telacrg);
 strcpy(VD_GETEND(VIDEO_CARGA_CRG_sistema,char),objeto->sistcrg);
 VD_GETBUF(VIDEO_CARGA_CRG_tipoobj,WORD) = tipo;

 bufreg = CTREE_filbuf(arquivo);

 if ((posicao = VIDEO_lseek(VIDEO_GRI_descidx,0L,VIDEO_INI_ARQ)) < 0L)
    {
     sprintf(buffer,"ERRO SEEK OBJETOS [%s] [%s] [%d] %ld",
                     CTREE_dodaend("CRG_objeto")->fadr,
                     CTREE_dodaend("CRG_sistema")->fadr,
                     CINT(CTREE_dodaend("CRG_tipoobj")->fadr),posicao);
     VIDEO_mostra_mens_erro(buffer,TRUE);
     return(FALSE);
    }

 do
  {
   if ((ret = VIDEO_read(VIDEO_GRI_descidx,bufreg,64)) < 64)
      {
       sprintf(buffer,"ERRO READ IDX OBJETOS [%s] [%s] [%d] %d",
                       CTREE_dodaend("CRG_objeto")->fadr,
                       CTREE_dodaend("CRG_sistema")->fadr,
                       CINT(CTREE_dodaend("CRG_tipoobj")->fadr),ret);
       VIDEO_mostra_mens_erro(buffer,TRUE);
       return(FALSE);
      }

   if (!strcmp(CTREE_dodaend("CRG_objeto")->fadr,objeto->telacrg)  &&
       !strcmp(CTREE_dodaend("CRG_sistema")->fadr,objeto->sistcrg) &&
       (VD_GETBUF("CRG_tipoobj",WORD) == 1))
      break;

  }while(TRUE);

 tamreg = VD_GETBUF("CRG_tamext",COUNT);

 if ((strtelacrg = VIDEO_alloc_parametros(tamreg)) == VD_NULO)
    {
     sprintf(buffer,"ERRO DE ALC MEM %d CRGCRT",tamreg);
     VIDEO_mostra_mens_erro(buffer,TRUE);
     return(FALSE);
    }

 if ((posicao = VIDEO_lseek(VIDEO_GRI_descdat,VD_GETBUF("CRG_null",DWORD),
                                    VIDEO_INI_ARQ)) < 0L)
    {
     sprintf(buffer,"ERRO SEEK DADOS OBJETOS [%s] [%s] [%d] %ld",
                     CTREE_dodaend("CRG_objeto")->fadr,
                     CTREE_dodaend("CRG_sistema")->fadr,
                     CINT(CTREE_dodaend("CRG_tipoobj")->fadr),posicao);
     VIDEO_mostra_mens_erro(buffer,TRUE);
     VIDEO_free_alloc_parametros(strtelacrg);
     return(FALSE);
    }

 if ((ret = VIDEO_read(VIDEO_GRI_descdat,strtelacrg,tamreg)) != tamreg)
    {
     sprintf(buffer,"ERRO READ EXT OBJETOS [%s] [%s] %d",
                     objeto->telacrg,objeto->sistcrg,ret);
     VIDEO_mostra_mens_erro(buffer,TRUE);
     VIDEO_free_alloc_parametros(strtelacrg);
     return(FALSE);
    }

 objeto->strtelacrg = strtelacrg;
 objeto->tela       = PTR_CAST(VIDEO_TABCRGTELA,strtelacrg)->telasai;
#else
 VD_VOID         *strtelacrg;
 WORD			 tamreg,indice,flag,
                 arquivo,ret,real_arquivo;
 char            buffer[200],nomeindice[21];
 IDE_DODA        *doda;
 VIDEO_SEG_CHAVE *seg;
 IDE_ARQUIVOS    *workifil;
 INT2             desc, tipoind;

 ATIVA_BUF_DADOS;
 //printf ("\n Entrou Aqui ..."); getch();

 desc = strlen(VIDEO_CARGA_indice_carga);
 strcpy(nomeindice,VIDEO_CARGA_indice_carga);

 if (CDWORD(&objeto->telacrg) < 1000L)
    {
     nomeindice[desc  ] = '_',
     nomeindice[desc+1] = '0',
     nomeindice[desc+2] = '1',
     nomeindice[desc+3] = '\0';
     tipoind = TRUE;
    }
  else
     tipoind = FALSE;

 indice  = CTREE_keynm(nomeindice);
 arquivo = CTREE_keyfil(indice);
 CTREE_inbuf(arquivo);

 if (tipoind)
     VD_GETBUF(VIDEO_CARGA_CRG_numobj,WORD) = W(CDWORD(&objeto->telacrg));
   else
     strcpy(VD_GETEND(VIDEO_CARGA_CRG_objeto,char),objeto->telacrg);

 strcpy(VD_GETEND(VIDEO_CARGA_CRG_sistema,char),objeto->sistcrg);

 VD_GETBUF(VIDEO_CARGA_CRG_tipoobj,WORD) = tipo;

 if (/*VIDEO_ACESSO_testa_acesso_objeto(VIDEO_ACESSO_USUARIO)*/ TRUE)
    {
     if ((ret = CTREE_find(indice,VD_NULO,
                FIND_IGUAL,CT_LE_EXTRA_REPASSA)) != 0)
        {
    /*
         sprintf(buffer,"OBJETO NAO ENCONTRADO [%s] [%s] [%d] ST %d",
                         VD_GETEND("CRG_sistema",char),
                         VD_GETEND("CRG_objeto",char) ,
                         VD_GETBUF("CRG_tipoobj",INT2 ),ret);
         VIDEO_mostra_mens_erro(buffer,TRUE);
         sprintf(buffer,"ERRO CARGA %d",ret);
         VIDEO_mostra_mens_erro(buffer,TRUE);
    */
         return(FALSE);
        }


     if ((workifil = CTREE_ifilend(arquivo)) == VD_NULO)
        {
         VIDEO_mostra_mens_erro(VIDEO_CARGA_ifil_carga,
                                VIDEO_ERRO_ifil_crg_tela_nao_encontrado);
         return(FALSE);
        }

     tamreg = VD_GETBUF(VIDEO_CARGA_CRG_tamext,WORD) + workifil->dreclen;

     if ((strtelacrg = VIDEO_alloc_parametros(tamreg)) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_CARGA_TELA);
         return(FALSE);
        }

     if ((real_arquivo=CTREE_tmpfil(arquivo))<0)
        {
         VIDEO_mostra_mens_erro(VIDEO_CARGA_real_carga,
                                VIDEO_ERRO_tmpfil_tela_nao_encontrado);
         VIDEO_free_alloc_parametros(strtelacrg);
         return(FALSE);
        }

     if ((ret=DATABASE_ReReadVRecord(real_arquivo, strtelacrg,tamreg))!=0)
        {
    /*
         sprintf(buffer,"ERRO LEITURA (EXTENSAO) OBJETO [%s] [%s] %d",
                         objeto->telacrg,objeto->sistcrg,ret);
         VIDEO_free_alloc_parametros(strtelacrg);
         VIDEO_mostra_mens_erro(buffer,TRUE);
         sprintf(buffer,"ERRO EXTENCAO %d",ret);
         VIDEO_mostra_mens_erro(buffer,TRUE);
    */
         VIDEO_free_alloc_parametros(strtelacrg);
         return(FALSE);
        }

     VIDEO_copbloco(strtelacrg,PTR_CAST(char,strtelacrg)+workifil->dreclen,
                    tamreg-workifil->dreclen);

     objeto->strtelacrg = strtelacrg;

     if (tipo == 1)
         objeto->tela = PTR_CAST(VIDEO_TABCRGTELA,strtelacrg)->telasai;
       else
         objeto->tela = VD_NULO;

#endif

     if (!VIDEO_ctrl_carga)
        {
         if (VIDEO_ALLOC_MEM(VIDEO_ctrl_carga,sizeof(VIDEO_CTRL_CARGA)) == VD_NULO)
            {
             VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONTROLE_CARGA);
            }
          else
            VIDEO_setmem(VIDEO_ctrl_carga,sizeof(VIDEO_CTRL_CARGA),0);
        }

     if (VIDEO_ctrl_carga)
        {
         VIDEO_CTRL_CARGA *aux;

         if (!VIDEO_ctrl_carga->atual)
            {
             VIDEO_ctrl_carga->atual = objeto;
             VIDEO_ctrl_carga->tipo  = tipo;
            }
          else
            {
             if (VIDEO_ALLOC_MEM(aux,sizeof(VIDEO_CTRL_CARGA)) == VD_NULO)
                {
                 VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONTROLE_CARGA);
                }
              else
                {
                 VIDEO_setmem(aux,sizeof(VIDEO_CTRL_CARGA),0);
                 VIDEO_ctrl_carga->posterior = aux;
                 aux->anterior    = VIDEO_ctrl_carga;
                 aux->atual       = objeto;
                 aux->tipo        = tipo;
                 VIDEO_ctrl_carga = aux;
                }
            }

         VIDEO_imagem_atual = VD_NULO;
         VIDEO_tela_atual   = VD_NULO;
         VIDEO_cons_atual   = VD_NULO;
         VIDEO_campo_atual  = VD_NULO;
         VIDEO_doda_campo   = VD_NULO;
        }

     return(TRUE);
    }
  else
    return(FALSE);

}
