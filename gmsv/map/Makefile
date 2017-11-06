INCFLAGS=-I. -I../include
MYOPTIMIZE = -g -O2 -fomit-frame-pointer
CFLAGS=-Wall $(INCFLAGS) $(MYOPTIMIZE)
PROG=libmap.a

SRC=readmap.c map_deal.c map_util.c map_warppoint.c
OBJ=$(SRC:.c=.o)

ifeq (0,$(MAKELEVEL))
CC=gcc
RM=rm -f
AR=ar cr
MV=mv
RANLIB=ranlib
SED=sed
SHELL=/bin/sh
endif

all: $(PROG)

$(PROG): $(OBJ)
	$(RM) $(PROG)
	$(AR) $(PROG) $(OBJ)
	$(RANLIB) $(PROG)

depend:
	$(MV) Makefile Makefile.bak
	$(SED) -ne '1,/^# DO NOT DELETE THIS LINE/p' Makefile.bak>Makefile
	$(CC) $(INCFLAGS) -M $(SRC) >> Makefile 

clean:
	$(RM) $(PROG)
	$(RM) $(OBJ)
	$(RM) *~
	$(RM) *.bak

distclean:
	$(RM) $(PROG)
	$(RM) $(OBJ)
	$(RM) *~
	$(MV) Makefile Makefile.bak
	$(SED) -ne '1,/^# DO NOT DELETE THIS LINE/p' Makefile.bak>Makefile
	$(RM) Makefile.bak

# DO NOT DELETE THIS LINE
readmap.o: readmap.c ../include/version.h ../include/correct_bug.h \
  ../include/version_pk.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
  /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
  /usr/include/endian.h /usr/include/bits/endian.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/bits/time.h \
  /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
  /usr/include/bits/sched.h /usr/include/alloca.h /usr/include/string.h \
  /usr/include/dirent.h /usr/include/bits/dirent.h \
  /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h \
  /usr/include/linux/limits.h /usr/include/errno.h \
  /usr/include/bits/errno.h /usr/include/linux/errno.h \
  /usr/include/asm/errno.h /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h /usr/include/netinet/in.h /usr/include/stdint.h \
  /usr/include/sys/socket.h /usr/include/sys/uio.h \
  /usr/include/bits/uio.h /usr/include/bits/socket.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/limits.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix2_lim.h \
  /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
  /usr/include/asm/sockios.h /usr/include/bits/in.h \
  /usr/include/bits/byteswap.h /usr/include/sys/stat.h \
  /usr/include/bits/stat.h ../include/common.h ../include/object.h \
  ../include/common.h ../include/readmap.h ../include/util.h \
  /usr/include/sys/time.h ../include/buf.h ../include/util.h \
  ../include/char.h ../include/char_base.h ../include/version.h \
  ../include/skill.h ../include/title.h ../include/addressbook.h \
  ../include/net.h /usr/include/signal.h /usr/include/bits/signum.h \
  /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/linux/compiler.h /usr/include/bits/sigstack.h \
  /usr/include/bits/sigthread.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/initspin.h ../include/link.h \
  ../include/char_data.h ../include/item.h ../include/char.h \
  ../include/lssproto_serv.h ../include/lssproto_util.h \
  /usr/include/strings.h ../include/configfile.h
map_deal.o: map_deal.c ../include/version.h ../include/correct_bug.h \
  ../include/version_pk.h ../include/common.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
  ../include/readmap.h ../include/common.h ../include/util.h \
  /usr/include/sys/time.h /usr/include/time.h /usr/include/bits/time.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/alloca.h ../include/char.h ../include/char_base.h \
  ../include/version.h ../include/skill.h ../include/title.h \
  ../include/addressbook.h ../include/net.h /usr/include/netinet/in.h \
  /usr/include/stdint.h /usr/include/sys/socket.h /usr/include/sys/uio.h \
  /usr/include/bits/uio.h /usr/include/bits/socket.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/limits.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/sockaddr.h \
  /usr/include/asm/socket.h /usr/include/asm/sockios.h \
  /usr/include/bits/in.h /usr/include/bits/byteswap.h \
  /usr/include/signal.h /usr/include/bits/signum.h \
  /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/linux/compiler.h /usr/include/bits/sigstack.h \
  /usr/include/bits/sigthread.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/initspin.h ../include/link.h \
  ../include/char_data.h ../include/item.h ../include/char.h \
  ../include/map_util.h ../include/lssproto_serv.h \
  ../include/lssproto_util.h /usr/include/string.h /usr/include/strings.h \
  /usr/include/unistd.h /usr/include/bits/posix_opt.h \
  /usr/include/bits/confname.h /usr/include/getopt.h ../include/net.h \
  ../include/anim_tbl.h
map_util.o: map_util.c ../include/version.h ../include/correct_bug.h \
  ../include/version_pk.h ../include/common.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
  ../include/char.h ../include/common.h ../include/char_base.h \
  ../include/version.h ../include/skill.h ../include/util.h \
  /usr/include/sys/time.h /usr/include/time.h /usr/include/bits/time.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/alloca.h ../include/title.h ../include/addressbook.h \
  ../include/net.h /usr/include/netinet/in.h /usr/include/stdint.h \
  /usr/include/sys/socket.h /usr/include/sys/uio.h \
  /usr/include/bits/uio.h /usr/include/bits/socket.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/limits.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/sockaddr.h \
  /usr/include/asm/socket.h /usr/include/asm/sockios.h \
  /usr/include/bits/in.h /usr/include/bits/byteswap.h \
  /usr/include/signal.h /usr/include/bits/signum.h \
  /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/linux/compiler.h /usr/include/bits/sigstack.h \
  /usr/include/bits/sigthread.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/initspin.h ../include/link.h \
  ../include/char_data.h ../include/item.h ../include/char.h \
  ../include/readmap.h
map_warppoint.o: map_warppoint.c ../include/version.h \
  ../include/correct_bug.h ../include/version_pk.h /usr/include/string.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stddef.h \
  ../include/common.h /usr/include/stdio.h /usr/include/bits/types.h \
  /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
  ../include/char.h ../include/common.h ../include/char_base.h \
  ../include/version.h ../include/skill.h ../include/util.h \
  /usr/include/sys/time.h /usr/include/time.h /usr/include/bits/time.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/alloca.h ../include/title.h ../include/addressbook.h \
  ../include/net.h /usr/include/netinet/in.h /usr/include/stdint.h \
  /usr/include/sys/socket.h /usr/include/sys/uio.h \
  /usr/include/bits/uio.h /usr/include/bits/socket.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/limits.h \
  /usr/lib/gcc/i486-slackware-linux/3.4.6/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/sockaddr.h \
  /usr/include/asm/socket.h /usr/include/asm/sockios.h \
  /usr/include/bits/in.h /usr/include/bits/byteswap.h \
  /usr/include/signal.h /usr/include/bits/signum.h \
  /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/linux/compiler.h /usr/include/bits/sigstack.h \
  /usr/include/bits/sigthread.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/initspin.h ../include/link.h \
  ../include/char_data.h ../include/item.h ../include/char.h \
  ../include/char_base.h ../include/object.h ../include/buf.h \
  ../include/util.h ../include/configfile.h ../include/readmap.h \
  ../include/map_warppoint.h
