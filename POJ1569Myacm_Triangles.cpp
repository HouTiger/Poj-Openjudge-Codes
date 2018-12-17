#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;
#define CPoint CVector
const double PI = acos(-1);
const double INF = 1e20;
const double EPS = 1e-6;
bool IsZero(double x)
{
    return (-EPS < x) && (x < EPS);
}
class CVector
{
  public:
    double x, y;
    char name;
    CVector() {}
    CVector(double xx, double yy) : x(xx), y(yy) {}
    friend istream &operator>>(istream &is, CVector &p);
};
CPoint a[20];
class CLine
{
  public:
    CPoint a, b;
    CLine(CPoint aa, CPoint bb) : a(aa), b(bb) {}
    CLine() {}
};
istream &operator>>(istream &is, CVector &p)
{
    is >> p.name >> p.x >> p.y;
    return is;
}
CVector operator-(CVector p, CVector q)
{
    return CVector(p.x - q.x, p.y - q.y);
}
CVector operator+(CVector p, CVector q)
{
    return CVector(p.x + q.x, p.y + q.y);
}
CVector operator*(double k, CVector p)
{
    return CVector(k * p.x, k * p.y);
}
double operator*(CVector p, CVector q)
{
    return p.x * q.x + p.y * q.y;
}
double length(CVector p)
{
    return sqrt(p * p);
}
CVector unit(CVector p)
{
    return 1 / length(p) * p;
}
double project(CVector p, CVector n)
{
    return p * unit(n);
}
double operator^(CVector p, CVector q)
{
    return p.x * q.y - q.x * p.y;
}
double area(CPoint p, CPoint q)
{
    return (p ^ q) / 2;
}
double dist(CPoint p, CLine l)
{
    return fabs((p - l.a) ^ (l.b - l.a)) / length(l.b - l.a);
}
int SideofLine(CPoint p, CPoint a, CPoint b)
{
    double result = (b - a) ^ (p - a);
    if (IsZero(result)) // p on a->b
        return 0;
    else if (result > 0) // p on the left side of a->b
        return 1;
    else
        return -1; // p on the right side of a->b
}
bool InsideTriangle(int p, int x, int y, int z) // in or on any line
{
    int t1, t2, t3;
    t1 = SideofLine(a[p], a[x], a[y]);
    t2 = SideofLine(a[p], a[y], a[z]);
    t3 = SideofLine(a[p], a[z], a[x]);
    if (t1 <= 0 && t2 <= 0 && t3 <= 0)
    {
        return true;
    }
    if (t1 >= 0 && t2 >= 0 && t3 >= 0)
    {
        return true;
    }
    return false;
}
double AreaofTriangle(CPoint p1, CPoint p2, CPoint p3)
{
    return fabs(area(CVector(p1 - p2), CVector(p3 - p2)));
}
int main()
{
    int n;
    double size = -1;
    double pre_size = -1;
    bool AnyInside = false;
    int result[3];
    while (cin >> n && (n != 0))
    {
        size = -1;
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        for (int i1 = 0; i1 < n - 2; ++i1)
        {
            for (int i2 = i1 + 1; i2 < n - 1; ++i2)
            {
                if (i2 == i1)
                    continue;
                for (int i3 = i2 + 1; i3 < n; ++i3)
                {
                    if (i3 == i1 || i3 == i2)
                        continue;
                    double area;
                    if ((area = AreaofTriangle(a[i1], a[i2], a[i3])) > size)
                    {
                        AnyInside = false;
                        for (int i4 = 0; i4 < n; ++i4)
                        {
                            if (i4 == i1 || i4 == i2 || i4 == i3)
                                continue;
                            if (InsideTriangle(i4, i1, i2, i3))
                            {
                                AnyInside = true;
                                break;
                            }
                        }
                        if (!AnyInside)
                        {
                            // update
                            // printf("Update AreaofTriangle(%d %d %d) = %lf\n", i1, i2, i3, AreaofTriangle(a[i1], a[i2], a[i3]));
                            size = area;
                            result[0] = i1;
                            result[1] = i2;
                            result[2] = i3;
                            sort(result, result + 3);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 3; ++i)
            cout << a[result[i]].name;
        cout << endl;
    }
    return 0;
}
