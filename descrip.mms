! VMS MAKEFILE (for MMS)
!

all depends_on crashme.exe pddet.exe
 !(ALL DONE)

crashme.exe depends_on crashme.obj
 optarg = ",crashme.vms-opt/opt"
 if f$getsyi("SID") .lt. 0 then optarg = ""
 link crashme.obj'optarg'
 ! re-execute the next line in your superior process:
 crashme == "$" + f$env("DEFAULT") + "CRASHME"

crashme.obj depends_on crashme.c
 PF = ""
 if f$getsyi("SID") .lt. 0 then PF = "/PREFIX=ALL"
 CC/DEBUG/OPTIMIZE=(NOINLINE)'PF' CRASHME.C

pddet.exe depends_on pddet.obj
 optarg = ",crashme.opt/opt"
 if f$getsyi("SID") .lt. 0 then optarg = ""
 link pddet.obj'optarg'
 ! re-execute the next line in your superior process:
 pddet == "$" + f$env("DEFAULT") + "PDDET"

pddet.obj depends_on pddet.c
 PF = ""
 if f$getsyi("SID") .lt. 0 then PF = "/PREFIX=ALL"
 CC/DEBUG/OPTIMIZE=(NOINLINE)'PF' PDDET.C


crashme_dbg.exe depends_on crashme.obj
 optarg = ",crashme.opt/opt"
 if f$getsyi("SID") .lt. 0 then optarg = ""
 link/debug/exe=crashme_dbg.exe crashme.obj'optarg'

! note: do not use continuation character here.
DIST_FILES = crashme.1,crashme.c,makefile,descrip.mms,crashme.opt,read.me,shar.db,makefile.wnt,make.bat,pddet.c

crashme.shar depends_on $(DIST_FILES)
 minishar crashme.shar shar.db

crashme.1_of_1 depends_on $(DIST_FILES)
 define share_max_part_size 1000
 vms_share $(DIST_FILES) crashme
