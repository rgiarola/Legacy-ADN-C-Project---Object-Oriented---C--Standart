# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "MASCARA".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\MASCARA



# Arquivos Alvo para a Construcao de Objetos.
# Diretorio MASCARA
#       $(LIB)\VDTELSTP.OBJ   -> Objeto de Dados Invalido.......
OBJETOS_MASCARA: \
        $(LIB)\VDEDTMAS.OBJ           \
        $(LIB)\VDEDTMTM.OBJ           \
        $(LIB)\VDEDTEXM.OBJ           \
        $(LIB)\VDEDTTCM.OBJ           \
        $(LIB)\VDEDTBKE.OBJ           \
        $(LIB)\VDDISPMA.OBJ           \
        $(LIB)\VDEDTCES.OBJ           \
        $(LIB)\VDEDTCDI.OBJ           \
        $(LIB)\VDEDTDCA.OBJ           \
	$(LIB)\VDEDTPOS.OBJ	      \
        $(LIB)\VDMASC.LIB


# <<<<<<<<<<   Diretorio BOX.   >>>>>>>>>>
$(LIB)\VDEDTMAS.OBJ: \
        $(SOURCE)\VDEDTMAS.C

        $(COMP_HH) $(SOURCE)\VDEDTMAS.C

$(LIB)\VDEDTMTM.OBJ: \
        $(SOURCE)\VDEDTMTM.C

        $(COMP_HH) $(SOURCE)\VDEDTMTM.C

$(LIB)\VDEDTEXM.OBJ: \
        $(SOURCE)\VDEDTEXM.C

        $(COMP_HH) $(SOURCE)\VDEDTEXM.C

$(LIB)\VDEDTTCM.OBJ: \
        $(SOURCE)\VDEDTTCM.C

        $(COMP_HH) $(SOURCE)\VDEDTTCM.C

$(LIB)\VDEDTBKE.OBJ: \
        $(SOURCE)\VDEDTBKE.C

        $(COMP_HH) $(SOURCE)\VDEDTBKE.C

$(LIB)\VDDISPMA.OBJ: \
        $(SOURCE)\VDDISPMA.C

        $(COMP_HH) $(SOURCE)\VDDISPMA.C

$(LIB)\VDEDTCES.OBJ: \
        $(SOURCE)\VDEDTCES.C

        $(COMP_HH) $(SOURCE)\VDEDTCES.C

$(LIB)\VDEDTCDI.OBJ: \
        $(SOURCE)\VDEDTCDI.C

        $(COMP_HH) $(SOURCE)\VDEDTCDI.C

$(LIB)\VDEDTDCA.OBJ: \
        $(SOURCE)\VDEDTDCA.C

        $(COMP_HH) $(SOURCE)\VDEDTDCA.C

$(LIB)\VDEDTPOS.OBJ: \
        $(SOURCE)\VDEDTPOS.C

        $(COMP_HH) $(SOURCE)\VDEDTPOS.C

$(LIB)\VDMASC.LIB: \
	$(LIB)\VDEDTMAS.OBJ	      \
        $(LIB)\VDEDTMTM.OBJ           \
        $(LIB)\VDEDTEXM.OBJ           \
        $(LIB)\VDEDTTCM.OBJ           \
        $(LIB)\VDEDTBKE.OBJ           \
        $(LIB)\VDDISPMA.OBJ           \
        $(LIB)\VDEDTCES.OBJ           \
        $(LIB)\VDEDTCDI.OBJ           \
        $(LIB)\VDEDTDCA.OBJ           \
	$(LIB)\VDEDTPOS.OBJ
        DEL VDMASC.LIB
        TLIB VDMASC.LIB @MASCARA.RSP > 13

# =============================================================================
#
#      Fim de Make File - DIRETORIO "MASCARA" (Gerenciamento Video).
#
# =============================================================================
