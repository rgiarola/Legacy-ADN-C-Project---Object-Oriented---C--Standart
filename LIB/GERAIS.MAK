# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "GERAIS".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\GERAIS


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio GERAIS
OBJETOS_TELA: \
        $(LIB)\VDATCOPC.OBJ     \
        $(LIB)\VDCRMXTE.OBJ     \
        $(LIB)\VDGETXY.OBJ      \
        $(LIB)\VDGTXY.OBJ       \
        $(LIB)\VDMOVQDR.OBJ     \
        $(LIB)\VDMOVWIN.OBJ     \
        $(LIB)\VDMTMASC.OBJ     \
        $(LIB)\VDNUCLEO.OBJ     \
        $(LIB)\VDOPERTE.OBJ     \
        $(LIB)\VDQUADR.OBJ      \
        $(LIB)\VDRESCOR.OBJ     \
        $(LIB)\VDSETATR.OBJ     \
        $(LIB)\VDTCURSO.OBJ     \
        $(LIB)\VDTPRT.OBJ       \
        $(LIB)\VDTSTCRD.OBJ     \
        $(LIB)\VDTSTSKP.OBJ     \
        $(LIB)\VDVETOR.OBJ      \
        $(LIB)\VDDISMEN.OBJ     \
        $(LIB)\VDMEN2.OBJ       \
        $(LIB)\VDDISCON.OBJ     \
        $(LIB)\VDMENGEN.OBJ     \
        $(LIB)\VDINITEL.OBJ     \
        $(LIB)\VDSYSDAT.OBJ     \
        $(LIB)\VDTABSKP.OBJ     \
        $(LIB)\VDTABFNC.OBJ     \
        $(LIB)\VDATOFT.OBJ      \
        $(LIB)\VDATOLT.OBJ      \
        $(LIB)\VDATOULT.OBJ     \
        $(LIB)\VDTABCOR.OBJ     \
        $(LIB)\VDMONCOR.OBJ     \
	$(LIB)\VDINSWTR.OBJ	\
	$(LIB)\VDSWTRSE.OBJ	\
        $(LIB)\VDINITRN.OBJ     \
        $(LIB)\VDPUTMEN.OBJ     \
        $(LIB)\VDPSQBIN.OBJ     \
        $(LIB)\VDDCOMP.OBJ      \
        $(LIB)\VDLCOMP.OBJ      \
        $(LIB)\VDQUICK.OBJ      \
        $(LIB)\VDINITBF.OBJ     \
        $(LIB)\VDPSQFCN.OBJ     \
        $(LIB)\VDINICRG.OBJ     \
        $(LIB)\VDPSQCRG.OBJ     \
        $(LIB)\VDCONTEL.OBJ     \
        $(LIB)\VDICOMP.OBJ      \
        $(LIB)\MENS.OBJ         \
        $(LIB)\VDSYSTIM.OBJ     \
        $(LIB)\VDIMPINI.OBJ     \
        $(LIB)\VDIMPSTS.OBJ     \
        $(LIB)\VDABORTA.OBJ     \
        $(LIB)\VDIMPENV.OBJ     \
        $(LIB)\VDMENTEL.OBJ     \
        $(LIB)\VDDISMEM.OBJ     \
	$(LIB)\VDPUTERR.OBJ	\
        $(LIB)\VDVARERR.OBJ     \
	$(LIB)\VDLOCSER.OBJ	\
	$(LIB)\VDERRCRI.OBJ	\
	$(LIB)\VDESPERA.OBJ	\
        $(LIB)\VDALARME.OBJ     \
        $(LIB)\VDGERAIS.LIB     \
        $(LIB)\VDMLHH.LIB



# <<<<<<<<<<   Diretorio GERAIS.   >>>>>>>>>>
$(LIB)\VDATCOPC.OBJ: \
        $(SOURCE)\VDATCOPC.C

        $(COMP_HH) $(SOURCE)\VDATCOPC.C

$(LIB)\VDERRCRI.OBJ: \
        $(SOURCE)\VDERRCRI.C

        $(COMP_HH) $(SOURCE)\VDERRCRI.C

$(LIB)\VDDISCON.OBJ: \
        $(SOURCE)\VDDISCON.C

        $(COMP_HH) $(SOURCE)\VDDISCON.C

$(LIB)\VDDISMEN.OBJ: \
        $(SOURCE)\VDDISMEN.C

        $(COMP_HH) $(SOURCE)\VDDISMEN.C

$(LIB)\VDCRMXTE.OBJ: \
        $(SOURCE)\VDCRMXTE.C

        $(COMP_HH) $(SOURCE)\VDCRMXTE.C

$(LIB)\VDGETXY.OBJ: \
        $(SOURCE)\VDGETXY.C

        $(COMP_HH) $(SOURCE)\VDGETXY.C

$(LIB)\VDGTXY.OBJ: \
        $(SOURCE)\VDGTXY.C

        $(COMP_HH) $(SOURCE)\VDGTXY.C

$(LIB)\VDMOVQDR.OBJ: \
        $(SOURCE)\VDMOVQDR.C

        $(COMP_HH) $(SOURCE)\VDMOVQDR.C

$(LIB)\VDMOVWIN.OBJ: \
        $(SOURCE)\VDMOVWIN.C

        $(COMP_HH) $(SOURCE)\VDMOVWIN.C

$(LIB)\VDMTMASC.OBJ: \
        $(SOURCE)\VDMTMASC.C

        $(COMP_HH) $(SOURCE)\VDMTMASC.C

$(LIB)\VDNUCLEO.OBJ: \
        $(SOURCE)\VDNUCLEO.C

        $(COMP_HH) $(SOURCE)\VDNUCLEO.C

$(LIB)\VDOPERTE.OBJ: \
        $(SOURCE)\VDOPERTE.C

        $(COMP_HH) $(SOURCE)\VDOPERTE.C

$(LIB)\VDQUADR.OBJ: \
        $(SOURCE)\VDQUADR.C

        $(COMP_HH) $(SOURCE)\VDQUADR.C

$(LIB)\VDRESCOR.OBJ: \
        $(SOURCE)\VDRESCOR.C

        $(COMP_HH) $(SOURCE)\VDRESCOR.C

$(LIB)\VDSETATR.OBJ: \
        $(SOURCE)\VDSETATR.C

        $(COMP_HH) $(SOURCE)\VDSETATR.C

$(LIB)\VDTCURSO.OBJ: \
        $(SOURCE)\VDTCURSO.C

        $(COMP_HH) $(SOURCE)\VDTCURSO.C

$(LIB)\VDTPRT.OBJ: \
        $(SOURCE)\VDTPRT.C

        $(COMP_HH) $(SOURCE)\VDTPRT.C

$(LIB)\VDTSTCRD.OBJ: \
        $(SOURCE)\VDTSTCRD.C

        $(COMP_HH) $(SOURCE)\VDTSTCRD.C

$(LIB)\VDTSTSKP.OBJ: \
        $(SOURCE)\VDTSTSKP.C

        $(COMP_HH) $(SOURCE)\VDTSTSKP.C

$(LIB)\VDVETOR.OBJ: \
        $(SOURCE)\VDVETOR.C

        $(COMP_HH) $(SOURCE)\VDVETOR.C

$(LIB)\VDMENGEN.OBJ: \
        $(SOURCE)\VDMENGEN.C

        $(COMP_HH) $(SOURCE)\VDMENGEN.C

$(LIB)\VDMEN2.OBJ: \
        $(SOURCE)\VDMEN2.C

        $(COMP_HH) $(SOURCE)\VDMEN2.C

$(LIB)\VDINITEL.OBJ: \
        $(SOURCE)\VDINITEL.C

        $(COMP_HH) $(SOURCE)\VDINITEL.C

$(LIB)\VDSYSDAT.OBJ: \
        $(SOURCE)\VDSYSDAT.C

        $(COMP_HH) $(SOURCE)\VDSYSDAT.C

$(LIB)\VDTABFNC.OBJ: \
        $(SOURCE)\VDTABFNC.C

        $(COMP_HH) $(SOURCE)\VDTABFNC.C

$(LIB)\VDTABSKP.OBJ: \
        $(SOURCE)\VDTABSKP.C

        $(COMP_HH) $(SOURCE)\VDTABSKP.C

$(LIB)\VDCONTEL.OBJ: \
        $(SOURCE)\VDCONTEL.C

        $(COMP_HH) $(SOURCE)\VDCONTEL.C

$(LIB)\VDATOFT.OBJ: \
        $(SOURCE)\VDATOFT.C

        $(COMP_HH) $(SOURCE)\VDATOFT.C

$(LIB)\VDATOLT.OBJ: \
        $(SOURCE)\VDATOLT.C

        $(COMP_HH) $(SOURCE)\VDATOLT.C

$(LIB)\VDATOULT.OBJ: \
        $(SOURCE)\VDATOULT.C

        $(COMP_HH) $(SOURCE)\VDATOULT.C

$(LIB)\VDTABCOR.OBJ: \
        $(SOURCE)\VDTABCOR.C

        $(COMP_HH) $(SOURCE)\VDTABCOR.C

$(LIB)\VDMONCOR.OBJ: \
	$(SOURCE)\VDMONCOR.C

	$(COMP_HH) $(SOURCE)\VDMONCOR.C

$(LIB)\VDINSWTR.OBJ: \
	$(SOURCE)\VDINSWTR.C

	$(COMP_HH) $(SOURCE)\VDINSWTR.C

$(LIB)\VDSWTRSE.OBJ: \
	$(SOURCE)\VDSWTRSE.C

	$(COMP_HH) $(SOURCE)\VDSWTRSE.C

$(LIB)\VDINITRN.OBJ: \
        $(SOURCE)\VDINITRN.C

        $(COMP_HH) $(SOURCE)\VDINITRN.C

$(LIB)\VDPUTMEN.OBJ: \
        $(SOURCE)\VDPUTMEN.C

        $(COMP_HH) $(SOURCE)\VDPUTMEN.C

$(LIB)\VDICOMP.OBJ: \
        $(SOURCE)\VDICOMP.C

        $(COMP_HH) $(SOURCE)\VDICOMP.C

$(LIB)\VDLCOMP.OBJ: \
        $(SOURCE)\VDLCOMP.C

        $(COMP_HH) $(SOURCE)\VDLCOMP.C

$(LIB)\VDDCOMP.OBJ: \
        $(SOURCE)\VDDCOMP.C

        $(COMP_HH) $(SOURCE)\VDDCOMP.C

$(LIB)\VDPSQBIN.OBJ: \
        $(SOURCE)\VDPSQBIN.C

        $(COMP_HH) $(SOURCE)\VDPSQBIN.C

$(LIB)\VDQUICK.OBJ: \
        $(SOURCE)\VDQUICK.C

        $(COMP_HH) $(SOURCE)\VDQUICK.C

$(LIB)\VDINITBF.OBJ: \
	$(SOURCE)\VDINITBF.C

	$(COMP_HH) $(SOURCE)\VDINITBF.C

$(LIB)\VDPSQFCN.OBJ: \
        $(SOURCE)\VDPSQFCN.C

        $(COMP_HH) $(SOURCE)\VDPSQFCN.C

$(LIB)\VDINICRG.OBJ: \
        $(SOURCE)\VDINICRG.C

        $(COMP_HH) $(SOURCE)\VDINICRG.C

$(LIB)\VDPSQCRG.OBJ: \
        $(SOURCE)\VDPSQCRG.C

        $(COMP_HH) $(SOURCE)\VDPSQCRG.C

$(LIB)\MENS.OBJ: \
        $(DRIVE)\ADN2\VDMACROS\MENS.H

        $(COMP_HH) $(DRIVE)\ADN2\VDMACROS\MENS.H

$(LIB)\VDDISMEM.OBJ: \
        $(SOURCE)\VDDISMEM.C

        $(COMP_HH) $(SOURCE)\VDDISMEM.C

$(LIB)\VDSYSTIM.OBJ: \
	$(SOURCE)\VDSYSTIM.C

	$(COMP_HH) $(SOURCE)\VDSYSTIM.C

$(LIB)\VDIMPINI.OBJ: \
        $(SOURCE)\VDIMPINI.C

        $(COMP_HH) $(SOURCE)\VDIMPINI.C

$(LIB)\VDIMPENV.OBJ: \
        $(SOURCE)\VDIMPENV.C

        $(COMPHT) $(SOURCE)\VDIMPENV.C

$(LIB)\VDIMPSTS.OBJ: \
        $(SOURCE)\VDIMPSTS.C

        $(COMP_HH) $(SOURCE)\VDIMPSTS.C

$(LIB)\VDABORTA.OBJ: \
        $(SOURCE)\VDABORTA.C

        $(COMP_HH) $(SOURCE)\VDABORTA.C

$(LIB)\VDMENTEL.OBJ: \
        $(SOURCE)\VDMENTEL.C

        $(COMP_HH) $(SOURCE)\VDMENTEL.C

$(LIB)\BACKUP.OBJ: \
        $(SOURCE)\BACKUP.C

        $(COMP_HH) $(SOURCE)\BACKUP.C

$(LIB)\VDLOCSER.OBJ: \
        $(SOURCE)\VDLOCSER.C

        $(COMP_HH) $(SOURCE)\VDLOCSER.C

$(LIB)\VDPUTERR.OBJ: \
	$(SOURCE)\VDPUTERR.C

	$(COMP_HH) $(SOURCE)\VDPUTERR.C

$(LIB)\VDVARERR.OBJ: \
        $(SOURCE)\VDVARERR.C

        $(COMP_HH) $(SOURCE)\VDVARERR.C

$(LIB)\VDDISPRC.OBJ: \
        $(SOURCE)\VDDISPRC.C

        $(COMP_HH) $(SOURCE)\VDDISPRC.C

$(LIB)\VDESPERA.OBJ: \
	$(SOURCE)\VDESPERA.C

	$(COMP_HH) $(SOURCE)\VDESPERA.C

$(LIB)\VDALARME.OBJ: \
        $(SOURCE)\VDALARME.C

        $(COMP_HH) $(SOURCE)\VDALARME.C

$(LIB)\VDGERAIS.LIB: \
        $(LIB)\VDATCOPC.OBJ     \
        $(LIB)\VDERRCRI.OBJ     \
        $(LIB)\VDCRMXTE.OBJ     \
        $(LIB)\VDMOVQDR.OBJ     \
        $(LIB)\VDMOVWIN.OBJ     \
        $(LIB)\VDTSTCRD.OBJ     \
        $(LIB)\VDDISMEN.OBJ     \
        $(LIB)\VDDISCON.OBJ     \
        $(LIB)\VDINITEL.OBJ     \
        $(LIB)\VDSYSDAT.OBJ     \
        $(LIB)\VDTABFNC.OBJ     \
        $(LIB)\VDATOFT.OBJ      \
        $(LIB)\VDATOLT.OBJ      \
        $(LIB)\VDATOULT.OBJ     \
        $(LIB)\VDTABCOR.OBJ     \
        $(LIB)\VDMONCOR.OBJ     \
	$(LIB)\VDINSWTR.OBJ	\
	$(LIB)\VDSWTRSE.OBJ	\
        $(LIB)\VDINITRN.OBJ     \
        $(LIB)\VDPUTMEN.OBJ     \
        $(LIB)\VDPSQBIN.OBJ     \
        $(LIB)\VDDCOMP.OBJ      \
        $(LIB)\VDLCOMP.OBJ      \
        $(LIB)\VDQUICK.OBJ      \
        $(LIB)\VDINITBF.OBJ     \
        $(LIB)\VDPSQFCN.OBJ     \
        $(LIB)\VDINICRG.OBJ     \
        $(LIB)\VDCONTEL.OBJ     \
        $(LIB)\VDICOMP.OBJ      \
        $(LIB)\VDSYSTIM.OBJ     \
        $(LIB)\VDIMPINI.OBJ     \
        $(LIB)\VDIMPSTS.OBJ     \
        $(LIB)\VDABORTA.OBJ     \
        $(LIB)\VDIMPENV.OBJ     \
        $(LIB)\VDMENTEL.OBJ     \
        $(LIB)\VDDISMEM.OBJ     \
	$(LIB)\VDPUTERR.OBJ	\
        $(LIB)\VDVARERR.OBJ     \
        $(LIB)\VDDISPRC.OBJ     \
	$(LIB)\VDESPERA.OBJ	\
        $(LIB)\VDALARME.OBJ     \
        $(LIB)\VDLOCSER.OBJ
        DEL VDGERAIS.LIB
        TLIB VDGERAIS.LIB @GERAIS.RSP > 9


$(LIB)\VDMLHH.LIB: \
        $(LIB)\MENS.OBJ         \
        $(LIB)\VDPSQCRG.OBJ     \
        $(LIB)\VDTABSKP.OBJ     \
        $(LIB)\VDOPERTE.OBJ     \
        $(LIB)\VDMENGEN.OBJ     \
        $(LIB)\VDMEN2.OBJ       \
        $(LIB)\VDTSTSKP.OBJ     \
        $(LIB)\VDVETOR.OBJ      \
        $(LIB)\VDGETXY.OBJ      \
        $(LIB)\VDGTXY.OBJ       \
        $(LIB)\VDMTMASC.OBJ     \
        $(LIB)\VDNUCLEO.OBJ     \
        $(LIB)\VDQUADR.OBJ      \
        $(LIB)\VDRESCOR.OBJ     \
        $(LIB)\VDSETATR.OBJ     \
        $(LIB)\VDTCURSO.OBJ     \
        $(LIB)\VDTPRT.OBJ
        TLIB VDMLHH.LIB -+VDGETXY-+VDGTXY-+VDMTMASC-+VDNUCLEO-+VDQUADR > 9a
        TLIB VDMLHH.LIB -+VDRESCOR-+VDSETATR-+VDTCURSO-+VDTPRT > 9b
        TLIB VDMLHH.LIB -+VDTABSKP-+VDOPERTE-+VDMENGEN-+VDMEN2-+VDTSTSKP-+VDVETOR > 9c
        TLIB VDMLHH.LIB -+VDPSQCRG-+MENS > 9d

# =============================================================================
#
#      Fim de Make File - DIRETORIO "GERAIS".
#
# =============================================================================





