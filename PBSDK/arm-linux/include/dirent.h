/* Copyright (C) 1991-1999, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 *	POSIX Standard: 5.1.2 Directory Operations	<dirent.h>
 */

#ifndef	_DIRENT_H
#define	_DIRENT_H	1

#include <features.h>

__BEGIN_DECLS

#include <bits/types.h>

#ifdef __USE_XOPEN
# ifndef __ino_t_defined
#  ifndef __USE_FILE_OFFSET64
typedef __ino_t ino_t;
#  else
typedef __ino64_t ino_t;
#  endif
#  define __ino_t_defined
# endif
# if defined __USE_LARGEFILE64 && !defined __ino64_t_defined
typedef __ino64_t ino64_t;
#  define __ino64_t_defined
# endif
#endif

/* This file defines `struct dirent'.

   It defines the macro `_DIRENT_HAVE_D_NAMLEN' iff there is a `d_namlen'
   member that gives the length of `d_name'.

   It defines the macro `_DIRENT_HAVE_D_RECLEN' iff there is a `d_reclen'
   member that gives the size of the entire directory entry.

   It defines the macro `_DIRENT_HAVE_D_OFF' iff there is a `d_off'
   member that gives the file offset of the next directory entry.

   It defines the macro `_DIRENT_HAVE_D_TYPE' iff there is a `d_type'
   member that gives the type of the file.
 */

#include <bits/dirent.h>

#if (defined __USE_BSD || defined __USE_MISC) && !defined d_fileno
# define d_ino	d_fileno		 /* Backward compatibility.  */
#endif

/* These macros extract size information from a `struct dirent *'.
   They may evaluate their argument multiple times, so it must not
   have side effects.  Each of these may involve a relatively costly
   call to `strlen' on some systems, so these values should be cached.

   _D_EXACT_NAMLEN (DP)	returns the length of DP->d_name, not including
   its terminating null character.

   _D_ALLOC_NAMLEN (DP)	returns a size at least (_D_EXACT_NAMLEN (DP) + 1);
   that is, the allocation size needed to hold the DP->d_name string.
   Use this macro when you don't need the exact length, just an upper bound.
   This macro is less likely to require calling `strlen' than _D_EXACT_NAMLEN.
   */

#ifdef _DIRENT_HAVE_D_NAMLEN
# define _D_EXACT_NAMLEN(d) ((d)->d_namlen)
# define _D_ALLOC_NAMLEN(d) (_D_EXACT_NAMLEN (d) + 1)
#else
# define _D_EXACT_NAMLEN(d) (strlen ((d)->d_name))
# ifdef _DIRENT_HAVE_D_RECLEN
#  define _D_ALLOC_NAMLEN(d) (((char *) (d) + (d)->d_reclen) - &(d)->d_name[0])
# else
#  define _D_ALLOC_NAMLEN(d) (sizeof (d)->d_name > 1 ? sizeof (d)->d_name : \
			      _D_EXACT_NAMLEN (d) + 1)
# endif
#endif


#ifdef __USE_BSD
/* File types for `d_type'.  */
enum
  {
    DT_UNKNOWN = 0,
# define DT_UNKNOWN	DT_UNKNOWN
    DT_FIFO = 1,
# define DT_FIFO	DT_FIFO
    DT_CHR = 2,
# define DT_CHR		DT_CHR
    DT_DIR = 4,
# define DT_DIR		DT_DIR
    DT_BLK = 6,
# define DT_BLK		DT_BLK
    DT_REG = 8,
# define DT_REG		DT_REG
    DT_LNK = 10,
# define DT_LNK		DT_LNK
    DT_SOCK = 12,
# define DT_SOCK	DT_SOCK
    DT_WHT = 14
# define DT_WHT		DT_WHT
  };

/* Convert between stat structure types and directory types.  */
# define IFTODT(mode)	(((mode) & 0170000) >> 12)
# define DTTOIF(dirtype)	((dirtype) << 12)
#endif


/* This is the data type of directory stream objects.
   The actual structure is opaque to users.  */
typedef struct __dirstream DIR;

/* Open a directory stream on NAME.
   Return a DIR stream on the directory, or NULL if it could not be opened.  */
extern DIR *opendir (__const char *__name) __THROW;

/* Close the directory stream DIRP.
   Return 0 if successful, -1 if not.  */
extern int closedir (DIR *__dirp) __THROW;

/* Read a directory entry from DIRP.  Return a pointer to a `struct
   dirent' describing the entry, or NULL for EOF or error.  The
   storage returned may be overwritten by a later readdir call on the
   same DIR stream.

   If the Large File Support API is selected we have to use the
   appropriate interface.  */
#ifndef __USE_FILE_OFFSET64
extern struct dirent *readdir (DIR *__dirp) __THROW;
#else
# ifdef __REDIRECT
extern struct dirent *__REDIRECT (readdir, (DIR *__dirp) __THROW, readdir64);
# else
#  define readdir readdir64
# endif
#endif

#ifdef __USE_LARGEFILE64
extern struct dirent64 *readdir64 (DIR *__dirp) __THROW;
#endif

#if defined __USE_POSIX || defined __USE_MISC
/* Reentrant version of `readdir'.  Return in RESULT a pointer to the
   next entry.  */
# ifndef __USE_FILE_OFFSET64
extern int readdir_r (DIR *__restrict __dirp,
		      struct dirent *__restrict __entry,
		      struct dirent **__restrict __result) __THROW;
# else
#  ifdef __REDIRECT
extern int __REDIRECT (readdir_r,
		       (DIR *__restrict __dirp,
			struct dirent *__restrict __entry,
			struct dirent **__restrict __result) __THROW,
		       readdir64_r);
#  else
#   define readdir_r readdir64_r
#  endif
# endif

# ifdef __USE_LARGEFILE64
extern int readdir64_r (DIR *__restrict __dirp,
			struct dirent64 *__restrict __entry,
			struct dirent64 **__restrict __result) __THROW;
# endif
#endif	/* POSIX or misc */

/* Rewind DIRP to the beginning of the directory.  */
extern void rewinddir (DIR *__dirp) __THROW;

#if defined __USE_BSD || defined __USE_MISC || defined __USE_XOPEN
# include <bits/types.h>

/* Seek to position POS on DIRP.  */
extern void seekdir (DIR *__dirp, long int __pos) __THROW;

/* Return the current position of DIRP.  */
extern long int telldir (DIR *__dirp) __THROW;
#endif

#if defined __USE_BSD || defined __USE_MISC

/* Return the file descriptor used by DIRP.  */
extern int dirfd (DIR *__dirp) __THROW;

# if defined __OPTIMIZE__ && defined _DIR_dirfd
#  define dirfd(dirp)	_DIR_dirfd (dirp)
# endif

# ifndef MAXNAMLEN
/* Get the definitions of the POSIX.1 limits.  */
#  include <bits/posix1_lim.h>

/* `MAXNAMLEN' is the BSD name for what POSIX calls `NAME_MAX'.  */
#  ifdef NAME_MAX
#   define MAXNAMLEN	NAME_MAX
#  else
#   define MAXNAMLEN	255
#  endif
# endif

# define __need_size_t
# include <stddef.h>

/* Scan the directory DIR, calling SELECTOR on each directory entry.
   Entries for which SELECT returns nonzero are individually malloc'd,
   sorted using qsort with CMP, and collected in a malloc'd array in
   *NAMELIST.  Returns the number of entries selected, or -1 on error.  */
# ifndef __USE_FILE_OFFSET64
extern int scandir (__const char *__restrict __dir,
		    struct dirent ***__restrict __namelist,
		    int (*__selector) (__const struct dirent *),
		    int (*__cmp) (__const void *, __const void *)) __THROW;
# else
#  ifdef __REDIRECT
extern int __REDIRECT (scandir,
		       (__const char *__restrict __dir,
			struct dirent ***__restrict __namelist,
			int (*__selector) (__const struct dirent *),
			int (*__cmp) (__const void *, __const void *)) __THROW,
		       scandir64);
#  else
#   define scandir scandir64
#  endif
# endif

# if defined __USE_GNU && defined __USE_LARGEFILE64
/* This function is like `scandir' but it uses the 64bit dirent structure.
   Please note that the CMP function must now work with struct dirent64 **.  */
extern int scandir64 (__const char *__restrict __dir,
		      struct dirent64 ***__restrict __namelist,
		      int (*__selector) (__const struct dirent64 *),
		      int (*__cmp) (__const void *, __const void *)) __THROW;
# endif

/* Function to compare two `struct dirent's alphabetically.  */
# ifndef __USE_FILE_OFFSET64
extern int alphasort (__const void *__e1, __const void *__e2)
     __THROW __attribute_pure__;
# else
#  ifdef __REDIRECT
extern int __REDIRECT (alphasort,
		       (__const void *__e1, __const void *__e2)
		       __THROW,
		       alphasort64) __attribute_pure__;
#  else
#   define alphasort alphasort64
#  endif
# endif

# if defined __USE_GNU && defined __USE_LARGEFILE64
extern int alphasort64 (__const void *__e1, __const void *__e2)
     __THROW __attribute_pure__;
# endif

# ifdef __USE_GNU
/* Function to compare two `struct dirent's by name & version.  */
#  ifndef __USE_FILE_OFFSET64
extern int versionsort (__const void *__e1, __const void *__e2)
     __THROW __attribute_pure__;
#  else
#   ifdef __REDIRECT
extern int __REDIRECT (versionsort,
		       (__const void *__e1, __const void *__e2)
		       __THROW,
		       versionsort64) __attribute_pure__;
#   else
#    define versionsort versionsort64
#   endif
#  endif

#  ifdef __USE_LARGEFILE64
extern int versionsort64 (__const void *__e1, __const void *__e2)
     __THROW __attribute_pure__;
#  endif
# endif

/* Read directory entries from FD into BUF, reading at most NBYTES.
   Reading starts at offset *BASEP, and *BASEP is updated with the new
   position after reading.  Returns the number of bytes read; zero when at
   end of directory; or -1 for errors.  */
# ifndef __USE_FILE_OFFSET64
extern __ssize_t getdirentries (int __fd, char *__restrict __buf,
				size_t __nbytes,
				__off_t *__restrict __basep) __THROW;
# else
#  ifdef __REDIRECT
extern __ssize_t __REDIRECT (getdirentries,
			     (int __fd, char *__restrict __buf,
			      size_t __nbytes,
			      __off64_t *__restrict __basep) __THROW,
			     getdirentries64);
#  else
#   define getdirentries getdirentries64
#  endif
# endif

# ifdef __USE_LARGEFILE64
extern __ssize_t getdirentries64 (int __fd, char *__restrict __buf,
				  size_t __nbytes,
				  __off64_t *__restrict __basep) __THROW;
# endif

#endif /* Use BSD or misc.  */

__END_DECLS

#endif /* dirent.h  */
