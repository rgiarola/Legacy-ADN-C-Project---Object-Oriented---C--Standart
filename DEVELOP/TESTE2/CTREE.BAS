DefInt I
Declare Function BPtr2Lng Lib "pointers.dll" (sptr As Any) As Long
Declare Function BPtr2Str Lib "pointers.dll" (sptr As String) As Long
Declare Function GetERROR Lib "pointers.dll" (ctWNGV As Long, pint As Long) As Integer
Declare Function GetWindowTask Lib "User.dll" (ByVal hWnd As Integer) As Integer

Global ctWNGV As Long
Global ResFilno As Integer
Global filname As String

Declare Function ADDKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long, ByVal i) As Integer
Declare Function ADDREC Lib "ctreestd.dll" (ByVal i, p) As Integer
Declare Function ADDRES Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long) As Integer
Declare Function ADDVREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long) As Integer
Declare Function ALCSET Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function AVLFILNUM Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function BATSET Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long, ByVal l As Long, ByVal i) As Integer
Declare Function CHGSET Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function CLIFIL Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function CLIFIL Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function CLISAM Lib "ctreestd.dll" () As Integer
Declare Function CLRFIL Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function CLSFIL Lib "ctreestd.dll" (ByVal i, ByVal i) As Integer
Declare Function CREDAT Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long, ByVal i, ByVal i) As Integer
Declare Function CREDAT Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long, ByVal i, ByVal i) As Integer
Declare Function CREDATX Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long, ByVal i, ByVal i, ByVal l As Long, ByVal p As Long, p) As Integer
Declare Function CREIDX Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i, ByVal i, ByVal i, ByVal i, ByVal i, ByVal i) As Integer
Declare Function CREIFIL Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function CREIFILX Lib "ctreestd.dll" (ByVal p As Long, ByVal p As Long, ByVal p As Long, ByVal l As Long, ByVal p As Long, ByVal p As Long) As Integer
Declare Function CREIFILz Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function CREISAM Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function CREISAMX Lib "ctreestd.dll" (ByVal p As Long, ByVal i, ByVal p As Long, ByVal p As Long, ByVal p As Long, ByVal l As Long, ByVal p As Long, p) As Integer
Declare Function CREMEM Lib "ctreestd.dll" (ByVal i, ByVal i, ByVal i, ByVal i, ByVal i) As Integer
Declare Function ctdidx Lib "ctreestd.dll" (ByVal p As Long, ByVal i) As Long
Declare Function ctree Lib "ctreestd.dll" (ByVal i, ByVal i, ByVal p As Long, ByVal p As Long, ByVal p As Long, ByVal p As Long, ByVal i) As Integer
Declare Function cttseg Lib "ctreestd.dll" (ByVal i, ByVal i, ByVal i, ByVal p As Long, ByVal i, p) As Integer
Declare Function DATENT Lib "ctreestd.dll" (ByVal i) As Long
Declare Function DELBLD Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Long
Declare Function DELCHK Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long) As Integer
Declare Function DELFIL Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function DELIFIL Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function DELREC Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function DELRES Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function DELRFIL Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function DELVREC Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function ENARES Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function EQLKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Long
Declare Function EQLREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, p) As Integer
Declare Function ESTKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, p) As Long
Declare Function FRCKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i) As Long
Declare Function frmkey Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long, ByVal p As Long, ByVal l As Long) As Integer
Declare Function FRSKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Long
Declare Function FRSREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function FRSSET Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long, ByVal i) As Integer
Declare Function GETALTSEQ Lib "ctreestd.dll" (ByVal i, ByVal i) As Integer
Declare Function GETCTREE Lib "ctreestd.dll" (ByVal l As Long) As Integer
Declare Function GETCURK Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Long
Declare Function GETCURP Lib "ctreestd.dll" (ByVal i) As Long
Declare Function GETDEFBLK Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function GETDODA Lib "ctreestd.dll" (ByVal i, ByVal l As Long, ByVal p As Long, ByVal i) As Long
Declare Function GETFIL Lib "ctreestd.dll" (ByVal i, ByVal i) As Long
Declare Function GETIFIL Lib "ctreestd.dll" (ByVal i, ByVal l As Long, ByVal p As Long) As Long
Declare Function GETNAM Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVall As Long, ByVal i) As Integer
Declare Function GETRES Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long, ByVal l As Long, ByVal i) As Long
Declare Function GETVLEN Lib "ctreestd.dll" (ByVal i) As Long
Declare Function GTEKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Long
Declare Function GTEREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Integer
Declare Function GTREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Integer
Declare Function GTKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Long
Declare Function GTVLEN Lib "ctreestd.dll" (ByVal i, ByVal l As Long) As Long
Declare Function IDXENT Lib "ctreestd.dll" (ByVal i) As Long
Declare Function InitCtreeGV Lib "ctreestd.dll" () As Long
Declare Function INTISAM Lib "ctreestd.dll" (ByVal Bufs%, ByVal Files%, ByVal Sects%) As Integer
Declare Function INTISAMX Lib "ctreestd.dll" (ByVal i, ByVal i, ByVal i, ByVal i, ByVal i, ByVal p As Long, ByVal p As Long, ByVal p As Long) As Integer
Declare Function INTREE Lib "ctreestd.dll" (ByVal i, ByVal i, ByVal i) As Integer
Declare Function INTREEX Lib "ctreestd.dll" (ByVal i, ByVal i, ByVal i, ByVal i, ByVal i, ByVal p As Long, ByVal p As Long, ByVal p As Long) As Integer
Declare Function iTMPNAME Lib "ctreestd.dll" (ByVal p As Long, ByVal l As Long) As Integer
Declare Function LKISAM Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function LOADKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long, ByVal i) As Integer
Declare Function LOKREC Lib "ctreestd.dll" (ByVal i, ByVal i, ByVal l As Long) As Integer
Declare Function LSTKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Long
Declare Function LSTREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function LSTSET Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long, ByVal i) As Integer
Declare Function LTEKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Long
Declare Function LTEREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Integer
Declare Function LTREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Integer
Declare Function LTKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Long
Declare Function MIDSET Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i) As Integer
Declare Function NEWREC Lib "ctreestd.dll" (ByVal i) As Long
Declare Function NEWVREC Lib "ctreestd.dll" (ByVal i, ByVal l As Long) As Long
Declare Function NXTKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Long
Declare Function NXTREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function NXTSET Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function OPNFIL Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i) As Integer
Declare Function OPNFILX Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i, ByVal p As Long) As Integer
Declare Function OPNIFIL Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function OPNIFILX Lib "ctreestd.dll" (ByVal p As Long, ByVal p As Long, ByVal p As Long, ByVal p As Long) As Integer
Declare Function OPNIFILz Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function OPNISAM Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function OPNISAMX Lib "ctreestd.dll" (ByVal p As Long, ByVal i, ByVal p As Long, ByVal p As Long, ByVal p As Long, ByVal p As Long) As Integer
Declare Function OPNRFIL Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i) As Integer
Declare Function OPNRFILX Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i, ByVal p As Long) As Integer
Declare Function PRMIIDX Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function PRMIIDXz Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function PRVKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Long
Declare Function PRVREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function PRVSET Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function PUTDODA Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal i) As Integer
Declare Function PUTFIL Lib "ctreestd.dll" (ByVal i, ByVal i) As Integer
Declare Function RBLIFIL Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function RBLIFILX Lib "ctreestd.dll" (ByVal p As Long, ByVal i, ByVal p As Long, ByVall As Long, ByVal p As Long, ByVal p As Long) As Integer
Declare Function RBLIFILz Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function RDVREC Lib "ctreestd.dll" (ByVal i, ByVal l As Long, ByVal p As Long, ByVal l As Long) As Integer
Declare Function REDREC Lib "ctreestd.dll" (ByVal i, ByVal l As Long, ByVal p As Long) As Integer
Declare Function REDVREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long) As Integer
Declare Function REGCTREE Lib "ctreestd.dll" (ByVal l As Long) As Integer
Declare Function reset_cur Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal p As Long) As Integer
Declare Function RETREC Lib "ctreestd.dll" (ByVal i, ByVal l As Long) As Integer
Declare Function RETVREC Lib "ctreestd.dll" (ByVal i, ByVal l As Long) As Integer
Declare Function RRDREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function RWTREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function RWTVREC Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long) As Integer
Declare Function SECURITY Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVall As Long, ByVal i) As Integer
Declare Function SERIALNUM Lib "ctreestd.dll" (ByVal i) As Long
Declare Function SETALTSEQ Lib "ctreestd.dll" (ByVal i, ByVal i) As Integer
Declare Sub SetCtreeGV Lib "ctreestd.dll" (ByVal p As Long)
Declare Function SETCURI Lib "ctreestd.dll" (ByVal i, ByVal l As Long, ByVal p As Long, ByVal l As Long) As Integer
Declare Function SETDEFBLK Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function SETVARBYTS Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Integer
Declare Function TFRMKEY Lib "ctreestd.dll" (ByVal i, ByVal p As Long) As Long
Declare Function TMPIIDX Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function TMPIIDXX Lib "ctreestd.dll" (ByVal p As Long, ByVall As Long, ByVal p As Long, ByVal p As Long) As Integer
Declare Function TMPIIDXz Lib "ctreestd.dll" (ByVal p As Long) As Integer
Declare Function TMPNAME Lib "ctreestd.dll" (ByVal p As Long, ByVal l As Long) As Integer
Declare Function TRANBEG Lib "ctreestd.dll" (ByVal i) As Long
Declare Function TRANEND Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function TRANRST Lib "ctreestd.dll" (ByVal i) As Integer
Declare Function UPDCURI Lib "ctreestd.dll" (ByVal i, ByVal i) As Integer
Declare Function UPDRES Lib "ctreestd.dll" (ByVal i, ByVal p As Long, ByVal l As Long) As Integer
Declare Function WCHCTREE Lib "ctreestd.dll" () As Long
Declare Function WRTREC Lib "ctreestd.dll" (ByVal i, ByVal l As Long, ByVal p As Long) As Integer
Declare Function WRTVREC Lib "ctreestd.dll" (ByVal i, ByVal l As Long, ByVal p As Long, ByVal l As Long) As Integer

Type ISEG
    soffset As Integer
    slength As Integer
    segmode As Integer
End Type

Type IIDX
    ikeylen As Integer
    ikeytyp As Integer
    ikeydup As Integer
    inulkey As Integer
    iempchr As Integer
    inumseg As Integer
    seg     As Long
    ridxnam As Long
    aidxnam As Long
    altseq  As Long
    pvbyte  As Long
End Type

Type IFIL
    pfilnam As Long
    dfilno  As Integer
    dreclen As Integer 'Note limit to 32K
    dxtdsiz As Integer
    dfilmod As Integer
    dnumidx As Integer
    ixtdsiz As Integer
    ifilmod As Integer
    ix      As Long
    rfstfld As Long
    rlstfld As Long
    tfilno  As Integer
End Type

Type CMRType
    cm_custnumb   As String * 5
    cm_custzipc   As String * 10
    cm_custstat   As String * 3
    cm_custratg   As String * 2
    cm_custname   As String * 48
    cm_custstrt   As String * 48
    cm_custcity   As String * 48
End Type

Type CustRecType
    CustRec       As String * 1000
End Type

Type CustKeyType
    CustKeyBuff  As String * 5
End Type

Type RegCtreeType
    RegID    As String * 5
End Type

Global AccessMethod As Integer
Global CustLok      As IFIL
Global CustMast     As IFIL
Global CustMastIx   As IIDX
Global CustMastSeg  As ISEG
Global CustMastRec  As CMRType
Global CustBuff     As CustRecType
Global RegisterID   As RegCtreeType
Global CustKey      As CustKeyType

Global Const Filno = 1
Global Const Keyno = 2
Global Const curB = 0
Global Const updB = 1
Global Const chkB = 2

Global Const FixedRecLen = 113
Global Const CTFREE = 0
Global Const CTRESET = 1
Global Const CTENABLE = 2
Global Const CTENABLE_BLK = 3
Global Const CTREADREC = 4
Global Const CTSUSPEND = 5
Global Const CTRESTORE = 6
Global Const CTRESTRED = 7
Global Const CTRESTORE_BLK = 8
Global Const CTKEEP = 9
Global Const CTFREE_TRAN = 10

Global Const NO_ERROR = 0
Global Const KDUP_ERR = 2
Global Const KMAT_ERR = 3
Global Const KDEL_ERR = 4
Global Const KBLD_ERR = 5
Global Const BJMP_ERR = 6
Global Const SPAC_ERR = 10
Global Const SPRM_ERR = 11
Global Const FNOP_ERR = 12
Global Const FUNK_ERR = 13
Global Const FCRP_ERR = 14
Global Const FCMP_ERR = 15
Global Const KCRAT_ERR = 16
Global Const DCRAT_ERR = 17
Global Const KOPN_ERR = 18
Global Const DOPN_ERR = 19
Global Const KMIN_ERR = 20
Global Const DREC_ERR = 21
Global Const FNUM_ERR = 22
Global Const KMEM_ERR = 23
Global Const FCLS_ERR = 24
Global Const KLNK_ERR = 25
Global Const FACS_ERR = 26
Global Const LBOF_ERR = 27
Global Const ZDRN_ERR = 28
Global Const ZREC_ERR = 29
Global Const LEOF_ERR = 30
Global Const DELFLG_ERR = 31
Global Const DDRN_ERR = 32
Global Const DNUL_ERR = 33
Global Const PRDS_ERR = 34
Global Const SEEK_ERR = 35
Global Const READ_ERR = 36
Global Const WRITE_ERR = 37
Global Const VRTO_ERR = 38
Global Const FULL_ERR = 39
Global Const KSIZ_ERR = 40
Global Const UDLK_ERR = 41
Global Const DLOK_ERR = 42
Global Const FVER_ERR = 43
Global Const OSRL_ERR = 44
Global Const KLEN_ERR = 45
Global Const FUSE_ERR = 46
Global Const FINT_ERR = 47
Global Const FMOD_ERR = 48
Global Const FSAV_ERR = 49
Global Const LNOD_ERR = 50
Global Const UNOD_ERR = 51
Global Const KTYP_ERR = 52
Global Const FTYP_ERR = 53
Global Const REDF_ERR = 54
Global Const DLTF_ERR = 55
Global Const DLTP_ERR = 56
Global Const DADV_ERR = 57
Global Const KLOD_ERR = 58
Global Const KLOR_ERR = 59
Global Const KFRC_ERR = 60
Global Const CTNL_ERR = 61
Global Const LERR_ERR = 62
Global Const RSER_ERR = 63
Global Const RLEN_ERR = 64
Global Const RMEM_ERR = 65
Global Const RCHK_ERR = 66
Global Const RENF_ERR = 67
Global Const LALC_ERR = 68
Global Const BNOD_ERR = 69
Global Const TEXS_ERR = 70
Global Const TNON_ERR = 71
Global Const TSHD_ERR = 72
Global Const TLOG_ERR = 73
Global Const TRAC_ERR = 74
Global Const TROW_ERR = 75
Global Const TBAD_ERR = 76
Global Const TRNM_ERR = 77
Global Const TABN_ERR = 78
Global Const FLOG_ERR = 79
Global Const BKEY_ERR = 80
Global Const ATRN_ERR = 81
Global Const UALC_ERR = 82
Global Const IALC_ERR = 83
Global Const MUSR_ERR = 84
Global Const DEAD_ERR = 86
Global Const QIET_ERR = 87
Global Const LMEM_ERR = 88
Global Const TMEM_ERR = 89
Global Const NQUE_ERR = 90
Global Const QWRT_ERR = 91
Global Const QMRT_ERR = 92
Global Const QRED_ERR = 93
Global Const PNDG_ERR = 94
Global Const STSK_ERR = 95
Global Const LOPN_ERR = 96
Global Const SUSR_ERR = 97
Global Const BTMD_ERR = 98
Global Const TTYP_ERR = 99
Global Const ICUR_ERR = 100
Global Const INOT_ERR = 101
Global Const INOD_ERR = 102
Global Const IGIN_ERR = 103
Global Const IFIL_ERR = 104
Global Const IUND_ERR = 105
Global Const IDRI_ERR = 106
Global Const IDRK_ERR = 107
Global Const IMKY_ERR = 108
Global Const IKRS_ERR = 109
Global Const ISRC_ERR = 110
Global Const IKRI_ERR = 111
Global Const IPND_ERR = 112
Global Const INOL_ERR = 113
Global Const IRED_ERR = 114
Global Const ISLN_ERR = 115
Global Const IMOD_ERR = 116
Global Const IMRI_ERR = 117
Global Const SKEY_ERR = 118
Global Const SKTY_ERR = 119
Global Const RRLN_ERR = 120
Global Const RSPC_ERR = 121
Global Const RMOD_ERR = 122
Global Const RVHD_ERR = 123
Global Const INIX_ERR = 124
Global Const IINT_ERR = 125
Global Const ABDR_ERR = 126
Global Const ARQS_ERR = 127
Global Const ARSP_ERR = 128
Global Const NINT_ERR = 129
Global Const AFNM_ERR = 130
Global Const AFLN_ERR = 131
Global Const ASPC_ERR = 132
Global Const ASKY_ERR = 133
Global Const ASID_ERR = 134
Global Const AAID_ERR = 135
Global Const AMST_ERR = 136
Global Const AMQZ_ERR = 137
Global Const AMRD_ERR = 138
Global Const ABNM_ERR = 139
Global Const VMAX_ERR = 140
Global Const AMSG_ERR = 141
Global Const SMXL_ERR = 142
Global Const SHND_ERR = 143
Global Const QMEM_ERR = 144
Global Const ALOG_ERR = 145
Global Const VDLK_ERR = 146
Global Const VDLFLG_ERR = 147
Global Const VLEN_ERR = 148
Global Const VRLN_ERR = 149
Global Const SHUT_ERR = 150
Global Const STRN_ERR = 151
Global Const LEXT_ERR = 152
Global Const VBSZ_ERR = 153
Global Const VRCL_ERR = 154
Global Const SYST_ERR = 155
Global Const VFLG_ERR = 158
Global Const VPNT_ERR = 159
Global Const ITIM_ERR = 160
Global Const SINA_ERR = 161
Global Const SGON_ERR = 162
Global Const SFRE_ERR = 163
Global Const SFIL_ERR = 164
Global Const SNFB_ERR = 165
Global Const SNMC_ERR = 166
Global Const SRQS_ERR = 167
Global Const SRSP_ERR = 168
Global Const TCRE_ERR = 169
Global Const SFUN_ERR = 170
Global Const SMSG_ERR = 171
Global Const SSPC_ERR = 172
Global Const SSKY_ERR = 173
Global Const SSID_ERR = 174
Global Const SAMS_ERR = 175
Global Const SMST_ERR = 176
Global Const SMQZ_ERR = 177
Global Const SINM_ERR = 178
Global Const SOUT_ERR = 179
Global Const IKRU_ERR = 180
Global Const IKMU_ERR = 181
Global Const IKSR_ERR = 182
Global Const IDRU_ERR = 183
Global Const ISDP_ERR = 184
Global Const ISAL_ERR = 185
Global Const ISNM_ERR = 186
Global Const IRBF_ERR = 187
Global Const ITBF_ERR = 188
Global Const IJSK_ERR = 189
Global Const IJER_ERR = 190
Global Const IJNL_ERR = 191
Global Const IDSK_ERR = 192
Global Const IDER_ERR = 193
Global Const IDNL_ERR = 194
Global Const IDMU_ERR = 195
Global Const ITML_ERR = 196
Global Const IMEM_ERR = 197
Global Const BIFL_ERR = 198
Global Const NSCH_ERR = 199
Global Const RCRE_ERR = 400
Global Const RNON_ERR = 401
Global Const RXCL_ERR = 402
Global Const RZRO_ERR = 403
Global Const RBUF_ERR = 404
Global Const RDUP_ERR = 405
Global Const RCSE_ERR = 406
Global Const RRED_ERR = 407
Global Const RNOT_ERR = 408
Global Const USTP_ERR = 410
Global Const BSUP_ERR = 411
Global Const SDIR_ERR = 413
Global Const SNST_ERR = 414
Global Const SADD_ERR = 415
Global Const SDEL_ERR = 416
Global Const SPAG_ERR = 417
Global Const SNAM_ERR = 418
Global Const SRCV_ERR = 419
Global Const TPND_ERR = 420
Global Const BTFL_ERR = 421
Global Const BTFN_ERR = 422
Global Const BTIC_ERR = 423
Global Const BTAD_ERR = 424
Global Const BTIP_ERR = 425
Global Const BTNO_ERR = 426
Global Const BTST_ERR = 427
Global Const BTMT_ERR = 428
Global Const BTBZ_ERR = 429
Global Const BTRQ_ERR = 430
Global Const FLEN_ERR = 432
Global Const SSCH_ERR = 433
Global Const DLEN_ERR = 434
Global Const FMEM_ERR = 435
Global Const DNUM_ERR = 436
Global Const DADR_ERR = 437
Global Const DZRO_ERR = 438
Global Const DCNV_ERR = 439
Global Const DDDM_ERR = 440
Global Const DMEM_ERR = 441
Global Const DAVL_ERR = 442
Global Const DSIZ_ERR = 443
Global Const DCRE_ERR = 444
Global Const SDAT_ERR = 445
Global Const BMOD_ERR = 446
Global Const BOWN_ERR = 447
Global Const DEFP_ERR = 448
Global Const LUID_ERR = 450
Global Const LPWD_ERR = 451
Global Const LSRV_ERR = 452
Global Const NSRV_ERR = 453
Global Const SGRP_ERR = 455
Global Const SACS_ERR = 456
Global Const SPWD_ERR = 457
Global Const SWRT_ERR = 458
Global Const SDLT_ERR = 459
Global Const SRES_ERR = 460
Global Const SPER_ERR = 461
Global Const SHDR_ERR = 462
Global Const UQID_ERR = 463
Global Const IISM_ERR = 464
Global Const IINI_ERR = 465
Global Const IIDT_ERR = 466
Global Const IINM_ERR = 467
Global Const IITR_ERR = 468
Global Const SORT_ERR = 370
Global Const SQLINIT_ERR = 500
Global Const SQLCONNECT_ERR = 501
Global Const SQL_REQUEST_ERROR = 502
Global Const SQL_INVALID_CONTINUE = 503
Global Const NSQL_ERR = 504
Global Const USQL_ERR = 505
Global Const ISAM_METHOD = 0
Global Const IFIL_METHOD = 1

Global Const Bufs = 4
Global Const Files = 5
Global Const Sects = 16

Dim cterr As Integer

Global Const reclen = 0
Global Const KEYLEN = 1
Global Const FILTYP = 2
Global Const filmod = 3
Global Const REVMAP = 4
Global Const KEYTYP = 5
Global Const KEYDUP = 6
Global Const LOGSIZ = 10
Global Const PHYSIZ = 11
Global Const NODSIZ = 12
Global Const KEYMEM = 13
Global Const KEYPAD = 14
Global Const FLDELM = 15
Global Const RECPAD = 16
Global Const MIRRST = 17
Global Const RELKEY = 18

Global Const EXCLUSIVE = 0
Global Const ctSHARED = 1
Global Const VIRTUAL = 0
Global Const PERMANENT = 2
Global Const ctFIXED = 0
Global Const VLENGTH = 4
Global Const READFIL = 8
Global Const PREIMG = 16
Global Const TRNLOG = 48
Global Const WRITETHRU = 64
Global Const CHECKLOCK = 128
Global Const DUPCHANEL = 256
Global Const SUPERFILE = 512
Global Const CHECKREAD = 1024
Global Const DISABLERES = 2048
Global Const MIRROR_SKP = 8192
Global Const OPENCRPT = 16384

Global Const CT_BOOL = 8
Global Const CT_CHAR = 16
Global Const CT_CHARU = 24
Global Const CT_INT2 = 33
Global Const CT_INT2U = 41
Global Const CT_INT4 = 51
Global Const CT_INT4U = 59
Global Const CT_MONEY = 67
Global Const CT_DATE = 75
Global Const CT_TIME = 83
Global Const CT_SFLOAT = 91
Global Const CT_DFLOAT = 103
Global Const CT_SQLBCDold = 107
Global Const CT_SQLBCD = 108
Global Const CT_EFLOAT = 111
Global Const CT_TIMESold = 123
Global Const CT_TIMES = 124
Global Const CT_ARRAY = 128
Global Const CT_RESRVD = 136
Global Const CT_FSTRING = 144
Global Const CT_FPSTRING = 152
Global Const CT_F2STRING = 160
Global Const CT_F4STRING = 168
Global Const CT_STRING = 146
Global Const CT_PSTRING = 154
Global Const CT_2STRING = 162
Global Const CT_4STRING = 170

Type DodRec
        pSym As Long
        pAdr As Long
        fTyp As Integer
        fLen As Integer
        dwhat As Integer
        dlev As Integer
        fhrc As Integer
        frsv As Integer
        fusrp As Long
        frsrv As Long
End Type



Global IFILS() As IFIL
Global IIDXS() As IIDX
Global ISEGS() As ISEG
Rem======CONSTANTS==========================================================
Global Const ifil_top = 10  ''' absolute maximum number of ifils allowed
Global Const seg_top = 12        ''' absolute maximum number of segments allowed
Global Const smmax = 5  ''' maximum segment mode allowed
Global Const ix_top = 30   ''' absolute maximum number of indexes allowed
Global Const MAXFIXED = 128  ''' maximum fixed length portion of record
Global Const max_keyl = 30  ''' maximum key length allowed
Global Const max_seglen = 30   '''maximum segment length allowed
Global Const max_keytyp = 4    ''' number of key types allowed (0,4,8,12)
Global Const MAXSTRING = 1000  '''longest string allowed as a field in a record
Rem======CONSTANTS END========================================================
Rem =====VARIABLES==========================================================
Rem The following are some global variable and constants that will be needed
Rem in constructing the RANDOM program:
Global TotSeg As Integer  ''' Total number of ISEG allocated so far
Global TotIdx As Integer  ''' Total number of IIDX allocated so far
Global ifilmax As Integer   ''' max. number of ifils in a run
Rem Global cterr As Integer
Global curpath$

Global ixmax As Integer     ''' max. number of indexes for a run

Global segmax As Integer    ''' max. number of segments for a run

Global trlen As Integer
Global ixtot As Integer
Global segtot As Integer
Global Const r1$ = "First"
Global Const r2$ = "Last"
Global nam As String
Global NumberOfIdx() As Integer
Global LengthOfIdx() As Integer
Global TypeOfIdx() As Integer
Global NumberOfSeg() As Integer
Global LengthOfSeg() As Integer
Global OffsetOfSeg() As Integer
Global ModeOfSeg() As Integer
Rem Global FixedRecLen() As Integer
Global FilStats() As Integer
Global SchemaTyp(28) As Integer
Global SchemaLen() As Integer
Global SchemaSegs() As Integer
Rem Global VarLen() As Integer
Global VLnum As Integer
Global cumidx As Integer
Global cumseg As Integer
Global pNull As Long

Global Parms() As Integer
Global Doda()  As DodRec
Global Symbol() As String
Rem ====VARIABLES END=========================================================

