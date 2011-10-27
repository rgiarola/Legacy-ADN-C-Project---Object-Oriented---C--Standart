#include <INCVIDEO.H>

VD_VOID VIDEO_endereca_help(VIDEO_HELP_CONTROLE *help);

main(argc,argv)
INT2  argc;
char *argv[];
{
 VIDEO_HELP_CONTROLE *buffer;
 INT2                 ret    ,indice,
                     arquivo,cont;
 char                **linaux;

 if ((ret = VIDEO_cargaarq(VD_NILL(IDE_TABREFERBUFFER),"HELP.CRG")) != FALSE)
    {
     printf("ERRO CARGA DE PARAMETROS %d\n",ret);
     return;
    }

 CTREE_inicializa(VIDEO_bufparamarq->dodas, VIDEO_bufparamarq->arquivos);

 CTREE_open();

 indice  = CTREE_keynm("INDHELP");
 arquivo = CTREE_keyfil(indice);

 if (VIDEO_ALLOC_MEM(buffer,1024*20) == VD_NULO)
    {
     printf("ERRO ALOCACAO DE MEMORIA BUFFER");
     exit(0);
    }

 if (argc > 1)
    {
     CTREE_inbuf(arquivo);
     strcpy(VD_GETEND("HELP_nomehelp",char),argv[1]);

     if ((ret = CTREE_find(indice,VD_NULO,FIND_IGUAL,CT_LE_DADOS)) != 0)
        {
         sprintf(buffer,"ERRO FIND IGUAL %d %d %d",
                           ret,indice,arquivo);
         VIDEO_mensagem_default.mensagem = buffer;
         VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
        }

     printf("HELP [%s] TAMANHO [%5u]\n",
                               CTREE_dodaend("HELP_nomehelp")->fadr,
                               CWORD(CTREE_dodaend("HELP_tamanho")->fadr));
     if ((ret = CTREE_rdvlen(arquivo,buffer,
                          CWORD(CTREE_dodaend("HELP_tamanho")->fadr))) != FALSE)
        {
         sprintf(buffer,"ERRO REDEAD %d %d %d",ret,indice,arquivo);
         VIDEO_mensagem_default.mensagem = buffer;
         VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
        }
     printf("NUMLIN %5u \n",buffer->numlin);
     printf("%s\n",CAST_CHAR(W(buffer->titulo)+((char *)buffer)+(sizeof(char **)*buffer->numlin)));
     linaux = &buffer->linha[0];
     for (cont = 0;cont < (buffer->numlin-1);cont++)
         printf("%5u %p %s \n",cont,W(*(linaux+cont))+((char *) buffer)+(sizeof(char **)*buffer->numlin),
                           W(*(linaux+cont))+((char *) buffer)+(sizeof(char **)*buffer->numlin));
    }
  else
    {
     if ((ret = CTREE_find(indice,VD_NULO,FIND_PRIMEIRO,CT_LE_DADOS)) != 0)
        {
         sprintf(buffer,"ERRO FIND PRIMEIRO %d %d %d",
                           ret,indice,arquivo);
         VIDEO_mensagem_default.mensagem = buffer;
         VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
        }

     while(!ret)
      {
       printf("HELP [%s] TAMANHO [%5u]\n",
                                 CTREE_dodaend("HELP_nomehelp")->fadr,
                                 CWORD(CTREE_dodaend("HELP_tamanho")->fadr));
       if ((ret = CTREE_rdvlen(arquivo,buffer,
                            CWORD(CTREE_dodaend("HELP_tamanho")->fadr))) != FALSE)
          {
           sprintf(buffer,"ERRO REDEAD %d %d %d",ret,indice,arquivo);
           VIDEO_mensagem_default.mensagem = buffer;
           VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
          }
       printf("NUMLIN %5u \n",buffer->numlin);
       printf("%s\n",CAST_CHAR(W(buffer->titulo)+((char *)buffer)+(sizeof(char **)*buffer->numlin)));
       linaux = &buffer->linha[0];
       for (cont = 0;cont < (buffer->numlin-1);cont++)
           printf("%5u %p %s \n",cont,W(*(linaux+cont))+((char *) buffer)+(sizeof(char **)*buffer->numlin),
                             W(*(linaux+cont))+((char *) buffer)+(sizeof(char **)*buffer->numlin));
       ret = CTREE_find(indice,VD_NULO,FIND_PROXIMO,CT_LE_DADOS);
      }
    }

 CLISAM();

 VIDEO_freecarga();
}

VD_VOID VIDEO_endereca_help(help)
VIDEO_HELP_CONTROLE *help;
{
 INT2 cont;
 help->titulo = CAST_CHAR(W(help->titulo)+CAST_CHAR(help)+
                            (sizeof(char **)*help->numlin));
 for (cont = 0;cont < (help->numlin-1);cont++)
      help->linha[cont] = CAST_CHAR(W(help->linha[cont])+CAST_CHAR(help)+
                                    (sizeof(char **)*help->numlin));
 help->linha[cont] = VD_NILL(char);
}

