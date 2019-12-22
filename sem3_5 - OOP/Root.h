#pragma once
#include "stdafx.h"

template <typename T>
class Root
{
private:
	virtual void Menu() = 0;

	virtual void Input(T* t_array, unsigned int size) = 0;
	virtual void Input(T** t_array, unsigned int size) = 0;

	virtual void Output(const T* t_array, unsigned int size) = 0;
	virtual void Output(const T** t_array, unsigned int size) = 0;
};

