# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "PESQUISA".
#
# =============================================================================


!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\PESQUISA


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio PESQUISA
OBJETOS_TELA: \
        $(LIB)\VDPESACT.OBJ     \
        $(LIB)\VDPESDAT.OBJ     \
        $(LIB)\VDPESDPO.OBJ     \
        $(LIB)\VDPESLAT.OBJ     \
        $(LIB)\VDPESLPO.OBJ     \
        $(LIB)\VDPESPAT.OBJ     \
        $(LIB)\VDPESPPO.OBJ     \
        $(LIB)\VDPESPRI.OBJ     \
        $(LIB)\VDPESTER.OBJ     \
        $(LIB)\VDPESSEL.OBJ     \
        $(LIB)\VDPESULT.OBJ     \
        $(LIB)\VDPESCVA.OBJ     \
        $(LIB)\VDPESDPI.OBJ     \
        $(LIB)\VDPESUSR.OBJ     \
        $(LIB)\VDPESUSE.OBJ     \
        $(LIB)\VDPESMNT.OBJ     \
        $(LIB)\VDPESQ.LIB       \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<   Diretorio PESQUISA.   >>>>>>>>>>
$(LIB)\VDPESACT.OBJ: \
        $(SOURCE)\VDPESACT.C

        $(COMP_OV) $(SOURCE)\VDPESACT.C

$(LIB)\VDPESUSE.OBJ: \
        $(SOURCE)\VDPESUSE.C

        $(COMP_NO) $(SOURCE)\VDPESUSE.C

$(LIB)\VDPESUSR.OBJ: \
        $(SOURCE)\VDPESUSR.C

        $(COMP_OV) $(SOURCE)\VDPESUSR.C

$(LIB)\VDPESDPI.OBJ: \
        $(SOURCE)\VDPESDPI.C

        $(COMP_OV) $(SOURCE)\VDPESDPI.C

$(LIB)\VDPESDAT.OBJ: \
        $(SOURCE)\VDPESDAT.C

        $(COMP_OV) $(SOURCE)\VDPESDAT.C

$(LIB)\VDPESDPO.OBJ: \
        $(SOURCE)\VDPESDPO.C

        $(COMP_OV) $(SOURCE)\VDPESDPO.C

$(LIB)\VDPESLAT.OBJ: \
        $(SOURCE)\VDPESLAT.C

        $(COMP_OV) $(SOURCE)\VDPESLAT.C

$(LIB)\VDPESLPO.OBJ: \
        $(SOURCE)\VDPESLPO.C

        $(COMP_OV) $(SOURCE)\VDPESLPO.C

$(LIB)\VDPESPAT.OBJ: \
        $(SOURCE)\VDPESPAT.C

        $(COMP_OV) $(SOURCE)\VDPESPAT.C

$(LIB)\VDPESPPO.OBJ: \
        $(SOURCE)\VDPESPPO.C

        $(COMP_OV) $(SOURCE)\VDPESPPO.C

$(LIB)\VDPESPRI.OBJ: \
        $(SOURCE)\VDPESPRI.C

        $(COMP_OV) $(SOURCE)\VDPESPRI.C

$(LIB)\VDPESTER.OBJ: \
        $(SOURCE)\VDPESTER.C

        $(COMP_OV) $(SOURCE)\VDPESTER.C

$(LIB)\VDPESSEL.OBJ: \
        $(SOURCE)\VDPESSEL.C

        $(COMP_OV) $(SOURCE)\VDPESSEL.C

$(LIB)\VDPESULT.OBJ: \
        $(SOURCE)\VDPESULT.C

        $(COMP_OV) $(SOURCE)\VDPESULT.C

$(LIB)\VDPESCVA.OBJ: \
        $(SOURCE)\VDPESCVA.C

        $(COMP_NO) $(SOURCE)\VDPESCVA.C

$(LIB)\VDPESMNT.OBJ: \
        $(SOURCE)\VDPESMNT.C

        $(COMP_OV) $(SOURCE)\VDPESMNT.C

$(LIB)\VDPESQ.LIB: \
        $(LIB)\VDPESACT.OBJ     \
        $(LIB)\VDPESDAT.OBJ     \
        $(LIB)\VDPESDPO.OBJ     \
        $(LIB)\VDPESLAT.OBJ     \
        $(LIB)\VDPESLPO.OBJ     \
        $(LIB)\VDPESPAT.OBJ     \
        $(LIB)\VDPESPPO.OBJ     \
        $(LIB)\VDPESPRI.OBJ     \
        $(LIB)\VDPESTER.OBJ     \
        $(LIB)\VDPESSEL.OBJ     \
        $(LIB)\VDPESULT.OBJ     \
        $(LIB)\VDPESDPI.OBJ     \
        $(LIB)\VDPESUSR.OBJ     \
        $(LIB)\VDPESMNT.OBJ
        DEL VDPESQ.LIB
        TLIB VDPESQ.LIB @PESQUISA.RSP > 15

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDPESCVA.OBJ \
        $(LIB)\VDPESUSE.OBJ
        TLIB VDMLHH.LIB -+VDPESCVA.OBJ -+VDPESUSE.OBJ > 15a
# =============================================================================
#
#      Fim de Make File - DIRETORIO "PESQUISA" (Funcoes de Pesquisa PLANILHA).
#
# =============================================================================













