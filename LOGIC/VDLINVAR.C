#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
								COMANDOS
 ----------------------------------------------------------------------------
char *VIDEO_LINGUAGEM_tabela_comandos[] = {
                "PROCEDURE" , // DEFINICAO DE PROCEDIMRNTO
                "BEGIN"     , // DEFINICAO DE INICIO DE BLOCO
                "END"       , // DEFINICAO DE FIM DE BLOCO
                "CALL"      , // CHAMADA EXTERNA
                "FUNCTION"  , // CHAMADA DE FUNCAO
                "MAIN"      , // PROCEDIMENTO PRINCIPAL
                "PARAMETERS", // PARAMETROS DA FUNCAO
                "DO"        , // INICIO DE DO WHILE
                "WHILE"     , // WHILE
                "FOR"       , // FOR
                "BREAK"     , // INTERROMPE LOOP
                "CONTINUE"  , // SALTA PARA TESTE DE LOOP
                "SWITCH"    , // TESTE DE CASE
                "CASE"      , // CASE OPCAO
                "IF"        , // TESTE
                "ELSE"      , // SENAO
                "LOCAL"     , // VARIAVEIS LOCAIS
                "VIRTUAL"   , // VARIAVEL DODA VIRTUAL
                "EXTERN"    , // VARIAVEIS DODA GERAIS
                "CONSTANT"  , // CONSTANTE
                "EXIT"      , // RETORNA AO PROGRAMA
                "RETURN"    , // RETORNO NORMAL
                "SEG_CONST" , // SEGMENTO CONSTANTE
                "SEG_CAMPO" , // SEGMENTO CAMPO
                "SEG_CAMPO_CONST", // SEGMENTO CAMPO CONSTANTE
                VD_NULO};
/*----------------------------------------------------------------------------
				  OPERADORES LOGICOS
 ----------------------------------------------------------------------------
char *VIDEO_LINGUAGEM_tabela_operlogic[] = {
                "TRUE"      , // VERDADEIRO
                "FALSE"     , // FALSO
                "&&"        , // PORTA E
                "||"        , // PORTA OU
                "=="        , // IGUAL
                "!="        , // DIFERENTE
                ">"         , // MAIOR
                ">="        , // MAIOR IGUAL
                "<="        , // MENOR IGUAL
                "<"         , // MENOR
                VD_NULO};

/*----------------------------------------------------------------------------
							  OPERADORES ARITIMETICOS
 ----------------------------------------------------------------------------
char *VIDEO_LINGUAGEM_tabela_operarit[] = {
                "+"         , // SOMA
                "+="        , // SOMA REDUZIDO
                "-"         , // SUBTRACAO
                "-="        , // SUBTRACAO REDUZIDO
                "*"         , // MULTIPLICACAO
                "*="        , // MULTIPLICACAO REDUZIDO
                "/"         , // DIVISAO
                "/="        , // DIVISAO REDUZIDO
                "^"         , // EXPONENCIACAO
                "^="        , // EXPONENCIACAO REDUZIDO
                "%"         , // RESTO DA DIVISAO
                "%="        , // RESTO DA DIVISAO REDUZIDO
                "++"        , // INCREMENTO
                "--"        , // DECREMENTO
                VD_NULO};

/*----------------------------------------------------------------------------
				SEPARADORES
 ----------------------------------------------------------------------------
	 *VIDEO_LINGUAGEM_tabela_separadores[] = {
                "{"         ,
                "}"         ,
                "["         ,
                "]"         ,
                "("         ,
                ")"         ,
                VD_NULO};

/*--------------------------------------------------------------------------
				  DELIMITADORES
 ----------------------------------------------------------------------------
	 *VIDEO_LINGUAGEM_tabela_delimitadores[] = {
                "\""        ,
                "\'"        ,
                VD_NULO};

/*--------------------------------------------------------------------------
                           TIPOS DE CAMPOS
 ----------------------------------------------------------------------------
     *VIDEO_LINGUAGEM_tabela_tipodados[] = {
                "BYTE"      ,
                "SHORT"     ,
                "INT2U"     ,
                "INT2"      ,
                "INT4U"     ,
                "INT4"      ,
                "FLOAT"     ,
                "DOUBLE"    ,
                "DATA"      ,
                "HORA"      ,
                "CARAC"     ,
                "STRING"    ,
                "SEGCHAVE"  ,
                "TRANSPDADOS",
                VD_NULO};

/*----------------------------------------------------------------------------
			 CAMPOS DA VARIAVEL DODA
 ----------------------------------------------------------------------------
IDE_DODA->FSYMB          NOME DO CAMPO DODA
IDE_DODA->FADR           BUFFER DO DODA
IDE_DODA->FTYPE          TIPO DO DODA
IDE_DODA->FLEN           TAMANHO DO DODA
-----------------------------------------------------------------------------*/
char *VIDEO_LINGUAGEM_tabela_referencia[] = {
                "FSYMB" ,
                "FADR"  ,
                "FTYPE" ,
                "FLEN"  ,
/*----------------------------------------------------------------------------
			 CAMPOS DA VARIAVEL ARQUIVO
 ----------------------------------------------------------------------------
IDE_ARQUIVOS->PFILNAM    NOME DO ARQUIVO
IDE_ARQUIVOS->DFILNO     NUMERO DO ARQUIVO
IDE_ARQUIVOS->DRECLEN    TAMANHO DO REGISTRO
IDE_ARQUIVOS->DNUMIDX    NUMERO DE INDICES
IDE_ARQUIVOS->IX         INDICES
IDE_ARQUIVOS->RFSTFLD    PRIMEIRO CAMPO DO ARQUIVO
IDE_ARQUIVOS->RLSTFLD    ULTIMO CAMPO DO ARQUIVO
IDE_ARQUIVOS->TFILNO     NUMERO FISICO DO ARQUIVO
-----------------------------------------------------------------------------*/
                "PFILNAM" ,
                "DFILNO"  ,
                "DRECLEN" ,
                "DNUMIDX" ,
                "IX"      ,
                "RFSTFLD" ,
                "RLSTFLD" ,
                "TFILNO"  ,

/*----------------------------------------------------------------------------
			 CAMPOS DA VARIAVEL ARQUIVO
 ----------------------------------------------------------------------------
IDE_INDEX->IKEYLEN       TAMANHO DA CHAVE
IDE_INDEX->IKEYTYP       TIPO DA CHAVE
IDE_INDEX->IKEYDUP       FLAG DUPLICATA
IDE_INDEX->INUMSEG       NUMERO DE SEGMENTOS
IDE_INDEX->SEG           SEGMENTOS
-----------------------------------------------------------------------------*/
                "IKEYLEN" ,
                "IKEYTYP" ,
                "IKEYDUP" ,
                "INUMSEG" ,
                "SEG"     ,

/*----------------------------------------------------------------------------
			 CAMPOS DA VARIAVEL SEGMENTO
 ----------------------------------------------------------------------------
IDE_CHAVES->SOFFSET             OFFSET DO REGISTRO
IDE_CHAVES->SLENGTH             TAMANHO DO SEGMENTO
IDE_CHAVES->SEGMODE             TIPO DO SEGMENTO
-----------------------------------------------------------------------------*/
                "SOFFSET" ,
                "SLENGTH" ,
                "SEGMODE" ,
                VD_NULO};


int  VIDEO_MCLIN_desc_arq = -1;
char VIDEO_MCLIN_nome_arq[VD_MAX_TMP_NOME+1];
char VIDEO_texto_linguagem[] = "Analise Linha";
