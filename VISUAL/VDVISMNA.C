#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_menu_objetos(tabela_objetos,numele,coli,lini,tamcol)
char **tabela_objetos;
int  numele,
     coli,
     lini,
     tamcol;
{
 VIDEO_INFO_MENU   menu;
 VIDEO_NUCLEO_SERV nucleo;
 int               aux;

 aux = 23 - lini + 1;
 menu.MENU_pega_opcao = VIDEO_MENU_pega_selecao;
 menu.coli            = coli;
 menu.colf            = menu.coli+tamcol-1+1;
 menu.lini            = lini;
 menu.numop           = numele;
 menu.numlin          = numele > aux ? aux : numele;

 menu.numpag = (numele / aux) - ((numele % aux) == 0);
 menu.tamcol = tamcol;

 while((((menu.numpag+1)*menu.tamcol)+menu.coli) > 80)
    --menu.numpag;

 menu.linf            = menu.lini + menu.numlin-1;
 menu.opsel           = 0;
 menu.colatu          = 0;
 menu.col             = menu.coli;
 menu.lin             = menu.lini;
 menu.opini           = 0;
 menu.colpag          = 0;
 menu.opselec         = 0;
 menu.tamdispop       = tamcol-1;
 menu.funcserv        = VD_getkbd;
 menu.opcoes          = tabela_objetos;
 menu.cor_opcao       = VIDEO_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL);
 menu.cor_selecao     = VIDEO_FORMATO(VD_BLANK,VD_NORMAL,VD_AZULTURQ,VD_NORMAL);
 menu.cor_moldura     = VIDEO_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL);
 menu.cor_sombra      = VIDEO_FORMATO(VD_BLANK,VD_NORMAL,VD_PRETO,VD_NORMAL);
 menu.flagdispcol	  = TRUE;
 menu.flagdispop	  = TRUE;
 menu.flagmoldura     = TRUE;
 menu.tipomoldura     = VIDEO_BOX_SIMPLES;
 menu.titulo          = VIDEO_VISUAL_titulo_menu_arq;

 menu.caracmoldura    = 0;

 nucleo.VIDEO_campos    = PTR_CAST(VIDEO_TAB_FUNC,&menu);
 nucleo.VIDEO_numcampos = 1;
 nucleo.VIDEO_tamcampo  = sizeof(VIDEO_INFO_MENU);
 nucleo.VIDEO_inicial   = 0;
 nucleo.VIDEO_tabserv   = VIDEO_MENU_tabela_de_servicos;


 VIDEO_NUCLEO_servidor_mspas(&nucleo);

 return(menu.opselec);
}

