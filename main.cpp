#include "structures.h"
#include "Loader.h"
#include <iostream>

void PrintRoughModel(RoughModel& model)
{
    std::cout << "Model loaded:\n";
    QList<Face> faces = model.GetFaces();
    for (int i = 0; i < faces.size(); ++i)
    {
        std::cout << "Face #" << i << std::endl
                  << "Normal: " << faces.at(i).normal.x << ", " << faces.at(i).normal.y
                  << ", " << faces.at(i).normal.z << std::endl
                  << "Vertex 1: " << faces.at(i).points[0].x << ", " << faces.at(i).points[0].y
                  << ", " << faces.at(i).points[0].z << std::endl
                  << "Vertex 2: " << faces.at(i).points[1].x << ", " << faces.at(i).points[1].y
                  << ", " << faces.at(i).points[1].z << std::endl
                  << "Vertex 3: " << faces.at(i).points[2].x << ", " << faces.at(i).points[2].y
                  << ", " << faces.at(i).points[2].z << std::endl;
    }
}


int main(int argc, char** argv)
{
    RoughModel model;
    Loader loader(model);
    QString path =  "stl_template/Clamp.stl";
    try {
        loader.Load(path);
    } catch (std::exception& ex) {
        std::cerr << "Error!\n" << ex.what();
        return -1;
    }

    PrintRoughModel(model);

    return 0;
}
