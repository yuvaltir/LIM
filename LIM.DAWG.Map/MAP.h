	
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <thread>         // std::thread
#include <mutex>          // std::mutex

extern "C" __declspec(dllexport) char* replace(char* a, int len);
extern "C" __declspec(dllexport) char* replaceBack(char* a, int len);
extern "C" __declspec(dllexport) int add(int a, int b);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
char* replaceBack(char* a, int len);
char* replace(char* a, int len);
void FillMapWithvalue();
void VerifyMapLoaded();
extern std::mutex _mtx;
extern std::map<std::string, std::string> _stringLookupTable;
extern bool _mapLoaded;

#endif