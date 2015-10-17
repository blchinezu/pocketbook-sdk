#pragma once
#include <string>
class PBMD5
{
    static const int LENGTH = 16;
    void Init();
    void CalcFileMD5(const char *src, unsigned char *r);
public:
    PBMD5();
    PBMD5(const PBMD5 & other);
    PBMD5(const unsigned char * src, int length);
    PBMD5(const std::string & fileName);
    PBMD5(const char * src, int length);
    virtual ~PBMD5();

    static const PBMD5 & MainFileMD5();

    void Init(const unsigned char data[LENGTH]);
    void Init(const PBMD5 & other);
    void Init(const unsigned char * src, int length);
    void Init(const std::string & fileName);    

    int IsError() const { return m_error; }
    inline bool IsEmpty() const { return m_empty; }
    inline void Clear() { m_empty = true; }
    inline const unsigned char * GetData() const { return m_data; }


    virtual int GetLength() const {return LENGTH; }
    virtual std::string ToString() const;
    virtual PBMD5 & operator=(const PBMD5 & other);
    virtual bool operator==(const PBMD5 & other) const;
    virtual bool operator==(const std::string & other) const;

protected:
    unsigned char m_data[LENGTH];
    bool m_empty;
    int m_error;
};
