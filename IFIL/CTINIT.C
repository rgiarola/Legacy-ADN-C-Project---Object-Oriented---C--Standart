/* ============================================================================
   CTREE_inicializa() - Inicializa o sistema para operacao do ctree
                        conjuntamente com as funcoes extendidas.
        As variaveis de controle e seus respectivos buffer's serao
        inicializados ou criados.
   ============================================================================ */
#include <INCVIDEO.H>

/* ----------------------------------------------------------------------------
    <<<<<<      Variaveis de Controle e                     >>>>>
    <<<<<<      operacao das funcoes extendidas C-tree      >>>>>
   ---------------------------------------------------------------------------- */
/* Variavel de armazenamento da estrura IFIL.*/


IDE_ARQUIVOS    *ATIVO_IFIL[CTREE_MAXFIL+1];  // Controle Estrutura de Arquivos
IDE_DODA        *ATIVO_DODA;                  // Controle Estrutura DODA
CT_TMP_NOMES    *CT_arquivos_temporarios;     // Controle Arquivos Temporarios
CTGVAR          *ctWNGV;                      // Header do Ctree


/*  ---------------------------------------------------------------------------*/

INT2 CTREE_inicializa(init_doda, init_arquivos)
IDE_DODA        *init_doda;
IDE_ARQUIVOS    *init_arquivos;
{
 IDE_ARQUIVOS        **auxifil;
 register INT2        control_datno=0;
 INT2 ret;

 /* <<<< Check de Parametros da Funcao.*/
 if( init_doda == VD_NILL(IDE_DODA) || init_arquivos == VD_NILL(IDE_ARQUIVOS) )
     {   /* Erro em passagem de Parametros.*/
         return( I(-1) );
     }


 /* Inicializa a Estrutura de Controle "IDE_ARQUIVOS".*/
 auxifil = ATIVO_IFIL;
 control_datno=0;
 while( init_arquivos->pfilnam != VD_NULO	&&
        init_arquivos->dreclen != VD_NULO )
  {
//	 printf("%s\n",init_arquivos->pfilnam);
   *auxifil = init_arquivos;
   (*auxifil)->dfilno = control_datno;       /* Inicializa o Identificador*/
   (*auxifil)->tfilno = -1;
   control_datno += ((*auxifil)->dnumidx+1); /* Proximo Identificador.*/

   ++init_arquivos;
   ++auxifil;
  }
 *auxifil = VD_NILL(IDE_ARQUIVOS);



 /* Inicializa a Estrutura de Controle "IDE_DODA".*/
 ATIVO_DODA = init_doda;


 // Inicializacoes de ARQUIVOS TEMPORARIOS -----------------------------------
 //if ((ret=AdnMemAlocPool (sizeof (CT_TMP_NOMES) * VD_MAX_TMP,
 //                         &CT_arquivos_temporarios))!=FALSE)
 //   {
     if  ( VIDEO_ALLOC_MEM( CT_arquivos_temporarios,
                            (sizeof(CT_TMP_NOMES)*VD_MAX_TMP) ) == FALSE )
     return(-2);
 //   }

 VIDEO_setmem( CT_arquivos_temporarios, sizeof(CT_TMP_NOMES)*VD_MAX_TMP,
               VD_NULO);


 // Inicializacoes do C T R E E   ============================================
// if ((ret=AdnMemAlocPool (sizeof (CTGVAR),
//                          &ctWNGV))!=FALSE)
//    {
     if (!VIDEO_ALLOC_MEM( ctWNGV, sizeof(CTGVAR)) )
        {
         VIDEO_mostra_mens_erro_alloc(-1000);
         return(FALSE);
        }
//    }
 VIDEO_setmem(  ctWNGV, sizeof(CTGVAR), VD_NULO );


 if (DATABASE_logsis())     /* Inicializa o Sistema Ctree.*/
     return(TRUE);

 return( I(FALSE) );
}

