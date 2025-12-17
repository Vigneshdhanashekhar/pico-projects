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
void maxminarray();

/******************************************************************************
 * FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

void maxminarray() {
    array_size=get_user_input_int("Enter the number of elements in the array");
    if(0>array_size){
        log_error("Array  Size cannot be less than Zero");
        return;
    }
    temp_var=get_user_input_int("Enter the value for 1st Element:");
    maximum_val=temp_var;
    minimum_val=temp_var;
    for(int i=1;i<array_size;i++){
        temp_var=get_user_input_int("Enter the value for consecutive Elements:");
        if (maximum_val<temp_var){
            maximum_val=temp_var;
        }
        if (minimum_val>temp_var){
            minimum_val=temp_var;
        }
    }
    log_info_string("Maximum Value in the array is ");
    log_info_int(maximum_val);
    log_info_string("Minimum Value in the array is ");
    log_info_int(minimum_val);

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
    maxminarray();
    
    return 0;
}