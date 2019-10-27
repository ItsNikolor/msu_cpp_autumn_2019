#include "Matrix.h"
#include <stdexcept>
#include<iostream>

Matrix::Matrix(std::size_t rows, std::size_t colums,bool fill):rows(rows),colums(colums){
	if (rows == 0 || colums == 0) alldata = nullptr;
	else alldata = new int[rows * colums];
	if (fill) for (std::size_t i = 0; i < rows * colums; i++) alldata[i] = 0;
}

std::size_t Matrix::getRows(){
	return rows;
}

std::size_t Matrix::getColumns(){
	return colums;
}

Matrix::SingleColumn Matrix::operator[](std::size_t pos){
	if (pos < 0 || pos >= rows||colums==0) throw std::out_of_range("");
	return Matrix::SingleColumn(colums, alldata + pos * colums);
}

Matrix& Matrix::operator*=(int a) {
	for (std::size_t i = 0; i < rows * colums; i++) alldata[i] *= a;
	return *this;
}

bool Matrix::operator==(const Matrix& m) const {
	if (rows != m.rows || colums != m.colums) return false;
	for (std::size_t i = 0; i < rows * colums; i++) if (alldata[i] != m.alldata[i]) return false;
	return true;
}

bool Matrix::operator!=(const Matrix& m) const {
	return !(*this == m);
}

Matrix::~Matrix(){
	if(rows!=0&&colums!=0) delete[]alldata;
}

Matrix::SingleColumn::SingleColumn(std::size_t colums, int* data) :colums(colums), data(data) {}

int& Matrix::SingleColumn::operator[](std::size_t pos){
	if (pos < 0 || pos >= colums) throw std::out_of_range("");
	return data[pos];
}
