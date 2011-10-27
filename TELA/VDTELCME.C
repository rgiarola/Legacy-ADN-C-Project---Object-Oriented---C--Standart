#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_consiste_tabela_menu(campos, menu)
VIDEO_CAMPO_TELA  **campos;
VIDEO_INFO_MENU   *menu;
{
 VIDEO_CAMPO_TELA  *campo;
 VIDEO_EDITA_CAMPO campoedit;
 VIDEO_NUCLEO_SERV nucleo;
 char              *buffer;
 INT2               cont,tamanho;

 campo                  = (*campos);
 nucleo.VIDEO_campos    = PTR_CAST(VIDEO_TAB_FUNC,menu);
 nucleo.VIDEO_numcampos = 1;
 nucleo.VIDEO_tamcampo  = sizeof(VIDEO_INFO_MENU);
 nucleo.VIDEO_inicial   = 0;
 nucleo.VIDEO_tabserv   = VIDEO_MENU_tabela_de_servicos;
 menu->flagdispcol = menu->flagdispop = menu->flagmoldura = TRUE;

 VIDEO_NUCLEO_servidor_mspas(&nucleo);
 VD_POPWIN();
 cont = menu->opselec;
 if (!cont)
     return(TRUE);
 --cont;

 if (VIDEO_ALLOC_MEM(buffer,(campo->tamanho+1)*2) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONS_MENU);
     return(FALSE);
    }

 campoedit.pegacaracter = VD_lepos;
 campoedit.col      = (*campos)->col;
 campoedit.lin      = (*campos)->lin;
 campoedit.tamanho  = campo->tamanho;
 campoedit.tipo     = ((campo->tipo != VIDEO_CAMPO_STRING) &&
                       (campo->tipo != VIDEO_CAMPO_CARACTER));
 campoedit.tabskip  = campo->tabskip;
 campoedit.buffer   = buffer;
 campoedit.cor      = campo->entrada;
 campoedit.mascara  = campo->mascara;
 campoedit.decimais = campo->decimais;

 campoedit.autos =
 (campo->autos&VIDEO_EDITA_AUTOSKIP)                         |
 (campoedit.decimais ? campo->autos&VIDEO_EDITA_EDPONTO : 0) |
 (campo->autos&VIDEO_EDITA_AUTOIMP)                          |
 (campo->autos&VIDEO_EDITA_AUTOSKIP)                         |
 (campo->autos&VIDEO_EDITA_AUTOBLANK)                        |
 (campo->autos&VIDEO_EDITA_SINALMENOS)                       |
 (campo->autos&VIDEO_EDITA_SINALMAIS)                        |
 (campo->autos&VIDEO_EDITA_LSPACE)                           |
 (campo->autos&VIDEO_EDITA_LZEROS)                           |
 (campo->autos&VIDEO_EDITA_LIMPMASC)                         |
 (campo->autos&VIDEO_EDITA_EDTMASC)                          |
 (campo->autos&VIDEO_EDITA_VALOR)                            ;

 tamanho = min(campoedit.tamanho,strlen(menu->opcoes[menu->opselec-1]))+1;

 VIDEO_movbloco(buffer,menu->opcoes[menu->opselec-1],tamanho);

 VIDEO_movbloco(buffer+campoedit.tamanho+1,
                menu->opcoes[menu->opselec-1],tamanho);

 *(buffer+campoedit.tamanho) =
 *(buffer+((campoedit.tamanho*2)+1)) = '\0';

 VIDEO_TELA_consiste_saida(&campoedit,*campos,buffer+campoedit.tamanho+1);

 if (campoedit.mascara)
    VIDEO_TELA_monta_buffer_mascara(&campoedit,
       campo->buffer_binario,campo->tipo,
       (*campos)->saida);
  else
   {
    VIDEO_CLEAR_PIC(campoedit.col,campoedit.col+campoedit.tamanho-1,
             campoedit.lin,campoedit.lin,(*campos)->saida);
    VD_tprt_l(campoedit.col,campoedit.lin,buffer,(*campos)->saida);
   }

 VIDEO_FREE_ALLOC_MEM(buffer);
 return(FALSE);
}


