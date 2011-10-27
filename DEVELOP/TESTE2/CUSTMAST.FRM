VERSION 2.00
Begin Form custmast1 
   Caption         =   "Custmast - Variable Length Records Sample"
   ClientHeight    =   3480
   ClientLeft      =   225
   ClientTop       =   1485
   ClientWidth     =   8955
   Height          =   3885
   Left            =   165
   LinkTopic       =   "custmast"
   ScaleHeight     =   3480
   ScaleWidth      =   8955
   Top             =   1140
   Width           =   9075
   Begin CommandButton PB_LTRecord 
      Caption         =   "GETLTRecord"
      Height          =   255
      Left            =   4080
      TabIndex        =   27
      Top             =   2400
      Width           =   1335
   End
   Begin CommandButton PB_GTRecord 
      Caption         =   "GETGTRecord"
      Height          =   255
      Left            =   4080
      TabIndex        =   26
      Top             =   2040
      Width           =   1335
   End
   Begin CommandButton PB_LTERecord 
      Caption         =   "LTERecord"
      Height          =   255
      Left            =   2760
      TabIndex        =   25
      Top             =   2760
      Width           =   1215
   End
   Begin CommandButton PB_GTERecord 
      Caption         =   "GTERecord"
      Height          =   255
      Left            =   2760
      TabIndex        =   24
      Top             =   2400
      Width           =   1215
   End
   Begin CommandButton PB_GetRecord 
      Caption         =   "GetRecord"
      Height          =   255
      Left            =   2760
      TabIndex        =   23
      Top             =   2040
      Width           =   1215
   End
   Begin TextBox Text14 
      BorderStyle     =   0  'None
      Height          =   285
      Left            =   7320
      TabIndex        =   22
      TabStop         =   0   'False
      Text            =   "Status"
      Top             =   1200
      Width           =   615
   End
   Begin CommandButton PB_LastRecord 
      Caption         =   "LastRecord"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   3120
      Width           =   1215
   End
   Begin CommandButton PB_ClearFields 
      Caption         =   "Clear/Fields"
      Height          =   255
      Left            =   1440
      TabIndex        =   17
      Top             =   3120
      Width           =   1215
   End
   Begin TextBox cm_custratg 
      Height          =   285
      Left            =   7440
      MaxLength       =   1
      TabIndex        =   6
      Top             =   1560
      Width           =   255
   End
   Begin TextBox Text12 
      BorderStyle     =   0  'None
      Height          =   285
      Left            =   6240
      TabIndex        =   21
      TabStop         =   0   'False
      Text            =   "Zip Code"
      Top             =   1200
      Width           =   855
   End
   Begin TextBox Text11 
      BorderStyle     =   0  'None
      Height          =   285
      Left            =   5520
      TabIndex        =   20
      TabStop         =   0   'False
      Text            =   "State"
      Top             =   1200
      Width           =   495
   End
   Begin CommandButton PB_UpdRecord 
      Caption         =   "UpdRecord"
      Height          =   255
      Left            =   1440
      TabIndex        =   18
      Top             =   2760
      Width           =   1215
   End
   Begin CommandButton PB_DelRecord 
      Caption         =   "DelRecord"
      Height          =   255
      Left            =   1440
      TabIndex        =   16
      Top             =   2400
      Width           =   1215
   End
   Begin CommandButton PB_AddRecord 
      Caption         =   "AddRecord"
      Height          =   255
      Left            =   1440
      TabIndex        =   15
      Top             =   2040
      Width           =   1215
   End
   Begin CommandButton PB_PrevRecord 
      Caption         =   "PrevRecord"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   2760
      Width           =   1215
   End
   Begin CommandButton PB_Close_Exit 
      Caption         =   "Close/Exit"
      Height          =   255
      Left            =   2760
      TabIndex        =   19
      Top             =   3120
      Width           =   1215
   End
   Begin CommandButton PB_NextRecord 
      Caption         =   "NextRecord"
      Enabled         =   0   'False
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   2400
      Width           =   1215
   End
   Begin CommandButton PB_FirstRecord 
      Caption         =   "FirstRecord"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   2040
      Width           =   1215
   End
   Begin TextBox cm_custzipc 
      DataField       =   "cm_custzipd"
      Height          =   285
      Left            =   6120
      MaxLength       =   9
      TabIndex        =   5
      Top             =   1560
      Width           =   1215
   End
   Begin TextBox cm_custstat 
      DataField       =   "cm_custratg"
      Height          =   285
      Left            =   5520
      MaxLength       =   2
      TabIndex        =   4
      Top             =   1560
      Width           =   375
   End
   Begin TextBox cm_custcity 
      DataField       =   "cm_custcity"
      Height          =   285
      Left            =   1320
      MaxLength       =   47
      TabIndex        =   3
      Top             =   1560
      Width           =   3975
   End
   Begin TextBox Text7 
      BorderStyle     =   0  'None
      Height          =   285
      Left            =   0
      TabIndex        =   10
      TabStop         =   0   'False
      Text            =   "City:"
      Top             =   1560
      Width           =   495
   End
   Begin TextBox cm_custstrt 
      DataField       =   "cm_custstrt"
      Height          =   285
      Left            =   1320
      MaxLength       =   47
      TabIndex        =   2
      Top             =   1080
      Width           =   3975
   End
   Begin TextBox Text5 
      BorderStyle     =   0  'None
      Height          =   255
      Left            =   0
      TabIndex        =   9
      TabStop         =   0   'False
      Text            =   "Cust Address:"
      Top             =   1080
      Width           =   1215
   End
   Begin TextBox cm_custname 
      DataField       =   "cm_custname"
      Height          =   285
      Left            =   1320
      MaxLength       =   47
      TabIndex        =   1
      Top             =   600
      Width           =   3975
   End
   Begin TextBox Text3 
      BorderStyle     =   0  'None
      Height          =   285
      Left            =   0
      TabIndex        =   8
      TabStop         =   0   'False
      Text            =   "Cust. Name:"
      Top             =   600
      Width           =   1095
   End
   Begin TextBox cm_custnumb 
      DataField       =   "cm_custnumb"
      Height          =   285
      Left            =   1320
      MaxLength       =   4
      TabIndex        =   0
      Top             =   120
      Width           =   735
   End
   Begin TextBox Text1 
      BorderStyle     =   0  'None
      Height          =   285
      Left            =   0
      TabIndex        =   7
      TabStop         =   0   'False
      Text            =   "Customer No.:"
      Top             =   120
      Width           =   1215
   End
End

Sub DoErr (cterr As Integer, capt As String)
Dim z As Integer

If cterr <> -1 Then
    l$ = LTrim$(Str$(cterr))
    Msg$ = capt & l$
   MsgBox Msg$, 16, "ERROR"
Else
    'z = GetERROR(ctWNGV)
    l$ = Str$(z)
    Msg$ = capt & l$
   MsgBox Msg$, 16, "ISAM ERROR"
End If
PB_FirstRecord_Click
End Sub

'Initial ctree plus, Open Files or Create in they don't exits
Sub Form_Load ()
Dim ErrorMsg
Dim hTask As Integer
Dim pID As Long
Dim ID As String
Dim CustlokName As String
Dim cterr As Integer

'****************************************
'* Disable Buttons(NextRecord,PrevRecord*
'* and UpdRecord).                      *
'****************************************

PB_NextRecord.Enabled = False
PB_PrevRecord.Enabled = False
PB_UpdRecord.Enabled = False

'***************************************************************
' Register Ctree Instance below.  Only needed for              *
' 16bit windows and if not using ctPortAUTOWIN which           *
' was in release 6.5a or later of ctree plus.                  *
' If ctPortAUTOWIN was defined when making the ctree dll       *
' this is not needed.  It is recommended to build a dll which  *
' has #define ctPortAUTOWIN. This will save from registering   *
' and then switching between program instances.  If not doing  *
' this one program could clobber the other programs data group *
' space.                                                       *
'***************************************************************
'RegID = "REGID_1"
'RegisterID.RegCtreeIDBuff = RegID
'cterr = REGCTREE(ByVal BPtr2Lng(RegisterID))
'
'
'****************************************
'* INITISAM Function.                   *
'****************************************

cterr = INTISAM(bufs, Files, sects)
If cterr Then
  DoErr cterr, "INTISAM"
'  ErrorMsg = "IsamError = " & Str(cterr)
'  MsgBox ErrorMsg, 0, "INTISAM ERROR"
End If

'****************************************
'* Populate Incremental ISAM Structures *
'****************************************
Rem IFIL for Dummy lock file.
CustlokName = "d:\vb\ctree\custlok"
Custlok.pfilnam = BPtr2Lng(ByVal CustlokName)
Custlok.dfilno = 0
Custlok.dreclen = 128
Custlok.dxtdsiz = 0
Custlok.dfilmod = 3
Custlok.dnumidx = 0

Rem ISEG for Custmast Structure
CustMastSeg.soffset = 0
CustMastSeg.slength = 4
CustMastSeg.segmode = 2

Rem IIDX for Custmast Structure
CustMastIx.ikeylen = 4
CustMastIx.ikeytyp = 0
CustMastIx.ikeydup = 0
CustMastIx.inulkey = 1
CustMastIx.iempchr = 32
CustMastIx.inumseg = 1
CustMastIx.seg = BPtr2Lng(CustMastSeg)

Rem IFIL Structure for custmast file.
filname = "d:\vb\custmast\custmast"
CustMast.pfilnam = BPtr2Lng(ByVal filname)
CustMast.dfilno = -1
CustMast.dreclen = 20
CustMast.dxtdsiz = 4096
CustMast.dfilmod = 5
CustMast.dnumidx = 1
CustMast.ixtdsiz = 4096
CustMast.ifilmod = 1
CustMast.ix = BPtr2Lng(CustMastIx)
CustMast.rfstfld = BPtr2Lng("cm_custnumb")
CustMast.rlstfld = BPtr2Lng("cm_custcity")
CustMast.tfilno = -1

'***************************************************
'* Open Dummy Lock file.  If not there Create it.  *
'***************************************************
cterr = OPNIFIL(BPtr2Lng(Custlok))
If cterr Then
   ErrorMsg = "IsamError = " & Str(cterr)
   MsgBox ErrorMsg, 0, "Could not open dummy lock file. Try and Create it."
End If
 Select Case (cterr)
   Case FNOP_ERR
        cterr = CREIFIL(BPtr2Lng(Custlok))
        If cterr Then
            ErrorMsg = "IsamError = " & Str(cterr)
            MsgBox ErrorMsg, 0, "CREIFIL ERROR"
        Else
         cterr = CLIFIL(BPtr2Lng(Custlok))
         If cterr Then
           ErrorMsg = "IsamError = " & Str(cterr)
           MsgBox ErrorMsg, 0, "Could not close dummy lock file. Try and Create it."
         End If
         cterr = OPNIFIL(BPtr2Lng(Custlok))
         If cterr Then
           ErrorMsg = "IsamError = " & Str(cterr)
           MsgBox ErrorMsg, 0, "Could not open dummy lock file. Try and Create it."
         End If
         End If
   Case Is > NO_ERROR
    ErrorMsg = "Fatal ISAM Error = " & Str(cterr)
    MsgBox ErrorMsg, 0, "Closing Application"
    cterr = CLISAM()
    End
 End Select

'****************************************
'* Open Custmast.dat and .idx files.    *
'* If no file exits then create.        *
'****************************************

cterr = OPNIFIL(BPtr2Lng(CustMast))
If cterr Then
  Select Case (cterr)
   Case FCRP_ERR 'Check for corrupted file
         cterr = RBLIFIL(BPtr2Lng(CustMast)) 'Call rebuild
         If cterr Then
            ErrorMsg = "IsamError = " & Str(cterr)
            MsgBox ErrorMsg, 0, "Rebuild ERROR"
         End If
   Case FNOP_ERR 'Check for missing file, if not found create file
        cterr = CREIFIL(BPtr2Lng(CustMast))
        If cterr Then
            ErrorMsg = "IsamError = " & Str(cterr)
            MsgBox ErrorMsg, 0, "CREIFIL ERROR"
        End If
   Case Else 'Fatal error
    ErrorMsg = "Fatal ISAM Error = " & Str(cterr)
    MsgBox ErrorMsg, 0, "Closing Application"
    cterr = CLISAM() 'Close files
    End

   End Select
End If

End Sub

'This Function pads the fixed length fields with spaces
'and terminates with a NULL for the delimiter.
Sub PadFixedFields (S As String, MaxFieldLength As Integer)
Dim FieldLen As Integer

FieldLen = Len(S)
For i = FieldLen To MaxFieldLength - 1
  S = S + " "
Next i

'Put Null at the end of String.
S = S + Chr(0)

End Sub

' Add a new variable record.
Sub PB_AddRecord_Click ()
Dim Position
Dim FieldLen, RecordLen
Dim PadBuff As String
Dim AddRecBuff

'***************************************************************
'* Retrieve Data from screen and format with NULL Delimiters.  *
'***************************************************************
PadBuff = cm_custnumb
PadFixedFields PadBuff, 4
AddRecBuff = ""
AddRecBuff = PadBuff

PadBuff = cm_custzipc
PadFixedFields PadBuff, 9
AddRecBuff = AddRecBuff + PadBuff

PadBuff = cm_custstat
PadFixedFields PadBuff, 2
AddRecBuff = AddRecBuff + PadBuff

PadBuff = cm_custratg
PadFixedFields PadBuff, 1
AddRecBuff = AddRecBuff + PadBuff

CustMastRec.cm_custname = cm_custname
FieldLen = Len(cm_custname) + 1
Mid(CustMastRec.cm_custname, FieldLen, 1) = Chr(0)
AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custname)

CustMastRec.cm_custstrt = cm_custstrt
FieldLen = Len(cm_custstrt) + 1
Mid(CustMastRec.cm_custstrt, FieldLen, 1) = Chr(0)
AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custstrt)

CustMastRec.cm_custcity = cm_custcity
FieldLen = Len(cm_custcity) + 1
Mid(CustMastRec.cm_custcity, FieldLen, 1) = Chr(0)
AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custcity)

'***************************************************
'* Place a write lock on record.                   *
'***************************************************
cterr = LKISAM(CTENABLE)
Select Case (cterr)
  Case DLOK_ERR
       MsgBox "Record is locked by another process."
  Case INOL_ERR
   MsgBox "No more room left in internal lock table."
  End Select

'***************************************************
'* Write formatted data record to Ctree Plus File. *
'***************************************************
RecordLen = Len(AddRecBuff)
CustBuff.CustRec = AddRecBuff
cterr = ADDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), RecordLen)
Select Case (cterr)
  Case NO_ERROR
       MsgBox "Record Successfully Added"
  Case KDUP_ERR
   MsgBox "Record Already Exist. Duplicate Record."
  Case WRITE_ERR
   MsgBox "Write Error Most likely disk or directory is full."
  Case Else
   MsgBox "Error Adding Record."
  End Select

'***************************************************
'* Free all write locks on record.                 *
'***************************************************
cterr = LKISAM(CTFREE)
Select Case (cterr)
  Case DLOK_ERR
       MsgBox "Record is locked by another process."
  Case INOL_ERR
   MsgBox "No more room left in internal lock table."
  End Select

End Sub

Sub PB_ClearFields_Click ()
   cm_custnumb = ""
   cm_custname = ""
   cm_custstrt = ""
   cm_custcity = ""
   cm_custstat = ""
   cm_custzipc = ""
   cm_custratg = ""

End Sub

Sub PB_CLOSE_EXIT_Click ()

cterr = CLIFIL(BPtr2Lng(CustMast))
If cterr Then
  ErrorMsg = "IsamError = " & Str(cterr)
  MsgBox ErrorMsg, 0, "CLIFIL ERROR"
End If

cterr = CLIFIL(BPtr2Lng(Custlok))
If cterr Then
  ErrorMsg = "IsamError = " & Str(cterr)
  MsgBox ErrorMsg, 0, "Dummy lock file close ERROR."
End If

cterr = CLISAM()

End
End Sub

' Delete Record
Sub PB_DelRecord_Click ()
Dim CUSTRECORD As String
Dim Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7  As Integer
Dim cterr As Integer

'***************************************************
'* Place a write lock on record.                   *
'***************************************************
cterr = LKISAM(CTENABLE)
Select Case (cterr)
  Case DLOK_ERR
       MsgBox "Record is locked by another process."
  Case INOL_ERR
   MsgBox "No more room left in internal lock table."
  End Select

'************************************
'* Test to see if record exists.    *
'************************************
CustKey.CustKeyBuff = cm_custnumb
cterr = EQLREC(CustMast.tfilno + 1, BPtr2Lng(CustKey), BPtr2Lng(CustBuff))
If cterr Then
  DoErr cterr, "GetRecord"
End If

'**********************************
'* Delete Record.                 *
'**********************************
cterr = DELVREC(CustMast.tfilno)
Select Case (cterr)
  Case NO_ERROR
       MsgBox "Record Deleted Successfully"
       cm_custnumb = ""
       cm_custname = ""
       cm_custstrt = ""
       cm_custcity = ""
       cm_custstat = ""
       cm_custzipc = ""
       cm_custratg = ""

  Case FMOD_ERR
   MsgBox "datno is assigned to a fixed length data file"
  Case KDEL_ERR
   MsgBox "Could not Delete key Value"
  Case ICUR_ERR
   MsgBox "No current ISAM record for data file"
  Case Else
   MsgBox "Error Deleting Record."
  End Select

'***************************************************
'* Free all write locks on record.                 *
'***************************************************
cterr = LKISAM(CTFREE)
Select Case (cterr)
  Case DLOK_ERR
       MsgBox "Record is locked by another process."
  Case INOL_ERR
   MsgBox "No more room left in internal lock table."
  End Select

End Sub

'
' Retrieve first record from data file.
'
Sub PB_FirstRecord_Click ()
Dim CUSTRECORD As String
Dim Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7 As Integer
Dim cterr As Integer

' Clear screen fields
cm_custnumb = ""
cm_custname = ""
cm_custstrt = ""
cm_custcity = ""
cm_custstat = ""
cm_custzipc = ""
cm_custratg = ""
'***********************************************************
'* Get First Record.  Since these are variable length      *
'* records get length of record then reread variable part. *
'***********************************************************
cterr = FRSREC(CustMast.tfilno + 1, BPtr2Lng(CustBuff))
If cterr Then
  DoErr cterr, "FirstRecord"
End If
VarLen = GETVLEN(CustMast.tfilno)
cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)
If cterr Then
  DoErr cterr, "ReRecord"
End If

'***********************************************************
'* Separate Record based on the delimiter NULL.            *
'* Format data record layout                               *
'***********************************************************
CUSTRECORD = CustBuff.CustRec
'Field 1 customer number
Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

'Field 2 Zip code
Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

'Field 3 State Code
Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

'Field 4 Status flag
Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

'Field 5 Customer name
Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

'Field 6 Customer Street Address
Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

'Field 7 Customer City
Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

'**************************************
'*  Set Screen to values just read.   *
'**************************************
cm_custnumb = CustMastRec.cm_custnumb
cm_custname = CustMastRec.cm_custname
cm_custstrt = CustMastRec.cm_custstrt
cm_custcity = CustMastRec.cm_custcity
cm_custstat = CustMastRec.cm_custstat
cm_custzipc = CustMastRec.cm_custzipc
cm_custratg = CustMastRec.cm_custratg

'***********************************************
'* Enable NextRecord,PrevRecord,               *
'* and UpdRecord Buttons.                      *
'***********************************************
PB_NextRecord.Enabled = True
PB_PrevRecord.Enabled = True
PB_UpdRecord.Enabled = True

End Sub

Sub PB_GetRecord_Click ()
Dim CUSTRECORD

CustKey.CustKeyBuff = cm_custnumb
cterr = EQLREC(CustMast.tfilno + 1, BPtr2Lng(CustKey), BPtr2Lng(CustBuff))
Select Case (cterr)
  Case INOT_ERR
   MsgBox "Record not found."
   cm_custnumb = ""
   cm_custname = ""
   cm_custstrt = ""
   cm_custcity = ""
   cm_custstat = ""
   cm_custzipc = ""
   cm_custratg = ""

  Case NO_ERROR
   VarLen = GETVLEN(CustMast.tfilno)
   cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)
   '***********************************************************
   '* Separate Record based on delimiter NULL.                *
   '***********************************************************
   CUSTRECORD = CustBuff.CustRec
   Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
   Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

   Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
   Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

   Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
   Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

   Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
   Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

   Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
   Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

   Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
   Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

   Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
   Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

   '**************************************
   '*  Set Screen to values just read.   *
   '**************************************
   cm_custnumb = CustMastRec.cm_custnumb
   cm_custname = CustMastRec.cm_custname
   cm_custstrt = CustMastRec.cm_custstrt
   cm_custcity = CustMastRec.cm_custcity
   cm_custstat = CustMastRec.cm_custstat
   cm_custzipc = CustMastRec.cm_custzipc
   cm_custratg = CustMastRec.cm_custratg
   PB_NextRecord.Enabled = True
   PB_PrevRecord.Enabled = True
   PB_UpdRecord.Enabled = True
End Select

End Sub

Sub PB_GTERecord_Click ()
Dim CUSTRECORD

CustKey.CustKeyBuff = cm_custnumb
cterr = GTEREC(CustMast.tfilno + 1, BPtr2Lng(CustKey), BPtr2Lng(CustBuff))
VarLen = GETVLEN(CustMast.tfilno)
cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)

If cterr Then
  ErrorMsg = "IsamError = " & Str(cterr)
  MsgBox ErrorMsg, 0, "GetRecord Failed."
End If
'***********************************************************
'* Separate Record based on delimiter NULL.                *
'***********************************************************
CUSTRECORD = CustBuff.CustRec
Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

'**************************************
'*  Set Screen to values just read.   *
'**************************************
cm_custnumb = CustMastRec.cm_custnumb
cm_custname = CustMastRec.cm_custname
cm_custstrt = CustMastRec.cm_custstrt
cm_custcity = CustMastRec.cm_custcity
cm_custstat = CustMastRec.cm_custstat
cm_custzipc = CustMastRec.cm_custzipc
cm_custratg = CustMastRec.cm_custratg

PB_NextRecord.Enabled = True
PB_PrevRecord.Enabled = True
PB_UpdRecord.Enabled = True


End Sub

Sub PB_GTRecord_Click ()
Dim CUSTRECORD

CustKey.CustKeyBuff = cm_custnumb
cterr = GTREC(CustMast.tfilno + 1, BPtr2Lng(CustKey), BPtr2Lng(CustBuff))
VarLen = GETVLEN(CustMast.tfilno)
cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)

If cterr Then
  ErrorMsg = "IsamError = " & Str(cterr)
  MsgBox ErrorMsg, 0, "GetRecord Failed."
End If
'***********************************************************
'* Separate Record based on delimiter NULL.                *
'***********************************************************
CUSTRECORD = CustBuff.CustRec
Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

'**************************************
'*  Set Screen to values just read.   *
'**************************************
cm_custnumb = CustMastRec.cm_custnumb
cm_custname = CustMastRec.cm_custname
cm_custstrt = CustMastRec.cm_custstrt
cm_custcity = CustMastRec.cm_custcity
cm_custstat = CustMastRec.cm_custstat
cm_custzipc = CustMastRec.cm_custzipc
cm_custratg = CustMastRec.cm_custratg

PB_NextRecord.Enabled = True
PB_PrevRecord.Enabled = True
PB_UpdRecord.Enabled = True

End Sub

' Retrieve the last record.
Sub PB_LastRecord_Click ()
Dim CUSTRECORD As String
Dim Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7 As Integer

cm_custnumb = ""
cm_custname = ""
cm_custstrt = ""
cm_custcity = ""
cm_custstat = ""
cm_custzipc = ""
cm_custratg = ""

'**************************
'* Get Last Record.       *
'**************************
cterr = LSTREC(CustMast.tfilno + 1, BPtr2Lng(CustBuff))
VarLen = GETVLEN(CustMast.tfilno)
cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)

CUSTRECORD = CustBuff.CustRec
Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

cm_custnumb = CustMastRec.cm_custnumb
cm_custname = CustMastRec.cm_custname
cm_custstrt = CustMastRec.cm_custstrt
cm_custcity = CustMastRec.cm_custcity
cm_custstat = CustMastRec.cm_custstat
cm_custzipc = CustMastRec.cm_custzipc
cm_custratg = CustMastRec.cm_custratg

PB_NextRecord.Enabled = True
PB_PrevRecord.Enabled = True
PB_DelRecord.Enabled = True
PB_UpdRecord.Enabled = True

End Sub

Sub PB_LTERecord_Click ()
Dim CUSTRECORD

CustKey.CustKeyBuff = cm_custnumb
cterr = LTEREC(CustMast.tfilno + 1, BPtr2Lng(CustKey), BPtr2Lng(CustBuff))
VarLen = GETVLEN(CustMast.tfilno)
cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)

If cterr Then
  ErrorMsg = "IsamError = " & Str(cterr)
  MsgBox ErrorMsg, 0, "GetRecord Failed."
End If
'***********************************************************
'* Separate Record based on delimiter NULL.                *
'***********************************************************
CUSTRECORD = CustBuff.CustRec
Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

'**************************************
'*  Set Screen to values just read.   *
'**************************************
cm_custnumb = CustMastRec.cm_custnumb
cm_custname = CustMastRec.cm_custname
cm_custstrt = CustMastRec.cm_custstrt
cm_custcity = CustMastRec.cm_custcity
cm_custstat = CustMastRec.cm_custstat
cm_custzipc = CustMastRec.cm_custzipc
cm_custratg = CustMastRec.cm_custratg

PB_NextRecord.Enabled = True
PB_PrevRecord.Enabled = True
PB_UpdRecord.Enabled = True

End Sub

Sub PB_LTRecord_Click ()
Dim CUSTRECORD

CustKey.CustKeyBuff = cm_custnumb
cterr = LTREC(CustMast.tfilno + 1, BPtr2Lng(CustKey), BPtr2Lng(CustBuff))
VarLen = GETVLEN(CustMast.tfilno)
cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)

If cterr Then
  ErrorMsg = "IsamError = " & Str(cterr)
  MsgBox ErrorMsg, 0, "GetRecord Failed."
End If
'***********************************************************
'* Separate Record based on delimiter NULL.                *
'***********************************************************
CUSTRECORD = CustBuff.CustRec
Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

'**************************************
'*  Set Screen to values just read.   *
'**************************************
cm_custnumb = CustMastRec.cm_custnumb
cm_custname = CustMastRec.cm_custname
cm_custstrt = CustMastRec.cm_custstrt
cm_custcity = CustMastRec.cm_custcity
cm_custstat = CustMastRec.cm_custstat
cm_custzipc = CustMastRec.cm_custzipc
cm_custratg = CustMastRec.cm_custratg

PB_NextRecord.Enabled = True
PB_PrevRecord.Enabled = True
PB_UpdRecord.Enabled = True

End Sub

' Retrieve Next Record
Sub PB_NextRecord_Click ()
Dim CUSTRECORD As String
Dim Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7 As Integer
Dim cterr As Integer

'Clear Screen
cm_custnumb = ""
cm_custname = ""
cm_custstrt = ""
cm_custcity = ""
cm_custstat = ""
cm_custzipc = ""
cm_custratg = ""
'**************************
'* Retrieve Next Record.  *
'**************************
cterr = NXTREC(CustMast.tfilno + 1, BPtr2Lng(CustBuff))

Select Case (cterr)
  Case INOT_ERR
   MsgBox "End of File"

  Case Else
    VarLen = GETVLEN(CustMast.tfilno)
    cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)
    CUSTRECORD = CustBuff.CustRec
    Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD

    Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

    Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

    Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

    Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

    Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

    Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)
    
    'Set values to screen fields
    cm_custnumb = CustMastRec.cm_custnumb
    cm_custname = CustMastRec.cm_custname
    cm_custstrt = CustMastRec.cm_custstrt
    cm_custcity = CustMastRec.cm_custcity
    cm_custstat = CustMastRec.cm_custstat
    cm_custzipc = CustMastRec.cm_custzipc
    cm_custratg = CustMastRec.cm_custratg

End Select

End Sub

' Retrieve Previous Record
Sub PB_PrevRecord_Click ()
Dim CUSTRECORD As String
Dim Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7 As Integer

'Clear Screen
cm_custnumb = ""
cm_custname = ""
cm_custstrt = ""
cm_custcity = ""
cm_custstat = ""
cm_custzipc = ""
cm_custratg = ""

'*******************************
'* Retrieve Previous Record.   *
'*******************************
cterr = PRVREC(CustMast.tfilno + 1, BPtr2Lng(CustBuff))
Select Case (cterr)
  Case INOT_ERR
   MsgBox "No Previous Records"

  Case Else
    VarLen = GETVLEN(CustMast.tfilno)
    cterr = REDVREC(CustMast.tfilno, BPtr2Lng(CustBuff), VarLen)
    CUSTRECORD = CustBuff.CustRec
    Pos1 = InStr(1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custnumb, 1, Pos1 - 1) = CUSTRECORD
    Pos2 = InStr(Pos1 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custzipc, 1, (Pos2 - Pos1)) = Mid(CUSTRECORD, Pos1 + 1, (Pos2 - Pos1))

    Pos3 = InStr(Pos2 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custstat, 1, (Pos3 - Pos2)) = Mid(CUSTRECORD, Pos2 + 1, Pos3 - Pos2)

    Pos4 = InStr(Pos3 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custratg, 1, (Pos4 - Pos3)) = Mid(CUSTRECORD, Pos3 + 1, Pos4 - Pos3)

    Pos5 = InStr(Pos4 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custname, 1, (Pos5 - Pos4)) = Mid(CUSTRECORD, Pos4 + 1, Pos5 - Pos4)

    Pos6 = InStr(Pos5 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custstrt, 1, (Pos6 - Pos5)) = Mid(CUSTRECORD, Pos5 + 1, Pos6 - Pos5)

    Pos7 = InStr(Pos6 + 1, CUSTRECORD, Chr(0), 0)
    Mid$(CustMastRec.cm_custcity, 1, (Pos7 - Pos6)) = Mid(CUSTRECORD, Pos6 + 1, Pos7 - Pos6)

    cm_custnumb = CustMastRec.cm_custnumb
    cm_custname = CustMastRec.cm_custname
    cm_custstrt = CustMastRec.cm_custstrt
    cm_custcity = CustMastRec.cm_custcity
    cm_custstat = CustMastRec.cm_custstat
    cm_custzipc = CustMastRec.cm_custzipc
    cm_custratg = CustMastRec.cm_custratg

  End Select

End Sub

' Update Record.
Sub PB_UpdRecord_Click ()
Dim FieldLen, RecordLen
Dim AddRecBuff, CustNumbKey

'***************************************************
'* Place a write lock on record.                   *
'***************************************************
cterr = LKISAM(CTENABLE)
Select Case (cterr)
  Case DLOK_ERR
       MsgBox "Record is locked by another process."
  Case INOL_ERR
   MsgBox "No more room left in internal lock table."

End Select

'************************************
'* Test to see if record exists.    *
'************************************
CustKey.CustKeyBuff = cm_custnumb
cterr = EQLREC(CustMast.tfilno + 1, BPtr2Lng(CustKey), BPtr2Lng(CustBuff))
Select Case (cterr)
  Case INOT_ERR
   MsgBox "Record not found."

  Case NO_ERROR
   '********************************************
   '* Get data from screen and rewrite Record. *
   '********************************************
   CustMastRec.cm_custnumb = cm_custnumb
   FieldLen = Len(cm_custnumb) + 1
   Mid$(CustMastRec.cm_custnumb, FieldLen, 1) = Chr(0)
   AddRecBuff = ""
   AddRecBuff = Trim$(CustMastRec.cm_custnumb)
   CustMastRec.cm_custzipc = cm_custzipc
   FieldLen = Len(cm_custzipc) + 1
   Mid(CustMastRec.cm_custzipc, FieldLen, 1) = Chr(0)
   AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custzipc)

   CustMastRec.cm_custstat = cm_custstat
   FieldLen = Len(cm_custstat) + 1
   Mid(CustMastRec.cm_custstat, FieldLen, 1) = Chr(0)
   AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custstat)

   CustMastRec.cm_custratg = cm_custratg
   FieldLen = Len(cm_custratg) + 1
   Mid(CustMastRec.cm_custratg, FieldLen, 1) = Chr(0)
   AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custratg)

   CustMastRec.cm_custname = cm_custname
   FieldLen = Len(cm_custname) + 1
   Mid(CustMastRec.cm_custname, FieldLen, 1) = Chr(0)
   AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custname)

   CustMastRec.cm_custstrt = cm_custstrt
   FieldLen = Len(cm_custstrt) + 1
   Mid(CustMastRec.cm_custstrt, FieldLen, 1) = Chr(0)
   AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custstrt)

   CustMastRec.cm_custcity = cm_custcity
   FieldLen = Len(cm_custcity) + 1
   Mid(CustMastRec.cm_custcity, FieldLen, 1) = Chr(0)
   AddRecBuff = AddRecBuff + Trim$(CustMastRec.cm_custcity)

   RecordLen = Len(AddRecBuff)
   CustBuff.CustRec = AddRecBuff
   cterr = RWTVREC(CustMast.tfilno, BPtr2Lng(CustBuff), RecordLen)

   Select Case (cterr)
    Case NO_ERROR
      MsgBox "Record Successfully Updated"
      cterr = UPDCURI(CustMast.tfilno, SWTCURI)

    Case KDUP_ERR
      MsgBox "Record Already Exist. Duplicate Record."

    Case WRITE_ERR
      MsgBox "Write Error Most likely disk or directory is full."

    Case Else
      MsgBox "Error Adding Record."
   End Select

End Select

'***************************************************
'* Free all write locks on record.                 *
'***************************************************
cterr = LKISAM(CTFREE)
Select Case (cterr)
  Case DLOK_ERR
       MsgBox "Record is locked by another process."
  Case INOL_ERR
   MsgBox "No more room left in internal lock table."
  End Select

'Clear screen fields.
cm_custnumb = ""
cm_custname = ""
cm_custstrt = ""
cm_custcity = ""
cm_custstat = ""
cm_custzipc = ""
cm_custratg = ""

End Sub

