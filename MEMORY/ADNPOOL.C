/* ----------------------------------------------------------------------------
   Fun‡”es de aloca‡„o Avan‡ada (EMM->HIMEM.SYS)

   AdnMemPreparaPool    -> Prepara‡„o do POOL
   AdnMemLiberaPool     -> Libera‡„o do POOL
   AdnMemAlocPool       -> Aloca‡„o de Mem¢ria
   AdnMemSituacao       -> Situa‡„o da Aloca‡„o


   ---------------------------------------------------------------------------- */
#ifdef  MODULO_MEMORIA
#ifndef MODULO_INCLUSAO
#include <INCVIDEO.H>
#endif
#include <adnmem.h>

char *AdnBasePointerAddress;     // Ponteiro Base
static char  AdnMemPreparado = FALSE;   // Flag de Controle Prepara‡„o
static unsigned int
             AdnMemHandlePool= -1,      // Handle do POOL
             AdnMemContador  =  0;      // Contador de Aloca‡”es
static DWORD AdnMemMaximo,              // Tamanho em Bytes do POOL
             AdnMemPosicao;             // Posi‡„o Crescente no POOL

/* ----------------------------------------------------------------------------
   Prepara
   P O O L
   > Chamada Obrigat¢ria, Prepara Inicializa‡„o
   ---------------------------------------------------------------------------- */
INT2 AdnMemPreparaPool (DWORD Bytes)
{
 INT2 Paginas,
      PaginasLivres,
      PaginaFisica,
      PaginaLogica,
      Ret;
 int  segmento,
      offset;
  unsigned long errcode, nobytes, xaddress, xsize, xhandle;

 Paginas = (Bytes+16) / PAGINA_PADRAO;      // Espa‡O para 16 Bytes ...
 if ((Paginas*PAGINA_PADRAO)< (Bytes+16))
	++Paginas;

 printf ("\n Alocando %d Paginas para %ldKBytes",Paginas,Bytes/1024L);
/*
 Ret = INITXLIB();         //Initialize XLIB
  if(Ret != 0)
  {
    return (ADNMEM_ERRO_NOEMM );
  }

 Ret = XMALLOC(Bytes, &xaddress, &xsize, &xhandle);
 if (Ret)
    {
     return (ADNMEM_ERRO_SEMMEM);
    }

 AdnBasePointerAddress = (char *)xaddress;
 */


 // Incializando Controles
 // ---------------------------------------------------------------------------
 if ((Ret=ADNEmmInicializa())!=TRUE)
	{
	 if (Ret==-1)
		return (ADNMEM_ERRO_JAINIC);
	  else
        return (ADNMEM_ERRO_NOEMM );
	}

 // C lculo Espa‡o Dispon¡vel
 // ---------------------------------------------------------------------------
 if (!ADNEmmPaginasLivres(Paginas,&PaginasLivres))
	{
	 return (ADNMEM_ERRO_SEMMEM);
	}

 // Alloca‡„o de Mem¢ria
 // ---------------------------------------------------------------------------
 if (!ADNEmmAlocaPaginas(Paginas,&AdnMemHandlePool))
	{
     return (ADNMEM_ERRO_ALLOC);
	}

 // L¢gica MAP -> Onde Estar„o as P ginas?
 // ---------------------------------------------------------------------------
 PaginaFisica = 0;
 PaginaLogica = 0;
 /*
 if (!ADNEmmMapPaginas(AdnMemHandlePool, PaginaFisica, PaginaLogica))
    {
     return (ADNMEM_ERRO_MAP);
    }
   */

 /*
  L¢gica Ativa
 */
 for (Ret=0;Ret<Paginas;Ret++)
    {
     if (!ADNEmmMapPaginas(AdnMemHandlePool, PaginaFisica, Ret))
        {
         printf ("\n ** Map **");getch();
         return (ADNMEM_ERRO_MAP);
        }
    }

 // PageFrame -> Localiza‡„o BASE
 // ---------------------------------------------------------------------------
 if (!ADNEmmGetFrameAdres(&AdnBasePointerAddress))
	{
	 return (ADNMEM_ERRO_PAGEFRAME);
	}
 printf ("PaF %p",AdnBasePointerAddress); getch();

 /*
 segmento = FP_SEG (AdnBasePointerAddress);
 offset   = FP_OFF (AdnBasePointerAddress);

 AdnBasePointerAddress = MK_FP(segmento+(0x400 * PaginaFisica),offset);
 */
 /*
 AdnBasePointerAddress = MK_FP(0x5000,0);
  */

 // Flag de Prepara‡„o énica
 // ---------------------------------------------------------------------------
 AdnMemMaximo	 = DW (Paginas*PAGINA_PADRAO);
 AdnMemPosicao	 = 0L;
 AdnMemPreparado = TRUE;

 return (FALSE);
}

/* ----------------------------------------------------------------------------
   Finaliza/Libera
   P O O L
   > Chamada Obrigat¢ria, Antes de Sair do Programa
   ---------------------------------------------------------------------------- */
INT2 AdnMemLiberaPool (void)
{
 if (!AdnMemPreparado)
    return (ADNMEM_ERRO_NAOINIC);
/*
 if (!ADNEmmDesalocaPaginas(AdnMemHandlePool))
	return (ADNMEM_ERRO_LIBERA);
 */

 return (FALSE);
}

/* ----------------------------------------------------------------------------
   Alloc/Separa
   P O O L
   > Rotina de Aloca‡„o ADNMEM
   ---------------------------------------------------------------------------- */
INT2 AdnMemAlocPool (DWORD Bytes, char **PonteiroAlloc)
{
 int Segmento, Offset;

 if (!AdnMemPreparado)
    return (ADNMEM_ERRO_NAOINIC);

 if (Bytes > 4*(PAGINA_PADRAO)-4)
    return (ADNMEM_ERRO_SEG16);

 *PonteiroAlloc = VD_NULO;

 if (Bytes > (AdnMemMaximo-AdnMemPosicao))
    return (ADNMEM_ERRO_ALLOCPOOL);

 Segmento = FP_SEG (AdnBasePointerAddress) ;
 Offset   = FP_OFF (AdnBasePointerAddress) + AdnMemPosicao + 4;

 *PonteiroAlloc = MK_FP (Segmento,Offset);
 // (AdnBasePointerAddress+AdnMemPosicao);

 AdnMemPosicao += (Bytes+4);// Incrementa Posi‡„o
 ++AdnMemContador;          // Incrementa No. Aloca‡”es

 return (FALSE);
}

/* ----------------------------------------------------------------------------
   Estat¡sticas
   P O O L
   > Retorna Contador de Aloca‡”es, M ximo Permitido e Espa‡o Livre (Dispon¡vel)
   ---------------------------------------------------------------------------- */
INT2 AdnMemSituacao(DWORD *Contador, DWORD *Maximo, DWORD *Livre)
{
 if (!AdnMemPreparado)
    return (ADNMEM_ERRO_NAOINIC);

 *Contador = AdnMemContador;
 *Maximo   = AdnMemMaximo  ;
 *Livre    = AdnMemMaximo - AdnMemPosicao;

 return (FALSE);
}
#endif
