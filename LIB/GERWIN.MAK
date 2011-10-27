# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "GERWIN".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\GERWIN


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio GERWIN
OBJETOS_TELA: \
        $(LIB)\VDGERPOP.OBJ     \
        $(LIB)\VDGERPUS.OBJ     \
        $(LIB)\VDGERWIN.OBJ     \
        $(LIB)\VDGERWVR.OBJ     \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio GERWIN.   >>>>>>>>>>
$(LIB)\VDGERPOP.OBJ: \
        $(SOURCE)\VDGERPOP.C

        $(COMP_HH) $(SOURCE)\VDGERPOP.C

$(LIB)\VDGERPUS.OBJ: \
        $(SOURCE)\VDGERPUS.C

        $(COMP_HH) $(SOURCE)\VDGERPUS.C

$(LIB)\VDGERWIN.OBJ: \
        $(SOURCE)\VDGERWIN.C

        $(COMP_HH) $(SOURCE)\VDGERWIN.C

$(LIB)\VDGERWVR.OBJ: \
        $(SOURCE)\VDGERWVR.C

        $(COMP_HH) $(SOURCE)\VDGERWVR.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDGERPOP.OBJ     \
        $(LIB)\VDGERPUS.OBJ     \
        $(LIB)\VDGERWIN.OBJ     \
        $(LIB)\VDGERWVR.OBJ
        TLIB VDMLHH.LIB @GERWIN.RSP > 10

# =============================================================================
#
#      Fim de Make File - DIRETORIO "GERWIN".
#
# =============================================================================


