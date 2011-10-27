# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "TELA".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\TELA



# Arquivos Alvo para a Construcao de Objetos.
# Diretorio TELA
#       $(LIB)\VDTELSTP.OBJ   -> Objeto de Dados Invalido.......
OBJETOS_TELA: \
        $(LIB)\VDTELESP.OBJ           \
        $(LIB)\VDTELABO.OBJ           \
        $(LIB)\VDTELACT.OBJ           \
        $(LIB)\VDTELCFX.OBJ           \
        $(LIB)\VDTELCME.OBJ           \
        $(LIB)\VDTELCNU.OBJ           \
        $(LIB)\VDTELCON.OBJ           \
        $(LIB)\VDTELCPA.OBJ           \
        $(LIB)\VDTELCPP.OBJ           \
        $(LIB)\VDTELCPT.OBJ           \
        $(LIB)\VDTELCSD.OBJ           \
        $(LIB)\VDTELCTB.OBJ           \
        $(LIB)\VDTELCVA.OBJ           \
        $(LIB)\VDTELDAT.OBJ           \
        $(LIB)\VDTELDBA.OBJ           \
        $(LIB)\VDTELDBS.OBJ           \
        $(LIB)\VDTELDCP.OBJ           \
        $(LIB)\VDTELDFR.OBJ           \
        $(LIB)\VDTELDLS.OBJ           \
        $(LIB)\VDTELDPO.OBJ           \
        $(LIB)\VDTELDPR.OBJ           \
        $(LIB)\VDTELDSF.OBJ           \
        $(LIB)\VDTELEDC.OBJ           \
        $(LIB)\VDTELFNU.OBJ           \
        $(LIB)\VDTELFTX.OBJ           \
        $(LIB)\VDTELLIA.OBJ           \
        $(LIB)\VDTELLIP.OBJ           \
        $(LIB)\VDTELMEN.OBJ           \
        $(LIB)\VDTELMMA.OBJ           \
        $(LIB)\VDTELMSD.OBJ           \
        $(LIB)\VDTELPRI.OBJ           \
        $(LIB)\VDTELTAT.OBJ           \
        $(LIB)\VDTELTES.OBJ           \
        $(LIB)\VDTELTED.OBJ           \
        $(LIB)\VDTELTEX.OBJ           \
        $(LIB)\VDTELTPO.OBJ           \
        $(LIB)\VDTELULT.OBJ           \
        $(LIB)\VDTELINC.OBJ           \
        $(LIB)\VDTELDMA.OBJ           \
        $(LIB)\VDTELDME.OBJ           \
        $(LIB)\VDTELDPA.OBJ           \
        $(LIB)\VDTELDCO.OBJ           \
        $(LIB)\VDTELDBU.OBJ           \
        $(LIB)\VDTELUSR.OBJ           \
        $(LIB)\VDTELUSE.OBJ           \
        $(LIB)\VDTELDMN.OBJ           \
        $(LIB)\VDTELDDP.OBJ           \
        $(LIB)\VDTELRFS.OBJ           \
        $(LIB)\VDTELRFT.OBJ           \
        $(LIB)\VDTELRTL.OBJ           \
        $(LIB)\VDTELLSU.OBJ           \
        $(LIB)\VDTELSTA.OBJ           \
        $(LIB)\VDTELSSB.OBJ           \
	$(LIB)\VDTELBDR.OBJ	      \
        $(LIB)\VDTELTSG.OBJ           \
        $(LIB)\VDTELDST.OBJ           \
        $(LIB)\VDTELAPR.OBJ           \
        $(LIB)\VDTELTIP.OBJ           \
        $(LIB)\VDTELSIN.OBJ           \
        $(LIB)\VDTELALT.OBJ           \
        $(LIB)\VDTELABT.OBJ           \
        $(LIB)\VDTELCAL.OBJ           \
        $(LIB)\VDTELMPO.OBJ           \
        $(LIB)\VDTELDCN.OBJ           \
        $(LIB)\VDTELTSE.OBJ           \
        $(LIB)\VDTELHEL.OBJ           \
        $(LIB)\VDTELA.LIB             \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio BOX.   >>>>>>>>>>
$(LIB)\VDTELESP.OBJ: \
        $(SOURCE)\VDTELESP.C

        $(COMP_HH) $(SOURCE)\VDTELESP.C

$(LIB)\VDTELABO.OBJ: \
        $(SOURCE)\VDTELABO.C

        $(COMP_HH) $(SOURCE)\VDTELABO.C

$(LIB)\VDTELLSU.OBJ: \
        $(SOURCE)\VDTELLSU.C

	$(COMP_HH) $(SOURCE)\VDTELLSU.C

$(LIB)\VDTELUSR.OBJ: \
        $(SOURCE)\VDTELUSR.C

        $(COMP_HH) $(SOURCE)\VDTELUSR.C

$(LIB)\VDTELUSE.OBJ: \
        $(SOURCE)\VDTELUSE.C

        $(COMP_HH) $(SOURCE)\VDTELUSE.C

$(LIB)\VDTELACT.OBJ: \
        $(SOURCE)\VDTELACT.C

        $(COMP_HH) $(SOURCE)\VDTELACT.C

$(LIB)\VDTELCFX.OBJ: \
        $(SOURCE)\VDTELCFX.C

        $(COMP_HH) $(SOURCE)\VDTELCFX.C

$(LIB)\VDTELCME.OBJ: \
        $(SOURCE)\VDTELCME.C

        $(COMP_HH) $(SOURCE)\VDTELCME.C

$(LIB)\VDTELCNU.OBJ: \
        $(SOURCE)\VDTELCNU.C

        $(COMP_HH) $(SOURCE)\VDTELCNU.C

$(LIB)\VDTELCON.OBJ: \
        $(SOURCE)\VDTELCON.C

        $(COMP_HH) $(SOURCE)\VDTELCON.C

$(LIB)\VDTELCPA.OBJ: \
        $(SOURCE)\VDTELCPA.C

        $(COMP_HH) $(SOURCE)\VDTELCPA.C

$(LIB)\VDTELCPP.OBJ: \
        $(SOURCE)\VDTELCPP.C

        $(COMP_HH) $(SOURCE)\VDTELCPP.C

$(LIB)\VDTELCPT.OBJ: \
        $(SOURCE)\VDTELCPT.C

        $(COMP_HH) $(SOURCE)\VDTELCPT.C

$(LIB)\VDTELCSD.OBJ: \
        $(SOURCE)\VDTELCSD.C

        $(COMP_HH) $(SOURCE)\VDTELCSD.C

$(LIB)\VDTELCTB.OBJ: \
        $(SOURCE)\VDTELCTB.C

        $(COMP_HH) $(SOURCE)\VDTELCTB.C

$(LIB)\VDTELCVA.OBJ: \
        $(SOURCE)\VDTELCVA.C

        $(COMP_HH) $(SOURCE)\VDTELCVA.C

$(LIB)\VDTELDBA.OBJ: \
        $(SOURCE)\VDTELDBA.C

        $(COMP_HH) $(SOURCE)\VDTELDBA.C

$(LIB)\VDTELDBS.OBJ: \
        $(SOURCE)\VDTELDBS.C

        $(COMP_HH) $(SOURCE)\VDTELDBS.C

$(LIB)\VDTELDCP.OBJ: \
        $(SOURCE)\VDTELDCP.C

        $(COMP_HH) $(SOURCE)\VDTELDCP.C

$(LIB)\VDTELDSF.OBJ: \
        $(SOURCE)\VDTELDSF.C

        $(COMP_HH) $(SOURCE)\VDTELDSF.C

$(LIB)\VDTELEDC.OBJ: \
        $(SOURCE)\VDTELEDC.C

        $(COMP_HH) $(SOURCE)\VDTELEDC.C

$(LIB)\VDTELFNU.OBJ: \
        $(SOURCE)\VDTELFNU.C

        $(COMP_HH) $(SOURCE)\VDTELFNU.C

$(LIB)\VDTELFTX.OBJ: \
        $(SOURCE)\VDTELFTX.C

        $(COMP_HH) $(SOURCE)\VDTELFTX.C

$(LIB)\VDTELLIA.OBJ: \
        $(SOURCE)\VDTELLIA.C

        $(COMP_HH) $(SOURCE)\VDTELLIA.C

$(LIB)\VDTELLIP.OBJ: \
        $(SOURCE)\VDTELLIP.C

        $(COMP_HH) $(SOURCE)\VDTELLIP.C

$(LIB)\VDTELMEN.OBJ: \
        $(SOURCE)\VDTELMEN.C

        $(COMP_HH) $(SOURCE)\VDTELMEN.C

$(LIB)\VDTELMMA.OBJ: \
        $(SOURCE)\VDTELMMA.C

        $(COMP_HH) $(SOURCE)\VDTELMMA.C

$(LIB)\VDTELMSD.OBJ: \
        $(SOURCE)\VDTELMSD.C

        $(COMP_HH) $(SOURCE)\VDTELMSD.C

$(LIB)\VDTELPRI.OBJ: \
        $(SOURCE)\VDTELPRI.C

        $(COMP_HH) $(SOURCE)\VDTELPRI.C

$(LIB)\VDTELSTP.OBJ: \
        $(SOURCE)\VDTELSTP.C

        $(COMP_HH) $(SOURCE)\VDTELSTP.C

$(LIB)\VDTELTAT.OBJ: \
        $(SOURCE)\VDTELTAT.C

        $(COMP_HH) $(SOURCE)\VDTELTAT.C

$(LIB)\VDTELTES.OBJ: \
        $(SOURCE)\VDTELTES.C

        $(COMP_HH) $(SOURCE)\VDTELTES.C

$(LIB)\VDTELTED.OBJ: \
        $(SOURCE)\VDTELTED.C

        $(COMP_HH) $(SOURCE)\VDTELTED.C

$(LIB)\VDTELTEX.OBJ: \
        $(SOURCE)\VDTELTEX.C

        $(COMP_HH) $(SOURCE)\VDTELTEX.C

$(LIB)\VDTELTPO.OBJ: \
        $(SOURCE)\VDTELTPO.C

        $(COMP_HH) $(SOURCE)\VDTELTPO.C

$(LIB)\VDTELULT.OBJ: \
        $(SOURCE)\VDTELULT.C

        $(COMP_HH) $(SOURCE)\VDTELULT.C

$(LIB)\VDTELDAT.OBJ: \
        $(SOURCE)\VDTELDAT.C

        $(COMP_HH) $(SOURCE)\VDTELDAT.C

$(LIB)\VDTELDFR.OBJ: \
        $(SOURCE)\VDTELDFR.C

        $(COMP_HH) $(SOURCE)\VDTELDFR.C

$(LIB)\VDTELDLS.OBJ: \
        $(SOURCE)\VDTELDLS.C

        $(COMP_HH) $(SOURCE)\VDTELDLS.C

$(LIB)\VDTELDPR.OBJ: \
        $(SOURCE)\VDTELDPR.C

        $(COMP_HH) $(SOURCE)\VDTELDPR.C

$(LIB)\VDTELDPO.OBJ: \
        $(SOURCE)\VDTELDPO.C

        $(COMP_HH) $(SOURCE)\VDTELDPO.C

$(LIB)\VDTELINC.OBJ: \
        $(SOURCE)\VDTELINC.C

        $(COMP_HH) $(SOURCE)\VDTELINC.C

$(LIB)\VDTELDMA.OBJ: \
        $(SOURCE)\VDTELDMA.C

        $(COMP_HH) $(SOURCE)\VDTELDMA.C

$(LIB)\VDTELDME.OBJ: \
        $(SOURCE)\VDTELDME.C

        $(COMP_HH) $(SOURCE)\VDTELDME.C

$(LIB)\VDTELDPA.OBJ: \
        $(SOURCE)\VDTELDPA.C

        $(COMP_HH) $(SOURCE)\VDTELDPA.C

$(LIB)\VDTELDCO.OBJ: \
        $(SOURCE)\VDTELDCO.C

        $(COMP_HH) $(SOURCE)\VDTELDCO.C

$(LIB)\VDTELDBU.OBJ: \
        $(SOURCE)\VDTELDBU.C

        $(COMP_HH) $(SOURCE)\VDTELDBU.C

$(LIB)\VDTELCAL.OBJ: \
        $(SOURCE)\VDTELCAL.C

        $(COMP_HH) $(SOURCE)\VDTELCAL.C

$(LIB)\VDTELDMN.OBJ: \
        $(SOURCE)\VDTELDMN.C

        $(COMP_HH) $(SOURCE)\VDTELDMN.C

$(LIB)\VDTELRFS.OBJ: \
        $(SOURCE)\VDTELRFS.C

        $(COMP_HH) $(SOURCE)\VDTELRFS.C

$(LIB)\VDTELRFT.OBJ: \
        $(SOURCE)\VDTELRFT.C

        $(COMP_HH) $(SOURCE)\VDTELRFT.C

$(LIB)\VDTELRTL.OBJ: \
        $(SOURCE)\VDTELRTL.C

        $(COMP_HH) $(SOURCE)\VDTELRTL.C

$(LIB)\VDTELSTA.OBJ: \
        $(SOURCE)\VDTELSTA.C

        $(COMP_HH) $(SOURCE)\VDTELSTA.C

$(LIB)\VDTELDDP.OBJ: \
        $(SOURCE)\VDTELDDP.C

        $(COMP_HH) $(SOURCE)\VDTELDDP.C

$(LIB)\VDTELSSB.OBJ: \
        $(SOURCE)\VDTELSSB.C

        $(COMP_HH) $(SOURCE)\VDTELSSB.C

$(LIB)\VDTELBDR.OBJ: \
	$(SOURCE)\VDTELBDR.C

	$(COMP_HH) $(SOURCE)\VDTELBDR.C

$(LIB)\VDTELTSG.OBJ: \
        $(SOURCE)\VDTELTSG.C

        $(COMP_HH) $(SOURCE)\VDTELTSG.C

$(LIB)\VDTELDST.OBJ: \
        $(SOURCE)\VDTELDST.C

        $(COMP_HH) $(SOURCE)\VDTELDST.C

$(LIB)\VDTELAPR.OBJ: \
        $(SOURCE)\VDTELAPR.C

        $(COMP_HH) $(SOURCE)\VDTELAPR.C

$(LIB)\VDTELTIP.OBJ: \
        $(SOURCE)\VDTELTIP.C

        $(COMP_HH) $(SOURCE)\VDTELTIP.C

$(LIB)\VDTELSIN.OBJ: \
        $(SOURCE)\VDTELSIN.C

        $(COMP_HH) $(SOURCE)\VDTELSIN.C

$(LIB)\VDTELALT.OBJ: \
        $(SOURCE)\VDTELALT.C

        $(COMP_HH) $(SOURCE)\VDTELALT.C

$(LIB)\VDTELABT.OBJ: \
        $(SOURCE)\VDTELABT.C

        $(COMP_HH) $(SOURCE)\VDTELABT.C

$(LIB)\VDTELHEL.OBJ: \
        $(SOURCE)\VDTELHEL.C

        $(COMP_HH) $(SOURCE)\VDTELHEL.C

$(LIB)\VDTELDCN.OBJ: \
        $(SOURCE)\VDTELDCN.C

        $(COMP_HH) $(SOURCE)\VDTELDCN.C

$(LIB)\VDTELMPO.OBJ: \
        $(SOURCE)\VDTELMPO.C

        $(COMP_HH) $(SOURCE)\VDTELMPO.C

$(LIB)\VDTELTSE.OBJ: \
        $(SOURCE)\VDTELTSE.C

        $(COMP_HH) $(SOURCE)\VDTELTSE.C

$(LIB)\VDTELA.LIB: \
        $(LIB)\VDTELESP.OBJ           \
        $(LIB)\VDTELABO.OBJ           \
        $(LIB)\VDTELACT.OBJ           \
        $(LIB)\VDTELCFX.OBJ           \
        $(LIB)\VDTELCME.OBJ           \
        $(LIB)\VDTELCNU.OBJ           \
        $(LIB)\VDTELCON.OBJ           \
        $(LIB)\VDTELCPA.OBJ           \
        $(LIB)\VDTELCPP.OBJ           \
        $(LIB)\VDTELCPT.OBJ           \
        $(LIB)\VDTELCSD.OBJ           \
        $(LIB)\VDTELCTB.OBJ           \
        $(LIB)\VDTELDAT.OBJ           \
        $(LIB)\VDTELDBA.OBJ           \
        $(LIB)\VDTELDBS.OBJ           \
        $(LIB)\VDTELDCP.OBJ           \
        $(LIB)\VDTELDFR.OBJ           \
        $(LIB)\VDTELDLS.OBJ           \
        $(LIB)\VDTELDPO.OBJ           \
        $(LIB)\VDTELDPR.OBJ           \
        $(LIB)\VDTELDSF.OBJ           \
        $(LIB)\VDTELEDC.OBJ           \
        $(LIB)\VDTELFNU.OBJ           \
        $(LIB)\VDTELFTX.OBJ           \
        $(LIB)\VDTELLIA.OBJ           \
        $(LIB)\VDTELLIP.OBJ           \
        $(LIB)\VDTELMEN.OBJ           \
        $(LIB)\VDTELMMA.OBJ           \
        $(LIB)\VDTELMSD.OBJ           \
        $(LIB)\VDTELPRI.OBJ           \
        $(LIB)\VDTELTAT.OBJ           \
        $(LIB)\VDTELTES.OBJ           \
        $(LIB)\VDTELTED.OBJ           \
        $(LIB)\VDTELTEX.OBJ           \
        $(LIB)\VDTELTPO.OBJ           \
        $(LIB)\VDTELULT.OBJ           \
        $(LIB)\VDTELINC.OBJ           \
        $(LIB)\VDTELDMA.OBJ           \
        $(LIB)\VDTELDME.OBJ           \
        $(LIB)\VDTELDPA.OBJ           \
        $(LIB)\VDTELDCO.OBJ           \
        $(LIB)\VDTELDBU.OBJ           \
        $(LIB)\VDTELUSR.OBJ           \
        $(LIB)\VDTELUSE.OBJ           \
        $(LIB)\VDTELDMN.OBJ           \
        $(LIB)\VDTELDDP.OBJ           \
        $(LIB)\VDTELRFS.OBJ           \
        $(LIB)\VDTELRFT.OBJ           \
        $(LIB)\VDTELRTL.OBJ           \
        $(LIB)\VDTELLSU.OBJ           \
        $(LIB)\VDTELSTA.OBJ           \
        $(LIB)\VDTELSSB.OBJ           \
	$(LIB)\VDTELBDR.OBJ	      \
        $(LIB)\VDTELTSG.OBJ           \
        $(LIB)\VDTELDST.OBJ           \
        $(LIB)\VDTELAPR.OBJ           \
        $(LIB)\VDTELTIP.OBJ           \
        $(LIB)\VDTELSIN.OBJ           \
        $(LIB)\VDTELALT.OBJ           \
        $(LIB)\VDTELABT.OBJ           \
        $(LIB)\VDTELTSE.OBJ           \
        $(LIB)\VDTELHEL.OBJ           \
        $(LIB)\VDTELMPO.OBJ           \
        $(LIB)\VDTELDCN.OBJ           \
        $(LIB)\VDTELCAL.OBJ
        DEL VDTELA.LIB
        TLIB VDTELA.LIB @TELA.RSP > 18

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDTELCVA.OBJ
        TLIB VDMLHH.LIB -+VDTELCVA.OBJ > 18a

# =============================================================================
#
#      Fim de Make File - DIRETORIO "TELA" (Gerenciamento Video).
#
# =============================================================================
