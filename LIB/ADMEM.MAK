# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "ADMEM",
#               de gerenciamento de memoria.
#
# =============================================================================

!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\ADMEM


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio ADMEM
OBJETOS_TELA: \
        $(LIB)\VDADMALC.OBJ     \
        $(LIB)\VDADMFRE.OBJ     \
        $(LIB)\VDADMLOC.OBJ     \
        $(LIB)\VDADMORG.OBJ     \
        $(LIB)\VDADMVAR.OBJ     \
        $(LIB)\VDMLHH.LIB

# <<<<<<<<<<<<<<<  Diretorio ADMEM: >>>>>>>>>>>>>>
$(LIB)\VDADMALC.OBJ: \
        $(SOURCE)\VDADMALC.C

        $(COMPHH) $(SOURCE)\VDADMALC.C

$(LIB)\VDADMFRE.OBJ: \
        $(SOURCE)\VDADMFRE.C

        $(COMPHH) $(SOURCE)\VDADMFRE.C

$(LIB)\VDADMLOC.OBJ: \
        $(SOURCE)\VDADMLOC.C

        $(COMPHH) $(SOURCE)\VDADMLOC.C

$(LIB)\VDADMORG.OBJ: \
        $(SOURCE)\VDADMORG.C

        $(COMPHH) $(SOURCE)\VDADMORG.C

$(LIB)\VDADMVAR.OBJ: \
        $(SOURCE)\VDADMVAR.C

        $(COMPHH) $(SOURCE)\VDADMVAR.C

$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDADMALC.OBJ     \
        $(LIB)\VDADMFRE.OBJ     \
        $(LIB)\VDADMLOC.OBJ     \
        $(LIB)\VDADMORG.OBJ     \
        $(LIB)\VDADMVAR.OBJ
        TLIB VDMLHH   @ADMEM.RSP > 1

# =============================================================================
#
#      Fim de Make File - DIRETORIO "ADMEM" Gerenciamento de Memoria.
#
# =============================================================================



