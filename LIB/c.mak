# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "CARGA".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\CARGA


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio CARGA
#       $(LIB)\VDTELSTP.OBJ   -> Objeto de Dados Invalido.......
OBJETOS_CARGA: \
	$(LIB)\VDCRGARQ.OBJ	      \
	$(LIB)\VDCRGVAR.OBJ	      \
	$(LIB)\VDCRGIAN.OBJ	      \
	$(LIB)\VDCRGIDN.OBJ	      \
	$(LIB)\VDCRGITR.OBJ	      \
	$(LIB)\VDCRGIDB.OBJ	      \
	$(LIB)\VDCRGEDB.OBJ	      \
	$(LIB)\VDCRGFCR.OBJ	      \
	$(LIB)\VDCRGLIT.OBJ	      \
	$(LIB)\VDCRGENA.OBJ	      \
	$(LIB)\VDCRGENI.OBJ	      \
        $(LIB)\VDCRGEDT.OBJ           \
        $(LIB)\VDCRTETE.OBJ           \
        $(LIB)\VDCRTDIM.OBJ           \
        $(LIB)\VDCRTDIC.OBJ           \
        $(LIB)\VDCRTSGA.OBJ           \
        $(LIB)\VDCRTTEL.OBJ           \
        $(LIB)\VDCRTDST.OBJ           \
        $(LIB)\VDCRTECO.OBJ           \
        $(LIB)\VDCRTECP.OBJ           \
        $(LIB)\VDCRTPTE.OBJ           \
        $(LIB)\VDCRTFRT.OBJ           \
        $(LIB)\VDCRMEXM.OBJ           \
        $(LIB)\VDCRMPMN.OBJ           \
        $(LIB)\VDCRMDMN.OBJ           \
        $(LIB)\VDCRTDCP.OBJ           \
        $(LIB)\VDCRGIDE.OBJ           \
        $(LIB)\VDCRTEXT.OBJ           \
        $(LIB)\VDCARGA.LIB

# <<<<<<<<<<   Diretorio CARGA   >>>>>>>>>>
$(LIB)\VDCRTPTE.OBJ: \
        $(SOURCE)\VDCRTPTE.C
        $(COMP_HH) $(SOURCE)\VDCRTPTE.C

$(LIB)\VDCRTDIM.OBJ: \
        $(SOURCE)\VDCRTDIM.C
        $(COMP_HH) $(SOURCE)\VDCRTDIM.C

$(LIB)\VDCRTDIC.OBJ: \
        $(SOURCE)\VDCRTDIC.C

        $(COMP_HH) $(SOURCE)\VDCRTDIC.C

$(LIB)\VDCRTFRT.OBJ: \
        $(SOURCE)\VDCRTFRT.C

        $(COMP_HH) $(SOURCE)\VDCRTFRT.C

$(LIB)\VDCRTEXT.OBJ: \
        $(SOURCE)\VDCRTEXT.C

        $(COMP_HH) $(SOURCE)\VDCRTEXT.C

$(LIB)\VDCRTECP.OBJ: \
        $(SOURCE)\VDCRTECP.C

        $(COMP_HH) $(SOURCE)\VDCRTECP.C

$(LIB)\VDCRTECO.OBJ: \
        $(SOURCE)\VDCRTECO.C

        $(COMP_HH) $(SOURCE)\VDCRTECO.C

$(LIB)\VDCRTDST.OBJ: \
        $(SOURCE)\VDCRTDST.C

        $(COMP_HH) $(SOURCE)\VDCRTDST.C

$(LIB)\VDCRTTEL.OBJ: \
        $(SOURCE)\VDCRTTEL.C

        $(COMP_HH) $(SOURCE)\VDCRTTEL.C

$(LIB)\VDCRTETE.OBJ: \
        $(SOURCE)\VDCRTETE.C

        $(COMP_HH) $(SOURCE)\VDCRTETE.C

$(LIB)\VDCRTSGA.OBJ: \
        $(SOURCE)\VDCRTSGA.C

        $(COMP_HH) $(SOURCE)\VDCRTSGA.C

$(LIB)\VDCRGLIT.OBJ: \
	$(SOURCE)\VDCRGLIT.C

	$(COMP_HH) $(SOURCE)\VDCRGLIT.C


$(LIB)\VDCRGENA.OBJ: \
	$(SOURCE)\VDCRGENA.C

	$(COMP_HH) $(SOURCE)\VDCRGENA.C

$(LIB)\VDCRGENI.OBJ: \
	$(SOURCE)\VDCRGENI.C

	$(COMP_HH) $(SOURCE)\VDCRGENI.C

$(LIB)\VDCRGARQ.OBJ: \
        $(SOURCE)\VDCRGARQ.C

        $(COMP_HH) $(SOURCE)\VDCRGARQ.C

$(LIB)\VDCRGVAR.OBJ: \
        $(SOURCE)\VDCRGVAR.C

        $(COMP_HH) $(SOURCE)\VDCRGVAR.C

$(LIB)\VDCRGIAN.OBJ: \
        $(SOURCE)\VDCRGIAN.C

        $(COMP_HH) $(SOURCE)\VDCRGIAN.C


$(LIB)\VDCRGIDN.OBJ: \
        $(SOURCE)\VDCRGIDN.C

        $(COMP_HH) $(SOURCE)\VDCRGIDN.C

$(LIB)\VDCRGITR.OBJ: \
        $(SOURCE)\VDCRGITR.C

        $(COMP_HH) $(SOURCE)\VDCRGITR.C

$(LIB)\VDCRGIDB.OBJ: \
        $(SOURCE)\VDCRGIDB.C

        $(COMP_HH) $(SOURCE)\VDCRGIDB.C

$(LIB)\VDCRGEDB.OBJ: \
        $(SOURCE)\VDCRGEDB.C

        $(COMP_HH) $(SOURCE)\VDCRGEDB.C

$(LIB)\VDCRGFCR.OBJ: \
        $(SOURCE)\VDCRGFCR.C

        $(COMP_HH) $(SOURCE)\VDCRGFCR.C

$(LIB)\VDCRGEDT.OBJ: \
        $(SOURCE)\VDCRGEDT.C

        $(COMP_HH) $(SOURCE)\VDCRGEDT.C

$(LIB)\VDCRMDMN.OBJ: \
        $(SOURCE)\VDCRMDMN.C

        $(COMP_HH) $(SOURCE)\VDCRMDMN.C

$(LIB)\VDCRMPMN.OBJ: \
        $(SOURCE)\VDCRMPMN.C

        $(COMP_HH) $(SOURCE)\VDCRMPMN.C

$(LIB)\VDCRMEXM.OBJ: \
        $(SOURCE)\VDCRMEXM.C

        $(COMP_HH) $(SOURCE)\VDCRMEXM.C

$(LIB)\VDCRTDCP.OBJ: \
        $(SOURCE)\VDCRTDCP.C

        $(COMP_HH) $(SOURCE)\VDCRTDCP.C

$(LIB)\VDCRGIDE.OBJ: \
        $(SOURCE)\VDCRGIDE.C

        $(COMP_HH) $(SOURCE)\VDCRGIDE.C

$(LIB)\VDCARGA.LIB: \
	$(LIB)\VDCRGARQ.OBJ	      \
	$(LIB)\VDCRGVAR.OBJ	      \
	$(LIB)\VDCRGIAN.OBJ	      \
	$(LIB)\VDCRGIDN.OBJ	      \
	$(LIB)\VDCRGITR.OBJ	      \
	$(LIB)\VDCRGIDB.OBJ	      \
	$(LIB)\VDCRGEDB.OBJ	      \
	$(LIB)\VDCRGFCR.OBJ	      \
	$(LIB)\VDCRGLIT.OBJ	      \
	$(LIB)\VDCRGENA.OBJ	      \
	$(LIB)\VDCRGENI.OBJ	      \
        $(LIB)\VDCRGEDT.OBJ           \
        $(LIB)\VDCRTETE.OBJ           \
        $(LIB)\VDCRTDIM.OBJ           \
        $(LIB)\VDCRTDIC.OBJ           \
        $(LIB)\VDCRTSGA.OBJ           \
        $(LIB)\VDCRTTEL.OBJ           \
        $(LIB)\VDCRTDST.OBJ           \
        $(LIB)\VDCRTECO.OBJ           \
        $(LIB)\VDCRTECP.OBJ           \
        $(LIB)\VDCRTPTE.OBJ           \
        $(LIB)\VDCRTFRT.OBJ           \
        $(LIB)\VDCRMEXM.OBJ           \
        $(LIB)\VDCRMPMN.OBJ           \
        $(LIB)\VDCRMDMN.OBJ           \
        $(LIB)\VDCRTDCP.OBJ           \
        $(LIB)\VDCRGIDE.OBJ           \
        $(LIB)\VDCRTEXT.OBJ
        DEL VDCARGA.LIB
        TLIB VDCARGA.LIB @CARGA.RSP

# =============================================================================
#
#      Fim de Make File - DIRETORIO "CARGA" (GerencIANento Video).
#
# =============================================================================
