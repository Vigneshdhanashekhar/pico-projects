#include "mock/logger.h"
#include "mock/user_input.h"

/******************************************************************************
 * TEST VARIABLES
 ******************************************************************************/
int temp = 0;
int bin_num = 0;
int num_dec2bin = 0;
int pos_value = 1;

/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/
void dec2bin();
void test_dec2bin_with_value(int value);

/******************************************************************************
 * FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

void dec2bin() {
    num_dec2bin = get_user_input_int("Enter the Integer: ");
    log_info_string("You entered:");
    log_info_int(num_dec2bin);
    
    bin_num = 0;
    temp = num_dec2bin;
    pos_value = 1;
    
    while(temp > 0) {
        int bit_val = temp % 2;
        bin_num = (bit_val * pos_value) + bin_num;
        pos_value = 10 * pos_value;
        temp = temp / 2;
    }
    
    log_info_string("The binary equivalent is:");
    log_info_int(bin_num);
}

// Helper function to test with specific values (no user input needed)
void test_dec2bin_with_value(int value) {
    printf("\n=== Testing with value: %d ===\n", value);
    
    num_dec2bin = value;
    bin_num = 0;
    temp = num_dec2bin;
    pos_value = 1;
    
    while(temp > 0) {
        int bit_val = temp % 2;
        bin_num = (bit_val * pos_value) + bin_num;
        pos_value = 10 * pos_value;
        temp = temp / 2;
    }
    
    printf("Decimal: %d -> Binary: %d\n", num_dec2bin, bin_num);
}

/******************************************************************************
 * MAIN TEST FUNCTION
 ******************************************************************************/
int main() {
    printf("=================================\n");
    printf("   Logic Testing Environment\n");
    printf("=================================\n\n");
    
    // Automated tests
    printf("--- Automated Tests ---\n");
    test_dec2bin_with_value(5);
    test_dec2bin_with_value(10);
    test_dec2bin_with_value(15);
    test_dec2bin_with_value(255);
    
    // Interactive test
    printf("\n--- Interactive Test ---\n");
    dec2bin();
    
    return 0;
}