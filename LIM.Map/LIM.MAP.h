#include <iostream>
#include <string>
#include <algorithm>

extern "C" __declspec(dllexport) char* replace(char* a, int len);
extern "C" __declspec(dllexport) int add(int a, int b);
void replaceAll(std::string& str, const std::string& from, const std::string& to);