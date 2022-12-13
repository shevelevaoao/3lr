#include <iostream>
#include <string>
#include <chrono>
#include <Windows.h>

using namespace std;

//������ ��������� �������
void swap(int* array, int first, int second) {
	int temp = array[second];
	array[second] = array[first];
	array[first] = temp;
}

//���������� ��������� (������, ������ � ������� - O(n^2))
void insertionSort(int* array, int size) {
	for (int i = 1; i < size; ++i) {
		int j = i;
		while (j >= 0 && array[j] < array[j - 1]) {
			swap(array, j, j - 1);
			--j;
		}
	}
}

//���������� ������� (������, ������ � ������� - O(n^2))
void selectionSort(int* array, int size) {
	for (int i = 0; i < size - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < size; ++j) {
			if (array[j] < array[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swap(array, i, minIndex);
		}
	}
}

//����������� ���������� (������, ������ � ������� - O(n^2))
void bubbleSort(int* array, int size) {
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - 1; ++j) {
			if (array[j] > array[j + 1]) {
				swap(array, j, j + 1);
			}
		}
	}
}

//������� ����������� ��� ���������� ��������
void merge(int* array, int left, int middle, int right) {
	int subArrayOne = middle - left + 1;
	int subArrayTwo = right - middle;
	int* leftArray = new int[subArrayOne];
	int* rightArray = new int[subArrayTwo];
	for (int i = 0; i < subArrayOne; ++i) {
		leftArray[i] = array[left + i];
	}
	for (int i = 0; i < subArrayTwo; ++i) {
		rightArray[i] = array[middle + 1 + i];
	}
	int indexOfSubArrayOne = 0;
	int indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

//����������� ���������� ��������
void mergeSortRecursive(int* array, int left, int right) {
	if (left >= right) {
		return;
	}
	int middle = left + (right - left) / 2;
	mergeSortRecursive(array, left, middle);
	mergeSortRecursive(array, middle + 1, right);
	merge(array, left, middle, right);
}

//���������� �������� (������, ������ � ������� - O(n log n))
void mergeSort(int* array, int size) {
	mergeSortRecursive(array, 0, size - 1);
}

//���������� ����� (������ - O(n log^2 n), ������ - O(n^2), ������� - O(n (log n)^2))
void shellSort(int* array, int size) {
	for (int gap = size / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < size; ++i) {
			int temp = array[i];
			int j;
			for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
				array[j] = array[j - gap];
			}
			array[j] = temp;
		}
	}
}

int partition(int* array, int left, int right)
{
	int pivot = array[right];
	int i = (left - 1);
	for (int j = left; j <= right - 1; j++) {
		if (array[j] < pivot) {
			i++;
			swap(array, i, j);
		}
	}
	swap(array, i + 1, right);
	return (i + 1);
}

//����������� ������� ����������
void quickSortRecursive(int arr[], int left, int right)
{
	if (left < right) {
		int pi = partition(arr, left, right);
		quickSortRecursive(arr, left, pi - 1);
		quickSortRecursive(arr, pi + 1, right);
	}
}

//������� ���������� (������ � ������� - O(n log n), ������ - O(n^2))
void quickSort(int* array, int size) {
	quickSortRecursive(array, 0, size - 1);
}

int* inputArray(int size) {
	int* result = new int[size];
	cout << "������� " << size << " ����� ������� ����� ������: ";
	for (int i = 0; i < size; ++i) {
		cin >> result[i];
	}
	return result;
}

void printArray(int* array, int size) {
	for (int i = 0; i < size; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");


	string command;

	do {
		int size;
		int* array;
		cin >> command;

		if (command == "help") {
			cout << "������ ������:" << endl
				<< "insertion - ���������� ���������" << endl
				<< "selection - ���������� �������" << endl
				<< "bubble - ����������� ����������" << endl
				<< "merge - ���������� ��������" << endl
				<< "shell - ���������� �����" << endl
				<< "quick - ������� ����������" << endl
				<< "exit - �����" << endl;
		}
		else if (command == "insertion") {
			cout << "������� ������ �������: ";
			cin >> size;
			array = inputArray(size);
			auto begin = chrono::high_resolution_clock::now();
			insertionSort(array, size);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> spent = end - begin;
			cout << "��������� �������: " << spent.count() << " ��" << endl;
			printArray(array, size);
			delete[] array;
		}
		else if (command == "selection") {
			cout << "������� ������ �������: ";
			cin >> size;
			array = inputArray(size);
			auto begin = chrono::high_resolution_clock::now();
			selectionSort(array, size);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> spent = end - begin;
			cout << "��������� �������: " << spent.count() << " ��" << endl;
			printArray(array, size);
			delete[] array;
		}
		else if (command == "bubble") {
			cout << "������� ������ �������: ";
			cin >> size;
			array = inputArray(size);
			auto begin = chrono::high_resolution_clock::now();
			bubbleSort(array, size);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> spent = end - begin;
			cout << "��������� �������: " << spent.count() << " ��" << endl;
			printArray(array, size);
			delete[] array;
		}
		else if (command == "merge") {
			cout << "������� ������ �������: ";
			cin >> size;
			array = inputArray(size);
			auto begin = chrono::high_resolution_clock::now();
			mergeSort(array, size);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> spent = end - begin;
			cout << "��������� �������: " << spent.count() << " ��" << endl;
			printArray(array, size);
			delete[] array;
		}
		else if (command == "shell") {
			cout << "������� ������ �������: ";
			cin >> size;
			array = inputArray(size);
			auto begin = chrono::high_resolution_clock::now();
			shellSort(array, size);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> spent = end - begin;
			cout << "��������� �������: " << spent.count() << " ��" << endl;
			printArray(array, size);
			delete[] array;
		}
		else if (command == "quick") {
			cout << "������� ������ �������: ";
			cin >> size;
			array = inputArray(size);
			auto begin = chrono::high_resolution_clock::now();
			quickSort(array, size);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> spent = end - begin;
			cout << "��������� �������: " << spent.count() << " ��" << endl;
			printArray(array, size);
			delete[] array;
		}
	} while (command != "exit");

	return 0;
}
