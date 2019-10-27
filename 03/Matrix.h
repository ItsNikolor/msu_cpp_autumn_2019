#pragma once
class Matrix {
	size_t rows, colums;
	int *alldata;
	class SingleColumn {
		friend class Matrix;
		size_t rows;
		int *data;
		SingleColumn(size_t rows, int* data);
	public:
		int& operator[](size_t pos);
	};
public:
	Matrix(size_t rows, size_t colums,bool fill=true);
	size_t getRows();
	size_t getColumns();
	SingleColumn operator[](size_t pos);
	Matrix& operator*=(int a);
	bool operator==(const Matrix& m)const;
	bool operator!=(const Matrix& m)const;
	~Matrix();
};