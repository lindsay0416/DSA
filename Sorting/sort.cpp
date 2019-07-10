// Example program
#include <iostream>
#include <string>


void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void printOut(const char* sortType, int array[], int iteration) 
{
	printf("%s iterations: %d\n", sortType, iteration);
	printf("Sorted array: \n");
	for (int i = 0; i < 1000; i++)
	{
		printf("array[%d] =%d \n", i, array[i]);
	}
	printf("============================\n");
}

// bubble sort
int* bubbleSort(int array[], int len) 
{
	int i, j;
	for (i = 0; i < len - 1; i++) 
	{
		for (j = i + 1; j < len; j++) 
		{
			if (array[i] > array[j]) 
			{
				swap(&array[i], &array[j]);
			}
		}
	}
	return array;
}
int bubbleSortIteration(int array[], int len) 
{
	int i, j, iteration;
	for (i = 0; i < len - 1; i++) 
	{
		for (j = i + 1; j < len; j++) 
		{
			if (array[i] > array[j]) 
			{
				swap(&array[i], &array[j]);
			}
			iteration++;
		}
	}
	return iteration;
}

// insertion sort
int* insertionSort(int array[], int len)
{
   int i, j, num;
   for (i = 1; i < len; i++) 
   {
       num = array[i];
       j = i-1;
       while (j >= 0 && array[j] > num) 
	   {
           array[j+1] = array[j];
           j = j-1; 
       }
       array[j+1] = num;
   }
   return array;
}
int insertionSortIteration(int array[], int len) 
{
   int i, j, num, iteration;
   for (i = 1; i < len; i++)
   {
       num = array[i];
       j = i-1;
       while (j >= 0 && array[j] > num) 
	   {
           array[j+1] = array[j];
           j = j-1; 
       }
       array[j+1] = num;
	   iteration++;
   }
   return iteration;
}

// selection sort
int* selectionSort(int array[], int len) 
{
    int i, j, min_idx;
    for (i = 0; i < len-1; i++) 
	{
        min_idx = i;
        for (j = i+1; j < len; j++) 
		{
          	if (array[j] < array[min_idx]) 
			{
				min_idx = j;
			}
		}
        swap(&array[min_idx], &array[i]);
    }
   return array;
}

int selectionSortIteration(int array[], int len) {
    int i, j, min_idx, iteration;
    for (i = 0; i < len-1; i++) {
        min_idx = i;
        for (j = i+1; j < len; j++) {
          	if (array[j] < array[min_idx]) {
				min_idx = j;
			}
	   		iteration++;
		}
        swap(&array[min_idx], &array[i]);
    }
   return iteration;
}

int main() {
	int ranInt[1000];
	for (int i = 0; i < 1000; i++) {
		ranInt[i] = rand() % 900 - 200;
	}
	int arrayLen = sizeof(ranInt) / sizeof(ranInt[0]);

	// bubble sort
	int* bubbleSortA = bubbleSort(ranInt, arrayLen);
	int bubbleSortI = bubbleSortIteration(ranInt, arrayLen);
	printOut("bubble sort", bubbleSortA, bubbleSortI);

	// insertion sort
	int* insertionSortA = insertionSort(ranInt, arrayLen);
	int insertionSortI = insertionSortIteration(ranInt, arrayLen);
	printOut("insertion sort", insertionSortA, insertionSortI);

	// selection sort
	int* selectionSortA = selectionSort(ranInt, arrayLen);
	int selectionSortI = selectionSortIteration(ranInt, arrayLen);
	printOut("selection sort", selectionSortA, selectionSortI);
}