
#ifndef MOCK_USER_INPUT_H
#define MOCK_USER_INPUT_H

// Mock function that reads from stdin
static inline int get_user_input_int(const char* prompt) {
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    return value;
}

#endif // MOCK_USER_INPUT_H