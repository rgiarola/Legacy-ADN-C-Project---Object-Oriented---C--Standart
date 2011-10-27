@ECHO OFF
ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( CARGA )))))
ECHO ===================================================================
if exist \APP\BC45\BIN\BCDEF.CSM DEL \APP\BC45\BIN\BCDEF.CSM
if exist \APP\BC45\BIN\TCDEF.SYM DEL \APP\BC45\BIN\TCDEF.SYM
make -fCARGA
IF ERRORLEVEL 1    GOTO FIM;

ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( IFIL )))))
ECHO ===================================================================
if exist \APP\BC45\BIN\BCDEF.CSM DEL \APP\BC45\BIN\BCDEF.CSM
if exist \APP\BC45\BIN\TCDEF.SYM DEL \APP\BC45\BIN\TCDEF.SYM
make -fIFIL
IF ERRORLEVEL 1    GOTO FIM;

ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( pesquisa )))))
ECHO ===================================================================
if exist \APP\BC45\BIN\BCDEF.CSM DEL \APP\BC45\BIN\BCDEF.CSM
if exist \APP\BC45\BIN\TCDEF.SYM DEL \APP\BC45\BIN\TCDEF.SYM
make -fpesquisa
IF ERRORLEVEL 1    GOTO FIM;

ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( TELA )))))
ECHO ===================================================================
if exist \APP\BC45\BIN\BCDEF.CSM DEL \APP\BC45\BIN\BCDEF.CSM
if exist \APP\BC45\BIN\TCDEF.SYM DEL \APP\BC45\BIN\TCDEF.SYM
make -fTELA
IF ERRORLEVEL 1    GOTO FIM;

Goto Tudo_OK;

:FIM
ECHO -------- ERRO EM make FILES ---------
PAUSE

:TUDO_OK
ECHO ON
CALL DELET
DEL *.AA*

