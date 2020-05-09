
#include "stdafx.h"
#include "PieCalculation.h"


CPieCalculation::CPieCalculation()
{
	m_nIndex = 0;
	m_dPercentage = 0.0;
	m_dAngle = 0.0;
	d_totalVal = 0.0;
	
}


CPieCalculation::~CPieCalculation()
{
}


vector<pair<int, string>> CPieCalculation::CalculateShape(vector<pair<string, string>> pInput)
{
	for (vector<pair<string, string>>::iterator itr = pInput.begin(); itr != pInput.end(); itr++)
	{
		string sElement = itr->first;
		int nValue = stoi(itr->second);
		InsertItem(sElement, nValue);

	}
	return map_pChart;
}

void CPieCalculation::InsertItem(string sElement, int dValue)
{
	try
	{
		if (sElement.compare("") && dValue > 0)
		{
			if (dValue > 100) { dValue = dValue / 100; }
			map_pChart.push_back(make_pair(m_nIndex, sElement));
			string sVal;
			sVal = std::to_string(dValue);
			d_totalVal += dValue;
			map_pChart.push_back(make_pair(++m_nIndex, sVal));
			string sPercentage;
			m_dPercentage = 0;
			sPercentage = std::to_string(m_dPercentage);
			map_pChart.push_back(make_pair(++m_nIndex, sPercentage));
			string sAngle;
			m_dAngle = 0;
			sAngle = std::to_string(m_dAngle);
			map_pChart.push_back(make_pair(++m_nIndex, sAngle));
			m_nIndex++;
			UpdatePieChart();
		}
	}
	catch (exception &e)
	{
		// log using e
	}
}

void CPieCalculation::UpdatePieChart(void)
{
	try
	{
		string svalue, sPercentage, sAngle;
		double dpercentage, dAngle;
		int nvalue;
		for (int i = 0; i < map_pChart.size(); i = i + 4)
		{
			svalue = map_pChart[i + 1].second;
			nvalue = stoi(svalue);
			sPercentage = map_pChart[i + 2].second;
			dpercentage = stof(sPercentage);
			sAngle = map_pChart[i + 3].second;
			dAngle = stof(sAngle);
			if (d_totalVal > 0){
				dpercentage = float(nvalue / d_totalVal);
				dAngle = 360 * dpercentage;
			}
			sPercentage = to_string(dpercentage);
			map_pChart[i + 2].second = sPercentage;
			sAngle = to_string(dAngle);
			map_pChart[i + 3].second = sAngle;
		}
	}
	catch (exception &e)
	{

	}
}



