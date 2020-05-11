#include <Windows.h>
#include "BellmanFord_algorithm.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	BellmanFord_algorithm example;
	unsigned city_from, city_to;
	bool there_is_no_error = true;

	try
	{
		example.get_data("flights.txt");
	}
	catch (invalid_argument ex)
	{
		cout << "Error. " << ex.what() << endl;
		there_is_no_error = false;
	}

	if (there_is_no_error == true)
	{
		cout << endl << "Choose the departure city number from the list: ";
		cin >> city_from;
		cout << "Choose the arrival city number from the list: ";
		cin >> city_to;

		try
		{
			example.search_algorithm(city_from, city_to);
		}
		catch (invalid_argument ex)
		{
			cout << "Error. " << ex.what() << endl;
		}
	}

	system("pause");
	return 0;
}