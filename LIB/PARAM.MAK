# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "PARAM".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\BOX


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio PARAM
#       $(LIB)\VDPARCRI.OBJ -> Objeto do Diretorio Invalido.

OBJETOS_TELA: \
        $(LIB)\VDPARARQ.OBJ             \
        $(LIB)\VDPARCRG.OBJ             \
        $(LIB)\VDPARDES.OBJ             \
	$(LIB)\VDPARVAR.OBJ		\
	$(LIB)\VDMLHH.LIB


# <<<<<<<<<<   Diretorio PARAM.   >>>>>>>>>>
$(LIB)\VDPARARQ.OBJ: \
        $(SOURCE)\VDPARARQ.C

        $(COMP_HH) $(SOURCE)\VDPARARQ.C

$(LIB)\VDPARCRG.OBJ: \
        $(SOURCE)\VDPARCRG.C

        $(COMP_HH) $(SOURCE)\VDPARCRG.C

$(LIB)\VDPARCRI.OBJ: \
        $(SOURCE)\VDPARCRI.C

        $(COMP_HH) $(SOURCE)\VDPARCRI.C

$(LIB)\VDPARDES.OBJ: \
        $(SOURCE)\VDPARDES.C

        $(COMP_HH) $(SOURCE)\VDPARDES.C

$(LIB)\VDPARVAR.OBJ: \
        $(SOURCE)\VDPARVAR.C

        $(COMP_HH) $(SOURCE)\VDPARVAR.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDPARARQ.OBJ             \
        $(LIB)\VDPARCRG.OBJ             \
        $(LIB)\VDPARDES.OBJ             \
	$(LIB)\VDPARVAR.OBJ
        TLIB VDMLHH.LIB @PARAM.CRG > 14

# =============================================================================
#
#      Fim de Make File - DIRETORIO "PARAM" (Parametros).
#
# =============================================================================

