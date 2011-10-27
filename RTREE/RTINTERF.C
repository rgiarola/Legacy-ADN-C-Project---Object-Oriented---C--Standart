/* 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커
   � Executa um rtree SCRIPT                                                  �
   읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸 */
#include <INCVIDEO.H>
extern char rtfname[];

extern char   *VIDEO_RTREE_dispositivo_impressao;
extern char    VIDEO_RTREE_fase_processo;
extern VD_time VIDEO_RTREE_cronometro;

#ifdef PD_COR_01
#undef PD_COR_01
#endif

#ifdef PD_COR_02
#undef PD_COR_02
#endif

#ifdef PD_COR_03
#undef PD_COR_03
#endif

#ifdef PD_COR_04
#undef PD_COR_04
#endif

#define PD_COR_01       VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL)
#define PD_COR_02       VD_FORMATO(VD_VERMELHO,VD_INTER ,VD_BLANK,VD_BRIL)
#define PD_COR_20       VD_FORMATO(VD_PRETO   ,VD_NORMAL,VD_BLANK,VD_BRIL)

#define PD_COR_03       VD_FORMATO(VD_AZULTURQ,VD_NORMAL,VD_BLANK,VD_BRIL)
#define PD_COR_04       VD_FORMATO(VD_BLANK   ,VD_NORMAL,VD_PRETO,VD_NORMAL)

VD_VOID RTREE_processo()
{
 char    auxmens[100];
 VD_time horaatual;
 double  inicio,
         atual ,
         tempo ;

 if (VIDEO_RTREE_dispositivo_impressao &&
     (*VIDEO_RTREE_dispositivo_impressao)!=3)
    {
     VIDEO_plotcarac(VIDEO_mensagem_default.col,
                     VIDEO_mensagem_default.lin,' ',PD_COR_01);

     ++VIDEO_mensagem_default.col;
     if (VIDEO_mensagem_default.col>=49)
         VIDEO_mensagem_default.col=32;

     VIDEO_plotcarac(VIDEO_mensagem_default.col,
                     VIDEO_mensagem_default.lin,178,PD_COR_01);

     // Fase do Processamento
     if (VIDEO_RTREE_fase_processo==2)
        sprintf (auxmens,"%s", "IMPRESS랳 ");
      else
        sprintf (auxmens,"%s", "PREPARANDO");
     VD_tprt_l (67,18,auxmens,PD_COR_04);

     // N즡ero de P쟥inas
     sprintf (auxmens,"%04d",rtpage);
     VD_tprt_l (67,19,auxmens,PD_COR_04);

     // N즡ero de Linhas Geradas
     sprintf (auxmens,"%04d", bdycnt); // rtline); -> Linhas Por P쟥ina
     VD_tprt_l (67,20,auxmens,PD_COR_04);

     // Cron뱈etro
     inicio = VIDEO_total_tempo (VIDEO_RTREE_cronometro);
     VD_gettime(&horaatual);
     atual  = VIDEO_total_tempo (horaatual);
     if (inicio <= atual)
        tempo = atual - inicio;
      else
        tempo = inicio- atual ;

     horaatual = VIDEO_conv_tempo_total(tempo);

     sprintf(auxmens,"%02d:%02d:%02dhs",
                     VD_timeHor(horaatual),
                     VD_timeMin(horaatual),
                     VD_timeSeg(horaatual));
     VD_tprt_l (67,22,auxmens,PD_COR_04);

    }
 return;
}

INT2 RTREE_interface(mode,tp,tlen)
INT2    mode;
char   *tp;
INT2    tlen;
{
 BYTE             ascii,scan;
        int       ILBAGNO_interface_extenso();


    /*
       mode
         == LOOP_SEL : Chamada apartir da secao SELECT.
            LOOP_SRT : Chamada apartir da secao SORT.
            LOOP_IMG : Chamada apartir da secao line OUTPUT.
            LOOP_INP : Chamada apartir da Funcao INTERFACE.
        */

    switch (mode)
     {
      case LOOP_SRT:    // Sort
      case LOOP_SEL:    // Selection
        /* -----------------------------------------
           Check para algum caracter de cancelamento
           ----------------------------------------- */

           if (VD_getkey(&ascii,&scan) && ascii == 27)
            {
              /*   1o. -> Flush o buffer de dispositivo.*/
              put_lin();

              /*   2o. -> Pede confirmacao para o cancelamento.*/
              printf("\nESC Cancela / Outra continua");
              fflush(stdin);

              /*   3o. -> Se "abort" e requisitado.*/
              VD_getkbd(&ascii,&scan);

              if (ascii == 27)
                 return(1);  /* Retorna um valor diferente de zero.*/
            }
           RTREE_processo();
           return(0);   /*  Retorna Zero Para Continuar.*/

case LOOP_IMG:
        /* process image at tp with length tlen
           return a 1 if you wish r-tree to NOT process image
           return a 0 if you wish r-tree to process image

           looper does process the image                         */

           VIDEO_RTREE_fase_processo = 2;
           RTREE_processo();
           return(0);

case LOOP_INP:

        /* Funcao INTERFACE invocada: "tp" aponta para o argumento da
           INTERFACE, "tlen" e'o tamanho do argumento, o tipo do
           argumento e'desconhecido.
           O valor de retorno desta funcao nao e'testado.
                */

        /* 1o. -> Flush o buffer de dispositivos do RTREE.*/
        put_lin();

        /* Dispara USR-FUNC se alguma. ========================================*/
         if ( VIDEO_tabfuncuser[0].userfunc )
             (VIDEO_tabfuncuser[0].userfunc)( tp, tlen );

         return(0);
        }

    return (1);
}


INT2 RTREE_exec( relatorio, path, arquivo )
char *relatorio,
     *path,
     *arquivo;
{
 VIDEO_ESTMANUT tela_aguarde = { VIDEO_padrao_sistema, TELA_PADROES_TELAGREL },
                tela_final   = { VIDEO_padrao_sistema, TELA_PADROES_TELAFREL };
 COUNT    ret;
 TEXT     script[128],
          texto[100];
 COUNT    report();
 BYTE     ascii,scan;
 BOOLEAN  flagint = FALSE;

 /* Prepara o Display =========================================================*/
 VIDEO_RTREE_fase_processo = 0;
 if (VIDEO_RTREE_dispositivo_impressao)
    {
     VD_PUSHWIN( 1,80,1,25);
     VD_CLS;

     VIDEO_CRG_display_imagem(&tela_aguarde,1,1);
    }

 strcpy( script, path     );
 strcat( script, relatorio);
 strcat( script, ".RTS"   );
 if(arquivo)
   {
    strcpy(rtfname, arquivo);
    strcat(rtfname, ".OUT");
   }
 else
  {
   strcpy(rtfname,"rel");
   strcat(rtfname, ".OUT");
  }

 /* ---------------------------------------------------------------------------
    Verifica Status da Impressora
    para Impress꼘
    --------------------------------------------------------------------------- */
 if (VIDEO_RTREE_dispositivo_impressao &&
     (*VIDEO_RTREE_dispositivo_impressao == 1))
    {
     VIDEO_VISUAL_flag_erro = FALSE;
     VIDEO_VISUAL_flag_int  = TRUE;

     if (VIDEO_VISUAL_nova_int24 != getvect(0X24))
        {
         VIDEO_VISUAL_velha_int24 = getvect(0X24);
         setvect(0X24,VIDEO_VISUAL_nova_int24);
         flagint = TRUE;
        }
     do
      {
       /*
          Vai Testar a Impressora ...
          Nao funciona mais !!! -> Bug do Compilador ...
        */

       VIDEO_VISUAL_flag_erro = FALSE;
       VIDEO_VISUAL_flag_int  = FALSE;
       ret = VIDEO_IMPRESS_envia(0X0D,1);
       if (ret&(B08|B11|B13) || !(ret&B12))
          {
           VIDEO_VISUAL_flag_int  = TRUE;
           if (VIDEO_mostra_mens_erro(VIDEO_IMPRESS_erro_impressora,FALSE) ==
               VD_MTTECLA(ESCAPE,ESCAPESCAN))
              {
               VIDEO_VISUAL_flag_erro = FALSE;
               VD_POPWIN();
               return(FALSE);
              }
            continue;
           }
       break;
      }while(TRUE);
    }

 VIDEO_mensagem_default.col=32;
 VIDEO_mensagem_default.lin= 8;
 VIDEO_VISUAL_flag_erro    = FALSE;
 VIDEO_VISUAL_flag_int     = TRUE;

 /* ---------------------------------------------------------------------------
                     Restaura Interrup뇙o do D O S
    --------------------------------------------------------------------------- */
 if (flagint)
     setvect(0X24,VIDEO_VISUAL_velha_int24);

 VD_gettime(&VIDEO_RTREE_cronometro);   // Start Cron뱈etro

 ret = report(script, ATIVO_DODA,"", RTREE_interface);

 printf("\n");
 fflush(stdin);

 sprintf(texto, "RELATORIO %s FINALIZADO. [%03d/%02d] [OPCIONAL %s]",
         relatorio, ret,VIDEO_RTREE_dispositivo_impressao    ?
                        I(*VIDEO_RTREE_dispositivo_impressao):
                        99, arquivo);

 if (VIDEO_RTREE_dispositivo_impressao)
    {
     VIDEO_box_simples(1,80,2,4,PD_COR_03);
     VD_quadro( 2,79,3,3,' ',PD_COR_03);
     VD_tprt_l(40-(strlen(texto)/2),3,texto, PD_COR_03);

     // VIDEO_box_simples(1,80,23,25,PD_COR_01);
     // VD_quadro( 1,80,25,25,' ',PD_COR_01);
    }

 if ((!ret || ret == 343 || ret==346) && VIDEO_RTREE_dispositivo_impressao &&
     (*VIDEO_RTREE_dispositivo_impressao == 2 ||
      *VIDEO_RTREE_dispositivo_impressao == 4))
    {
     VIDEO_CRG_display_imagem(&tela_final,1,0);

     if (VIDEO_CRG_executa_menu_carrega(&VIDEO_VISUAL_menu_seleciona))
        {
         switch(VIDEO_CRG_dispara_menu(&VIDEO_VISUAL_menu_seleciona,
                                       TRUE,TRUE,TRUE))
          {
		   case 1:(VIDEO_VISUAL_funcao_disparo)(rtfname,
                               VIDEO_VISUAL_titulo_tela,FALSE,
                               &VIDEO_VISUAL_imagem_padrao,VD_NULO,TRUE);
              break;

           case 2:ret = 1;
                  break;

           defalut:ret = 0;
          }
         VIDEO_CRG_libera_tela(&VIDEO_VISUAL_menu_seleciona);
         VD_POPWIN();
        }
      else
        ret = VD_telaconf((80-strlen(VIDEO_VISUAL_visualizar_arquivo))/2,9,
               VIDEO_VISUAL_visualizar_arquivo,VIDEO_PADRAO_COR);

     VD_POPWIN();
     if (ret == 1)
		 (VIDEO_VISUAL_funcao_disparo)(rtfname,VIDEO_VISUAL_titulo_tela,FALSE,
                                     &VIDEO_VISUAL_imagem_padrao,
                                     VD_NULO,FALSE);
    }
  else
    {
     if (VIDEO_RTREE_dispositivo_impressao) 
        {
         if ((*VIDEO_RTREE_dispositivo_impressao)<=4)
            VD_getkbd(&ascii,&scan);

         VD_POPWIN();
        }
    }
 return(FALSE);
}



