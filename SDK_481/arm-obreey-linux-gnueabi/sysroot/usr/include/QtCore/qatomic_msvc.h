/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QATOMIC_MSVC_H
#define QATOMIC_MSVC_H

#include <QtCore/qgenericatomic.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef Q_OS_WINCE

// use compiler intrinsics for all atomic functions
# define QT_INTERLOCKED_PREFIX _
# define QT_INTERLOCKED_PROTOTYPE __cdecl
# define QT_INTERLOCKED_DECLARE_PROTOTYPES
# define QT_INTERLOCKED_INTRINSIC
# define Q_ATOMIC_INT16_IS_SUPPORTED

# ifdef _WIN64
#  define Q_ATOMIC_INT64_IS_SUPPORTED
# endif

#else // Q_OS_WINCE

# if _WIN32_WCE < 0x600 && defined(_X86_)
// For X86 Windows CE, include winbase.h to catch inline functions which
// override the regular definitions inside of coredll.dll.
// Though one could use the original version of Increment/Decrement, others are
// not exported at all.
#  include <winbase.h>

// It's safer to remove the volatile and let the compiler add it as needed.
#  define QT_INTERLOCKED_VOLATILE

# else // _WIN32_WCE >= 0x600 || !_X86_

#  define QT_INTERLOCKED_PROTOTYPE __cdecl
#  define QT_INTERLOCKED_DECLARE_PROTOTYPES

#  if _WIN32_WCE >= 0x600
#   if defined(_X86_)
#    define QT_INTERLOCKED_PREFIX _
#    define QT_INTERLOCKED_INTRINSIC
#   endif
#  else
#   define QT_INTERLOCKED_VOLATILE
#  endif

# endif // _WIN32_WCE >= 0x600 || !_X86_

#endif // Q_OS_WINCE

////////////////////////////////////////////////////////////////////////////////////////////////////
// Prototype declaration

#define QT_INTERLOCKED_CONCAT_I(prefix, suffix) \
    prefix ## suffix
#define QT_INTERLOCKED_CONCAT(prefix, suffix) \
    QT_INTERLOCKED_CONCAT_I(prefix, suffix)

// MSVC intrinsics prefix function names with an underscore. Also, if platform
// SDK headers have been included, the Interlocked names may be defined as
// macros.
// To avoid double underscores, we paste the prefix with Interlocked first and
// then the remainder of the function name.
#define QT_INTERLOCKED_FUNCTION(name) \
    QT_INTERLOCKED_CONCAT( \
        QT_INTERLOCKED_CONCAT(QT_INTERLOCKED_PREFIX, Interlocked), name)

#ifndef QT_INTERLOCKED_VOLATILE
# define QT_INTERLOCKED_VOLATILE volatile
#endif

#ifndef QT_INTERLOCKED_PREFIX
#define QT_INTERLOCKED_PREFIX
#endif

#ifndef QT_INTERLOCKED_PROTOTYPE
#define QT_INTERLOCKED_PROTOTYPE
#endif

#ifdef QT_INTERLOCKED_DECLARE_PROTOTYPES
#undef QT_INTERLOCKED_DECLARE_PROTOTYPES

extern "C" {

    long QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Increment )(long QT_INTERLOCKED_VOLATILE *);
    long QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Decrement )(long QT_INTERLOCKED_VOLATILE *);
    long QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( CompareExchange )(long QT_INTERLOCKED_VOLATILE *, long, long);
    long QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Exchange )(long QT_INTERLOCKED_VOLATILE *, long);
    long QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( ExchangeAdd )(long QT_INTERLOCKED_VOLATILE *, long);

# if !defined(Q_OS_WINCE) && !defined(__i386__) && !defined(_M_IX86)
    void * QT_INTERLOCKED_FUNCTION( CompareExchangePointer )(void * QT_INTERLOCKED_VOLATILE *, void *, void *);
    void * QT_INTERLOCKED_FUNCTION( ExchangePointer )(void * QT_INTERLOCKED_VOLATILE *, void *);
    __int64 QT_INTERLOCKED_FUNCTION( ExchangeAdd64 )(__int64 QT_INTERLOCKED_VOLATILE *, __int64);
# endif

# ifdef Q_ATOMIC_INT16_IS_SUPPORTED
    short QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Increment16 )(short QT_INTERLOCKED_VOLATILE *);
    short QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Decrement16 )(short QT_INTERLOCKED_VOLATILE *);
    short QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( CompareExchange16 )(short QT_INTERLOCKED_VOLATILE *, short, short);
    short QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Exchange16 )(short QT_INTERLOCKED_VOLATILE *, short);
    short QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( ExchangeAdd16 )(short QT_INTERLOCKED_VOLATILE *, short);
# endif
# ifdef Q_ATOMIC_INT64_IS_SUPPORTED
    __int64 QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Increment64 )(__int64 QT_INTERLOCKED_VOLATILE *);
    __int64 QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Decrement64 )(__int64 QT_INTERLOCKED_VOLATILE *);
    __int64 QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( CompareExchange64 )(__int64 QT_INTERLOCKED_VOLATILE *, __int64, __int64);
    __int64 QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( Exchange64 )(__int64 QT_INTERLOCKED_VOLATILE *, __int64);
    //above already: qint64 QT_INTERLOCKED_PROTOTYPE QT_INTERLOCKED_FUNCTION( ExchangeAdd64 )(qint64 QT_INTERLOCKED_VOLATILE *, qint64);
# endif
}

#endif // QT_INTERLOCKED_DECLARE_PROTOTYPES

#undef QT_INTERLOCKED_PROTOTYPE

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef QT_INTERLOCKED_INTRINSIC
#undef QT_INTERLOCKED_INTRINSIC

# pragma intrinsic (_InterlockedIncrement)
# pragma intrinsic (_InterlockedDecrement)
# pragma intrinsic (_InterlockedExchange)
# pragma intrinsic (_InterlockedCompareExchange)
# pragma intrinsic (_InterlockedExchangeAdd)

# if !defined(Q_OS_WINCE) && !defined(_M_IX86)
#  pragma intrinsic (_InterlockedCompareExchangePointer)
#  pragma intrinsic (_InterlockedExchangePointer)
#  pragma intrinsic (_InterlockedExchangeAdd64)
# endif

#endif // QT_INTERLOCKED_INTRINSIC

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interlocked* replacement macros

#if defined(Q_OS_WINCE) || defined(__i386__) || defined(_M_IX86)

# define QT_INTERLOCKED_COMPARE_EXCHANGE_POINTER(value, newValue, expectedValue) \
    reinterpret_cast<void *>( \
        QT_INTERLOCKED_FUNCTION(CompareExchange)( \
                reinterpret_cast<long QT_INTERLOCKED_VOLATILE *>(value), \
                long(newValue), \
                long(expectedValue)))

# define QT_INTERLOCKED_EXCHANGE_POINTER(value, newValue) \
    QT_INTERLOCKED_FUNCTION(Exchange)( \
            reinterpret_cast<long QT_INTERLOCKED_VOLATILE *>(value), \
            long(newValue))

# define QT_INTERLOCKED_EXCHANGE_ADD_POINTER(value, valueToAdd) \
    QT_INTERLOCKED_FUNCTION(ExchangeAdd)( \
            reinterpret_cast<long QT_INTERLOCKED_VOLATILE *>(value), \
            (valueToAdd))

#else // !defined(Q_OS_WINCE) && !defined(__i386__) && !defined(_M_IX86)

# define QT_INTERLOCKED_COMPARE_EXCHANGE_POINTER(value, newValue, expectedValue) \
    QT_INTERLOCKED_FUNCTION(CompareExchangePointer)( \
            (void * QT_INTERLOCKED_VOLATILE *)(value), \
            (void *) (newValue), \
            (void *) (expectedValue))

# define QT_INTERLOCKED_EXCHANGE_POINTER(value, newValue) \
    QT_INTERLOCKED_FUNCTION(ExchangePointer)( \
            (void * QT_INTERLOCKED_VOLATILE *)(value), \
            (void *) (newValue))

# define QT_INTERLOCKED_EXCHANGE_ADD_POINTER(value, valueToAdd) \
    QT_INTERLOCKED_FUNCTION(ExchangeAdd64)( \
            reinterpret_cast<qint64 QT_INTERLOCKED_VOLATILE *>(value), \
            (valueToAdd))

#endif // !defined(Q_OS_WINCE) && !defined(__i386__) && !defined(_M_IX86)

////////////////////////////////////////////////////////////////////////////////////////////////////

QT_BEGIN_NAMESPACE

#if 0
// silence syncqt warnings
QT_END_NAMESPACE
#pragma qt_sync_skip_header_check
#pragma qt_sync_stop_processing
#endif

#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_WAIT_FREE

#define Q_ATOMIC_INT_TEST_AND_SET_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT_TEST_AND_SET_IS_WAIT_FREE

#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_WAIT_FREE

#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_WAIT_FREE

#define Q_ATOMIC_INT32_IS_SUPPORTED

#define Q_ATOMIC_INT32_REFERENCE_COUNTING_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT32_REFERENCE_COUNTING_IS_WAIT_FREE

#define Q_ATOMIC_INT32_TEST_AND_SET_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT32_TEST_AND_SET_IS_WAIT_FREE

#define Q_ATOMIC_INT32_FETCH_AND_STORE_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT32_FETCH_AND_STORE_IS_WAIT_FREE

#define Q_ATOMIC_INT32_FETCH_AND_ADD_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT32_FETCH_AND_ADD_IS_WAIT_FREE

#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_WAIT_FREE

#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_ALWAYS_NATIVE
#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_WAIT_FREE

#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_ALWAYS_NATIVE
#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_WAIT_FREE

#ifdef Q_ATOMIC_INT16_IS_SUPPORTED
# define Q_ATOMIC_INT16_REFERENCE_COUNTING_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT16_REFERENCE_COUNTING_IS_WAIT_FREE

# define Q_ATOMIC_INT16_TEST_AND_SET_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT16_TEST_AND_SET_IS_WAIT_FREE

# define Q_ATOMIC_INT16_FETCH_AND_STORE_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT16_FETCH_AND_STORE_IS_WAIT_FREE

# define Q_ATOMIC_INT16_FETCH_AND_ADD_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT16_FETCH_AND_ADD_IS_WAIT_FREE

template<> struct QAtomicOpsSupport<2> { enum { IsSupported = 1 }; };
#endif

#ifdef Q_ATOMIC_INT64_IS_SUPPORTED
# define Q_ATOMIC_INT64_REFERENCE_COUNTING_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT64_REFERENCE_COUNTING_IS_WAIT_FREE

# define Q_ATOMIC_INT64_TEST_AND_SET_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT64_TEST_AND_SET_IS_WAIT_FREE

# define Q_ATOMIC_INT64_FETCH_AND_STORE_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT64_FETCH_AND_STORE_IS_WAIT_FREE

# define Q_ATOMIC_INT64_FETCH_AND_ADD_IS_ALWAYS_NATIVE
# define Q_ATOMIC_INT64_FETCH_AND_ADD_IS_WAIT_FREE

template<> struct QAtomicOpsSupport<8> { enum { IsSupported = 1 }; };
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

template <int N> struct QAtomicWindowsType { typedef typename QIntegerForSize<N>::Signed Type; };
template <> struct QAtomicWindowsType<4> { typedef long Type; };


template <int N> struct QAtomicOpsBySize : QGenericAtomicOps<QAtomicOpsBySize<N> >
{
    static inline Q_DECL_CONSTEXPR bool isReferenceCountingNative() Q_DECL_NOTHROW { return true; }
    static inline Q_DECL_CONSTEXPR bool isReferenceCountingWaitFree() Q_DECL_NOTHROW { return true; }
    template <typename T> static bool ref(T &_q_value) Q_DECL_NOTHROW;
    template <typename T> static bool deref(T &_q_value) Q_DECL_NOTHROW;

    static inline Q_DECL_CONSTEXPR bool isTestAndSetNative() Q_DECL_NOTHROW { return true; }
    static inline Q_DECL_CONSTEXPR bool isTestAndSetWaitFree() Q_DECL_NOTHROW { return true; }
    template <typename T> static bool testAndSetRelaxed(T &_q_value, T expectedValue, T newValue) Q_DECL_NOTHROW;
    template <typename T>
    static bool testAndSetRelaxed(T &_q_value, T expectedValue, T newValue, T *currentValue) Q_DECL_NOTHROW;

    static inline Q_DECL_CONSTEXPR bool isFetchAndStoreNative() Q_DECL_NOTHROW { return true; }
    static inline Q_DECL_CONSTEXPR bool isFetchAndStoreWaitFree() Q_DECL_NOTHROW { return true; }
    template <typename T> static T fetchAndStoreRelaxed(T &_q_value, T newValue) Q_DECL_NOTHROW;

    static inline Q_DECL_CONSTEXPR bool isFetchAndAddNative() Q_DECL_NOTHROW { return true; }
    static inline Q_DECL_CONSTEXPR bool isFetchAndAddWaitFree() Q_DECL_NOTHROW { return true; }
    template <typename T> static T fetchAndAddRelaxed(T &_q_value, typename QAtomicAdditiveType<T>::AdditiveT valueToAdd) Q_DECL_NOTHROW;

private:
    typedef typename QAtomicWindowsType<N>::Type Type;
    template <typename T> static inline Type *atomic(T *t)
    { Q_STATIC_ASSERT(sizeof(T) == sizeof(Type)); return reinterpret_cast<Type *>(t); }
    template <typename T> static inline Type value(T t)
    { Q_STATIC_ASSERT(sizeof(T) == sizeof(Type)); return Type(t); }
};

template <typename T>
struct QAtomicOps : QAtomicOpsBySize<sizeof(T)>
{
    typedef T Type;
};

template<> template<typename T>
inline bool QAtomicOpsBySize<4>::ref(T &_q_value) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Increment)(atomic(&_q_value)) != 0;
}

template<> template<typename T>
inline bool QAtomicOpsBySize<4>::deref(T &_q_value) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Decrement)(atomic(&_q_value)) != 0;
}

template<> template<typename T>
inline bool QAtomicOpsBySize<4>::testAndSetRelaxed(T &_q_value, T expectedValue, T newValue) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(CompareExchange)(atomic(&_q_value), value(newValue), value(expectedValue)) == value(expectedValue);
}

template<> template <typename T>
inline bool QAtomicOpsBySize<4>::testAndSetRelaxed(T &_q_value, T expectedValue, T newValue, T *currentValue) Q_DECL_NOTHROW
{
    *currentValue = T(QT_INTERLOCKED_FUNCTION(CompareExchange)(atomic(&_q_value), newValue, expectedValue));
    return *currentValue == expectedValue;
}

template<> template<typename T>
inline T QAtomicOpsBySize<4>::fetchAndStoreRelaxed(T &_q_value, T newValue) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Exchange)(atomic(&_q_value), value(newValue));
}

template<> template<typename T>
inline T QAtomicOpsBySize<4>::fetchAndAddRelaxed(T &_q_value, typename QAtomicAdditiveType<T>::AdditiveT valueToAdd) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(ExchangeAdd)(atomic(&_q_value), value<T>(valueToAdd * QAtomicAdditiveType<T>::AddScale));
}

#ifdef Q_ATOMIC_INT16_IS_SUPPORTED
template<> template<typename T>
inline bool QAtomicOpsBySize<2>::ref(T &_q_value) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Increment16)(atomic(&_q_value)) != 0;
}

template<> template<typename T>
inline bool QAtomicOpsBySize<2>::deref(T &_q_value) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Decrement16)(atomic(&_q_value)) != 0;
}

template<> template<typename T>
inline bool QAtomicOpsBySize<2>::testAndSetRelaxed(T &_q_value, T expectedValue, T newValue) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(CompareExchange16)(atomic(&_q_value), value(newValue), value(expectedValue)) == value(expectedValue);
}

template<> template <typename T>
inline bool QAtomicOpsBySize<2>::testAndSetRelaxed(T &_q_value, T expectedValue, T newValue, T *currentValue) Q_DECL_NOTHROW
{
    *currentValue = T(QT_INTERLOCKED_FUNCTION(CompareExchange16)(atomic(&_q_value), newValue, expectedValue));
    return *currentValue == expectedValue;
}

template<> template<typename T>
inline T QAtomicOpsBySize<2>::fetchAndStoreRelaxed(T &_q_value, T newValue) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Exchange16)(atomic(&_q_value), value(newValue));
}

template<> template<typename T>
inline T QAtomicOpsBySize<2>::fetchAndAddRelaxed(T &_q_value, typename QAtomicAdditiveType<T>::AdditiveT valueToAdd) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(ExchangeAdd16)(atomic(&_q_value), value<T>(valueToAdd * QAtomicAdditiveType<T>::AddScale));
}
#endif

#ifdef Q_ATOMIC_INT64_IS_SUPPORTED
template<> template<typename T>
inline bool QAtomicOpsBySize<8>::ref(T &_q_value) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Increment64)(atomic(&_q_value)) != 0;
}

template<> template<typename T>
inline bool QAtomicOpsBySize<8>::deref(T &_q_value) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Decrement64)(atomic(&_q_value)) != 0;
}

template<> template<typename T>
inline bool QAtomicOpsBySize<8>::testAndSetRelaxed(T &_q_value, T expectedValue, T newValue) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(CompareExchange64)(atomic(&_q_value), value(newValue), value(expectedValue)) == value(expectedValue);
}

template<> template <typename T>
inline bool QAtomicOpsBySize<8>::testAndSetRelaxed(T &_q_value, T expectedValue, T newValue, T *currentValue) Q_DECL_NOTHROW
{
    *currentValue = T(QT_INTERLOCKED_FUNCTION(CompareExchange64)(atomic(&_q_value), newValue, expectedValue));
    return *currentValue == expectedValue;
}

template<> template<typename T>
inline T QAtomicOpsBySize<8>::fetchAndStoreRelaxed(T &_q_value, T newValue) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(Exchange64)(atomic(&_q_value), value(newValue));
}

template<> template<typename T>
inline T QAtomicOpsBySize<8>::fetchAndAddRelaxed(T &_q_value, typename QAtomicAdditiveType<T>::AdditiveT valueToAdd) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_FUNCTION(ExchangeAdd64)(atomic(&_q_value), value<T>(valueToAdd * QAtomicAdditiveType<T>::AddScale));
}
#endif

// Specialization for pointer types, since we have Interlocked*Pointer() variants in some configurations
template <typename T>
struct QAtomicOps<T *> : QGenericAtomicOps<QAtomicOps<T *> >
{
    typedef T *Type;

    static inline Q_DECL_CONSTEXPR bool isTestAndSetNative() Q_DECL_NOTHROW { return true; }
    static inline Q_DECL_CONSTEXPR bool isTestAndSetWaitFree() Q_DECL_NOTHROW { return true; }
    static bool testAndSetRelaxed(T *&_q_value, T *expectedValue, T *newValue) Q_DECL_NOTHROW;
    static bool testAndSetRelaxed(T *&_q_value, T *expectedValue, T *newValue, T **currentValue) Q_DECL_NOTHROW;

    static inline Q_DECL_CONSTEXPR bool isFetchAndStoreNative() Q_DECL_NOTHROW { return true; }
    static inline Q_DECL_CONSTEXPR bool isFetchAndStoreWaitFree() Q_DECL_NOTHROW { return true; }
    static T *fetchAndStoreRelaxed(T *&_q_value, T *newValue) Q_DECL_NOTHROW;

    static inline Q_DECL_CONSTEXPR bool isFetchAndAddNative() Q_DECL_NOTHROW { return true; }
    static inline Q_DECL_CONSTEXPR bool isFetchAndAddWaitFree() Q_DECL_NOTHROW { return true; }
    static T *fetchAndAddRelaxed(T *&_q_value, qptrdiff valueToAdd) Q_DECL_NOTHROW;
};

template <typename T>
inline bool QAtomicOps<T *>::testAndSetRelaxed(T *&_q_value, T *expectedValue, T *newValue) Q_DECL_NOTHROW
{
    return QT_INTERLOCKED_COMPARE_EXCHANGE_POINTER(&_q_value, newValue, expectedValue) == expectedValue;
}

template <typename T>
inline bool QAtomicOps<T *>::testAndSetRelaxed(T *&_q_value, T *expectedValue, T *newValue, T **currentValue) Q_DECL_NOTHROW
{
    *currentValue = reinterpret_cast<T *>(QT_INTERLOCKED_COMPARE_EXCHANGE_POINTER(&_q_value, newValue, expectedValue));
    return *currentValue == expectedValue;
}

template <typename T>
inline T *QAtomicOps<T *>::fetchAndStoreRelaxed(T *&_q_value, T *newValue) Q_DECL_NOTHROW
{
    return reinterpret_cast<T *>(QT_INTERLOCKED_EXCHANGE_POINTER(&_q_value, newValue));
}

template <typename T>
inline T *QAtomicOps<T *>::fetchAndAddRelaxed(T *&_q_value, qptrdiff valueToAdd) Q_DECL_NOTHROW
{
    return reinterpret_cast<T *>(QT_INTERLOCKED_EXCHANGE_ADD_POINTER(&_q_value, valueToAdd * sizeof(T)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Cleanup

#undef QT_INTERLOCKED_CONCAT_I
#undef QT_INTERLOCKED_CONCAT
#undef QT_INTERLOCKED_FUNCTION
#undef QT_INTERLOCKED_PREFIX

#undef QT_INTERLOCKED_VOLATILE

#undef QT_INTERLOCKED_INCREMENT
#undef QT_INTERLOCKED_DECREMENT
#undef QT_INTERLOCKED_COMPARE_EXCHANGE
#undef QT_INTERLOCKED_EXCHANGE
#undef QT_INTERLOCKED_EXCHANGE_ADD
#undef QT_INTERLOCKED_COMPARE_EXCHANGE_POINTER
#undef QT_INTERLOCKED_EXCHANGE_POINTER
#undef QT_INTERLOCKED_EXCHANGE_ADD_POINTER

QT_END_NAMESPACE
#endif // QATOMIC_MSVC_H
