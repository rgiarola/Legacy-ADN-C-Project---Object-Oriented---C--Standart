# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "EDITA",
#               de gerenciamento de memoria.
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\EDITA

# Arquivos Alvo para a Construcao de Objetos.
# Diretorio EDITA
OBJETOS_TELA: \
        $(LIB)\VDEDITA.OBJ      \
        $(LIB)\VDEDTSSP.OBJ     \
        $(LIB)\VDEDTTNU.OBJ     \
        $(LIB)\VDEDTTPT.OBJ     \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio EDITA.   >>>>>>>>>>
$(LIB)\VDEDITA.OBJ: \
        $(SOURCE)\VDEDITA.C

        $(COMP_HH) $(SOURCE)\VDEDITA.C

$(LIB)\VDEDTSSP.OBJ: \
        $(SOURCE)\VDEDTSSP.C

        $(COMP_HH) $(SOURCE)\VDEDTSSP.C

$(LIB)\VDEDTTNU.OBJ: \
        $(SOURCE)\VDEDTTNU.C

        $(COMP_HH) $(SOURCE)\VDEDTTNU.C

$(LIB)\VDEDTTPT.OBJ: \
        $(SOURCE)\VDEDTTPT.C

        $(COMP_HH) $(SOURCE)\VDEDTTPT.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDEDITA.OBJ      \
        $(LIB)\VDEDTSSP.OBJ     \
        $(LIB)\VDEDTTNU.OBJ     \
        $(LIB)\VDEDTTPT.OBJ
        TLIB VDMLHH.LIB -+VDEDITA.OBJ -+VDEDTSSP.OBJ -+VDEDTTNU.OBJ -+VDEDTTPT.OBJ > 8


# =============================================================================
#
#      Fim de Make File - DIRETORIO "EDITA" Gerenciamento de Memoria.
#
# =============================================================================




