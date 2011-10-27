/* ----------------------------------------------------------------------------
   REBUILD   (main)
      ISAM REBUILD de para arquivos CTREE.
   PARAMETROS:  CARGA:   nome completo do arquivo de carga.
                ARQUIVO: nome do arquivo s/ extensao.
   ---------------------------------------------------------------------------- */
#include <INCVIDEO.H>

unsigned _stklen = 20000;

aborta(void)
{
 return(TRUE);
}

char dicionario[128],
     nomearq   [128],
     nomedisco [128],
     path[128];

INT2 main( argc, argv)
INT2   argc;
char *argv[];
{
 IDE_ARQUIVOS *auxifil;
 INT2  arquivo,
      ret;



 ctrlbrk(aborta);

 if (argc<3 || argc>6)
    {
     printf("REBUILD: Comando Invalido.\n");
     printf("Tech C Infomatica 1993\n\n");
     printf("SINTAXE\n");
     printf("REBUILD DICARQ.CRG ARQIDE ARQNOME\n");
     printf("Onde: REBUILD     e'o nome deste utilitario\n");
     printf("      DICARQ.CRG  e'o nome o dicionario de arquivos do sistema\n");
     printf("      ARQIDE      e'o nome IDENTIFICADOR do arquivo.\n");
     printf("      ARQNOME     e'o nome em disco do arquivo (somente T M P\n");
     exit(1);
    }

 strcpy(dicionario,argv[1]);
 strcpy(nomearq   ,argv[2]);
 if (argc>4)
    {
     strcpy( nomedisco, argv[3]);
     strcpy( path, argv[4]);
    }
  else
     strcpy( path, argv[3]);


 if ((ret=VIDEO_cargaarq(VIDEO_NILL(IDE_TABREFERBUFFER),dicionario,path)) != FALSE)
    {
     printf("\nSTATUS DE ERRO <DICIONARIO DE ARQUIVOS> %s [%d]\n",
            dicionario, ret);
     exit(1);
    }

 if ((ret = CTREE_inicializa(VIDEO_bufparamarq->dodas,
                             VIDEO_bufparamarq->arquivos)) != 0)
    {
     printf("\nSTATUS DE ERRO <INICIALIZA€ŽO DO SISTEMA> [%d %d]",ret,isam_err);
     exit(1);
    }

 arquivo=0;
 if ((arquivo=CTREE_filnm(nomearq,FALSE))<0)
    {
     printf("\n NOME DO ARQUIVO [%s] NAO ENCONTRADO ST %d",nomearq,arquivo);
     exit(1);
    }

 auxifil = CTREE_ifilend(arquivo);

 if (argc>3)
    auxifil->pfilnam = nomedisco;

 auxifil->dfilno = -1;
 if ((ret=DATABASE_RebuildIFile(auxifil))!=FALSE)   /* Rebuild*/
    {
     printf("\nFATAL ERRO!!! REBUILD ST [%d %d] ARQUIVO [%s]",ret,isam_err,
             auxifil->pfilnam);
     exit(1);
    }


 return(0);
}
