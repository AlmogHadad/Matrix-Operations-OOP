#pragma once
#include "Matrix.h"
#define YES 2 //Symbolizes if the matrix or matrixes found.

template <int row, int col, typename T> 
struct MatrixNode{
	Matrix<row,col,T> mat;
	MatrixNode* next = NULL; 
	MatrixNode* pri = NULL;
};

template <int row, int col, typename T = int>
class MatrixContainer
{
private:
	MatrixNode<row, col, T>* tail = NULL; // the tail of the linked list
	MatrixNode<row, col, T>* head = NULL; // the head of the linked list
	int count = 0; // matrix couner

public:
	void addMatrix(const Matrix<row,col,T>& newMat) { // adding matrix to the list
		MatrixNode<row, col, T> *temp = new MatrixNode<row, col, T>; //add new node
		temp->mat = newMat;
		temp->next = NULL;
		
		if (head == NULL) { //if the list is empty, add and change tail
			this->head = temp;
			this->tail = temp;
		} else // if the list not empty, add and change the tail
		{
			temp->pri = tail;
			this->tail->next = temp;
			this->tail = tail->next;
		}
		count++; // add 1 matrix to matrix counter
	}

	void removeLastMatrix() { 
		MatrixNode<row, col, T> *temp = tail->pri; //save the privous 
		delete tail; // delete the tail
		temp->next = NULL; // update date
		this->tail = temp;
		count--;
	}

	Matrix<row,col,T> addMatricesAtIndexes(int i,int j) {  
		int index = 0;
		int found = 0;
		MatrixNode<row, col, T> *temp = head; //save the head
	
		Matrix<row, col,T> iMatrix; //to save the wanted matrix
		Matrix<row, col,T> jMatrix;
	
		//while the list not empty and the matrixs not found
		while ((temp != NULL) && (found != YES))  { 
			if (index == i) {
			    iMatrix = temp->mat; //save the matrix
				found++; //add to found
			}
			if (index == j) {
				jMatrix = temp->mat; //save matrix
				found++; //add to found
			}
			//move to the next index, the next matrix in the list.
			index++; 
			temp = temp->next; 
		}
		 //return the adding
		Matrix<row, col, T> matrix = (jMatrix + iMatrix);
		return matrix;
	}

	Matrix<row,col,T> mulMatAtIndexByScalar(int matrixIndex, int scalar) { 
		int index = 0;
		int found = 0;
		MatrixNode<row, col, T> *temp = head; 
		//while the index not found and the list not empty
		while (index != matrixIndex) { //move the index and to the next matrix in the list.
			index++; 
			temp = temp->next; 
		}

		return (temp->mat * scalar);	
	}

	template <int row, int col, typename T = int>
	friend std::ostream& operator<<(std::ostream& out, const MatrixContainer<row, col, T>& printMatrixes) {
		MatrixNode<row,col,T> *temp = printMatrixes.head; //save the head
		cout << "There are " << printMatrixes.count << " matrices in the container. The matrices:" << endl; 
		while (temp != NULL) { // print all matrixes (using << matrix)
			cout << temp->mat << endl;
			temp = temp->next;
		}
		return out;
	}
};