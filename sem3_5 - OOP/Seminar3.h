#pragma once
#include "stdafx.h"
#include "Root.h"

template <class T>
class Seminar3 :
	private Root<T>
{
public:
	Seminar3()
	{
		t_array = new T[max_size];
		sorted_array = new T[max_size];

		is_created = false;
		is_sorted = false;

		Seminar3<T>::Menu();
	}

	void Menu() override;
	void Input(T* t_array, unsigned int size) override;
	void Input(T** t_array, unsigned int size) override;

	void Output(const T* t_array, unsigned int size) override;
	void Output(const T** t_array, unsigned int size) override;

	~Seminar3()
	{
		//cout << endl << "Deleting the main array." << endl;//DEBUG
		delete[] t_array;																					//DELETE t_array[]
		//cout << "Deleting the sorted array." << endl;//DEBUG
		delete[] sorted_array;																				//DELETE sorted_array[]
		//cout << "Arrays deleted." << endl;//DEBUG
	}

private:
	//states
	bool is_created;											//whether the array is created or not
	bool is_sorted;												//state of the array (sorted/not sorted)

	const unsigned int max_size = 50;									//max size of the array

	//arrays
	T* t_array;							//t_array announcement
	T* sorted_array;									//sorted array


	//logic
	int array_size(const unsigned int max_size);
	int max_position(const T* t_array, unsigned int size);
	int* product(const T* t_array, unsigned int size);
	

	//display
	void display_product(const T* t_array, int* borders);
	void display_array(const T* t_array, unsigned int size);
};


//INTERFACE
//MENU(), main menu of Sem3
template <typename T> void Seminar3<T>::Menu()
{
	char selector = 'a';												//main menu selector
	unsigned int size = 0;												//user-defined size of the array, 0 by default


	//menu loop
	do
	{
		cout << endl;
		cout << "----SEMINAR 3 MENU----" << endl;
		cout << " 1. Array input" << endl;
		cout << " 2. Sort the array" << endl;
		cout << " 3. Display the tasks" << endl;
		cout << " 5. Exit" << endl;
		cout << "Your selection: ";
		cin >> selector;


		switch (selector)
		{
			//input() is called
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
						//if 'y' re-enter <size>
					case 'y':
					{
						size = array_size(max_size);
						Input(t_array, size);																	//INPUT() is called -> t_array
						is_created = true;																		//array state change (creation)
						is_sorted = false;

						break;
					}

					//if 'n' do not change <size>
					case 'n': break;

					default: cout << "Wrong input, try again." << endl;
						break;
					}
				}
			}
			else
			{
				size = array_size(max_size);
				Input(t_array, size);																	//INPUT() is called -> t_array
				is_created = true;																		//array state change (creation)
			}

			break;
		}

		//sort() is called
		case '2':
		{
			if (is_created == false)
			{
				cout << "Error: The array is not created." << endl;
				break;
			}
			else
			{
				cout << "Sorted." << endl;//DEBUG
				//sorted_array = sort(t_array, size);																							//SORT() is called -> t_array
				is_sorted = true;
				break;
			}

		}

		//output() check and call
		case '3':
		{
			//check whether the array is created
			if (is_created == true)
			{
				if (is_sorted == true)
				{
					char o_sel = 'a';
					while ((o_sel != 'o') && (o_sel != 's') && (o_sel != 'c'))
					{
						cout << endl << "Do you want to use the original array, the sorted array or to cancel? (o/s/c): ";
						cin >> o_sel;

						switch (o_sel)
						{
							//OUTPUT() is called on the original array
						case 'o': Output(t_array, size);
							break;

							//OUTPUT() is called on the sorted array
						case 's': Output(sorted_array, size);
							break;

							//return to the menu
						case 'c': break;

						default: cout << "Wrong input, please try again." << endl;
							break;
						}
					}
				}
				else
				{
					//OUTPUT() is called
					Output(t_array, size);
					break;
				}
			}
			else
			{
				cout << "Error: The array is not created." << endl;
				break;
			}
		}

		//return
		case '5':
			break;

		default: cout << "Wrong input, try again." << endl;
			break;
		}

	} while (selector != '5');



}
//INPUT(), handles the arra input
template <typename T> void Seminar3<T>::Input(T* t_array, unsigned int size)
{
	unsigned int i;																			//iterator
	char selector = 'n';																	//local selector

	cout << endl << "----INPUT----" << endl;


	//filling the array
	cout << "Filling the array with " << size << " element(s)." << endl;
	for (i = 0; i < size; i++) {
		cout << "Element #" << i << ": ";
		cin >> t_array[i];
	}

	cout << "Array created";


	cout << endl << "----INPUT END----" << endl;
	//return *t_array;																		//-> *t_array
};
//OUTPUT(), handles the output menu of Sem3
template <typename T> void Seminar3<T>::Output(const T* t_array, unsigned int size)
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


//LOGIC FUNCTIONS
//ARRAY_SIZE() -> int user_size, handles setting the size of the array and <is_created> check
template <typename T> int Seminar3<T>::array_size(const unsigned int max_size)
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
//MAX_POSITION() -> int, determines the position of the greatest element
template<typename T> int Seminar3<T>::max_position(const T* t_array, unsigned int size) {
	unsigned int i;																//iterator
	T max = t_array[0];															//setting array[0] as max
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
template<typename T> int* Seminar3<T>::product(const T* t_array, unsigned int size)
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

//DISPLAY FUNCTIONS
//CALCULATE_PRODUCT(), calculates the product of elements between first two 0
template<typename T> void Seminar3<T>::display_product(const T* t_array, int* borders)
{
	T result = 1.0;																//product
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
template<typename T> void Seminar3<T>::display_array(const T* t_array, unsigned int size)
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