#include "mock/logger.h"
#include "mock/user_input.h"

/******************************************************************************
 * TEST VARIABLES
 ******************************************************************************/
int maximum_val = 0;
int array_size = 0;
int minimum_val = 1;
int temp_var=0;
/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/
void getarray();
int removeduplicate(int arr[],int size);
/******************************************************************************
 * FUNCTIONS IMPLEMENTATION
 ******************************************************************************/
int removeduplicate(int arr[], int size){
    int j=0;
    for(int i=1;i<size;i++){
        if(arr[j]!=arr[i]){
            j++;
            arr[j]=arr[i];
        }
    }
    return(j+1);
}
void getarray() {
    array_size=get_user_input_int("Enter the number of elements in the array");
    int array_element[array_size];
    for(int i=0;i<array_size;i++){
        array_element[i]=get_user_input_int("Enter the value for consecutive Elements:");
    }
    log_info_string("Displaying the duplicate filtered numbers");
    // for(int i=0;i<array_size;i++){
    //     log_info_int(array_element[i]);
    // }
    int filtered_Array_size=removeduplicate(array_element,array_size);
    for(int i=0;i<filtered_Array_size;i++){
        log_info_int(array_element[i]);
    }
}

/******************************************************************************
 * MAIN TEST FUNCTION
 ******************************************************************************/
int main() {
    printf("=================================\n");
    printf("   Logic Testing Environment\n");
    printf("=================================\n\n");
    
    // Interactive test
    printf("\n--- Interactive Test ---\n");
    getarray();
    
    return 0;
}