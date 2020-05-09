#include "stdafx.h"
#include "ShapeClient.h"
#include "PieCalculation.h"

CShapeClient::CShapeClient()
{
	pInstance = NULL;
}


CShapeClient::~CShapeClient()
{
}

CShapeInterface* CShapeClient::Create(int type)
{
	switch (type)
	{
	case SHAPES::PIE:
		pInstance = new CPieCalculation();
		break;
	}
	return pInstance;
}