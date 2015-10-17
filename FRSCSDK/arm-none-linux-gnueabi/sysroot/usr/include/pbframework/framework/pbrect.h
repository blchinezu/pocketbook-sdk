#ifndef __PBRECT_H__
#define __PBRECT_H__

#include <vector>
#include <algorithm>
#include <numeric>
#include "pbpoint.h"

// Additional class for grafic
class PBRect
{
public:
	PBRect(int x, int y, int width, int height);
        PBRect(const PBPoint & p1, const PBPoint & p2);
        PBRect();
	~PBRect();

	// суммирует координаты верхнего левого угла с координатами точки
        void operator+= (const PBPoint &r);

        void operator-= (const PBPoint &r);


	// объединяет прямоугольники. Результат - прямоугольник описывающий оба прямоугольника
	void operator+= (const PBRect &r);

	int GetX() const;
	int GetY() const;
	int GetLeft() const;
	int GetTop() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetRight() const;
	int GetBottom() const;
	int GetCenterX() const;
	int GetCenterY() const;
	int GetSquare() const;
	PBPoint GetCenter() const;

	void SetX(int value);
	void SetY(int value);
	void SetWidth(int value);
	void SetHeight(int value);
	void SetRight(int value);
	void SetBottom(int value);

	bool isValid();

	bool isInRectange(int x, int y);

	bool AddRectHorizontal(int x, int y, int width, int height);

	static PBRect GetUpdateRectange(std::vector<PBRect> &src);

protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

#endif /* __PBRECT_H__ */
