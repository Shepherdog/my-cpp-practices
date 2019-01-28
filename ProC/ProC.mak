# Microsoft Developer Studio Generated NMAKE File, Based on ProC.dsp
!IF "$(CFG)" == ""
CFG=ProC - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ProC - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ProC - Win32 Release" && "$(CFG)" != "ProC - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProC.mak" CFG="ProC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProC - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ProC - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ProC - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : 


CLEAN :
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ProC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\ProC.pdb" /machine:I386 /out:"$(OUTDIR)\ProC.exe" 
LINK32_OBJS= \
	

!ELSEIF  "$(CFG)" == "ProC - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\ProC.c" 


CLEAN :
	-@erase 
	-@erase ".\ProC.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ProC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib oraSQL8.lib oraSQX8.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\ProC.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ProC.exe" /pdbtype:sept 
LINK32_OBJS= \
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ProC.dep")
!INCLUDE "ProC.dep"
!ELSE 
!MESSAGE Warning: cannot find "ProC.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ProC - Win32 Release" || "$(CFG)" == "ProC - Win32 Debug"
SOURCE=.\ProC.pc

!IF  "$(CFG)" == "ProC - Win32 Release"

!ELSEIF  "$(CFG)" == "ProC - Win32 Debug"

InputDir=.
InputPath=.\ProC.pc
InputName=ProC

".\ProC.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	call vcvars32.bat 
	proc iname="$(InputName).pc" include="%MSVCDIR%\include" include="$(MSDEVDIR)\..\vc98\include" code=ansi_c parse=full lines=yes 
<< 
	

!ENDIF 


!ENDIF 

