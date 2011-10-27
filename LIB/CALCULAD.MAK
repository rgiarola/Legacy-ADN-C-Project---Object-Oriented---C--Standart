# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "CALCULAD",
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\CALCULAD


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio CALCULAD
OBJETOS_TELA: \
        $(LIB)\VDCALPER.OBJ        \
        $(LIB)\VDCALOPE.OBJ        \
        $(LIB)\VDCALEFT.OBJ        \
        $(LIB)\VDCALVAR.OBJ        \
        $(LIB)\VDCALVAD.OBJ        \
        $(LIB)\VDCALFDC.OBJ        \
        $(LIB)\VDCALERR.OBJ        \
        $(LIB)\VDCALDSP.OBJ        \
        $(LIB)\VDCALTCL.OBJ        \
        $(LIB)\VDCALINI.OBJ        \
        $(LIB)\VDCALC.LIB          \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio CALCULAD.   >>>>>>>>>>
$(LIB)\VDCALPER.OBJ: \
        $(SOURCE)\VDCALPER.C

        $(COMP_OV) $(SOURCE)\VDCALPER.C

$(LIB)\VDCALOPE.OBJ: \
        $(SOURCE)\VDCALOPE.C

        $(COMP_OV) $(SOURCE)\VDCALOPE.C

$(LIB)\VDCALEFT.OBJ: \
        $(SOURCE)\VDCALEFT.C

        $(COMP_OV) $(SOURCE)\VDCALEFT.C

$(LIB)\VDCALVAR.OBJ: \
        $(SOURCE)\VDCALVAR.C

        $(COMP_NO) $(SOURCE)\VDCALVAR.C

$(LIB)\VDCALVAD.OBJ: \
        $(SOURCE)\VDCALVAD.C

        $(COMP_NO) $(SOURCE)\VDCALVAD.C

$(LIB)\VDCALFDC.OBJ: \
        $(SOURCE)\VDCALFDC.C

        $(COMP_OV) $(SOURCE)\VDCALFDC.C

$(LIB)\VDCALERR.OBJ: \
        $(SOURCE)\VDCALERR.C

        $(COMP_OV) $(SOURCE)\VDCALERR.C

$(LIB)\VDCALDSP.OBJ: \
        $(SOURCE)\VDCALDSP.C

        $(COMP_OV) $(SOURCE)\VDCALDSP.C

$(LIB)\VDCALTCL.OBJ: \
        $(SOURCE)\VDCALTCL.C

        $(COMP_OV) $(SOURCE)\VDCALTCL.C

$(LIB)\VDCALINI.OBJ: \
        $(SOURCE)\VDCALINI.C

        $(COMP_OV) $(SOURCE)\VDCALINI.C

$(LIB)\VDCALC.LIB: \
        $(LIB)\VDCALPER.OBJ        \
        $(LIB)\VDCALOPE.OBJ        \
        $(LIB)\VDCALEFT.OBJ        \
        $(LIB)\VDCALFDC.OBJ        \
        $(LIB)\VDCALERR.OBJ        \
        $(LIB)\VDCALDSP.OBJ        \
        $(LIB)\VDCALTCL.OBJ        \
        $(LIB)\VDCALINI.OBJ
        DEL VDCALC.LIB
        TLIB VDCALC.LIB  @CALCULAD.RSP > 5

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDCALVAR.OBJ \
        $(LIB)\VDCALVAD.OBJ
        TLIB VDMLHH.LIB -+VDCALVAR.OBJ -+VDCALVAD.OBJ > 5a

# =============================================================================
#
#      Fim de Make File - DIRETORIO "CALCULAD" (Funcoes de CALCULAD).
#
# =============================================================================





