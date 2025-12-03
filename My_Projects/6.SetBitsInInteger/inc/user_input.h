#ifndef USER_INPUT_H
#define USER_INPUT_H

/******************************************************************************
 * USER INPUT FUNCTIONS
 ******************************************************************************/
int get_user_input_int(char *prompt);
float get_user_input_float(char *prompt);
void get_user_input_string(char *prompt, char *output_buffer, int max_length);

#endif // USER_INPUT_H