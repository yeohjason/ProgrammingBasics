/**
 * Name: Jason Yeoh
 * Date: 09.25.17
 * Desc: Balanced Symbol Checker (only checks for the FIRST error)
 **/

#include <stdio.h>      // to use fgets() function
#include <stdlib.h>
#include <ctype.h>      // to use toupper() function
#include <string.h>     // to use strcmp() function

#define ARRAY_SIZE 300      // string size
#define TRUE    1           // boolean TRUE
#define FALSE   0           // boolean FALSE

// Stack declaration
typedef struct stack {
    char *pArray;   // pointer to the dynamic array
    int size;       // size of the stack
    int inUse;      // "top" of the stack (or current use)
} STACK;


// Function 1: initializeStack()
//  - Initialize a stack array.
void initializeStack(STACK *string) {
    string->size = 2;   // set size as 2
    string->pArray = (char *)malloc(sizeof(char) * string->size);   // allocate a dynamic array
    string->inUse = 0;  // set top as 2
}//end initializeStack()


// Function 2: checkifStackIsEmpty()
//  - Return TRUE if the stack is EMPTY. Otherwise, return FALSE.
int checkifStackIsEmpty(STACK *string) {
    if(string->inUse == 0)
        return TRUE;
    else
        return FALSE;
}//end checkifStackIsEmpty()


// Subset of Function 3: growArray()
//  - This function is a subset of pushStack() function. It is used
//    to grow array if the inUse is full, allowing additional size
//    to the stack.
void growArray(STACK *string) {
    // (A) Allocate a new "temporary" dynamic array with (current size + 2).
    char *pTemp = (char *)malloc((sizeof(char) * string->size) + 2);
    int i;  // index for the loop below
    
    // (B) Copy the existing values from the current stack array to the
    //     "temporary" dynamic array.
    for(i = 0; i < string->size; i++)
        pTemp[i] = string->pArray[i];
    
    // (C) Deallocate the current stack array.
    free(string->pArray);
    // (D) Refer stack array variable to where "temporary" dynamic array points.
    string->pArray = pTemp;
    // (E) Update the maximum size for the stack
    string->size = string->size + 2;
}//end growArray()


// Function 3: pushStack()
//  - Push/add an element to the stack.
void pushStack(STACK *string, char value) {
    if(string->inUse == string->size)       // (A) If the array is full, grow an
        growArray(string);                  //     array. (call growArray() func.)
    
    string->pArray[string->inUse] = value;  // (B) Add the value to the stack array.
    (string->inUse)++;                      // (C) Increment the top of the stack.
}//end pushStacK()


// Function 4: popOnStack()
//  - Pop/remove an element to the stack.
void popStack(STACK *string) {
    (string->inUse)--;                      // (A) Decrement the top of the stack.
    string->pArray[string->inUse] = 0;      // (B) Set the stack value to 0.
}//end popStack()


// Function 5: accessTop()
//  - Return to the top of the stack.
int accessTop(STACK *string) {
    return string->pArray[string->inUse-1];
}//end accessTop()


// Function 6: resetStack()
//  - Somewhat similar with what we did with initializeStack() but
//    we allocate a new stack array and deallocate the current
//    stack array. Additionally, we point stack array variable to
//    the new stack array.
void resetStack(STACK *string) {
    string->size = 2;           // Re-initialize size as 2
    string->inUse = 0;          // Re-initialize top as 0
    char *ppArray = (char *)malloc(sizeof(char) * string->size);    // Allocate a new dynamic array.
    free(string->pArray);       // Deallocate the current stack array variable.
    string->pArray = ppArray;   // Refer the stack array variable to the new dynamic array.
}//end resetStack()


// Subset Function: getCorrespondingOpenSymbol()
//  - Return to its corresponding open symbol.
char getCorrespondingOpenSymbol(char value) {
    if(value == ')') return '(';
    if(value == '}') return '{';
    if(value == ']') return '[';
    if(value == '>') return '<';
    
    return '\0';
}//end getCorrespondingOpenSymbol()


// Subset Function: getCorrespondingCloseSymbol()
//  - Return to its corresponding close symbol.
char getCorrespondingCloseSymbol(char value) {
    if(value == '(') return ')';
    if(value == '{') return '}';
    if(value == '[') return ']';
    if(value == '<') return '>';

    return '\0';
}//end getCorrespondingCloseSymbol()


// Subset Function: getCorrespondingSymbol()
//  - Return to its corresponding open/close symbol.
char getCorrespondingSymbol(char value) {
    if(value == '(') return ')';
    if(value == '{') return '}';
    if(value == '[') return ']';
    if(value == '<') return '>';
    if(value == ')') return '(';
    if(value == '}') return '{';
    if(value == ']') return '[';
    if(value == '>') return '<';

    return '\0';
}//end getCorrespondingSymbol()


// Subset Function: checkIfOpenSymbol()
//  - Return TRUE if the character is an OPEN symbol. Otherwise, return FALSE.
int checkIfOpenSymbol(char value) {
    if(value == '(' || value == '{' || value == '[' || value == '<')
        return TRUE;
    else
        return FALSE;
}//end checkIfOpenSymbol()


// Subset Function: checkIfCloseSymbol()
//  - Return TRUE if the character is a CLOSE symbol. Otherwise, return FALSE.
int checkIfCloseSymbol(char value) {
    if(value == ')' || value == '}' || value == ']' || value == '>')
        return TRUE;
    else
        return FALSE;
}//end checkIfCloseSymbol()


// Subset Function: expectedSymbolChecker()
//  - Looks out for the expected symbol and places it to its appropriate position.
char expectedSymbolChecker(STACK *string, int forLoopIndex) {
    // Set the character as the expected "corresponding symbol".
    char expectedSymbol = getCorrespondingCloseSymbol( accessTop(string));
    int i;  // index for the loop below
    
    // Print spaces to point out where the expected symbol must be at place.
    for(i = 0; i < forLoopIndex; i++)
        printf(" ");
    printf("^ expecting %c \n\n", expectedSymbol);
    
    return expectedSymbol;
}//end expectedSymbolChecker()


// Subset Function: missedSymbolChecker()
//  - Looks out for the missed symbol and places it to its appropriate position.
char missedSymbolChecker(STACK *string, char value, int forLoopIndex) {
    // Set the character as the missed "corresponding symbol".
    char missedSymbol = getCorrespondingSymbol(value);
    int i;  // index for the loop below
    
    // Print spaces to point out where the missing symbol must be at place.
    for(i = 0; i < forLoopIndex; i++)
        printf(" ");
    printf("^ missing %c \n\n", missedSymbol);
    
    return missedSymbol;
}//end missedSymbolChecker()


// Subset Function: missedTopSymbol()
//  - Looks out for the missed top symbol and places it to its appropriate position.
char missedTopSymbol(STACK *string, int forLoopIndex) {
    // Set the character as the missed "corresponding symbol".
    char missedSymbol = getCorrespondingSymbol(accessTop(string));
    int i;  // index for the loop below
    
    // Print spaces to point out where the missing symbol must be at place.
    for(i = 0; i < forLoopIndex; i++)
        printf(" ");
    printf("^ missing %c \n\n", missedSymbol);
    
    return missedSymbol;
}//end missedTopSymbol()


// Main Program
int main(int argv, char** argc)
{
    STACK charList;             // Declare stack locally in main()
    char input[ARRAY_SIZE];     // Char string with ARRAY_SIZE = 300
    int isSymbolBalanced = TRUE;// Indicates if symbols are balanced
    
    initializeStack(&charList); // Initialize the stack array.
    
    // Loop until the user prompts to quit the program.
    while(1) {
        // Prompt the user to input string with maximum size of ARRAY_SIZE.
        printf("***Press 'Q' or 'q' to quit the program***\n");
        printf("Enter input: ");
        fgets(input, ARRAY_SIZE, stdin);    // Read input using fgets()
        
        // If user entered 'Q' or 'q', break out of the loop and exit.
        if(toupper(input[0]) == 'Q') {
            printf("User exits the program. \n");
            break;  // break out of the loop
        }
        
        int stringLength = strlen(input); // string length minus the 'new line' or '\n'
        int i;  // index for the loops
        
        // Instead of '\n', use '\0' to determine that it's the end element.
        for(i = 0; i < stringLength; i++)
            if(input[i] == '\n')
                input[i] = '\0';
        
        printf("%s \n", input);    // print out the string entered by the user
        
        for(i = 0; i < stringLength - 1; i++) {
            // PUSH stack, if the character is an OPEN symbol.
            if(checkIfOpenSymbol(input[i]))
                pushStack(&charList, input[i]);
            
            if(checkIfCloseSymbol(input[i])) {
                // If the CLOSE & CORRESPONDING symbol is at the top of the stack,
                //   POP the stack.
                if(accessTop(&charList) == getCorrespondingOpenSymbol(input[i])) {
                    popStack(&charList);
                    continue;
                }//end if(..
                
                // If the CLOSE & CORRESPONDING symbol is not at the top of the stack,
                //   check for missed or expected symbol.
                else {
                    if(checkifStackIsEmpty(&charList) != TRUE) {
                        expectedSymbolChecker(&charList, i);        // check for expecting symbol
                        isSymbolBalanced = FALSE;
                        break;
                    }//end if(...
                    else {
                        missedSymbolChecker(&charList, input[i], i); // check for missing symbol
                        isSymbolBalanced = FALSE;
                        break;
                    }//end else {...
                }//end else {...
            }//end if(checkIfClose...
        }//end for(...
        
        // If the symbols are balanced & the stack is empty, then the expression is balanced.
        if(isSymbolBalanced == TRUE && checkifStackIsEmpty(&charList) == TRUE) {
            printf("Expression is balanced. \n\n");
            continue;
        }//end if(...
        
        // If the symbols are balanced (in between) & the stack is not empty, then
        //  the program will look out for the missing & remaining "top" element.
        if(isSymbolBalanced == TRUE && checkifStackIsEmpty(&charList) == FALSE)
            missedTopSymbol(&charList, i);
        
        // Reset the stack.
        resetStack(&charList);
    }//end while(...
    
    return 0;
}//end main()
