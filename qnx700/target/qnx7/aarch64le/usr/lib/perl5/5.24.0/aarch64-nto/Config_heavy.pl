# This file was created by configpm when Perl was built. Any changes
# made to this file will be lost the next time perl is built.

package Config;
use strict;
use warnings;
use vars '%Config';

sub bincompat_options {
    return split ' ', (Internals::V())[0];
}

sub non_bincompat_options {
    return split ' ', (Internals::V())[1];
}

sub compile_date {
    return (Internals::V())[2]
}

sub local_patches {
    my (undef, undef, undef, @patches) = Internals::V();
    return @patches;
}

sub _V {
    die "Perl lib was built for 'linux' but is being run on '$^O'"
        unless "linux" eq $^O;

    my ($bincompat, $non_bincompat, $date, @patches) = Internals::V();

    my $opts = join ' ', sort split ' ', "$bincompat $non_bincompat";

    # wrap at 76 columns.

    $opts =~ s/(?=.{53})(.{1,53}) /$1\n                        /mg;

    print Config::myconfig();
    print "\nCharacteristics of this binary (from libperl): \n";

    print "  Compile-time options: $opts\n";

    if (@patches) {
        print "  Locally applied patches:\n";
        print "\t$_\n" foreach @patches;
    }

    print "  Built under linux\n";

    print "  $date\n" if defined $date;

    my @env = map { "$_=\"$ENV{$_}\"" } sort grep {/^PERL/} keys %ENV;

    if (@env) {
        print "  \%ENV:\n";
        print "    $_\n" foreach @env;
    }
    print "  \@INC:\n";
    print "    $_\n" foreach @INC;
}

sub header_files {
    return qw(EXTERN.h INTERN.h XSUB.h av.h config.h cop.h cv.h
              dosish.h embed.h embedvar.h form.h gv.h handy.h hv.h hv_func.h
              intrpvar.h iperlsys.h keywords.h mg.h nostdio.h op.h opcode.h
              pad.h parser.h patchlevel.h perl.h perlio.h perliol.h perlsdio.h
              perlvars.h perly.h pp.h pp_proto.h proto.h regcomp.h regexp.h
              regnodes.h scope.h sv.h thread.h time64.h unixish.h utf8.h
              util.h);
}

#

our $summary = <<'!END!';
Summary of my $package (revision $revision $version_patchlevel_string) configuration:
  $git_commit_id_title $git_commit_id$git_ancestor_line
  Platform:
    osname=$osname, osvers=$osvers, archname=$archname
    uname='$myuname'
    config_args='$config_args'
    hint=$hint, useposix=$useposix, d_sigaction=$d_sigaction
    useithreads=$useithreads, usemultiplicity=$usemultiplicity
    use64bitint=$use64bitint, use64bitall=$use64bitall, uselongdouble=$uselongdouble
    usemymalloc=$usemymalloc, bincompat5005=undef
  Compiler:
    cc='$cc', ccflags ='$ccflags',
    optimize='$optimize',
    cppflags='$cppflags'
    ccversion='$ccversion', gccversion='$gccversion', gccosandvers='$gccosandvers'
    intsize=$intsize, longsize=$longsize, ptrsize=$ptrsize, doublesize=$doublesize, byteorder=$byteorder, doublekind=$doublekind
    d_longlong=$d_longlong, longlongsize=$longlongsize, d_longdbl=$d_longdbl, longdblsize=$longdblsize, longdblkind=$longdblkind
    ivtype='$ivtype', ivsize=$ivsize, nvtype='$nvtype', nvsize=$nvsize, Off_t='$lseektype', lseeksize=$lseeksize
    alignbytes=$alignbytes, prototype=$prototype
  Linker and Libraries:
    ld='$ld', ldflags ='$ldflags'
    libpth=$libpth
    libs=$libs
    perllibs=$perllibs
    libc=$libc, so=$so, useshrplib=$useshrplib, libperl=$libperl
    gnulibc_version='$gnulibc_version'
  Dynamic Linking:
    dlsrc=$dlsrc, dlext=$dlext, d_dlsymun=$d_dlsymun, ccdlflags='$ccdlflags'
    cccdlflags='$cccdlflags', lddlflags='$lddlflags'

!END!
my $summary_expanded;

sub myconfig {
    return $summary_expanded if $summary_expanded;
    ($summary_expanded = $summary) =~ s{\$(\w+)}
		 { 
			my $c;
			if ($1 eq 'git_ancestor_line') {
				if ($Config::Config{git_ancestor}) {
					$c= "\n  Ancestor: $Config::Config{git_ancestor}";
				} else {
					$c= "";
				}
			} else {
                     		$c = $Config::Config{$1}; 
			}
			defined($c) ? $c : 'undef' 
		}ge;
    $summary_expanded;
}

local *_ = \my $a;
$_ = <<'!END!';
Author=''
CONFIG='true'
Date='$Date'
Header=''
Id='$Id'
Locker=''
Log='$Log'
PATCHLEVEL='24'
PERL_API_REVISION='5'
PERL_API_SUBVERSION='0'
PERL_API_VERSION='24'
PERL_CONFIG_SH='true'
PERL_PATCHLEVEL=''
PERL_REVISION='5'
PERL_SUBVERSION='0'
PERL_VERSION='24'
RCSfile='$RCSfile'
Revision='$Revision'
SUBVERSION='0'
Source=''
State=''
_a='.a'
_exe=''
_o='.o'
afs='false'
afsroot='/afs'
alignbytes='8'
ansi2knr=''
aphostname='/bin/hostname'
api_revision='5'
api_subversion='0'
api_version='24'
api_versionstring='5.24.0'
ar='aarch64-unknown-nto-qnx7.0.0-ar'
archlib='/usr/lib/perl5/5.24.0/aarch64-nto'
archlibexp='/usr/lib/perl5/5.24.0/aarch64-nto'
archname64=''
archname='aarch64-nto'
archobjs=''
asctime_r_proto='0'
awk='awk'
baserev='5.0'
bash=''
bin='/usr/bin'
bin_ELF='define'
binexp='/usr/bin'
bison='bison'
byacc='byacc'
byteorder='12345678'
c=''
castflags='0'
cat='cat'
cc='aarch64-unknown-nto-qnx7.0.0-gcc'
cccdlflags='-fPIC'
ccdlflags='-Wl,-E'
ccflags='--sysroot=/opt/qnx700/target/qnx7 -mlittle-endian  -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64-W'
ccflags_uselargefiles=''
ccname=''
ccsymbols=''
ccversion=''
cf_by='builder'
cf_email='builder@cltbuild1.bts.rim.net'
cf_time='Sat Jan 28 13:43:45 EST 2017'
charbits='8'
charsize='1'
chgrp=''
chmod='chmod'
chown=''
clocktype='long'
comm='comm'
compress=''
config_arg0='cnf/configure'
config_argc='8'
config_args='--host=aarch64-unknown-nto-qnx7.0.0 --target=aarch64-unknown-nto-qnx7.0.0 --sysroot=/opt/qnx700/target/qnx7 --prefix=/usr --keeplog --mode=target --target=aarch64-unknown-nto-qnx7.0.0 --targetarch=aarch64-unknown-nto-qnx7.0.0'
contains='grep'
cp='cp'
cpio=''
cpp='aarch64-unknown-nto-qnx7.0.0-gcc -E'
cpp_stuff='42'
cppccsymbols=''
cppflags='--sysroot=/opt/qnx700/target/qnx7 -mlittle-endian -I/opt/qnx700/target/qnx7/usr/include'
cpplast='-'
cppminus='-'
cpprun='aarch64-unknown-nto-qnx7.0.0-gcc -E'
cppstdin='aarch64-unknown-nto-qnx7.0.0-gcc -E'
cppsymbols=''
crypt_r_proto='0'
cryptlib=''
csh=''
ctermid_r_proto='0'
ctime_r_proto='0'
d_Gconvert='sprintf((b),"%.*g",(n),(x))'
d_PRIEUldbl='undef'
d_PRIFUldbl='undef'
d_PRIGUldbl='undef'
d_PRIXU64='undef'
d_PRId64='undef'
d_PRIeldbl='undef'
d_PRIfldbl='undef'
d_PRIgldbl='undef'
d_PRIi64='undef'
d_PRIo64='undef'
d_PRIu64='undef'
d_PRIx64='undef'
d_SCNfldbl='undef'
d__fwalk='undef'
d_access='define'
d_accessx='undef'
d_acosh='define'
d_aintl='undef'
d_alarm='define'
d_archlib='define'
d_asctime64='undef'
d_asctime_r='undef'
d_asinh='define'
d_atanh='define'
d_atolf='undef'
d_atoll='define'
d_attribute_deprecated='undef'
d_attribute_format='define'
d_attribute_malloc='define'
d_attribute_nonnull='define'
d_attribute_noreturn='define'
d_attribute_pure='define'
d_attribute_unused='define'
d_attribute_warn_unused_result='define'
d_backtrace='undef'
d_bcmp='define'
d_bcopy='define'
d_bsd='undef'
d_bsdgetpgrp='undef'
d_bsdsetpgrp='undef'
d_builtin_choose_expr='define'
d_builtin_expect='undef'
d_bzero='define'
d_c99_variadic_macros='define'
d_casti32='undef'
d_castneg='define'
d_cbrt='define'
d_charvspr='undef'
d_chown='define'
d_chroot='define'
d_chsize='undef'
d_class='undef'
d_clearenv='define'
d_closedir='define'
d_cmsghdr_s='undef'
d_const='define'
d_copysign='define'
d_copysignl='define'
d_cplusplus='undef'
d_crypt='define'
d_crypt_r='undef'
d_csh='undef'
d_ctermid='define'
d_ctermid_r='undef'
d_ctime64='undef'
d_ctime_r='undef'
d_cuserid='undef'
d_dbl_dig='define'
d_dbminitproto='define'
d_difftime64='undef'
d_difftime='define'
d_dir_dd_fd='undef'
d_dirfd='define'
d_dirnamlen='undef'
d_dladdr='define'
d_dlerror='define'
d_dlopen='define'
d_dlsymun='undef'
d_dosuid='undef'
d_drand48_r='undef'
d_drand48proto='define'
d_dup2='define'
d_duplocale='undef'
d_eaccess='define'
d_endgrent='define'
d_endgrent_r='undef'
d_endhent='define'
d_endhostent_r='undef'
d_endnent='define'
d_endnetent_r='undef'
d_endpent='define'
d_endprotoent_r='define'
d_endpwent='define'
d_endpwent_r='undef'
d_endsent='define'
d_endservent_r='undef'
d_eofnblk='define'
d_erf='define'
d_erfc='define'
d_eunice='undef'
d_exp2='define'
d_expm1='define'
d_faststdio='undef'
d_fchdir='define'
d_fchmod='define'
d_fchown='define'
d_fcntl='define'
d_fcntl_can_lock='undef'
d_fd_macros='undef'
d_fd_set='undef'
d_fdclose='undef'
d_fdim='define'
d_fds_bits='undef'
d_fegetround='define'
d_fgetpos='define'
d_finite='define'
d_finitel='undef'
d_flexfnam='define'
d_flock='define'
d_flockproto='define'
d_fma='define'
d_fmax='define'
d_fmin='define'
d_fork='define'
d_fp_class='undef'
d_fp_classify='undef'
d_fp_classl='undef'
d_fpathconf='define'
d_fpclass='undef'
d_fpclassify='undef'
d_fpclassl='undef'
d_fpgetround='undef'
d_fpos64_t='undef'
d_freelocale='undef'
d_frexpl='define'
d_fs_data_s='undef'
d_fseeko='define'
d_fsetpos='define'
d_fstatfs='undef'
d_fstatvfs='define'
d_fsync='define'
d_ftello='define'
d_ftime='undef'
d_futimes='undef'
d_gdbm_ndbm_h_uses_prototypes='define'
d_gdbm_ndbm_h_uses_prototypes='define'
d_gdbmndbm_h_uses_prototypes='define'
d_gdbmndbm_h_uses_prototypes='define'
d_getaddrinfo='define'
d_getcwd='define'
d_getespwnam='undef'
d_getfsstat='undef'
d_getgrent='define'
d_getgrent_r='undef'
d_getgrgid_r='undef'
d_getgrnam_r='undef'
d_getgrps='define'
d_gethbyaddr='define'
d_gethbyname='define'
d_gethent='define'
d_gethname='define'
d_gethostbyaddr_r='undef'
d_gethostbyname_r='undef'
d_gethostent_r='undef'
d_gethostprotos='define'
d_getitimer='define'
d_getlogin='define'
d_getlogin_r='undef'
d_getmnt='undef'
d_getmntent='undef'
d_getnameinfo='define'
d_getnbyaddr='define'
d_getnbyname='define'
d_getnent='define'
d_getnetbyaddr_r='undef'
d_getnetbyname_r='undef'
d_getnetent_r='undef'
d_getnetprotos='define'
d_getpagsz='define'
d_getpbyname='define'
d_getpbynumber='define'
d_getpent='define'
d_getpgid='define'
d_getpgrp2='undef'
d_getpgrp='define'
d_getppid='define'
d_getprior='define'
d_getprotobyname_r='define'
d_getprotobynumber_r='define'
d_getprotoent_r='define'
d_getprotoprotos='define'
d_getprpwnam='undef'
d_getpwent='define'
d_getpwent_r='undef'
d_getpwnam_r='undef'
d_getpwuid_r='undef'
d_getsbyname='define'
d_getsbyport='define'
d_getsent='define'
d_getservbyname_r='undef'
d_getservbyport_r='undef'
d_getservent_r='undef'
d_getservprotos='define'
d_getspnam='define'
d_getspnam_r='undef'
d_gettimeod='define'
d_gmtime64='undef'
d_gmtime_r='undef'
d_gnulibc='undef'
d_grpasswd='define'
d_hasmntopt='undef'
d_htonl='define'
d_hypot='define'
d_ilogb='define'
d_ilogbl='define'
d_inc_version_list='undef'
d_index='define'
d_inetaton='define'
d_inetntop='define'
d_inetpton='define'
d_int64_t='undef'
d_ip_mreq='undef'
d_ip_mreq_source='undef'
d_ipv6_mreq='undef'
d_ipv6_mreq_source='undef'
d_isascii='define'
d_isblank='define'
d_isfinite='define'
d_isfinitel='undef'
d_isinf='define'
d_isinfl='undef'
d_isless='define'
d_isnan='define'
d_isnanl='undef'
d_isnormal='define'
d_j0='define'
d_j0l='undef'
d_killpg='define'
d_lc_monetary_2008='undef'
d_lchown='define'
d_ldbl_dig='define'
d_ldexpl='define'
d_lgamma='define'
d_lgamma_r='define'
d_libm_lib_version='undef'
d_link='define'
d_llrint='define'
d_llrintl='define'
d_llround='define'
d_llroundl='define'
d_localtime64='undef'
d_localtime_r='undef'
d_localtime_r_needs_tzset='undef'
d_locconv='define'
d_lockf='define'
d_log1p='define'
d_log2='define'
d_logb='define'
d_longdbl='define'
d_longlong='define'
d_lrint='define'
d_lrintl='define'
d_lround='define'
d_lroundl='define'
d_lseekproto='define'
d_lstat='define'
d_madvise='undef'
d_malloc_good_size='undef'
d_malloc_size='undef'
d_mblen='define'
d_mbstowcs='define'
d_mbtowc='define'
d_memchr='define'
d_memcmp='define'
d_memcpy='define'
d_memmem='undef'
d_memmove='define'
d_memset='define'
d_mkdir='define'
d_mkdtemp='define'
d_mkfifo='define'
d_mkstemp='define'
d_mkstemps='define'
d_mktime64='undef'
d_mktime='define'
d_mmap='define'
d_modfl='define'
d_modflproto='define'
d_mprotect='define'
d_msg='undef'
d_msg_ctrunc='undef'
d_msg_dontroute='undef'
d_msg_oob='undef'
d_msg_peek='undef'
d_msg_proxy='undef'
d_msgctl='undef'
d_msgget='undef'
d_msghdr_s='undef'
d_msgrcv='undef'
d_msgsnd='undef'
d_msync='define'
d_munmap='define'
d_mymalloc='undef'
d_nan='define'
d_ndbm='undef'
d_ndbm_h_uses_prototypes='define'
d_nearbyint='define'
d_newlocale='undef'
d_nextafter='define'
d_nexttoward='define'
d_nice='define'
d_nl_langinfo='undef'
d_nv_preserves_uv='undef'
d_nv_zero_is_allbits_zero='define'
d_off64_t='undef'
d_old_pthread_create_joinable='undef'
d_oldpthreads='undef'
d_oldsock='undef'
d_open3='define'
d_pathconf='define'
d_pause='define'
d_perl_otherlibdirs='undef'
d_phostname='undef'
d_pipe='define'
d_poll='define'
d_portable='undef'
d_prctl='undef'
d_prctl_set_name='undef'
d_printf_format_null='define'
d_procselfexe='undef'
d_pseudofork='undef'
d_pthread_atfork='define'
d_pthread_attr_setscope='define'
d_pthread_yield='undef'
d_ptrdiff_t='undef'
d_pwage='define'
d_pwchange='undef'
d_pwclass='undef'
d_pwcomment='define'
d_pwexpire='undef'
d_pwgecos='define'
d_pwpasswd='define'
d_pwquota='undef'
d_qgcvt='undef'
d_quad='define'
d_random_r='undef'
d_re_comp='define'
d_readdir64_r='undef'
d_readdir='define'
d_readdir_r='undef'
d_readlink='define'
d_readv='define'
d_recvmsg='define'
d_regcmp='undef'
d_regcomp='define'
d_remainder='define'
d_remquo='define'
d_rename='define'
d_rewinddir='define'
d_rint='define'
d_rmdir='define'
d_round='define'
d_safebcpy='undef'
d_safemcpy='undef'
d_sanemcmp='define'
d_sbrkproto='define'
d_scalbn='define'
d_scalbnl='define'
d_sched_yield='define'
d_scm_rights='undef'
d_seekdir='define'
d_select='define'
d_sem='undef'
d_semctl='undef'
d_semctl_semid_ds='undef'
d_semctl_semun='undef'
d_semget='undef'
d_semop='undef'
d_sendmsg='define'
d_setegid='define'
d_seteuid='define'
d_setgrent='define'
d_setgrent_r='undef'
d_setgrps='define'
d_sethent='define'
d_sethostent_r='undef'
d_setitimer='define'
d_setlinebuf='define'
d_setlocale='define'
d_setlocale_r='undef'
d_setnent='define'
d_setnetent_r='undef'
d_setpent='define'
d_setpgid='define'
d_setpgrp2='undef'
d_setpgrp='define'
d_setprior='define'
d_setproctitle='undef'
d_setprotoent_r='define'
d_setpwent='define'
d_setpwent_r='undef'
d_setregid='define'
d_setresgid='undef'
d_setresuid='undef'
d_setreuid='define'
d_setrgid='undef'
d_setruid='undef'
d_setsent='define'
d_setservent_r='undef'
d_setsid='define'
d_setvbuf='define'
d_sfio='undef'
d_shm='undef'
d_shmat='undef'
d_shmatprototype='define'
d_shmctl='undef'
d_shmdt='undef'
d_shmget='undef'
d_sigaction='define'
d_siginfo_si_addr='undef'
d_siginfo_si_band='undef'
d_siginfo_si_errno='undef'
d_siginfo_si_fd='undef'
d_siginfo_si_pid='undef'
d_siginfo_si_status='undef'
d_siginfo_si_uid='undef'
d_siginfo_si_value='undef'
d_signbit='define'
d_sigprocmask='define'
d_sigsetjmp='define'
d_sin6_scope_id='define'
d_sitearch='define'
d_snprintf='define'
d_sockaddr_in6='undef'
d_sockaddr_sa_len='define'
d_sockatmark='define'
d_sockatmarkproto='define'
d_socket='define'
d_socklen_t='undef'
d_sockpair='define'
d_socks5_init='undef'
d_sprintf_returns_strlen='define'
d_sqrtl='define'
d_srand48_r='undef'
d_srandom_r='undef'
d_sresgproto='define'
d_sresuproto='define'
d_stat='define'
d_statblks='define'
d_statfs_f_flags='undef'
d_statfs_s='undef'
d_static_inline='undef'
d_statvfs='define'
d_stdio_cnt_lval='undef'
d_stdio_ptr_lval='undef'
d_stdio_ptr_lval_nochange_cnt='undef'
d_stdio_ptr_lval_sets_cnt='undef'
d_stdio_stream_array='undef'
d_stdiobase='undef'
d_stdstdio='undef'
d_strchr='define'
d_strcoll='define'
d_strctcpy='define'
d_strerrm='strerror(e)'
d_strerror='define'
d_strerror_r='undef'
d_strftime='define'
d_strlcat='define'
d_strlcpy='define'
d_strtod='define'
d_strtol='define'
d_strtold='define'
d_strtoll='define'
d_strtoq='undef'
d_strtoul='define'
d_strtoull='define'
d_strtouq='undef'
d_strxfrm='define'
d_suidsafe='undef'
d_symlink='define'
d_syscall='undef'
d_syscallproto='define'
d_sysconf='define'
d_sysernlst=''
d_syserrlst='undef'
d_system='define'
d_tcgetpgrp='define'
d_tcsetpgrp='define'
d_telldir='define'
d_telldirproto='define'
d_tgamma='define'
d_time='define'
d_timegm='define'
d_times='define'
d_tm_tm_gmtoff='define'
d_tm_tm_zone='define'
d_tmpnam_r='undef'
d_trunc='define'
d_truncate='define'
d_truncl='define'
d_ttyname_r='undef'
d_tz_name=''
d_tzname='define'
d_u32align='undef'
d_ualarm='define'
d_umask='define'
d_uname='define'
d_union_semun='undef'
d_unordered='undef'
d_unsetenv='define'
d_uselocale='undef'
d_usleep='define'
d_usleepproto='define'
d_ustat='undef'
d_vendorarch='undef'
d_vendorbin='undef'
d_vendorlib='undef'
d_vendorscript='undef'
d_vfork='undef'
d_void_closedir='undef'
d_voidsig='undef'
d_voidtty=''
d_volatile='define'
d_vprintf='define'
d_vsnprintf='define'
d_wait4='define'
d_waitpid='define'
d_wcscmp='define'
d_wcstombs='define'
d_wcsxfrm='define'
d_wctomb='define'
d_writev='define'
d_xenix='undef'
date='date'
db_hashtype='unsigned int'
db_prefixtype='size_t'
db_version_major=''
db_version_minor=''
db_version_patch=''
defvoidused='15'
direntrytype='struct dirent'
disable_win32='1'
disable_win32api_file='1'
disable_win32core='1'
disabled_dynamic_ext='ext/Amiga-ARexx ext/Amiga-Exec ext/GDBM_File ext/I18N-Langinfo ext/NDBM_File ext/ODBM_File ext/VMS-DCLsym ext/VMS-Stdio ext/Win32CORE cpan/DB_File cpan/IPC-SysV cpan/Win32 cpan/Win32API-File '
disabled_nonxs_ext='ext/VMS-Filespec '
disabledmods='define'
dlext='so'
dlsrc='dl_dlopen.xs'
doubleinfbytes='0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f'
doublekind='3'
doublemantbits='0'
doublenanbytes='0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x7f'
doublesize='8'
drand01='drand48()'
drand48_r_proto='0'
dtrace=''
dtraceobject='undef'
dynamic_ext='arybase attributes B Devel/Peek Fcntl File/DosGlob File/Glob Hash/Util Hash/Util/FieldHash mro Opcode PerlIO/encoding PerlIO/mmap PerlIO/scalar PerlIO/via POSIX re SDBM_File Sys/Hostname Tie/Hash/NamedCapture XS/APItest XS/Typemap Compress/Raw/Bzip2 Compress/Raw/Zlib Devel/PPPort Digest/MD5 Digest/SHA Encode Filter/Util/Call Math/BigInt/FastCalc MIME/Base64 Scalar/List/Utils Socket Sys/Syslog Time/Piece Unicode/Collate Unicode/Normalize Data/Dumper IO PathTools Storable threads threads/shared Time/HiRes'
eagain='EAGAIN'
ebcdic='undef'
echo='echo'
egrep='egrep'
emacs=''
endgrent_r_proto='0'
endhostent_r_proto='0'
endnetent_r_proto='0'
endprotoent_r_proto='0'
endpwent_r_proto='0'
endservent_r_proto='0'
eunicefix=':'
exe_ext=''
expr=''
expr='expr'
extensions='arybase attributes B Devel/Peek Fcntl File/DosGlob File/Glob Hash/Util Hash/Util/FieldHash mro Opcode PerlIO/encoding PerlIO/mmap PerlIO/scalar PerlIO/via POSIX re SDBM_File Sys/Hostname Tie/Hash/NamedCapture XS/APItest XS/Typemap Compress/Raw/Bzip2 Compress/Raw/Zlib Devel/PPPort Digest/MD5 Digest/SHA Encode Filter/Util/Call Math/BigInt/FastCalc MIME/Base64 Scalar/List/Utils Socket Sys/Syslog Time/Piece Unicode/Collate Unicode/Normalize Data/Dumper IO PathTools Storable threads threads/shared Time/HiRes Errno ExtUtils/Miniperl FileCache File/Find IPC/Open3 Pod/Functions Pod/Html Tie/Memoize Archive/Tar autodie AutoLoader B/Debug bignum Config/Perl/V CPAN CPAN/Meta CPAN/Meta/Requirements CPAN/Meta/YAML Digest experimental ExtUtils/Constant ExtUtils/Install ExtUtils/MakeMaker ExtUtils/Manifest File/Fetch File/Path File/Temp Getopt/Long HTTP/Tiny IO/Compress IO/Socket/IP IO/Zlib IPC/Cmd JSON/PP libnet Locale/Codes Locale/Maketext/Simple Math/BigInt Math/BigRat Math/Complex Memoize Module/Load Module/Load/Conditional Module/Loaded Module/Metadata NEXT Params/Check parent Parse/CPAN/Meta perlfaq PerlIO/via/QuotedPrint Perl/OSType Pod/Checker Pod/Escapes podlators Pod/Parser Pod/Perldoc Pod/Simple Pod/Usage Term/ANSIColor Term/Cap Test/Harness Test/Simple Text/Balanced Text/ParseWords Text/Tabs Tie/RefHash Time/Local version Attribute/Handlers autouse base Carp constant Devel/SelfStubber Dumpvalue encoding/warnings Env Exporter ExtUtils/CBuilder ExtUtils/ParseXS Filter/Simple I18N/Collate I18N/LangTags if lib Locale/Maketext Module/CoreList Net/Ping Safe Search/Dict SelfLoader Term/Complete Term/ReadLine Test Text/Abbrev Thread/Queue Thread/Semaphore Tie/File XSLoader'
extern_C='extern'
extras=''
fflushNULL='define'
fflushall='undef'
find=''
firstmakefile='Makefile'
flex=''
fpossize='16'
fpostype='fpos_t'
freetype='void'
from=':'
full_ar='ar'
full_csh='csh'
full_sed='sed'
gccansipedantic=''
gccosandvers=''
gccversion='5.4.0 [qnx700 1233]'
getgrent_r_proto='0'
getgrgid_r_proto='0'
getgrnam_r_proto='0'
gethostbyaddr_r_proto='0'
gethostbyname_r_proto='0'
gethostent_r_proto='0'
getlogin_r_proto='0'
getnetbyaddr_r_proto='0'
getnetbyname_r_proto='0'
getnetent_r_proto='0'
getprotobyname_r_proto='0'
getprotobynumber_r_proto='0'
getprotoent_r_proto='0'
getpwent_r_proto='0'
getpwnam_r_proto='0'
getpwuid_r_proto='0'
getservbyname_r_proto='0'
getservbyport_r_proto='0'
getservent_r_proto='0'
getspnam_r_proto='0'
gidformat='"lu"'
gidsign='1'
gidsize='4'
gidtype='gid_t'
glibpth='/lib /usr/lib /usr/local/lib'
gmake='gmake'
gmtime_r_proto='0'
gnulibc_version=''
grep='grep'
groupcat='cat /etc/group'
groupstype='gid_t'
gzip='gzip'
h_fcntl='false'
h_sysfile='true'
hint='default'
hostcat='cat /etc/hosts'
html1dir='/usr/share/doc/perl/html'
html1direxp='/usr/share/doc/perl/html'
html3dir='/usr/share/doc/perl/html'
html3direxp='/usr/share/doc/perl/html'
i16size='2'
i16type='int16_t'
i32size='4'
i32type='int32_t'
i64size='8'
i64type='int64_t'
i8size='1'
i8type='int8_t'
i_arpainet='define'
i_assert='define'
i_bfd='undef'
i_bsdioctl=''
i_crypt='undef'
i_db='undef'
i_dbm='undef'
i_dirent='define'
i_dld='undef'
i_dlfcn='define'
i_execinfo='undef'
i_fcntl='define'
i_fenv='define'
i_float='define'
i_fp='undef'
i_fp_class='undef'
i_gdbm='undef'
i_gdbm_ndbm='undef'
i_gdbmndbm='undef'
i_grp='define'
i_ieeefp='undef'
i_inttypes='define'
i_langinfo='undef'
i_libutil='undef'
i_limits='define'
i_locale='define'
i_machcthr='undef'
i_malloc='define'
i_mallocmalloc='undef'
i_math='define'
i_memory='define'
i_mntent='undef'
i_ndbm='undef'
i_netdb='define'
i_neterrno='undef'
i_netinettcp='define'
i_niin='define'
i_poll='define'
i_prot='undef'
i_pthread='undef'
i_pwd='define'
i_quadmath='undef'
i_rpcsvcdbm='undef'
i_sfio='undef'
i_sgtty='define'
i_shadow='define'
i_socks='undef'
i_stdarg='define'
i_stdbool='define'
i_stddef='define'
i_stdint='define'
i_stdlib='define'
i_string='define'
i_sunmath='undef'
i_sysaccess='undef'
i_sysdir='define'
i_sysfile='define'
i_sysfilio='undef'
i_sysin='undef'
i_sysioctl='define'
i_syslog='define'
i_sysmman='define'
i_sysmode='undef'
i_sysmount='define'
i_sysndir='undef'
i_sysparam='define'
i_syspoll='define'
i_sysresrc='define'
i_syssecrt='undef'
i_sysselct='define'
i_syssockio='define'
i_sysstat='define'
i_sysstatfs='undef'
i_sysstatvfs='define'
i_systime='define'
i_systimek='undef'
i_systimes='define'
i_systypes='define'
i_sysuio='define'
i_sysun='define'
i_sysutsname='define'
i_sysvfs='undef'
i_syswait='define'
i_termio='undef'
i_termios='define'
i_time='define'
i_unistd='define'
i_ustat='define'
i_utime='define'
i_values='undef'
i_varargs='undef'
i_varhdr='stdarg.h'
i_vfork='undef'
i_xocale='undef'
ignore_versioned_solibs=''
inc_version_list=''
inc_version_list_init=''
incpath=''
inews=''
initialinstalllocation=''
installarchlib='/usr/lib/perl5/5.24.0/aarch64-nto'
installbin='/usr/bin'
installhtml1dir='/usr/share/doc/perl/html'
installhtml1dir='/usr/share/doc/perl/html'
installhtml3dir='/usr/share/doc/perl/html'
installhtml3dir='/usr/share/doc/perl/html'
installlib='/usr/lib'
installman1dir='/usr/share/man/man1'
installman3dir='/usr/share/man/man3'
installprefix=''
installprefixexp=''
installprivlib='/usr/lib/perl5/5.24.0'
installscript='/usr/bin'
installsitearch='/usr/lib/perl5/site_perl/5.24.0/aarch64-nto'
installsitebin='/usr/bin'
installsitehtml1dir='/usr/share/doc/perl/html'
installsitehtml3dir='/usr/share/doc/perl/html'
installsitelib='/usr/lib/perl5/site_perl/5.24.0'
installsiteman1dir='/usr/share/man/man1'
installsiteman3dir='/usr/share/man/man3'
installsitescript='/usr/bin'
installstyle='lib/perl5'
installusrbinperl='define'
installvendorarch=''
installvendorbin=''
installvendorhtml1dir='/usr/share/doc/perl/html'
installvendorhtml3dir='/usr/share/doc/perl/html'
installvendorlib=''
installvendorman1dir='/usr/share/man/man1'
installvendorman3dir='/usr/share/man/man3'
installvendorscript=''
intsize='4'
issymlink='test -h'
ivdformat='"ld"'
ivsize='8'
ivtype='long'
known_extensions='Amiga/ARexx Amiga/Exec arybase attributes B Devel/Peek Errno ExtUtils/Miniperl Fcntl FileCache File/DosGlob File/Find File/Glob GDBM_File Hash/Util Hash/Util/FieldHash I18N/Langinfo IPC/Open3 mro NDBM_File ODBM_File Opcode PerlIO/encoding PerlIO/mmap PerlIO/scalar PerlIO/via Pod/Functions Pod/Html POSIX re SDBM_File Sys/Hostname Tie/Hash/NamedCapture Tie/Memoize VMS/DCLsym VMS/Filespec VMS/Stdio Win32CORE XS/APItest XS/Typemap Archive/Tar autodie AutoLoader B/Debug bignum Compress/Raw/Bzip2 Compress/Raw/Zlib Config/Perl/V CPAN CPAN/Meta CPAN/Meta/Requirements CPAN/Meta/YAML DB_File Devel/PPPort Digest Digest/MD5 Digest/SHA Encode experimental ExtUtils/Constant ExtUtils/Install ExtUtils/MakeMaker ExtUtils/Manifest File/Fetch File/Path File/Temp Filter/Util/Call Getopt/Long HTTP/Tiny IO/Compress IO/Socket/IP IO/Zlib IPC/Cmd IPC/SysV JSON/PP libnet Locale/Codes Locale/Maketext/Simple Math/BigInt Math/BigInt/FastCalc Math/BigRat Math/Complex Memoize MIME/Base64 Module/Load Module/Load/Conditional Module/Loaded Module/Metadata NEXT Params/Check parent Parse/CPAN/Meta perlfaq PerlIO/via/QuotedPrint Perl/OSType Pod/Checker Pod/Escapes podlators Pod/Parser Pod/Perldoc Pod/Simple Pod/Usage Scalar/List/Utils Socket Sys/Syslog Term/ANSIColor Term/Cap Test/Harness Test/Simple Text/Balanced Text/ParseWords Text/Tabs Tie/RefHash Time/Local Time/Piece Unicode/Collate Unicode/Normalize version Win32 Win32API/File Attribute/Handlers autouse base Carp constant Data/Dumper Devel/SelfStubber Dumpvalue encoding/warnings Env Exporter ExtUtils/CBuilder ExtUtils/ParseXS Filter/Simple I18N/Collate I18N/LangTags if IO lib Locale/Maketext Module/CoreList Net/Ping PathTools Safe Search/Dict SelfLoader Storable Term/Complete Term/ReadLine Test Text/Abbrev Thread/Queue threads Thread/Semaphore threads/shared Tie/File Time/HiRes XSLoader'
ksh=''
ld='aarch64-unknown-nto-qnx7.0.0-gcc'
ld_can_script='define'
lddlflags='--sysroot=/opt/qnx700/target/qnx7 -shared -L/opt/qnx700/target/qnx7/aarch64le/lib -L/opt/qnx700/target/qnx7/aarch64le/usr/lib'
ldflags='--sysroot=/opt/qnx700/target/qnx7 -mlittle-endian -L/opt/qnx700/target/qnx7/aarch64le/lib -L/opt/qnx700/target/qnx7/aarch64le/usr/lib'
ldflags_uselargefiles=''
ldlibpthname='LD_LIBRARY_PATH'
less='less'
lib='/usr/lib'
lib_ext='.a'
libc=''
libperl='libperl.a'
libpth='/lib /usr/lib /usr/local/lib'
libs=' -lm -lsocket -lc'
libsdirs=' '
libsfiles=''
libsfound=''
libspath=''
libswanted='m crypt pthread sfio socket inet nsl nm ndbm gdbm dbm db malloc dl dld ld sun sec util c cposix posix ucb BSD gdbm_compat'
libswanted_uselargefiles=''
line=''
lint=''
lkflags=''
ln='ln'
lns='ln -s'
localtime_r_proto='0'
locincpth=''
loclibpth=''
longdblinfbytes='0'
longdblkind='-1'
longdblmantbits='0'
longdblnanbytes='0'
longdblsize='16'
longlongsize='8'
longsize='8'
lp=''
lpr=''
ls='ls'
lseeksize='8'
lseektype='off_t'
mad='undef'
madlyh=''
madlyobj=''
madlysrc=''
mail=''
mailx=''
make='make'
make_set_make='#'
mallocobj=''
mallocsrc=''
malloctype='void*'
man1dir='/usr/share/man/man1'
man1direxp='/usr/share/man/man1'
man1ext='1'
man3dir='/usr/share/man/man3'
man3direxp='/usr/share/man/man3'
man3ext='3'
mips_type=''
mistrustnm=''
mkdir='mkdir'
mmaptype='void *'
modetype='mode_t'
more='more'
multiarch='undef'
mv=''
myarchname=''
mydomain=''
myhostname='cltbuild1'
myuname='aarch64-unknown-nto-qnx7.0.0'
n='XS/Typemap'
n='XS/Typemap'
need_va_copy='define'
netdb_hlen_type='socklen_t'
netdb_host_type='const void *'
netdb_name_type='int'
netdb_net_type='uint32_t'
nm='nm'
nm_opt=''
nm_so_opt=''
nonxs_ext='Errno ExtUtils/Miniperl FileCache File/Find IPC/Open3 Pod/Functions Pod/Html Tie/Memoize Archive/Tar autodie AutoLoader B/Debug bignum Config/Perl/V CPAN CPAN/Meta CPAN/Meta/Requirements CPAN/Meta/YAML Digest experimental ExtUtils/Constant ExtUtils/Install ExtUtils/MakeMaker ExtUtils/Manifest File/Fetch File/Path File/Temp Getopt/Long HTTP/Tiny IO/Compress IO/Socket/IP IO/Zlib IPC/Cmd JSON/PP libnet Locale/Codes Locale/Maketext/Simple Math/BigInt Math/BigRat Math/Complex Memoize Module/Load Module/Load/Conditional Module/Loaded Module/Metadata NEXT Params/Check parent Parse/CPAN/Meta perlfaq PerlIO/via/QuotedPrint Perl/OSType Pod/Checker Pod/Escapes podlators Pod/Parser Pod/Perldoc Pod/Simple Pod/Usage Term/ANSIColor Term/Cap Test/Harness Test/Simple Text/Balanced Text/ParseWords Text/Tabs Tie/RefHash Time/Local version Attribute/Handlers autouse base Carp constant Devel/SelfStubber Dumpvalue encoding/warnings Env Exporter ExtUtils/CBuilder ExtUtils/ParseXS Filter/Simple I18N/Collate I18N/LangTags if lib Locale/Maketext Module/CoreList Net/Ping Safe Search/Dict SelfLoader Term/Complete Term/ReadLine Test Text/Abbrev Thread/Queue Thread/Semaphore Tie/File XSLoader'
nroff='nroff'
nvEUformat='"E"'
nvFUformat='"F"'
nvGUformat='"G"'
nv_overflows_integers_at='256.0*256.0*256.0*256.0*256.0*256.0*2.0*2.0*2.0*2.0*2.0'
nv_preserves_uv_bits='53'
nveformat='"e"'
nvfformat='"f"'
nvgformat='"g"'
nvmantbits='0'
nvsize='8'
nvtype='double'
o_nonblock='O_NONBLOCK'
obj_ext='.o'
objdump='aarch64-unknown-nto-qnx7.0.0-objdump'
old_pthread_create_joinable='PTHREAD_CREATE_JOINABLE'
optimize=''
orderlib=''
osname='linux'
osvers='current'
otherlibdirs=' '
package='perl5'
pager='less'
passcat='cat /etc/passwd'
patchlevel='24'
path_sep=':'
perl5=''
perl=''
perl_patchlevel=''
perl_static_inline='static'
perladmin='nobody@nowhere.land'
perllibs='-lm'
perlpath='/usr/bin/perl'
pg='pg'
phostname='hostname'
pidtype='pid_t'
plibpth=''
pmake=''
pr=''
prefix='/usr'
prefixexp='/usr'
privlib='/usr/lib/perl5/5.24.0'
privlibexp='/usr/lib/perl5/5.24.0'
procselfexe='"/proc/self/exe"'
prototype='define'
ptrsize='8'
quadkind='QUAD_IS_INT64_T'
quadtype='int64_t'
randbits='48'
randfunc='drand48'
random_r_proto='0'
randseedtype='long'
ranlib='aarch64-unknown-nto-qnx7.0.0-ranlib'
rd_nodata='-1'
readdir64_r_proto='0'
readdir_r_proto='0'
revision='5'
rm='rm'
rm_try=''
rmail=''
run=''
runnm='false'
sGMTIME_max='2147483647'
sGMTIME_min='-2147483648'
sLOCALTIME_max='2147483647'
sLOCALTIME_min='-2147483648'
sPRIEUldbl='"LE"'
sPRIFUldbl='"LF"'
sPRIGUldbl='"LG"'
sPRIXU64='"LX"'
sPRId64='"Ld"'
sPRIeldbl='"Le"'
sPRIfldbl='"Lf"'
sPRIgldbl='"Lg"'
sPRIi64='"Li"'
sPRIo64='"Lo"'
sPRIu64='"Lu"'
sPRIx64='"Lx"'
sSCNfldbl='"Lf"'
sched_yield='sched_yield()'
scriptdir='/usr/bin'
scriptdirexp='/usr/bin'
sed='sed'
seedfunc='srand48'
selectminbits='32'
selecttype='fd_set *'
sendmail=''
setgrent_r_proto='0'
sethostent_r_proto='0'
setlocale_r_proto='0'
setnetent_r_proto='0'
setprotoent_r_proto='0'
setpwent_r_proto='0'
setservent_r_proto='0'
sh='/bin/sh'
shar=''
sharedir='/usr/share'
sharpbang='#!'
shmattype='void *'
shortsize='2'
shrpenv=''
shsharp='true'
sig_count=''
sig_name='ZERO SIGHUP SIGINT SIGQUIT SIGILL SIGTRAP SIGABRT SIGBUS SIGFPE SIGKILL SIGUSR1 SIGSEGV SIGUSR2 SIGPIPE SIGALRM SIGTERM SIGCHLD SIGCONT SIGSTOP SIGTSTP SIGTTIN SIGTTOU SIGURG SIGXCPU SIGXFSZ SIGVTALRM SIGPROF SIGWINCH SIGIO SIGPWR SIGSYS SIGRTMAX SIGIOT SIGCLD SIGPOLL'
sig_name_init='"ZERO", "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE", "KILL", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "CHLD", "CONT", "STOP", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH", "IO", "PWR", "SYS", "RTMAX", "IOT", "CLD", "POLL", 0'
sig_num='0 1 2 3 4 5 6 10 8 9 16 11 17 13 14 15 18 25 23 24 26 27 21 30 31 28 29 20 22 19 12 56 6 18 22'
sig_num_init='0, 1, 2, 3, 4, 5, 6, 10, 8, 9, 16, 11, 17, 13, 14, 15, 18, 25, 23, 24, 26, 27, 21, 30, 31, 28, 29, 20, 22, 19, 12, 56, 6, 18, 22, 0'
sig_size='35'
signal_t='void'
sitearch='/usr/lib/perl5/site_perl/5.24.0/aarch64-nto'
sitearchexp='/usr/lib/perl5/site_perl/5.24.0/aarch64-nto'
sitebin='/usr/bin'
sitebinexp='/usr/bin'
sitehtml1dir='/usr/share/doc/perl/html'
sitehtml1direxp='/usr/share/doc/perl/html'
sitehtml3dir='/usr/share/doc/perl/html'
sitehtml3direxp='/usr/share/doc/perl/html'
sitelib='/usr/lib/perl5/site_perl/5.24.0'
sitelib_stem='/usr/lib/perl5/site_perl'
sitelibexp='/usr/lib/perl5/site_perl/5.24.0'
siteman1dir='/usr/share/man/man1'
siteman1direxp='/usr/share/man/man1'
siteman3dir='/usr/share/man/man3'
siteman3direxp='/usr/share/man/man3'
siteprefix='/usr'
siteprefixexp='/usr'
sitescript='/usr/bin'
sitescriptexp='/usr/bin'
sizesize='8'
sizetype='size_t'
sleep=''
smail=''
so='so'
sockethdr=''
socketlib=''
socksizetype='socklen_t'
soname=''
sort='sort'
spackage='Perl5'
spitshell='cat'
srand48_r_proto='0'
srandom_r_proto='0'
src='/builds/SDP700-perl/perl/build'
ssizetype='ssize_t'
st_ino_sign='1'
st_ino_size='4'
startperl='#!/usr/bin/perl'
startsh='#!/bin/sh'
static_ext=''
stdchar='char'
stdio_base=''
stdio_bufsiz=''
stdio_cnt=''
stdio_filbuf=''
stdio_ptr=''
stdio_stream_array=''
strerror_r_proto='0'
strings=''
submit=''
subversion='0'
sysman=''
sysroot='/opt/qnx700/target/qnx7'
tail=''
tar=''
targetarch='aarch64-unknown-nto-qnx7.0.0'
targetsh='/bin/sh'
tbl=''
tee=''
test='test'
timeincl=''
timetype='time_t'
tmpnam_r_proto='0'
to=':'
touch='touch'
tr='tr'
trnl='\n'
troff=''
ttyname_r_proto='0'
u16size='2'
u16type='uint16_t'
u32size='4'
u32type='uint32_t'
u64size='8'
u64type='uint64_t'
u8size='1'
u8type='uint8_t'
uidformat='"lu"'
uidsign='1'
uidsize='4'
uidtype='uid_t'
uname='uname'
uniq='uniq'
uquadtype='uint64_t'
use5005threads='undef'
use64bitall='undef'
use64bitint='undef'
usecbacktrace='undef'
usecrosscompile='define'
usedevel='undef'
usedl='define'
usedtrace='undef'
usefaststdio='undef'
useithreads='undef'
usekernprocpathname='undef'
uselargefiles='define'
uselongdouble='undef'
usemallocwrap='define'
usemmldlt='define'
usemorebits='undef'
usemultiplicity='undef'
usemymalloc='n'
usenm='false'
usensgetexecutablepath='undef'
useopcode='define'
useperlio='define'
useposix='true'
usequadmath='undef'
usereentrant='undef'
userelocatableinc='undef'
usesfio='false'
useshrplib='false'
usesitecustomize='undef'
usesocks='undef'
usethreads='undef'
usevendorprefix='undef'
useversionedarchname='undef'
usevfork='false'
usrinc=''
uuname=''
uvXUformat='"lX"'
uvoformat='"lo"'
uvsize='8'
uvtype='unsigned long'
uvuformat='"lu"'
uvxformat='"lx"'
vaproto='define'
vendorarch=''
vendorarchexp=''
vendorbin=''
vendorbinexp=''
vendorhtml1dir='/usr/share/doc/perl/html'
vendorhtml1direxp='/usr/share/doc/perl/html'
vendorhtml3dir='/usr/share/doc/perl/html'
vendorhtml3direxp='/usr/share/doc/perl/html'
vendorlib=''
vendorlib_stem=''
vendorlibexp=''
vendorman1dir='/usr/share/man/man1'
vendorman1direxp='/usr/share/man/man1'
vendorman3dir='/usr/share/man/man3'
vendorman3direxp='/usr/share/man/man3'
vendorprefix=''
vendorprefixexp=''
vendorscript=''
vendorscriptexp=''
version='5.24.0'
version_patchlevel_string='version 24 subversion 0'
versiononly='undef'
vi=''
voidflags='15'
xlibpth=''
yacc='yacc'
yaccflags=''
zcat=''
zip='zip'
!END!

my $i = ord(8);
foreach my $c (7,6,5,4,3,2,1) { $i <<= 8; $i |= ord($c); }
our $byteorder = join('', unpack('aaaaaaaa', pack('L!', $i)));
s/(byteorder=)(['"]).*?\2/$1$2$Config::byteorder$2/m;

my $config_sh_len = length $_;

our $Config_SH_expanded = "\n$_" . << 'EOVIRTUAL';
ccflags_nolargefiles='--sysroot=/opt/qnx700/target/qnx7 -mlittle-endian  -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64-W'
ldflags_nolargefiles='--sysroot=/opt/qnx700/target/qnx7 -mlittle-endian -L/opt/qnx700/target/qnx7/aarch64le/lib -L/opt/qnx700/target/qnx7/aarch64le/usr/lib'
libs_nolargefiles=' -lm -lsocket -lc'
libswanted_nolargefiles='m crypt pthread sfio socket inet nsl nm ndbm gdbm dbm db malloc dl dld ld sun sec util c cposix posix ucb BSD gdbm_compat'
ccwarnflags=' -Wall -Werror=declaration-after-statement -Wextra -Wc++-compat -Wwrite-strings'
ccstdflags=' -std=c89'
EOVIRTUAL
eval {
	# do not have hairy conniptions if this isnt available
	require 'Config_git.pl';
	$Config_SH_expanded .= $Config::Git_Data;
	1;
} or warn "Warning: failed to load Config_git.pl, something strange about this perl...\n";

# Search for it in the big string
sub fetch_string {
    my($self, $key) = @_;

    return undef unless $Config_SH_expanded =~ /\n$key=\'(.*?)\'\n/s;
    # So we can say "if $Config{'foo'}".
    $self->{$key} = $1 eq 'undef' ? undef : $1;
}

my $prevpos = 0;

sub FIRSTKEY {
    $prevpos = 0;
    substr($Config_SH_expanded, 1, index($Config_SH_expanded, '=') - 1 );
}

sub NEXTKEY {
    my $pos = index($Config_SH_expanded, qq('\n), $prevpos) + 2;
    my $len = index($Config_SH_expanded, "=", $pos) - $pos;
    $prevpos = $pos;
    $len > 0 ? substr($Config_SH_expanded, $pos, $len) : undef;
}

sub EXISTS {
    return 1 if exists($_[0]->{$_[1]});

    return(index($Config_SH_expanded, "\n$_[1]='") != -1
          );
}

sub STORE  { die "\%Config::Config is read-only\n" }
*DELETE = *CLEAR = \*STORE; # Typeglob aliasing uses less space

sub config_sh {
    substr $Config_SH_expanded, 1, $config_sh_len;
}

sub config_re {
    my $re = shift;
    return map { chomp; $_ } grep eval{ /^(?:$re)=/ }, split /^/,
    $Config_SH_expanded;
}

sub config_vars {
    # implements -V:cfgvar option (see perlrun -V:)
    foreach (@_) {
	# find optional leading, trailing colons; and query-spec
	my ($notag,$qry,$lncont) = m/^(:)?(.*?)(:)?$/;	# flags fore and aft, 
	# map colon-flags to print decorations
	my $prfx = $notag ? '': "$qry=";		# tag-prefix for print
	my $lnend = $lncont ? ' ' : ";\n";		# line ending for print

	# all config-vars are by definition \w only, any \W means regex
	if ($qry =~ /\W/) {
	    my @matches = config_re($qry);
	    print map "$_$lnend", @matches ? @matches : "$qry: not found"		if !$notag;
	    print map { s/\w+=//; "$_$lnend" } @matches ? @matches : "$qry: not found"	if  $notag;
	} else {
	    my $v = (exists $Config::Config{$qry}) ? $Config::Config{$qry}
						   : 'UNKNOWN';
	    $v = 'undef' unless defined $v;
	    print "${prfx}'${v}'$lnend";
	}
    }
}

# Called by the real AUTOLOAD
sub launcher {
    undef &AUTOLOAD;
    goto \&$Config::AUTOLOAD;
}

1;
