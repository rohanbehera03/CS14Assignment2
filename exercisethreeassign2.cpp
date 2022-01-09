// Assignment 2, exercise 3
// To compile, run:
//    g++ -std=c++11 exercise_3.cpp

#include <chrono>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
/*
 * Implement the 4 in-place sort functions for exercise 3.a.
 */

/* a sorting algorithm that treats the input as two parts, 
 * a sorted part and an unsorted part, and repeatedly inserts 
 *  the next value from the unsorted part into the correct location in the sorted part.
 */

//Setting global variables for each sort for each array
double firstInsertion, firstQuicksort, firstHeap, firstMerge;
double secondInsertion, secondQuicksort, secondHeap, secondMerge;
double thirdInsertion, thirdQuicksort, thirdHeap, thirdMerge;
double fourthInsertion, fourthQuicksort, fourthHeap, fourthMerge;
double fifthInsertion, fifthQuicksort, fifthHeap, fifthMerge;
double sixthInsertion, sixthQuicksort, sixthHeap, sixthMerge;

void insertion_sort(int array[], size_t size) {
  // Implement here
    int n, j;
    for (int i = 1; i < size; i++) {
        n = array[i];
        j = i-1;
        while (j >= 0 && array[j] > n) {
            array[j+1] = array[j];
            j = j-1;
        }
        array[j+1] = n;
    }
}

//Finds pivot element and divides array into two parts so 
//elements on the left are smaller than the ones on the right
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int partIndex = low;
    for (int i = low; i < high; i++) {
        if (array[i] <= pivot) {
            swap(array[i], array[partIndex]);
            partIndex++;
        }
    }
    swap(array[partIndex], array[high]);
    return partIndex;
}

void quicksortCopy(int array[], int low, int high) {
  // Implement here
    if (low < high) {
        int partIndex = partition(array, low, high);
        quicksortCopy(array, low, partIndex-1);
        quicksortCopy(array, partIndex+1, high);
    }
}

void quick_sort(int array[], size_t size) {
    int low = 0;
    int high = size-1;
    quicksortCopy(array, low, high);
}

//build heap with given elements
//Create max heap to sort elements in ascending order
//Swap root node with last node and delete last node from heap
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
      
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int array[], size_t size) {
  // Implement here
    for (int i = size/2-1; i >= 0; i--) {
        heapify(array, size, i);
    }
    
    for (int i = size-1; i >= 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

// divides the input array into two halves, calls itself for the two halves, 
// and then merges the two sorted halves.
void merge(int array[], int low, int middle, int high) {
    int num1 = middle-low+1;
    int num2 = high-middle;
    
    int leftArray[num1], rightArray[num2];
 
    for (int i = 0; i < num1; i++) {
        leftArray[i] = array[low+i];
    }
    for (int j = 0; j < num2; j++) {
        rightArray[j] = array[middle+j+1];
    }
    
    int i = 0;
    int j = 0;
    int k = low;
    
    while (i < num1 && j < num2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        }
        else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    while (i < num1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < num2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}
void mergesortCopy(int array[], int left, int right) {
  // Implement here
    if (left < right) {
        int middle;
        middle = left + (right-left)/2;
        mergesortCopy(array, left, middle);
        mergesortCopy(array, middle+1, right);
        merge(array, left, middle, right);
    }
}

void merge_sort(int array[], size_t size) {
    int low = 0;
    int high = size-1;
    mergesortCopy(array, low, high);
}

/*
 * Generate random integers for exercise 3.b
 */
int *random_ints(size_t size) {
  int *numbers = new int[size];
  // Generate random numbers here
  srand(time(0));
  for (int i = 0; i < size; i++) {
        numbers[i] = (rand() % (100)+1); //setting range of random numbers from 0-100
  }
  return numbers;
}


int randarrayten() {
    for (int i = 0; i < 30; i++) {
        int *firstarray = random_ints(10);

         //insertion sort time output
        auto start_time = chrono::high_resolution_clock::now();
        insertion_sort(firstarray, 10);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
          cout << "Length 10 Array Insertion sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
          firstInsertion = duration.count();
          
        //quicksort time output
        start_time = chrono::high_resolution_clock::now();
        quick_sort(firstarray, 10);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Length 10 Array Quicksort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
        firstQuicksort = duration.count();
        
        //heapsort time output
        start_time = chrono::high_resolution_clock::now();
        heap_sort(firstarray, 10);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Length 10 Array Heap sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
        firstHeap = duration.count();
        
        //merge sort time output
        start_time = chrono::high_resolution_clock::now();
        merge_sort(firstarray, 10);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Length 10 Array Merge sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
        firstMerge = duration.count();
    }
        cout << endl;
}
 
int randarrayhundred() {
        for (int i = 0; i < 30; i++) {
            int *secondarray = random_ints(100);
             //insertion sort time output
            auto start_time = chrono::high_resolution_clock::now();
            insertion_sort(secondarray, 100);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
              cout << "Length 100 array Insertion sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
              secondInsertion = duration.count();
              
            //quicksort time output
            start_time = chrono::high_resolution_clock::now();
            quick_sort(secondarray, 100);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 100 Array Quicksort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            secondQuicksort = duration.count();
            
            //heapsort time output
            start_time = chrono::high_resolution_clock::now();
            heap_sort(secondarray, 100);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 100 Array Heap sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            secondHeap = duration.count();
            
            //merge sort time output
            start_time = chrono::high_resolution_clock::now();
            merge_sort(secondarray, 100);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 100 Array Merge sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            secondMerge = duration.count();
        }
            cout << endl;
}
 
int randarraythousand() {
        for (int i = 0; i < 30; i++) {
            int *thirdarray = random_ints(1000);

            //insertion sort time output
            auto start_time = chrono::high_resolution_clock::now();
            insertion_sort(thirdarray, 1000);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
              cout << "Length 1000 Array Insertion sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
              thirdInsertion = duration.count();
              
            //quicksort time output
            start_time = chrono::high_resolution_clock::now();
            quick_sort(thirdarray, 1000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 1000 Array Quicksort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            thirdQuicksort = duration.count();
            
            //heapsort time output
            start_time = chrono::high_resolution_clock::now();
            heap_sort(thirdarray, 1000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 1000 Array Heap sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            thirdHeap = duration.count();
            
            //merge sort time output
            start_time = chrono::high_resolution_clock::now();
            merge_sort(thirdarray, 1000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 1000 Array Merge sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            thirdMerge = duration.count();
        }
            cout << endl;
}
 
int randarraytenthousand() {
        for (int i = 0; i < 30; i++) {
            int *fourtharray = random_ints(10000);

            //insertion sort time output
            auto start_time = chrono::high_resolution_clock::now();
            insertion_sort(fourtharray, 10000);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
              cout << "Length 10000 Array Insertion sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
              fourthInsertion = duration.count();
              
            //quicksort time output
            start_time = chrono::high_resolution_clock::now();
            quick_sort(fourtharray, 10000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 10000 Array Quicksort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            fourthQuicksort = duration.count();
            
            //heapsort time output
            start_time = chrono::high_resolution_clock::now();
            heap_sort(fourtharray, 10000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 10000 Array Heap sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            fourthHeap = duration.count();
            
            //merge sort time output
            start_time = chrono::high_resolution_clock::now();
            merge_sort(fourtharray, 10000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 10000 Array Merge sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            fourthMerge = duration.count();
    
        }
            cout << endl;
}

int randarrayhundredthousand() {
        for (int i = 0; i < 30; i++) {
            int *fiftharray = random_ints(100000);
            //insertion sort time output
            auto start_time = chrono::high_resolution_clock::now();
            insertion_sort(fiftharray, 100000);
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
              cout << "Length 100000 Array Insertion sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
              fifthInsertion = duration.count();
              
            //quicksort time output
            start_time = chrono::high_resolution_clock::now();
            quick_sort(fiftharray, 100000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 100000 Array Quicksort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            fifthQuicksort = duration.count();
            
            //heapsort time output
            start_time = chrono::high_resolution_clock::now();
            heap_sort(fiftharray, 100000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 100000 Array Heap sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            fifthHeap = duration.count();
            
            //merge sort time output
            start_time = chrono::high_resolution_clock::now();
            merge_sort(fiftharray, 100000);
            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
            cout << "Length 100000 Array Merge sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
            fifthMerge = duration.count();
        }
            cout << endl;
}

int randarraymillion() { 
    for (int i = 0; i < 30; i++) {
        int *sixtharray = random_ints(1000000);
    
         //insertion sort time output
        auto start_time = chrono::high_resolution_clock::now();
        insertion_sort(sixtharray, 1000000);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
          cout << "Length of a million Array Insertion sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
          sixthInsertion = duration.count();
          
        //quick sort time output
        start_time = chrono::high_resolution_clock::now();
        quick_sort(sixtharray, 1000000);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Length of a million Array Quicksort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
        sixthQuicksort = duration.count();
        
        //heap sort time output
        start_time = chrono::high_resolution_clock::now();
        heap_sort(sixtharray, 1000000);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Length of a million Array Heap sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
        sixthHeap = duration.count();
        
        //merge sort time output
        start_time = chrono::high_resolution_clock::now();
        merge_sort(sixtharray, 1000000);
        end_time = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Length of a million Array Merge sort elapsed time in nanoseconds: " << duration.count() << " ns" << endl;
        sixthMerge = duration.count();
    }
        cout << endl;
}

double averageSortingTime() {
    int i;
    double avgtimeInsertion[], avgtimeQuicksort[], avgtimeHeap[], avgtimeMerge[];
        avgtimeInsertion[i] = (firstInsertion + secondInsertion + thirdInsertion + fourthInsertion + fifthInsertion + sixthInsertion)/6;
        avgtimeQuicksort[i] = (firstQuicksort + secondQuicksort + thirdQuicksort + fourthQuicksort + fifthQuicksort + sixthQuicksort)/6;
        avgtimeHeap[i] = (firstHeap + secondHeap + thirdHeap + fourthHeap + fifthHeap + sixthHeap)/6;
        avgtimeMerge[i] = (firstMerge + secondMerge + thirdMerge + fourthMerge + fifthMerge + sixthMerge)/6;
        cout << "Average insertion sort time: " << avgtimeInsertion[i] << endl;
        cout << "Average quicksort time: " << avgtimeQuicksort[i] << endl;
        cout << "Average heapsort time: " << avgtimeHeap[i] << endl;
        cout << "Average mergesort time: " << avgtimeMerge[i] << endl;
    
}

int main() {
        
        int generateArray1 = randarrayten();
        cout << generateArray1 << endl;

        int generateArray2 = randarrayhundred();
        cout << generateArray2 << endl;

        int generateArray3 = randarraythousand();
        cout << generateArray3 << endl;

        int generateArray4 = randarraytenthousand();
        cout << generateArray4 << endl;
        
        int generateArray5 = randarrayhundredthousand();
        cout << generateArray5 << endl;
        
//        int generateArray6 = randarraymillion();
//        cout << generateArray6 << endl;
    
        double copyavgsortTime = averageSortingTime();
        cout << copyavgsortTime << endl;
    
    return 0;
}