# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#		dos arquivos descritos no diretorio "LOGIC".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\LOGIC


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio LOGIC
OBJETOS_TELA: \
              $(LIB)\VDLOGRNU.OBJ          \
              $(LIB)\VDLOGERR.OBJ          \
              $(LIB)\VDLOGCOR.OBJ          \
              $(LIB)\VDLOGCP.OBJ           \
              $(LIB)\VDLOGANB.OBJ          \
              $(LIB)\VDLOGCNU.OBJ          \
              $(LIB)\VDLOGCOP.OBJ          \
              $(LIB)\VDLOGANA.OBJ          \
              $(LIB)\VDLOGVR.OBJ           \
              $(LIB)\VDLOGTNU.OBJ          \
              $(LIB)\LOGIC.LIB             \
              $(LIB)\VDMLHH.LIB


# <<<<<<<<<<   Diretorio LOGIC.   >>>>>>>>>>
$(LIB)\VDLOGRNU.OBJ: \
	$(SOURCE)\VDLOGRNU.C

        $(COMP_OV) $(SOURCE)\VDLOGRNU.C

$(LIB)\VDLOGERR.OBJ: \
	$(SOURCE)\VDLOGERR.C

        $(COMP_OV) $(SOURCE)\VDLOGERR.C

$(LIB)\VDLOGCOR.OBJ: \
	$(SOURCE)\VDLOGCOR.C

        $(COMP_OV) $(SOURCE)\VDLOGCOR.C

$(LIB)\VDLOGCP.OBJ: \
	$(SOURCE)\VDLOGCP.C

        $(COMP_OV) $(SOURCE)\VDLOGCP.C

$(LIB)\VDLOGANB.OBJ: \
	$(SOURCE)\VDLOGANB.C

        $(COMP_OV) $(SOURCE)\VDLOGANB.C

$(LIB)\VDLOGCNU.OBJ: \
	$(SOURCE)\VDLOGCNU.C

        $(COMP_OV) $(SOURCE)\VDLOGCNU.C

$(LIB)\VDLOGCOP.OBJ: \
	$(SOURCE)\VDLOGCOP.C

        $(COMP_OV) $(SOURCE)\VDLOGCOP.C

$(LIB)\VDLOGANA.OBJ: \
	$(SOURCE)\VDLOGANA.C

        $(COMP_OV) $(SOURCE)\VDLOGANA.C

$(LIB)\VDLOGVR.OBJ: \
	$(SOURCE)\VDLOGVR.C

        $(COMP_NO) $(SOURCE)\VDLOGVR.C

$(LIB)\VDLOGTNU.OBJ: \
	$(SOURCE)\VDLOGTNU.C

        $(COMP_OV) $(SOURCE)\VDLOGTNU.C

$(LIB)\LOGIC.LIB: \
	      $(LIB)\VDLOGRNU.OBJ	   \
	      $(LIB)\VDLOGERR.OBJ	   \
	      $(LIB)\VDLOGCOR.OBJ	   \
	      $(LIB)\VDLOGCP.OBJ	   \
	      $(LIB)\VDLOGANB.OBJ	   \
	      $(LIB)\VDLOGCNU.OBJ	   \
	      $(LIB)\VDLOGCOP.OBJ	   \
	      $(LIB)\VDLOGANA.OBJ	   \
              $(LIB)\VDLOGTNU.OBJ
              TLIB LOGIC.LIB @LOGIC.RSP > 12

$(LIB)\VDMLHH.LIB: \
              $(LIB)\VDLOGVR.OBJ
              TLIB VDMLHH.LIB -+VDLOGVR.OBJ > 12a

	      
# =============================================================================
#
#      Fim de Make File - DIRETORIO "LOGIC" (Manipulacao INTERPRETACAO LOGIC).
#
# =============================================================================





