#pragma once
#include "stdafx.h"
#include "Root.h"

template <typename T>
class Seminar5 :
	private Root<T>
{
public:
	Seminar5()
	{
		t_array = new char[size];
		*t_array = { ' ' };

		Seminar5::Menu();
	}

	void Menu() override;
	void Input(T* t_array, unsigned int size) override;
	void Input(T** t_array, unsigned int size) override {}
	void Output(T* t_array, unsigned int size) override;
	void Output(T** t_array, unsigned int size) override {}

	~Seminar5()
	{
		//cout << "Deleting the array." << endl;//DEBUG
		delete[] t_array;
		//cout << "Array deleted." << endl;//DEBUG
	}
private:
	const unsigned int size = 64;
	char* t_array;


	char** parse(const T* t_array, const unsigned int size);
	void display_text(const char* t_array, const unsigned int size);
	void display_words(char** words, const unsigned int size);
};

template <typename T> void Seminar5<T>::Menu()
{
	char selector = 'a';

	cout << endl;
	cout << "----SEMINAR 5 MENU----";
	cout << endl;


	do
	{
		cout << " 1. Enter the text." << endl;
		cout << " 2. Display the tasks." << endl;
		cout << " 5. Exit." << endl;
		cout << "Your selection: ";
		cin >> selector;


		switch (selector)
		{
		case '1':
		{
			Input(t_array, size);
			cout << endl;
			break;
		}
		case '2':
		{
			Output(t_array, size);
			cout << endl;
			break;
		}
		case '5':
			break;

		default: cout << "Wrong input, try again. " << endl;
		}

	} while (selector != '5');
}

template <typename T> void Seminar5<T>::Input(T* t_array, unsigned int size)
{
	//MAX LENGTH OF THE FILENAME
	const unsigned int filename_size = 64; 

	unsigned int i = 0;

	char* local_t_array = new char[size];
	for (i = 0; i < size; i++)
		local_t_array[i] = ' ';

	
	char filename[filename_size];
	ifstream input_file;

	cout << endl;
	cout << "----INPUT----";
	cout << endl;

	do
	{
		cout << endl;
		cout << "Specify the name of the file (max. " << filename_size << " symbols): ";
		cin >> filename;


		cout << "Opening the file..." << endl;
		input_file.open(filename);
		if (!input_file) cout << "Error: Could not open the file specified." << endl;

	} while (!input_file);

	cout << "File was successfully opened, reading..." << endl;

	input_file.getline(local_t_array, size - 1);

	cout << "The file was read successfully.";
	cout << endl;

	input_file.close();

	for (i = 0; i < size; i++)
	{
		//cout << local_t_array[i];//DEBUG
		t_array[i] = local_t_array[i];
	}



	//cout << "Deleting the local_t_array" << endl;//DEBUG
	delete[] local_t_array;
	//cout << "t_array deleted" << endl;//DEBUG

	cout << endl;
	cout << "----INPUT END----";
	cout << endl;
}

template <typename T> void Seminar5<T>::Output(T* t_array, unsigned int size)
{
	char selector = 'a';
	unsigned int i;
	unsigned int words_size = size / 4;


	char** words = new char* [words_size];
	for (i = 0; i < words_size; i++) //WAS I=1 FOR SOME REASON
	{
		words[i] = new char[4];
	}



	cout << endl;
	cout << "----OUTPUT MENU----";
	cout << endl;



	do
	{
		cout << " 1. Find words with less then five symbols" << endl;
		cout << " 2. Print the text" << endl;
		cout << " 5. Return" << endl;
		cout << "Your selection: ";
		cin >> selector;

		switch (selector)
		{
		case '1':
		{
			words = parse(t_array, size);
			//cout << endl;
			display_words(words, size);
			break;
		}

		case '2':
		{
			display_text(t_array, size);
			break;
		}

		case '5': break;

		default: cout << "Wrong input, try again." << endl;
			break;
		}
	} while (selector != '5');


	cout << endl;
	cout << "----OUTPUT END----";
	cout << endl;


	for (i = 0; i < words_size; i++)
	{
		delete[] words[i];
	}
	delete[] words;

}


template <typename T> char** Seminar5<T>::parse(const T* t_array, const unsigned int size)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int c;
	unsigned int c2;
	//unsigned int words_position = 0;
	unsigned int length = 0;
	unsigned int words_count = 0;


	char* local_t_array = new char[size];
	for (i = 0; i < size; i++)
	{
		local_t_array[i] = t_array[i];
		//cout << local_t_array[i];//DEBUG
	}


	unsigned int words_size = size / 4;
	char** words = new char* [words_size];
	for (i = 0; i < words_size; i++)
	{
		words[i] = new char[4];

		for (j = 0; j < 4; j++)
		{
			words[i][j] = ' ';
		}
	}



	i = 0;
	while ((local_t_array[i] != '\0') && (i < size - 1))
	{
		j = i;
		while ((local_t_array[j] != ' ') && (local_t_array[j] != '.'))
		{
			//cout << " /" << local_t_array[j] << "/ ";//DEBUG
			length++;
			j++;
		}
		//cout << "|j1=" << j << "| ";//DEBUG
		if ((length < 5) && (length > 0))
		{
			//cout << " /" << words[words_count][0] << "/ ";//DEBUG
			c2 = 0;
			for (c = i; c < i + length; c++)
			{

				//cout << " I am here! ";//DEBUG
				//cout << local_t_array[c];//DEBUG
				//cout << c2 << " ";//DEBUG
				//cout << c << " ";//DEBUG
				//cout << words_count << " ";//DEBUG
				words[words_count][c2] = local_t_array[c];
				c2++;
			}
			//cout << "|j2="<<j<<"|";//DEBUG
			//cout << "|";//DEBUG
			words_count++;
			//cout << " ";//DEBUG

		}

		i += length + 1;
		length = 0;
		//cout << i << endl;//DEBUG
	}



	delete[] local_t_array;

	return words;
}

template <typename T> void Seminar5<T>::display_text(const char* t_array, unsigned int size)
{
	unsigned int i;

	cout << endl;
	cout << "You entered the following text: " << endl;
	for (i = 0; i < size; i++)
	{
		cout << t_array[i];
	}
	cout << endl << endl;
}


template <typename T> void Seminar5<T>::display_words(char** words, const unsigned int size)
{
	unsigned int i = 0;
	unsigned words_size = size / 4;
	unsigned int words_count = 0;

	cout << endl << "Words with no more than 4 symbols in them: ";
	cout << endl;

	while ((words[words_count][0] != ' ') && (words_count <= size))
	{
		i = 0;
		cout << "\"";
		while ((words[words_count][i] != ' ') && (i < 4))
		{
			cout << words[words_count][i];
			i++;
		}
		cout << "\" ";
		words_count++;
	}


	if (words_count == 0)
		cout << "There are no words with no more than 4 symbols." << endl;
	else
		cout << endl << "There is a total of " << words_count << " of such words in the text." << endl;

	cout << endl;
}