/* ============================================================================
    CTREE_dodaend() - Consegue o endereco do buffer de dados, apartir do nome
                      do DODA do campo.
    DODAEND()       - Nome abreviado.
    PARAMETRO:      nome_campo
    RETORNA:        Retorna o ponteiro (char *) do buffer, se nao encontrado
                    retorna NULL.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 VIDEO_testa_nome_doda_pesquisa_binaria();

IDE_DODA *CTREE_dodaend(nome_campo)
char     *nome_campo;
{
 INT2        num_doda,cont,*tab;
 static INT2 ultimos_dodas[5]={-1,-1,-1,-1,-1};
 char        buffer[200];

 if ( nome_campo == VD_NILL(char) )       /* Nome do Campo invalido.*/
	 return(VD_NILL(IDE_DODA *));

 for (cont = 0,tab = ultimos_dodas;(cont < 5) && (*tab > -1);cont++,tab++)
      if (!strcmp(nome_campo,(*(VIDEO_tabela_doda+*tab))->fsymb))
         {
          if (cont)
             {
              cont = *tab;
              *tab = *ultimos_dodas;
              *ultimos_dodas = cont;
             }
          return(*(VIDEO_tabela_doda+*ultimos_dodas));
         }

 if (VIDEO_pesquisa_binaria((char *) VIDEO_tabela_doda,&num_doda,
						VIDEO_testa_nome_doda_pesquisa_binaria,
						VIDEO_bufparamarq->numdoda-1,
                        nome_campo,sizeof(IDE_DODA *),sizeof(IDE_DODA *)))
    {
     VIDEO_copbloco(&ultimos_dodas[1],&ultimos_dodas[0],sizeof(INT2)*4);
     ultimos_dodas[0] = num_doda;
	 return(*(VIDEO_tabela_doda+num_doda));
    }

 sprintf(buffer,"Erro doda [%s]",nome_campo);

 VIDEO_grava_erro(buffer);

 return(VD_NILL(IDE_DODA *));
}

INT2 VIDEO_testa_nome_doda_pesquisa_binaria(nomedoda,doda,tamanho)
char     *nomedoda;
IDE_DODA **doda;
WORD     tamanho;
{
 return(strcmp(nomedoda,(*doda)->fsymb));
}

