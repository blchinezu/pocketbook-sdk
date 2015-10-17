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

#ifndef QHASH_H
#define QHASH_H

#include <QtCore/qchar.h>
#include <QtCore/qiterator.h>
#include <QtCore/qlist.h>
#include <QtCore/qpair.h>
#include <QtCore/qrefcount.h>

#ifdef Q_COMPILER_INITIALIZER_LISTS
#include <initializer_list>
#endif

#if defined(Q_CC_MSVC)
#pragma warning( push )
#pragma warning( disable : 4311 ) // disable pointer truncation warning
#pragma warning( disable : 4127 ) // conditional expression is constant
#endif

QT_BEGIN_NAMESPACE

class QBitArray;
class QByteArray;
class QString;
class QStringRef;
class QLatin1String;

inline uint qHash(char key, uint seed = 0) Q_DECL_NOTHROW { return uint(key) ^ seed; }
inline uint qHash(uchar key, uint seed = 0) Q_DECL_NOTHROW { return uint(key) ^ seed; }
inline uint qHash(signed char key, uint seed = 0) Q_DECL_NOTHROW { return uint(key) ^ seed; }
inline uint qHash(ushort key, uint seed = 0) Q_DECL_NOTHROW { return uint(key) ^ seed; }
inline uint qHash(short key, uint seed = 0) Q_DECL_NOTHROW { return uint(key) ^ seed; }
inline uint qHash(uint key, uint seed = 0) Q_DECL_NOTHROW { return key ^ seed; }
inline uint qHash(int key, uint seed = 0) Q_DECL_NOTHROW { return uint(key) ^ seed; }
inline uint qHash(ulong key, uint seed = 0) Q_DECL_NOTHROW
{
    if (sizeof(ulong) > sizeof(uint)) {
        return uint(((key >> (8 * sizeof(uint) - 1)) ^ key) & (~0U)) ^ seed;
    } else {
        return uint(key & (~0U)) ^ seed;
    }
}
inline uint qHash(long key, uint seed = 0) Q_DECL_NOTHROW { return qHash(ulong(key), seed); }
inline uint qHash(quint64 key, uint seed = 0) Q_DECL_NOTHROW
{
    if (sizeof(quint64) > sizeof(uint)) {
        return uint(((key >> (8 * sizeof(uint) - 1)) ^ key) & (~0U)) ^ seed;
    } else {
        return uint(key & (~0U)) ^ seed;
    }
}
inline uint qHash(qint64 key, uint seed = 0) Q_DECL_NOTHROW { return qHash(quint64(key), seed); }
Q_CORE_EXPORT uint qHash(float key, uint seed = 0) Q_DECL_NOTHROW;
Q_CORE_EXPORT uint qHash(double key, uint seed = 0) Q_DECL_NOTHROW;
#ifndef Q_OS_DARWIN
Q_CORE_EXPORT uint qHash(long double key, uint seed = 0) Q_DECL_NOTHROW;
#endif
inline uint qHash(QChar key, uint seed = 0) Q_DECL_NOTHROW { return qHash(key.unicode(), seed); }
Q_CORE_EXPORT uint qHash(const QByteArray &key, uint seed = 0) Q_DECL_NOTHROW;
Q_CORE_EXPORT uint qHash(const QString &key, uint seed = 0) Q_DECL_NOTHROW;
Q_CORE_EXPORT uint qHash(const QStringRef &key, uint seed = 0) Q_DECL_NOTHROW;
Q_CORE_EXPORT uint qHash(const QBitArray &key, uint seed = 0) Q_DECL_NOTHROW;
Q_CORE_EXPORT uint qHash(QLatin1String key, uint seed = 0) Q_DECL_NOTHROW;
Q_CORE_EXPORT uint qt_hash(const QString &key) Q_DECL_NOTHROW;
Q_CORE_EXPORT uint qt_hash(const QStringRef &key) Q_DECL_NOTHROW;

template <class T> inline uint qHash(const T *key, uint seed = 0) Q_DECL_NOTHROW
{
    return qHash(reinterpret_cast<quintptr>(key), seed);
}
template<typename T> inline uint qHash(const T &t, uint seed)
    Q_DECL_NOEXCEPT_EXPR(noexcept(qHash(t)))
{ return (qHash(t) ^ seed); }

template <typename T1, typename T2> inline uint qHash(const QPair<T1, T2> &key, uint seed = 0)
    Q_DECL_NOEXCEPT_EXPR(noexcept(qHash(key.first, seed)) && noexcept(qHash(key.second, seed)))
{
    uint h1 = qHash(key.first, seed);
    uint h2 = qHash(key.second, seed);
    return ((h1 << 16) | (h1 >> 16)) ^ h2 ^ seed;
}

struct Q_CORE_EXPORT QHashData
{
    struct Node {
        Node *next;
        uint h;
    };

    Node *fakeNext;
    Node **buckets;
    QtPrivate::RefCount ref;
    int size;
    int nodeSize;
    short userNumBits;
    short numBits;
    int numBuckets;
    uint seed;
    uint sharable : 1;
    uint strictAlignment : 1;
    uint reserved : 30;

    void *allocateNode(int nodeAlign);
    void freeNode(void *node);
    QHashData *detach_helper(void (*node_duplicate)(Node *, void *), void (*node_delete)(Node *),
                             int nodeSize, int nodeAlign);
    bool willGrow();
    void hasShrunk();
    void rehash(int hint);
    void free_helper(void (*node_delete)(Node *));
    Node *firstNode();
#ifdef QT_QHASH_DEBUG
    void dump();
    void checkSanity();
#endif
    static Node *nextNode(Node *node);
    static Node *previousNode(Node *node);

    static const QHashData shared_null;
};

inline bool QHashData::willGrow()
{
    if (size >= numBuckets) {
        rehash(numBits + 1);
        return true;
    } else {
        return false;
    }
}

inline void QHashData::hasShrunk()
{
    if (size <= (numBuckets >> 3) && numBits > userNumBits) {
        QT_TRY {
            rehash(qMax(int(numBits) - 2, int(userNumBits)));
        } QT_CATCH(const std::bad_alloc &) {
            // ignore bad allocs - shrinking shouldn't throw. rehash is exception safe.
        }
    }
}

inline QHashData::Node *QHashData::firstNode()
{
    Node *e = reinterpret_cast<Node *>(this);
    Node **bucket = buckets;
    int n = numBuckets;
    while (n--) {
        if (*bucket != e)
            return *bucket;
        ++bucket;
    }
    return e;
}

struct QHashDummyValue
{
};

inline bool operator==(const QHashDummyValue & /* v1 */, const QHashDummyValue & /* v2 */)
{
    return true;
}

Q_DECLARE_TYPEINFO(QHashDummyValue, Q_MOVABLE_TYPE | Q_DUMMY_TYPE);

template <class Key, class T>
struct QHashNode
{
    QHashNode *next;
    const uint h;
    const Key key;
    T value;

    inline QHashNode(const Key &key0, const T &value0, uint hash, QHashNode *n)
        : next(n), h(hash), key(key0), value(value0) {}
    inline bool same_key(uint h0, const Key &key0) const { return h0 == h && key0 == key; }

private:
    Q_DISABLE_COPY(QHashNode)
};

template <class Key, class T>
struct QHashDummyNode
{
    QHashNode<Key, T> *next;
    const uint h;
    const Key key;

    inline QHashDummyNode(const Key &key0, uint hash, QHashNode<Key, T> *n) : next(n), h(hash), key(key0) {}

private:
    Q_DISABLE_COPY(QHashDummyNode)
};


#if 0
// ###
// The introduction of the QHash random seed breaks this optimization, as it
// relies on qHash(int i) = i. If the hash value is salted, then the hash
// table becomes corrupted.
//
// A bit more research about whether it makes sense or not to salt integer
// keys (and in general keys whose hash value is easy to invert)
// is needed, or about how keep this optimization and the seed (f.i. by
// specializing QHash for integer values, and re-apply the seed during lookup).
//
// Be aware that such changes can easily be binary incompatible, and therefore
// cannot be made during the Qt 5 lifetime.
#define Q_HASH_DECLARE_INT_NODES(key_type) \
    template <class T> \
    struct QHashDummyNode<key_type, T> { \
        QHashDummyNode *next; \
        union { uint h; key_type key; }; \
\
        inline QHashDummyNode(key_type /* key0 */) {} \
    }; \
\
    template <class T> \
    struct QHashNode<key_type, T> { \
        QHashNode *next; \
        union { uint h; key_type key; }; \
        T value; \
\
        inline QHashNode(key_type /* key0 */) {} \
        inline QHashNode(key_type /* key0 */, const T &value0) : value(value0) {} \
        inline bool same_key(uint h0, key_type) const { return h0 == h; } \
    }

#if defined(Q_BYTE_ORDER) && Q_BYTE_ORDER == Q_LITTLE_ENDIAN
Q_HASH_DECLARE_INT_NODES(short);
Q_HASH_DECLARE_INT_NODES(ushort);
#endif
Q_HASH_DECLARE_INT_NODES(int);
Q_HASH_DECLARE_INT_NODES(uint);
#undef Q_HASH_DECLARE_INT_NODES
#endif // #if 0

template <class Key, class T>
class QHash
{
    typedef QHashDummyNode<Key, T> DummyNode;
    typedef QHashNode<Key, T> Node;

    union {
        QHashData *d;
        QHashNode<Key, T> *e;
    };

    static inline Node *concrete(QHashData::Node *node) {
        return reinterpret_cast<Node *>(node);
    }

    static inline int alignOfNode() { return qMax<int>(sizeof(void*), Q_ALIGNOF(Node)); }
    static inline int alignOfDummyNode() { return qMax<int>(sizeof(void*), Q_ALIGNOF(DummyNode)); }

public:
    inline QHash() : d(const_cast<QHashData *>(&QHashData::shared_null)) { }
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QHash(std::initializer_list<std::pair<Key,T> > list)
        : d(const_cast<QHashData *>(&QHashData::shared_null))
    {
        reserve(list.size());
        for (typename std::initializer_list<std::pair<Key,T> >::const_iterator it = list.begin(); it != list.end(); ++it)
            insert(it->first, it->second);
    }
#endif
    inline QHash(const QHash<Key, T> &other) : d(other.d) { d->ref.ref(); if (!d->sharable) detach(); }
    inline ~QHash() { if (!d->ref.deref()) freeData(d); }

    QHash<Key, T> &operator=(const QHash<Key, T> &other);
#ifdef Q_COMPILER_RVALUE_REFS
    inline QHash(QHash<Key, T> &&other) : d(other.d) { other.d = const_cast<QHashData *>(&QHashData::shared_null); }
    inline QHash<Key, T> &operator=(QHash<Key, T> &&other)
    { qSwap(d, other.d); return *this; }
#endif
    inline void swap(QHash<Key, T> &other) { qSwap(d, other.d); }

    bool operator==(const QHash<Key, T> &other) const;
    inline bool operator!=(const QHash<Key, T> &other) const { return !(*this == other); }

    inline int size() const { return d->size; }

    inline bool isEmpty() const { return d->size == 0; }

    inline int capacity() const { return d->numBuckets; }
    void reserve(int size);
    inline void squeeze() { reserve(1); }

    inline void detach() { if (d->ref.isShared()) detach_helper(); }
    inline bool isDetached() const { return !d->ref.isShared(); }
#if QT_SUPPORTS(UNSHARABLE_CONTAINERS)
    inline void setSharable(bool sharable) { if (!sharable) detach(); if (d != &QHashData::shared_null) d->sharable = sharable; }
#endif
    inline bool isSharedWith(const QHash<Key, T> &other) const { return d == other.d; }

    void clear();

    int remove(const Key &key);
    T take(const Key &key);

    bool contains(const Key &key) const;
    const Key key(const T &value) const;
    const Key key(const T &value, const Key &defaultKey) const;
    const T value(const Key &key) const;
    const T value(const Key &key, const T &defaultValue) const;
    T &operator[](const Key &key);
    const T operator[](const Key &key) const;

    QList<Key> uniqueKeys() const;
    QList<Key> keys() const;
    QList<Key> keys(const T &value) const;
    QList<T> values() const;
    QList<T> values(const Key &key) const;
    int count(const Key &key) const;

    class const_iterator;

    class iterator
    {
        friend class const_iterator;
        friend class QHash<Key, T>;
        QHashData::Node *i;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;

        inline iterator() : i(0) { }
        explicit inline iterator(void *node) : i(reinterpret_cast<QHashData::Node *>(node)) { }

        inline const Key &key() const { return concrete(i)->key; }
        inline T &value() const { return concrete(i)->value; }
        inline T &operator*() const { return concrete(i)->value; }
        inline T *operator->() const { return &concrete(i)->value; }
        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }

        inline iterator &operator++() {
            i = QHashData::nextNode(i);
            return *this;
        }
        inline iterator operator++(int) {
            iterator r = *this;
            i = QHashData::nextNode(i);
            return r;
        }
        inline iterator &operator--() {
            i = QHashData::previousNode(i);
            return *this;
        }
        inline iterator operator--(int) {
            iterator r = *this;
            i = QHashData::previousNode(i);
            return r;
        }
        inline iterator operator+(int j) const
        { iterator r = *this; if (j > 0) while (j--) ++r; else while (j++) --r; return r; }
        inline iterator operator-(int j) const { return operator+(-j); }
        inline iterator &operator+=(int j) { return *this = *this + j; }
        inline iterator &operator-=(int j) { return *this = *this - j; }

#ifndef QT_STRICT_ITERATORS
    public:
        inline bool operator==(const const_iterator &o) const
            { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const
            { return i != o.i; }
#endif
    };
    friend class iterator;

    class const_iterator
    {
        friend class iterator;
        QHashData::Node *i;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;

        inline const_iterator() : i(0) { }
        explicit inline const_iterator(void *node)
            : i(reinterpret_cast<QHashData::Node *>(node)) { }
#ifdef QT_STRICT_ITERATORS
        explicit inline const_iterator(const iterator &o)
#else
        inline const_iterator(const iterator &o)
#endif
        { i = o.i; }

        inline const Key &key() const { return concrete(i)->key; }
        inline const T &value() const { return concrete(i)->value; }
        inline const T &operator*() const { return concrete(i)->value; }
        inline const T *operator->() const { return &concrete(i)->value; }
        inline bool operator==(const const_iterator &o) const { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const { return i != o.i; }

        inline const_iterator &operator++() {
            i = QHashData::nextNode(i);
            return *this;
        }
        inline const_iterator operator++(int) {
            const_iterator r = *this;
            i = QHashData::nextNode(i);
            return r;
        }
        inline const_iterator &operator--() {
            i = QHashData::previousNode(i);
            return *this;
        }
        inline const_iterator operator--(int) {
            const_iterator r = *this;
            i = QHashData::previousNode(i);
            return r;
        }
        inline const_iterator operator+(int j) const
        { const_iterator r = *this; if (j > 0) while (j--) ++r; else while (j++) --r; return r; }
        inline const_iterator operator-(int j) const { return operator+(-j); }
        inline const_iterator &operator+=(int j) { return *this = *this + j; }
        inline const_iterator &operator-=(int j) { return *this = *this - j; }

        // ### Qt 5: not sure this is necessary anymore
#ifdef QT_STRICT_ITERATORS
    private:
        inline bool operator==(const iterator &o) const { return operator==(const_iterator(o)); }
        inline bool operator!=(const iterator &o) const { return operator!=(const_iterator(o)); }
#endif
    };
    friend class const_iterator;

    // STL style
    inline iterator begin() { detach(); return iterator(d->firstNode()); }
    inline const_iterator begin() const { return const_iterator(d->firstNode()); }
    inline const_iterator cbegin() const { return const_iterator(d->firstNode()); }
    inline const_iterator constBegin() const { return const_iterator(d->firstNode()); }
    inline iterator end() { detach(); return iterator(e); }
    inline const_iterator end() const { return const_iterator(e); }
    inline const_iterator cend() const { return const_iterator(e); }
    inline const_iterator constEnd() const { return const_iterator(e); }
    iterator erase(iterator it);

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    inline int count() const { return d->size; }
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
    const_iterator constFind(const Key &key) const;
    iterator insert(const Key &key, const T &value);
    iterator insertMulti(const Key &key, const T &value);
    QHash<Key, T> &unite(const QHash<Key, T> &other);

    // STL compatibility
    typedef T mapped_type;
    typedef Key key_type;
    typedef qptrdiff difference_type;
    typedef int size_type;

    inline bool empty() const { return isEmpty(); }

#ifdef QT_QHASH_DEBUG
    inline void dump() const { d->dump(); }
    inline void checkSanity() const { d->checkSanity(); }
#endif

private:
    void detach_helper();
    void freeData(QHashData *d);
    Node **findNode(const Key &key, uint *hp = 0) const;
    Node *createNode(uint h, const Key &key, const T &value, Node **nextNode);
    void deleteNode(Node *node);
    static void deleteNode2(QHashData::Node *node);

    static void duplicateNode(QHashData::Node *originalNode, void *newNode);

    bool isValidIterator(const iterator &it) const
    {
#if defined(QT_DEBUG) && !defined(Q_HASH_NO_ITERATOR_DEBUG)
        QHashData::Node *node = it.i;
        while (node->next)
            node = node->next;
        return (static_cast<void *>(node) == d);
#else
        Q_UNUSED(it);
        return true;
#endif
    }
    friend class QSet<Key>;
};


template <class Key, class T>
Q_INLINE_TEMPLATE void QHash<Key, T>::deleteNode(Node *node)
{
    deleteNode2(reinterpret_cast<QHashData::Node*>(node));
    d->freeNode(node);
}

template <class Key, class T>
Q_INLINE_TEMPLATE void QHash<Key, T>::deleteNode2(QHashData::Node *node)
{
#ifdef Q_CC_BOR
    concrete(node)->~QHashNode<Key, T>();
#else
    concrete(node)->~Node();
#endif
}

template <class Key, class T>
Q_INLINE_TEMPLATE void QHash<Key, T>::duplicateNode(QHashData::Node *node, void *newNode)
{
    Node *concreteNode = concrete(node);
    if (QTypeInfo<T>::isDummy) {
        (void) new (newNode) DummyNode(concreteNode->key, concreteNode->h, 0);
    } else {
        (void) new (newNode) Node(concreteNode->key, concreteNode->value, concreteNode->h, 0);
    }
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QHash<Key, T>::Node *
QHash<Key, T>::createNode(uint ah, const Key &akey, const T &avalue, Node **anextNode)
{
    Node *node;

    if (QTypeInfo<T>::isDummy) {
        node = reinterpret_cast<Node *>(new (d->allocateNode(alignOfDummyNode())) DummyNode(akey, ah, *anextNode));
    } else {
        node = new (d->allocateNode(alignOfNode())) Node(akey, avalue, ah, *anextNode);
    }

    *anextNode = node;
    ++d->size;
    return node;
}

template <class Key, class T>
Q_INLINE_TEMPLATE QHash<Key, T> &QHash<Key, T>::unite(const QHash<Key, T> &other)
{
    QHash<Key, T> copy(other);
    const_iterator it = copy.constEnd();
    while (it != copy.constBegin()) {
        --it;
        insertMulti(it.key(), it.value());
    }
    return *this;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE void QHash<Key, T>::freeData(QHashData *x)
{
    x->free_helper(deleteNode2);
}

template <class Key, class T>
Q_INLINE_TEMPLATE void QHash<Key, T>::clear()
{
    *this = QHash<Key,T>();
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE void QHash<Key, T>::detach_helper()
{
    QHashData *x = d->detach_helper(duplicateNode, deleteNode2,
        QTypeInfo<T>::isDummy ? sizeof(DummyNode) : sizeof(Node),
        QTypeInfo<T>::isDummy ? alignOfDummyNode() : alignOfNode());
    if (!d->ref.deref())
        freeData(d);
    d = x;
}

template <class Key, class T>
Q_INLINE_TEMPLATE QHash<Key, T> &QHash<Key, T>::operator=(const QHash<Key, T> &other)
{
    if (d != other.d) {
        QHashData *o = other.d;
        o->ref.ref();
        if (!d->ref.deref())
            freeData(d);
        d = o;
        if (!d->sharable)
            detach_helper();
    }
    return *this;
}

template <class Key, class T>
Q_INLINE_TEMPLATE const T QHash<Key, T>::value(const Key &akey) const
{
    Node *node;
    if (d->size == 0 || (node = *findNode(akey)) == e) {
        return T();
    } else {
        return node->value;
    }
}

template <class Key, class T>
Q_INLINE_TEMPLATE const T QHash<Key, T>::value(const Key &akey, const T &adefaultValue) const
{
    Node *node;
    if (d->size == 0 || (node = *findNode(akey)) == e) {
        return adefaultValue;
    } else {
        return node->value;
    }
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QHash<Key, T>::uniqueKeys() const
{
    QList<Key> res;
    res.reserve(size()); // May be too much, but assume short lifetime
    const_iterator i = begin();
    if (i != end()) {
        for (;;) {
            const Key &aKey = i.key();
            res.append(aKey);
            do {
                if (++i == end())
                    goto break_out_of_outer_loop;
            } while (aKey == i.key());
        }
    }
break_out_of_outer_loop:
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QHash<Key, T>::keys() const
{
    QList<Key> res;
    res.reserve(size());
    const_iterator i = begin();
    while (i != end()) {
        res.append(i.key());
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<Key> QHash<Key, T>::keys(const T &avalue) const
{
    QList<Key> res;
    const_iterator i = begin();
    while (i != end()) {
        if (i.value() == avalue)
            res.append(i.key());
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE const Key QHash<Key, T>::key(const T &avalue) const
{
    return key(avalue, Key());
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE const Key QHash<Key, T>::key(const T &avalue, const Key &defaultValue) const
{
    const_iterator i = begin();
    while (i != end()) {
        if (i.value() == avalue)
            return i.key();
        ++i;
    }

    return defaultValue;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<T> QHash<Key, T>::values() const
{
    QList<T> res;
    res.reserve(size());
    const_iterator i = begin();
    while (i != end()) {
        res.append(i.value());
        ++i;
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE QList<T> QHash<Key, T>::values(const Key &akey) const
{
    QList<T> res;
    Node *node = *findNode(akey);
    if (node != e) {
        do {
            res.append(node->value);
        } while ((node = node->next) != e && node->key == akey);
    }
    return res;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE int QHash<Key, T>::count(const Key &akey) const
{
    int cnt = 0;
    Node *node = *findNode(akey);
    if (node != e) {
        do {
            ++cnt;
        } while ((node = node->next) != e && node->key == akey);
    }
    return cnt;
}

template <class Key, class T>
Q_INLINE_TEMPLATE const T QHash<Key, T>::operator[](const Key &akey) const
{
    return value(akey);
}

template <class Key, class T>
Q_INLINE_TEMPLATE T &QHash<Key, T>::operator[](const Key &akey)
{
    detach();

    uint h;
    Node **node = findNode(akey, &h);
    if (*node == e) {
        if (d->willGrow())
            node = findNode(akey, &h);
        return createNode(h, akey, T(), node)->value;
    }
    return (*node)->value;
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QHash<Key, T>::iterator QHash<Key, T>::insert(const Key &akey,
                                                                         const T &avalue)
{
    detach();

    uint h;
    Node **node = findNode(akey, &h);
    if (*node == e) {
        if (d->willGrow())
            node = findNode(akey, &h);
        return iterator(createNode(h, akey, avalue, node));
    }

    if (!QTypeInfo<T>::isDummy)
        (*node)->value = avalue;
    return iterator(*node);
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QHash<Key, T>::iterator QHash<Key, T>::insertMulti(const Key &akey,
                                                                              const T &avalue)
{
    detach();
    d->willGrow();

    uint h;
    Node **nextNode = findNode(akey, &h);
    return iterator(createNode(h, akey, avalue, nextNode));
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE int QHash<Key, T>::remove(const Key &akey)
{
    if (isEmpty()) // prevents detaching shared null
        return 0;
    detach();

    int oldSize = d->size;
    Node **node = findNode(akey);
    if (*node != e) {
        bool deleteNext = true;
        do {
            Node *next = (*node)->next;
            deleteNext = (next != e && next->key == (*node)->key);
            deleteNode(*node);
            *node = next;
            --d->size;
        } while (deleteNext);
        d->hasShrunk();
    }
    return oldSize - d->size;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE T QHash<Key, T>::take(const Key &akey)
{
    if (isEmpty()) // prevents detaching shared null
        return T();
    detach();

    Node **node = findNode(akey);
    if (*node != e) {
        T t = (*node)->value;
        Node *next = (*node)->next;
        deleteNode(*node);
        *node = next;
        --d->size;
        d->hasShrunk();
        return t;
    }
    return T();
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE typename QHash<Key, T>::iterator QHash<Key, T>::erase(iterator it)
{
    Q_ASSERT_X(isValidIterator(it), "QHash::erase", "The specified iterator argument 'it' is invalid");

    if (it == iterator(e))
        return it;

    if (d->ref.isShared()) {
        int bucketNum = (it.i->h % d->numBuckets);
        iterator bucketIterator(*(d->buckets + bucketNum));
        int stepsFromBucketStartToIte = 0;
        while (bucketIterator != it) {
            ++stepsFromBucketStartToIte;
            ++bucketIterator;
        }
        detach();
        it = iterator(*(d->buckets + bucketNum));
        while (stepsFromBucketStartToIte > 0) {
            --stepsFromBucketStartToIte;
            ++it;
        }
    }

    iterator ret = it;
    ++ret;

    Node *node = concrete(it.i);
    Node **node_ptr = reinterpret_cast<Node **>(&d->buckets[node->h % d->numBuckets]);
    while (*node_ptr != node)
        node_ptr = &(*node_ptr)->next;
    *node_ptr = node->next;
    deleteNode(node);
    --d->size;
    return ret;
}

template <class Key, class T>
Q_INLINE_TEMPLATE void QHash<Key, T>::reserve(int asize)
{
    detach();
    d->rehash(-qMax(asize, 1));
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QHash<Key, T>::const_iterator QHash<Key, T>::find(const Key &akey) const
{
    return const_iterator(*findNode(akey));
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QHash<Key, T>::const_iterator QHash<Key, T>::constFind(const Key &akey) const
{
    return const_iterator(*findNode(akey));
}

template <class Key, class T>
Q_INLINE_TEMPLATE typename QHash<Key, T>::iterator QHash<Key, T>::find(const Key &akey)
{
    detach();
    return iterator(*findNode(akey));
}

template <class Key, class T>
Q_INLINE_TEMPLATE bool QHash<Key, T>::contains(const Key &akey) const
{
    return *findNode(akey) != e;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE typename QHash<Key, T>::Node **QHash<Key, T>::findNode(const Key &akey,
                                                                            uint *ahp) const
{
    Node **node;
    uint h = 0;

    if (d->numBuckets || ahp) {
        h = qHash(akey, d->seed);
        if (ahp)
            *ahp = h;
    }
    if (d->numBuckets) {
        node = reinterpret_cast<Node **>(&d->buckets[h % d->numBuckets]);
        Q_ASSERT(*node == e || (*node)->next);
        while (*node != e && !(*node)->same_key(h, akey))
            node = &(*node)->next;
    } else {
        node = const_cast<Node **>(reinterpret_cast<const Node * const *>(&e));
    }
    return node;
}

template <class Key, class T>
Q_OUTOFLINE_TEMPLATE bool QHash<Key, T>::operator==(const QHash<Key, T> &other) const
{
    if (size() != other.size())
        return false;
    if (d == other.d)
        return true;

    const_iterator it = begin();

    while (it != end()) {
        const Key &akey = it.key();

        const_iterator it2 = other.find(akey);
        do {
            if (it2 == other.end() || !(it2.key() == akey))
                return false;
            if (!QTypeInfo<T>::isDummy && !(it.value() == it2.value()))
                return false;
            ++it;
            ++it2;
        } while (it != end() && it.key() == akey);
    }
    return true;
}

template <class Key, class T>
class QMultiHash : public QHash<Key, T>
{
public:
    QMultiHash() {}
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QMultiHash(std::initializer_list<std::pair<Key,T> > list)
    {
        this->reserve(list.size());
        for (typename std::initializer_list<std::pair<Key,T> >::const_iterator it = list.begin(); it != list.end(); ++it)
            insert(it->first, it->second);
    }
#endif
    QMultiHash(const QHash<Key, T> &other) : QHash<Key, T>(other) {}
    inline void swap(QMultiHash<Key, T> &other) { QHash<Key, T>::swap(other); } // prevent QMultiHash<->QHash swaps

    inline typename QHash<Key, T>::iterator replace(const Key &key, const T &value)
    { return QHash<Key, T>::insert(key, value); }

    inline typename QHash<Key, T>::iterator insert(const Key &key, const T &value)
    { return QHash<Key, T>::insertMulti(key, value); }

    inline QMultiHash &operator+=(const QMultiHash &other)
    { this->unite(other); return *this; }
    inline QMultiHash operator+(const QMultiHash &other) const
    { QMultiHash result = *this; result += other; return result; }

#if !defined(Q_NO_USING_KEYWORD) && !defined(Q_CC_RVCT)
    // RVCT compiler doesn't handle using-keyword right when used functions are overloaded in child class
    using QHash<Key, T>::contains;
    using QHash<Key, T>::remove;
    using QHash<Key, T>::count;
    using QHash<Key, T>::find;
    using QHash<Key, T>::constFind;
#else
    inline bool contains(const Key &key) const
    { return QHash<Key, T>::contains(key); }
    inline int remove(const Key &key)
    { return QHash<Key, T>::remove(key); }
    inline int count(const Key &key) const
    { return QHash<Key, T>::count(key); }
    inline int count() const
    { return QHash<Key, T>::count(); }
    inline typename QHash<Key, T>::iterator find(const Key &key)
    { return QHash<Key, T>::find(key); }
    inline typename QHash<Key, T>::const_iterator find(const Key &key) const
    { return QHash<Key, T>::find(key); }
    inline typename QHash<Key, T>::const_iterator constFind(const Key &key) const
    { return QHash<Key, T>::constFind(key); }
#endif

    bool contains(const Key &key, const T &value) const;

    int remove(const Key &key, const T &value);

    int count(const Key &key, const T &value) const;

    typename QHash<Key, T>::iterator find(const Key &key, const T &value) {
        typename QHash<Key, T>::iterator i(find(key));
        typename QHash<Key, T>::iterator end(this->end());
        while (i != end && i.key() == key) {
            if (i.value() == value)
                return i;
            ++i;
        }
        return end;
    }
    typename QHash<Key, T>::const_iterator find(const Key &key, const T &value) const {
        typename QHash<Key, T>::const_iterator i(constFind(key));
        typename QHash<Key, T>::const_iterator end(QHash<Key, T>::constEnd());
        while (i != end && i.key() == key) {
            if (i.value() == value)
                return i;
            ++i;
        }
        return end;
    }
    typename QHash<Key, T>::const_iterator constFind(const Key &key, const T &value) const
        { return find(key, value); }
private:
    T &operator[](const Key &key);
    const T operator[](const Key &key) const;
};

template <class Key, class T>
Q_INLINE_TEMPLATE bool QMultiHash<Key, T>::contains(const Key &key, const T &value) const
{
    return constFind(key, value) != QHash<Key, T>::constEnd();
}

template <class Key, class T>
Q_INLINE_TEMPLATE int QMultiHash<Key, T>::remove(const Key &key, const T &value)
{
    int n = 0;
    typename QHash<Key, T>::iterator i(find(key));
    typename QHash<Key, T>::iterator end(QHash<Key, T>::end());
    while (i != end && i.key() == key) {
        if (i.value() == value) {
            i = this->erase(i);
            ++n;
        } else {
            ++i;
        }
    }
    return n;
}

template <class Key, class T>
Q_INLINE_TEMPLATE int QMultiHash<Key, T>::count(const Key &key, const T &value) const
{
    int n = 0;
    typename QHash<Key, T>::const_iterator i(constFind(key));
    typename QHash<Key, T>::const_iterator end(QHash<Key, T>::constEnd());
    while (i != end && i.key() == key) {
        if (i.value() == value)
            ++n;
        ++i;
    }
    return n;
}

Q_DECLARE_ASSOCIATIVE_ITERATOR(Hash)
Q_DECLARE_MUTABLE_ASSOCIATIVE_ITERATOR(Hash)

QT_END_NAMESPACE

#if defined(Q_CC_MSVC)
#pragma warning( pop )
#endif

#endif // QHASH_H
