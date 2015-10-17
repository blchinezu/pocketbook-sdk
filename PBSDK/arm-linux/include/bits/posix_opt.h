/* Define POSIX options for Linux.
   Copyright (C) 1996-2001, 2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef	_POSIX_OPT_H
#define	_POSIX_OPT_H	1

/* Job control is supported.  */
#define	_POSIX_JOB_CONTROL	1

/* Processes have a saved set-user-ID and a saved set-group-ID.  */
#define	_POSIX_SAVED_IDS	1

/* Priority scheduling is supported.  */
#define	_POSIX_PRIORITY_SCHEDULING	200112L

/* Synchronizing file data is supported.  */
#define	_POSIX_SYNCHRONIZED_IO	200112L

/* The fsync function is present.  */
#define	_POSIX_FSYNC	200112L

/* Mapping of files to memory is supported.  */
#define	_POSIX_MAPPED_FILES	200112L

/* Locking of all memory is supported.  */
#define	_POSIX_MEMLOCK	200112L

/* Locking of ranges of memory is supported.  */
#define	_POSIX_MEMLOCK_RANGE	200112L

/* Setting of memory protections is supported.  */
#define	_POSIX_MEMORY_PROTECTION	200112L

/* Only root can change owner of file.  */
#define	_POSIX_CHOWN_RESTRICTED	1

/* `c_cc' member of 'struct termios' structure can be disabled by
   using the value _POSIX_VDISABLE.  */
#define	_POSIX_VDISABLE	'\0'

/* Filenames are not silently truncated.  */
#define	_POSIX_NO_TRUNC	1

/* X/Open realtime support is available.  */
#define _XOPEN_REALTIME	1

/* X/Open realtime thread support is available.  */
#define _XOPEN_REALTIME_THREADS	1

/* XPG4.2 shared memory is supported.  */
#define	_XOPEN_SHM	1

/* Tell we have POSIX threads.  */
#define _POSIX_THREADS	200112L

/* We have the reentrant functions described in POSIX.  */
#define _POSIX_REENTRANT_FUNCTIONS      1
#define _POSIX_THREAD_SAFE_FUNCTIONS	200112L

/* We provide priority scheduling for threads.  */
#define	_POSIX_THREAD_PRIORITY_SCHEDULING	200112L

/* We support user-defined stack sizes.  */
#define _POSIX_THREAD_ATTR_STACKSIZE	200112L

/* We support user-defined stacks.  */
#define _POSIX_THREAD_ATTR_STACKADDR	200112L

/* We support POSIX.1b semaphores, but only the non-shared form for now.  */
#define _POSIX_SEMAPHORES	200112L

/* Real-time signals are supported.  */
#define _POSIX_REALTIME_SIGNALS	200112L

/* We support asynchronous I/O.  */
#define _POSIX_ASYNCHRONOUS_IO	200112L
#define _POSIX_ASYNC_IO		1
/* Alternative name for Unix98.  */
#define _LFS_ASYNCHRONOUS_IO	1

/* The LFS support in asynchronous I/O is also available.  */
#define _LFS64_ASYNCHRONOUS_IO	1

/* The rest of the LFS is also available.  */
#define _LFS_LARGEFILE		1
#define _LFS64_LARGEFILE	1
#define _LFS64_STDIO		1

/* POSIX shared memory objects are implemented.  */
#define _POSIX_SHARED_MEMORY_OBJECTS	200112L

/* GNU libc provides regular expression handling.  */
#define _POSIX_REGEXP	1

/* Reader/Writer locks are available.  */
#define _POSIX_READER_WRITER_LOCKS	200112L

/* We have a POSIX shell.  */
#define _POSIX_SHELL	1

/* We support the Timeouts option.  */
#define _POSIX_TIMEOUTS	200112L

/* We support spinlocks.  */
#define _POSIX_SPIN_LOCKS	200112L

/* The `spawn' function family is supported.  */
#define _POSIX_SPAWN	200112L

/* We have POSIX timers.  */
#define _POSIX_TIMERS	200112L

/* The barrier functions are available.  */
#define _POSIX_BARRIERS	200112L

/* POSIX message queues are not yet supported.  */
#undef	_POSIX_MESSAGE_PASSING

#endif /* posix_opt.h */
