#pragma once
#include<iostream>
using std::cout;
using std::endl;

template <int row, int col, typename T = int>
class Matrix
{
	template<int row, int col, typename T>
	friend class MatrixContainer;
private:

	T** matrix;
	T value;

public:
	
	Matrix(T value = T(0)) { // c'tor
		this->value = value;
		matrix = new T * [row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[col];
		}

		for (int i = 0; i < row; i++) {  // Inserting the value to the matrix
			for (int j = 0; j < col; j++) {
				matrix[i][j] = this->value;
			}
		}
	}

	Matrix(const Matrix<row, col, T>& otherMatrix) { //copy constructor
		this->matrix = new T * [row]; // Dynamic allocation memory
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[col];
		}

		for (int i = 0; i < row; i++) { // copy the matrix
			for (int j = 0; j < col; j++) {
				this->matrix[i][j] = otherMatrix.matrix[i][j];
			}
		}
	}

	~Matrix() { //d'tor
		for (int i = 0; i < row; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	Matrix<row, col, T> operator=(const Matrix<row, col, T>& other) { // = operator
		if (this == &other) { //if its the same matrix return her
			return *this;
		}

		for (int i = 0; i < row; i++) { // deleting the previous matrix
			delete[] matrix[i];
		}

		matrix = new T* [row]; // allocate new matrix cell's
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[col];
		}

		for (int i = 0; i < row; i++) { // copy other matrix value's
			for (int j = 0; j < col; j++) {
				this->matrix[i][j] = other.matrix[i][j];
			}
		}

		this->value = other.value; // copy value	
		return *this;
	}

	friend Matrix<row, col, T> operator+(const Matrix& matrix1, const Matrix& matrix2) { // + operator
		Matrix<row, col, T> temp;
		for (int i = 0;i < row;i++) {
			for (int j = 0; j < col; j++) {
				temp.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
			}
		}
		return temp;
	}

	friend Matrix<row, col, T> operator-(const Matrix& matrix1, const Matrix& matrix2) { // - operator
		Matrix<row, col, T> temp;
		for (int i = 0;i < row;i++) {
			for (int j = 0; j < col; j++) {
				temp.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
			}
		}
		return temp;
	}

	T& operator() (int i, int j) const { // () operator
		return this->matrix[i][j];
	}

	Matrix<row, col, T> operator*(const T& other) { // * numbers
		
		Matrix<row, col, T> tmp(*this); // copy matrix by C'tor to tmp

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				tmp.matrix[i][j] = tmp.matrix[i][j] * other; 
			}
		}
		return tmp;
	}

	Matrix& operator++() { // matrix ++
		*this = (*this + 1);
		return *this;
	}


	const Matrix operator++(int) { // ++ matrix
		Matrix old = *this;
		++(*this);
		return old;
	}

	Matrix& operator--() { // matrix--
		*this = (*this - 1);
		return *this;
	}

	const Matrix operator--(int) { // --matrix
		Matrix old = *this;
		--(*this);
		return old;
	}

	Matrix operator-() { // -1* oprator
		Matrix temp = *this;
		temp =  (temp * (-1));
		return temp;
	}

	T trace() { // return trace of the matrix
		T trace = 0;
		int number = 0;
		T* diagonal = getDiag(number); // get diagonal value
		for (int i = 0; i < number; i++) {
			trace = trace + diagonal[i]; // sum diagonal value
		}
		return trace;
	}

	T* getDiag(int& number) { //getDiag
		if (row < col) 
			number = row;
		else 
			number = col;
		// allocate new array for diag 
		T* diagArr= new T[number]; 
		for (int i = 0; i < number ; i++) { // get diag matrix values to diag Array 
				diagArr[i] = this->matrix[i][i];
		}
	
		return diagArr; 
	}

	friend std::ostream& operator<<(std::ostream& out, const Matrix<row, col, T>& printMatrix) {

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				out << printMatrix.matrix[i][j] << " ";
			}
			cout << endl;
		}
		return out;
	}

	friend Matrix<row, col, T> operator-=(const Matrix& matrix1, const Matrix& matrix2) { // -= operator
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix1.matrix[i][j] =matrix1.matrix[i][j]- matrix2.matrix[i][j];
			}
		}
		return matrix1;
	}


	friend Matrix<row, col, T> operator+=(const Matrix& matrix1, const Matrix& matrix2) { // += operator
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				matrix1.matrix[i][j] =matrix1.matrix[i][j] + matrix2.matrix[i][j];
			}
		}
		return matrix1;
	}
};




