#include "stdafx.h"
#include "Main.h"

int main(int argc, char *argv[])
{
	CMain* cmainInstance = new CMain();

	cmainInstance->MenuLoop();

	cmainInstance->GameLoop();

	return 0;
}

