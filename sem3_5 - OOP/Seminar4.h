#pragma once
#include "stdafx.h"
#include <fstream>
#include "Root.h"

using std::ifstream;

template <typename T>
class Seminar4 :
	private Root<T>
{
public:
	Seminar4()
	{
		t_array = new T*[max_dimension];													//main array allocation
		for (unsigned int i = 0; i < max_dimension; i++)
			t_array[i] = new T[max_dimension];

		Seminar4::Menu();
	}

	void Menu() override;
	void Input(T* t_array, unsigned int size) override {}
	void Input(T** t_array, unsigned int size) override;
	void Output(T* t_array, unsigned int size) override {}
	void Output(T** t_array, unsigned int size) override;


	~Seminar4()
	{
		//array deletion
		//cout << endl << "Deleting the array." << endl;//DEBUG
		for (unsigned int i = 0; i < max_dimension; i++)
			delete[] t_array[i];
		delete[] t_array;
		//cout << "Array deleted." << endl;//DEBUG
	}

private:
	bool is_created = false;
	
	const unsigned int max_dimension = 10;														//max size of the array, referenced in s4_array_size, s4_input
	unsigned int dimension = 0;																//custom array dimensions, 0 by default

	T** t_array;


	int array_dimension(unsigned int max_dimension);
	bool compare(T** t_array, unsigned int dimension, int start_index);
	int* identical(T** t_array, unsigned int dimension);
	T** search(T** t_array, const unsigned int dimension);


	void display_array(T** target, unsigned int dimension);
	void display_identical(T* target, unsigned int dimension);
	void display_search(T** target, unsigned int dimension);


};


//INTERFACE
//MENU(), main menu of Sem4
template <typename T> void Seminar4<T>::Menu()
{


	char selector = '0';																	//menu selector
														//array state (created)


	cout << endl;
	cout << "----SEMINAR 4 MENU----";
	cout << endl;



	do
	{
		cout << " 1. Enter the array" << endl;
		cout << " 2. Display the tasks" << endl;
		cout << " 5. Exit" << endl;
		cout << "Your selection: ";
		cin >> selector;


		switch (selector)
		{
			//input() and dimension() are called
		case '1':
		{
			//overwrite check
			if (is_created == true)
			{
				char selector = 'a';

				//overwrite confirmation
				cout << endl << "The array is already created. If you proceed it will be overwritten. Continue? (y/n)" << endl;
				while ((selector != 'y') && (selector != 'n'))
				{
					cout << "Your selection: ";
					cin >> selector;
					switch (selector)
					{
						//if 'y' re-enter <dimension>
					case 'y':
					{
						dimension = array_dimension(max_dimension);
						Input(t_array, dimension);																//INPUT() is called -> t_array
						is_created = true;																		//array state change (creation)

						break;
					}

					//if 'n' do not change <dimension>
					case 'n': break;

					default: cout << "Wrong input, try again." << endl;
						break;
					}
				}
			}
			else
			{
				dimension = array_dimension(max_dimension);
				Input(t_array, dimension);																	//INPUT() is called -> t_array
				is_created = true;																		//array state change (creation)
			}

			cout << endl;
			break;
		}

		//output() is called
		case '2':
		{
			if (is_created == true)
				Output(t_array, dimension);
			else
			{
				cout << "Error: The array is not created.";
			}

			cout << endl;
			break;
		}

		//return
		case '5':
			break;

		default: cout << "Wrong input, try again." << endl;
			break;
		}

	} while (selector != '5');



}


//INPUT(), handles the array input
template <typename T> void Seminar4<T>::Input(T** t_array, unsigned int size)
{
	//unsigned int local_dimension = *dimension;
	//int n = 0;
	unsigned int i, j;
	char selector = '0';

	//t_array = new int* [local_dimension];

	const unsigned int filename_size = 64;
	char filename[filename_size];
	ifstream input_file;


	cout << endl;
	cout << "----INPUT----";
	cout << endl;

	while ((selector != '1') && (selector != '2') && (selector != '5'))
	{
		cout << " 1. Enter the array from the keyboard ";
		cout << endl;
		cout << " 2. Read the array from the file";
		cout << endl;
		cout << " 5. Cancel";
		cout << endl;
		cout << "Your selection: ";
		cin >> selector;

		switch (selector)
		{
			//from the file
		case '1':
		{
			for (i = 0; i < dimension; i++)
			{
				for (j = 0; j < dimension; j++)
				{
					cout << "Enter the element [" << i << "][" << j << "]: ";
					cin >> t_array[i][j];
				}
			}
			cout << "Array created.";
			break;
		}

		//from the keyboard
		case '2':
		{
			do
			{
				cout << "Specify the name of the file (max. " << filename_size << " symbols): ";
				cin >> filename;

				cout << "Opening the file..." << endl;
				input_file.open(filename);
				if (!input_file) cout << "Error: Could not open the file specified." << endl;

			} while (!input_file);

			cout << "File was successfully opened, reading..." << endl;

			for (i = 0; i < dimension; i++)
			{
				for (j = 0; j < dimension; j++)
				{
					input_file >> t_array[i][j];
					if (!input_file)
					{
						cout << "Error: could not read the element, please try again." << endl;
					}
				}
			}
			input_file.close();

			break;
		}

		//return
		case '5': break;

		default: cout << "Wrong input, please try again" << endl;
			break;
		}
	}


	cout << endl;
	cout << "----INPUT END----";
	cout << endl;
}
//OUTPUT(), handles the array output
template <typename T> void Seminar4<T>::Output(T** t_array, unsigned int size)
{
	unsigned int i;
	char selector = 'n';

	int* arr_identical = new int[dimension];
	int** arr_search = new int*[dimension];
	for (i = 0; i < dimension; i++)
		arr_search[i] = new int[2];


	cout << endl;
	cout << "----OUTPUT MENU----";
	cout << endl;

	do
	{
		cout << " 1. Search for identical rows and columns" << endl;
		cout << " 2. Sum the rows with the negative elements" << endl;
		cout << " 3. Display the array" << endl;
		cout << " 5. Return" << endl;
		cout << "Your selection: ";
		cin >> selector;

		switch (selector)
		{
		case '1':
		{
			arr_identical = identical(t_array, dimension);
			display_identical(arr_identical, dimension);
			cout << endl;
			break;
		}

		case '2':
		{
			arr_search = search(t_array, dimension);
			display_search(arr_search, dimension);
			cout << endl;
			break;
		}

		case '3':
		{
			display_array(t_array, dimension);
			cout << endl;
			break;
		}

		case '5':
		{
			break;
		}

		default: cout << "Wrong input, please try again." << endl;
			break;
		}

	} while (selector != '5');

	delete[] arr_identical;
	for (i = 0; i < dimension; i++)
		delete[] arr_search[i];
	delete[] arr_search;


	cout << endl;
	cout << "----OUTPUT END----";
	cout << endl;
}


//LOGIC
//ARRAY_DIMENSION() -> int user_dimension, handles the array size setting and <is_created> check
template <typename T> int Seminar4<T>::array_dimension(unsigned int max_dimension)
{
	int user_dimension = 0;


	while (true)
	{
		cout << endl;
		cout << "Enter the size of the array (NxN, >0, max " << max_dimension << "): ";
		cin >> user_dimension;

		//input check
		if ((user_dimension <= 0) || (user_dimension > max_dimension))
			cout << "Error: Array size must be >0 and <=" << max_dimension << ", please try again." << endl;
		else
			break;
	}


	return user_dimension;
}
//COMPARE() -> bool t/f, compares the <start_index> column and row, ->true if identical
template <typename T> bool Seminar4<T>::compare(T** t_array, unsigned int dimension, int start_index)
{
	unsigned int c = 0;


	while ((t_array[c][start_index] == t_array[start_index][c]) && (c < dimension))
	{
		c++;																//counts equal elements in row/column
	}

	if (c == dimension) {													//if all elements are equal -> true
		return true;
	}

	return false;															//-> false
}
//IDENTICAL() -> int* numbers, finds and returns the array of numbers of identical r&c
template <typename T> int* Seminar4<T>::identical(T** t_array, unsigned int dimension)
{
	unsigned int i;
	int result = 0;
	bool is_found = false;
	int* numbers = new int[dimension];


	//i[0-k] loop, checks the first numbers in columns/rows
	for (i = 0; i < dimension; i++)
	{
		numbers[i] = -1;
		if (t_array[0][i] == t_array[i][0])
		{
			//COMPARE() is called, output is stored in <result>
			if (compare(t_array, dimension, i) == true)
			{
				result = i;
				is_found = true;
			}

			//cout << "The result is \"" << result << "\"";//DEBUG

			if (is_found == true)
			{
				numbers[i] = result;
			}

		}
	}

	return numbers;
}
//SEARCH() ->int** sums, checks whether the row has <0 elements, sums and puts in the array if true
template <typename T> T** Seminar4<T>::search(T** t_array, const unsigned int dimension)
{
	unsigned int t, i, j;
	T tmp = 0.00f;
	//bool is_found = false;

	T** sums = new T*[dimension];
	for (i = 0; i < dimension; i++)
	{
		sums[i] = new T[2];
		sums[i][0] = -1.00f;
		sums[i][1] = 0.00f;
	}


	for (i = 0; i < dimension; i++)
	{
		//j[0-k] loop, searches for negatives, sums the row in <tmp> if found
		for (j = 0; j < dimension; j++)
		{
			if (t_array[i][j] < 0)
			{
				for (t = 0; t < dimension; t++)
				{
					tmp += t_array[i][t];
				}
				sums[i][0] = i;
				sums[i][1] = tmp;
				tmp = 0;
			}
		}
	}

	return sums;
}


//DISPLAY
//DISPLAY_ARRAY(), prints the array
template <typename T> void Seminar4<T>::display_array(T** target, unsigned int dimension)
{
	unsigned int i, j;

	cout << endl;
	cout << "Array output: ";
	cout << endl;

	for (i = 0; i < dimension; i++)
	{
		for (j = 0; j < dimension; j++)
		{
			cout << target[i][j] << "	";
		}
		cout << endl;
	}
}
//DISPLAY_IDENTICAL(), prints the numbers of the identical r&c if found
template <typename T> void Seminar4<T>::display_identical(T* target, unsigned int dimension)
{
	unsigned int i;
	bool is_found = false;

	for (i = 0; i < dimension; i++)
	{
		if (target[i] > -1)
		{
			cout << "Row #" << target[i] << "is identical to the column #" << target[i] << "." << endl;
			is_found = true;
		}
	}

	if (is_found == false)
		cout << "There are no identical rows and columns in the array." << endl;
}
//DISPLAY_SEARCH(), prints the sums of the rows with negative elements
template <typename T> void Seminar4<T>::display_search(T** target, unsigned int dimension)
{
	unsigned int i;
	bool is_found = false;

	for (i = 0; i < dimension; i++)
	{
		if (target[i][0] != -1)
		{
			cout << "The sum of the row #" << i << " is " << target[i][1] << "." << endl;
			is_found = true;
		}
	}

	if (is_found == false)
		cout << "There are no negative elements in the array." << endl;
}