#include <iostream>
struct Point
{
	char x, y, z,w;
};

Point operator+ (Point &p1, Point &p2)
{
	Point p = {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z, p1.w+p2.w};
	return p;
}

int main()
{
Point p1 = {65, 67, 64, 60};
Point p2 = {2, 6, 1, 19 };

Point p3 = p1+p2;

std::cout << p3.x << " " << p3.y << " "<< p3.z <<" "<< p3.w;
std::cin.get();

return 0;
}
