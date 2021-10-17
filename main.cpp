#include "include/frontend/map.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{
    Map map;
		if (map.Construct(384, 216, 5, 5))
			map.Start();
}