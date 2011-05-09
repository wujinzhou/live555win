#pragma once

#include <string>
#include <map>
using namespace std;

class Mime
{
public:
	static string ext2mime(const string &ext);
	static void mimeinit();
private:
	static map<string,string> c_mmapMime;
};
