#include <INCVIDEO.H>

INT2 VIDEO_mostra_mens_erro(mens,flagerro)
char *mens;
int  flagerro;
{
 INT2           ret,col,lin,aux;
 static BOOLEAN flag = TRUE;
 char           mensagem[200];

 VIDEO_movbloco(mensagem,mens,78);
 mensagem[78] = 0;


 if (!flagerro)
    {
     strcat(mensagem,VIDEO_cancela_operacao);
     if (strlen(mensagem) > 78)
         mensagem[78] = 0;
    }
  else
    if (flagerro < 0)
       {
        sprintf(mensagem,"Erro %s Cod[%d]",mens,flagerro);
        mensagem[78] = 0;
       }

 col = VIDEO_mensagem_default.col;
 lin = VIDEO_mensagem_default.lin;

#ifdef APLIC_POS4000
 if ((aux = strlen(mensagem)) > 40)
     aux = 40;
 mensagem[aux] = 0;
 aux = (40-aux)/2+1;
 if ((aux + strlen(mensagem)-1) > 40)
    --aux;

 VIDEO_mensagem_default.col = aux;
 VIDEO_mensagem_default.lin = 1;

 VIDEO_mensagem_default.mensagem = mensagem;
 ret = VIDEO_TELA_display_mens(&VIDEO_mensagem_default);

 if (flagerro < 0)
    VIDEO_grava_erro(mensagem);
#else
 if (flag)
    {
     flag = FALSE;
     VD_tcursor(0X20,0X20);
     VIDEO_libera_buffer_teclado();
     if (isam_err != 101 && isam_err != 100 && isam_err)
         ret = VIDEO_mostra_erro_critico(flagerro);
       else
         ret = VD_telaerr((80-strlen(mensagem))/2-2,VIDEO_LIN_MENSAGEM,
                           mensagem,VIDEO_mensagem_default.cor);

     flag = TRUE;
         if (flagerro < 0)
                VIDEO_grava_erro(mensagem);
    }
  else
    {
     VIDEO_mensagem_default.mensagem = mensagem;
     ret = VIDEO_TELA_display_mens(&VIDEO_mensagem_default);
         if (flagerro < 0)
                VIDEO_grava_erro(mensagem);
    }
#endif


#ifdef VIDEO_UNIX
 VIDEO_UNIX_refresh_tela();
#endif

 VIDEO_mensagem_default.col = col;
 VIDEO_mensagem_default.lin = lin;

 return(ret);
}

INT2 VIDEO_mostra_mens_erro_alloc(num_erro)
INT2 num_erro;
{
 char buffer[200];
 sprintf(buffer,VIDEO_mensagem_erro_alloc,farcoreleft());
 return(VIDEO_mostra_mens_erro(buffer,num_erro));
}


VD_VOID VIDEO_libera_buffer_teclado(VD_VOID)
{
 BYTE ascii,scan;

 while(VIDEO_getkey(&ascii, &scan));
 if (VIDEO_MOUSE_ativo)
    {
     int botpres,numclick,
         colclick,linclick;
     while(VIDEO_MOUSE_intbotpres())
        VIDEO_MOUSE_intbot(&botpres,&numclick,
                           &colclick,&linclick);
    }
}

