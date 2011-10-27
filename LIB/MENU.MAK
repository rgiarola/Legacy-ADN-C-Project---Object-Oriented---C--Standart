# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "MENU".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\MENU


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio MENU
OBJETOS_TELA: \
        $(LIB)\VDMNCOAN.OBJ     \
        $(LIB)\VDMNCOPO.OBJ     \
        $(LIB)\VDMNLCMN.OBJ     \
        $(LIB)\VDMNMTOP.OBJ     \
        $(LIB)\VDMNPGAN.OBJ     \
        $(LIB)\VDMNPGPO.OBJ     \
        $(LIB)\VDMNPGSE.OBJ     \
        $(LIB)\VDMNSEAB.OBJ     \
        $(LIB)\VDMNSEAN.OBJ     \
        $(LIB)\VDMNSEAT.OBJ     \
        $(LIB)\VDMNSEDI.OBJ     \
        $(LIB)\VDMNSEES.OBJ     \
        $(LIB)\VDMNSEFI.OBJ     \
        $(LIB)\VDMNSEIN.OBJ     \
        $(LIB)\VDMNSEMV.OBJ     \
        $(LIB)\VDMNSEOP.OBJ     \
        $(LIB)\VDMNSEPO.OBJ     \
        $(LIB)\VDMNSEPR.OBJ     \
        $(LIB)\VDMNSEUL.OBJ     \
        $(LIB)\VDMNHELP.OBJ     \
	$(LIB)\VDMNSELT.OBJ	\
        $(LIB)\MENUMOVE.OBJ     \
	$(LIB)\VDMNVAR.OBJ	\
	$(LIB)\VDMLHH.LIB	\
	$(LIB)\VDMENU.LIB


$(LIB)\VDMNCOAN.OBJ: \
        $(SOURCE)\VDMNCOAN.C

        $(COMP_OV) $(SOURCE)\VDMNCOAN.C

$(LIB)\VDMNCOPO.OBJ: \
        $(SOURCE)\VDMNCOPO.C

        $(COMP_OV) $(SOURCE)\VDMNCOPO.C

$(LIB)\VDMNLCMN.OBJ: \
        $(SOURCE)\VDMNLCMN.C

        $(COMP_OV) $(SOURCE)\VDMNLCMN.C

$(LIB)\VDMNMTOP.OBJ: \
        $(SOURCE)\VDMNMTOP.C

        $(COMP_OV) $(SOURCE)\VDMNMTOP.C

$(LIB)\VDMNPGAN.OBJ: \
        $(SOURCE)\VDMNPGAN.C

        $(COMP_OV) $(SOURCE)\VDMNPGAN.C

$(LIB)\VDMNPGPO.OBJ: \
        $(SOURCE)\VDMNPGPO.C

        $(COMP_OV) $(SOURCE)\VDMNPGPO.C

$(LIB)\VDMNPGSE.OBJ: \
        $(SOURCE)\VDMNPGSE.C

        $(COMP_OV) $(SOURCE)\VDMNPGSE.C

$(LIB)\VDMNSEAB.OBJ: \
        $(SOURCE)\VDMNSEAB.C

        $(COMP_OV) $(SOURCE)\VDMNSEAB.C

$(LIB)\VDMNSEAN.OBJ: \
        $(SOURCE)\VDMNSEAN.C

        $(COMP_OV) $(SOURCE)\VDMNSEAN.C

$(LIB)\VDMNSEAT.OBJ: \
        $(SOURCE)\VDMNSEAT.C

        $(COMP_OV) $(SOURCE)\VDMNSEAT.C

$(LIB)\VDMNSEDI.OBJ: \
        $(SOURCE)\VDMNSEDI.C

        $(COMP_OV) $(SOURCE)\VDMNSEDI.C

$(LIB)\VDMNSEES.OBJ: \
        $(SOURCE)\VDMNSEES.C

        $(COMP_OV) $(SOURCE)\VDMNSEES.C

$(LIB)\VDMNSEFI.OBJ: \
        $(SOURCE)\VDMNSEFI.C

        $(COMP_OV) $(SOURCE)\VDMNSEFI.C

$(LIB)\VDMNSEIN.OBJ: \
        $(SOURCE)\VDMNSEIN.C

        $(COMP_OV) $(SOURCE)\VDMNSEIN.C

$(LIB)\VDMNSEMV.OBJ: \
        $(SOURCE)\VDMNSEMV.C

        $(COMP_OV) $(SOURCE)\VDMNSEMV.C

$(LIB)\VDMNSEOP.OBJ: \
        $(SOURCE)\VDMNSEOP.C

        $(COMP_OV) $(SOURCE)\VDMNSEOP.C

$(LIB)\VDMNSEPO.OBJ: \
        $(SOURCE)\VDMNSEPO.C

        $(COMP_OV) $(SOURCE)\VDMNSEPO.C

$(LIB)\VDMNSEPR.OBJ: \
        $(SOURCE)\VDMNSEPR.C

        $(COMP_OV) $(SOURCE)\VDMNSEPR.C

$(LIB)\VDMNSEUL.OBJ: \
        $(SOURCE)\VDMNSEUL.C

        $(COMP_OV) $(SOURCE)\VDMNSEUL.C

$(LIB)\VDMNVAR.OBJ: \
        $(SOURCE)\VDMNVAR.C

        $(COMP_NO) $(SOURCE)\VDMNVAR.C

$(LIB)\MENUMOVE.OBJ: \
        $(SOURCE)\VDMNVAR.C

        $(COMP_NO) -DMOVER_ATRIBUTO -oMENUMOVE $(SOURCE)\VDMNVAR.C

$(LIB)\VDMNHELP.OBJ: \
        $(SOURCE)\VDMNHELP.C

        $(COMP_OV) $(SOURCE)\VDMNHELP.C

$(LIB)\VDMNSELT.OBJ: \
        $(SOURCE)\VDMNSELT.C

        $(COMP_OV) $(SOURCE)\VDMNSELT.C

$(LIB)\VDMENU.LIB: \
        $(LIB)\VDMNCOAN.OBJ     \
        $(LIB)\VDMNCOPO.OBJ     \
        $(LIB)\VDMNLCMN.OBJ     \
        $(LIB)\VDMNMTOP.OBJ     \
        $(LIB)\VDMNPGAN.OBJ     \
        $(LIB)\VDMNPGPO.OBJ     \
        $(LIB)\VDMNPGSE.OBJ     \
        $(LIB)\VDMNSEAB.OBJ     \
        $(LIB)\VDMNSEAN.OBJ     \
        $(LIB)\VDMNSEAT.OBJ     \
        $(LIB)\VDMNSEDI.OBJ     \
        $(LIB)\VDMNSEES.OBJ     \
        $(LIB)\VDMNSEFI.OBJ     \
        $(LIB)\VDMNSEIN.OBJ     \
        $(LIB)\VDMNSEMV.OBJ     \
        $(LIB)\VDMNSEOP.OBJ     \
        $(LIB)\VDMNSEPO.OBJ     \
        $(LIB)\VDMNSEPR.OBJ     \
        $(LIB)\VDMNSEUL.OBJ     \
        $(LIB)\VDMNHELP.OBJ     \
	$(LIB)\VDMNSELT.OBJ
	DEL VDMENU.LIB
        TLIB VDMENU.LIB @MENU.RSP > 13

$(LIB)\VDMLHH.LIB: \
	$(LIB)\VDMNVAR.OBJ
        TLIB VDMLHH.LIB -+VDMNVAR.OBJ > 13a

# =============================================================================
#
#      Fim de Make File - DIRETORIO "MENU".
#
# =============================================================================




