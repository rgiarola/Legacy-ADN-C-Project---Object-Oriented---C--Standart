@ECHO OFF
REM ==========================================
REM Arquivo de Geracao Biblioteca - ADN
REM ==========================================

rem ECHO ===================================================================
rem ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( ADMEM )))))
rem ECHO ===================================================================
rem IF NOT %1N == N make -fADMEM >>ERROS
rem IF %1N == N     make -fADMEM
rem IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( CARGA )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fCARGA >>ERROS
IF %1N == N     make -fCARGA
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( ARVORE )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fARVORE >>ERROS
IF %1N == N     make -fARVORE
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( BOX )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fBOX >>ERROS
IF %1N == N     make -fBOX
IF ERRORLEVEL 1    GOTO FIM;


rem ECHO ===================================================================
rem ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( DOSMEM )))))
rem ECHO ===================================================================
rem IF NOT %1N == N make -fDOSMEM >>ERROS
rem IF %1N == N     make -fDOSMEM
rem IF ERRORLEVEL 1    GOTO FIM


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( EDITA )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fEDITA >>ERROS
IF %1N == N     make -fEDITA
IF ERRORLEVEL 1    GOTO FIM


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( GERAIS )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fGERAIS >>ERROS
IF %1N == N     make -fGERAIS
IF ERRORLEVEL 1   GOTO FIM


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( GERWIN )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fGERWIN >>ERROS
IF %1N == N     make -fGERWIN
IF ERRORLEVEL 1   GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( MENU )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N CALL make -fMENU >>ERROS
IF %1N == N     CALL make -fMENU
IF ERRORLEVEL 1    GOTO FIM;


rem ECHO ===================================================================
rem ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( PARAM )))))
rem ECHO ===================================================================
rem IF NOT %1N == N make -fPARAM >>ERROS
rem IF %1N == N     make -fPARAM
rem IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( PESQUISA ))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fPESQUISA >>ERROS
IF %1N == N     make -fPESQUISA
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( TECLADO )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fTECLADO >>ERROS
IF %1N == N     make -fTECLADO
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( TELA )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fTELA >>ERROS
IF %1N == N     make -fTELA
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( IFIL )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fIFIL >>ERROS
IF %1N == N     make -fIFIL
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( MOUSE )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fMOUSE >>ERROS
IF %1N == N     make -fMOUSE
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( MASCARA )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N CALL make -fMASCARA >>ERROS
IF %1N == N     CALL make -fMASCARA
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( VISUALIZACAO )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fVISUAL >>ERROS
IF %1N == N     make -fVISUAL
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( RTREE )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fRTREE >>ERROS
IF %1N == N     make -fRTREE
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( GRI )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fGRI >>ERROS
IF %1N == N     make -fGRI
IF ERRORLEVEL 1    GOTO FIM;


ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( CALCULAD )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fCALCULAD >>ERROS
IF %1N == N     make -fCALCULAD
IF ERRORLEVEL 1    GOTO FIM;

ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - DIRETORIO (((( LOGIC )))))
ECHO ===================================================================
if exist \APP\bc45\BIN\BCDEF.CSM DEL \APP\bc45\BIN\BCDEF.CSM
if exist \APP\bc45\BIN\TCDEF.SYM DEL \APP\bc45\BIN\TCDEF.SYM
IF NOT %1N == N make -fLOGIC>>ERROS
IF %1N == N     make -fLOGIC
IF ERRORLEVEL 1    GOTO FIM;

ECHO ===================================================================
ECHO CHECK/ATUALIZACACAO - ((((   BIBLIOTECA     ))))
ECHO ===================================================================

CALL DELET

REM (((((   TERMINA TUDO OK....   )))))
GOTO TUDO_OK;

:FIM
ECHO -------- ERRO EM make FILES ---------
PAUSE

:TUDO_OK
ECHO ON
CALL DELET
DEL *.AA*

