#include "stdafx.h"
#include "CppUnitTest.h"
#include"../Bellman-Ford algorithm/BellmanFord_algorithm.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		BellmanFord_algorithm test_algorithm1, test_algorithm2, test_algorithm3;

	public:
		TEST_METHOD(test_get_data)
		{
			try
			{
				test_algorithm1.get_data("wrong_test_file.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "File is not found.");
			}

			try
			{
				test_algorithm2.get_data("C:/Users/Екатерина Иванова/source/repos/Bellman-Ford algorithm/Bellman-Ford algorithm/empty_file.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "Data is not set.");
			}

			try
			{
				test_algorithm3.get_data("C:/Users/Екатерина Иванова/source/repos/Bellman-Ford algorithm/Bellman-Ford algorithm/one_city.txt");
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "The list of cities available for air travel cannot contain only one element, there must be at least two of them.");
			}

			test_algorithm1.get_data("C:/Users/Екатерина Иванова/source/repos/Bellman-Ford algorithm/Bellman-Ford algorithm/test_file.txt");
		}

		TEST_METHOD(test_search_algorithm)
		{
			test_algorithm1.get_data("C:/Users/Екатерина Иванова/source/repos/Bellman-Ford algorithm/Bellman-Ford algorithm/test_file.txt");
			try
			{
				test_algorithm1.search_algorithm(1, 1);
			}
			catch (invalid_argument ex)
			{
				Assert::AreEqual(ex.what(), "The arrival city and / or departure city were selected incorrectly.");
			}

			Assert::AreEqual(test_algorithm1.search_algorithm(3, 0), (unsigned)68);
		}

	};
}