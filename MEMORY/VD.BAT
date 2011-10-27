@ECHO OFF
IF "%1" == "" GOTO ERRO1
ECHO здддддддддддддддддддддддддддддддддддддддбддддддддддд©
ECHO Ё ADN - Compiler/Linker - UTILITARIOS   ЁVersao 2.00Ё
ECHO юдддддддддддддддддддддддддддддддддддддддаддддддддддды
d:\BC45\BIN\BCC -mh -3 -Y -P-C -f87 -d -O -G -Z -c -I.;..\VDMACROS %1 %2 %3
IF ERRORLEVEL 1               GOTO ERRO2
d:\BC45\BIN\TLINK d:\BC45\LIB\c0h.obj %1 %2 %3,%1,,@TESTE.ALL
IF ERRORLEVEL 1               GOTO ERRO2



GOTO FIM
:ERRO1
ECHO зддддддддддддддддддддддддддддддддддддддддддддддддддд©
ECHO Ё ADN - Compiler/Linker          === ERRO ===       Ё
ECHO цддддддддддддддддддддддддддддддддддддддддддддддддддд╢
ECHO Ё VOCE DEVE ESTABELECER O NOME DO ARQUIVO           Ё
ECHO Ё PARA COMPILACAO/LINK-EDICAO....                   Ё
ECHO юддддддддддддддддддддддддддддддддддддддддддддддддддды
GOTO FIM

:ERRO2
ECHO зддддддддддддддддддддддддддддддддддддддддддддддддддд©
ECHO Ё ERRO EM EXECUCAO - Operacao Abortada              Ё
ECHO юддддддддддддддддддддддддддддддддддддддддддддддддддды
ECHO .

:FIM
delet

