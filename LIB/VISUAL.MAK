# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "VISUAL".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\VISUAL


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio VISUAL
#       $(LIB)\VDVISSTP.OBJ   -> Objeto de Dados Invalido.......
OBJETOS_VISUAL: \
        $(LIB)\VDVISVAR.OBJ           \
        $(LIB)\VDVISULT.OBJ           \
        $(LIB)\VDVISMPO.OBJ           \
        $(LIB)\VDVISDSP.OBJ           \
        $(LIB)\VDVISPRI.OBJ           \
        $(LIB)\VDVISLPO.OBJ           \
        $(LIB)\VDVISACT.OBJ           \
        $(LIB)\VDVISFIP.OBJ           \
        $(LIB)\VDVISLAT.OBJ           \
        $(LIB)\VDVISPAT.OBJ           \
        $(LIB)\VDVISPPO.OBJ           \
        $(LIB)\VDVISTER.OBJ           \
        $(LIB)\VDVISCPO.OBJ           \
        $(LIB)\VDVISTPO.OBJ           \
        $(LIB)\VDVISCAT.OBJ           \
        $(LIB)\VDVISINP.OBJ           \
        $(LIB)\VDVISIND.OBJ           \
        $(LIB)\VDVISCRP.OBJ           \
        $(LIB)\VDVISMNA.OBJ           \
        $(LIB)\VDVISMAR.OBJ           \
        $(LIB)\VDVISINT.OBJ           \
        $(LIB)\VDVISPRC.OBJ           \
        $(LIB)\VDVISIMP.OBJ           \
        $(LIB)\VDVISSPL.OBJ           \
	$(LIB)\VDVISDEL.OBJ	      \
        $(LIB)\VDVISTAT.OBJ           \
        $(LIB)\VDVISCON.OBJ           \
        $(LIB)\VDVISCTI.OBJ           \
        $(LIB)\VDMLHH.LIB             \
        $(LIB)\VDVISUAL.LIB



# <<<<<<<<<<   Diretorio BOX.   >>>>>>>>>>
$(LIB)\VDVISVAR.OBJ: \
        $(SOURCE)\VDVISVAR.C

        $(COMP_NO) $(SOURCE)\VDVISVAR.C

$(LIB)\VDVISULT.OBJ: \
        $(SOURCE)\VDVISULT.C

        $(COMP_OV) $(SOURCE)\VDVISULT.C

$(LIB)\VDVISMPO.OBJ: \
        $(SOURCE)\VDVISMPO.C

        $(COMP_OV) $(SOURCE)\VDVISMPO.C

$(LIB)\VDVISDSP.OBJ: \
        $(SOURCE)\VDVISDSP.C

        $(COMP_OV) $(SOURCE)\VDVISDSP.C

$(LIB)\VDVISCTI.OBJ: \
        $(SOURCE)\VDVISCTI.C

        $(COMP_OV) $(SOURCE)\VDVISCTI.C

$(LIB)\VDVISPRI.OBJ: \
        $(SOURCE)\VDVISPRI.C

        $(COMP_OV) $(SOURCE)\VDVISPRI.C

$(LIB)\VDVISLPO.OBJ: \
        $(SOURCE)\VDVISLPO.C

        $(COMP_OV) $(SOURCE)\VDVISLPO.C

$(LIB)\VDVISACT.OBJ: \
        $(SOURCE)\VDVISACT.C

        $(COMP_NO) $(SOURCE)\VDVISACT.C

$(LIB)\VDVISFIP.OBJ: \
        $(SOURCE)\VDVISFIP.C

        $(COMP_OV) $(SOURCE)\VDVISFIP.C

$(LIB)\VDVISLAT.OBJ: \
        $(SOURCE)\VDVISLAT.C

        $(COMP_OV) $(SOURCE)\VDVISLAT.C

$(LIB)\VDVISCON.OBJ: \
        $(SOURCE)\VDVISCON.C

        $(COMP_OV) $(SOURCE)\VDVISCON.C

$(LIB)\VDVISPAT.OBJ: \
        $(SOURCE)\VDVISPAT.C

        $(COMP_OV) $(SOURCE)\VDVISPAT.C

$(LIB)\VDVISPPO.OBJ: \
        $(SOURCE)\VDVISPPO.C

        $(COMP_OV) $(SOURCE)\VDVISPPO.C

$(LIB)\VDVISTER.OBJ: \
        $(SOURCE)\VDVISTER.C

        $(COMP_OV) $(SOURCE)\VDVISTER.C

$(LIB)\VDVISINP.OBJ: \
        $(SOURCE)\VDVISINP.C

        $(COMP_OV) $(SOURCE)\VDVISINP.C

$(LIB)\VDVISCPO.OBJ: \
        $(SOURCE)\VDVISCPO.C

        $(COMP_OV) $(SOURCE)\VDVISCPO.C

$(LIB)\VDVISCAT.OBJ: \
        $(SOURCE)\VDVISCAT.C

        $(COMP_OV) $(SOURCE)\VDVISCAT.C

$(LIB)\VDVISTPO.OBJ: \
        $(SOURCE)\VDVISTPO.C

        $(COMP_OV) $(SOURCE)\VDVISTPO.C

$(LIB)\VDVISTAT.OBJ: \
        $(SOURCE)\VDVISTAT.C

        $(COMP_OV) $(SOURCE)\VDVISTAT.C

$(LIB)\VDVISCRP.OBJ: \
        $(SOURCE)\VDVISCRP.C

        $(COMP_OV) $(SOURCE)\VDVISCRP.C

$(LIB)\VDVISIND.OBJ: \
        $(SOURCE)\VDVISIND.C

        $(COMP_OV) $(SOURCE)\VDVISIND.C

$(LIB)\VDVISMNA.OBJ: \
        $(SOURCE)\VDVISMNA.C

        $(COMP_OV) $(SOURCE)\VDVISMNA.C

$(LIB)\VDVISMAR.OBJ: \
        $(SOURCE)\VDVISMAR.C

        $(COMP_OV) $(SOURCE)\VDVISMAR.C

$(LIB)\VDVISINT.OBJ: \
        $(SOURCE)\VDVISINT.C

        $(COMP_NO) $(SOURCE)\VDVISINT.C

$(LIB)\VDVISIMP.OBJ: \
        $(SOURCE)\VDVISIMP.C

        $(COMP_OV) $(SOURCE)\VDVISIMP.C

$(LIB)\VDVISSPL.OBJ: \
        $(SOURCE)\VDVISSPL.C

        $(COMP_OV) $(SOURCE)\VDVISSPL.C

$(LIB)\VDVISPRC.OBJ: \
        $(SOURCE)\VDVISPRC.C

        $(COMP_OV) $(SOURCE)\VDVISPRC.C

$(LIB)\VDVISDEL.OBJ: \
	$(SOURCE)\VDVISDEL.C

        $(COMP_OV) $(SOURCE)\VDVISDEL.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDVISVAR.OBJ \
        $(LIB)\VDVISINT.OBJ
        TLIB VDMLHH.LIB -+VDVISVAR.OBJ -+VDVISINT.OBJ > 19

$(LIB)\VDVISUAL.LIB: \
        $(LIB)\VDVISULT.OBJ           \
        $(LIB)\VDVISMPO.OBJ           \
        $(LIB)\VDVISDSP.OBJ           \
        $(LIB)\VDVISCTI.OBJ           \
        $(LIB)\VDVISPRI.OBJ           \
        $(LIB)\VDVISLPO.OBJ           \
        $(LIB)\VDVISACT.OBJ           \
        $(LIB)\VDVISFIP.OBJ           \
        $(LIB)\VDVISLAT.OBJ           \
        $(LIB)\VDVISCON.OBJ           \
        $(LIB)\VDVISPAT.OBJ           \
        $(LIB)\VDVISPPO.OBJ           \
        $(LIB)\VDVISTER.OBJ           \
        $(LIB)\VDVISCPO.OBJ           \
        $(LIB)\VDVISTPO.OBJ           \
        $(LIB)\VDVISCAT.OBJ           \
        $(LIB)\VDVISINP.OBJ           \
        $(LIB)\VDVISIND.OBJ           \
        $(LIB)\VDVISCRP.OBJ           \
        $(LIB)\VDVISMNA.OBJ           \
        $(LIB)\VDVISMAR.OBJ           \
        $(LIB)\VDVISINT.OBJ           \
        $(LIB)\VDVISPRC.OBJ           \
        $(LIB)\VDVISIMP.OBJ           \
        $(LIB)\VDVISSPL.OBJ           \
	$(LIB)\VDVISDEL.OBJ	      \
	$(LIB)\VDVISTAT.OBJ
	DEL VDVISUAL.LIB
        TLIB VDVISUAL.LIB @VISUAL.RSP > 19a

# =============================================================================
#
#      Fim de Make File - DIRETORIO "VISP" (Gerenciamento Video).
#
# =============================================================================
