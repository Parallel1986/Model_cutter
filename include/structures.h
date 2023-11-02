#ifndef STRUCTURES_02112023
#define STRUCTURES_02112023

#include <QList>

#define DEFAULT_COLOR 16
#define BLUE_MASK 31
#define GREEN_MASK 992
#define RED_MASK 31744


struct Point3
{
    double x = 0.0,
           y = 0.0,
           z = 0.0;
};

struct Vector3
{
    double x = 0.0,
           y = 0.0,
           z = 0.0;
};

struct Face
{
    Point3 points[3];
    Vector3 normal;
    int color[3] {DEFAULT_COLOR,DEFAULT_COLOR,DEFAULT_COLOR};
};

class RoughModel
{
public:
    void addFace(Face);
    QList<Face> GetFaces();
private:
    QList<Face> faces;
    Point3 pivot_point;
};

#endif //STRUCTURES_02112023
