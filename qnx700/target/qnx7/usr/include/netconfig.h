/*	$NetBSD: netconfig.h,v 1.1 2000/06/02 22:57:54 fvdl Exp $	*/


#ifndef _NETCONFIG_H_
#define _NETCONFIG_H_

#include <sys/cdefs.h>

#define NETCONFIG	"/etc/netconfig"
#define NETPATH		"NETPATH"

struct netconfig {
	char *nc_netid;			/* Network ID */
	unsigned long nc_semantics;	/* Semantics (see below) */
	unsigned long nc_flag;		/* Flags (see below) */
	char *nc_protofmly;		/* Protocol family */
	char *nc_proto;			/* Protocol name */
	char *nc_device;		/* Network device pathname */
	unsigned long nc_nlookups;	/* Number of directory lookup libs */
	char **nc_lookups;		/* Names of the libraries */
	unsigned long nc_unused[9];	/* reserved */
};

typedef struct {
	struct netconfig **nc_head;
	struct netconfig **nc_curr;
} NCONF_HANDLE;

/*
 * nc_semantics values
 */
#define NC_TPI_CLTS	1
#define NC_TPI_COTS	2
#define NC_TPI_COTS_ORD	3
#define NC_TPI_RAW	4

/*
 * nc_flag values
 */
#define NC_NOFLAG	0x00
#define NC_VISIBLE	0x01
#define NC_BROADCAST	0x02

/*
 * nc_protofmly values
 */
#define NC_NOPROTOFMLY	"-"
#define NC_LOOPBACK	"loopback"
#define NC_INET		"inet"
#define NC_INET6	"inet6"
#define NC_IMPLINK	"implink"
#define NC_PUP		"pup"
#define NC_CHAOS	"chaos"
#define NC_NS		"ns"
#define NC_NBS		"nbs"
#define NC_ECMA		"ecma"
#define NC_DATAKIT	"datakit"
#define NC_CCITT	"ccitt"
#define NC_SNA		"sna"
#define NC_DECNET	"decnet"
#define NC_DLI		"dli"
#define NC_LAT		"lat"
#define NC_HYLINK	"hylink"
#define NC_APPLETALK	"appletalk"
#define NC_NIT		"nit"
#define NC_IEEE802	"ieee802"
#define NC_OSI		"osi"
#define NC_X25		"x25"
#define NC_OSINET	"osinet"
#define NC_GOSIP	"gosip"

/*
 * nc_proto values
 */
#define NC_NOPROTO	"-"
#define NC_TCP		"tcp"
#define NC_UDP		"udp"
#define NC_ICMP		"icmp"

__BEGIN_DECLS
void *setnetconfig __P((void));
struct netconfig *getnetconfig __P((void *));
struct netconfig *getnetconfigent __P((char *));
void freenetconfigent __P((struct netconfig *));
int endnetconfig __P((void *));

void *setnetpath __P((void));
struct netconfig *getnetpath __P((void *));
int endnetpath(void *);

void nc_perror __P((const char *));
char *nc_sperror __P((void));
__END_DECLS

#endif /* _NETCONFIG_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/rpc/public/netconfig.h $ $Rev: 680336 $")
#endif
