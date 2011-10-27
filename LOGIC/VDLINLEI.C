#include<INCVIDEO.H>
#include "VDLINALF.H"

/*===========================================================================
			   PEGALINHA BUFFERIZADA
===========================================================================*/
char *VIDEO_MCLIN_pega_linha(expande)
VIDEO_MCLIN_STR_EXPAND *expande;
{
 int  buffer_ler,tam;
 char *linha,*ini_linha;

 expande->flags &= ~VIDEO_MCLIN_LEU_LINHA;

 do
  {
/*----------------------------------------------------------------------------
                               LE BUFFER
----------------------------------------------------------------------------*/
   if (expande->flags&VIDEO_MCLIN_LER_BUFFER)
	  {
       expande->flags &= ~VIDEO_MCLIN_LER_BUFFER;

       if (expande->posbuffer < expande->lido)
	  {
           VIDEO_copbloco(expande->buffer_leitura,
                          expande->buffer_leitura+expande->posbuffer,
                          expande->lido-expande->posbuffer);
           expande->posbuffer =
                           expande->lido - expande->posbuffer;
          }

       if (expande->flags&VIDEO_MCLIN_FIM_ARQ)
          {
           if (expande->flags&VIDEO_MCLIN_TERMINA)
              return(VD_NULO);
            else
              {
               *(expande->buffer_leitura+expande->lido) = 0X0D;
               expande->flags |= VIDEO_MCLIN_TERMINA;
	      }
          }
        else
          {
	   buffer_ler = 1023 - expande->posbuffer;
           if (buffer_ler > 1023 || buffer_ler < 1)
	       VIDEO_mostra_mens_erro(VIDEO_texto_linguagem,VIDEO_ERRO_LING_tamanho_1);

           if ((expande->lido = VIDEO_read(expande->descritor,
                                     expande->buffer_leitura+expande->posbuffer,
                                    buffer_ler)) <= 0 || expande->lido < buffer_ler)
               expande->flags |= VIDEO_MCLIN_FIM_ARQ;
           expande->lido += expande->posbuffer;
          }

       expande->posbuffer = VD_NULO;
      }

/*----------------------------------------------------------------------------
                            ENCONTRA O FIM DA LINHA
----------------------------------------------------------------------------*/
   expande->linha = expande->buffer_leitura + expande->posbuffer;
   linha = expande->linha;
   buffer_ler = expande->posbuffer;
   do
	{
     ini_linha = linha;
	 while(*linha != 0X0D && *linha != 0X0A && buffer_ler < expande->lido)
	  {
	   ++linha;
       ++buffer_ler;
	  }

     if (buffer_ler >= expande->lido)
		{
         expande->flags |= VIDEO_MCLIN_LER_BUFFER;
         break;
		}

     tam = I(VIDEO_FP_OFF(linha))-I(VIDEO_FP_OFF(expande->buffer_leitura));

     if (tam > 1023 || tam < 0)
         VIDEO_mostra_mens_erro(VIDEO_texto_linguagem,VIDEO_ERRO_LING_analise_1);

     *linha = '\0';

     expande->posbuffer = buffer_ler+1;
     expande->flags |= VIDEO_MCLIN_LEU_LINHA;

     if (expande->posbuffer >= expande->lido)
        {
         expande->flags |= VIDEO_MCLIN_LER_BUFFER;
         expande->posbuffer = expande->lido = VD_NULO;
        }

     break;
    }while(TRUE);

  }while(!(expande->flags&VIDEO_MCLIN_LEU_LINHA));

 return(ini_linha);
}


