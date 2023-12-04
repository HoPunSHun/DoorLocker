#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "DoorManager.h"

int main()
{

	srand((unsigned)time(NULL));

	DoorManager doorManager;

	doorManager.Init();

	doorManager.ListCards();

	doorManager.SaveNextId();

}
