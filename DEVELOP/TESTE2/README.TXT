This sample Visual Basic program demonstrates how to use Visual Basic
with the Faircom c-tree plus Dynamic Link Library "DLL".

It is recommended that you upgrade your ctree plus to the latest version.
This has only been tested with ctree plus version 6.6a CD or later and with
Microsoft Visual Basic 4.0 and Windows 3.1 and Windows 95.  If you are 
using Microsoft Visual Basic 3.0 see zip file vb3ctree.zip.
For upgrade pricing or to purchase ctree plus - email faircom at
sales@faircom.com or call (573) 445-6833.  FairCom also has an ODBC driver 
"Open Data Base Connectivity" to use with ctree plus or Client/Server versions.

In order to use this Visual Basic sample you will need to purchase 
ctree plus version 6.6a or later from FairCom Corporation.  You will also
need a Microsoft "C/C++" compiler to compile and link the ctree plus 
windows DLL "ctreestd.dll".
Other companies compilers (borland) for example should work fine.  Only 
Microsoft compiler Visual C has been tested.
For 16bit applications your target platform will be Windows 3.x.
For 32bit applications your target platform will be windows 95.
This sample has not been test on MS-Windows NT.


There are two DLL's that are needed pointers.dll and ctreestd.dll.  
The ctreestd.dll is build from the c-tree plus SDK.  It has been 
build in multi-user/non-server mode.  This sample program demonstrates 
how to add, update, delete, and view variable length records in 
c-tree plus files using function calls to the c-tree plus DLL.

To use this with Visual Basic 4.x 16bit you will need to
make a ctreestd.dll for 16bit windows using the ctree plus SDK. Also
copy pointers.16b to pointers.dll.  If you intend to use 
Visual Basic 4.x 32bit windows copy pointers.32b to pointers.dll.  You 
will need to make a change in the ctcmpl.h before making a 32bit 
ctreestd.dll.


To make the CTREESTD.DLL for visual basic 4.x 32bit windows 95.
You will need to #define ctDECL in file 
\faircom\ctree\source\msc.nt\ctcmpl.h
to
#define ctDECL  _stdcall
Then remake a new CTREESTD.DLL.


Files included:
Readme.txt - this file.
ctree.bas - this contains most of ctree plus functions.  If a function is
missing you will need to add it to this file.
custmast.dat - test data file.  This file also comes with the ODBC drivers.
custmast.idx - test index file. This file also comes with the ODBC drivers.
custlok.dat  - dummy lock file.
custmast.frm - this is the basic form file for custmast.frm.
Custmast.mak - make file for sample program.
Pointers.dll - See below.

Note on "C" pointers:
The code in POINTERS.DLL is intended as a 'fix' for limitations of 
Visual Basic in interfacing with C code DLL's.  Since Visual Basic 
doesn't support a pointer type or a method of getting the address 
of a function or variable.

The function BPtr2Lng is just a method of getting an address 
(which VB has but won't give to you) by just casting the address to 
a long and returning it.  This function should be used whenever you 
would normally use the & operator in C.


For example in custmast.frm the function call OPNIFIL(BPtrLng(CustMast)) 
this can be achieved by casting the address to a long and returning it.

Visual Basic uses the Pascal String convention of preceding the string 
with a count of the number of characters.  Even worse for our purposes 
is the way VB accesses a string.  The address of the string, that one 
would get if the string were referenced in a function without the 
ByVal modifier, is a pointer to an offset in the same segment.  
This offset is the address of the length member of the string.  This 
is the reason for the 'finagling' represented by the BPtr2Str function.  
The function Bptr2Str transforms a VB string (not one derived by 
DIM String * x but by default or by defining Str$ or Dim String) 
into a zero terminated C string, i.e. a char[], and returns a 
far char * to it.
	

Note that it is necessary to change the path in CTREE.BAS for both
pointers.dll and ctreestd.dll to reflect your setup.  You can also 
put them in your windows directory.  You will need to change the 
IFIL structure path to locate the custlok.dat, custmast.dat, and 
custmast.idx files.  If these files are not found it will create them.
Generally if you receive a 48 or 49 error in this sample program
Visual Basic cannot find the ctreestd.dll or the pointers.dll.

Before running this program.
1) Make sure you have build the proper ctreestd.dll and that it is
   in the path (c:\windows).

2) The pointers.dll is in the path or (c:\windows).

3) If using 32bit windows make sure you have made a ctreestd.dll with
   #define ctDECL _stdcall in file \faircom\ctree\source\msc.nt\ctcmpl.h.

4) You will also need to change the path in the IFIL stucture to reflect
the file name it is currently d:\vb4\custmast\custmast

To try this program simply bring up visual basic and open custmast.mak
then run program.


This program has been tested in non-server/multi-user ctree plus 
version 6.6a CD release mode.  There may be some bugs or improvements 
needed to this sample program.  Your help is solicited in identifying 
any of these and in proposing solutions/improvements.
email support@faircom.com with hints or questions.


08/30/96 W. Seidt







