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

//void FillMapWithvalue()
//{
//	_values.push_back("~Business");
//	_values.push_back("~Retalix");
//	_values.push_back("~Services");
//	dawg_builder.Insert("b", 0);
//	dawg_builder.Insert("r", 1);
//	dawg_builder.Insert("s", 2);
//
//	dawg_builder.Finish(&dawg);
//	dawgdic::DictionaryBuilder::Build(dawg, &dawg_dic);
//
//	_valuesReverse.push_back("b");
//	_valuesReverse.push_back("r");
//	_valuesReverse.push_back("s");
//	dawg_builderReverse.Insert("~Business", 0);
//	dawg_builderReverse.Insert("~Retalix", 1);
//	dawg_builderReverse.Insert("~Services", 2);
//
//	dawg_builderReverse.Finish(&dawgReverse);
//	dawgdic::DictionaryBuilder::Build(dawgReverse, &dawg_dicReverse);
//}


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
#if defined(DEBUG)
		cout << "\r\n";
#endif
		while (f == true && strLen<len)
		{
			f = dawg_dic.Follow(a[currentIndex+strLen], &lastIndex);
			if (f == true)
			{
				strLen++;				
				i++;
			}
#if defined(DEBUG)
			cout << a[currentIndex + strLen];
			cout << "\r\n";
#endif
		}
		if (strLen > 0)
		{			 
			string strFoundStr = temp.substr(currentIndex, strLen);
#if defined(DEBUG)
			cout << "strFoundStr = " + strFoundStr + " \r\n";
#endif
			dawgdic::ValueType res1 = dawg_dic.Find(strFoundStr.c_str());
			if (res1 > -1)
			{
#if defined(DEBUG)
				cout << "Appending = " + _values[res1] + " \r\n";
#endif
				res = res.append(_values[res1]);
#if defined(DEBUG)
				cout << " res1 is " + res + "\r\n";
#endif
			}	
			else
			{
#if defined(DEBUG)
				cout << "Appending strFoundStr = " + strFoundStr + "\r\n";
#endif
				res = res.append(strFoundStr);
#if defined(DEBUG)
				cout << " res2 is " + res + "\r\n";
#endif
			}
			--i;
		}
		else
		{ 
#if defined(DEBUG)
			cout << "Else Appending = " + temp.substr(currentIndex, 1) + " \r\n";
#endif
			res = res.append(temp.substr(currentIndex, 1));
#if defined(DEBUG)
			cout << " res3 is " + res + "\r\n";
#endif
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
			if (res1 > -1)
			{
				res = res.append(_valuesReverse[res1]);
				
			}
			else
			{
				res = res.append(strFoundStr);
			}
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

