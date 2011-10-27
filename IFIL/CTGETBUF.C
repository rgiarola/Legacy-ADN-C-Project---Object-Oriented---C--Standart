/* ============================================================================
   CTREE_getbuf() - Consegue o buffer de uma variavel DODA.
   GETBUF()       - Nome abreviado.
   RETORNA:
        Em erro retorna o buffer inicial do video, e imprime mensagem.
        Quando tudo OK, retorna endereco do buffer doda.
   ============================================================================ */
#include <INCVIDEO.H>

char *CTREE_getbuf( doda_nome )
char *doda_nome;
{
 IDE_DODA *auxdoda;
 char far *ptrvideo;

 ptrvideo = VIDEO_FISICO(1,1);

 if((auxdoda=CTREE_dodaend(doda_nome)) == VD_NULO )
   {
    char buffer[200];
    sprintf(buffer,CTREE_mens_getbuf,doda_nome);
    VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_getbuf_doda);
    return( ptrvideo );
   }

 return(auxdoda->fadr);
}

