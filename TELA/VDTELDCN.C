#include <INCVIDEO.H>

INT2 VIDEO_TELA_mouse_dispcons(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_CAMPO_TELA         *campo;
 VIDEO_NUCLEO_SERV        *nucleo;
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_INFO_MENU          *menu;

 VIDEO_TELA_mouse_posiciona(tela,param);

 if ((*param)->VIDEO_repdisp)
    return(TRUE);

 nucleo    = (*tela)->imagem_ativa->campos;

 campo     = PTR_CAST(VIDEO_CAMPO_TELA,nucleo->VIDEO_campos)+
                      nucleo->VIDEO_inicial;

 if (campo->status&VIDEO_EDITA_PROTEGIDO)
    return(TRUE);

 if (!((campo->lin == VIDEO_MOUSE_linha_atual)  &&
       (campo->col <= VIDEO_MOUSE_coluna_atual) &&
       ((campo->col + campo->tamanho) >= VIDEO_MOUSE_coluna_atual)))
     return(TRUE);

 if ((consiste = campo->consiste) == VD_NULO)
    return(TRUE);

 do
  {
   switch(consiste->tipocons)
    {
     case  VIDEO_TELA_CONS_MENU:
           VIDEO_TELA_consiste_tabela_menu(&campo,consiste->objetocons.menu);
           return(TRUE);

     case VIDEO_TELA_CONS_BUSCA_DB:
          (*param)->VIDEO_repdisp = TRUE;
          (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_B);
          return(TRUE);
    }
   ++consiste;
  }while(consiste->tipocons);

 return(TRUE);
}

