
#ifndef MOCK_LOGGER_H
#define MOCK_LOGGER_H


// Mock implementations that print to stdout
#define log_info_string(msg) printf("%s\n", msg)
#define log_info_int(val) printf("%d\n", val)
#define log_error(msg) printf("ERROR: %s\n", msg)
#define log_system_status(msg) printf("STATUS: %s\n", msg)

#endif // MOCK_LOGGER_H