# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "CARGA".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\CARGA
SOURCE2=$(DRIVE)\ADN2\MEMORY

OBJETOS_CARGA: \
        $(LIB)\VDCRGARQ.OBJ           \
        $(LIB)\VDCRGVAR.OBJ           \
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
        $(LIB)\VDCARGA.LIB            \
        $(LIB)\VDMLHH.LIB

$(LIB)\ADNMEM.OBJ: \
        $(SOURCE2)\ADNMEM.C
        $(COMP_NO) $(SOURCE2)\ADNMEM.C

$(LIB)\ADNPOOL.OBJ: \
        $(SOURCE2)\ADNPOOL.C
        $(COMP_NO) $(SOURCE2)\ADNPOOL.C

$(LIB)\VDCRTPTE.OBJ: \
        $(SOURCE)\VDCRTPTE.C
        $(COMP_NO) $(SOURCE)\VDCRTPTE.C

$(LIB)\VDCRTDIM.OBJ: \
        $(SOURCE)\VDCRTDIM.C
        $(COMP_NO) $(SOURCE)\VDCRTDIM.C

$(LIB)\VDCRTDIC.OBJ: \
        $(SOURCE)\VDCRTDIC.C

        $(COMP_NO) $(SOURCE)\VDCRTDIC.C

$(LIB)\VDCRTFRT.OBJ: \
        $(SOURCE)\VDCRTFRT.C

        $(COMP_NO) $(SOURCE)\VDCRTFRT.C

$(LIB)\VDCRTEXT.OBJ: \
        $(SOURCE)\VDCRTEXT.C

        $(COMP_NO) $(SOURCE)\VDCRTEXT.C

$(LIB)\VDCRTECP.OBJ: \
        $(SOURCE)\VDCRTECP.C

        $(COMP_NO) $(SOURCE)\VDCRTECP.C

$(LIB)\VDCRTECO.OBJ: \
        $(SOURCE)\VDCRTECO.C

        $(COMP_NO) $(SOURCE)\VDCRTECO.C

$(LIB)\VDCRTDST.OBJ: \
        $(SOURCE)\VDCRTDST.C

        $(COMP_NO) $(SOURCE)\VDCRTDST.C

$(LIB)\VDCRTTEL.OBJ: \
        $(SOURCE)\VDCRTTEL.C

        $(COMP_NO) $(SOURCE)\VDCRTTEL.C

$(LIB)\VDCRTETE.OBJ: \
        $(SOURCE)\VDCRTETE.C

        $(COMP_NO) $(SOURCE)\VDCRTETE.C

$(LIB)\VDCRTSGA.OBJ: \
        $(SOURCE)\VDCRTSGA.C

        $(COMP_NO) $(SOURCE)\VDCRTSGA.C

$(LIB)\VDCRGLIT.OBJ: \
	$(SOURCE)\VDCRGLIT.C

        $(COMP_NO) $(SOURCE)\VDCRGLIT.C


$(LIB)\VDCRGENA.OBJ: \
	$(SOURCE)\VDCRGENA.C

        $(COMP_NO) $(SOURCE)\VDCRGENA.C

$(LIB)\VDCRGENI.OBJ: \
	$(SOURCE)\VDCRGENI.C

        $(COMP_NO) $(SOURCE)\VDCRGENI.C

$(LIB)\VDCRGARQ.OBJ: \
        $(SOURCE)\VDCRGARQ.C

        $(COMP_NO) $(SOURCE)\VDCRGARQ.C

$(LIB)\VDCRGVAR.OBJ: \
        $(SOURCE)\VDCRGVAR.C

        $(COMP_NO) $(SOURCE)\VDCRGVAR.C

$(LIB)\VDCRGIAN.OBJ: \
        $(SOURCE)\VDCRGIAN.C

        $(COMP_NO) $(SOURCE)\VDCRGIAN.C


$(LIB)\VDCRGIDN.OBJ: \
        $(SOURCE)\VDCRGIDN.C

        $(COMP_NO) $(SOURCE)\VDCRGIDN.C

$(LIB)\VDCRGITR.OBJ: \
        $(SOURCE)\VDCRGITR.C

        $(COMP_NO) $(SOURCE)\VDCRGITR.C

$(LIB)\VDCRGIDB.OBJ: \
        $(SOURCE)\VDCRGIDB.C

        $(COMP_NO) $(SOURCE)\VDCRGIDB.C

$(LIB)\VDCRGEDB.OBJ: \
        $(SOURCE)\VDCRGEDB.C

        $(COMP_NO) $(SOURCE)\VDCRGEDB.C

$(LIB)\VDCRGFCR.OBJ: \
        $(SOURCE)\VDCRGFCR.C

        $(COMP_NO) $(SOURCE)\VDCRGFCR.C

$(LIB)\VDCRGEDT.OBJ: \
        $(SOURCE)\VDCRGEDT.C

        $(COMP_NO) $(SOURCE)\VDCRGEDT.C

$(LIB)\VDCRMDMN.OBJ: \
        $(SOURCE)\VDCRMDMN.C

        $(COMP_NO) $(SOURCE)\VDCRMDMN.C

$(LIB)\VDCRMPMN.OBJ: \
        $(SOURCE)\VDCRMPMN.C

        $(COMP_NO) $(SOURCE)\VDCRMPMN.C

$(LIB)\VDCRMEXM.OBJ: \
        $(SOURCE)\VDCRMEXM.C

        $(COMP_NO) $(SOURCE)\VDCRMEXM.C

$(LIB)\VDCRTDCP.OBJ: \
        $(SOURCE)\VDCRTDCP.C

        $(COMP_NO) $(SOURCE)\VDCRTDCP.C

$(LIB)\VDCRGIDE.OBJ: \
        $(SOURCE)\VDCRGIDE.C

        $(COMP_NO) $(SOURCE)\VDCRGIDE.C

$(LIB)\VDCARGA.LIB: \
	$(LIB)\VDCRGARQ.OBJ	      \
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
        TLIB VDCARGA.LIB @CARGA.RSP > 6

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDCRGVAR.OBJ
        TLIB VDMLHH.LIB -+VDCRGVAR.OBJ


# =============================================================================
#
#      Fim de Make File - DIRETORIO "CARGA" (GerencIANento Video).
#
# =============================================================================
