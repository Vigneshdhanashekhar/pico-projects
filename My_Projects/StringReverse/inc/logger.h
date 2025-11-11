#ifndef LOGGER_H
#define LOGGER_H

/******************************************************************************
 * LOGGING FUNCTIONS
 ******************************************************************************/
void log_error(char *prompt);
void log_system_status(char *prompt);
void log_debug(char *prompt);
void log_warning(char *prompt);
void log_info_int(int value);
void log_info_string(char *str);
void log_info_float(float value);
void clear_console(void);

#endif // LOGGER_H