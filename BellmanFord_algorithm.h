#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <clocale>
#include <string>
#include "C:\Users\Екатерина Иванова\source\repos\шаблон List\list.h"
#include "C:\Users\Екатерина Иванова\source\repos\шаблон List\List_iterator.h"
using namespace std;

class BellmanFord_algorithm
{
private:
	struct edge
	{
		unsigned vertex_from,
			vertex_to,
			edge_weight;
	};
	List<edge> edges;
	List<string> cities;
	const unsigned INF = 1000000000;

	// Reading data from a file.
	void input(string info_file)
	{
		ifstream file(info_file);
		if (!file.is_open())
			throw invalid_argument("File is not found.");

		string current_city = "";
		edge current_edge;
		char symbol;
		unsigned index_of_city = 0, current_city1 = 0, current_city2 = 0;

		while (!file.eof())
		{
			file >> noskipws >> symbol;
			if (file.eof()) break;
			else current_city += symbol;

			for (auto i = 0; i <= 1; i++)
			{
				do
				{
					file >> symbol;
					if (symbol != ';') current_city += symbol;
				} while (symbol != ';');
				if (!cities.contains(current_city))
				{
					cities.push_back(current_city);
					if (i == 0) current_city1 = index_of_city;
					else current_city2 = index_of_city;
					index_of_city++;
				}
				else
				{
					if (i == 0) current_city1 = cities.get_index(current_city);
					else current_city2 = cities.get_index(current_city);
				}
				current_city.clear();
			}

			for (auto i = 0; i <= 1; i++)
			{
				file >> symbol;
				// If there is no direct flight from one city to another, then this edge is not added to 
				// the list of edges, because it will not be used to find the minimum path.
				if (symbol == 'N')
				{
					while (symbol != '\n' && !file.eof() && symbol != ';')
						file >> symbol;
				}
				else
				{
					file.unget();
					file >> current_edge.edge_weight;
					if (i == 0)
					{
						current_edge.vertex_from = current_city1;
						current_edge.vertex_to = current_city2;
					}
					else
					{
						current_edge.vertex_from = current_city2;
						current_edge.vertex_to = current_city1;
					}
					edges.push_back(current_edge);
					file >> symbol;
				}
			}
		}

		file.close();
	}

	// Creating a connectivity matrix.
	unsigned** creation_of_matrix()
	{
		unsigned n = cities.get_size();
	    int i, j;

		unsigned** connectivity_matrix = new unsigned*[n];
		for (i = 0; i < n; i++)
		{
			connectivity_matrix[i] = new unsigned[n];
			for (j = 0; j < n; j++)
			{
				if (i == j)
					connectivity_matrix[i][j] = 0;
				else
					connectivity_matrix[i][j] = INF;
			}
		}

		edge current_edge;
		Iterator<edge> *iter = edges.create_iterator();
		while (iter->has_next())
		{
			current_edge = iter->next();
			connectivity_matrix[current_edge.vertex_from][current_edge.vertex_to] = current_edge.edge_weight;
		}
		delete iter;


		cout << endl << "The connectivity matrix:" << endl << "     ";
		for (i = 0; i < n; i++)
			cout << setw(5) << i;
		cout << endl;
		for (i = 0; i < n; i++)
		{
			cout << setw(5) << i;
			for (j = 0; j < n; j++)
			{
				if (connectivity_matrix[i][j] == INF)
					cout << setw(5) << "INF";
				else
					cout << setw(5) << connectivity_matrix[i][j];
			}
			cout << endl;
		}

		return connectivity_matrix;
	}

	// Display a list of cities in the console.
	void show_the_list_of_cities()
	{
		if (cities.isEmpty())
			throw invalid_argument("Data is not set.");

		unsigned i = 0;
		cout << "List of cities available for air travel:" << endl;
		Iterator<string> *iter = cities.create_iterator();
		while (iter->has_next())
		{
			cout << i << " : " << iter->next() << endl;
			i++;
		}
		delete iter;

		if (cities.get_size() == 1)
			throw invalid_argument("The list of cities available for air travel cannot contain only one element, there must be at least two of them.");
	}

	// The output of the search result.
	void output(unsigned min_price, string city_from, string city_to)
	{
		if (min_price == INF)
			cout << endl << "No flights from " << city_from << " to " << city_to << "." << endl;
		else
			cout << endl << "Cheapest flight from " << city_from << " to " << city_to << " costs " << min_price << "." << endl;
	}

public:
	BellmanFord_algorithm() {};

	~BellmanFord_algorithm()
	{
		if (!edges.isEmpty())
			edges.clear();
		if (!cities.isEmpty())
			cities.clear();
	};

	// Reading data from a file and displaying a list of cities in the console.
	void get_data(string info_file)
	{
		input(info_file);
		show_the_list_of_cities();
	}

	// Search for the minimum cost of a flight from one city to another.
	unsigned search_algorithm(unsigned city_from, unsigned city_to)
	{
		if (city_from >= cities.get_size() || city_to >= cities.get_size() || city_from == city_to)
			throw invalid_argument("The arrival city and / or departure city were selected incorrectly.");

		unsigned** connectivity_matrix = creation_of_matrix();

		unsigned *min_path, n = cities.get_size();

		min_path = new unsigned[n];
		for (unsigned i = 0; i < n; i++)
			min_path[i] = INF;
		min_path[city_from] = 0;

		for (unsigned k = 0; k < n; k++)
		{
			for (unsigned i = 0; i < n; i++)
			{
				for (unsigned j = 0; j < n; j++)
				{
					if (connectivity_matrix[i][j] < INF && connectivity_matrix[i][j] != 0)
						if (min_path[j] > min_path[i] + connectivity_matrix[i][j])
							min_path[j] = min_path[i] + connectivity_matrix[i][j];
				}
			}
		}

		output(min_path[city_to], cities.at(city_from), cities.at(city_to));

		return min_path[city_to];
	}
};