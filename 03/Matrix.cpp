#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(size_t rows, size_t colums,bool fill):rows(rows),colums(colums){
	if (rows == 0 || colums == 0) alldata = nullptr;
	else alldata = new int[rows * colums];
	if (fill) for (size_t i = 0; i < rows * colums; i++) alldata[i] = 0;
}

size_t Matrix::getRows(){
	return rows;
}

size_t Matrix::getColumns(){
	return colums;
}

Matrix::SingleColumn Matrix::operator[](size_t pos){
	if (pos < 0 || pos >= colums||rows==0) throw std::out_of_range("");
	return Matrix::SingleColumn(rows, alldata + pos * rows);
}

Matrix& Matrix::operator*=(int a) {
	for (size_t i = 0; i < rows * colums; i++) alldata[i] *= a;
	return *this;
}

bool Matrix::operator==(const Matrix& m) const {
	if (rows != m.rows || colums != m.colums) return false;
	for (size_t i = 0; i < rows * colums; i++) if (alldata[i] != m.alldata[i]) return false;
	return true;
}

bool Matrix::operator!=(const Matrix& m) const {
	return !(*this == m);
}

Matrix::~Matrix(){
	if(rows!=0&&colums!=0) delete[]alldata;
}

Matrix::SingleColumn::SingleColumn(size_t rows, int* data) :rows(rows), data(data) {}

int& Matrix::SingleColumn::operator[](size_t pos){
	if (pos < 0 || pos >= rows) throw std::out_of_range("");
	return data[pos];
}