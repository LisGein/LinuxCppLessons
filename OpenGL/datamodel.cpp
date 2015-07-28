#include "datamodel.h"


DataModel::DataModel()
{
}

void DataModel::read_date()
{
    std::ifstream fin("data.txt");
    size_t samples_count;
    fin >> samples_count;
    std::string line;
    while (!fin.eof()) {
        std::getline(fin, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            float coor_x, coor_y, coor_z;
            iss >> trash >> coor_x >> coor_y >> coor_z;

            point_3f point(coor_x, coor_y, coor_z);
            point++;
            verts_.push_back(point);
        }
        else if (!line.compare(0, 3, "vt "))
        {
            iss >> trash >> trash;
            float vt1, vt2;
            iss >> vt1 >> vt2;
            point_2f point(vt1, vt2);
            vt_.push_back(point);
        }
        else if (!line.compare(0, 3, "vn "))
        {
            float vn1, vn2, vn3;
            iss >> trash >> trash >> vn1 >> vn2 >> vn3;
            point_3f point(vn1, vn2, vn3);
            vn_.push_back(point);
        }
        else if (!line.compare(0, 2, "f "))
        {
            iss >> trash;
            QVector<point_3i> f;
            for (int i = 0; i < 3; ++i)
            {
                point_3i fm;
                iss >> fm.x >> trash >> fm.y  >> trash >> fm.z;
                fm--;
                f.push_back(fm);
            }
            faces_.push_back(f);
        }
    }
}

QVector<vector_3i> DataModel::faces()
{
    return faces_;
}

QVector<point_3f> DataModel::verts()
{
    return verts_;
}

QVector<point_2f> DataModel::vt()
{
    return vt_;
}

QVector<point_3f> DataModel::vn()
{
    return vn_;
}
