# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "MOUSE".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\MOUSE



# Arquivos Alvo para a Construcao de Objetos.
# Diretorio MOUSE
OBJETOS_TELA: \
              $(LIB)\VDMOUVAR.OBJ          \
              $(LIB)\VDMOUDPI.OBJ          \
              $(LIB)\VDMOUIBO.OBJ          \
              $(LIB)\VDMOUINI.OBJ          \
              $(LIB)\VDMOUHCU.OBJ          \
              $(LIB)\VDMOUDCU.OBJ          \
              $(LIB)\VDMOUGPO.OBJ          \
              $(LIB)\VDMOUSPO.OBJ          \
              $(LIB)\VDMOUVEL.OBJ          \
	      $(LIB)\VDMOUBPR.OBJ	   \
	      $(LIB)\VDMOUCFG.OBJ	   \
              $(LIB)\VDMOUSE.LIB


# <<<<<<<<<<   Diretorio MOUSE.   >>>>>>>>>>
$(LIB)\VDMOUVAR.OBJ: \
        $(SOURCE)\VDMOUVAR.C

        $(COMP_HH) $(SOURCE)\VDMOUVAR.C

$(LIB)\VDMOUCFG.OBJ: \
	$(SOURCE)\VDMOUCFG.C

	$(COMP_HH) $(SOURCE)\VDMOUCFG.C

$(LIB)\VDMOUIBO.OBJ: \
        $(SOURCE)\VDMOUIBO.C

        $(COMP_HH) $(SOURCE)\VDMOUIBO.C

$(LIB)\VDMOUINI.OBJ: \
        $(SOURCE)\VDMOUINI.C

        $(COMP_HH) $(SOURCE)\VDMOUINI.C

$(LIB)\VDMOUHCU.OBJ: \
        $(SOURCE)\VDMOUHCU.C

        $(COMP_HH) $(SOURCE)\VDMOUHCU.C

$(LIB)\VDMOUDCU.OBJ: \
        $(SOURCE)\VDMOUDCU.C

        $(COMP_HH) $(SOURCE)\VDMOUDCU.C

$(LIB)\VDMOUGPO.OBJ: \
        $(SOURCE)\VDMOUGPO.C

        $(COMP_HH) $(SOURCE)\VDMOUGPO.C

$(LIB)\VDMOUSPO.OBJ: \
        $(SOURCE)\VDMOUSPO.C

        $(COMP_HH) $(SOURCE)\VDMOUSPO.C

$(LIB)\VDMOUBPR.OBJ: \
        $(SOURCE)\VDMOUBPR.C

        $(COMP_HH) $(SOURCE)\VDMOUBPR.C

$(LIB)\VDMOUVEL.OBJ: \
        $(SOURCE)\VDMOUVEL.C

        $(COMP_HH) $(SOURCE)\VDMOUVEL.C

$(LIB)\VDMOUDPI.OBJ: \
        $(SOURCE)\VDMOUDPI.C

        $(COMP_HH) $(SOURCE)\VDMOUDPI.C

$(LIB)\VDMOUSE.LIB: \
              $(LIB)\VDMOUVAR.OBJ          \
	      $(LIB)\VDMOUCFG.OBJ	   \
              $(LIB)\VDMOUIBO.OBJ          \
              $(LIB)\VDMOUINI.OBJ          \
              $(LIB)\VDMOUHCU.OBJ          \
              $(LIB)\VDMOUDCU.OBJ          \
              $(LIB)\VDMOUGPO.OBJ          \
              $(LIB)\VDMOUSPO.OBJ          \
              $(LIB)\VDMOUVEL.OBJ          \
              $(LIB)\VDMOUDPI.OBJ          \
	      $(LIB)\VDMOUBPR.OBJ
              DEL VDMOUSE.LIB
              TLIB VDMOUSE.LIB @MOUSE.RSP > 13b
	      
# =============================================================================
#
#      Fim de Make File - DIRETORIO "MOUSE" (Manipulacao MOUSE).
#
# =============================================================================





