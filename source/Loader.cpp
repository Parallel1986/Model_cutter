#include "Loader.h"
#include <QFile>
#include <QString>
#include <fstream>

void Loader::Load(QString& file_name)
{
    auto file_type = AnalizeFile(file_name);
    if (file_type == Loader::FileTypes::STL)
        LoadFromSTL(file_name);
    else if (file_type == Loader::FileTypes::OBJ)
        LoadFromOBJ(file_name);
}

Loader::Loader(RoughModel& model_ref)
{
    model = &model_ref;
}

Loader::FileTypes Loader::AnalizeFile(QString& file_name)
{
    return Loader::FileTypes::STL;
}

void Loader::LoadFromOBJ(QString& file_name)
{

}

void Loader::LoadFromSTL(QString& file_name)
{
    QFile file(file_name);
    QByteArray byte_array;
    QString buffer;
    if (file.open(QIODevice::ReadOnly))
    {
        byte_array = file.read(5);
        file.close();
        buffer = byte_array;

        if (buffer == "solid")
            return LoadAsASCIISTL(file_name);
        else
            return loadAsBinarySTL(file_name);
    }
}


void Loader::LoadAsASCIISTL(QString& file_name)
{
    QFile file(file_name);
    QString buffer;
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        buffer = file.readAll();
        file.close();
    }
    else
        throw std::runtime_error("Error while trying to open file" + file_name.toStdString());

    QRegExp expr("\\w+");
    QStringList words = buffer.split(expr);

    auto word = words.begin();
    while (*word != "endsolid" || word != words.end())
    {
        while (*word != "facet")
            word++;

        word++;
        int vertex_ind = 0;
        Face face;
        while (*word != "endfacet" || word != words.end())
        {
            if (*word == "normal")
            {
                word++;
                face.normal.x = (*word).toDouble();
                word++;
                face.normal.y = (*word).toDouble();
                word++;
                face.normal.z = (*word).toDouble();
            }
            else if (*word == "vertex")
            {
                word++;
                face.points[vertex_ind].x = (*word).toDouble();
                word++;
                face.points[vertex_ind].y = (*word).toDouble();
                word++;
                face.points[vertex_ind].z = (*word).toDouble();
                ++vertex_ind;
            }
            else
                word++;
        }
        model->addFace(face);
    }
}

void Loader::loadAsBinarySTL(QString& file_name)
{
    QFile file(file_name);
    QByteArray byte_array;
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        byte_array = file.read(80);
        byte_array.clear();

        byte_array = file.read(4);
        char triangle_num[4];
        for (int i = 0; i<4;++i)
            triangle_num[i] = byte_array.data()[i];
        byte_array.clear();
        unsigned int trian = *((unsigned int*)triangle_num);
        for (auto ind = 0; ind < trian; ++ind)
        {
            Face face;
            char buf[4];
            char col[2];

            byte_array = file.read(4);
            for (int i = 0; i < 4; ++i) {
                buf[i] = byte_array[i];
            }
            face.normal.x = TransformFromBytes(buf);
            byte_array.clear();

            byte_array = file.read(4);
            for (int i = 0; i < 4; ++i) {
                buf[i] = byte_array[i];
            }
            face.normal.y = TransformFromBytes(buf);
            byte_array.clear();

            byte_array = file.read(4);
            for (int i = 0; i < 4; ++i) {
                buf[i] = byte_array[i];
            }
            face.normal.z = TransformFromBytes(buf);
            byte_array.clear();

            for (int i = 0; i < 3; ++i)
            {
                byte_array = file.read(4);
                for (int i = 0; i < 4; ++i) {
                    buf[i] = byte_array[i];
                }
                face.points[i].x = TransformFromBytes(buf);
                byte_array.clear();

                byte_array = file.read(4);
                for (int i = 0; i < 4; ++i) {
                    buf[i] = byte_array[i];
                }
                face.points[i].y = TransformFromBytes(buf);
                byte_array.clear();

                byte_array = file.read(4);
                for (int i = 0; i < 4; ++i) {
                    buf[i] = byte_array[i];
                }
                face.points[i].z = TransformFromBytes(buf);
                byte_array.clear();
            }
            byte_array = file.read(2);
            col[0] = byte_array[0];
            col[1] = byte_array[1];

            GetColotForFace(face, *((unsigned short*)col));
            byte_array.clear();
            model->addFace(face);
        }
    }
    else
        throw std::runtime_error("Error while trying to open file" + file_name.toStdString());
}

void Loader::GetColotForFace(Face& face, unsigned short color)
{
    face.color[0] = color&BLUE_MASK;
    face.color[1] = (color&GREEN_MASK)>>5;
    face.color[2] = (color&RED_MASK)>>10;
}

double Loader::TransformFromBytes(char* byte_array)
{
    return *((float*)byte_array);
}
