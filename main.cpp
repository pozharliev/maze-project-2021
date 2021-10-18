#include "include/backend/gameManager.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{

	Map map;
	GameManager gm;
	
	if (gm.Construct(384, 216, 5, 5))
		gm.Start();
}