#ifndef HEADER_WHRLPOOL_H
# define HEADER_WHRLPOOL_H

# include <openssl/e_os2.h>
# include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

# define WHIRLPOOL_DIGEST_LENGTH (512/8)
# define WHIRLPOOL_BBLOCK        512
# define WHIRLPOOL_COUNTER       (256/8)

typedef struct {
    union {
        unsigned char c[WHIRLPOOL_DIGEST_LENGTH];
        /* double q is here to ensure 64-bit alignment */
        double q[WHIRLPOOL_DIGEST_LENGTH / sizeof(double)];
    } H;
    unsigned char data[WHIRLPOOL_BBLOCK / 8];
    unsigned int bitoff;
    size_t bitlen[WHIRLPOOL_COUNTER / sizeof(size_t)];
} WHIRLPOOL_CTX;

# ifndef OPENSSL_NO_WHIRLPOOL
#  ifdef OPENSSL_FIPS
int private_WHIRLPOOL_Init(WHIRLPOOL_CTX *c);
#  endif
int WHIRLPOOL_Init(WHIRLPOOL_CTX *c);
int WHIRLPOOL_Update(WHIRLPOOL_CTX *c, const void *inp, size_t bytes);
void WHIRLPOOL_BitUpdate(WHIRLPOOL_CTX *c, const void *inp, size_t bits);
int WHIRLPOOL_Final(unsigned char *md, WHIRLPOOL_CTX *c);
unsigned char *WHIRLPOOL(const void *inp, size_t bytes, unsigned char *md);
# endif

#ifdef __cplusplus
}
#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/io-pkt/crypto/dist2/openssl/crypto/whrlpool/whrlpool.h $ $Rev: 798582 $")
#endif
