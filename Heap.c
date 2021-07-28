#include <stdio.h>
#include <stdlib.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
 char cName[50];
 float balance;
 int order;
}Item;

typedef struct
{
    int size;
    Item* array;
}MaxHeap;

void swap(Item* a, Item* b) {
     Item t = *a;
     *a = *b;
     *b = t;
}

/*
 * Heapify index i in array of Items with size n
 */
void max_heapify(MaxHeap* maxHeap, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < maxHeap->size &&
        maxHeap->array[left].balance > maxHeap->array[largest].balance)
        largest = left;
    if (left < maxHeap->size && maxHeap->array[left].balance == maxHeap->array[largest].balance && maxHeap->array[left].order < maxHeap->array[largest].order)
        largest = left;

    if (right < maxHeap->size &&
        maxHeap->array[right].balance > maxHeap->array[largest].balance)
        largest = right;
    if (right < maxHeap->size && maxHeap->array[right].balance == maxHeap->array[largest].balance && maxHeap->array[right].order < maxHeap->array[largest].order)
        largest = right;

    if (largest != i)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[i]);
        max_heapify(maxHeap, largest);
    }
}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
MaxHeap* construct_PQ(Item*arr,int n)
{
	int i;
    MaxHeap* maxHeap = (MaxHeap*) malloc(sizeof(MaxHeap));
    maxHeap->size = n;
    maxHeap->array = arr;
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
    max_heapify(maxHeap, i);
    return maxHeap;
}

void heapSort(Item* array, int size)
{
    MaxHeap* maxHeap = construct_PQ(array, size);

    while (maxHeap->size > 1)
    {
        swap(&maxHeap->array[0],&maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;
        max_heapify(maxHeap, 0);
    }
}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item*arr,int n)
{
    MaxHeap* maxHeap = construct_PQ(arr,n);
	Item returnItem = maxHeap->array[0];
	maxHeap->array[0]=maxHeap->array[n];
	maxHeap->size--;
	max_heapify(maxHeap,0);
	return returnItem;
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
    int i = 0;
	FILE *fp;
    fp = fopen (fname,"r");
    if(!fp){
     printf("Error opening file\n" );
   }
    while(!feof(fp)){
    fscanf(fp, "%s %f\n", arr[i].cName, &arr[i].balance);
    arr[i].order=i+1;
    ++i;
    }
    return i;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
	int i;
    for (i = 0; i < n; ++i){
        Item value =extract_maximum(arr,n);
        printf("%d - %s %.2f %d\n",i+1,value.cName,value.balance,value.order);
    }
}
/*
 *
 */
int main(){
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile("Heap.txt",customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
