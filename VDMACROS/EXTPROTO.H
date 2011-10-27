/*  ===========================================================================
    extproto.h  -   Prototipos de Funcoes da extendida biblioteca ctree.
    =========================================================================== */

/* Rotinas de Inicializacao.*/
INT2             CTREE_inicializa(IDE_DODA *, IDE_ARQUIVOS *);
INT2             CTREE_open   (VOID);
INT2             CTREE_erroreb_rede(INT2);

INT2             CTREE_open2  (IDE_ARQUIVOS *, char *,char *,char *,char *,INT2);
INT2             CTREE_deltmp (INT2 numero_arquivo);

COUNT            CTREE_opentmp(IDE_ARQUIVOS *,  CT_TMP_NOMES *);
COUNT            CTREE_criatmp(IDE_ARQUIVOS *,  CT_TMP_NOMES *);
INT2             CTREE_closetmp(INT2 );
INT2             CTREE_temp(IDE_ARQUIVOS *);


/* Rotinas de Manipulacao de Estruturas de Controle.*/
IDE_DODA       *CTREE_dodaend( char *);
IDE_ARQUIVOS   *CTREE_ifilend( INT2   );
char           *CTREE_getbuf ( char *);
INT2             CTREE_filnm  ( char * , INT2);
char           *CTREE_filbuf (INT2    );
INT2             CTREE_inbuf  (INT2    );

INT2             CTREE_keynm (char *);
INT2             CTREE_keyfil(INT2 );
INT2             CTREE_tmpkey(INT2 );
INT2             CTREE_tmpfil(INT2 );

/* Rotinas de Manipulacao de Dados em Arquivo.*/
INT2             CTREE_adrec (INT2 );
INT2             CTREE_advrec(INT2,char *, VRLEN);
INT2             CTREE_rdvlen(INT2,char *, VRLEN);
INT2             CTREE_dlrec (INT2 );
INT2             CTREE_dlall(INT2 ,VIDEO_SEG_CHAVE *,INT2 (_CDECL *)());

INT2             CTREE_rewrec(INT2 );
INT2             CTREE_rwvrec(INT2,char *, VRLEN);
INT2             CTREE_readrec(INT2,char *, INT2 );
INT2             CTREE_lterec(INT2, char *, INT2 );
INT2             CTREE_gterec(INT2, char *, INT2 );

INT2             CTREE_setfrs(INT2, char *, INT2, INT2 );
INT2             CTREE_setlst(INT2, char *, INT2, INT2 );
INT2             CTREE_setnxt(INT2, INT2 );
INT2             CTREE_setprv(INT2, INT2 );

INT2             CTREE_frsrec(INT2, INT2 );
INT2             CTREE_prvrec(INT2, INT2 );
INT2             CTREE_nxtrec(INT2, INT2 );
INT2             CTREE_lstrec(INT2, INT2 );

INT2             CTREE_cmpchave( INT2, VIDEO_SEG_CHAVE *, INT2);
INT2             CTREE_getchave( INT2, char * , INT2);
INT2             CTREE_find    ( INT2, VIDEO_SEG_CHAVE *, INT2, INT2);
VOID            CTREE_cpydoda(VIDEO_TRANSP_DADOS *transpdados);

DATET           datein(COUNT ano,COUNT mes,COUNT dia);
COUNT           dateout(DATET data,COUNT *ano,COUNT *mes,COUNT *dia,COUNT *sem);
INT2             CTREE_copy(INT2 , INT2 ,VIDEO_SEG_CHAVE *,INT2 , INT2 (_CDECL *)());

INT2             RTREE_exec(char *, char *,char *);
char			 *CTREE_posicao_arq(int arquivo,int serv,char *buffer);

INT2             CTREE_adlog(INT2 arquivo);

