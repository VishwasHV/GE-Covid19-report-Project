#include "stdafx.h"
#include "APICall.h"
#include "ShapeClient.h"

vector<pair<int, string>> _declspec(dllexport) APICall(vector<pair<string, string>>& pInput, int type)
{
	try
	{
		CShapeClient pClient;

		CShapeInterface* pInstance;
		pInstance = pClient.Create(type);

		out = pInstance->CalculateShape(pInput);
		//delete pClient;
		//pClient = NULL;
	}
	catch (exception &e){}
	return out;
	
}