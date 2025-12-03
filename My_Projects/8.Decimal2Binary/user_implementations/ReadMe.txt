Code for GCD of Two Numbers

void dec2bin(){
    num_dec2bin= get_user_input_int("Enter the Integer: ");
    log_info_string("You entered :");
    log_info_int(num_dec2bin);
    bin_num =0;
    temp=num_dec2bin;
    while(temp>0){
        int bit_val=temp%2;
        bin_num=(bit_val*pos_value) +bin_num;
        pos_value=10*pos_value;
        temp=temp/2;
    }
    log_info_string("The binary equivalent is: ");
    log_info_int(bin_num);
    pos_value=1;
}

How It Works (Input = 5)
Iterationtempbit_valpositionbin_num calculationbin_numStart5-1-015110 + (1×1) = 11220101 + (0×10) = 113111001 + (1×100) = 101101
Output: 101 ✓