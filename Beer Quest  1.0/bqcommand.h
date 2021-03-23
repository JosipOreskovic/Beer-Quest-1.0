#pragma once

#include "stdafx.h"
#include <cstdio>
#include <cctype>
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>



class Command
{
private:
	static int elapsedTime;
public:
	static int GetElapsedtime() { return elapsedTime; }
	static char Get();
};


