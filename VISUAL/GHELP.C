#include <INCVIDEO.H>

INT2         coli = 0,colf = 0,
             lini = 0,linf = 0,
             desc = -1,
             posbuffer = 0,
             flagfim,
             contlinha = 0;
IDE_ARQUIVOS *workifil;
DWORD tamarq;

char *pegalinha(VD_VOID);
char arquivo[100] = "HELP.DOC";
char buflinha[5010];
INT2 pegalimite(VD_VOID);
VD_VOID gerahelp(VD_VOID);
INT2 peganumhelp(DWORD *numhelp);

char BDISP_texto1[]          =   "DISP_texto1",
     BDISP_texto2[]          =   "DISP_texto2",
     BDISP_texto3[]          =   "DISP_texto3",
     BREL_selec1[]           =   "REL_selec1",
     BREL_selec2[]           =   "REL_selec2",
     BREL_selec3[]           =   "REL_selec3",
     BREL_selec4[]           =   "REL_selec4",
     BREL_selec5[]           =   "REL_selec5",
     BREL_selec6[]           =   "REL_selec6",
     BREL_selec7[]           =   "REL_selec7",
     BREL_selec8[]           =   "REL_selec8";

main(argc,argv)
INT2  argc;
char *argv[];
{
 INT2  ret;
 char *linha;

 if (argc > 1)
    strcpy( arquivo,argv[1] );


 if ((ret = VIDEO_cargaarq(VD_NILL(IDE_TABREFERBUFFER),"HELP.CRG","HELP.PAT")) != FALSE)
    {
     printf("ERRO CARGA DE PARAMETROS %d\n",ret);
     return;
    }

 CTREE_inicializa(VIDEO_bufparamarq->dodas, VIDEO_bufparamarq->arquivos);

 ret = CTREE_keyfil(CTREE_keynm("INDHELP"));
 workifil = CTREE_ifilend(ret);
 if ((ret = CTREE_open2(workifil,"HELP","DAT",
                                 "HELP","IDX",TRUE)) != FALSE)
    {
         printf("\nIMPOSSIVEL ABRIR ARQUIVO DE HELP %s ST [%d %d]\n",
                "HELP",ret,isam_err);
         VIDEO_freecarga();
         exit(1);
    }

 gerahelp();

 CLISAM();

 VIDEO_freecarga();
}

INT2 pegalimite(VD_VOID)
{
 char *linha, numero[3],
      *elem, *prx;
 INT2  tamlinha,
      cont,contelem;

 tamlinha = strlen(linha);

 if ((linha = pegalinha()) == VD_NULO)
    {
     printf("ERRO LINHA DE LIMITE LINHA %d\n",contlinha);
     CLISAM();
     exit(0);
    }

 tamlinha = strlen(linha);
 cont     = 0;

 contelem = 0;
 do
  {
   if (*linha >= '0' && *linha <= '9')
      numero[contelem] = *linha;
  }while (*linha++ && contelem++ < 2);
 numero[contelem] = '\0';

 coli = 1;
 colf = atoi(numero);
 lini = 1;
 linf = 25;

 return(VIDEO_teste_4(coli,colf,lini,linf));
}




char *pegalinha()
{
 DWORD tamanho;
 INT2      posfim;
 char     *fim;

 if (desc < 0)
    {
     if ((desc = VIDEO_open_ler(arquivo)) < 0)
        {
         printf("ERRO NA ABERTURA DO ARQUIVO %s %d\n",arquivo,desc);
         CLISAM();
         exit(0);
        }

     if ((tamarq = filelength(desc)) <= 0)
        {
         printf("ERRO TAMANHO ARQUIVO %s %ld\n",arquivo,tamarq);
         close(desc);
         CLISAM();
         exit(0);
        }
     posbuffer = 5000;
    }

 if (posbuffer >= 5000)
    {
     if ((flagfim = read(desc,buflinha,5000)) < 0)
        {
         printf("ERRO DE LEITURA NO ARQUIVO DE HELP %d LINHA %d\n",flagfim,contlinha);
         CLISAM();
         exit(0);
        }

     if (!flagfim)
        return(VD_NILL(char));

     posbuffer = 0;
     buflinha[flagfim] = '\0';
    }

 if (posbuffer < 5000)
    {
     if ((fim = strchr(&buflinha[posbuffer],0X0D)) == VD_NULO)
        {
         posfim = strlen(&buflinha[posbuffer]);
         VIDEO_copbloco(buflinha,&buflinha[posbuffer],posfim + 1);
         posbuffer = 0;
         if ((flagfim = read(desc,&buflinha[posfim],5000-posfim)) < 0)
            {
             printf("ERRO DE LEITURA NO ARQUIVO DE HELP %d LINHA %d\n",flagfim,contlinha);
             CLISAM();
             exit(0);
            }
         buflinha[flagfim] = '\0';
         if (!flagfim)
            {
             if (!strlen(&buflinha[posbuffer]))
                 return(VIDEO_NILL(char));
             buflinha[posfim]   = 0X0D;
             buflinha[posfim+1] = 0X00;
            }
         if ((fim = strchr(&buflinha[posbuffer],0X0D)) == VD_NULO)
            {
             printf("ERRO LOCALIZACAO DO FIM DA LINHA %d\n",contlinha);
             CLISAM();
             exit(0);
            }
        }
     *fim = 0X00;
     posfim = posbuffer;
     if (buflinha[posfim] == 0X0A || buflinha[posfim] == 0X0D)
        {
         ++posfim;
         ++posbuffer;
        }
     posbuffer += (strlen(&buflinha[posfim])+1);
     ++contlinha;
/*     printf("LINHA %5u %s \n",contlinha,&buflinha[posfim]);*/
     return(&buflinha[posfim]);
    }
 return(VIDEO_NILL(char));
}

VD_VOID gerahelp(VD_VOID)
{
 char    *bufhelp, **linhelp,**linaux,
         *linha  , *ininum,
         *fimnum ,*aux    , numero[13];
 INT2     contbuf   , contlin,
         tamlin    , maxlin,
         linsep    , tamaux,
         contnumero, ret,tamhelp,cont,titulo;
 char    nomehelp[31];
 BOOLEAN flaghelp;
 VIDEO_VISUAL_CONTROLE *help;

 if (!pegalimite())
    {
     printf("ERRO LIMITE COLI [%d] COLF [%d] LINI [%d] LINF [%d] LINHA %d\n",
                         coli,colf,lini,linf,contlinha);
     CLISAM();
     exit(0);
    }

 maxlin = colf - coli + 1;
 printf("LIMITE COLI [%d] COLF [%d] LINI [%d] LINF [%d] LINHA %d\n",
                     coli,colf,lini,linf,contlinha);
 if (VIDEO_ALLOC_MEM(bufhelp,1024*20) == VD_NULO)
    {
     printf("ERRO ALOCACAO DE MEMORIA BUFHELP\n");
     CLISAM();
     exit(0);
    }

 if (VIDEO_ALLOC_MEM(CAST_CHAR(linhelp),1000*sizeof(char **)) == VD_NULO)
    {
     printf("ERRO ALOCACAO DE MEMORIA LINHELP\n");
     CLISAM();
     exit(0);
    }

 contlin = contbuf = 0;

 flaghelp = TRUE;
 do
  {
   if ((linha = pegalinha()) == VD_NULO)
       break;

   if ((ininum = strstr(linha,"{{")) == VD_NULO)
      {
       if (!flaghelp)
          {
           if ((tamlin = strlen(linha)) > maxlin)
              {
               linsep = maxlin-1;
               aux = linha + linsep;
               do
                {
                 while(aux != linha && *aux != ' ')
                  --aux;

                 if (aux == linha)
                    {
                     VIDEO_movbloco(bufhelp+contbuf,linha,linsep);
                     *(bufhelp+contbuf+linsep) = '-';
                     *(bufhelp+contbuf+linsep+1) = '\0';
                     *(linhelp+contlin) = ((char *) contbuf);
/*                     printf("LINHA HELP %5u %s\n",contlin+1,bufhelp+contbuf);*/
                     contbuf += (maxlin+1);
                     ++contlin;
                     linha += linsep;
                     if (strlen(linha) > maxlin)
                         aux = linha + linsep;
                       else
                         {
                          tamaux = strlen(linha);
                          strcpy(bufhelp+contbuf,linha);
                          *(linhelp+contlin) = ((char *) contbuf);
/*                          printf("LINHA HELP %5u %s\n",contlin+1,bufhelp+contbuf);*/
                          contbuf += (tamaux+1);
                          ++contlin;
                          break;
                         }
                    }
                  else
                    {
                     *aux = '\0';
                     tamaux = strlen(linha);
                     strcpy(bufhelp+contbuf,linha);
/*                     printf("LINHA HELP %5u %s\n",contlin+1,bufhelp+contbuf);*/
                     *(linhelp+contlin) = ((char *) contbuf);
                     contbuf += (tamaux+1);
                     ++contlin;
                     linha = aux + 1;
                     if (strlen(linha) > maxlin)
                         aux = linha + linsep;
                       else
                         {
                          tamaux = strlen(linha);
                          strcpy(bufhelp+contbuf,linha);
                          *(linhelp+contlin) = ((char *) contbuf);
/*                          printf("LINHA HELP %5u %s\n",contlin+1,bufhelp+contbuf);*/
                          contbuf += (tamaux+1);
                          ++contlin;
                          break;
                         }
                    }
                }while(TRUE);
              }
            else
              {
               strcpy(bufhelp+contbuf,linha);
/*               printf("LINHA HELP %5u %s\n",contlin+1,bufhelp+contbuf);*/
               *(linhelp+contlin) = ((char *) contbuf);
               contbuf += (tamlin+1);
               ++contlin;
              }
          }
       continue;
      }
    else
      {
	   if (!flaghelp)
		  {
		   if (contlin)
			  {
               INT2 indice,arquivo;

			   indice  = CTREE_keynm("INDHELP");
			   arquivo = CTREE_keyfil(indice);

			   CTREE_inbuf(arquivo);

               help = PTR_CAST(VIDEO_VISUAL_CONTROLE,bufhelp);

               aux = CTREE_dodaend("HELP_nomehelp")->fadr;
               strcpy(aux,nomehelp);
               help->numlin = contlin+1;
               help->titulo = ((char *) titulo);
               help->coli   = coli;
               help->colf   = colf;
               help->lini   = lini;
               help->linf   = linf;
/*
               printf("TITULO [%s] \n",titulo);
               for (cont = 0;cont < contlin;cont++)
                   printf("LINHA %5u %p %s\n",cont,W(*(linhelp+cont))+bufhelp,
                                                   W(*(linhelp+cont))+bufhelp);
*/
               VIDEO_copbloco(bufhelp+(sizeof(char **)*(contlin+1))+
                              (sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)),
                              bufhelp+(sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)),
                              contbuf-(sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)));

/*
               for (cont = 0;cont < contlin;cont++)
                   printf("LINHA %5u %p %s\n",cont,
                   W(*(linhelp+cont))+(sizeof(char **)*(contlin+1))+bufhelp,
                   W(*(linhelp+cont))+(sizeof(char **)*(contlin+1))+bufhelp);
*/
               *(linhelp+contlin+1) = CAST_CHAR(0xFFFF);
               VIDEO_movbloco(bufhelp+(sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)),
                              ((char *) linhelp),(sizeof(char **)*(contlin+1)));

/*
               linaux = ((char **)(bufhelp+sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)));
               for (cont = 0;cont < contlin;cont++)
                   printf("LINHA %5u %p %s\n",cont,
                          W(*(linaux+cont))+(sizeof(char **)*(contlin+1))+bufhelp,
                          W(*(linaux+cont))+(sizeof(char **)*(contlin+1))+bufhelp);
*/
               aux = CTREE_dodaend("HELP_tamanho")->fadr;
               tamhelp = CWORD(aux) = contbuf+((contlin+1)*sizeof(char **));
			   if (CTREE_find(indice,VD_NULO,FIND_IGUAL,CT_LE_EXTRA) != 0)
				  {
                   if ((ret = CTREE_advrec(arquivo,bufhelp,tamhelp)) != 0)
					  {
                       sprintf(bufhelp,"ERRO ADVREC HELP] %s %d %d %d",
                                         nomehelp,ret,indice,arquivo);
                       VIDEO_mensagem_default.mensagem = bufhelp;
					   VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
					  }
				  }
				else
                   if ((ret = CTREE_rwvrec(arquivo,bufhelp,tamhelp)) != 0)
					  {
                       sprintf(bufhelp,"ERRO RWVREC HELP] %s %d %d %d",
                                         nomehelp,ret,indice,arquivo);
                       VIDEO_mensagem_default.mensagem = bufhelp;
					   VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
					  }
/*               printf("TAMHELP %d CONTLIN %d\n",tamhelp,contlin);*/
			  }
		  }
	   flaghelp = FALSE;
       contbuf  = sizeof(VIDEO_VISUAL_CONTROLE) - sizeof(char *);
	   contlin	= 0;
	  }

   if ((fimnum = strstr(linha,"}}")) == VD_NULO)
      {
       printf("NAO LOCALIZADO NUMERO DE HELP LINHA %s %d\n",linha,contlinha);
       CLISAM();
       exit(0);
      }

   strcpy(bufhelp+contbuf,fimnum + 2);
   titulo = contbuf;
   contbuf += (strlen(fimnum + 2)+1);
   nomehelp[30] = *fimnum = '\0';

   ininum += 2;
   VIDEO_movbloco(nomehelp,ininum,30);

 }while(TRUE);

 if (contlin)
    {
     INT2 indice,arquivo;

     indice  = CTREE_keynm("INDHELP");
     arquivo = CTREE_keyfil(indice);

     CTREE_inbuf(arquivo);

     help = PTR_CAST(VIDEO_VISUAL_CONTROLE,bufhelp);

     aux = CTREE_dodaend("HELP_nomehelp")->fadr;
     strcpy(aux,nomehelp);
     help->numlin = contlin+1;
     help->titulo = ((char *) titulo);
     help->coli   = coli;
     help->colf   = colf;
     help->lini   = lini;
     help->linf   = linf;

     VIDEO_copbloco(bufhelp+(sizeof(char **)*(contlin+1))+
                    (sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)),
                    bufhelp+(sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)),
                    contbuf-(sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)));

     *(linhelp+contlin+1) = CAST_CHAR(0xFFFF);
     VIDEO_movbloco(bufhelp+(sizeof(VIDEO_VISUAL_CONTROLE)-sizeof(char **)),
                    CAST_CHAR(linhelp),(sizeof(char **)*(contlin+1)));
     aux = CTREE_dodaend("HELP_tamanho")->fadr;
     linsep = CWORD(aux) = contbuf+((contlin+1)*sizeof(char **));
     if (CTREE_find(indice,VD_NULO,FIND_IGUAL,CT_LE_EXTRA) != 0)
        {
         if ((ret = CTREE_advrec(arquivo,bufhelp,linsep)) != 0)
            {
             sprintf(bufhelp,"ERRO ADVREC HELP] %s %d %d %d",
                               nomehelp,ret,indice,arquivo);
             VIDEO_mensagem_default.mensagem = bufhelp;
             VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
            }
        }
      else
         if ((ret = CTREE_rwvrec(arquivo,bufhelp,linsep)) != 0)
            {
             sprintf(bufhelp,"ERRO RWVREC HELP] %s %d %d %d",
                               nomehelp,ret,indice,arquivo);
             VIDEO_mensagem_default.mensagem = bufhelp;
             VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
            }
    }
 printf("NUMERO DE LINHAS DE HELP %d\n",contlinha);
}
