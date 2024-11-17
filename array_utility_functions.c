//Importing Libraries
#include<stdio.h> 
#include <stdbool.h> 

//Defining Constants
#define SIZE 24
#define nRows 8
#define nCols 3

// Given Prototypes
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);

//User-Defined Function Prototypes
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int arr2d[nRows][nCols]);
void trans_matrix(const int mat[nRows][nCols], int mat_transp[nCols][nRows]);
bool found_duplicate(int arr[], int length);

//Main Function
int main(){
   int arr[SIZE];
   int arr2d[nRows][nCols];
   int user_choice;
   int position;

   print_array(arr, SIZE);

while (true)
{
   //Printing Main Menu
      printf("\n\nMain Menu\n");
      printf("1. Remove Element\n");
      printf("2. Insert Element\n");
      printf("3. Reshape Matrix\n");
      printf("4. Transpose\n");
      printf("5. Check for Duplicates\n");
      printf("0. Exit\n");
      printf("Please choose your preference: ");
      scanf("%d",&user_choice);

      if (user_choice==1){
         printf("Removing Element \n");
         printf("Enter the position at which the element should be removed: ");
         scanf("%d",&position);
         if(isValid(arr, SIZE, position)){
            printf("Position is in the range\n");
            remove_element(arr,SIZE,position);
            printf("The updated array is: ");
            for (int j=0; j<SIZE;j++){
               printf("%d ",arr[j]);
            }
         }
         else{
            printf("Position Out of Bound for the Array");
         }
      }

      else if (user_choice==2){
         int new_elem;
         printf("Inserting Element\n");
         printf("Enter the position of the new element: ");
         scanf("%d",&position);
         printf("Enter the new element to be added: ");
         scanf("%d",&new_elem);
         if(isValid(arr, SIZE, position)){
            printf("Position is in the range\n");
            insert_element(arr, SIZE, position, new_elem);
            for(int j=0; j<SIZE;j++){
               printf("%d ",arr[j]);
            }
         }
         else{
            printf("Wrong Value");
         }
      }

      else if (user_choice==3){
         reshape(arr, SIZE, arr2d);
         for(int x=0; x<nRows; x++){
            for(int y=0;y<nCols;y++){
               printf("%d ",arr2d[x][y]);
            }
            printf("\n");
         }
      }

      else if(user_choice==4){   
         int mat_transpose[nCols][nRows];
         // Calling reshape function to create the 2D array from the 1D array
         reshape(arr, SIZE,arr2d);
         // Calling function to create transpose
         trans_matrix(arr2d, mat_transpose);

         for(int i=0;i<nCols;i++){
            for(int j=0;j<nRows;j++){
               printf("%d ", mat_transpose[i][j]);
            }
         printf("\n");
         }
      }

      else if(user_choice==5){
         bool duplicate = found_duplicate(arr,SIZE);
         printf("Array has duplicate: %s", duplicate ? "true" : "false");
      }

      else if (user_choice==0){
         break;
      }

      else{
         printf("Invalid Input");
      }
}
}


//___________________________________________________________________________

//FUNCTION DEFINITIONS

//Function for Printing the Array
void print_array(int array[], int length){
   printf("Your array is: ");
   for(int i=0;i<length; i++){
      array[i] = i;
      printf("%d ",array[i]);
   }
   printf("\n");
}

//Function for Printing the Matrix
void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}

//Checking for Validity Function
bool isValid(const int arr[], int length, int pos) {
    return (pos >= 0 && pos < length);
}

//Remove Element Function
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid position\n");
    }
    else{
        for (int i = pos; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }
    }
    
}

//Insert Element Function
void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid position\n");
    }
    else{
        for (int i = length - 1; i > pos; i--) {
            arr[i] = arr[i - 1];
        }
        arr[pos] = value;
    }
    
}

//Reshape Function
void reshape(const int arr[], int length, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Invalid dimensions\n");
    }
    else{
        int i=0;
        for (int j = 0; j<nRows; j++) {
            for (int k = 0; k<nCols; k++) {
                arr2d[j][k] = arr[i];
                i++;
            }
        }
    }
}

//Transpose Matrix Function
void trans_matrix(const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

//Found Duplicate Function
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}
