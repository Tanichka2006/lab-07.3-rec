#include <iostream>
#include <iomanip>
using namespace std;

void CreateMatrix(int** matrix, int rows, int cols, int i = 0, int j = 0);
void PrintMatrix(int** matrix, int rows, int cols, int i = 0, int j = 0);
int CountRowsWithZero(int** matrix, int rows, int cols, int i = 0, int j = 0);
void FindColumnWithLongestSeries(int** matrix, int rows, int cols, int& column, int& maxSeriesLength, int j = 0, int i = 1, int currentSeriesLength = 1);

int main() {
    int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    CreateMatrix(matrix, rows, cols);
    cout << "Matrix:" << endl;
    PrintMatrix(matrix, rows, cols);

    int zeroRows = CountRowsWithZero(matrix, rows, cols);
    cout << "Number of rows with at least one zero element: " << zeroRows << endl;

    int column = 0, maxSeriesLength = 0;
    FindColumnWithLongestSeries(matrix, rows, cols, column, maxSeriesLength);
    cout << "Column with the longest series of identical elements: " << column << " (length = " << maxSeriesLength << ")" << endl;

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

// –екурсивне заповненн€ матриц≥
void CreateMatrix(int** matrix, int rows, int cols, int i, int j) {
    if (i >= rows) return;
    cout << "matrix[" << i << "][" << j << "] = ";
    cin >> matrix[i][j];
    if (j + 1 < cols) {
        CreateMatrix(matrix, rows, cols, i, j + 1);
    }
    else {
        CreateMatrix(matrix, rows, cols, i + 1, 0);
    }
}

// –екурсивне виведенн€ матриц≥
void PrintMatrix(int** matrix, int rows, int cols, int i, int j) {
    if (i >= rows) return;
    cout << setw(4) << matrix[i][j];
    if (j + 1 < cols) {
        PrintMatrix(matrix, rows, cols, i, j + 1);
    }
    else {
        cout << endl;
        PrintMatrix(matrix, rows, cols, i + 1, 0);
    }
}

// –екурсивний п≥драхунок р€дк≥в з нульовими елементами
int CountRowsWithZero(int** matrix, int rows, int cols, int i, int j) {
    if (i >= rows) return 0; // ”мова завершенн€: пройдено вс≥ р€дки

    if (j < cols) {
        if (matrix[i][j] == 0) return 1 + CountRowsWithZero(matrix, rows, cols, i + 1); // «найдено нуль
        return CountRowsWithZero(matrix, rows, cols, i, j + 1); // ѕерев≥рка наступного елемента в р€дку
    }
    return CountRowsWithZero(matrix, rows, cols, i + 1); // ѕерев≥рка наступного р€дка
}

// –екурсивний пошук стовпц€ з найдовшою сер≥Їю однакових елемент≥в
void FindColumnWithLongestSeries(int** matrix, int rows, int cols, int& column, int& maxSeriesLength, int j, int i, int currentSeriesLength) {
    if (j >= cols) return; // ”мова завершенн€: пройдено вс≥ стовпц≥

    if (i < rows) {
        if (matrix[i][j] == matrix[i - 1][j]) {
            currentSeriesLength++;
            if (currentSeriesLength > maxSeriesLength) {
                maxSeriesLength = currentSeriesLength;
                column = j;
            }
        }
        else {
            currentSeriesLength = 1;
        }
        FindColumnWithLongestSeries(matrix, rows, cols, column, maxSeriesLength, j, i + 1, currentSeriesLength); // –екурс≥€ по р€дках
    }
    else {
        FindColumnWithLongestSeries(matrix, rows, cols, column, maxSeriesLength, j + 1, 1, 1); // ѕереход до наступного стовпц€
    }
}
