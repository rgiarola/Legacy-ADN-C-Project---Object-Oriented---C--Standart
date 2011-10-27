# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "GRI".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\GRI


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio TELA
#       $(LIB)\VDTELSTP.OBJ   -> Objeto de Dados Invalido.......
OBJETOS_TELA: \
        $(LIB)\VDGRIRTT.OBJ           \
        $(LIB)\VDGRIRTF.OBJ           \
        $(LIB)\VDMLHH.LIB


# <<<<<<<<<<   Diretorio BOX.   >>>>>>>>>>
$(LIB)\VDGRIRTT.OBJ: \
        $(SOURCE)\VDGRIRTT.C

        $(COMP_HH) $(SOURCE)\VDGRIRTT.C

$(LIB)\VDGRIRTF.OBJ: \
        $(SOURCE)\VDGRIRTF.C

        $(COMP_HH) $(SOURCE)\VDGRIRTF.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDGRIRTT.OBJ           \
	$(LIB)\VDGRIRTF.OBJ
        TLIB VDMLHH.LIB @GRI.RSP > 11

# =============================================================================
#
#      Fim de Make File - DIRETORIO "GRI" (Padronizacao de Funcoes).
#
# =============================================================================
