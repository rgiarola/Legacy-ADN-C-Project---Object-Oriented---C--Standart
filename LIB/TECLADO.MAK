# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "TECLADO".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\TECLADO



# Arquivos Alvo para a Construcao de Objetos.
# Diretorio Teclado
OBJETOS_TELA: \
        $(LIB)\VDKBDGET.OBJ     \
        $(LIB)\VDKBDPOS.OBJ     \
        $(LIB)\VDKEYGET.OBJ     \
        $(LIB)\VDKEYPOS.OBJ     \
        $(LIB)\VDTCLGET.OBJ     \
        $(LIB)\VDTCLINS.OBJ     \
        $(LIB)\VDTCLKEY.OBJ     \
        $(LIB)\VDTCLKPS.OBJ     \
        $(LIB)\VDTCLPOS.OBJ     \
        $(LIB)\VDTCLTST.OBJ     \
        $(LIB)\VDKEYVAR.OBJ     \
        $(LIB)\VDTCLVAR.OBJ     \
        $(LIB)\TECLADO.LIB


# <<<<<<<<<<   Diretorio TECLADO.   >>>>>>>>>>
$(LIB)\VDKBDGET.OBJ: \
        $(SOURCE)\VDKBDGET.C

        $(COMP_HH) $(SOURCE)\VDKBDGET.C

$(LIB)\VDKBDPOS.OBJ: \
        $(SOURCE)\VDKBDPOS.C

        $(COMP_HH) $(SOURCE)\VDKBDPOS.C

$(LIB)\VDKEYGET.OBJ: \
        $(SOURCE)\VDKEYGET.C

        $(COMP_HH) $(SOURCE)\VDKEYGET.C

$(LIB)\VDKEYPOS.OBJ: \
        $(SOURCE)\VDKEYPOS.C

        $(COMP_HH) $(SOURCE)\VDKEYPOS.C

$(LIB)\VDTCLGET.OBJ: \
        $(SOURCE)\VDTCLGET.C

        $(COMP_HH) $(SOURCE)\VDTCLGET.C

$(LIB)\VDTCLINS.OBJ: \
        $(SOURCE)\VDTCLINS.C

        $(COMP_HH) $(SOURCE)\VDTCLINS.C

$(LIB)\VDTCLKEY.OBJ: \
        $(SOURCE)\VDTCLKEY.C

        $(COMP_HH) $(SOURCE)\VDTCLKEY.C

$(LIB)\VDTCLKPS.OBJ: \
        $(SOURCE)\VDTCLKPS.C

        $(COMP_HH) $(SOURCE)\VDTCLKPS.C

$(LIB)\VDTCLPOS.OBJ: \
        $(SOURCE)\VDTCLPOS.C

        $(COMP_HH) $(SOURCE)\VDTCLPOS.C

$(LIB)\VDTCLTST.OBJ: \
        $(SOURCE)\VDTCLTST.C

        $(COMP_HH) $(SOURCE)\VDTCLTST.C

$(LIB)\VDTCLVAR.OBJ: \
        $(SOURCE)\VDTCLVAR.C

        $(COMP_HH) $(SOURCE)\VDTCLVAR.C

$(LIB)\VDKEYVAR.OBJ: \
        $(SOURCE)\VDKEYVAR.C

        $(COMP_HH) $(SOURCE)\VDKEYVAR.C


$(LIB)\TECLADO.LIB: \
        $(LIB)\VDKBDGET.OBJ     \
        $(LIB)\VDKBDPOS.OBJ     \
        $(LIB)\VDKEYGET.OBJ     \
        $(LIB)\VDKEYPOS.OBJ     \
        $(LIB)\VDTCLGET.OBJ     \
        $(LIB)\VDTCLINS.OBJ     \
        $(LIB)\VDTCLKEY.OBJ     \
        $(LIB)\VDTCLKPS.OBJ     \
        $(LIB)\VDTCLPOS.OBJ     \
        $(LIB)\VDTCLTST.OBJ     \
        $(LIB)\VDKEYVAR.OBJ     \
        $(LIB)\VDTCLVAR.OBJ
        DEL TECLADO.LIB
        TLIB TECLADO.LIB @TECLADO.RSP > 17

# =============================================================================
#
#      Fim de Make File - DIRETORIO "TECLADO" (Controle de Teclado).
#
# =============================================================================





