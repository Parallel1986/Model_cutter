#include "structures.h"

void RoughModel::addFace(Face face)
{
    faces.append(face);
}

QList<Face> RoughModel::GetFaces()
{
    return faces;
}
