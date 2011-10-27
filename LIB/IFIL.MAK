# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio  "IFIL".
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=\APP\ADN2\IFIL

# Arquivos Alvo para a Construcao de Objetos.
# Diretorio IFIL - 1a. Parte.
OBJETOS_TELA: \
              $(LIB)\CTADLOG.OBJ        \
              $(LIB)\CTADREC.OBJ        \
              $(LIB)\CTADVREC.OBJ       \
              $(LIB)\CTRDVLEN.OBJ       \
              $(LIB)\CTDLVREC.OBJ       \
              $(LIB)\CTDLREC.OBJ        \
              $(LIB)\CTDLALL.OBJ        \
              $(LIB)\CTCMPCHV.OBJ       \
              $(LIB)\CTFILBUF.OBJ       \
              $(LIB)\CTFIND.OBJ         \
              $(LIB)\CTKEYFIL.OBJ       \
              $(LIB)\CTFILNM.OBJ        \
              $(LIB)\CTFRSREC.OBJ       \
              $(LIB)\CTINBUF.OBJ        \
              $(LIB)\CTINIT.OBJ         \
              $(LIB)\CTKEYNM.OBJ        \
              $(LIB)\CTLSTREC.OBJ       \
              $(LIB)\CTGTEREC.OBJ       \
              $(LIB)\CTGETCHV.OBJ       \
              $(LIB)\CTLTEREC.OBJ       \
              $(LIB)\CTNXTREC.OBJ       \
              $(LIB)\CTOPEN.OBJ         \
              $(LIB)\CTOPEN2.OBJ        \
              $(LIB)\CTPRVREC.OBJ       \
              $(LIB)\CTREAD.OBJ         \
              $(LIB)\CTREWREC.OBJ       \
              $(LIB)\CTRWVREC.OBJ       \
              $(LIB)\CTSETFRS.OBJ       \
              $(LIB)\CTSETLST.OBJ       \
              $(LIB)\CTSETNXT.OBJ       \
              $(LIB)\CTSETPRV.OBJ       \
              $(LIB)\CTGETBUF.OBJ       \
              $(LIB)\GETDODA.OBJ        \
              $(LIB)\GETIFIL.OBJ        \
              $(LIB)\PCREAT.OBJ         \
              $(LIB)\PINIT.OBJ          \
              $(LIB)\CTTABSET.OBJ       \
              $(LIB)\CTCPYBUF.OBJ       \
              $(LIB)\CTCPDODA.OBJ       \
              $(LIB)\CTTMPFIL.OBJ       \
              $(LIB)\CTTMPKEY.OBJ       \
              $(LIB)\CTISOPEN.OBJ       \
              $(LIB)\CTISCRIA.OBJ       \
              $(LIB)\CTDELTMP.OBJ       \
              $(LIB)\CTTEMP.OBJ         \
	      $(LIB)\CTCLOSE.OBJ	\
	      $(LIB)\CTCOPY.OBJ 	\
	      $(LIB)\CTISPOS.OBJ	\
	      $(LIB)\VDCTREE.LIB


# <<<<<<<<<<   Diretorio BOX.   >>>>>>>>>>
$(LIB)\CTADLOG.OBJ:  $(SOURCE)\CTADLOG.C
                     $(COMP_HH) $(SOURCE)\CTADLOG.C

$(LIB)\CTADREC.OBJ:  $(SOURCE)\CTADREC.C
                     $(COMP_HH) $(SOURCE)\CTADREC.C

$(LIB)\CTADVREC.OBJ: $(SOURCE)\CTADVREC.C
                     $(COMP_HH) $(SOURCE)\CTADVREC.C

$(LIB)\CTRDVLEN.OBJ: $(SOURCE)\CTRDVLEN.C
                     $(COMP_HH) $(SOURCE)\CTRDVLEN.C

$(LIB)\CTDLVREC.OBJ: $(SOURCE)\CTDLVREC.C
                     $(COMP_HH) $(SOURCE)\CTDLVREC.C

$(LIB)\CTDLREC.OBJ:  $(SOURCE)\CTDLREC.C
                     $(COMP_HH) $(SOURCE)\CTDLREC.C

$(LIB)\CTDLALL.OBJ:  $(SOURCE)\CTDLALL.C
                     $(COMP_HH) $(SOURCE)\CTDLALL.C

$(LIB)\CTCMPCHV.OBJ: $(SOURCE)\CTCMPCHV.C
                     $(COMP_HH) $(SOURCE)\CTCMPCHV.C

$(LIB)\CTFILBUF.OBJ: $(SOURCE)\CTFILBUF.C
                     $(COMP_HH) $(SOURCE)\CTFILBUF.C

$(LIB)\CTFIND.OBJ:   $(SOURCE)\CTFIND.C
                     $(COMP_HH) $(SOURCE)\CTFIND.C

$(LIB)\CTKEYFIL.OBJ: $(SOURCE)\CTKEYFIL.C
                     $(COMP_HH) $(SOURCE)\CTKEYFIL.C

$(LIB)\CTFILNM.OBJ:  $(SOURCE)\CTFILNM.C
                     $(COMP_HH) $(SOURCE)\CTFILNM.C

$(LIB)\CTFRSREC.OBJ: $(SOURCE)\CTFRSREC.C
                     $(COMP_HH) $(SOURCE)\CTFRSREC.C

$(LIB)\CTINBUF.OBJ:  $(SOURCE)\CTINBUF.C
                     $(COMP_HH) $(SOURCE)\CTINBUF.C

$(LIB)\CTINIT.OBJ:   $(SOURCE)\CTINIT.C
                     $(COMP_HH) $(SOURCE)\CTINIT.C

$(LIB)\CTKEYNM.OBJ:  $(SOURCE)\CTKEYNM.C
                     $(COMP_HH) $(SOURCE)\CTKEYNM.C

$(LIB)\CTLSTREC.OBJ: $(SOURCE)\CTLSTREC.C
                     $(COMP_HH) $(SOURCE)\CTLSTREC.C

$(LIB)\CTGTEREC.OBJ: $(SOURCE)\CTGTEREC.C
                     $(COMP_HH) $(SOURCE)\CTGTEREC.C

$(LIB)\CTGETCHV.OBJ: $(SOURCE)\CTGETCHV.C
                     $(COMP_HH) $(SOURCE)\CTGETCHV.C

$(LIB)\CTLTEREC.OBJ: $(SOURCE)\CTLTEREC.C
                     $(COMP_HH) $(SOURCE)\CTLTEREC.C

$(LIB)\CTNXTREC.OBJ: $(SOURCE)\CTNXTREC.C
                     $(COMP_HH) $(SOURCE)\CTNXTREC.C

$(LIB)\CTOPEN.OBJ:   $(SOURCE)\CTOPEN.C
                     $(COMP_HH) $(SOURCE)\CTOPEN.C

$(LIB)\CTOPEN2.OBJ:  $(SOURCE)\CTOPEN2.C
                     $(COMP_HH) $(SOURCE)\CTOPEN2.C

$(LIB)\CTPRVREC.OBJ: $(SOURCE)\CTPRVREC.C
                     $(COMP_HH) $(SOURCE)\CTPRVREC.C

$(LIB)\CTREAD.OBJ:   $(SOURCE)\CTREAD.C
                     $(COMP_HH) $(SOURCE)\CTREAD.C

$(LIB)\CTREWREC.OBJ: $(SOURCE)\CTREWREC.C
                     $(COMP_HH) $(SOURCE)\CTREWREC.C

$(LIB)\CTRWVREC.OBJ: $(SOURCE)\CTRWVREC.C
                     $(COMP_HH) $(SOURCE)\CTRWVREC.C

$(LIB)\CTSETFRS.OBJ: $(SOURCE)\CTSETFRS.C
                     $(COMP_HH) $(SOURCE)\CTSETFRS.C

$(LIB)\CTSETLST.OBJ: $(SOURCE)\CTSETLST.C
                     $(COMP_HH) $(SOURCE)\CTSETLST.C

$(LIB)\CTSETNXT.OBJ: $(SOURCE)\CTSETNXT.C
                     $(COMP_HH) $(SOURCE)\CTSETNXT.C

$(LIB)\CTSETPRV.OBJ: $(SOURCE)\CTSETPRV.C
                     $(COMP_HH) $(SOURCE)\CTSETPRV.C

$(LIB)\CTGETBUF.OBJ: $(SOURCE)\CTGETBUF.C
                     $(COMP_HH) $(SOURCE)\CTGETBUF.C

$(LIB)\GETDODA.OBJ:  $(SOURCE)\GETDODA.C
                     $(COMP_HH) $(SOURCE)\GETDODA.C

$(LIB)\GETIFIL.OBJ:  $(SOURCE)\GETIFIL.C
                     $(COMP_HH) $(SOURCE)\GETIFIL.C

$(LIB)\PCREAT.OBJ:   $(SOURCE)\PCREAT.C
                     $(COMP_HH) $(SOURCE)\PCREAT.C

$(LIB)\PINIT.OBJ:    $(SOURCE)\PINIT.C
                     $(COMP_HH) $(SOURCE)\PINIT.C

$(LIB)\CTTABSET.OBJ: $(SOURCE)\CTTABSET.C
                     $(COMP_HH) $(SOURCE)\CTTABSET.C

$(LIB)\CTCPYBUF.OBJ: $(SOURCE)\CTCPYBUF.C
                     $(COMP_HH) $(SOURCE)\CTCPYBUF.C

$(LIB)\CTCPDODA.OBJ: $(SOURCE)\CTCPDODA.C
                     $(COMP_HH) $(SOURCE)\CTCPDODA.C

$(LIB)\CTTMPFIL.OBJ: $(SOURCE)\CTTMPFIL.C
                     $(COMP_HH) $(SOURCE)\CTTMPFIL.C

$(LIB)\CTTMPKEY.OBJ: $(SOURCE)\CTTMPKEY.C
                     $(COMP_HH) $(SOURCE)\CTTMPKEY.C

$(LIB)\CTISCRIA.OBJ: $(SOURCE)\CTISCRIA.C
                     $(COMP_HH) $(SOURCE)\CTISCRIA.C

$(LIB)\CTISOPEN.OBJ: $(SOURCE)\CTISOPEN.C
                     $(COMP_HH) $(SOURCE)\CTISOPEN.C

$(LIB)\CTDELTMP.OBJ: $(SOURCE)\CTDELTMP.C
                     $(COMP_HH) $(SOURCE)\CTDELTMP.C

$(LIB)\CTTEMP.OBJ:   $(SOURCE)\CTTEMP.C
                     $(COMP_HH) $(SOURCE)\CTTEMP.C

$(LIB)\CTCOPY.OBJ:   $(SOURCE)\CTCOPY.C
                     $(COMP_HH) $(SOURCE)\CTCOPY.C

$(LIB)\CTCLOSE.OBJ:   $(SOURCE)\CTCLOSE.C
		     $(COMP_HH) $(SOURCE)\CTCLOSE.C

$(LIB)\CTISPOS.OBJ:   $(SOURCE)\CTISPOS.C
		     $(COMP_HH) $(SOURCE)\CTISPOS.C

$(LIB)\VDCTREE.LIB: \
              $(LIB)\CTADlog.OBJ        \
              $(LIB)\CTADREC.OBJ        \
              $(LIB)\CTADVREC.OBJ       \
              $(LIB)\CTRDVLEN.OBJ       \
              $(LIB)\CTDLVREC.OBJ       \
              $(LIB)\CTDLREC.OBJ        \
              $(LIB)\CTDLALL.OBJ        \
              $(LIB)\CTCMPCHV.OBJ       \
              $(LIB)\CTFILBUF.OBJ       \
              $(LIB)\CTFIND.OBJ         \
              $(LIB)\CTKEYFIL.OBJ       \
              $(LIB)\CTFILNM.OBJ        \
              $(LIB)\CTFRSREC.OBJ       \
              $(LIB)\CTINBUF.OBJ        \
              $(LIB)\CTINIT.OBJ         \
              $(LIB)\CTKEYNM.OBJ        \
              $(LIB)\CTLSTREC.OBJ       \
              $(LIB)\CTGTEREC.OBJ       \
              $(LIB)\CTGETCHV.OBJ       \
              $(LIB)\CTLTEREC.OBJ       \
              $(LIB)\CTNXTREC.OBJ       \
              $(LIB)\CTOPEN.OBJ         \
              $(LIB)\CTOPEN2.OBJ        \
              $(LIB)\CTPRVREC.OBJ       \
              $(LIB)\CTREAD.OBJ         \
              $(LIB)\CTREWREC.OBJ       \
              $(LIB)\CTRWVREC.OBJ       \
              $(LIB)\CTSETFRS.OBJ       \
              $(LIB)\CTSETLST.OBJ       \
              $(LIB)\CTSETNXT.OBJ       \
              $(LIB)\CTSETPRV.OBJ       \
              $(LIB)\CTGETBUF.OBJ       \
              $(LIB)\GETDODA.OBJ        \
              $(LIB)\GETIFIL.OBJ        \
              $(LIB)\PCREAT.OBJ         \
              $(LIB)\PINIT.OBJ          \
              $(LIB)\CTTABSET.OBJ       \
              $(LIB)\CTCPYBUF.OBJ       \
              $(LIB)\CTCPDODA.OBJ       \
              $(LIB)\CTTMPFIL.OBJ       \
              $(LIB)\CTTMPKEY.OBJ       \
              $(LIB)\CTISOPEN.OBJ       \
              $(LIB)\CTISCRIA.OBJ       \
              $(LIB)\CTDELTMP.OBJ       \
              $(LIB)\CTTEMP.OBJ         \
	      $(LIB)\CTCOPY.OBJ 	\
	      $(LIB)\CTCLOSE.OBJ	\
	      $(LIB)\CTISPOS.OBJ
	      DEL VDCTREE.LIB
              TLIB VDCTREE.LIB @VDCTREE.RSP > 12

# =============================================================================
#
#      Fim de Make File - DIRETORIO "IFIL" 1a. Parte (Banco de Dados).
#
# =============================================================================





