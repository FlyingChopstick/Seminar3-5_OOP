#pragma once
#include "stdafx.h"
#include "Root.h"

template <class T>
class Seminar3 :
	private Root
{
public:
	int array_size(const unsigned int max_size);

	void Input(T t_array, unsigned int size) override;
	void Output(const T t_array, unsigned int size) override;

private:
	int max_position(const int* t_array, unsigned int size);
	int* product(const int* t_array, unsigned int size);
	void display_product(const int* t_array, int* borders);
	void display_array(const int* t_array, unsigned int size);

};



//ARRAY_SIZE() -> int user_size, handles setting the size of the array and <is_created> check
int Seminar3<void>::array_size(const unsigned int max_size)
{
	int user_size = 0;


	while (true)
	{
		cout << endl;
		cout << "Enter the size of the array (max. " << max_size << "): ";
		cin >> user_size;

		//input check
		if ((user_size <= 0) || (user_size > max_size))
			cout << "Error: Array size must be >0 and <=" << max_size << ". Please try again." << endl;
		else
			break;
	}


	return user_size;
}

//INPUT(), fills the array
void Seminar3<void>::Input(int* t_array, unsigned int size)
{
	unsigned int i;																			//iterator
	char selector = 'n';																	//local selector

	cout << endl << "----INPUT----" << endl;

	//if the array is already created, reallocate the memory. s3_array_size handles the confirmation now

	//filling the array
	cout << "Filling the array with " << size << " element(s)." << endl;
	for (i = 0; i < size; i++) {
		cout << "Element #" << i << ": ";
		cin >> t_array[i];
	}

	cout << "Array created";


	cout << endl << "----INPUT END----" << endl;
	//return *t_array;																		//-> *t_array
}


//MAX_POSITION() -> int, determines the position of the greatest element
int Seminar3<void>::max_position(const int* t_array, unsigned int size) {
	unsigned int i;																//iterator
	int max = t_array[0];														//setting array[0] as max
	int position = 0;															//setting the position of max as 0

	//standart loop for finding max
	for (i = 1; i < size; i++) {
		if (t_array[i] > max) {
			max = t_array[i];
			position = i;
		}
	}

	return position;															//-> position
}

//PRODUCT() -> int or 0, product of the elements btwn the 1st and the 2nd negeatives
int* Seminar3<void>::product(const int* t_array, unsigned int size)
{
	unsigned int i;																	//iterator

	int* borders = new int[2];														//positions of the first and the second 0
	borders[0] = -1;
	borders[1] = -1;

	//determining the borders
	for (i = 0; i < size; i++)
	{
		if (t_array[i] == 0)
		{
			if (borders[0] == -1)
			{
				borders[0] = i;																//left border
			}
			else if (borders[1] == -1)
			{
				borders[1] = i;															//right border
				break;
			}
		}
	}


	return borders;															//-> product
}

//CALCULATE_PRODUCT(), calculates the product of elements between first two 0
void Seminar3<void>::display_product(const int* t_array, int* borders)
{
	int result = 1;																//product
	unsigned int i;

	//output determination

	//if there's no zeroes -> 0
	if ((borders[0] == -1) && (borders[1] == -1))
	{
		cout << "There are no 0 in the array, unable to calculate." << endl;
		cout << endl;
		//return
	}
	//if at least one of the borders exist
	else
	{
		//if only one 0 is found -> 0
		if (borders[1] == -1)
		{
			cout << "There is only one 0 in the array, unable to calculate." << endl;
			cout << endl;
			//return
		}
		//if both 0 are found
		else
		{
			//if this is a "...0 0..." situation -> 0
			if (borders[1] == borders[0] + 1)
			{
				cout << "Zeroes are following each other, unable to calculate." << endl;
				cout << endl;
				//return
			}
			//both 0 are valid, calculation of the product
			else
			{
				for (i = borders[0] + 1; i < borders[1]; i++)
				{
					result *= t_array[i];
				}
				cout << endl << "The product of the elements between the first and the second 0 is " << result << endl;
			}
		}
	}

	//return result;
}

//DISPLAY_ARRAY(), prints the 1d array
void Seminar3<void>::display_array(const int* t_array, unsigned int size)
{
	unsigned int i;

	cout << endl;
	cout << "Array output: ";

	for (i = 0; i < size; i++)
	{
		cout << t_array[i] << " ";
	}

	cout << endl;
}


//int OUTPUT() -> 0, handles the output of the values and the array
void Seminar3<void>::Output(const int* t_array, unsigned int size)
{
	int* borders = new int[2];

	char selector = '0';


	cout << endl;
	cout << "----OUTPUT MENU----";
	cout << endl;


	do
	{
		cout << " 1. The greatest element" << endl;
		cout << " 2. The product of the elements between zeroes" << endl;
		cout << " 3. Array output" << endl;
		cout << " 5. Return" << endl;
		cout << "Your selection: ";
		cin >> selector;

		switch (selector)
		{
			//max_pos calculation
		case '1':
		{
			unsigned int max_pos = max_position(t_array, size);
			cout << endl << "The position of the greatest element is #" << max_pos << " (" << t_array[max_pos] << ")";
			cout << endl;
			break;
		}

		//product calculation
		case '2':
		{
			borders = product(t_array, size);
			display_product(t_array, borders);

			break;
		}

		//array output
		case'3':
		{
			display_array(t_array, size);

			break;
		}

		//return
		case '5': break;

		default: cout << "Wrong input, please try again."
			<< endl;
		}

	} while (selector != '5');


	delete[] borders;

	cout << endl;
	cout << "----OUTPUT END----";
	cout << endl;
}








