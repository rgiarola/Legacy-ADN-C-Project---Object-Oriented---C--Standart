# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "ARVORE".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\ARVORE




# Arquivos Alvo para a Construcao de Objetos.
# Diretorio ARVORE
OBJETOS_TELA: \
              $(LIB)\VDARVACT.OBJ          \
              $(LIB)\VDARVESP.OBJ          \
              $(LIB)\VDARVCOA.OBJ          \
              $(LIB)\VDARVCOP.OBJ          \
              $(LIB)\VDARVDAR.OBJ          \
              $(LIB)\VDARVDCL.OBJ          \
              $(LIB)\VDARVDLI.OBJ          \
              $(LIB)\VDARVDMA.OBJ          \
              $(LIB)\VDARVDSB.OBJ          \
              $(LIB)\VDARVDSP.OBJ          \
              $(LIB)\VDARVFAR.OBJ          \
              $(LIB)\VDARVFJA.OBJ          \
              $(LIB)\VDARVFLI.OBJ          \
              $(LIB)\VDARVIAR.OBJ          \
              $(LIB)\VDARVIJA.OBJ          \
              $(LIB)\VDARVILI.OBJ          \
              $(LIB)\VDARVLII.OBJ          \
              $(LIB)\VDARVLIS.OBJ          \
              $(LIB)\VDARVMTA.OBJ          \
              $(LIB)\VDARVMTB.OBJ          \
              $(LIB)\VDARVMTE.OBJ          \
              $(LIB)\VDARVPGA.OBJ          \
              $(LIB)\VDARVPGP.OBJ          \
              $(LIB)\VDARVPIT.OBJ          \
              $(LIB)\VDARVREC.OBJ          \
              $(LIB)\VDARVREL.OBJ          \
              $(LIB)\VDARVSEL.OBJ          \
              $(LIB)\VDARVTER.OBJ          \
              $(LIB)\VDARVUIT.OBJ          \
              $(LIB)\VDARVVAR.OBJ          \
              $(LIB)\VDARVDCM.OBJ          \
              $(LIB)\VDARVSEM.OBJ          \
              $(LIB)\VDARVSTM.OBJ          \
              $(LIB)\VDARVDTB.OBJ          \
              $(LIB)\VDARVUTB.OBJ          \
              $(LIB)\VDARVABO.OBJ          \
              $(LIB)\VDARVUCM.OBJ          \
              $(LIB)\VDARVORE.LIB          \
              $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio ARVORE.   >>>>>>>>>>
$(LIB)\VDARVACT.OBJ: \
        $(SOURCE)\VDARVACT.C

        $(COMP_OV) $(SOURCE)\VDARVACT.C

$(LIB)\VDARVESP.OBJ: \
        $(SOURCE)\VDARVESP.C

        $(COMP_OV) $(SOURCE)\VDARVESP.C

$(LIB)\VDARVCOA.OBJ: \
        $(SOURCE)\VDARVCOA.C

        $(COMP_OV) $(SOURCE)\VDARVCOA.C

$(LIB)\VDARVCOP.OBJ: \
        $(SOURCE)\VDARVCOP.C

        $(COMP_OV) $(SOURCE)\VDARVCOP.C

$(LIB)\VDARVDAR.OBJ: \
        $(SOURCE)\VDARVDAR.C

        $(COMP_OV) $(SOURCE)\VDARVDAR.C

$(LIB)\VDARVDCL.OBJ: \
        $(SOURCE)\VDARVDCL.C

        $(COMP_OV) $(SOURCE)\VDARVDCL.C

$(LIB)\VDARVDLI.OBJ: \
        $(SOURCE)\VDARVDLI.C

        $(COMP_OV) $(SOURCE)\VDARVDLI.C

$(LIB)\VDARVDMA.OBJ: \
        $(SOURCE)\VDARVDMA.C

        $(COMP_OV) $(SOURCE)\VDARVDMA.C

$(LIB)\VDARVDSB.OBJ: \
        $(SOURCE)\VDARVDSB.C

        $(COMP_OV) $(SOURCE)\VDARVDSB.C

$(LIB)\VDARVDSP.OBJ: \
        $(SOURCE)\VDARVDSP.C

        $(COMP_OV) $(SOURCE)\VDARVDSP.C

$(LIB)\VDARVFAR.OBJ: \
        $(SOURCE)\VDARVFAR.C

        $(COMP_OV) $(SOURCE)\VDARVFAR.C

$(LIB)\VDARVFJA.OBJ: \
        $(SOURCE)\VDARVFJA.C

        $(COMP_OV) $(SOURCE)\VDARVFJA.C

$(LIB)\VDARVFLI.OBJ: \
        $(SOURCE)\VDARVFLI.C

        $(COMP_OV) $(SOURCE)\VDARVFLI.C

$(LIB)\VDARVIAR.OBJ: \
        $(SOURCE)\VDARVIAR.C

        $(COMP_OV) $(SOURCE)\VDARVIAR.C

$(LIB)\VDARVIJA.OBJ: \
        $(SOURCE)\VDARVIJA.C

        $(COMP_OV) $(SOURCE)\VDARVIJA.C

$(LIB)\VDARVILI.OBJ: \
        $(SOURCE)\VDARVILI.C

        $(COMP_OV) $(SOURCE)\VDARVILI.C

$(LIB)\VDARVLII.OBJ: \
        $(SOURCE)\VDARVLII.C

        $(COMP_OV) $(SOURCE)\VDARVLII.C

$(LIB)\VDARVLIS.OBJ: \
        $(SOURCE)\VDARVLIS.C

        $(COMP_OV) $(SOURCE)\VDARVLIS.C

$(LIB)\VDARVMTA.OBJ: \
        $(SOURCE)\VDARVMTA.C

        $(COMP_OV) $(SOURCE)\VDARVMTA.C

$(LIB)\VDARVMTB.OBJ: \
        $(SOURCE)\VDARVMTB.C

        $(COMP_OV) $(SOURCE)\VDARVMTB.C

$(LIB)\VDARVMTE.OBJ: \
        $(SOURCE)\VDARVMTE.C

        $(COMP_OV) $(SOURCE)\VDARVMTE.C

$(LIB)\VDARVPGA.OBJ: \
        $(SOURCE)\VDARVPGA.C

        $(COMP_OV) $(SOURCE)\VDARVPGA.C

$(LIB)\VDARVPGP.OBJ: \
        $(SOURCE)\VDARVPGP.C

        $(COMP_OV) $(SOURCE)\VDARVPGP.C

$(LIB)\VDARVPIT.OBJ: \
        $(SOURCE)\VDARVPIT.C

        $(COMP_OV) $(SOURCE)\VDARVPIT.C

$(LIB)\VDARVREC.OBJ: \
        $(SOURCE)\VDARVREC.C

        $(COMP_OV) $(SOURCE)\VDARVREC.C

$(LIB)\VDARVREL.OBJ: \
        $(SOURCE)\VDARVREL.C

        $(COMP_OV) $(SOURCE)\VDARVREL.C

$(LIB)\VDARVUIT.OBJ: \
        $(SOURCE)\VDARVUIT.C

        $(COMP_OV) $(SOURCE)\VDARVUIT.C

$(LIB)\VDARVVAR.OBJ: \
        $(SOURCE)\VDARVVAR.C

        $(COMP_NO) $(SOURCE)\VDARVVAR.C

$(LIB)\VDARVDCM.OBJ: \
        $(SOURCE)\VDARVDCM.C

        $(COMP_OV) $(SOURCE)\VDARVDCM.C

$(LIB)\VDARVSEM.OBJ: \
        $(SOURCE)\VDARVSEM.C

        $(COMP_OV) $(SOURCE)\VDARVSEM.C

$(LIB)\VDARVSTM.OBJ: \
        $(SOURCE)\VDARVSTM.C

        $(COMP_OV) $(SOURCE)\VDARVSTM.C

$(LIB)\VDARVDTB.OBJ: \
        $(SOURCE)\VDARVDTB.C

        $(COMP_OV) $(SOURCE)\VDARVDTB.C

$(LIB)\VDARVUTB.OBJ: \
        $(SOURCE)\VDARVUTB.C

        $(COMP_OV) $(SOURCE)\VDARVUTB.C

$(LIB)\VDARVUCM.OBJ: \
        $(SOURCE)\VDARVUCM.C

        $(COMP_OV) $(SOURCE)\VDARVUCM.C

$(LIB)\VDARVSEL.OBJ: \
        $(SOURCE)\VDARVSEL.C

        $(COMP_OV) $(SOURCE)\VDARVSEL.C

$(LIB)\VDARVTER.OBJ: \
        $(SOURCE)\VDARVTER.C

        $(COMP_OV) $(SOURCE)\VDARVTER.C

$(LIB)\VDARVABO.OBJ: \
        $(SOURCE)\VDARVABO.C

        $(COMP_OV) $(SOURCE)\VDARVABO.C

$(LIB)\VDARVORE.LIB: \
              $(LIB)\VDARVACT.OBJ          \
              $(LIB)\VDARVESP.OBJ          \
              $(LIB)\VDARVCOA.OBJ          \
              $(LIB)\VDARVCOP.OBJ          \
              $(LIB)\VDARVDAR.OBJ          \
              $(LIB)\VDARVDCL.OBJ          \
              $(LIB)\VDARVDLI.OBJ          \
              $(LIB)\VDARVDMA.OBJ          \
              $(LIB)\VDARVDSB.OBJ          \
              $(LIB)\VDARVDSP.OBJ          \
              $(LIB)\VDARVFAR.OBJ          \
              $(LIB)\VDARVFJA.OBJ          \
              $(LIB)\VDARVFLI.OBJ          \
              $(LIB)\VDARVIAR.OBJ          \
              $(LIB)\VDARVIJA.OBJ          \
              $(LIB)\VDARVILI.OBJ          \
              $(LIB)\VDARVLII.OBJ          \
              $(LIB)\VDARVLIS.OBJ          \
              $(LIB)\VDARVMTA.OBJ          \
              $(LIB)\VDARVMTB.OBJ          \
              $(LIB)\VDARVMTE.OBJ          \
              $(LIB)\VDARVPGA.OBJ          \
              $(LIB)\VDARVPGP.OBJ          \
              $(LIB)\VDARVPIT.OBJ          \
              $(LIB)\VDARVREC.OBJ          \
              $(LIB)\VDARVREL.OBJ          \
              $(LIB)\VDARVSEL.OBJ          \
              $(LIB)\VDARVTER.OBJ          \
              $(LIB)\VDARVUIT.OBJ          \
              $(LIB)\VDARVDCM.OBJ          \
              $(LIB)\VDARVSEM.OBJ          \
              $(LIB)\VDARVSTM.OBJ          \
              $(LIB)\VDARVDTB.OBJ          \
              $(LIB)\VDARVUTB.OBJ          \
              $(LIB)\VDARVABO.OBJ          \
              $(LIB)\VDARVUCM.OBJ
              DEL  VDARVORE.LIB
              TLIB VDARVORE @ARVORE.RSP > 2

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDARVVAR.OBJ
        TLIB VDMLHH.LIB -+VDARVVAR.OBJ > 3

# =============================================================================
#
#      Fim de Make File - DIRETORIO "ARVORE" (Manipulacao Arvore).
#
# =============================================================================





