












		/**********************************************************************************************/
		/*											      */
		/* 		          M  O  D  U  L  O       G  R  Y  B  C  .  H      		      */
		/*											      */
		/**********************************************************************************************/
		/*											      */
		/*   Descricao : Este modulo contem o lay-out da area de comunicacao do GRI para programas    */
		/*		 em "C". Nesta area, o programa da/recebe informacoes ao/do GRI  relativas    */
		/*		 'as funcoes a executar/executadas pelo GRI.				      */
		/*											      */
		/**********************************************************************************************/



/**********************************************************************************************/
/*											      */
/*     CONSTANTES RELACIONADAS AO "BCT70" - Area de Comunicacao GRI-Programa de Apliacao      */
/*											      */
/**********************************************************************************************/


/*  ---------   BCT70AP	  ---------  	 *  status da aplicacao para estatistica	      */
#define		BCT70APS	'S'	/** indica execucao normal do programa		      */
#define		BCT70APN	'N'	/** indica que o programa nao foi executado	      */
#define		BCT70APX	'X'	/** indica erro imprevisto na execucao		      */

/*  ---------   BCT70CT   ---------	 *  controle de conexao do terminal 		      */
#define		BCT70CTI	'I'	/** identifica conexao ou reconexao do terminal       */

/*  ---------   BCT70CWR  ---------      *  comando de erase/write para 3270		      */
#define		BCT70CF1	'1'	/** indica escrever a partir do cursor		      */
#define		BCT70CF5	'5'	/** indica limpar tela e escrever do inicio	      */

/*  ---------   BCT70IO   ---------  	 *  comando APLicacao==>SIAD sobre atual. em arquivos */
#define		BCT70IOL	'S'	/** indica que o SIAD deve efetivar atualizacoes      */
#define		BCT70IOD	'N'	/** indica que o SIAD deve desfazer atualizacoes      */

/*  ---------   BCT70MA   ---------      *  comando GRI<==>APLicacao  	    quem seta =(XXX)  */
#define		BCT70MAI	'I'	/** indica inicio da transacao		       (GRI)  */
#define		BCT70MAC	'C'	/** indica continuacao da transacao	       (APL)  */
#define		BCT70MAF	'F'	/** indica final da transacao		       (APL)  */
#define		BCT70MAG	'G'	/** gerar transacao - se erro reativa mae      (APL)  */
#define		BCT70MAJ	'J'	/** gerar transacao - se erro nao reativa mae  (APL)  */
#define		BCT70MAH	'H'	/** ind. que transacao foi ativada via geracao (GRI)  */
#define		BCT70MAV	'V'	/** ind. a transacao mae que a filha deu erro  (GRI)  */
#define		BCT70MAT	'T'	/** ind. que transacao foi ativada via STRANS  (GRI)  */

/*  ---------   BCT70TCL  ---------      *  tecla de entrada de dados pressionada pelo usuario*/
#define		BCT70TCLCR	0x27	/** foi teclado <ENTER>		*/
#define		BCT70TCLF1	0x31	/** foi teclado <F1>		*/
#define		BCT70TCLF2	0x32	/** foi teclado <F2>		*/
#define		BCT70TCLF3	0x33	/** foi teclado <F3>		*/
#define		BCT70TCLF4	0x34	/** foi teclado <F4>		*/
#define		BCT70TCLF5	0x35	/** foi teclado <F5>		*/
#define		BCT70TCLF6	0x36	/** foi teclado <F6>		*/
#define		BCT70TCLF7	0x37	/** foi teclado <F7>		*/
#define		BCT70TCLF8	0x38	/** foi teclado <F8>		*/
#define		BCT70TCLF9	0x39	/** foi teclado <F9>		*/
#define		BCT70TCLF10	0x3A	/** foi teclado <F10>		*/
#define		BCT70TCLF11	0x23	/** foi teclado <F11>		*/
#define		BCT70TCLF12	0x40	/** foi teclado <F12>		*/

/*  ---------   BCT70TIP  ----------     * tipo do terminal (ASCII)	*/
#define		BCT70T03	"03"	/** tipo 3270 (invertido)	*/
#define		BCT70T30	"30"	/** tipo PDV  (invertido)	*/




/**********************************************************************************************/
/*											      */
/*	        LAY-OUT  DO  "BCT70" - Area de Comunicacao GRI-Programa de Apliacao           */
/*											      */
/**********************************************************************************************/


struct	bct70

	{

	char	bct70ct;		/* controle de conexao do terminal			*/
	char	bct70nme[8];		/* nome logico do terminal				*/
	char	bct70nez[2];		/* nr da entrada do terminal no concentrador (zonado)   */
	char	bct70tip[2];		/* tipo do terminal (tt)				*/
	char	bct70hdw[2];		/* versao offline (ff)					*/
	char	bct70sfw[2];		/* versao online  (oo)					*/
	char	bct70ctr[3];		/* codigo da transacao					*/
	char	bct70ma;		/* comando GRI<==>APLicacao				*/
	char	bct70cfm[2];		/* codigo formato input/output				*/
	char	bct70io;		/* comando APLicacao==>SIAD sobre atual. em arquivos	*/
	char	bct70ap;		/* status da aplicacao para estatistica			*/
	int	bct70res;		/* tamanho real da msg resposta				*/
	char	bct70clo[4];		/* nr da agencia origem					*/
	char	bct70nut[5];		/* nr do terminal					*/
	char	bct70cld[4];		/* nr da agencia destino				*/
	char	bct70cpd;		/* nr da CPU destino					*/
	char	bct70cfn[2];		/* formato input (3270)					*/
	char	bct70tcl;		/* indica tecla pressionada (3270)			*/
	char	bct70cwr;		/* comando de erase/write   (3270)			*/
	char	bct70fd;		/* formata resp nesta CPU ou na ag do terminal		*/
	char	bct70fil[8];		/* filler						*/

	};

