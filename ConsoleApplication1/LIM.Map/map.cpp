// LIM.Map.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "map.h"
using namespace std;
#include <strsafe.h>
#include <objbase.h>

//#include <iostream>
//#include <string>
//
//char* replace(char* a, int len)
//{
//	VerifyMapLoaded();
//	string s(a);
//	string res = s + "abc";
//	replaceAll(res, "abc", "def");
//	//char test1[5] = "abcd";
//	size_t stSize = res.length() + 1;// strlen(a) + sizeof(char);
//	char* pszReturn = NULL;
//
//	pszReturn = (char*)::CoTaskMemAlloc(stSize);
//	// Copy the contents of test1
//	// to the memory pointed to by pszReturn.
//	strcpy_s(pszReturn, stSize, res.c_str());
//	// Return pszReturn.
//	return pszReturn;	
//}

std::mutex _mtx;
std::map<std::string, std::string> _stringLookupTable;
bool _mapLoaded = false;


void VerifyMapLoaded()
{
	if (_mapLoaded == true)
	{
		return;
	}
	cout << "VerifyMapLoaded";
	_mtx.lock();
	if (_mapLoaded == true)
	{
		return;
	}
	FillMapWithvalue();
	_mapLoaded = true;
	_mtx.unlock();
}

void FillMapWithvalue()
{
	_stringLookupTable["Retalix"] = "~r";
	_stringLookupTable["Business"] = "~b";
	_stringLookupTable["Services"] = "~s";
}

char* replace(char* a, int len)
{
	//VerifyMapLoaded();
	string temp(a);
	string res = temp;
	for (auto &x : _stringLookupTable)
	{
		replaceAll(res, x.first, x.second);
	}	
	
	size_t stSize = res.length() + 1;// strlen(a) + sizeof(char);
	char* pszReturn = NULL;

	pszReturn = (char*)::CoTaskMemAlloc(stSize);
	// Copy the contents of test1
	// to the memory pointed to by pszReturn.
	strcpy_s(pszReturn, stSize, res.c_str());
	// Return pszReturn.
	return pszReturn;
}

char* replaceBack(char* a, int len)
{
	//VerifyMapLoaded();
	string s(a);
	string res = s;
	for (auto &x : _stringLookupTable)
	{
		replaceAll(res, x.second, x.first);
	}

	//char test1[5] = "abcd";
	size_t stSize = res.length() + 1;// strlen(a) + sizeof(char);
	char* pszReturn = NULL;

	pszReturn = (char*)::CoTaskMemAlloc(stSize);
	// Copy the contents of test1
	// to the memory pointed to by pszReturn.
	strcpy_s(pszReturn, stSize, res.c_str());
	// Return pszReturn.
	return pszReturn;
}

void some_func() 
{
	std::string s = "example string";
	replaceAll(s, "1", "7"); // replace all 'x' to 'y'
	
}

int add(int a, int b)
{
	return a + b;
}



void replaceAll(std::string& str, const std::string& from, const std::string& to) 
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) 
	{
		size_t end_pos = start_pos + from.length();
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

