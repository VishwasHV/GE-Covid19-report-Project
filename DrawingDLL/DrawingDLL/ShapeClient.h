#ifndef _H_SHAPE_CLIENT_
#define _H_SHAPE_CLIENT_
#include "ShapeInterface.h"
class CShapeClient
{
public:
	CShapeClient();
	~CShapeClient();

	CShapeInterface* Create(int type);
	CShapeInterface* pInstance;

	enum SHAPES
	{
		PIE,
		BAR
	};
};
#endif
