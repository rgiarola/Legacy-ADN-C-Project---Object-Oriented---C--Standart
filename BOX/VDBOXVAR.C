#include <INCVIDEO.H>

#if defined(__VIDEO_BOX_CARGA_PARAMETROS)
        VIDEO_BOX_PARAMETROS *VIDEO_box_parametros =
                             VD_NILL(VIDEO_BOX_PARAMETROS);
#else
 char        VIDEO_conec_se_dupla[]   = { 0xC9, '\0' },
             VIDEO_conec_sd_dupla[]   = { 0xBB, '\0' },
             VIDEO_conec_ie_dupla[]   = { 0xC8, '\0' },
             VIDEO_conec_id_dupla[]   = { 0xBC, '\0' },
             VIDEO_conec_se_simples[] = { 0xDA, '\0' },
             VIDEO_conec_sd_simples[] = { 0xBF, '\0' },
             VIDEO_conec_ie_simples[] = { 0xC0, '\0' },
             VIDEO_conec_id_simples[] = { 0xD9, '\0' },
             VIDEO_conec_se_carac[]   = { 0x00, '\0' },
             VIDEO_conec_sd_carac[]   = { 0x00, '\0' },
             VIDEO_conec_ie_carac[]   = { 0x00, '\0' },
             VIDEO_conec_id_carac[]   = { 0x00, '\0' },
             VIDEO_conec_col_dupla    = 0xBA,
             VIDEO_conec_col_simples  = 0xB3,
             VIDEO_conec_col_carac    = 0x00,
             VIDEO_conec_lin_dupla    = 0xCD,
             VIDEO_conec_lin_simples  = 0xC4,
             VIDEO_conec_lin_carac    = 0x00;
#endif


