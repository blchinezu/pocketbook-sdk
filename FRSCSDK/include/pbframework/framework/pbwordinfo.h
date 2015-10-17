#ifndef __PBWORDINFO_H__
#define __PBWORDINFO_H__

class PBWordInfo
{
public:
    PBWordInfo(int screen, char *word, int x1, int y1, int x2, int y2);
    PBWordInfo(const PBWordInfo &src);
    ~PBWordInfo();

    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();

	void SetX(int value);
	void SetY(int value);
	void SetWidth(int value);
	void SetHeight(int value);

    int GetScreen();

    bool isLastWord();
    char GetLastChar();
    char *GetWord();
    int GetWordLen();

protected:

private:
    char *m_word;
    int m_wordlen;
    int m_screen;

    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

#endif /* __PBWORDINFO_H__ */
