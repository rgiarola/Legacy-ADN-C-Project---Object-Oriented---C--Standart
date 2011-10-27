#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO		  :  VIDEO_ARVORE_termina()
 *----------------------------------------------------------------------------
 * Descricao	  :  termina navegacao da arvore
 * Parametros	  :  parametros do nucleo
 * Retorno		  :  FALSE
 * Autor		  :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_termina(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 VIDEO_ARVORE_ESTRUTURA *arvloc;

 arvloc = *arvore;

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo && VIDEO_MOUSE_cursor_ativo)
     VIDEO_MOUSE_deshabcursor();
#endif

 arvloc->servico = FALSE;

 VIDEO_horizontal(arvloc->colf-5,arvloc->colf-1,
                  arvloc->lini,' ',arvloc->cor_titulo);

 if (arvloc->flagsalva&VIDEO_ARVORE_FLAGPOPWIN)
    {
     VD_POPWIN();
#ifdef VIDEO_UNIX
     VIDEO_UNIX_refresh_tela();
#endif
    }

 return(FALSE);
}

