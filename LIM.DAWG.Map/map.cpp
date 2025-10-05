// LIM.Map.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "map.h"
using namespace std;
//#include <strsafe.h>
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

char* replace(char* a, int len)
{
	try
	{
		//VerifyMapLoaded();
		string temp(a);
		string res;

		int tempLen = temp.length();

		for (int i = 0; i < tempLen; ++i)
		{
			dawgdic::BaseType lastIndex = 0;
			int strLen = 0;
			int currentIndex = i;
			bool f = true;
			while (f == true && currentIndex + strLen < temp.length() )
			{
				f = dawg_dic.Follow(a[currentIndex + strLen], &lastIndex);
				if (f == true)
				{
					strLen++;
					i++;
				}
			}
			if (strLen > 0 )
			{
				string strFoundStr = temp.substr(currentIndex, strLen);
				dawgdic::ValueType res1 = dawg_dic.has_value(strLen);//
				dawgdic::ValueType res2 = dawg_dic.Find(strFoundStr.c_str());
				if (res2 > -1)
				{
					res = res.append(_values[res2]);
					--i;
					continue;
				}				
			}
			
			res = res.append(temp.substr(currentIndex, strLen + 1));
			
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
 	catch (...)
	{
		return 0;
	}
}

char* replaceBack(char* a, int len)
{
	try
	{
		//VerifyMapLoaded();
		string temp(a);
		string res;

		for (int i = 0; i < temp.length(); ++i)
		{
			dawgdic::BaseType lastIndex = 0;
			int strLen = 0;
			int currentIndex = i;
			bool f = true;
			while (f == true && currentIndex + strLen<temp.length())
			{
				f = dawg_dicReverse.Follow(a[currentIndex + strLen], &lastIndex);
				if (f == true)
				{
					strLen++;
					i++;
				}
			}
			if (strLen > 0 )
			{
				string strFoundStr = temp.substr(currentIndex, strLen);
				dawgdic::ValueType res1 = dawg_dicReverse.Find(strFoundStr.c_str());
				if (res1 > -1)
				{
					res = res.append(_valuesReverse[res1]);
					--i;
					continue;
				}
			}

			res = res.append(temp.substr(currentIndex, strLen+1));
		
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
	catch (...)
	{
		return 0;
	}
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



























void FillMapWithvalue()
{

	_values.push_back("~em");

	_values.push_back("~km");

	_values.push_back("~fs");

	_values.push_back("~jd");

	_values.push_back("~jl");

	_values.push_back("~e7");

	_values.push_back("~k5");

	_values.push_back("~i4");

	_values.push_back("~l7");

	_values.push_back("~c3");

	_values.push_back("~l6");

	_values.push_back("~k3");

	_values.push_back("~lc");

	_values.push_back("~la");

	_values.push_back("~bm");

	_values.push_back("~lx");

	_values.push_back("~j0");

	_values.push_back("~lq");

	_values.push_back("~f");

	_values.push_back("~k2");

	_values.push_back("~kd");

	_values.push_back("~gs");

	_values.push_back("~k4");

	_values.push_back("~8");

	_values.push_back("~cs");

	_values.push_back("~b5");

	_values.push_back("~cm");

	_values.push_back("~a3");

	_values.push_back("~l0");

	_values.push_back("~dl");

	_values.push_back("~f6");

	_values.push_back("~f4");

	_values.push_back("~e4");

	_values.push_back("~lj");

	_values.push_back("~fc");

	_values.push_back("~7");

	_values.push_back("~kf");

	_values.push_back("~1");

	_values.push_back("~f0");

	_values.push_back("~fl");

	_values.push_back("~di");

	_values.push_back("~hj");

	_values.push_back("~jn");

	_values.push_back("~iu");

	_values.push_back("~hm");

	_values.push_back("~a");

	_values.push_back("~iq");

	_values.push_back("~u");

	_values.push_back("~e1");

	_values.push_back("~ea");

	_values.push_back("~j5");

	_values.push_back("~kr");

	_values.push_back("~j4");

	_values.push_back("~dx");

	_values.push_back("~jk");

	_values.push_back("~hv");

	_values.push_back("~cy");

	_values.push_back("~l1");

	_values.push_back("~je");

	_values.push_back("~fh");

	_values.push_back("~n");

	_values.push_back("~i");

	_values.push_back("~lw");

	_values.push_back("~h");

	_values.push_back("~l2");

	_values.push_back("~d5");

	_values.push_back("~by");

	_values.push_back("~ki");

	_values.push_back("~i3");

	_values.push_back("~kg");

	_values.push_back("~gq");

	_values.push_back("~go");

	_values.push_back("~g6");

	_values.push_back("~ho");

	_values.push_back("~a7");

	_values.push_back("~g0");

	_values.push_back("~ap");

	_values.push_back("~b1");

	_values.push_back("~ct");

	_values.push_back("~er");

	_values.push_back("~ay");

	_values.push_back("~bc");

	_values.push_back("~aa");

	_values.push_back("~ba");

	_values.push_back("~ae");

	_values.push_back("~6");

	_values.push_back("~x");

	_values.push_back("~al");

	_values.push_back("~q");

	_values.push_back("~ax");

	_values.push_back("~ik");

	_values.push_back("~bj");

	_values.push_back("~fi");

	_values.push_back("~e0");

	_values.push_back("~lt");

	_values.push_back("~i2");

	_values.push_back("~jb");

	_values.push_back("~ce");

	_values.push_back("~ku");

	_values.push_back("~fx");

	_values.push_back("~e");

	_values.push_back("~ag");

	_values.push_back("~bk");

	_values.push_back("~c0");

	_values.push_back("~lm");

	_values.push_back("~bi");

	_values.push_back("~kt");

	_values.push_back("~kj");

	_values.push_back("~lu");

	_values.push_back("~jh");

	_values.push_back("~fg");

	_values.push_back("~j1");

	_values.push_back("~lp");

	_values.push_back("~h6");

	_values.push_back("~cq");

	_values.push_back("~fw");

	_values.push_back("~ke");

	_values.push_back("~bu");

	_values.push_back("~fa");

	_values.push_back("~2");

	_values.push_back("~jt");

	_values.push_back("~jg");

	_values.push_back("~hw");

	_values.push_back("~if");

	_values.push_back("~h1");

	_values.push_back("~in");

	_values.push_back("~h2");

	_values.push_back("~ii");

	_values.push_back("~io");

	_values.push_back("~ij");

	_values.push_back("~il");

	_values.push_back("~e5");

	_values.push_back("~hy");

	_values.push_back("~en");

	_values.push_back("~cb");

	_values.push_back("~do");

	_values.push_back("~l4");

	_values.push_back("~cp");

	_values.push_back("~ac");

	_values.push_back("~ci");

	_values.push_back("~s");

	_values.push_back("~bf");

	_values.push_back("~jc");

	_values.push_back("~ia");

	_values.push_back("~br");

	_values.push_back("~k");

	_values.push_back("~w");

	_values.push_back("~dv");

	_values.push_back("~hh");

	_values.push_back("~c7");

	_values.push_back("~b8");

	_values.push_back("~dy");

	_values.push_back("~lh");

	_values.push_back("~b4");

	_values.push_back("~fd");

	_values.push_back("~i6");

	_values.push_back("~kx");

	_values.push_back("~ar");

	_values.push_back("~j6");

	_values.push_back("~iy");

	_values.push_back("~dj");

	_values.push_back("~gi");

	_values.push_back("~fe");

	_values.push_back("~iv");

	_values.push_back("~k7");

	_values.push_back("~hf");

	_values.push_back("~bo");

	_values.push_back("~ja");

	_values.push_back("~a2");

	_values.push_back("~ai");

	_values.push_back("~db");

	_values.push_back("~eg");

	_values.push_back("~ak");

	_values.push_back("~a6");

	_values.push_back("~cv");

	_values.push_back("~ch");

	_values.push_back("~ec");

	_values.push_back("~ds");

	_values.push_back("~bl");

	_values.push_back("~v");

	_values.push_back("~hi");

	_values.push_back("~i0");

	_values.push_back("~kq");

	_values.push_back("~hd");

	_values.push_back("~gy");

	_values.push_back("~ei");

	_values.push_back("~4");

	_values.push_back("~b3");

	_values.push_back("~l");

	_values.push_back("~e2");

	_values.push_back("~kh");

	_values.push_back("~fj");

	_values.push_back("~bh");

	_values.push_back("~fn");

	_values.push_back("~gn");

	_values.push_back("~he");

	_values.push_back("~ad");

	_values.push_back("~it");

	_values.push_back("~aj");

	_values.push_back("~lg");

	_values.push_back("~as");

	_values.push_back("~ip");

	_values.push_back("~gl");

	_values.push_back("~d1");

	_values.push_back("~ft");

	_values.push_back("~t");

	_values.push_back("~k8");

	_values.push_back("~k1");

	_values.push_back("~i5");

	_values.push_back("~kn");

	_values.push_back("~lv");

	_values.push_back("~f8");

	_values.push_back("~dh");

	_values.push_back("~fm");

	_values.push_back("~jo");

	_values.push_back("~ef");

	_values.push_back("~cw");

	_values.push_back("~l3");

	_values.push_back("~co");

	_values.push_back("~lb");

	_values.push_back("~is");

	_values.push_back("~h8");

	_values.push_back("~f5");

	_values.push_back("~bx");

	_values.push_back("~c4");

	_values.push_back("~dq");

	_values.push_back("~kv");

	_values.push_back("~li");

	_values.push_back("~eu");

	_values.push_back("~jy");

	_values.push_back("~cl");

	_values.push_back("~gf");

	_values.push_back("~lo");

	_values.push_back("~cr");

	_values.push_back("~ir");

	_values.push_back("~ck");

	_values.push_back("~gm");

	_values.push_back("~cd");

	_values.push_back("~ha");

	_values.push_back("~dr");

	_values.push_back("~jx");

	_values.push_back("~c5");

	_values.push_back("~c8");

	_values.push_back("~m");

	_values.push_back("~i1");

	_values.push_back("~f3");

	_values.push_back("~ln");

	_values.push_back("~ka");

	_values.push_back("~ju");

	_values.push_back("~ge");

	_values.push_back("~fu");

	_values.push_back("~jw");

	_values.push_back("~h4");

	_values.push_back("~l8");

	_values.push_back("~g4");

	_values.push_back("~jf");

	_values.push_back("~bt");

	_values.push_back("~h3");

	_values.push_back("~iw");

	_values.push_back("~hq");

	_values.push_back("~ex");

	_values.push_back("~gd");

	_values.push_back("~j3");

	_values.push_back("~bq");

	_values.push_back("~af");

	_values.push_back("~cc");

	_values.push_back("~d0");

	_values.push_back("~es");

	_values.push_back("~eo");

	_values.push_back("~dp");

	_values.push_back("~hb");

	_values.push_back("~fy");

	_values.push_back("~kk");

	_values.push_back("~gp");

	_values.push_back("~ga");

	_values.push_back("~g3");

	_values.push_back("~gj");

	_values.push_back("~hs");

	_values.push_back("~bv");

	_values.push_back("~cu");

	_values.push_back("~dd");

	_values.push_back("~a8");

	_values.push_back("~a4");

	_values.push_back("~c6");

	_values.push_back("~d8");

	_values.push_back("~eb");

	_values.push_back("~kp");

	_values.push_back("~g5");

	_values.push_back("~e8");

	_values.push_back("~d6");

	_values.push_back("~cg");

	_values.push_back("~b7");

	_values.push_back("~o");

	_values.push_back("~c");

	_values.push_back("~bg");

	_values.push_back("~kb");

	_values.push_back("~ly");

	_values.push_back("~h5");

	_values.push_back("~gu");

	_values.push_back("~j2");

	_values.push_back("~bw");

	_values.push_back("~js");

	_values.push_back("~hp");

	_values.push_back("~eq");

	_values.push_back("~f2");

	_values.push_back("~fv");

	_values.push_back("~ek");

	_values.push_back("~gc");

	_values.push_back("~d");

	_values.push_back("~bp");

	_values.push_back("~dc");

	_values.push_back("~fp");

	_values.push_back("~f1");

	_values.push_back("~av");

	_values.push_back("~b0");

	_values.push_back("~cx");

	_values.push_back("~jq");

	_values.push_back("~le");

	_values.push_back("~da");

	_values.push_back("~ll");

	_values.push_back("~hr");

	_values.push_back("~ks");

	_values.push_back("~ca");

	_values.push_back("~jm");

	_values.push_back("~et");

	_values.push_back("~b6");

	_values.push_back("~k6");

	_values.push_back("~f7");

	_values.push_back("~el");

	_values.push_back("~d2");

	_values.push_back("~bb");

	_values.push_back("~gx");

	_values.push_back("~ah");

	_values.push_back("~an");

	_values.push_back("~0");

	_values.push_back("~g");

	_values.push_back("~5");

	_values.push_back("~be");

	_values.push_back("~a1");

	_values.push_back("~a0");

	_values.push_back("~jp");

	_values.push_back("~dw");

	_values.push_back("~ew");

	_values.push_back("~ji");

	_values.push_back("~cj");

	_values.push_back("~gh");

	_values.push_back("~dn");

	_values.push_back("~fq");

	_values.push_back("~at");

	_values.push_back("~d7");

	_values.push_back("~dm");

	_values.push_back("~bn");

	_values.push_back("~e6");

	_values.push_back("~fr");

	_values.push_back("~ls");

	_values.push_back("~fk");

	_values.push_back("~bs");

	_values.push_back("~dt");

	_values.push_back("~b");

	_values.push_back("~hk");

	_values.push_back("~fb");

	_values.push_back("~ev");

	_values.push_back("~3");

	_values.push_back("~g8");

	_values.push_back("~j");

	_values.push_back("~b2");

	_values.push_back("~cf");

	_values.push_back("~dk");

	_values.push_back("~bd");

	_values.push_back("~y");

	_values.push_back("~k0");

	_values.push_back("~ee");

	_values.push_back("~d3");

	_values.push_back("~cn");

	_values.push_back("~gt");

	_values.push_back("~l5");

	_values.push_back("~jv");

	_values.push_back("~e3");

	_values.push_back("~jr");

	_values.push_back("~jj");

	_values.push_back("~r");

	_values.push_back("~lr");

	_values.push_back("~g7");

	_values.push_back("~gw");

	_values.push_back("~gk");

	_values.push_back("~c2");

	_values.push_back("~au");

	_values.push_back("~h7");

	_values.push_back("~ey");

	_values.push_back("~kl");

	_values.push_back("~gv");

	_values.push_back("~gg");

	_values.push_back("~p");

	_values.push_back("~aq");

	_values.push_back("~am");

	_values.push_back("~i8");

	_values.push_back("~ld");

	_values.push_back("~lf");

	_values.push_back("~hc");

	_values.push_back("~im");

	_values.push_back("~hu");

	_values.push_back("~kw");

	_values.push_back("~hn");

	_values.push_back("~id");

	_values.push_back("~ie");

	_values.push_back("~ih");

	_values.push_back("~ic");

	_values.push_back("~ib");

	_values.push_back("~ig");

	_values.push_back("~ht");

	_values.push_back("~hl");

	_values.push_back("~eh");

	_values.push_back("~ep");

	_values.push_back("~ff");

	_values.push_back("~i7");

	_values.push_back("~g1");

	_values.push_back("~hg");

	_values.push_back("~hx");

	_values.push_back("~kc");

	_values.push_back("~a5");

	_values.push_back("~ko");

	_values.push_back("~j8");

	_values.push_back("~lk");

	_values.push_back("~gr");

	_values.push_back("~c1");

	_values.push_back("~ix");

	_values.push_back("~h0");

	_values.push_back("~ab");

	_values.push_back("~g2");

	_values.push_back("~j7");

	_values.push_back("~d4");

	_values.push_back("~ed");

	_values.push_back("~ky");

	_values.push_back("~du");

	_values.push_back("~dg");

	_values.push_back("~de");

	_values.push_back("~gb");

	_values.push_back("~ej");

	_values.push_back("~fo");

	_values.push_back("~df");

	_values.push_back("~aw");

	_values.push_back("~ao");

	dawg_builder.Insert("\"GETALLPROVIDERSSERVICE\"", 0);

	dawg_builder.Insert("1/01/0001", 1);

	dawg_builder.Insert("1/1/1753", 2);

	dawg_builder.Insert("1005SA", 3);

	dawg_builder.Insert("1005TAS", 4);

	dawg_builder.Insert("12/31/9999", 5);

	dawg_builder.Insert("1578", 6);

	dawg_builder.Insert("1652", 7);

	dawg_builder.Insert("4184", 8);

	dawg_builder.Insert("5672", 9);

	dawg_builder.Insert("9B2E", 10);

	dawg_builder.Insert("A99F01138AF7", 11);

	dawg_builder.Insert("ACTION", 12);

	dawg_builder.Insert("ACTION`1", 13);

	dawg_builder.Insert("ACTIVELY", 14);

	dawg_builder.Insert("ALREADY", 15);

	dawg_builder.Insert("ALREADYCLOSEDEXCEPTION", 16);

	dawg_builder.Insert("AMQP", 17);

	dawg_builder.Insert("AMQPTCPENDPOINT", 18);

	dawg_builder.Insert("ARCHIVE", 19);

	dawg_builder.Insert("ARGUMENTS", 20);

	dawg_builder.Insert("ASYNC", 21);

	dawg_builder.Insert("ASYNCCLOSE", 22);

	dawg_builder.Insert("ASYNCRESULT", 23);

	dawg_builder.Insert("ASYNCWRITE", 24);

	dawg_builder.Insert("BASICPROPERTIES", 25);

	dawg_builder.Insert("BASICPUBLISH", 26);

	dawg_builder.Insert("BECAUSE", 27);

	dawg_builder.Insert("BEEN", 28);

	dawg_builder.Insert("BEHAVIOR", 29);

	dawg_builder.Insert("BETWEEN", 30);

	dawg_builder.Insert("BINARYBULKEXECUTION", 31);

	dawg_builder.Insert("BINARYBULKEXECUTIONSTRATEGY", 32);

	dawg_builder.Insert("BINDER", 33);

	dawg_builder.Insert("BODY", 34);

	dawg_builder.Insert("BOOLEAN", 35);

	dawg_builder.Insert("BREAKCONNECTION", 36);

	dawg_builder.Insert("BROKERUNREACHABLEEXCEPTION", 37);

	dawg_builder.Insert("BUFFER", 38);

	dawg_builder.Insert("BUFFEREDSTREAM", 39);

	dawg_builder.Insert("BULKACCUMULATOR`1", 40);

	dawg_builder.Insert("BULKADDORUPDATE", 41);

	dawg_builder.Insert("BULKCOPYHANDLER", 42);

	dawg_builder.Insert("BULKCOPYSIMPLERESULTSET", 43);

	dawg_builder.Insert("BUSINESS", 44);

	dawg_builder.Insert("BUSINESSCOMPONENTS", 45);

	dawg_builder.Insert("BUSINESSRULESINITILIZER", 46);

	dawg_builder.Insert("BUSINESSSERVICES", 47);

	dawg_builder.Insert("BUSINESSUNITNOTFOUNDEXCEPTION", 48);

	dawg_builder.Insert("BUSINESSUNITS", 49);

	dawg_builder.Insert("BWS1", 50);

	dawg_builder.Insert("BWS2", 51);

	dawg_builder.Insert("BWS3", 52);

	dawg_builder.Insert("BYTE", 53);

	dawg_builder.Insert("CALLERHASCONNECTIONLOCK", 54);

	dawg_builder.Insert("CANNOT", 55);

	dawg_builder.Insert("CAUGHT", 56);

	dawg_builder.Insert("CAUSE", 57);

	dawg_builder.Insert("CHANGEPASSWORD", 58);

	dawg_builder.Insert("CHANNEL", 59);

	dawg_builder.Insert("CHANNELCONFUGRATION", 60);

	dawg_builder.Insert("CHANNELCREATOR", 61);

	dawg_builder.Insert("CLASSID", 62);

	dawg_builder.Insert("CLIENT", 63);

	dawg_builder.Insert("CLOSE", 64);

	dawg_builder.Insert("CLOSED", 65);

	dawg_builder.Insert("CMDBEHAVIOR", 66);

	dawg_builder.Insert("CMDHANDLER", 67);

	dawg_builder.Insert("CODE", 68);

	dawg_builder.Insert("CODEEXECUTER", 69);

	dawg_builder.Insert("COLDSTART", 70);

	dawg_builder.Insert("COLDSTARTINSTRUMENTATION0", 71);

	dawg_builder.Insert("COLDSTARTINSTRUMENTATIONLOCAL", 72);

	dawg_builder.Insert("COLDSTARTINSTRUMENTATIONPARENTWORKER", 73);

	dawg_builder.Insert("COLLECTIONS", 74);

	dawg_builder.Insert("COMMAND", 75);

	dawg_builder.Insert("COMMANDBEHAVIOR", 76);

	dawg_builder.Insert("COMMON", 77);

	dawg_builder.Insert("COMPLETION", 78);

	dawg_builder.Insert("COMPONENT", 79);

	dawg_builder.Insert("COMPONENTNAME", 80);

	dawg_builder.Insert("CONCURRENT", 81);

	dawg_builder.Insert("CONCURRENTDICTIONARY`2", 82);

	dawg_builder.Insert("CONFIGURATIONS", 83);

	dawg_builder.Insert("CONNECT", 84);

	dawg_builder.Insert("CONNECTFAILUREEXCEPTION", 85);

	dawg_builder.Insert("CONNECTION", 86);

	dawg_builder.Insert("CONNECTIONCREATOR", 87);

	dawg_builder.Insert("CONNECTIONFACTORY", 88);

	dawg_builder.Insert("CONNECTIONKEY", 89);

	dawg_builder.Insert("CONNECTIVITY", 90);

	dawg_builder.Insert("CONNECTIVITYSERVICES", 91);

	dawg_builder.Insert("CONSUMER", 92);

	dawg_builder.Insert("CONTENTHEADERBASE", 93);

	dawg_builder.Insert("CONTEXT", 94);

	dawg_builder.Insert("CONTROLTRANSACTIONLOG", 95);

	dawg_builder.Insert("CONTROLTRANSACTIONLOGDAO", 96);

	dawg_builder.Insert("COULD", 97);

	dawg_builder.Insert("COUNT", 98);

	dawg_builder.Insert("CREATE", 99);

	dawg_builder.Insert("CREATECONNECTION", 100);

	dawg_builder.Insert("CREATEFRAMEHANDLER", 101);

	dawg_builder.Insert("CREDENTIALS", 102);

	dawg_builder.Insert("CTOR", 103);

	dawg_builder.Insert("CULTURE", 104);

	dawg_builder.Insert("DATA", 105);

	dawg_builder.Insert("DATAREADY", 106);

	dawg_builder.Insert("DATASTREAM", 107);

	dawg_builder.Insert("DATE", 108);

	dawg_builder.Insert("DATETIME", 109);

	dawg_builder.Insert("DBCOMMAND", 110);

	dawg_builder.Insert("DBCONNECTIONINTERNAL", 111);

	dawg_builder.Insert("DE852166", 112);

	dawg_builder.Insert("DECLINED", 113);

	dawg_builder.Insert("DEQUEPAGEOFMESSAGES", 114);

	dawg_builder.Insert("DEQUEUE", 115);

	dawg_builder.Insert("DEQUEUETIMEOUT", 116);

	dawg_builder.Insert("DESCRIBEPARAMETERENCRYPTIONREQUEST", 117);

	dawg_builder.Insert("DISPATCHERCHANNEL", 118);

	dawg_builder.Insert("DMS", 119);

	dawg_builder.Insert("DOCUMENT", 120);

	dawg_builder.Insert("DOESN", 121);

	dawg_builder.Insert("DOWNLOAD11", 122);

	dawg_builder.Insert("DOWNLOAD12", 123);

	dawg_builder.Insert("DOWNLOAD2", 124);

	dawg_builder.Insert("DOWNLOAD3", 125);

	dawg_builder.Insert("DOWNLOAD4", 126);

	dawg_builder.Insert("DOWNLOAD5", 127);

	dawg_builder.Insert("DOWNLOAD6", 128);

	dawg_builder.Insert("DOWNLOAD7", 129);

	dawg_builder.Insert("DOWNLOAD8", 130);

	dawg_builder.Insert("DOWNLOADRELAYWORKER", 131);

	dawg_builder.Insert("DPOS", 132);

	dawg_builder.Insert("DTOBASEBULKS", 133);

	dawg_builder.Insert("DTOSDATARESPONSEXMLWRITER", 134);

	dawg_builder.Insert("DURING", 135);

	dawg_builder.Insert("EF08", 136);

	dawg_builder.Insert("EITHER", 137);

	dawg_builder.Insert("ENDCONNECT", 138);

	dawg_builder.Insert("ENDOFSTREAMEXCEPTION", 139);

	dawg_builder.Insert("ENDPOINT", 140);

	dawg_builder.Insert("ENDPOINTS", 141);

	dawg_builder.Insert("ENLISTMENTOPTIONS", 142);

	dawg_builder.Insert("ENTITIES", 143);

	dawg_builder.Insert("ERROR", 144);

	dawg_builder.Insert("EXCEPTION", 145);

	dawg_builder.Insert("EXCEPTIONS", 146);

	dawg_builder.Insert("EXCHANGE", 147);

	dawg_builder.Insert("EXECUTE", 148);

	dawg_builder.Insert("EXECUTEDBDATAREADER", 149);

	dawg_builder.Insert("EXECUTEREADER", 150);

	dawg_builder.Insert("EXECUTESERVICE", 151);

	dawg_builder.Insert("EXECUTING", 152);

	dawg_builder.Insert("EXECUTION", 153);

	dawg_builder.Insert("EXISTING", 154);

	dawg_builder.Insert("EXISTS", 155);

	dawg_builder.Insert("EXPORT", 156);

	dawg_builder.Insert("FAILED", 157);

	dawg_builder.Insert("FAILURE", 158);

	dawg_builder.Insert("FAILUREHISTORY", 159);

	dawg_builder.Insert("FETCHALLORDERED>D", 160);

	dawg_builder.Insert("FLUSHWRITE", 161);

	dawg_builder.Insert("FORCIBLY", 162);

	dawg_builder.Insert("FOUND", 163);

	dawg_builder.Insert("FRAME", 164);

	dawg_builder.Insert("FRAMES", 165);

	dawg_builder.Insert("FRAMING", 166);

	dawg_builder.Insert("FROM", 167);

	dawg_builder.Insert("FRONTEND", 168);

	dawg_builder.Insert("FUNC`2", 169);

	dawg_builder.Insert("GENERAL", 170);

	dawg_builder.Insert("GET/CREATE", 171);

	dawg_builder.Insert("GETALLPROVIDERS", 172);

	dawg_builder.Insert("GETALLPROVIDERSSERVICE", 173);

	dawg_builder.Insert("GETBULKSFROMSTREAM>D", 174);

	dawg_builder.Insert("GETCHANNEL", 175);

	dawg_builder.Insert("GETDATAREADER", 176);

	dawg_builder.Insert("GETDTOSINBULK>D", 177);

	dawg_builder.Insert("GETORADD", 178);

	dawg_builder.Insert("GETORCREATECONNECTION", 179);

	dawg_builder.Insert("GETVALIDBUSINESSUNIT", 180);

	dawg_builder.Insert("GETVALIDMANDATORYDATE", 181);

	dawg_builder.Insert("HANDLERS", 182);

	dawg_builder.Insert("HEADER", 183);

	dawg_builder.Insert("HOST", 184);

	dawg_builder.Insert("HTTPRESPONSE", 185);

	dawg_builder.Insert("IASYNCRESULT", 186);

	dawg_builder.Insert("IBASICPROPERTIES", 187);

	dawg_builder.Insert("ICHANNELCONFUGRATION", 188);

	dawg_builder.Insert("IDBCOMMAND", 189);

	dawg_builder.Insert("IDOCUMENTREQUEST", 190);

	dawg_builder.Insert("IDOCUMENTRESPONSE", 191);

	dawg_builder.Insert("IENUMERABLE`1", 192);

	dawg_builder.Insert("ILIST`1", 193);

	dawg_builder.Insert("IMMEDIATE", 194);

	dawg_builder.Insert("IMODEL", 195);

	dawg_builder.Insert("IMPL", 196);

	dawg_builder.Insert("IMPORT", 197);

	dawg_builder.Insert("INITIALTRANS", 198);

	dawg_builder.Insert("INITIATED", 199);

	dawg_builder.Insert("INNER", 200);

	dawg_builder.Insert("INPUTDATAVALIDATIONEXTENSION", 201);

	dawg_builder.Insert("INPUTSTREAM", 202);

	dawg_builder.Insert("INRETRY", 203);

	dawg_builder.Insert("INSCHEMA", 204);

	dawg_builder.Insert("INT32", 205);

	dawg_builder.Insert("INTERRUPTED", 206);

	dawg_builder.Insert("INVALID", 207);

	dawg_builder.Insert("INVALIDDATAEXCEPTION", 208);

	dawg_builder.Insert("INVOCATION", 209);

	dawg_builder.Insert("INVOKE", 210);

	dawg_builder.Insert("IOEXCEPTION", 211);

	dawg_builder.Insert("IPROMOTIONALPRICE", 212);

	dawg_builder.Insert("IREQUEST", 213);

	dawg_builder.Insert("IREQUESTHANDLINGCONTEXT", 214);

	dawg_builder.Insert("ISCOMMANDPROC", 215);

	dawg_builder.Insert("ISECURITYIDENTIFIER", 216);

	dawg_builder.Insert("ITEM", 217);

	dawg_builder.Insert("LISTENER", 218);

	dawg_builder.Insert("LOADALL", 219);

	dawg_builder.Insert("LOCATION", 220);

	dawg_builder.Insert("LOCATIONATTRIBUTES/STORERANGE/START", 221);

	dawg_builder.Insert("LOCATIONATTRIBUTESTYPE", 222);

	dawg_builder.Insert("MACHINE", 223);

	dawg_builder.Insert("MADE", 224);

	dawg_builder.Insert("MAINTENANCE", 225);

	dawg_builder.Insert("MANAGEMENT", 226);

	dawg_builder.Insert("MANAGER", 227);

	dawg_builder.Insert("MANDATORY", 228);

	dawg_builder.Insert("MESSAGE", 229);

	dawg_builder.Insert("METHOD", 230);

	dawg_builder.Insert("METHODBASE", 231);

	dawg_builder.Insert("METHODID", 232);

	dawg_builder.Insert("MILLISECONDSTIMEOUT", 233);

	dawg_builder.Insert("MODEL", 234);

	dawg_builder.Insert("MODELBASE", 235);

	dawg_builder.Insert("MODELSEND", 236);

	dawg_builder.Insert("MOVENEXT", 237);

	dawg_builder.Insert("MUST", 238);

	dawg_builder.Insert("NETWORKSTREAM", 239);

	dawg_builder.Insert("NHIBERNATE", 240);

	dawg_builder.Insert("NONE", 241);

	dawg_builder.Insert("NOTIFICATIONREQUEST", 242);

	dawg_builder.Insert("NULL", 243);

	dawg_builder.Insert("OBJECT", 244);

	dawg_builder.Insert("OFFSET", 245);

	dawg_builder.Insert("ONERROR", 246);

	dawg_builder.Insert("OPERATION", 247);

	dawg_builder.Insert("OTHERS", 248);

	dawg_builder.Insert("OUTPUTWRITER", 249);

	dawg_builder.Insert("OVERFLOW", 250);

	dawg_builder.Insert("PARAMETERS", 251);

	dawg_builder.Insert("PARTS", 252);

	dawg_builder.Insert("PEER", 253);

	dawg_builder.Insert("PESSIMISTIC", 254);

	dawg_builder.Insert("POINT", 255);

	dawg_builder.Insert("POSID", 256);

	dawg_builder.Insert("PRICE", 257);

	dawg_builder.Insert("PRICEAPPROVALDAILYMAINTENANCEREQUEST", 258);

	dawg_builder.Insert("PRICEAPPROVALDAILYMAINTENANCESERVICE", 259);

	dawg_builder.Insert("PRICEWITHTRENDMAINTENANCESERVICE", 260);

	dawg_builder.Insert("PRICEWITHTRENDMAINTENANCESERVICERETALIX", 261);

	dawg_builder.Insert("PRIORITY", 262);

	dawg_builder.Insert("PRIORITYDOWNLOADOUTBOXPUBLISHER", 263);

	dawg_builder.Insert("PRIORITYQUEUE", 264);

	dawg_builder.Insert("PRIORITYQUEUEBACKWARDSCOMPATIBILITYOUTBOXCONSUMER", 265);

	dawg_builder.Insert("PRIORITYQUEUEDOWNLOAD0", 266);

	dawg_builder.Insert("PRIORITYQUEUEDOWNLOAD1", 267);

	dawg_builder.Insert("PRIORITYQUEUEDOWNLOAD2", 268);

	dawg_builder.Insert("PRIORITYQUEUEOUTBOXCONSUMER", 269);

	dawg_builder.Insert("PROCESS", 270);

	dawg_builder.Insert("PRODUCT", 271);

	dawg_builder.Insert("PRODUCTID", 272);

	dawg_builder.Insert("PRODUCTMAINTENANCESERVICE", 273);

	dawg_builder.Insert("PRODUCTMAINTENANCESERVICERETALIX", 274);

	dawg_builder.Insert("PRODUCTPRICES", 275);

	dawg_builder.Insert("PRODUCTTYPE", 276);

	dawg_builder.Insert("PRODUCTTYPES", 277);

	dawg_builder.Insert("PROIDERDTOSWRITER", 278);

	dawg_builder.Insert("PROMOPRICE", 279);

	dawg_builder.Insert("PROMOTION", 280);

	dawg_builder.Insert("PROMOTIONALPRICEBULKLOADER", 281);

	dawg_builder.Insert("PROTOCOLBASE", 282);

	dawg_builder.Insert("PROVIDERDTOSBUILDER", 283);

	dawg_builder.Insert("PROVIDERSDATA", 284);

	dawg_builder.Insert("PROVIDERSLEFT", 285);

	dawg_builder.Insert("PTRL", 286);

	dawg_builder.Insert("PUBLISH", 287);

	dawg_builder.Insert("PUBLISHINGBUCKETS", 288);

	dawg_builder.Insert("QUEUE", 289);

	dawg_builder.Insert("QUEUEINGBASICCONSUMER", 290);

	dawg_builder.Insert("QUEUEPROCESSINGBATCHSIZE", 291);

	dawg_builder.Insert("RABBIT", 292);

	dawg_builder.Insert("RABBITMQ", 293);

	dawg_builder.Insert("REACHABLE", 294);

	dawg_builder.Insert("REACHED", 295);

	dawg_builder.Insert("REASON", 296);

	dawg_builder.Insert("RECEIVED", 297);

	dawg_builder.Insert("RECOGNIZED", 298);

	dawg_builder.Insert("REFLECTION", 299);

	dawg_builder.Insert("REFUSED", 300);

	dawg_builder.Insert("REJECTING", 301);

	dawg_builder.Insert("RELAY", 302);

	dawg_builder.Insert("RELAYWORKER", 303);

	dawg_builder.Insert("REMOTE", 304);

	dawg_builder.Insert("REQUEST", 305);

	dawg_builder.Insert("RESPONSE", 306);

	dawg_builder.Insert("RESULT", 307);

	dawg_builder.Insert("RETALIX", 308);

	dawg_builder.Insert("RETURNSTREAM", 309);

	dawg_builder.Insert("ROUTINGKEY", 310);

	dawg_builder.Insert("RPCARRAY", 311);

	dawg_builder.Insert("RTIHTTPHANDLER", 312);

	dawg_builder.Insert("RUNBEHAVIOR", 313);

	dawg_builder.Insert("RUNEXECUTEREADER", 314);

	dawg_builder.Insert("RUNEXECUTEREADERTDS", 315);

	dawg_builder.Insert("RUNTIMEMETHODINFO", 316);

	dawg_builder.Insert("SAVE", 317);

	dawg_builder.Insert("SECURITYIDENTIFIER", 318);

	dawg_builder.Insert("SELLING", 319);

	dawg_builder.Insert("SERVICE", 320);

	dawg_builder.Insert("SERVICEBASE`2", 321);

	dawg_builder.Insert("SERVICEEXECUTION", 322);

	dawg_builder.Insert("SERVICEEXECUTIONHANDLERS", 323);

	dawg_builder.Insert("SERVICENAME", 324);

	dawg_builder.Insert("SERVICERUNNER", 325);

	dawg_builder.Insert("SESSION", 326);

	dawg_builder.Insert("SESSIONBASE", 327);

	dawg_builder.Insert("SHAREDQUEUE", 328);

	dawg_builder.Insert("SHAREDQUEUE`1", 329);

	dawg_builder.Insert("SINGLEPROVIDERPARAMETERS", 330);

	dawg_builder.Insert("SIZE", 331);

	dawg_builder.Insert("SOCKET", 332);

	dawg_builder.Insert("SOCKETEXCEPTION", 333);

	dawg_builder.Insert("SOCKETFACTORY", 334);

	dawg_builder.Insert("SOCKETFRAMEHANDLER", 335);

	dawg_builder.Insert("SOCKETS", 336);

	dawg_builder.Insert("SPECIFIED", 337);

	dawg_builder.Insert("SQLCLIENT", 338);

	dawg_builder.Insert("SQLCOMMAND", 339);

	dawg_builder.Insert("SQLCONNECTION", 340);

	dawg_builder.Insert("SQLDATAREADER", 341);

	dawg_builder.Insert("SQLDATETIME", 342);

	dawg_builder.Insert("SQLEXCEPTION", 343);

	dawg_builder.Insert("SQLNOTIFICATIONREQUEST", 344);

	dawg_builder.Insert("SQLRPC", 345);

	dawg_builder.Insert("SQLTYPEEXCEPTION", 346);

	dawg_builder.Insert("SQLTYPES", 347);

	dawg_builder.Insert("STACK", 348);

	dawg_builder.Insert("START", 349);

	dawg_builder.Insert("STARTINGPOSITION", 350);

	dawg_builder.Insert("STARTLISTENING", 351);

	dawg_builder.Insert("STARTPARAM", 352);

	dawg_builder.Insert("STARTRPC", 353);

	dawg_builder.Insert("STATE", 354);

	dawg_builder.Insert("STATEOBJ", 355);

	dawg_builder.Insert("STORE", 356);

	dawg_builder.Insert("STORERANGEPARTOFPRODUCTMAINTENANCESERVICE", 357);

	dawg_builder.Insert("STORESERVICES", 358);

	dawg_builder.Insert("STREAM", 359);

	dawg_builder.Insert("STREAMEDSERVICEBASE", 360);

	dawg_builder.Insert("STREAMINGCOMPATIBILITY", 361);

	dawg_builder.Insert("STRING", 362);

	dawg_builder.Insert("SYNC", 363);

	dawg_builder.Insert("SYSTEM", 364);

	dawg_builder.Insert("TARGET", 365);

	dawg_builder.Insert("TARGETVERSIONENTITYNAME", 366);

	dawg_builder.Insert("TASK", 367);

	dawg_builder.Insert("TASKCOMPLETIONSOURCE`1", 368);

	dawg_builder.Insert("TCPCLIENT", 369);

	dawg_builder.Insert("TDMARCHIVE", 370);

	dawg_builder.Insert("TDSEXECUTERPC", 371);

	dawg_builder.Insert("TDSPARSER", 372);

	dawg_builder.Insert("TDSPARSERSTATEOBJECT", 373);

	dawg_builder.Insert("TERMINATED", 374);

	dawg_builder.Insert("TEXT", 375);

	dawg_builder.Insert("THAT", 376);

	dawg_builder.Insert("THREADABORTEXCEPTION", 377);

	dawg_builder.Insert("THRESHOLD", 378);

	dawg_builder.Insert("THROWEXCEPTIONANDWARNING", 379);

	dawg_builder.Insert("TIMEOUT", 380);

	dawg_builder.Insert("TIMESPAN", 381);

	dawg_builder.Insert("TIMUSERUPDATEERROR", 382);

	dawg_builder.Insert("TIMUSERUPDATEEXCEPTION", 383);

	dawg_builder.Insert("TIMUSERUPDATEEXPORTMETHOD", 384);

	dawg_builder.Insert("TKEY", 385);

	dawg_builder.Insert("TRACE", 386);

	dawg_builder.Insert("TRANSACTION", 387);

	dawg_builder.Insert("TRANSACTIONEXCEPTION", 388);

	dawg_builder.Insert("TRANSACTIONS", 389);

	dawg_builder.Insert("TRANSMIT", 390);

	dawg_builder.Insert("TRANSPORT", 391);

	dawg_builder.Insert("TRANSPORTATIONCONSUMERBASE", 392);

	dawg_builder.Insert("TRANSPORTATIONCONSUMERS", 393);

	dawg_builder.Insert("TRANSPORTATIONEXCEPTION", 394);

	dawg_builder.Insert("TRANSPORTSTATISTICSPROVIDERBASE", 395);

	dawg_builder.Insert("TRYRUN", 396);

	dawg_builder.Insert("TYPE", 397);

	dawg_builder.Insert("UNABLE", 398);

	dawg_builder.Insert("UNIT", 399);

	dawg_builder.Insert("UNLOCKACCOUNT", 400);

	dawg_builder.Insert("UOWID", 401);

	dawg_builder.Insert("UPLOAD", 402);

	dawg_builder.Insert("UPLOAD0", 403);

	dawg_builder.Insert("UPLOAD1", 404);

	dawg_builder.Insert("UPLOAD2", 405);

	dawg_builder.Insert("UPLOAD3", 406);

	dawg_builder.Insert("UPLOAD4", 407);

	dawg_builder.Insert("UPLOAD5", 408);

	dawg_builder.Insert("UPLOADDEADLETTER", 409);

	dawg_builder.Insert("UPLOADDEADLETTERTRANSPORTATIONCONSUMER", 410);

	dawg_builder.Insert("UPLOADINBOXTRANSPORTATIONCONSUMER", 411);

	dawg_builder.Insert("UPLOADLOCALINBOX", 412);

	dawg_builder.Insert("USEDCACHE", 413);

	dawg_builder.Insert("USER", 414);

	dawg_builder.Insert("UTIL", 415);

	dawg_builder.Insert("VALIDATEBUSINESSUNITS", 416);

	dawg_builder.Insert("VALIDITY", 417);

	dawg_builder.Insert("VALUE", 418);

	dawg_builder.Insert("VALUEFACTORY", 419);

	dawg_builder.Insert("VALUEPATH", 420);

	dawg_builder.Insert("WAITFORCONFIRMSORDIE", 421);

	dawg_builder.Insert("WARMUP", 422);

	dawg_builder.Insert("WEBSERVICE", 423);

	dawg_builder.Insert("WERE", 424);

	dawg_builder.Insert("WHEN", 425);

	dawg_builder.Insert("WILL", 426);

	dawg_builder.Insert("WOOLWORTHS", 427);

	dawg_builder.Insert("WOWEXPORT", 428);

	dawg_builder.Insert("WRAPCLOSEINACTION", 429);

	dawg_builder.Insert("WRITE", 430);

	dawg_builder.Insert("WRITEDTOSDATA", 431);

	dawg_builder.Insert("WRITEFRAME", 432);

	dawg_builder.Insert("WRITEFRAMESET", 433);

	dawg_builder.Insert("WRITEFROMSNAPSHOT", 434);

	dawg_builder.Insert("WRITEPROVIDERSDATA", 435);

	dawg_builder.Insert("WRITERESPONSE", 436);

	dawg_builder.Insert("WRITERESPONSEIFSTREAMING", 437);

	dawg_builder.Insert("WRITEXML", 438);

	dawg_builder.Insert("WRONG", 439);

	dawg_builder.Insert("WRONG/INSUFFICIENT", 440);

	dawg_builder.Insert("XMLWRITER", 441);

	dawg_builder.Finish(&dawg);

	dawgdic::DictionaryBuilder::Build(dawg, &dawg_dic);

	_valuesReverse.push_back("SOCKETFACTORY");

	_valuesReverse.push_back("BROKERUNREACHABLEEXCEPTION");

	_valuesReverse.push_back("DMS");

	_valuesReverse.push_back("STRING");

	_valuesReverse.push_back("IASYNCRESULT");

	_valuesReverse.push_back("SOCKETS");

	_valuesReverse.push_back("CONNECTFAILUREEXCEPTION");

	_valuesReverse.push_back("BOOLEAN");

	_valuesReverse.push_back("ASYNCRESULT");

	_valuesReverse.push_back("BUSINESSCOMPONENTS");

	_valuesReverse.push_back("SQLCOMMAND");

	_valuesReverse.push_back("SQLCLIENT");

	_valuesReverse.push_back("FRONTEND");

	_valuesReverse.push_back("BECAUSE");

	_valuesReverse.push_back("PROTOCOLBASE");

	_valuesReverse.push_back("VALUEFACTORY");

	_valuesReverse.push_back("GETALLPROVIDERSSERVICE");

	_valuesReverse.push_back("COLLECTIONS");

	_valuesReverse.push_back("PROMOTIONALPRICEBULKLOADER");

	_valuesReverse.push_back("CONCURRENTDICTIONARY`2");

	_valuesReverse.push_back("WOOLWORTHS");

	_valuesReverse.push_back("ENDCONNECT");

	_valuesReverse.push_back("IMPL");

	_valuesReverse.push_back("CONNECT");

	_valuesReverse.push_back("PRIORITYQUEUE");

	_valuesReverse.push_back("CREATEFRAMEHANDLER");

	_valuesReverse.push_back("SOCKET");

	_valuesReverse.push_back("FUNC`2");

	_valuesReverse.push_back("INITIALTRANS");

	_valuesReverse.push_back("GETALLPROVIDERS");

	_valuesReverse.push_back("CONNECTIONCREATOR");

	_valuesReverse.push_back("TRANSPORTATIONEXCEPTION");

	_valuesReverse.push_back("SOCKETEXCEPTION");

	_valuesReverse.push_back("XMLWRITER");

	_valuesReverse.push_back("COMMANDBEHAVIOR");

	_valuesReverse.push_back("TRANSPORTATIONCONSUMERS");

	_valuesReverse.push_back("FAILED");

	_valuesReverse.push_back("INNER");

	_valuesReverse.push_back("STACK");

	_valuesReverse.push_back("TRACE");

	_valuesReverse.push_back("RUNBEHAVIOR");

	_valuesReverse.push_back("WRONG/INSUFFICIENT");

	_valuesReverse.push_back("CONNECTIONKEY");

	_valuesReverse.push_back("COMPONENTNAME");

	_valuesReverse.push_back("STORESERVICES");

	_valuesReverse.push_back("RUNEXECUTEREADER");

	_valuesReverse.push_back("COMMON");

	_valuesReverse.push_back("TARGET");

	_valuesReverse.push_back("IBASICPROPERTIES");

	_valuesReverse.push_back("EXECUTION");

	_valuesReverse.push_back("BASICPROPERTIES");

	_valuesReverse.push_back("SERVICERUNNER");

	_valuesReverse.push_back("QUEUEPROCESSINGBATCHSIZE");

	_valuesReverse.push_back("EXECUTEREADER");

	_valuesReverse.push_back("CONFIGURATIONS");

	_valuesReverse.push_back("SINGLEPROVIDERPARAMETERS");

	_valuesReverse.push_back("CONCURRENT");

	_valuesReverse.push_back("TASKCOMPLETIONSOURCE`1");

	_valuesReverse.push_back("SPECIFIED");

	_valuesReverse.push_back("ENDPOINTS");

	_valuesReverse.push_back("REACHABLE");

	_valuesReverse.push_back("IENUMERABLE`1");

	_valuesReverse.push_back("DATA");

	_valuesReverse.push_back("CONNECTIVITYSERVICES");

	_valuesReverse.push_back("CREDENTIALS");

	_valuesReverse.push_back("GETORADD");

	_valuesReverse.push_back("ACTIVELY");

	_valuesReverse.push_back("STARTLISTENING");

	_valuesReverse.push_back("FRAMING");

	_valuesReverse.push_back("RETURNSTREAM");

	_valuesReverse.push_back("PRIORITYDOWNLOADOUTBOXPUBLISHER");

	_valuesReverse.push_back("ERROR");

	_valuesReverse.push_back("STORE");

	_valuesReverse.push_back("POSID");

	_valuesReverse.push_back("DESCRIBEPARAMETERENCRYPTIONREQUEST");

	_valuesReverse.push_back("PROIDERDTOSWRITER");

	_valuesReverse.push_back("REFUSED");

	_valuesReverse.push_back("MACHINE");

	_valuesReverse.push_back("CMDBEHAVIOR");

	_valuesReverse.push_back("RABBITMQ");

	_valuesReverse.push_back("CTOR");

	_valuesReverse.push_back("WERE");

	_valuesReverse.push_back("TKEY");

	_valuesReverse.push_back("5672");

	_valuesReverse.push_back("MADE");

	_valuesReverse.push_back("NONE");

	_valuesReverse.push_back("PROVIDERDTOSBUILDER");

	_valuesReverse.push_back("EXECUTEDBDATAREADER");

	_valuesReverse.push_back("NOTIFICATIONREQUEST");

	_valuesReverse.push_back("SERVICEEXECUTION");

	_valuesReverse.push_back("DTOSDATARESPONSEXMLWRITER");

	_valuesReverse.push_back("PRIORITYQUEUEBACKWARDSCOMPATIBILITYOUTBOXCONSUMER");

	_valuesReverse.push_back("MOVENEXT");

	_valuesReverse.push_back("COULD");

	_valuesReverse.push_back("TARGETVERSIONENTITYNAME");

	_valuesReverse.push_back("QUEUEINGBASICCONSUMER");

	_valuesReverse.push_back("GETCHANNEL");

	_valuesReverse.push_back("ENDOFSTREAMEXCEPTION");

	_valuesReverse.push_back("SQLNOTIFICATIONREQUEST");

	_valuesReverse.push_back("MODELBASE");

	_valuesReverse.push_back("METHOD");

	_valuesReverse.push_back("BASICPUBLISH");

	_valuesReverse.push_back("TDSPARSERSTATEOBJECT");

	_valuesReverse.push_back("LISTENER");

	_valuesReverse.push_back("EITHER");

	_valuesReverse.push_back("DEQUEPAGEOFMESSAGES");

	_valuesReverse.push_back("MILLISECONDSTIMEOUT");

	_valuesReverse.push_back("ASYNCWRITE");

	_valuesReverse.push_back("COMPLETION");

	_valuesReverse.push_back("PROMOPRICE");

	_valuesReverse.push_back("GETBULKSFROMSTREAM>D");

	_valuesReverse.push_back("ISECURITYIDENTIFIER");

	_valuesReverse.push_back("RUNEXECUTEREADERTDS");

	_valuesReverse.push_back("CAUGHT");

	_valuesReverse.push_back("RETALIX");

	_valuesReverse.push_back("PRIORITYQUEUEDOWNLOAD0");

	_valuesReverse.push_back("INRETRY");

	_valuesReverse.push_back("SHAREDQUEUE`1");

	_valuesReverse.push_back("TDSPARSER");

	_valuesReverse.push_back("WRITE");

	_valuesReverse.push_back("CLOSED");

	_valuesReverse.push_back("QUEUE");

	_valuesReverse.push_back("START");

	_valuesReverse.push_back("PROVIDERSDATA");

	_valuesReverse.push_back("SECURITYIDENTIFIER");

	_valuesReverse.push_back("GENERAL");

	_valuesReverse.push_back("ROUTINGKEY");

	_valuesReverse.push_back("PROMOTION");

	_valuesReverse.push_back("WRITEPROVIDERSDATA");

	_valuesReverse.push_back("WRONG");

	_valuesReverse.push_back("WRITEFROMSNAPSHOT");

	_valuesReverse.push_back("IPROMOTIONALPRICE");

	_valuesReverse.push_back("BULKACCUMULATOR`1");

	_valuesReverse.push_back("FETCHALLORDERED>D");

	_valuesReverse.push_back("TASK");

	_valuesReverse.push_back("BEHAVIOR");

	_valuesReverse.push_back("STARTINGPOSITION");

	_valuesReverse.push_back("SQLTYPEEXCEPTION");

	_valuesReverse.push_back("DURING");

	_valuesReverse.push_back("PRIORITYQUEUEOUTBOXCONSUMER");

	_valuesReverse.push_back("MAINTENANCE");

	_valuesReverse.push_back("NETWORKSTREAM");

	_valuesReverse.push_back("GETDTOSINBULK>D");

	_valuesReverse.push_back("STORERANGEPARTOFPRODUCTMAINTENANCESERVICE");

	_valuesReverse.push_back("WRITEFRAMESET");

	_valuesReverse.push_back("EXCHANGE");

	_valuesReverse.push_back("SQLDATAREADER");

	_valuesReverse.push_back("BYTE");

	_valuesReverse.push_back("EXECUTESERVICE");

	_valuesReverse.push_back("CREATECONNECTION");

	_valuesReverse.push_back("CONTENTHEADERBASE");

	_valuesReverse.push_back("BUSINESSUNITNOTFOUNDEXCEPTION");

	_valuesReverse.push_back("IDBCOMMAND");

	_valuesReverse.push_back("THREADABORTEXCEPTION");

	_valuesReverse.push_back("BINARYBULKEXECUTIONSTRATEGY");

	_valuesReverse.push_back("DOWNLOADRELAYWORKER");

	_valuesReverse.push_back("STARTPARAM");

	_valuesReverse.push_back("12/31/9999");

	_valuesReverse.push_back("PUBLISHINGBUCKETS");

	_valuesReverse.push_back("BUSINESSUNITS");

	_valuesReverse.push_back("PROVIDERSLEFT");

	_valuesReverse.push_back("GETDATAREADER");

	_valuesReverse.push_back("WRITEDTOSDATA");

	_valuesReverse.push_back("TDSEXECUTERPC");

	_valuesReverse.push_back("ISCOMMANDPROC");

	_valuesReverse.push_back("GET/CREATE");

	_valuesReverse.push_back("UPLOADINBOXTRANSPORTATIONCONSUMER");

	_valuesReverse.push_back("HTTPRESPONSE");

	_valuesReverse.push_back("WRITERESPONSEIFSTREAMING");

	_valuesReverse.push_back("RESPONSE");

	_valuesReverse.push_back("SHAREDQUEUE");

	_valuesReverse.push_back("\"GETALLPROVIDERSSERVICE\"");

	_valuesReverse.push_back("DTOBASEBULKS");

	_valuesReverse.push_back("PRIORITYQUEUEDOWNLOAD2");

	_valuesReverse.push_back("UPLOADLOCALINBOX");

	_valuesReverse.push_back("RELAYWORKER");

	_valuesReverse.push_back("COMPONENT");

	_valuesReverse.push_back("PRIORITYQUEUEDOWNLOAD1");

	_valuesReverse.push_back("SERVICENAME");

	_valuesReverse.push_back("MANDATORY");

	_valuesReverse.push_back("STREAMINGCOMPATIBILITY");

	_valuesReverse.push_back("SQLDATETIME");

	_valuesReverse.push_back("PRICEWITHTRENDMAINTENANCESERVICE");

	_valuesReverse.push_back("TRANSACTIONEXCEPTION");

	_valuesReverse.push_back("AMQPTCPENDPOINT");

	_valuesReverse.push_back("BUFFER");

	_valuesReverse.push_back("RTIHTTPHANDLER");

	_valuesReverse.push_back("REMOTE");

	_valuesReverse.push_back("OFFSET");

	_valuesReverse.push_back("BINARYBULKEXECUTION");

	_valuesReverse.push_back("LOCATIONATTRIBUTESTYPE");

	_valuesReverse.push_back("BETWEEN");

	_valuesReverse.push_back("SESSIONBASE");

	_valuesReverse.push_back("IOEXCEPTION");

	_valuesReverse.push_back("DISPATCHERCHANNEL");

	_valuesReverse.push_back("STREAMEDSERVICEBASE");

	_valuesReverse.push_back("BODY");

	_valuesReverse.push_back("EXISTING");

	_valuesReverse.push_back("FORCIBLY");

	_valuesReverse.push_back("USEDCACHE");

	_valuesReverse.push_back("DBCOMMAND");

	_valuesReverse.push_back("CHANNEL");

	_valuesReverse.push_back("CONSUMER");

	_valuesReverse.push_back("IDOCUMENTRESPONSE");

	_valuesReverse.push_back("STATEOBJ");

	_valuesReverse.push_back("BUFFEREDSTREAM");

	_valuesReverse.push_back("IREQUEST");

	_valuesReverse.push_back("ILIST`1");

	_valuesReverse.push_back("WRITEXML");

	_valuesReverse.push_back("RPCARRAY");

	_valuesReverse.push_back("SQLTYPES");

	_valuesReverse.push_back("STARTRPC");

	_valuesReverse.push_back("1/1/1753");

	_valuesReverse.push_back("INSCHEMA");

	_valuesReverse.push_back("OVERFLOW");

	_valuesReverse.push_back("REQUEST");

	_valuesReverse.push_back("DEQUEUE");

	_valuesReverse.push_back("CREATE");

	_valuesReverse.push_back("PRODUCT");

	_valuesReverse.push_back("SOCKETFRAMEHANDLER");

	_valuesReverse.push_back("COMMAND");

	_valuesReverse.push_back("UTIL");

	_valuesReverse.push_back("WOWEXPORT");

	_valuesReverse.push_back("PRODUCTPRICES");

	_valuesReverse.push_back("PESSIMISTIC");

	_valuesReverse.push_back("PUBLISH");

	_valuesReverse.push_back("COLDSTARTINSTRUMENTATIONLOCAL");

	_valuesReverse.push_back("TIMUSERUPDATEERROR");

	_valuesReverse.push_back("SYNC");

	_valuesReverse.push_back("PRODUCTMAINTENANCESERVICERETALIX");

	_valuesReverse.push_back("WRITERESPONSE");

	_valuesReverse.push_back("RESULT");

	_valuesReverse.push_back("PRICEWITHTRENDMAINTENANCESERVICERETALIX");

	_valuesReverse.push_back("OUTPUTWRITER");

	_valuesReverse.push_back("METHODBASE");

	_valuesReverse.push_back("TRANSPORT");

	_valuesReverse.push_back("SQLRPC");

	_valuesReverse.push_back("FLUSHWRITE");

	_valuesReverse.push_back("PRODUCTTYPE");

	_valuesReverse.push_back("TIMUSERUPDATEEXPORTMETHOD");

	_valuesReverse.push_back("INPUTSTREAM");

	_valuesReverse.push_back("MODELSEND");

	_valuesReverse.push_back("IMMEDIATE");

	_valuesReverse.push_back("COLDSTARTINSTRUMENTATION0");

	_valuesReverse.push_back("PRODUCTMAINTENANCESERVICE");

	_valuesReverse.push_back("COLDSTART");

	_valuesReverse.push_back("WEBSERVICE");

	_valuesReverse.push_back("ASYNC");

	_valuesReverse.push_back("TERMINATED");

	_valuesReverse.push_back("RECOGNIZED");

	_valuesReverse.push_back("TRANSMIT");

	_valuesReverse.push_back("TIMUSERUPDATEEXCEPTION");

	_valuesReverse.push_back("SIZE");

	_valuesReverse.push_back("HOST");

	_valuesReverse.push_back("CLIENT");

	_valuesReverse.push_back("WILL");

	_valuesReverse.push_back("DOWNLOAD2");

	_valuesReverse.push_back("DOWNLOAD4");

	_valuesReverse.push_back("PRICE");

	_valuesReverse.push_back("PARTS");

	_valuesReverse.push_back("RECEIVED");

	_valuesReverse.push_back("DECLINED");

	_valuesReverse.push_back("TRANSACTION");

	_valuesReverse.push_back("LOCATIONATTRIBUTES/STORERANGE/START");

	_valuesReverse.push_back("MUST");

	_valuesReverse.push_back("PROCESS");

	_valuesReverse.push_back("UNABLE");

	_valuesReverse.push_back("HEADER");

	_valuesReverse.push_back("IMODEL");

	_valuesReverse.push_back("FRAMES");

	_valuesReverse.push_back("VALIDATEBUSINESSUNITS");

	_valuesReverse.push_back("EXECUTE");

	_valuesReverse.push_back("GETVALIDBUSINESSUNIT");

	_valuesReverse.push_back("BULKADDORUPDATE");

	_valuesReverse.push_back("STREAM");

	_valuesReverse.push_back("UPLOADDEADLETTERTRANSPORTATIONCONSUMER");

	_valuesReverse.push_back("BUSINESS");

	_valuesReverse.push_back("UPLOAD");

	_valuesReverse.push_back("COLDSTARTINSTRUMENTATIONPARENTWORKER");

	_valuesReverse.push_back("RELAY");

	_valuesReverse.push_back("PRICEAPPROVALDAILYMAINTENANCESERVICE");

	_valuesReverse.push_back("SERVICE");

	_valuesReverse.push_back("PRODUCTTYPES");

	_valuesReverse.push_back("UPLOADDEADLETTER");

	_valuesReverse.push_back("UNLOCKACCOUNT");

	_valuesReverse.push_back("CANNOT");

	_valuesReverse.push_back("DOWNLOAD11");

	_valuesReverse.push_back("VALIDITY");

	_valuesReverse.push_back("DPOS");

	_valuesReverse.push_back("CHANNELCREATOR");

	_valuesReverse.push_back("GETVALIDMANDATORYDATE");

	_valuesReverse.push_back("OBJECT");

	_valuesReverse.push_back("CONTROLTRANSACTIONLOG");

	_valuesReverse.push_back("CODE");

	_valuesReverse.push_back("1652");

	_valuesReverse.push_back("INVALIDDATAEXCEPTION");

	_valuesReverse.push_back("EXISTS");

	_valuesReverse.push_back("USER");

	_valuesReverse.push_back("TRANSPORTSTATISTICSPROVIDERBASE");

	_valuesReverse.push_back("ENTITIES");

	_valuesReverse.push_back("UPLOAD4");

	_valuesReverse.push_back("UPLOAD3");

	_valuesReverse.push_back("UPLOAD0");

	_valuesReverse.push_back("UPLOAD1");

	_valuesReverse.push_back("DOWNLOAD12");

	_valuesReverse.push_back("UPLOAD5");

	_valuesReverse.push_back("UPLOAD2");

	_valuesReverse.push_back("DOWNLOAD5");

	_valuesReverse.push_back("DOWNLOAD7");

	_valuesReverse.push_back("CONNECTIVITY");

	_valuesReverse.push_back("DOWNLOAD8");

	_valuesReverse.push_back("UNIT");

	_valuesReverse.push_back("DOWNLOAD3");

	_valuesReverse.push_back("DOWNLOAD6");

	_valuesReverse.push_back("INPUTDATAVALIDATIONEXTENSION");

	_valuesReverse.push_back("BUSINESSRULESINITILIZER");

	_valuesReverse.push_back("MODEL");

	_valuesReverse.push_back("LOCATION");

	_valuesReverse.push_back("IMPORT");

	_valuesReverse.push_back("BULKCOPYSIMPLERESULTSET");

	_valuesReverse.push_back("FOUND");

	_valuesReverse.push_back("PRICEAPPROVALDAILYMAINTENANCEREQUEST");

	_valuesReverse.push_back("WHEN");

	_valuesReverse.push_back("FAILUREHISTORY");

	_valuesReverse.push_back("SYSTEM");

	_valuesReverse.push_back("ALREADYCLOSEDEXCEPTION");

	_valuesReverse.push_back("DBCONNECTIONINTERNAL");

	_valuesReverse.push_back("REFLECTION");

	_valuesReverse.push_back("PRIORITY");

	_valuesReverse.push_back("BWS3");

	_valuesReverse.push_back("BWS1");

	_valuesReverse.push_back("FAILURE");

	_valuesReverse.push_back("WRAPCLOSEINACTION");

	_valuesReverse.push_back("WAITFORCONFIRMSORDIE");

	_valuesReverse.push_back("FROM");

	_valuesReverse.push_back("CONTROLTRANSACTIONLOGDAO");

	_valuesReverse.push_back("ENLISTMENTOPTIONS");

	_valuesReverse.push_back("1005SA");

	_valuesReverse.push_back("CHANGEPASSWORD");

	_valuesReverse.push_back("POINT");

	_valuesReverse.push_back("DOESN");

	_valuesReverse.push_back("DATETIME");

	_valuesReverse.push_back("SQLEXCEPTION");

	_valuesReverse.push_back("THROWEXCEPTIONANDWARNING");

	_valuesReverse.push_back("CALLERHASCONNECTIONLOCK");

	_valuesReverse.push_back("1005TAS");

	_valuesReverse.push_back("SERVICEEXECUTIONHANDLERS");

	_valuesReverse.push_back("BULKCOPYHANDLER");

	_valuesReverse.push_back("IREQUESTHANDLINGCONTEXT");

	_valuesReverse.push_back("SQLCONNECTION");

	_valuesReverse.push_back("RUNTIMEMETHODINFO");

	_valuesReverse.push_back("THRESHOLD");

	_valuesReverse.push_back("REJECTING");

	_valuesReverse.push_back("DOCUMENT");

	_valuesReverse.push_back("OTHERS");

	_valuesReverse.push_back("THAT");

	_valuesReverse.push_back("PARAMETERS");

	_valuesReverse.push_back("NHIBERNATE");

	_valuesReverse.push_back("MESSAGE");

	_valuesReverse.push_back("EXCEPTION");

	_valuesReverse.push_back("TDMARCHIVE");

	_valuesReverse.push_back("INVALID");

	_valuesReverse.push_back("ARCHIVE");

	_valuesReverse.push_back("A99F01138AF7");

	_valuesReverse.push_back("ASYNCCLOSE");

	_valuesReverse.push_back("1578");

	_valuesReverse.push_back("SESSION");

	_valuesReverse.push_back("FRAME");

	_valuesReverse.push_back("INTERRUPTED");

	_valuesReverse.push_back("OPERATION");

	_valuesReverse.push_back("REACHED");

	_valuesReverse.push_back("VALUE");

	_valuesReverse.push_back("ARGUMENTS");

	_valuesReverse.push_back("DEQUEUETIMEOUT");

	_valuesReverse.push_back("BREAKCONNECTION");

	_valuesReverse.push_back("CODEEXECUTER");

	_valuesReverse.push_back("IDOCUMENTREQUEST");

	_valuesReverse.push_back("CMDHANDLER");

	_valuesReverse.push_back("DATASTREAM");

	_valuesReverse.push_back("PRODUCTID");

	_valuesReverse.push_back("TRANSACTIONS");

	_valuesReverse.push_back("1/01/0001");

	_valuesReverse.push_back("INVOCATION");

	_valuesReverse.push_back("VALUEPATH");

	_valuesReverse.push_back("PTRL");

	_valuesReverse.push_back("HANDLERS");

	_valuesReverse.push_back("BWS2");

	_valuesReverse.push_back("SERVICEBASE`2");

	_valuesReverse.push_back("DATAREADY");

	_valuesReverse.push_back("COUNT");

	_valuesReverse.push_back("MANAGEMENT");

	_valuesReverse.push_back("UOWID");

	_valuesReverse.push_back("EXPORT");

	_valuesReverse.push_back("WRITEFRAME");

	_valuesReverse.push_back("ICHANNELCONFUGRATION");

	_valuesReverse.push_back("BEEN");

	_valuesReverse.push_back("CAUSE");

	_valuesReverse.push_back("CLOSE");

	_valuesReverse.push_back("ITEM");

	_valuesReverse.push_back("EF08");

	_valuesReverse.push_back("TEXT");

	_valuesReverse.push_back("9B2E");

	_valuesReverse.push_back("4184");

	_valuesReverse.push_back("PEER");

	_valuesReverse.push_back("ACTION`1");

	_valuesReverse.push_back("LOADALL");

	_valuesReverse.push_back("ACTION");

	_valuesReverse.push_back("TRYRUN");

	_valuesReverse.push_back("SAVE");

	_valuesReverse.push_back("TYPE");

	_valuesReverse.push_back("INITIATED");

	_valuesReverse.push_back("EXECUTING");

	_valuesReverse.push_back("MANAGER");

	_valuesReverse.push_back("BINDER");

	_valuesReverse.push_back("WARMUP");

	_valuesReverse.push_back("SELLING");

	_valuesReverse.push_back("CULTURE");

	_valuesReverse.push_back("ONERROR");

	_valuesReverse.push_back("METHODID");

	_valuesReverse.push_back("DE852166");

	_valuesReverse.push_back("AMQP");

	_valuesReverse.push_back("TIMESPAN");

	_valuesReverse.push_back("STATE");

	_valuesReverse.push_back("CONTEXT");

	_valuesReverse.push_back("DATE");

	_valuesReverse.push_back("INVOKE");

	_valuesReverse.push_back("CLASSID");

	_valuesReverse.push_back("ALREADY");

	_valuesReverse.push_back("REASON");

	_valuesReverse.push_back("NULL");

	_valuesReverse.push_back("CHANNELCONFUGRATION");

	_valuesReverse.push_back("RABBIT");

	_valuesReverse.push_back("TRANSPORTATIONCONSUMERBASE");

	_valuesReverse.push_back("CONNECTIONFACTORY");

	_valuesReverse.push_back("TIMEOUT");

	_valuesReverse.push_back("ENDPOINT");

	_valuesReverse.push_back("INT32");

	_valuesReverse.push_back("BUSINESSSERVICES");

	_valuesReverse.push_back("GETORCREATECONNECTION");

	_valuesReverse.push_back("EXCEPTIONS");

	_valuesReverse.push_back("CONNECTION");

	_valuesReverse.push_back("TCPCLIENT");

	dawg_builderReverse.Insert("~0", 0);

	dawg_builderReverse.Insert("~1", 1);

	dawg_builderReverse.Insert("~2", 2);

	dawg_builderReverse.Insert("~3", 3);

	dawg_builderReverse.Insert("~4", 4);

	dawg_builderReverse.Insert("~5", 5);

	dawg_builderReverse.Insert("~6", 6);

	dawg_builderReverse.Insert("~7", 7);

	dawg_builderReverse.Insert("~8", 8);

	dawg_builderReverse.Insert("~a", 9);

	dawg_builderReverse.Insert("~a0", 10);

	dawg_builderReverse.Insert("~a1", 11);

	dawg_builderReverse.Insert("~a2", 12);

	dawg_builderReverse.Insert("~a3", 13);

	dawg_builderReverse.Insert("~a4", 14);

	dawg_builderReverse.Insert("~a5", 15);

	dawg_builderReverse.Insert("~a6", 16);

	dawg_builderReverse.Insert("~a7", 17);

	dawg_builderReverse.Insert("~a8", 18);

	dawg_builderReverse.Insert("~aa", 19);

	dawg_builderReverse.Insert("~ab", 20);

	dawg_builderReverse.Insert("~ac", 21);

	dawg_builderReverse.Insert("~ad", 22);

	dawg_builderReverse.Insert("~ae", 23);

	dawg_builderReverse.Insert("~af", 24);

	dawg_builderReverse.Insert("~ag", 25);

	dawg_builderReverse.Insert("~ah", 26);

	dawg_builderReverse.Insert("~ai", 27);

	dawg_builderReverse.Insert("~aj", 28);

	dawg_builderReverse.Insert("~ak", 29);

	dawg_builderReverse.Insert("~al", 30);

	dawg_builderReverse.Insert("~am", 31);

	dawg_builderReverse.Insert("~an", 32);

	dawg_builderReverse.Insert("~ao", 33);

	dawg_builderReverse.Insert("~ap", 34);

	dawg_builderReverse.Insert("~aq", 35);

	dawg_builderReverse.Insert("~ar", 36);

	dawg_builderReverse.Insert("~as", 37);

	dawg_builderReverse.Insert("~at", 38);

	dawg_builderReverse.Insert("~au", 39);

	dawg_builderReverse.Insert("~av", 40);

	dawg_builderReverse.Insert("~aw", 41);

	dawg_builderReverse.Insert("~ax", 42);

	dawg_builderReverse.Insert("~ay", 43);

	dawg_builderReverse.Insert("~b", 44);

	dawg_builderReverse.Insert("~b0", 45);

	dawg_builderReverse.Insert("~b1", 46);

	dawg_builderReverse.Insert("~b2", 47);

	dawg_builderReverse.Insert("~b3", 48);

	dawg_builderReverse.Insert("~b4", 49);

	dawg_builderReverse.Insert("~b5", 50);

	dawg_builderReverse.Insert("~b6", 51);

	dawg_builderReverse.Insert("~b7", 52);

	dawg_builderReverse.Insert("~b8", 53);

	dawg_builderReverse.Insert("~ba", 54);

	dawg_builderReverse.Insert("~bb", 55);

	dawg_builderReverse.Insert("~bc", 56);

	dawg_builderReverse.Insert("~bd", 57);

	dawg_builderReverse.Insert("~be", 58);

	dawg_builderReverse.Insert("~bf", 59);

	dawg_builderReverse.Insert("~bg", 60);

	dawg_builderReverse.Insert("~bh", 61);

	dawg_builderReverse.Insert("~bi", 62);

	dawg_builderReverse.Insert("~bj", 63);

	dawg_builderReverse.Insert("~bk", 64);

	dawg_builderReverse.Insert("~bl", 65);

	dawg_builderReverse.Insert("~bm", 66);

	dawg_builderReverse.Insert("~bn", 67);

	dawg_builderReverse.Insert("~bo", 68);

	dawg_builderReverse.Insert("~bp", 69);

	dawg_builderReverse.Insert("~bq", 70);

	dawg_builderReverse.Insert("~br", 71);

	dawg_builderReverse.Insert("~bs", 72);

	dawg_builderReverse.Insert("~bt", 73);

	dawg_builderReverse.Insert("~bu", 74);

	dawg_builderReverse.Insert("~bv", 75);

	dawg_builderReverse.Insert("~bw", 76);

	dawg_builderReverse.Insert("~bx", 77);

	dawg_builderReverse.Insert("~by", 78);

	dawg_builderReverse.Insert("~c", 79);

	dawg_builderReverse.Insert("~c0", 80);

	dawg_builderReverse.Insert("~c1", 81);

	dawg_builderReverse.Insert("~c2", 82);

	dawg_builderReverse.Insert("~c3", 83);

	dawg_builderReverse.Insert("~c4", 84);

	dawg_builderReverse.Insert("~c5", 85);

	dawg_builderReverse.Insert("~c6", 86);

	dawg_builderReverse.Insert("~c7", 87);

	dawg_builderReverse.Insert("~c8", 88);

	dawg_builderReverse.Insert("~ca", 89);

	dawg_builderReverse.Insert("~cb", 90);

	dawg_builderReverse.Insert("~cc", 91);

	dawg_builderReverse.Insert("~cd", 92);

	dawg_builderReverse.Insert("~ce", 93);

	dawg_builderReverse.Insert("~cf", 94);

	dawg_builderReverse.Insert("~cg", 95);

	dawg_builderReverse.Insert("~ch", 96);

	dawg_builderReverse.Insert("~ci", 97);

	dawg_builderReverse.Insert("~cj", 98);

	dawg_builderReverse.Insert("~ck", 99);

	dawg_builderReverse.Insert("~cl", 100);

	dawg_builderReverse.Insert("~cm", 101);

	dawg_builderReverse.Insert("~cn", 102);

	dawg_builderReverse.Insert("~co", 103);

	dawg_builderReverse.Insert("~cp", 104);

	dawg_builderReverse.Insert("~cq", 105);

	dawg_builderReverse.Insert("~cr", 106);

	dawg_builderReverse.Insert("~cs", 107);

	dawg_builderReverse.Insert("~ct", 108);

	dawg_builderReverse.Insert("~cu", 109);

	dawg_builderReverse.Insert("~cv", 110);

	dawg_builderReverse.Insert("~cw", 111);

	dawg_builderReverse.Insert("~cx", 112);

	dawg_builderReverse.Insert("~cy", 113);

	dawg_builderReverse.Insert("~d", 114);

	dawg_builderReverse.Insert("~d0", 115);

	dawg_builderReverse.Insert("~d1", 116);

	dawg_builderReverse.Insert("~d2", 117);

	dawg_builderReverse.Insert("~d3", 118);

	dawg_builderReverse.Insert("~d4", 119);

	dawg_builderReverse.Insert("~d5", 120);

	dawg_builderReverse.Insert("~d6", 121);

	dawg_builderReverse.Insert("~d7", 122);

	dawg_builderReverse.Insert("~d8", 123);

	dawg_builderReverse.Insert("~da", 124);

	dawg_builderReverse.Insert("~db", 125);

	dawg_builderReverse.Insert("~dc", 126);

	dawg_builderReverse.Insert("~dd", 127);

	dawg_builderReverse.Insert("~de", 128);

	dawg_builderReverse.Insert("~df", 129);

	dawg_builderReverse.Insert("~dg", 130);

	dawg_builderReverse.Insert("~dh", 131);

	dawg_builderReverse.Insert("~di", 132);

	dawg_builderReverse.Insert("~dj", 133);

	dawg_builderReverse.Insert("~dk", 134);

	dawg_builderReverse.Insert("~dl", 135);

	dawg_builderReverse.Insert("~dm", 136);

	dawg_builderReverse.Insert("~dn", 137);

	dawg_builderReverse.Insert("~do", 138);

	dawg_builderReverse.Insert("~dp", 139);

	dawg_builderReverse.Insert("~dq", 140);

	dawg_builderReverse.Insert("~dr", 141);

	dawg_builderReverse.Insert("~ds", 142);

	dawg_builderReverse.Insert("~dt", 143);

	dawg_builderReverse.Insert("~du", 144);

	dawg_builderReverse.Insert("~dv", 145);

	dawg_builderReverse.Insert("~dw", 146);

	dawg_builderReverse.Insert("~dx", 147);

	dawg_builderReverse.Insert("~dy", 148);

	dawg_builderReverse.Insert("~e", 149);

	dawg_builderReverse.Insert("~e0", 150);

	dawg_builderReverse.Insert("~e1", 151);

	dawg_builderReverse.Insert("~e2", 152);

	dawg_builderReverse.Insert("~e3", 153);

	dawg_builderReverse.Insert("~e4", 154);

	dawg_builderReverse.Insert("~e5", 155);

	dawg_builderReverse.Insert("~e6", 156);

	dawg_builderReverse.Insert("~e7", 157);

	dawg_builderReverse.Insert("~e8", 158);

	dawg_builderReverse.Insert("~ea", 159);

	dawg_builderReverse.Insert("~eb", 160);

	dawg_builderReverse.Insert("~ec", 161);

	dawg_builderReverse.Insert("~ed", 162);

	dawg_builderReverse.Insert("~ee", 163);

	dawg_builderReverse.Insert("~ef", 164);

	dawg_builderReverse.Insert("~eg", 165);

	dawg_builderReverse.Insert("~eh", 166);

	dawg_builderReverse.Insert("~ei", 167);

	dawg_builderReverse.Insert("~ej", 168);

	dawg_builderReverse.Insert("~ek", 169);

	dawg_builderReverse.Insert("~el", 170);

	dawg_builderReverse.Insert("~em", 171);

	dawg_builderReverse.Insert("~en", 172);

	dawg_builderReverse.Insert("~eo", 173);

	dawg_builderReverse.Insert("~ep", 174);

	dawg_builderReverse.Insert("~eq", 175);

	dawg_builderReverse.Insert("~er", 176);

	dawg_builderReverse.Insert("~es", 177);

	dawg_builderReverse.Insert("~et", 178);

	dawg_builderReverse.Insert("~eu", 179);

	dawg_builderReverse.Insert("~ev", 180);

	dawg_builderReverse.Insert("~ew", 181);

	dawg_builderReverse.Insert("~ex", 182);

	dawg_builderReverse.Insert("~ey", 183);

	dawg_builderReverse.Insert("~f", 184);

	dawg_builderReverse.Insert("~f0", 185);

	dawg_builderReverse.Insert("~f1", 186);

	dawg_builderReverse.Insert("~f2", 187);

	dawg_builderReverse.Insert("~f3", 188);

	dawg_builderReverse.Insert("~f4", 189);

	dawg_builderReverse.Insert("~f5", 190);

	dawg_builderReverse.Insert("~f6", 191);

	dawg_builderReverse.Insert("~f7", 192);

	dawg_builderReverse.Insert("~f8", 193);

	dawg_builderReverse.Insert("~fa", 194);

	dawg_builderReverse.Insert("~fb", 195);

	dawg_builderReverse.Insert("~fc", 196);

	dawg_builderReverse.Insert("~fd", 197);

	dawg_builderReverse.Insert("~fe", 198);

	dawg_builderReverse.Insert("~ff", 199);

	dawg_builderReverse.Insert("~fg", 200);

	dawg_builderReverse.Insert("~fh", 201);

	dawg_builderReverse.Insert("~fi", 202);

	dawg_builderReverse.Insert("~fj", 203);

	dawg_builderReverse.Insert("~fk", 204);

	dawg_builderReverse.Insert("~fl", 205);

	dawg_builderReverse.Insert("~fm", 206);

	dawg_builderReverse.Insert("~fn", 207);

	dawg_builderReverse.Insert("~fo", 208);

	dawg_builderReverse.Insert("~fp", 209);

	dawg_builderReverse.Insert("~fq", 210);

	dawg_builderReverse.Insert("~fr", 211);

	dawg_builderReverse.Insert("~fs", 212);

	dawg_builderReverse.Insert("~ft", 213);

	dawg_builderReverse.Insert("~fu", 214);

	dawg_builderReverse.Insert("~fv", 215);

	dawg_builderReverse.Insert("~fw", 216);

	dawg_builderReverse.Insert("~fx", 217);

	dawg_builderReverse.Insert("~fy", 218);

	dawg_builderReverse.Insert("~g", 219);

	dawg_builderReverse.Insert("~g0", 220);

	dawg_builderReverse.Insert("~g1", 221);

	dawg_builderReverse.Insert("~g2", 222);

	dawg_builderReverse.Insert("~g3", 223);

	dawg_builderReverse.Insert("~g4", 224);

	dawg_builderReverse.Insert("~g5", 225);

	dawg_builderReverse.Insert("~g6", 226);

	dawg_builderReverse.Insert("~g7", 227);

	dawg_builderReverse.Insert("~g8", 228);

	dawg_builderReverse.Insert("~ga", 229);

	dawg_builderReverse.Insert("~gb", 230);

	dawg_builderReverse.Insert("~gc", 231);

	dawg_builderReverse.Insert("~gd", 232);

	dawg_builderReverse.Insert("~ge", 233);

	dawg_builderReverse.Insert("~gf", 234);

	dawg_builderReverse.Insert("~gg", 235);

	dawg_builderReverse.Insert("~gh", 236);

	dawg_builderReverse.Insert("~gi", 237);

	dawg_builderReverse.Insert("~gj", 238);

	dawg_builderReverse.Insert("~gk", 239);

	dawg_builderReverse.Insert("~gl", 240);

	dawg_builderReverse.Insert("~gm", 241);

	dawg_builderReverse.Insert("~gn", 242);

	dawg_builderReverse.Insert("~go", 243);

	dawg_builderReverse.Insert("~gp", 244);

	dawg_builderReverse.Insert("~gq", 245);

	dawg_builderReverse.Insert("~gr", 246);

	dawg_builderReverse.Insert("~gs", 247);

	dawg_builderReverse.Insert("~gt", 248);

	dawg_builderReverse.Insert("~gu", 249);

	dawg_builderReverse.Insert("~gv", 250);

	dawg_builderReverse.Insert("~gw", 251);

	dawg_builderReverse.Insert("~gx", 252);

	dawg_builderReverse.Insert("~gy", 253);

	dawg_builderReverse.Insert("~h", 254);

	dawg_builderReverse.Insert("~h0", 255);

	dawg_builderReverse.Insert("~h1", 256);

	dawg_builderReverse.Insert("~h2", 257);

	dawg_builderReverse.Insert("~h3", 258);

	dawg_builderReverse.Insert("~h4", 259);

	dawg_builderReverse.Insert("~h5", 260);

	dawg_builderReverse.Insert("~h6", 261);

	dawg_builderReverse.Insert("~h7", 262);

	dawg_builderReverse.Insert("~h8", 263);

	dawg_builderReverse.Insert("~ha", 264);

	dawg_builderReverse.Insert("~hb", 265);

	dawg_builderReverse.Insert("~hc", 266);

	dawg_builderReverse.Insert("~hd", 267);

	dawg_builderReverse.Insert("~he", 268);

	dawg_builderReverse.Insert("~hf", 269);

	dawg_builderReverse.Insert("~hg", 270);

	dawg_builderReverse.Insert("~hh", 271);

	dawg_builderReverse.Insert("~hi", 272);

	dawg_builderReverse.Insert("~hj", 273);

	dawg_builderReverse.Insert("~hk", 274);

	dawg_builderReverse.Insert("~hl", 275);

	dawg_builderReverse.Insert("~hm", 276);

	dawg_builderReverse.Insert("~hn", 277);

	dawg_builderReverse.Insert("~ho", 278);

	dawg_builderReverse.Insert("~hp", 279);

	dawg_builderReverse.Insert("~hq", 280);

	dawg_builderReverse.Insert("~hr", 281);

	dawg_builderReverse.Insert("~hs", 282);

	dawg_builderReverse.Insert("~ht", 283);

	dawg_builderReverse.Insert("~hu", 284);

	dawg_builderReverse.Insert("~hv", 285);

	dawg_builderReverse.Insert("~hw", 286);

	dawg_builderReverse.Insert("~hx", 287);

	dawg_builderReverse.Insert("~hy", 288);

	dawg_builderReverse.Insert("~i", 289);

	dawg_builderReverse.Insert("~i0", 290);

	dawg_builderReverse.Insert("~i1", 291);

	dawg_builderReverse.Insert("~i2", 292);

	dawg_builderReverse.Insert("~i3", 293);

	dawg_builderReverse.Insert("~i4", 294);

	dawg_builderReverse.Insert("~i5", 295);

	dawg_builderReverse.Insert("~i6", 296);

	dawg_builderReverse.Insert("~i7", 297);

	dawg_builderReverse.Insert("~i8", 298);

	dawg_builderReverse.Insert("~ia", 299);

	dawg_builderReverse.Insert("~ib", 300);

	dawg_builderReverse.Insert("~ic", 301);

	dawg_builderReverse.Insert("~id", 302);

	dawg_builderReverse.Insert("~ie", 303);

	dawg_builderReverse.Insert("~if", 304);

	dawg_builderReverse.Insert("~ig", 305);

	dawg_builderReverse.Insert("~ih", 306);

	dawg_builderReverse.Insert("~ii", 307);

	dawg_builderReverse.Insert("~ij", 308);

	dawg_builderReverse.Insert("~ik", 309);

	dawg_builderReverse.Insert("~il", 310);

	dawg_builderReverse.Insert("~im", 311);

	dawg_builderReverse.Insert("~in", 312);

	dawg_builderReverse.Insert("~io", 313);

	dawg_builderReverse.Insert("~ip", 314);

	dawg_builderReverse.Insert("~iq", 315);

	dawg_builderReverse.Insert("~ir", 316);

	dawg_builderReverse.Insert("~is", 317);

	dawg_builderReverse.Insert("~it", 318);

	dawg_builderReverse.Insert("~iu", 319);

	dawg_builderReverse.Insert("~iv", 320);

	dawg_builderReverse.Insert("~iw", 321);

	dawg_builderReverse.Insert("~ix", 322);

	dawg_builderReverse.Insert("~iy", 323);

	dawg_builderReverse.Insert("~j", 324);

	dawg_builderReverse.Insert("~j0", 325);

	dawg_builderReverse.Insert("~j1", 326);

	dawg_builderReverse.Insert("~j2", 327);

	dawg_builderReverse.Insert("~j3", 328);

	dawg_builderReverse.Insert("~j4", 329);

	dawg_builderReverse.Insert("~j5", 330);

	dawg_builderReverse.Insert("~j6", 331);

	dawg_builderReverse.Insert("~j7", 332);

	dawg_builderReverse.Insert("~j8", 333);

	dawg_builderReverse.Insert("~ja", 334);

	dawg_builderReverse.Insert("~jb", 335);

	dawg_builderReverse.Insert("~jc", 336);

	dawg_builderReverse.Insert("~jd", 337);

	dawg_builderReverse.Insert("~je", 338);

	dawg_builderReverse.Insert("~jf", 339);

	dawg_builderReverse.Insert("~jg", 340);

	dawg_builderReverse.Insert("~jh", 341);

	dawg_builderReverse.Insert("~ji", 342);

	dawg_builderReverse.Insert("~jj", 343);

	dawg_builderReverse.Insert("~jk", 344);

	dawg_builderReverse.Insert("~jl", 345);

	dawg_builderReverse.Insert("~jm", 346);

	dawg_builderReverse.Insert("~jn", 347);

	dawg_builderReverse.Insert("~jo", 348);

	dawg_builderReverse.Insert("~jp", 349);

	dawg_builderReverse.Insert("~jq", 350);

	dawg_builderReverse.Insert("~jr", 351);

	dawg_builderReverse.Insert("~js", 352);

	dawg_builderReverse.Insert("~jt", 353);

	dawg_builderReverse.Insert("~ju", 354);

	dawg_builderReverse.Insert("~jv", 355);

	dawg_builderReverse.Insert("~jw", 356);

	dawg_builderReverse.Insert("~jx", 357);

	dawg_builderReverse.Insert("~jy", 358);

	dawg_builderReverse.Insert("~k", 359);

	dawg_builderReverse.Insert("~k0", 360);

	dawg_builderReverse.Insert("~k1", 361);

	dawg_builderReverse.Insert("~k2", 362);

	dawg_builderReverse.Insert("~k3", 363);

	dawg_builderReverse.Insert("~k4", 364);

	dawg_builderReverse.Insert("~k5", 365);

	dawg_builderReverse.Insert("~k6", 366);

	dawg_builderReverse.Insert("~k7", 367);

	dawg_builderReverse.Insert("~k8", 368);

	dawg_builderReverse.Insert("~ka", 369);

	dawg_builderReverse.Insert("~kb", 370);

	dawg_builderReverse.Insert("~kc", 371);

	dawg_builderReverse.Insert("~kd", 372);

	dawg_builderReverse.Insert("~ke", 373);

	dawg_builderReverse.Insert("~kf", 374);

	dawg_builderReverse.Insert("~kg", 375);

	dawg_builderReverse.Insert("~kh", 376);

	dawg_builderReverse.Insert("~ki", 377);

	dawg_builderReverse.Insert("~kj", 378);

	dawg_builderReverse.Insert("~kk", 379);

	dawg_builderReverse.Insert("~kl", 380);

	dawg_builderReverse.Insert("~km", 381);

	dawg_builderReverse.Insert("~kn", 382);

	dawg_builderReverse.Insert("~ko", 383);

	dawg_builderReverse.Insert("~kp", 384);

	dawg_builderReverse.Insert("~kq", 385);

	dawg_builderReverse.Insert("~kr", 386);

	dawg_builderReverse.Insert("~ks", 387);

	dawg_builderReverse.Insert("~kt", 388);

	dawg_builderReverse.Insert("~ku", 389);

	dawg_builderReverse.Insert("~kv", 390);

	dawg_builderReverse.Insert("~kw", 391);

	dawg_builderReverse.Insert("~kx", 392);

	dawg_builderReverse.Insert("~ky", 393);

	dawg_builderReverse.Insert("~l", 394);

	dawg_builderReverse.Insert("~l0", 395);

	dawg_builderReverse.Insert("~l1", 396);

	dawg_builderReverse.Insert("~l2", 397);

	dawg_builderReverse.Insert("~l3", 398);

	dawg_builderReverse.Insert("~l4", 399);

	dawg_builderReverse.Insert("~l5", 400);

	dawg_builderReverse.Insert("~l6", 401);

	dawg_builderReverse.Insert("~l7", 402);

	dawg_builderReverse.Insert("~l8", 403);

	dawg_builderReverse.Insert("~la", 404);

	dawg_builderReverse.Insert("~lb", 405);

	dawg_builderReverse.Insert("~lc", 406);

	dawg_builderReverse.Insert("~ld", 407);

	dawg_builderReverse.Insert("~le", 408);

	dawg_builderReverse.Insert("~lf", 409);

	dawg_builderReverse.Insert("~lg", 410);

	dawg_builderReverse.Insert("~lh", 411);

	dawg_builderReverse.Insert("~li", 412);

	dawg_builderReverse.Insert("~lj", 413);

	dawg_builderReverse.Insert("~lk", 414);

	dawg_builderReverse.Insert("~ll", 415);

	dawg_builderReverse.Insert("~lm", 416);

	dawg_builderReverse.Insert("~ln", 417);

	dawg_builderReverse.Insert("~lo", 418);

	dawg_builderReverse.Insert("~lp", 419);

	dawg_builderReverse.Insert("~lq", 420);

	dawg_builderReverse.Insert("~lr", 421);

	dawg_builderReverse.Insert("~ls", 422);

	dawg_builderReverse.Insert("~lt", 423);

	dawg_builderReverse.Insert("~lu", 424);

	dawg_builderReverse.Insert("~lv", 425);

	dawg_builderReverse.Insert("~lw", 426);

	dawg_builderReverse.Insert("~lx", 427);

	dawg_builderReverse.Insert("~ly", 428);

	dawg_builderReverse.Insert("~m", 429);

	dawg_builderReverse.Insert("~n", 430);

	dawg_builderReverse.Insert("~o", 431);

	dawg_builderReverse.Insert("~p", 432);

	dawg_builderReverse.Insert("~q", 433);

	dawg_builderReverse.Insert("~r", 434);

	dawg_builderReverse.Insert("~s", 435);

	dawg_builderReverse.Insert("~t", 436);

	dawg_builderReverse.Insert("~u", 437);

	dawg_builderReverse.Insert("~v", 438);

	dawg_builderReverse.Insert("~w", 439);

	dawg_builderReverse.Insert("~x", 440);

	dawg_builderReverse.Insert("~y", 441);

	dawg_builderReverse.Finish(&dawgReverse);

	dawgdic::DictionaryBuilder::Build(dawgReverse, &dawg_dicReverse);

}
