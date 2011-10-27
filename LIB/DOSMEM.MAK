# =============================================================================
# MAKE FILE -
#               Responsavel pela administracao e compilacao
#               dos arquivos descritos no diretorio "DOSMEM",
#               de gerenciamento de memoria.
#
# =============================================================================
!include "AMBIENTE.MAC"

# <<<<<<   Diretorios de Arquivos.  >>>>>>
SOURCE=$(DRIVE)\ADN2\DOSMEM


# Arquivos Alvo para a Construcao de Objetos.
# Diretorio DOSMEM
OBJETOS_TELA: \
        $(LIB)\VDDOSALM.OBJ     \
        $(LIB)\VDDOSFRM.OBJ     \
        $(LIB)\VDMLHH.LIB


# <<<<<<<<<<      Diretorio DOSMEM.     >>>>>>>>>>
$(LIB)\VDDOSALM.OBJ: \
        $(SOURCE)\VDDOSALM.C

        $(COMP_HH) $(SOURCE)\VDDOSALM.C

$(LIB)\VDDOSFRM.OBJ: \
        $(SOURCE)\VDDOSFRM.C

        $(COMP_HH) $(SOURCE)\VDDOSFRM.C


$(LIB)\VDMLHH.LIB: \
        $(LIB)\VDDOSALM.OBJ     \
        $(LIB)\VDDOSFRM.OBJ
        TLIB VDMLHH.LIB -+VDDOSALM.OBJ -+VDDOSFRM.OBJ > 7


# =============================================================================
#
#      Fim de Make File - DIRETORIO "DOSMEM" Gerenciamento de Memoria via DOS.
#
# =============================================================================

