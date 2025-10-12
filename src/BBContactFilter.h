#pragma once
#include "MobyDick.h"

class BBContactFilter : public ContactFilter
{
public:
	BBContactFilter();
	static bool ShouldCollide(b2ShapeId shapeAId, b2ShapeId shapeBId, void* context) ;

};

