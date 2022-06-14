#include <iostream>
#include "NanoTube.h"

int main()
{
	for (int i = 1; i < 30; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			NanoTube nt(i, j, "C");
			nt.place_atom();
			nt.tubize_all();
			nt.find_bond();
			nt.to_csv();
			std::cout << "(" << i << "," << j << ") nanotube has been created." << std::endl;
		}
	}
	return EXIT_SUCCESS;
}
