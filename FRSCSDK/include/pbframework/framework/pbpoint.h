#ifndef PBPOINT_H
#define PBPOINT_H

class PBPoint
{
public:
	PBPoint();
	PBPoint(int x, int y);
	PBPoint operator+ (PBPoint &r);
	void operator+= (PBPoint &r);
	void operator-= (PBPoint &r);
	void operator= (const PBPoint &r);

	int GetX() const;
	int GetY() const;

	double Distance(const PBPoint& p);

protected:
	int m_x;
	int m_y;
};

#endif // PBPOINT_H
