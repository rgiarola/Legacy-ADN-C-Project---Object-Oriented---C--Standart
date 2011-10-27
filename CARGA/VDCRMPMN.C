#include <INCVIDEO.H>

VD_VOID VIDEO_CRG_prepara_menu(menu)
VIDEO_ESTMANUT *menu;
{
 VIDEO_NUCLEO_SERV *nucleo;
 VIDEO_INFO_MENU   *menudisp;
 char              *buffercrg,
                   **opcoes;
 INT2               cont;

 buffercrg = PTR_CAST(char,menu->strtelacrg);

 menudisp   = PTR_CAST(VIDEO_INFO_MENU,(buffercrg+sizeof(VIDEO_NUCLEO_SERV)));
 nucleo = PTR_CAST(VIDEO_NUCLEO_SERV,buffercrg);

 nucleo->VIDEO_campos  = PTR_CAST(VIDEO_TAB_FUNC,menudisp);
 nucleo->VIDEO_tabserv = VIDEO_MENU_tabela_de_servicos;

 menudisp->MENU_pega_opcao = VIDEO_MENU_pega_selecao;
 menudisp->funcserv        = VIDEO_getkbd;
 opcoes = menudisp->opcoes = PTR_CAST(char *,(W(menudisp->opcoes)+buffercrg));

 cont = 0;
 do
  {
   *opcoes = W(*opcoes) + buffercrg;
   ++opcoes;
  }while(++cont < menudisp->numop);

 menudisp->nomehelp = (W(menudisp->nomehelp ) !=  0XFFFE)  ?
         PTR_CAST(char,(W(menudisp->nomehelp )+buffercrg)) :
         VIDEO_NILL(char);

 menudisp->titulo = (W(menudisp->titulo ) !=  0XFFFE)  ?
         PTR_CAST(char,(W(menudisp->titulo )+buffercrg)) :
         VIDEO_NILL(char);
}
