#ifndef _H_PIE_CAL_H_
#define _H_PIE_CAL_H_

#include"stdafx.h"
#include "ShapeInterface.h"
#include <vector>
#include <string>
using namespace std;
class CPieCalculation :
	public CShapeInterface
{
public:
	CPieCalculation();
	~CPieCalculation();

private:
	void InsertItem(string sElement, int dValue);

	vector<pair<int, string>> map_pChart;

	int m_nIndex;
	double m_dPercentage;
	double m_dAngle;
	double d_totalVal;
//	vector<pair<int, string>> GetValuesForPie(vector<pair<string, string>> pInput);
	void UpdatePieChart();

	vector<pair<int, string>> CalculateShape(vector<pair<string, string>> pInput);


};

#endif
