#include <INCVIDEO.H>

#include "VDDSPECO.C"
#include "VDDSPECP.C"
#include "VDDSPETE.C"

main(argc,argv)
int  argc;
char *argv[];
{
 IDE_ARQUIVOS   *workifil;
 VIDEO_ESTMANUT tela;
 int            ret;
 char           teladisp[31];
 char           sisteladisp[31];
 IDE_ARQUIVOS   **auxifil;

 if (argc < 3)
    {
     printf("PARAMETROS INVALIDOS\n");
     exit(1);
    }

 if ((ret=VIDEO_cargaarq(VIDEO_NILL(IDE_TABREFERBUFFER),argv[1])) != FALSE)
    {
     printf("\nSTATUS DE ERRO <CARGA DE CONFIGURACAO DE ARQUIVOS> [%d] %s\n",ret,argv[1]);
     exit(1);
    }

 if ((ret = CTREE_inicializa(VIDEO_bufparamarq->dodas,
                             VIDEO_bufparamarq->arquivos)) != 0)
    {
     printf("\nSTATUS DE ERRO <INICIALIZACAO DO SISTEMA> [%d %d]",ret,isam_err);
     VIDEO_freecarga();
     exit(1);
    }

 auxifil = ATIVO_IFIL;
 ret = 0;
 while( *auxifil )
  {
   (*auxifil)->dfilno = ret;
   ret += ((*auxifil)->dnumidx+1);
   ++auxifil;
  }

 if ((ret = CTREE_keynm("SCRPTKEY")) < 1)
    {
     char bufferlocal[100];
     sprintf(bufferlocal,"INDICE SCRPTKEY NAO CARREGADO %d ",ret);
     VIDEO_mensagem_default.mensagem = bufferlocal;
     VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
     VIDEO_freecarga();
     exit(1);
    }

 if ((ret = CTREE_keyfil(ret)) < 0)
    {
     char bufferlocal[100];
     sprintf(bufferlocal,"ARQUIVO DO INDICE SCRPTKEY NAO ENCONTRADO %d ",ret);
     VIDEO_mensagem_default.mensagem = bufferlocal;
     VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
     VIDEO_freecarga();
     exit(1);
    }

 if ((workifil = CTREE_ifilend(ret)) == VD_NULO)
    {
     VIDEO_mensagem_default.mensagem = "IFIL DO INDICE SCRPTKEY NAO ENCONTRADO";
     VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
     VIDEO_freecarga();
     exit(1);
    }

 if ((ret = CTREE_open2(workifil,argv[2],"DAT",
                                 argv[2],"IDX",TRUE))
                        != FALSE)
    {
     printf("\nIMPOSSIVEL ABRIR ARQUIVO DE CARGA DE TELAS %s\n"
            "programa abortado com erro %d",argv[2],ret);
     VIDEO_freecarga();
     exit(1);
    }

 printf("ENTRE COM A TELA ");
 gets(teladisp);
 printf("ENTRE COM O SISTEMA ");
 gets(sisteladisp);
 tela.sistcrg = sisteladisp;
 tela.telacrg = teladisp;

 if (VIDEO_CRG_carrega_objeto(&tela,1))
     if (VIDEO_CRG_prepara_tela(&tela))
        {
         VIDEO_DISPLAY_endereca_tela(tela.strtelacrg);
         VIDEO_CRG_libera_tela(&tela);
        }
 CLISAM();
 VIDEO_freecarga();
}





