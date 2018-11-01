#ifndef DEF_POINT
#define DEF_POINT

class Point
{
    public:

    Point();
    Point(double X, double Y);
    double getX() const;
    double getY() const;

    private:
    
    double x;
    double y;
};

#endif