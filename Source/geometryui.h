#ifndef GEOMETRYUI_H
#define GEOMETRYUI_H
#include "geometrymeshengine.h"


/**
* @file
* @brief le fichier contient la classe geometryUI gère les maillage de type BillBoard
*/
/**
* @brief la classe geometryUI gère les maillage de type BillBoard
*/
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
