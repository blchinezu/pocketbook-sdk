#ifndef _IP_CONNTRACK_TUPLE_H
#define _IP_CONNTRACK_TUPLE_H

#include <linux/types.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>

/* A `tuple' is a structure containing the information to uniquely
  identify a connection.  ie. if two packets have the same tuple, they
  are in the same connection; if not, they are not.

  We divide the structure along "manipulatable" and
  "non-manipulatable" lines, for the benefit of the NAT code.
*/

/* The protocol-specific manipulable parts of the tuple: always in
   network order! */
union ip_conntrack_manip_proto
{
	/* Add other protocols here. */
	u_int16_t all;

	struct {
		__be16 port;
	} tcp;
	struct {
		__be16 port;
	} udp;
	struct {
		__be16 id;
	} icmp;
	struct {
		__be16 port;
	} sctp;
	struct {
		__be16 key;	/* key is 32bit, pptp only uses 16 */
	} gre;
};

/* The manipulable part of the tuple. */
struct ip_conntrack_manip
{
	__be32 ip;
	union ip_conntrack_manip_proto u;
};

/* This contains the information to distinguish a connection. */
struct ip_conntrack_tuple
{
	struct ip_conntrack_manip src;

	/* These are the parts of the tuple which are fixed. */
	struct {
		__be32 ip;
		union {
			/* Add other protocols here. */
			u_int16_t all;

			struct {
				__be16 port;
			} tcp;
			struct {
				__be16 port;
			} udp;
			struct {
				u_int8_t type, code;
			} icmp;
			struct {
				__be16 port;
			} sctp;
			struct {
				__be16 key;	/* key is 32bit, 
						 * pptp only uses 16 */
			} gre;
		} u;

		/* The protocol. */
		u_int8_t protonum;

		/* The direction (for tuplehash) */
		u_int8_t dir;
	} dst;
};

/* This is optimized opposed to a memset of the whole structure.  Everything we
 * really care about is the  source/destination unions */
#define IP_CT_TUPLE_U_BLANK(tuple) 				\
	do {							\
		(tuple)->src.u.all = 0;				\
		(tuple)->dst.u.all = 0;				\
	} while (0)


static __inline__ int ip_ct_tuple_src_equal(const struct ip_conntrack_tuple *t1,
				        const struct ip_conntrack_tuple *t2)
{
	return t1->src.ip == t2->src.ip
		&& t1->src.u.all == t2->src.u.all;
}

static __inline__ int ip_ct_tuple_dst_equal(const struct ip_conntrack_tuple *t1,
				        const struct ip_conntrack_tuple *t2)
{
	return t1->dst.ip == t2->dst.ip
		&& t1->dst.u.all == t2->dst.u.all
		&& t1->dst.protonum == t2->dst.protonum;
}

static __inline__ int ip_ct_tuple_equal(const struct ip_conntrack_tuple *t1,
				    const struct ip_conntrack_tuple *t2)
{
	return ip_ct_tuple_src_equal(t1, t2) && ip_ct_tuple_dst_equal(t1, t2);
}

static __inline__ int ip_ct_tuple_mask_cmp(const struct ip_conntrack_tuple *t,
				       const struct ip_conntrack_tuple *tuple,
				       const struct ip_conntrack_tuple *mask)
{
	return !(((t->src.ip ^ tuple->src.ip) & mask->src.ip)
		 || ((t->dst.ip ^ tuple->dst.ip) & mask->dst.ip)
		 || ((t->src.u.all ^ tuple->src.u.all) & mask->src.u.all)
		 || ((t->dst.u.all ^ tuple->dst.u.all) & mask->dst.u.all)
		 || ((t->dst.protonum ^ tuple->dst.protonum)
		     & mask->dst.protonum));
}

#endif /* _IP_CONNTRACK_TUPLE_H */
