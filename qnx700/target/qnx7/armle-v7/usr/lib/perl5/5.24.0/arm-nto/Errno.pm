# -*- buffer-read-only: t -*-
#
# This file is auto-generated. ***ANY*** changes here will be lost
#

package Errno;
require Exporter;
use strict;

use Config;
"$Config{'archname'}-$Config{'osvers'}" eq
"arm-nto-current" or
	die "Errno architecture (arm-nto-current) does not match executable architecture ($Config{'archname'}-$Config{'osvers'})";

our $VERSION = "1.25";
$VERSION = eval $VERSION;
our @ISA = 'Exporter';

my %err;

BEGIN {
    %err = (
	EOK => 0,
	EPERM => 1,
	ENOENT => 2,
	ESRCH => 3,
	EINTR => 4,
	EIO => 5,
	ENXIO => 6,
	E2BIG => 7,
	ENOEXEC => 8,
	EBADF => 9,
	ECHILD => 10,
	EAGAIN => 11,
	EWOULDBLOCK => 11,
	ENOMEM => 12,
	EACCES => 13,
	EFAULT => 14,
	ENOTBLK => 15,
	EBUSY => 16,
	EEXIST => 17,
	EXDEV => 18,
	ENODEV => 19,
	ENOTDIR => 20,
	EISDIR => 21,
	EINVAL => 22,
	ENFILE => 23,
	EMFILE => 24,
	ENOTTY => 25,
	ETXTBSY => 26,
	EFBIG => 27,
	ENOSPC => 28,
	ESPIPE => 29,
	EROFS => 30,
	EMLINK => 31,
	EPIPE => 32,
	EDOM => 33,
	ERANGE => 34,
	ENOMSG => 35,
	EIDRM => 36,
	ECHRNG => 37,
	EL2NSYNC => 38,
	EL3HLT => 39,
	EL3RST => 40,
	ELNRNG => 41,
	EUNATCH => 42,
	ENOCSI => 43,
	EL2HLT => 44,
	EDEADLK => 45,
	ENOLCK => 46,
	ECANCELED => 47,
	ENOTSUP => 48,
	EDQUOT => 49,
	EBADE => 50,
	EBADR => 51,
	EXFULL => 52,
	ENOANO => 53,
	EBADRQC => 54,
	EBADSLT => 55,
	EDEADLOCK => 56,
	EBFONT => 57,
	EOWNERDEAD => 58,
	ENOSTR => 60,
	ENODATA => 61,
	ETIME => 62,
	ENOSR => 63,
	ENONET => 64,
	ENOPKG => 65,
	EREMOTE => 66,
	ENOLINK => 67,
	EADV => 68,
	ESRMNT => 69,
	ECOMM => 70,
	EPROTO => 71,
	EMULTIHOP => 74,
	EBADMSG => 77,
	ENAMETOOLONG => 78,
	EOVERFLOW => 79,
	ENOTUNIQ => 80,
	EBADFD => 81,
	EREMCHG => 82,
	ELIBACC => 83,
	ELIBBAD => 84,
	ELIBSCN => 85,
	ELIBMAX => 86,
	ELIBEXEC => 87,
	EILSEQ => 88,
	ENOSYS => 89,
	ELOOP => 90,
	ERESTART => 91,
	ESTRPIPE => 92,
	ENOTEMPTY => 93,
	EUSERS => 94,
	ENOTRECOVERABLE => 95,
	EOPNOTSUPP => 103,
	EFPOS => 110,
	ESTALE => 122,
	EINPROGRESS => 236,
	EALREADY => 237,
	ENOTSOCK => 238,
	EDESTADDRREQ => 239,
	EMSGSIZE => 240,
	EPROTOTYPE => 241,
	ENOPROTOOPT => 242,
	EPROTONOSUPPORT => 243,
	ESOCKTNOSUPPORT => 244,
	EPFNOSUPPORT => 246,
	EAFNOSUPPORT => 247,
	EADDRINUSE => 248,
	EADDRNOTAVAIL => 249,
	ENETDOWN => 250,
	ENETUNREACH => 251,
	ENETRESET => 252,
	ECONNABORTED => 253,
	ECONNRESET => 254,
	ENOBUFS => 255,
	EISCONN => 256,
	ENOTCONN => 257,
	ESHUTDOWN => 258,
	ETOOMANYREFS => 259,
	ETIMEDOUT => 260,
	ECONNREFUSED => 261,
	EHOSTDOWN => 264,
	EHOSTUNREACH => 265,
	EBADRPC => 272,
	ERPCMISMATCH => 273,
	EPROGUNAVAIL => 274,
	EPROGMISMATCH => 275,
	EPROCUNAVAIL => 276,
	ENOREMOTE => 300,
	ENONDP => 301,
	EBADFSYS => 302,
	EMORE => 309,
	ECTRLTERM => 310,
	ENOLIC => 311,
	ESRVRFAULT => 312,
	EENDIAN => 313,
	ESECTYPEINVAL => 314,
    );
    # Generate proxy constant subroutines for all the values.
    # Well, almost all the values. Unfortunately we can't assume that at this
    # point that our symbol table is empty, as code such as if the parser has
    # seen code such as C<exists &Errno::EINVAL>, it will have created the
    # typeglob.
    # Doing this before defining @EXPORT_OK etc means that even if a platform is
    # crazy enough to define EXPORT_OK as an error constant, everything will
    # still work, because the parser will upgrade the PCS to a real typeglob.
    # We rely on the subroutine definitions below to update the internal caches.
    # Don't use %each, as we don't want a copy of the value.
    foreach my $name (keys %err) {
        if ($Errno::{$name}) {
            # We expect this to be reached fairly rarely, so take an approach
            # which uses the least compile time effort in the common case:
            eval "sub $name() { $err{$name} }; 1" or die $@;
        } else {
            $Errno::{$name} = \$err{$name};
        }
    }
}

our @EXPORT_OK = keys %err;

our %EXPORT_TAGS = (
    POSIX => [qw(
	E2BIG EACCES EADDRINUSE EADDRNOTAVAIL EAFNOSUPPORT EAGAIN EALREADY
	EBADF EBUSY ECHILD ECONNABORTED ECONNREFUSED ECONNRESET EDEADLK
	EDESTADDRREQ EDOM EDQUOT EEXIST EFAULT EFBIG EHOSTDOWN EHOSTUNREACH
	EINPROGRESS EINTR EINVAL EIO EISCONN EISDIR ELOOP EMFILE EMLINK
	EMSGSIZE ENAMETOOLONG ENETDOWN ENETRESET ENETUNREACH ENFILE ENOBUFS
	ENODEV ENOENT ENOEXEC ENOLCK ENOMEM ENOPROTOOPT ENOSPC ENOSYS ENOTBLK
	ENOTCONN ENOTDIR ENOTEMPTY ENOTSOCK ENOTTY ENXIO EOPNOTSUPP EPERM
	EPFNOSUPPORT EPIPE EPROTONOSUPPORT EPROTOTYPE ERANGE EREMOTE ERESTART
	EROFS ESHUTDOWN ESOCKTNOSUPPORT ESPIPE ESRCH ESTALE ETIMEDOUT
	ETOOMANYREFS ETXTBSY EUSERS EWOULDBLOCK EXDEV
    )],
);

sub TIEHASH { bless \%err }

sub FETCH {
    my (undef, $errname) = @_;
    return "" unless exists $err{$errname};
    my $errno = $err{$errname};
    return $errno == $! ? $errno : 0;
}

sub STORE {
    require Carp;
    Carp::confess("ERRNO hash is read only!");
}

*CLEAR = *DELETE = \*STORE; # Typeglob aliasing uses less space

sub NEXTKEY {
    each %err;
}

sub FIRSTKEY {
    my $s = scalar keys %err;	# initialize iterator
    each %err;
}

sub EXISTS {
    my (undef, $errname) = @_;
    exists $err{$errname};
}

tie %!, __PACKAGE__; # Returns an object, objects are true.

__END__

=head1 NAME

Errno - System errno constants

=head1 SYNOPSIS

    use Errno qw(EINTR EIO :POSIX);

=head1 DESCRIPTION

C<Errno> defines and conditionally exports all the error constants
defined in your system F<errno.h> include file. It has a single export
tag, C<:POSIX>, which will export all POSIX defined error numbers.

On Windows, C<Errno> also defines and conditionally exports all the
Winsock error constants defined in your system F<WinError.h> include
file. These are included in a second export tag, C<:WINSOCK>.

C<Errno> also makes C<%!> magic such that each element of C<%!> has a
non-zero value only if C<$!> is set to that value. For example:

    use Errno;

    unless (open(FH, "/fangorn/spouse")) {
        if ($!{ENOENT}) {
            warn "Get a wife!\n";
        } else {
            warn "This path is barred: $!";
        } 
    } 

If a specified constant C<EFOO> does not exist on the system, C<$!{EFOO}>
returns C<"">.  You may use C<exists $!{EFOO}> to check whether the
constant is available on the system.

=head1 CAVEATS

Importing a particular constant may not be very portable, because the
import will fail on platforms that do not have that constant.  A more
portable way to set C<$!> to a valid value is to use:

    if (exists &Errno::EFOO) {
        $! = &Errno::EFOO;
    }

=head1 AUTHOR

Graham Barr <gbarr@pobox.com>

=head1 COPYRIGHT

Copyright (c) 1997-8 Graham Barr. All rights reserved.
This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut

# ex: set ro:
