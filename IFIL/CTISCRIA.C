/* ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³   CRIA ARQUIVOS ISAM TEMPORARIOS.                                        ³
   ³   Usa os algoritmos C-TREE para criacao de arquivos ISAM.                ³
   ³   Estes arquivos poderao ter qualquer extensao, e assim serem usados     ³
   ³   como arquivos temporarios.                                             ³
   ³   PARAMETROS:                                                            ³
   ³   ifilptr   -> Poneteiro para estrutura IFIL de controle.                ³
   ³   pos_nomes -> Posicao, no array de controle "CT_arquivos_temporarios",  ³
   ³                onde estao armazenados os nomes do arquivo e do indice.   ³
   ³                                                                          ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ */
#include <INCVIDEO.H>

#ifdef PUTIFIL
#undef PUTIFIL
#endif

#ifdef RESOURCE
#ifndef PUTIFIL
#define PUTIFIL
#endif
#endif

#define CTPERM
#include "ctisam.h"
#include "cterrc.h"

#ifdef PUTIFIL
#include "ctpifl.c"
#endif


COUNT CTREE_criatmp(ifilptr, aux_tempor)
IDE_ARQUIVOS       *ifilptr;
CT_TMP_NOMES       *aux_tempor;
{
	COUNT	     filno,keyno,i;
	TEXT	     nambuf[MAX_NAME];
	pIIDX        idxp;
	pTEXT	     tp;
    TEXT         dext[EXZ];
	TEXT	     iext[EXZ];
/*    pIFIL        ifilptr = pifilblk->ptr_ifil;*/
#ifdef RESOURCE
	DEFDEF	     def;
	VRLEN	     len;
#endif

    /* Verifica se numero do arquivo compativel.*/
    isam_err = 0;
    /*ifilptr->dfilno*/
    if ((filno = filrng(-1, ifilptr->dnumidx,
                        ifilptr->dfilmod)) < 0 )
      {
       char buffer[200];
       sprintf(buffer,CTREE_mens_ctiscria,uerr_cod,filno);
       VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_filnrg_incompativel);
       return(-filno);
      }
/*
    else
      {
        VD_gtxy(1,5);
        printf("NUMERO ARQUIVO ENCONTRADO (CRIA) %d",filno);
      }
*/
    if ( ifilptr->dnumidx > MAX_DAT_KEY )
        return( ierr(IDRK_ERR,filno) );

    /* Prepara o nome do Arquivo.*/
    strcpy(nambuf, aux_tempor->temp_nome );


    /* Cria o Arquivo de DADOS.*/
    if (CREDAT( filno, nambuf, ifilptr->dreclen,
                ifilptr->dxtdsiz, ifilptr->dfilmod) )
		return(ierr(uerr_cod,filno));

    ifilptr->tfilno = filno;    /* Numero CTREE do arquivo.*/

    if (ifilptr->dnumidx > 0)
       {
        /* Prepara o nome do Indice.*/
        strcpy(nambuf, (aux_tempor+1)->temp_nome );

        idxp =  ifilptr->ix;
        if( (i = CREIDX(filno + 1, nambuf,
                        idxp->ikeylen,    idxp->ikeytyp,
                        idxp->ikeydup,    ifilptr->dnumidx-1,
                        ifilptr->ixtdsiz, ifilptr->ifilmod )) != 0)
         {
			ifilptr->tfilno = -1;
            DELFIL(filno);          /* Deleta o Arquivo.*/
			return(ierr(i,filno + 1));
		}

        /* Acrescenta os descritores ISAM do arquivo.*/
		if (setimap(0,ifilptr))
			goto err_creifil;

        for (i = 1; i <= ifilptr->dnumidx; i++)
			ct_dtmap(filno + i) = YES + 2;
       }
    else /* Nao Existem Indices.*/
       {
#ifdef CTSUPER
		if (ifilptr->dfilmod & SUPERFILE)
			ct_dtmap(filno + 1) = YES + 2;
#endif
		ct_kymap(filno,0)  = -1;
	}

	ct_dtmap(filno) = YES + 2;

#ifdef RTREE
    /* Variaveis de Controle (Descritores ISAM do arquivo).*/
    usrdat(filno).fldnam[1] = ifilptr->rfstfld;
	usrdat(filno).fldnam[2] = ifilptr->rlstfld;
#endif


   /* =================================================================
       Cria os Membros Indices do arquivo.
      ================================================================= */
    for (i = 0, keyno = filno + 1; i < ifilptr->dnumidx; i++, keyno++)
      {
       if (i > 0)
        {
          idxp = &ifilptr->ix[i];
          if ( CREMEM(filno + 1,idxp->ikeylen, idxp->ikeytyp, idxp->ikeydup,i) )
              {
                ierr(uerr_cod,filno + i + 1);
				goto err_creifil;
              }
          else
           if (setimap(i,ifilptr) )
				goto err_creifil;
		}
      }

    if (i < MAX_DAT_KEY)
		ct_kymap(filno,i) = -1;

#ifdef RESOURCE
    /* Poem Ressource IFIL para Header de Arquivo*/
    if ( !(ifilptr->dfilmod & DISABLERES) )
       {
        if ((tp = putifil( ifilptr,NULL,&len,dext,iext)) == NULL )
			goto err_creifil;

        def.ddeflen = def.ddeftot = len;
		def.ddefptr = tp;
		def.ddefnum = DEF_IFIL;
		def.ddeftyp = FCRES_DATA;
		SETDEFBLK(ifilptr->tfilno,&def);
		mbfree(tp);

        if ( (isam_err = uerr_cod)!=0 )
           {
			isam_fil = ifilptr->tfilno;
			goto err_creifil;
           }

       }
#endif

	return(NO_ERROR);

err_creifil:
    ifilptr->tfilno = -1;
    for (i = filno; i <= filno + ifilptr->dnumidx; i++)
      {
       ct_dtmap(i) = NO;
       if (i < (filno+2) )
          DELFIL(i);     /* Deleta Arquivo.*/
      }

    return(isam_err);

}
/* FIM DE FUNCAO ---------> Cria arquivos.*/

