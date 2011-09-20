#include <iostream>
struct Point
{
	double x, y, z;
};

Point operator+ (Point &p1, Point &p2)
{
	Point p = {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
	return p;
}

int main()
{
Point p1 = {1, 2, 3};
Point p2 = {4, 5, 6};

Point p3 = p1+p2;

std::cout << p3.x << " " << p3.y << " "<< p3.z;
std::cin.get();

return 0;
}
