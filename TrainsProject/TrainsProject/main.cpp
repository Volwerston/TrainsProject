#include <iostream>
#include <vector>

#include "Train.h"
#include "Algorithms.h"

using namespace std;

int main()
{
	vector<Train> trains = getTrainsByDate("2016-10-01");

	system("pause");
	return 0;
}