/*
 *  include/linux/nfs4.h
 *
 *  NFSv4 protocol definitions.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andros@umich.edu>
 */

#ifndef _LINUX_NFS4_H
#define _LINUX_NFS4_H

#include <linux/types.h>

#define NFS4_VERIFIER_SIZE	8
#define NFS4_FHSIZE		128
#define NFS4_MAXPATHLEN		PATH_MAX
#define NFS4_MAXNAMLEN		NAME_MAX

#define NFS4_ACCESS_READ        0x0001
#define NFS4_ACCESS_LOOKUP      0x0002
#define NFS4_ACCESS_MODIFY      0x0004
#define NFS4_ACCESS_EXTEND      0x0008
#define NFS4_ACCESS_DELETE      0x0010
#define NFS4_ACCESS_EXECUTE     0x0020

#define NFS4_FH_PERSISTENT		0x0000
#define NFS4_FH_NOEXPIRE_WITH_OPEN	0x0001
#define NFS4_FH_VOLATILE_ANY		0x0002
#define NFS4_FH_VOL_MIGRATION		0x0004
#define NFS4_FH_VOL_RENAME		0x0008

#define NFS4_OPEN_RESULT_CONFIRM 0x0002
#define NFS4_OPEN_RESULT_LOCKTYPE_POSIX 0x0004

#define NFS4_SHARE_ACCESS_READ	0x0001
#define NFS4_SHARE_ACCESS_WRITE	0x0002
#define NFS4_SHARE_ACCESS_BOTH	0x0003
#define NFS4_SHARE_DENY_READ	0x0001
#define NFS4_SHARE_DENY_WRITE	0x0002
#define NFS4_SHARE_DENY_BOTH	0x0003

#define NFS4_SET_TO_SERVER_TIME	0
#define NFS4_SET_TO_CLIENT_TIME	1

#define NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE 0
#define NFS4_ACE_ACCESS_DENIED_ACE_TYPE  1
#define NFS4_ACE_SYSTEM_AUDIT_ACE_TYPE   2
#define NFS4_ACE_SYSTEM_ALARM_ACE_TYPE   3

#define ACL4_SUPPORT_ALLOW_ACL 0x01
#define ACL4_SUPPORT_DENY_ACL  0x02
#define ACL4_SUPPORT_AUDIT_ACL 0x04
#define ACL4_SUPPORT_ALARM_ACL 0x08

#define NFS4_ACE_FILE_INHERIT_ACE             0x00000001
#define NFS4_ACE_DIRECTORY_INHERIT_ACE        0x00000002
#define NFS4_ACE_NO_PROPAGATE_INHERIT_ACE     0x00000004
#define NFS4_ACE_INHERIT_ONLY_ACE             0x00000008
#define NFS4_ACE_SUCCESSFUL_ACCESS_ACE_FLAG   0x00000010
#define NFS4_ACE_FAILED_ACCESS_ACE_FLAG       0x00000020
#define NFS4_ACE_IDENTIFIER_GROUP             0x00000040
#define NFS4_ACE_OWNER                        0x00000080
#define NFS4_ACE_GROUP                        0x00000100
#define NFS4_ACE_EVERYONE                     0x00000200

#define NFS4_ACE_READ_DATA                    0x00000001
#define NFS4_ACE_LIST_DIRECTORY               0x00000001
#define NFS4_ACE_WRITE_DATA                   0x00000002
#define NFS4_ACE_ADD_FILE                     0x00000002
#define NFS4_ACE_APPEND_DATA                  0x00000004
#define NFS4_ACE_ADD_SUBDIRECTORY             0x00000004
#define NFS4_ACE_READ_NAMED_ATTRS             0x00000008
#define NFS4_ACE_WRITE_NAMED_ATTRS            0x00000010
#define NFS4_ACE_EXECUTE                      0x00000020
#define NFS4_ACE_DELETE_CHILD                 0x00000040
#define NFS4_ACE_READ_ATTRIBUTES              0x00000080
#define NFS4_ACE_WRITE_ATTRIBUTES             0x00000100
#define NFS4_ACE_DELETE                       0x00010000
#define NFS4_ACE_READ_ACL                     0x00020000
#define NFS4_ACE_WRITE_ACL                    0x00040000
#define NFS4_ACE_WRITE_OWNER                  0x00080000
#define NFS4_ACE_SYNCHRONIZE                  0x00100000
#define NFS4_ACE_GENERIC_READ                 0x00120081
#define NFS4_ACE_GENERIC_WRITE                0x00160106
#define NFS4_ACE_GENERIC_EXECUTE              0x001200A0
#define NFS4_ACE_MASK_ALL                     0x001F01FF

enum nfs4_acl_whotype {
	NFS4_ACL_WHO_NAMED = 0,
	NFS4_ACL_WHO_OWNER,
	NFS4_ACL_WHO_GROUP,
	NFS4_ACL_WHO_EVERYONE,
};

#endif

/*
 * Local variables:
 *  c-basic-offset: 8
 * End:
 */
