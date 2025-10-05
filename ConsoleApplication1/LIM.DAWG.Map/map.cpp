// LIM.Map.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "map.h"
using namespace std;
#include <strsafe.h>
#include <objbase.h>

#include "dawg-builder.h"
#include "dictionary-builder.h"
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
std::vector<std::string> _values;
std::vector<std::string> _valuesReverse;
dawgdic::DawgBuilder dawg_builder;
dawgdic::DawgBuilder dawg_builderReverse;
dawgdic::Dictionary dawg_dic;
dawgdic::Dictionary dawg_dicReverse;
dawgdic::Dawg dawg;
dawgdic::Dawg dawgReverse;
//std::map<std::string, std::string> _stringLookupTable;
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
	_values.push_back("~b");
	_values.push_back("~r");
	_values.push_back("~s");	
	dawg_builder.Insert("Business", 0);
	dawg_builder.Insert("Retalix", 1);
	dawg_builder.Insert("Services", 2);
	
	dawg_builder.Finish(&dawg);
	dawgdic::DictionaryBuilder::Build(dawg, &dawg_dic);

	_valuesReverse.push_back("Business");
	_valuesReverse.push_back("Retalix");
	_valuesReverse.push_back("Services");
	dawg_builderReverse.Insert("~b", 0);
	dawg_builderReverse.Insert("~r", 1);	
	dawg_builderReverse.Insert("~s", 2);

	dawg_builderReverse.Finish(&dawgReverse);
	dawgdic::DictionaryBuilder::Build(dawgReverse, &dawg_dicReverse);
}


char* replace(char* a, int len)
{
	//VerifyMapLoaded();
	string temp(a);
	string res;	
	
	for (int i = 0; i < len; ++i)
	{
		dawgdic::BaseType lastIndex = 0;
		int strLen = 0;
		int currentIndex = i;
		bool f = true;
		while (f == true && strLen<len)
		{
			f = dawg_dic.Follow(a[currentIndex+strLen], &lastIndex);
			if (f == true)
			{
				strLen++;				
				i++;
			}
		}
		if (strLen > 0)
		{			 
			string strFoundStr = temp.substr(currentIndex, strLen);
			dawgdic::ValueType res1 = dawg_dic.Find(strFoundStr.c_str());
			res = res.append(_values[res1]);
			--i;
		}
		else
		{ 
			res = res.append(temp.substr(currentIndex, 1));
		}				
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
	string temp(a);
	string res;

	for (int i = 0; i < len; ++i)
	{
		dawgdic::BaseType lastIndex = 0;
		int strLen = 0;
		int currentIndex = i;
		bool f = true;
		while (f == true && strLen<len)
		{
			f = dawg_dicReverse.Follow(a[currentIndex + strLen], &lastIndex);
			if (f == true)
			{
				strLen++;
				i++;
			}
		}
		if (strLen > 0)
		{
			string strFoundStr = temp.substr(currentIndex, strLen);
			dawgdic::ValueType res1 = dawg_dicReverse.Find(strFoundStr.c_str());
			res = res.append(_valuesReverse[res1]);
			--i;
		}
		else
		{
			res = res.append(temp.substr(currentIndex, 1));
		}
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
	//size_t start_pos = 0;
	//while ((start_pos = str.find(from, start_pos)) != std::string::npos) 
	//{
	//	size_t end_pos = start_pos + from.length();
	//	str.replace(start_pos, from.length(), to);
	//	start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	//}

}

