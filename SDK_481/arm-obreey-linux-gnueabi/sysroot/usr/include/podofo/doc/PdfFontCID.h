/***************************************************************************
 *   Copyright (C) 2007 by Dominik Seichter                                *
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

#ifndef _PDF_FONT_CID_H_
#define _PDF_FONT_CID_H_

#include "podofo/base/PdfDefines.h"
#include "PdfFont.h"

namespace PoDoFo {

class PdfFontMetricsFreetype;

/** A PdfFont that represents a CID font.
 */
class PdfFontCID : public PdfFont {
 public:

    /** Create a new CID font. 
     * 
     *  \param pMetrics pointer to a font metrics object. The font in the PDF
     *         file will match this fontmetrics object. The metrics object is 
     *         deleted along with the font.
     *  \param pEncoding the encoding of this font. The font will take ownership of this object
     *                   depending on pEncoding->IsAutoDelete()
     *  \param pParent parent of the font object
     *  \param bEmbed specifies the embedding of font
     *  
     */
    PdfFontCID( PdfFontMetrics* pMetrics, const PdfEncoding* const pEncoding, 
                PdfVecObjects* pParent, bool bEmbed = true );

    // Peter Petrov 30 April 2008
    /** Create a PdfFont based on an existing PdfObject
     *  \param pMetrics pointer to a font metrics object. The font in the PDF
     *         file will match this fontmetrics object. The metrics object is 
     *         deleted along with the font.
     *  \param pEncoding the encoding of this font. The font will take ownership of this object
     *                   depending on pEncoding->IsAutoDelete()
     *  \param pObject an existing PdfObject
     *  \param bEmbed specifies the embedding of font
     */
    PdfFontCID( PdfFontMetrics* pMetrics, const PdfEncoding* const pEncoding, PdfObject* pObject, bool bEmbed );

    // Peter Petrov 24 September 2008
    /** Embeds the font into PDF page
     *
     */
    virtual void EmbedFont();

 private:
    /** Create the DW and W entries which contain
     *  all glyph width in the given font dictionary.
     *
     *  \param pFontDict a CID font dictionary
     */
    void CreateWidth( PdfObject* pFontDict ) const;

    /** Create a ToUnicode CMap and write it to the stream
     *  of the given object.
     *
     *  \param pUnicode the object which will contain the CMap
     */
    void CreateCMap( PdfObject* pUnicode ) const;

 protected:

    /** Initialize this font object.
     *
     *  \param bEmbed if true embed the font data into the PDF file.
     */
    void Init( bool bEmbed );


    /** Embed the font file directly into the PDF file.
     *
     *  \param pDescriptor font descriptor object
     */
    void EmbedFont( PdfObject* pDescriptor );

 protected:
    // Peter Petrov 24 September 2008
    PdfObject* m_pDescriptor;
};

};

#endif // _PDF_FONT_CID_H_

