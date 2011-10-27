# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "BOX",
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\BOX



# Arquivos Alvo para a Construcao de Objetos.
# Diretorio BOX
OBJETOS_TELA: \
        $(LIB)\VDBOX.OBJ        \
        $(LIB)\VDBOXVAR.OBJ     \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio BOX.   >>>>>>>>>>
$(LIB)\VDBOX.OBJ: \
        $(SOURCE)\VDBOX.C

        $(COMP_HH) $(SOURCE)\VDBOX.C

$(LIB)\VDBOXVAR.OBJ: \
        $(SOURCE)\VDBOXVAR.C

        $(COMP_HH) $(SOURCE)\VDBOXVAR.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDBOX.OBJ        \
        $(LIB)\VDBOXVAR.OBJ
        TLIB VDMLHH.LIB -+VDBOX.OBJ -+VDBOXVAR.OBJ > 4


# =============================================================================
#
#      Fim de Make File - DIRETORIO "BOX" (Funcoes de Box/Frame).
#
# =============================================================================





