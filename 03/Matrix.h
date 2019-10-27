#pragma once
#include<iostream>
class Matrix {
	std::size_t rows, colums;
	int *alldata;
	class SingleColumn {
		friend class Matrix;
		std::size_t rows;
		int *data;
		SingleColumn(std::size_t rows, int* data);
	public:
		int& operator[](std::size_t pos);
	};
public:
	Matrix(std::size_t rows, std::size_t colums,bool fill=true);
	std::size_t getRows();
	std::size_t getColumns();
	SingleColumn operator[](std::size_t pos);
	Matrix& operator*=(int a);
	bool operator==(const Matrix& m)const;
	bool operator!=(const Matrix& m)const;
	~Matrix();
};
