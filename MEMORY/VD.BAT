@ECHO OFF
IF "%1" == "" GOTO ERRO1
ECHO 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴쩡컴컴컴컴컴�
ECHO � ADN - Compiler/Linker - UTILITARIOS   쿣ersao 2.00�
ECHO 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴좔컴컴컴컴컴�
d:\BC45\BIN\BCC -mh -3 -Y -P-C -f87 -d -O -G -Z -c -I.;..\VDMACROS %1 %2 %3
IF ERRORLEVEL 1               GOTO ERRO2
d:\BC45\BIN\TLINK d:\BC45\LIB\c0h.obj %1 %2 %3,%1,,@TESTE.ALL
IF ERRORLEVEL 1               GOTO ERRO2



GOTO FIM
:ERRO1
ECHO 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
ECHO � ADN - Compiler/Linker          === ERRO ===       �
ECHO 쳐컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
ECHO � VOCE DEVE ESTABELECER O NOME DO ARQUIVO           �
ECHO � PARA COMPILACAO/LINK-EDICAO....                   �
ECHO 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
GOTO FIM

:ERRO2
ECHO 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
ECHO � ERRO EM EXECUCAO - Operacao Abortada              �
ECHO 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
ECHO .

:FIM
delet

