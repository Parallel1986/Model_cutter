#ifndef LOADER_02112023
#define LOADER_02112023

#include "structures.h"
#include <QFile>
#include <QString>

class Loader {
public:
    Loader(RoughModel& model_ref);
    void Load(QString& file_name);
private:
    enum FileTypes{
        STL,
        OBJ
    };

    FileTypes AnalizeFile(QString& file_name);
    void LoadFromSTL(QString& file_name);
    void LoadAsASCIISTL(QString& file_name);
    void loadAsBinarySTL(QString& file_name);
    void LoadFromOBJ(QString& file_name);
    RoughModel* model= nullptr;
    void GetColotForFace(Face& face, unsigned short color);
    double TransformFromBytes(char* byte_array);
};

#endif //LOADER_02112023
