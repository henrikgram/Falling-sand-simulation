#include <iostream>
#include <vector>

int mfain()
{
	std::vector<int> test;

	test.reserve(25);

	for (int i = 0; i < 25; i++)
	{
		test.push_back(i);
	}

	bool goRight = true;

	for (int y = 0; y < 5; y++)
	{
		int x;
		if (goRight)
		{
			for (int x = 0; x < 5; x++)
			{
				std::cout << test[y * 5 + x] << std::endl;
			}

		}
		else
		{
			for (int x = 4; x >= 0; x--)
			{
				std::cout << test[y * 5 + x] << std::endl;
			}
		}

		goRight = !goRight;


	}

	return 0;
}