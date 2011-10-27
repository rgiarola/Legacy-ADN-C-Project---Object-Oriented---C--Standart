#include <INCVIDEO.H>

main()
{
 INT2                 ret    ,indice,
                     arquivo,cont,col,lin;
 IDE_ARQUIVOS *workifil;

 if ((ret = VIDEO_cargaarq(VD_NILL(IDE_TABREFERBUFFER),"HELP.CRG")) != FALSE)
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

 ret      = CTREE_keynm("SCRPTKEY");
 ret      = CTREE_keyfil(ret);
 workifil = CTREE_ifilend(ret);
 if ((ret = CTREE_open2(workifil,"TELHELP","DAT",
                                 "TELHELP","IDX",TRUE)) != FALSE)
    {
     printf("\nIMPOSSIVEL ABRIR ARQUIVO DE CARGA DE TELAS %s ST [%d %d %d %d %d]\n",
            "TELHELP",
            ret,isam_err,isam_fil,workifil->dfilno,workifil->tfilno);
     printf("\n[%p %s]\n",workifil,workifil->pfilnam);
     CLISAM();
     VIDEO_freecarga();
     exit(1);
    }

 if ((VIDEO_MOUSE_ativo = VIDEO_MOUSE_inicializa()) > 0)
    {
     VIDEO_MOUSE_setpos(1,1);
     VIDEO_MOUSE_habcursor();
     VIDEO_MOUSE_deshabcursor();
    }

 VD_getxy(&col,&lin);

 VIDEO_VISUAL_dispara_visual("HELP DA ARVORE",VD_NULO,TRUE,
                                 &VIDEO_HELP_imagem_padrao,
                                 VIDEO_VISUAL_menu);
/*
 VIDEO_VISUAL_dispara_visual("TMENU.C","VISUALIZANDO ARQUIVO -> ",FALSE,
                                 &VIDEO_HELP_imagem_padrao,
                                 VIDEO_VISUAL_menu);
*/
 CLISAM();

 VIDEO_freecarga();

 VIDEO_MOUSE_deshabcursor();

 VD_gtxy(col,lin);
 VD_tcursor(6,7);
}



