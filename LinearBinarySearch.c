/*
 Name: Jason Yeoh
 Date: 09.10.17

 Desc: Program copies array, sorts elements in the list ascendingly,
 and finds the element using linear/binary search algorithm.
 */

#include <stdio.h>
#include <stdlib.h>

void arrayCopy(int fromArray[], int toArray[], int size);
void myFavoriteSort(int arr[], int size);
int linSearch(int arr[], int size, int target, int* numComparisons);
int binSearch(int arr[], int size, int target, int* numComparisons);

//----------------------------------------------------------------------
// Main Program
int main(int argc, char** argv)
{
    //Declare variables
    int value, targetValue, numComparisons, unsortedLocation, sortedLocation, i;
    int currentUse = 0;
    int size = 100;
    int *fromArray, *toArray;
    
    //Dynamically allocate fromArray and toArray.
    fromArray = (int*)malloc(size * sizeof(int));
    toArray = (int*)malloc(size * sizeof(int));
    
    printf("Please enter integer values: ");
    scanf ("%d", &value);
    
    //Loop until the user entered a value of -999.
    while(value != -999) {
        // If the array is full, then execute this statement.
        if(currentUse == size) {
            int* temp;
            int i;
            
            temp = (int*)malloc(size * 2 * sizeof(int));
            
            for(i=0; i<size; i++)
                temp[i] = fromArray[i];
            
            free(fromArray);
            fromArray = temp;
            size = size * 2;    // Grow the array.
        }
        
        fromArray[currentUse] = value;
        currentUse++;
        
        scanf("%d", &value);
    }//end while(...
    
    arrayCopy(fromArray, toArray, currentUse);
    myFavoriteSort(toArray, currentUse);
    
    // Print unsorted array.
    printf("[Unsorted Array] \n");
    for(i=0; i<currentUse; i++) {
        printf(" %d", fromArray[i]);
    }//end for(...
    printf("\n");
    
    // Print sorted array.
    printf("[Sorted Array] \n");
    for(i=0; i<currentUse; i++) {
        printf(" %d", toArray[i]);
    }//end for(...
    printf("\n\n");
    
    printf("Enter value(s) to find in the list: ");
    scanf("%d", &targetValue);
    
    //Loop until the user entered a value of -999.
    while(targetValue != -999) {
        // Use LINEAR SEARCH for unsorted array.
        unsortedLocation = linSearch(fromArray, currentUse, targetValue, &numComparisons);
        
        printf("[Linear Search]\n");
        if(unsortedLocation != -1)
            printf(" %d is found in location [%d] after %d comparisons. \n", targetValue, unsortedLocation, numComparisons);
        else
            printf(" %d is not found in the list after %d comparisons. \n", targetValue, numComparisons);
        
        // Use BINARY SEARCH for sorted array.
        sortedLocation = binSearch(toArray, currentUse, targetValue, &numComparisons);
        
        printf("[Binary Search]\n");
        if(sortedLocation != -1)
            printf(" %d is found in location [%d] after %d comparisons. \n", targetValue, sortedLocation, numComparisons);
        else
            printf(" %d is not found in the list after %d comparisons. \n", targetValue, numComparisons);
        
        printf("\n");
        scanf("%d", &targetValue);
    }//end while(...
    
    return 0;
}//end int main(...


//----------------------------------------------------------------------
// Make a copy of the input values from one array to another array.
void arrayCopy(int fromArray[], int toArray[], int size)
{
    int i;
    
    for(i=0; i<size; i++) {
        toArray[i] = fromArray[i];
    }
}//end void arrayCopy(...


//----------------------------------------------------------------------
// Bubble sort the array in ascending order.
void myFavoriteSort(int arr[], int size)
{
    int i, j;
    int storeValue;
    
    for(i=0; i<size-1; i++) {
        for(j=0; j<size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                storeValue = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = storeValue;
            }//end if(...
        }//end for(...
    }//end for(...
}//end void myFavoriteSort(...


//----------------------------------------------------------------------
// Do linear search.
int linSearch(int arr[], int size, int target, int* numComparisons)
{
    int i;
    *numComparisons = 0;
    
    for(i=0; i<size; i++) {
        (*numComparisons)++;
        if(arr[i] == target)
            return i;
    }//end for(...
    
    return -1;  //If the value is not found in the list, return -1.
}//end if linSearch(...


//----------------------------------------------------------------------
// Do binary search.
int binSearch(int arr[], int size, int target, int* numComparisons)
{
    int low = 0;
    int high = size - 1;
    
    *numComparisons = 0;
    
    while(low <= high) {
        (*numComparisons)++;
        int midpoint = (low+high)/2;
        
        if(arr[midpoint] == target)
            return midpoint;
        else if(arr[midpoint] < target)
            low = midpoint + 1;
        else
            high = midpoint - 1;
    }//end while(...
    
    return -1;  //If the value is not found in the list, return -1.
}//end binSearch(...
