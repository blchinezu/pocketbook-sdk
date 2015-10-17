#pragma once

class PBScreenBuffer
{
    unsigned char *m_src;
    int m_format;
    int m_sw;
    int m_sh;
    int m_scanline;
    bool m_empty;
    bool m_nBar;
public:
    PBScreenBuffer();

    //int dx, int dy, int dw, int dh, int rotate);
    PBScreenBuffer(const PBScreenBuffer & buff);

    PBScreenBuffer(unsigned char * src, int format, int sw, int sh, int scanline);

    void Clear();

    bool IsEmtpy() const;

    void Init(const PBScreenBuffer & buff);

    void Init(unsigned char * src, int format, int sw, int sh, int scanline);

    virtual ~PBScreenBuffer();

    PBScreenBuffer & operator = (const PBScreenBuffer &);

    void FromScreen(bool noNavigationBar);

    void ToScreen(int x, int y, int width, int height);

};

