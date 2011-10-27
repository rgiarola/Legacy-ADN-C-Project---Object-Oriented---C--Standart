# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "RTREE".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\RTREE


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio BOX
OBJETOS_TELA: \
        $(LIB)\RTVAR.OBJ    \
        $(LIB)\RTDATA.OBJ   \
        $(LIB)\RTINTERF.OBJ \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio RTREE.   >>>>>>>>>>
$(LIB)\RTDATA.OBJ: \
        $(SOURCE)\RTDATA.C

        $(COMP_HH) $(SOURCE)\RTDATA.C

$(LIB)\RTVAR.OBJ: \
        $(SOURCE)\RTVAR.C

        $(COMP_HH) $(SOURCE)\RTVAR.C

$(LIB)\RTINTERF.OBJ: \
        $(SOURCE)\RTINTERF.C

        $(COMP_HH) $(SOURCE)\RTINTERF.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\RTVAR.OBJ    \
        $(LIB)\RTDATA.OBJ   \
        $(LIB)\RTINTERF.OBJ
        TLIB VDMLHH.LIB @RTREE.RSP > 16

# =============================================================================
#
#      Fim de Make File - DIRETORIO "RTREE" (Funcoes de Operacao).
#
# =============================================================================

