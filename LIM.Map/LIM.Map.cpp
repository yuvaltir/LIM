// LIM.Map.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LIM.MAP.h"
using namespace std;

#include <strsafe.h>
#include <objbase.h>
#include <stdio.h>
//#include <iostream>
//#include <string>

char* replace(char* a, int len)
{
	string s(a);
	string res = s + "abc";
	replaceAll(res, "abc", "def");
	//char test1[5] = "abcd";
	size_t stSize = res.length() + 1;// strlen(a) + sizeof(char);
	char* pszReturn = NULL;

	pszReturn = (char*)::CoTaskMemAlloc(stSize);
	// Copy the contents of test1
	// to the memory pointed to by pszReturn.
	strcpy_s(pszReturn, stSize, res.c_str());
	// Return pszReturn.
	return pszReturn;

	//return (char *)res.c_str();
	
	//char* newStr = new char[len + 3];
	//for (int i = 0; i < len; ++i)
	//{
	//	newStr[i + 3] = a[i];
	//}
	//newStr[0] = 'a';
	//newStr[1] = 'b';
	//newStr[2] = 'c';
	//newStr[len+2] = '\0';
	//return newStr;
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