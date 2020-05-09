#ifndef _H_API_H
#define _H_API_H

#include "stdafx.h"
#include <vector>
using namespace std;

vector<pair<int, string>>  _declspec(dllexport)  APICall(vector<string, string>&, int);
vector<pair<int, string>> out;

#endif