/***************************************************************************
 *   Copyright (C) 2005 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PDF_OBJECT_H_
#define _PDF_OBJECT_H_

#include "PdfDefines.h"
#include "PdfName.h"
#include "PdfParser.h"
#include "PdfReference.h"
#include "PdfString.h"
#include "PdfVariant.h"

namespace PoDoFo {

class PdfEncrypt;
class PdfObject;
class PdfOutputDevice;
class PdfStream;
class PdfVecObjects;

/**
 * This class represents a PDF indirect Object in memory
 * 
 * It is possible to manipulate the stream which can be appended to the object
 * (if the object is of underlying type dictionary).  A PdfObject is uniquely
 * identified by an object number and a generation number which has to be
 * passed to the constructor.
 *
 * The object can be written to a file easily using the WriteObject() function.
 *
 * \see WriteObject()
 */
class PODOFO_API PdfObject : public PdfVariant {
    friend class PdfVecObjects;

 public:

    /** Create a PDF object with object and generation number -1
     *  and the value of being an empty PdfDictionary.
     */
    PdfObject();

    /** Construct a new PDF object of type PdfDictionary.
     *
     *  \param rRef reference of this object
     *  \param pszType if type is not null a key "/Type" will be added to the dictionary with
     *                 the value of type.
     */
    PdfObject( const PdfReference & rRef, const char* pszType);

    /** Construct a new PDF object.
     *  \param rRef reference of this object
     *  \param rVariant the value of the PdfObject (which is copied)
     */
    PdfObject( const PdfReference & rRef, const PdfVariant & rVariant );

    /** Create a PDF object with object and generation number -1
     *  and the value of the passed variant.
     *
     *  \param var the value of the object
     */
    PdfObject( const PdfVariant & var );

    /** Construct a PdfObject with object and generation number -1
     *  and a bool as value.
     *
     *  \param b the boolean value of this PdfObject
     */
    PdfObject( bool b );

    /** Construct a PdfObject with object and generation number -1
     *  and a pdf_int64 as value.
     *
     *  \param l the pdf_int64 value of this PdfObject
     */
    PdfObject( pdf_int64 l );

    /** Construct a PdfObject with object and generation number -1
     *  and a double as value.
     *
     *  \param d the double value of this PdfObject
     */
    PdfObject( double d );

    /** Construct a PdfObject with object and generation number -1
     *  and a PdfString as value.
     *
     *  \param rsString the string value of this PdfObject
     */        
    PdfObject( const PdfString & rsString );

    /** Construct a PdfObject with object and generation number -1
     *  and a PdfName as value.
     *
     *  \param rName the value of this PdfObject
     */        
    PdfObject( const PdfName & rName );

    /** Construct a PdfObject with object and generation number -1
     *  and a PdfReference as value.
     *
     *  \param rRef the value of the this PdfObject
     */        
    PdfObject( const PdfReference & rRef );

    /** Construct a PdfObject with object and generation number -1
     *  and a PdfArray as value.
     *
     *  \param tList the value of the this PdfObject
     */        
    PdfObject( const PdfArray & tList );

    /** Construct a PdfObject with object and generation number -1
     *  and a PdfDictionary as value.
     *
     *  \param rDict the value of the this PdfObject
     */        
    PdfObject( const PdfDictionary & rDict );

    /** Creates a copy of an existing PdfObject
     *  All assosiated objects and streams will be copied along with the PdfObject
     *  \param rhs PdfObject to clone
     */
    PdfObject( const PdfObject & rhs );

    virtual ~PdfObject();

    /** Get the keys value out of the dictionary. If the key is a reference, 
     *  the reference is resolved and the object pointed to by the reference is returned.
     *
     *  \param key look for the key named key in the dictionary
     * 
     *  \returns the found value or NULL if the value is not in the 
     *           dictionary or if this object is no dictionary
     */
    PdfObject* GetIndirectKey( const PdfName & key ) const;
    
    /**
     * MustGetIndirectKey() wraps GetIndirectKey to throw on null return.
     * This makes it MUCH more readable to look up deep chains of linked keys
     * with the cost that it's not easy to tell at which point a missing key/object
     * was encountered.
     *
     * \returns the found value, which is never null
     * \throws PdfError(ePdfError_NoObject) .
     */
    inline PdfObject* MustGetIndirectKey( const PdfName & key ) const;

    /** Write the complete object to a file.
     *  \param pDevice write the object to this device
     *  \param pEncrypt an encryption object which is used to encrypt this object
     *                  or NULL to not encrypt this object
     *  \param eWriteMode additional options for writing the object
     *  \param keyStop if not KeyNull and a key == keyStop is found
     *                 writing will stop right before this key!
     */
    void WriteObject( PdfOutputDevice* pDevice, EPdfWriteMode eWriteMode, PdfEncrypt* pEncrypt,
                      const PdfName & keyStop = PdfName::KeyNull ) const;

    /** Get the length of the object in bytes if it was written to disk now.
     *  \param eWriteMode additional options for writing the object
     *  \returns  the length of the object
     */
    pdf_long GetObjectLength( EPdfWriteMode eWriteMode );

    /** Get a indirect reference to this object
     *  \returns a PdfReference pointing to this object.
     */
    inline const PdfReference & Reference() const;

    /** Get a handle to a PDF stream object
     *  If the PDF object does not have a stream,
     *  one will be created.
     *  \returns a PdfStream object
     *
     *  This will set the dirty flag of this object.
     *  \see IsDirty
     */
    PdfStream* GetStream();

    /** Get a handle to a const PDF stream object
     *  If the PDF object does not have a stream,
     *  null is returned
     *  \returns a PdfStream object or null
     */
    const PdfStream* GetStream() const;

    /** Check if this object has a PdfStream object
     *  appended.
     * 
     *  \returns true if the object has a stream
     */
    inline bool HasStream() const;

    /** This operator is required for sorting a list of 
     *  PdfObjects. It compares the objectnumber. If objectnumbers
     *  are equal, the generation number is compared.
     */
    PODOFO_NOTHROW inline bool operator<( const PdfObject & rhs ) const;

    /** Comperasion operator.
     *  Compares two PDF object only based on their object and generation number
     */
    PODOFO_NOTHROW inline bool operator==( const PdfObject & rhs ) const;

    /** Set the owner of this object, i.e. the PdfVecObjects to which
     *  this object belongs.
     *
     *  \param pVecObjects a vector of pdf objects
     */
    inline void SetOwner( PdfVecObjects* pVecObjects );

    /** Get the owner of this object.
     *  \return the creator of this object
     */
    inline PdfVecObjects* GetOwner() const;

    /** Creates a copy of an existing PdfObject
     *  All assosiated objects and streams will be copied along with the PdfObject
     *  \param rhs PdfObject to clone
     *  \returns a reference to this object
     */
    const PdfObject & operator=( const PdfObject & rhs );

    /** This function compresses any currently set stream
     *  using the FlateDecode algorithm. JPEG compressed streams
     *  will not be compressed again using this function.
     *  Entries to the filter dictionary will be added if necessary.
     */
    void FlateCompressStream();

    /** Calculate the byte offset of the key pszKey from the start of the object
     *  if the object was written to disk at the moment of calling this function.
     *
     *  This function is very calculation intensive!
     *
     *  \param pszKey  key to calculate the byte offset
     *  \param eWriteMode additional options for writing the PDF
     *  \returns the offset of the key 
     */
    pdf_long GetByteOffset( const char* pszKey, EPdfWriteMode eWriteMode );

    /**
     * Dynamically load this object and any associated stream from a PDF file
     * by calling the virtual method DelayedStreamLoadImpl if the stream  is not
     * already loaded. Will call DelayedLoad() first if it is required.
     *
     * Call graph:
     *
     *    DelayedStreamLoad ---> DelayedLoad() --> DelayedLoadImpl()
     *                       |
     *                       --> DelayedStreamLoadImpl()
     *
     * For objects complete created in memory this function does nothing.
     */
    inline void DelayedStreamLoad() const;

 protected:
    /** Flag any stream associated with the object as incompletely loaded,
     *  so that DelayedStreamLoad() will be called when needed.
     *
     *  All constructors initialize a PdfObject with delayed loading of streams
     *  disabled .  If you want delayed loading of streams you must ask for it.
     *  If you do so, call this method early in your ctor and be sure to
     *  override DelayedStreamLoadImpl()
     *
     *  Note that it is quite possible to have a PdfObject that requires a
     *  delayed-load of its stream but does an immediate load of the PdfVariant
     *  base. If you want to delay loading of that too, make sure to call
     *  EnableDelayedLoading().
     */
    inline void EnableDelayedStreamLoading();

    /** Load the stream of the object if it has one and if delayed loading is enabled.
     *
     * You should override this to control deferred stream loading in your subclass.
     *
     * Never call this method directly; use DelayedStreamLoad() instead.
     */
    inline virtual void DelayedStreamLoadImpl();

    /** Same as GetStream() but won't trigger a delayed load, so it's safe
     *  for use while a delayed load is in progress.
     *
     *  This will set the dirty flag of this object.
     *  \see IsDirty
     */
    PdfStream* GetStream_NoDL();

 protected:
    PdfReference   m_reference;
    
    PdfStream*     m_pStream;
    PdfVecObjects* m_pOwner;

    PODOFO_NOTHROW inline bool DelayedStreamLoadDone() const;

 private:
    /* See PdfVariant.h for a detailed explanation of this member, which is
     * here to prevent accidental construction of a PdfObject of integer type
     * when passing a pointer. */
    template<typename T> PdfObject(T*);


    // Shared initialization between all the ctors
    void InitPdfObject();

    // No touchy. Only for manipulation by PdfObject private routines.
    // Tracks whether deferred loading is still pending (in which case it'll be
    // false). If true, deferred loading is not requried or has been completed.
    mutable bool m_bDelayedStreamLoadDone;

#if defined(PODOFO_EXTRA_CHECKS)
 protected:
    PODOFO_NOTHROW bool DelayedStreamLoadInProgress() const { return m_bDelayedStreamLoadInProgress; }
private:
    mutable bool m_bDelayedStreamLoadInProgress;
#endif
};

// -----------------------------------------------------
// 
// -----------------------------------------------------
bool PdfObject::DelayedStreamLoadDone() const
{
    return m_bDelayedStreamLoadDone;
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
void PdfObject::EnableDelayedStreamLoading()
{
    m_bDelayedStreamLoadDone = false;
}


// -----------------------------------------------------
// 
// -----------------------------------------------------
const PdfReference & PdfObject::Reference() const
{
    return m_reference;
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline void PdfObject::SetOwner( PdfVecObjects* pVecObjects )
{
    m_pOwner = pVecObjects;
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline PdfVecObjects* PdfObject::GetOwner() const
{
    return m_pOwner;
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
bool PdfObject::operator<( const PdfObject & rhs ) const
{
    return m_reference < rhs.m_reference;
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
bool PdfObject::operator==( const PdfObject & rhs ) const
{
    return (m_reference == rhs.m_reference);
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
inline bool PdfObject::HasStream() const
{
    DelayedStreamLoad();

    return ( m_pStream != NULL );
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
PdfObject* PdfObject::MustGetIndirectKey( const PdfName & key ) const
{
    PdfObject* obj = GetIndirectKey(key);
    if (!obj)
        PODOFO_RAISE_ERROR( ePdfError_NoObject );
    return obj;
}

// -----------------------------------------------------
// 
// -----------------------------------------------------
// Default implementation of virtual void DelayedStreamLoadImpl()
// throws, since delayed loading of steams should not be enabled
// except by types that support it.
inline void PdfObject::DelayedStreamLoadImpl()
{
   PODOFO_RAISE_ERROR( ePdfError_InternalLogic );
}

inline void PdfObject::DelayedStreamLoad() const
{
    DelayedLoad();

#if defined(PODOFO_EXTRA_CHECKS)
    if( m_bDelayedStreamLoadInProgress )
        PODOFO_RAISE_ERROR_INFO( ePdfError_InternalLogic, "Recursive DelayedStreamLoad() detected" );
#endif

    if( !m_bDelayedStreamLoadDone )
    {
#if defined(PODOFO_EXTRA_CHECKS)
        m_bDelayedStreamLoadInProgress = true;
#endif
        const_cast<PdfObject*>(this)->DelayedStreamLoadImpl();
        // Nothing was thrown, so if the implementer of DelayedstreamLoadImpl() is
        // following the rules we're done.
        m_bDelayedStreamLoadDone = true;
#if defined(PODOFO_EXTRA_CHECKS)
        m_bDelayedStreamLoadInProgress = false;
#endif
    }
}

};

#endif // _PDF_OBJECT_H_



