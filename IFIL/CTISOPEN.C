/* ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³   ABRE ARQUIVOS ISAM TEMPORARIOS.                                        ³
   ³   Usa os algoritmos C-TREE para criacao de arquivos ISAM.                ³
   ³   Estes arquivos poderao ter qualquer extensao, e assim serem usados     ³
   ³   como arquivos temporarios.                                             ³
   ³   PARAMETROS:                                                            ³
   ³   ifilptr   -> Poneteiro para estrutura IFIL de controle.                ³
   ³                                                                          ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ */
#include <INCVIDEO.H>
#define CTPERM
#include "ctisam.h"
#include "cterrc.h"
/*
 Nova Vers„o
#define SKIPDATA OPS_SKPDAT
 */

COUNT CTREE_opentmp(ifilptr, aux_tempor)
IDE_ARQUIVOS       *ifilptr;
CT_TMP_NOMES       *aux_tempor;
{
	FAST COUNT   i;
	COUNT	     filno,nm;
	NINT	     dtmap_flg;
    TEXT         nambuf[MAX_NAME + 4];
    /*pIFIL        ifilptr = pifilblk->ptr_ifil;*/
#ifdef RTREE
	pCTIS1	   pis1;
#endif

    isam_err = 0;
    if (ifilptr->dfilmod & SKIPDATA)
     {
      filno     = ifilptr->tfilno;
      dtmap_flg = 0;
     }
    else
     {
      ifilptr->tfilno = -1;
      dtmap_flg   = 2;
      /*ifilptr->dfilno*/
      if ((filno = filrng(-1,ifilptr->dnumidx,
                          ifilptr->dfilmod)) < 0)
          return(-filno);
/*
       else
        {
         VD_gtxy(1,6);
         printf("NUMERO ENCONTRADO (OPEN) %d",filno);
         getch();
        }
*/
     }

    if (ifilptr->dnumidx > MAX_DAT_KEY)
		return(ierr(IDRK_ERR,filno));


    if (!(ifilptr->dfilmod & SKIPDATA))
     {
      /* Abre o arquivo.*/
      strcpy(nambuf, aux_tempor->temp_nome );
      if ( OPNFIL(filno,nambuf,ifilptr->dfilmod) )
         return(ierr(uerr_cod,filno));
     }

    /* ====================================================
       Abre o Arquivo INDICE.
       ==================================================== */
    if (ifilptr->dnumidx > 0)
     {
      /*ctiflnam(pifilblk,nambuf,1,NULL);*/
      strcpy(nambuf, (aux_tempor+1)->temp_nome );
/*      printf("NOME DOS ARQUIVOS %s %s",aux_tempor->temp_nome, nambuf);*/

      if( (i = OPNFIL(filno + 1,nambuf,ifilptr->ifilmod))!=0)
       {
        /* Fecha o arquivo e retorna.*/
        CLSFIL(filno,ifilptr->dfilmod);
        return(ierr(i,filno + 1));
       }

      if ((ctkey(filno + 1))->nmem != ifilptr->dnumidx - 1)
       {
        ierr(INIX_ERR,filno);
        goto err_opnifil;
       }

     }

#ifdef CTSUPER
	if (ifilptr->dfilmod & SUPERFILE)
		nm = 1;
	else
#endif
	 nm = ifilptr->dnumidx;

	for (i = 0; i <= nm; i++)
        ct_dtmap(filno + i) = YES + dtmap_flg;

#ifdef RTREE
	pis1   = &ctis1[filno];
#ifdef RESOURCE
    if (!dtmap_flg)
     {
      if (((eusrdat(filno).fldnam[1] = ctrtnam(ifilptr->rfstfld))
          == NULL  && ifilptr->rfstfld) ||
          ((eusrdat(filno).fldnam[2] = ctrtnam(ifilptr->rlstfld))
          == NULL && ifilptr->rlstfld))
       {
          ierr(IDMU_ERR,filno);
          goto err_opnifil;
       }
     }
    else
     {
#endif /* RESOURCE*/
      eusrdat(filno).fldnam[1] = ifilptr->rfstfld;
      eusrdat(filno).fldnam[2] = ifilptr->rlstfld;
#ifdef RESOURCE
     }
#endif /* RESOURCE*/
#endif /* RTREE*/

    ifilptr->tfilno = filno;
    for (i = 0; i < ifilptr->dnumidx; i++)
      {
       if (setimap(i,ifilptr))
           goto err_opnifil;
      }

    if ( i < MAX_DAT_KEY )
		ct_kymap(filno,i) = -1;

	return(NO_ERROR);


err_opnifil:
    /* only can get here if at least one index file*/
	ifilptr->tfilno = -1;
	CLSFIL(filno,ifilptr->dfilmod);
	CLSFIL(filno + 1,ifilptr->ifilmod);

    for (i = 0; i <= ifilptr->dnumidx; i++)
		ct_dtmap(filno + i) = NO;

    return(isam_err);

}
/* FIM DE FUNCAO OPEN TMP  ====================================================*/

