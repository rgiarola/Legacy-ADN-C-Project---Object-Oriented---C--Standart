#define VIDEO_ERRO_monta_arvore                  I(-1) //VDARVACT
#define VIDEO_ERRO_objeto_nao_carregado          I(-2) //VDCALDSP
#define VIDEO_ERRO_doda_ini_nao_encontrado       I(-3) //VDCRGEDB
#define VIDEO_ERRO_doda_fim_nao_encontrado       I(-4) //VDCRGEDB
#define VIDEO_ERRO_doda_nao_encontrado           I(-5) //VDCRGEDT
#define VIDEO_ERRO_nome_ind_arq_nao_encontrado   I(-6) //VDCRGENA
#define VIDEO_ERRO_nome_ind_sub_nao_encontrado   I(-7) //VDCRGENA
#define VIDEO_ERRO_nome_ind_cons_nao_encontrado  I(-8) //VDCRGENI
#define VIDEO_ERRO_nome_ind_plan_nao_encontrado  I(-9) //VDCRGENI
#define VIDEO_ERRO_doda_ini_buf_nao_encontrado   I(-10)//VDCRGIDB
#define VIDEO_ERRO_end_espelho                   I(-11)//VDCRGIDB
#define VIDEO_ERRO_end_consistencia_campo        I(-12)//VDCRTECP
#define VIDEO_ERRO_tela_nao_encontrada           I(-13)//VDCRTEXT
#define VIDEO_ERRO_end_arquivo_tela              I(-14)//VDCRTPTE
#define VIDEO_ERRO_end_doda_tela                 I(-15)//VDCRTPTE
#define VIDEO_ERRO_end_ind_tela                  I(-16)//VDCRTPTE
#define VIDEO_ERRO_ifil_crg_tela_nao_encontrado  I(-17)//VDCRTTEL
#define VIDEO_ERRO_tmpfil_tela_nao_encontrado    I(-18)//VDCRTTEL
#define VIDEO_ERRO_tab_func_nao_ordenada         I(-19)//VDCRGARQ
#define VIDEO_ERRO_tab_elem_nao_ordenada         I(-20)//VDCRGARQ
#define VIDEO_ERRO_add_rec_ctcopy                I(-21)//CTCOPY
#define VIDEO_ERRO_rew_rec_ctcopy                I(-22)//CTCOPY
#define VIDEO_ERRO_close_arq_tmp                 I(-23)//CTDELTMP
#define VIDEO_ERRO_getbuf_doda                   I(-24)//CTGETBUF
#define VIDEO_ERRO_filnrg_incompativel           I(-25)//CTISCRIA
#define VIDEO_ERRO_posicao_seguinte              I(-26)//CTOPEN2
#define VIDEO_ERRO_reg_red_alterado              I(-27)//CTREWREC
#define VIDEO_ERRO_posicao_seguinte_cttemp       I(-28)//CTTEMP
#define VIDEO_ERRO_cria_tmp_cttemp               I(-29)//CTTEMP
#define VIDEO_ERRO_open_tmp_cttemp               I(-30)//CTTEMP
#define VIDEO_ERRO_tela_plan_nao_encontrada 	 I(-31)//VDPESACT
#define VIDEO_ERRO_tela_plan_nao_preparada		 I(-32)//VDPESACT
#define VIDEO_ERRO_funcao_nao_encontrada		 I(-33)//VDPESACT
#define VIDEO_ERRO_arquivo_planilha_vazio		 I(-34)//VDPESACT
#define VIDEO_ERRO_posic_planilha_errado         I(-35)//VDPESCVA
#define VIDEO_ERRO_fim_arq_planilha              I(-36)//VDPESCVA
#define VIDEO_ERRO_ini_arq_planilha              I(-37)//VDPESCVA
#define VIDEO_ERRO_ini_arq_planilha_lat          I(-38)//VDPESLAT
#define VIDEO_ERRO_ini_arq_planilha_lpo          I(-39)//VDPESLPO
#define VIDEO_ERRO_arq_planilha_vazio_pri        I(-40)//VDPESPRI
#define VIDEO_ERRO_rereadrec_planilha            I(-41)//VDPESSEL
#define VIDEO_ERRO_arq_planilha_vazio_ult        I(-42)//VDPESPRI
#define VIDEO_ERRO_funcao_serv_nao_encontrada    I(-43)//VDPESACT
#define VIDEO_ERRO_rewrec_tela                   I(-44)//VDTELALT
#define VIDEO_ERRO_montagem_faixa                I(-45)//VDTELALT
#define VIDEO_ERRO_cons_validacao                I(-46)//VDTELCON
#define VIDEO_ERRO_cons_dupkey                   I(-113)//VDTELCON
#define VIDEO_ERRO_cons_ret_dupkey               I(-47)//VDTELCON
#define VIDEO_ERRO_funcao_consistencia           I(-48)//VDTELCON
#define VIDEO_ERRO_tipo_consistencia_invalido    I(-49)//VDTELCON
#define VIDEO_ERRO_posiciciona_disp_pesq         I(-50)//VDTELDBU
#define VIDEO_ERRO_arquivo_vazio_pri             I(-51)//VDTELDFR
#define VIDEO_ERRO_arquivo_vazio_ult             I(-52)//VDTELDLS
#define VIDEO_ERRO_registro_nao_enc_maior        I(-53)//VDTELDMA
#define VIDEO_ERRO_registro_nao_enc_menor        I(-54)//VDTELDME
#define VIDEO_ERRO_tela_manutencao               I(-55)//VDTELDMN
#define VIDEO_ERRO_prep_tela_manutencao          I(-56)//VDTELDMN
#define VIDEO_ERRO_buffer_arquivo_manut 		 I(-57)//VDTELDMN
#define VIDEO_ERRO_ifil_arquivo_manut			 I(-58)//VDTELDMN
#define VIDEO_ERRO_offrec_arquivo_manut 		 I(-59)//VDTELDMN
#define VIDEO_ERRO_rest_offrec_arquivo_manut	 I(-60)//VDTELDMN
#define VIDEO_ERRO_edicao_de_linha				 I(-61)//VDTELEDC
#define VIDEO_ERRO_ini_buffer_inclusao			 I(-62)//VDTELINC
#define VIDEO_ERRO_del_arq_tmp					 I(-63)//VDTELLSU
#define VIDEO_ERRO_addrec_tela					 I(-64)//VDTELSIN
#define VIDEO_ERRO_ini_buffer_addrec			 I(-65)//VDTELSIN
#define VIDEO_ERRO_del_arq_sub					 I(-66)//VDTELSSB
#define VIDEO_ERRO_copy_arq_sub 				 I(-67)//VDTELSSB
#define VIDEO_ERRO_ifil_arquivo_tela			 I(-68)//VDTELTED
#define VIDEO_ERRO_posicao_arquivo_tela 		 I(-69)//VDTELTED
#define VIDEO_ERRO_ifil_sub_tela				 I(-70)//VDTELTED
#define VIDEO_ERRO_copy_arq_sub_ted 			 I(-71)//VDTELTED
#define VIDEO_ERRO_del_arq_sub_ted				 I(-72)//VDTELTED
#define VIDEO_ERRO_del_arq_sub_tes				 I(-73)//VDTELTED
#define VIDEO_ERRO_copy_arq_sub_tes 			 I(-74)//VDTELTED
#define VIDEO_ERRO_exclusao 					 I(-75)//VDTELTEX
#define VIDEO_ERRO_doda_sub_nao_encontrado		 I(-76)//VDTELTSG
#define VIDEO_ERRO_funcao_tela_serv_nao_enc 	 I(-77)//VDTELUSR
#define VIDEO_ERRO_inic_buffer_tela 			 I(-78)//VDTELACT
#define VIDEO_ERRO_doda_tela_nao_encontrado 	 I(-79)//VDTELACT
#define VIDEO_ERRO_segconst_tela_nao_def         I(-80)//VDTELACT
#define VIDEO_ERRO_cria_tmp_tela				 I(-81)//VDTELACT
#define VIDEO_ERRO_copy_arq_sub_act 			 I(-82)//VDTELACT
#define VIDEO_ERRO_display_imagem_fundo 		 I(-83)//VDTELACT
#define VIDEO_ERRO_carga_tela_visual			 I(-84)//VDVISACT
#define VIDEO_ERRO_prep_tela_visual 			 I(-85)//VDVISACT
#define VIDEO_ERRO_current_isam_ctcopy           I(-86)//CTCOPY
#define VIDEO_ERRO_rest_offrec_isam_ctcopy       I(-87)//CTCOPY
#define VIDEO_ERRO_ifil_arq_pesq_nao_enc		 I(-88)//VDTELDBU
#define VIDEO_ERRO_tipo_campo_inval_men          I(-89)//VDTELMEN
#define VIDEO_ERRO_tipo_campo_inval_mma          I(-90)//VDTELMMA
#define VIDEO_ERRO_tipo_campo_invalido           I(-91)//VDTELMEN

#define VIDEO_ERRO_carga_open_arq_path           I(-92)//VDCRGARQ
#define VIDEO_ERRO_carga_tam_arq_path            I(-93)//VDCRGARQ
#define VIDEO_ERRO_carga_read_arq_path           I(-94)//VDCRGARQ
#define VIDEO_ERRO_carga_oper_arq_crg            I(-95)//VDCRGARQ
#define VIDEO_ERRO_carga_ler_arq_crg             I(-96)//VDCRGARQ
#define VIDEO_ERRO_carga_tam_arq_crg             I(-97)//VDCRGARQ
#define VIDEO_ERRO_carga_alloc_arq_crg           I(-98)//VDCRGARQ
#define VIDEO_ERRO_carga_arq_crg                 I(-99)//VDCRGARQ
#define VIDEO_ERRO_carga_sort_doda               I(-100)//VDCRGARQ
#define VIDEO_ERRO_carga_alloc_doda_buffer       I(-101)//VDCRGARQ
#define VIDEO_ERRO_carga_end_doda_buffer         I(-102)//VDCRGARQ
#define VIDEO_ERRO_carga_end_doda_espelho        I(-103)//VDCRGARQ
#define VIDEO_ERRO_carga_end_estru_elem          I(-104)//VDCRGARQ

#define VIDEO_ERRO_GERWIN_param_invalidos        I(-105)//VDGERWIN
#define VIDEO_ERRO_GERWIN_estouro_descr          I(-106)//VDGERWIN
#define VIDEO_ERRO_GERWIN_num_desc_win           I(-107)//VDGERWIN popwin underflow
#define VIDEO_ERRO_GERWIN_num_window             I(-108)//VDGERWIN getwin
#define VIDEO_ERRO_GERWIN_mem_usada              I(-108)//VDGERWIN
#define VIDEO_ERRO_GERWIN_num_window_del         I(-110)//VDGERWIN getwin

#define VIDEO_ERRO_OPERTE_param_invalido         I(-111)//VDOPERTE
#define VIDEO_ERRO_OPERTE_servico_invalido       I(-112)//VDOPERTE
#define VIDEO_ERRO_OPERTE_servico_invalido       I(-112)//VDOPERTE

#define VIDEO_ERRO_arquivo_saida_rtree           I(-114)//RTPREP
#define VIDEO_ERRO_arquivo_entrada_rtree         I(-116)//RTPREP
#define VIDEO_ERRO_1_buffer_prep_danificado      I(-117)//RTPREP
#define VIDEO_ERRO_2_buffer_prep_danificado      I(-118)//RTPREP
#define VIDEO_ERRO_3_buffer_prep_danificado      I(-119)//RTPREP
#define VIDEO_ERRO_buffer_lido_inconsistente     I(-120)//RTPREP
#define VIDEO_ERRO_include_de_arquivo            I(-121)//RTPREP
#define VIDEO_ERRO_inclusao_path_no_arquivo      I(-122)//RTPREP
#define VIDEO_ERRO_analise_de_linha              I(-123)//RTPREP
#define VIDEO_ERRO_estrutura_comentario          I(-124)//RTPREP
#define VIDEO_ERRO_doda_nao_encontrado_linha     I(-125)//RTPREP
#define VIDEO_ERRO_doda_nao_definido_tabela      I(-126)//RTPREP
#define VIDEO_ERRO_caracter_definicao_nao_def    I(-127)//RTPREP
#define VIDEO_ERRO_analise_de_linha_2            I(-128)//RTPREP
#define VIDEO_ERRO_analise_de_linha_3            I(-129)//RTPREP
#define VIDEO_ERRO_analise_de_linha_4            I(-130)//RTPREP
#define VIDEO_ERRO_analise_de_linha_5            I(-131)//RTPREP
#define VIDEO_ERRO_tamanho_buffer                I(-132)//RTPREP
#define VIDEO_ERRO_arquivo_balance_line 		 I(-133)//VDTELSSB
#define VIDEO_ERRO_getchave_balance_line         I(-134)//VDTELSSB
#define VIDEO_ERRO_alocacao_chave_origem         I(-135)//VDTELSSB
#define VIDEO_ERRO_alocacao_chave_destino        I(-136)//VDTELSSB
#define VIDEO_ERRO_adrec_balance_line            I(-137)//VDTELSSB
#define VIDEO_ERRO_rewrec_balance_line           I(-138)//VDTELSSB
#define VIDEO_ERRO_dlrec_balance_line            I(-139)//VDTELSSB
#define VIDEO_ERRO_fim_definicao_script          I(-140)//VDTELSSB
#define VIDEO_ERRO_operando_doda				 I(-141)//VDCPLOG
#define VIDEO_ERRO_controle_carga                I(-142)//VDCRTFRT
#define VIDEO_ERRO_grupo_nao_encontrado          I(-143)//VDACSOBJ
#define VIDEO_ERRO_acesso_danificado             I(-144)//VDACSOBJ

//#define I(-143)

/*
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    VIDEO_PESQ_mens_ini_arquivo,
                    (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(pesquisa->indice))->reduzido,
                    ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,
                            isam_err != 101                ?
                            VIDEO_ERRO_ini_arq_planilha_lat:
                            TRUE                           );
*/
