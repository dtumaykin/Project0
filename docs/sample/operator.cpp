#include <iostream>

struct Point
{
	double x, y, z, w;
};

Point operator+ (Point &p1, Point &p2)
{
	Point p = {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z, p1.w + p2.w};
	return p;
}

std::ostream& operator<< (std::ostream &out, Point &p)
{
	out << "(x : " << p.x << ", y: " << p.y << ", z: " << p.z << ", w: " << p.w << ")";
	return out;
}

int main()
{

Point p1 = {65, 67, 64, 60};
Point p2 = {2, 6, 1, 19};

     Point p3 = p1+p2;
     std::cout << p3;
     std::cin.get();

return 0;
}
