// HeapConstruction.cpp : Defines the entry point for the console application.
//

/**
*@author Csillag Robert
*/

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "Profiler.h"

#define MAX_SIZE 10000

Profiler profiler("Heap Construction Median case");

//Begin Bottom-Up Heap Construction

void max_heapify(int* arr_to_heap, int i, int heap_size, Operation* bua, Operation* buc) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	(*buc).count();
	if ((left < heap_size) && (arr_to_heap[left] > arr_to_heap[i])) {
		largest = left;
	}

	(*buc).count();
	if ((right < heap_size) && (arr_to_heap[right] > arr_to_heap[largest])) {
		largest = right;
	}

	if (largest != i) {
		(*bua).count(3);
		int aux = arr_to_heap[i];
		arr_to_heap[i] = arr_to_heap[largest];
		arr_to_heap[largest] = aux;
		max_heapify(arr_to_heap, largest, heap_size, bua, buc);
	}
}

void build_heap_bottom_up(int* arr, int arr_length) {
	Operation buc = profiler.createOperation("bottom_up_comp", arr_length);
	Operation bua = profiler.createOperation("bottom_up_attr", arr_length);

	int heap_size_arr = arr_length;
	for (int i = (arr_length ) / 2; i >= 0; i--) {
		max_heapify(arr, i, heap_size_arr, &bua, &buc);
	}
}

//End Bottom-Up Heap Construction

//Begin Top-Down Heap Construction

void heap_increase_key(int* arr, int i, int key, Operation* tda, Operation* tdc) {
	(*tdc).count();
	if (key < arr[i]) {
		exit (10);
	}
	(*tda).count();
	arr[i] = key;
	while (i > 1 && arr[i / 2] < arr[i]) {
		(*tdc).count();
		(*tda).count(3);
		int aux = arr[i];
		arr[i] = arr[i/2];
		arr[i/2] = aux;
		i = i / 2;
	}
	if (i > 1) {
		(*tdc).count();
	}
}

void max_heap_insert(int* arr, int* heap_size, int key, Operation* tda, Operation* tdc) {
	(*heap_size)++;
	arr[(*heap_size)] = INT_MIN;
	(*tda).count();
	heap_increase_key(arr, (*heap_size), key, tda, tdc);
}

void build_heap_top_down(int* arr, int arr_length) {
	Operation tdc = profiler.createOperation("top_down_comp", arr_length);
	Operation tda = profiler.createOperation("top_down_attr", arr_length);
	int heap_size = 1;
	for (int i = 2; i <= arr_length; i++) {
		max_heap_insert(arr, &heap_size, arr[i], &tda, &tdc);
	}
}

//End Top-Down Heap Construction

int main()
{

	int arr[MAX_SIZE];
	int arr2[MAX_SIZE];

	for (int n = 100; n <= MAX_SIZE; n += 100) {
		for (int i = 0; i < 5; i++) {
			FillRandomArray(arr, n, 10, 100000, false, 0);
			memcpy(arr2, arr, sizeof(arr2));
			build_heap_bottom_up(arr, n);
			build_heap_top_down(arr2, n);
		}
	}


	profiler.divideValues("bottom_up_comp", 5);
	profiler.divideValues("bottom_up_attr", 5);
	profiler.divideValues("top_down_comp", 5);
	profiler.divideValues("top_down_attr", 5);

	profiler.addSeries("total_bottom_up", "bottom_up_comp", "bottom_up_attr");
	profiler.addSeries("total_top_down", "top_down_comp", "top_down_attr");

	profiler.createGroup("median_case_comp", "bottom_up_comp", "top_down_comp");
	profiler.createGroup("median_case_attr", "bottom_up_attr", "top_down_attr");
	profiler.createGroup("median_case_total", "total_bottom_up", "total_top_down");

	profiler.reset("Heap Construction Defav case");

	for (int n = 100; n <= MAX_SIZE; n += 100) {
		FillRandomArray(arr, n, 10, 100000, false, 1);
		memcpy(arr2, arr, sizeof(arr2));
		build_heap_bottom_up(arr, n);
		build_heap_top_down(arr2, n);
	}

	profiler.addSeries("total_bottom_up", "bottom_up_comp", "bottom_up_attr");
	profiler.addSeries("total_top_down", "top_down_comp", "top_down_attr");

	profiler.createGroup("defav_case_comp", "bottom_up_comp", "top_down_comp");
	profiler.createGroup("defav_case_attr", "bottom_up_attr", "top_down_attr");
	profiler.createGroup("defav_case_total", "total_bottom_up", "total_top_down");


	profiler.showReport();
    return 0;
}

