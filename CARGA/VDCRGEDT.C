#include <INCVIDEO.H>

INT2 VIDEO_enddodatela(campos,num)
VIDEO_CAMPO_TELA *campos;
INT2              num;
{
 IDE_DODA *doda;

 while(num)
  {
   if ((doda = CTREE_dodaend(campos->dodacampo)) == VIDEO_NILL(IDE_DODA))
      {
       char buflocal[100];
       sprintf(buflocal,VIDEO_CARGA_mens_end_dodatela,campos->dodacampo);
       VIDEO_mostra_mens_erro(buflocal,VIDEO_ERRO_doda_nao_encontrado);
       return(FALSE);
      }

   campos->buffer_binario = PTR_CAST(char,doda->fadr)+
                                   campos->offsetbuffer;
   ++campos;
   --num;
  }
 return(TRUE);
}

