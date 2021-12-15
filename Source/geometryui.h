#ifndef GEOMETRYUI_H
#define GEOMETRYUI_H
#include "geometrymeshengine.h"

class geometryUI: public GeometryMeshEngine
{
public:
    geometryUI();

void initLifeBar();
bool updateLifeBar(double time);
private:
double vie = 100;
};

#endif // GEOMETRYUI_H
