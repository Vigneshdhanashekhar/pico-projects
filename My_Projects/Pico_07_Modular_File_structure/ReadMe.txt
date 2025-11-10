# Raspberry Pi Pico UART Command Framework Documentation

## Table of Contents
1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Getting Started](#getting-started)
4. [Workflow Explanation](#workflow-explanation)
5. [File Responsibilities](#file-responsibilities)
6. [Adding New Features](#adding-new-features)
7. [Complete Example: Temperature Sensor](#complete-example-temperature-sensor)
8. [API Reference](#api-reference)
9. [Best Practices](#best-practices)

---

## Overview

This framework provides a modular, reusable architecture for building UART-based command-line interfaces on the Raspberry Pi Pico. The framework separates base functionality from user implementations, making it easy to add custom features without modifying core code.

### Key Features
- **Modular Architecture**: Clear separation between base code and user code
- **Easy Command Handling**: Simple pattern for adding new commands
- **Built-in Input Functions**: Ready-to-use functions for getting user input (int, float, string)
- **Logging System**: Consistent logging with different severity levels
- **Extensible**: Easy to add new features and commands

---

## Project Structure

```
project/
├── CMakeLists.txt                    # Build configuration
├── inc/                              # Header files (DO NOT MODIFY)
│   ├── uart_comm.h                   # UART communication definitions
│   ├── user_input.h                  # Input function declarations
│   └── logger.h                      # Logging function declarations
├── src/                              # Source files (DO NOT MODIFY)
│   ├── main.c                        # Main program loop
│   ├── uart_comm.c                   # UART and command processing
│   ├── logger.c                      # Logging implementations
│   └── user_input.c                  # Input function implementations
└── user_implementations/             # YOUR CODE GOES HERE ✅
    └── my_functions.c                # User implementation file
```

---

## Getting Started

### Prerequisites
- Raspberry Pi Pico SDK installed
- CMake build system
- UART terminal (PuTTY, Tera Term, or similar)

### Building the Project
```bash
mkdir build
cd build
cmake ..
make
```

### Uploading to Pico
1. Hold BOOTSEL button on Pico
2. Connect USB cable
3. Copy `Pico_05_Generalized_Code.uf2` to RPI-RP2 drive
4. Open UART terminal at 115200 baud

---

## Workflow Explanation

### Command Flow Diagram

```
┌─────────────────────────────────────────────────────────┐
│  1. User types "temperature" in terminal                │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  2. main.c receives input via UART                      │
│     - Collects characters into buffer                   │
│     - When Enter pressed, calls process_command()       │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  3. uart_comm.c → process_command()                     │
│     - Checks if it's a system command (help, reset...)  │
│     - Not a system command, so calls:                   │
│       handle_user_commands("temperature")               │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  4. my_functions.c → handle_user_commands()             │
│     - Compares cmd with "temperature"                   │
│     - Match found! Calls command_temperature()          │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  5. my_functions.c → command_temperature()              │
│     - Calls read_temperature()                          │
│     - Reads ADC, converts to temperature                │
│     - Prints result to terminal                         │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  6. Terminal displays temperature                       │
│     Temperature: 25.34 °C                               │
└─────────────────────────────────────────────────────────┘
```

---

## File Responsibilities

| File | Purpose | Editable? |
|------|---------|-----------|
| `src/main.c` | Main loop, UART input collection | ❌ NO |
| `src/uart_comm.c` | System commands (help, reset, clear) | ❌ NO |
| `src/logger.c` | Logging functions (log_info, log_error) | ❌ NO |
| `src/user_input.c` | User input collection (int, float, string) | ❌ NO |
| `inc/*.h` | Header files for all modules | ❌ NO |
| **`user_implementations/my_functions.c`** | **YOUR CUSTOM CODE** | ✅ **YES!** |

### Key Point
**All your code goes in one file:** `user_implementations/my_functions.c`

This file contains:
- Your variables
- Your function implementations
- Your command handlers
- User initialization (optional)
- Background tasks (optional)

---

## Adding New Features

### Three Simple Steps

#### Step 1: Write Your Function
```c
void command_myfeature(void) {
    log_info_string("Executing my feature...");
    
    // Your code here
    int value = get_user_input_int("Enter a value: ");
    printf("You entered: %d\n", value);
}
```

#### Step 2: Add to Command Handler
```c
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Add to help text
        printf("  myfeature - Description of my feature\n");
        return;
    }
    
    // Add your command
    if (strcmp(cmd, "myfeature") == 0) {
        command_myfeature();
    }
    // ... other commands ...
    else {
        log_error("Unknown command");
    }
}
```

#### Step 3: Test
```
Received: myfeature
[INFO] Executing my feature...
[INFO] Enter a value: 
```

---

## Complete Example: Temperature Sensor

### Implementation in `my_functions.c`

```c
#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include "hardware/adc.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
float current_temperature = 0.0;

/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void init_temperature_sensor(void);
float read_temperature(void);
void command_temperature(void);

/******************************************************************************
 * TEMPERATURE SENSOR FUNCTIONS
 ******************************************************************************/

// Initialize the temperature sensor (Pico's internal sensor)
void init_temperature_sensor(void) {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);  // Select ADC input 4 (temp sensor)
    log_system_status("Temperature sensor initialized");
}

// Read temperature from sensor
float read_temperature(void) {
    // Read raw ADC value
    uint16_t raw = adc_read();
    
    // Convert to voltage (12-bit ADC: 0-4095 → 0-3.3V)
    const float conversion_factor = 3.3f / (1 << 12);
    float voltage = raw * conversion_factor;
    
    // Convert voltage to temperature (Pico datasheet formula)
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
    
    return temperature;
}

// Command handler for temperature
void command_temperature(void) {
    log_info_string("Reading temperature sensor...\n");
    
    current_temperature = read_temperature();
    
    printf("========================================\n");
    printf("  Temperature Reading\n");
    printf("========================================\n");
    printf("  Temperature: %.2f °C\n", current_temperature);
    printf("  Temperature: %.2f °F\n", 
           (current_temperature * 9.0f / 5.0f) + 32.0f);
    printf("========================================\n");
}

/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        printf("  temperature - Read temperature sensor\n");
        printf("  temp        - Read temperature sensor (short)\n");
        return;
    }
    
    if (strcmp(cmd, "temperature") == 0 || strcmp(cmd, "temp") == 0) {
        command_temperature();
    }
    else {
        log_error("Unknown command");
        log_system_status("Type 'help' for available commands\n");
    }
}

/******************************************************************************
 * USER INITIALIZATION
 ******************************************************************************/
#define USER_INIT_ENABLED

void user_init(void) {
    // Initialize temperature sensor at startup
    init_temperature_sensor();
    log_system_status("User initialization complete");
}

/******************************************************************************
 * USER BACKGROUND TASKS (OPTIONAL)
 ******************************************************************************/
// Uncomment to enable continuous monitoring
// #define USER_BACKGROUND_TASKS_ENABLED

void user_background_tasks(void) {
    // Example: Read temperature every 5 seconds
    static uint32_t last_temp_read = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());
    
    if (now - last_temp_read > 5000) {
        current_temperature = read_temperature();
        last_temp_read = now;
    }
}
```

### Terminal Output

```
========================================
  UART Communication Initialized
  Baud Rate: 115200
========================================
Ready to receive commands...

[SYSTEM] command: 'Temperature sensor initialized'
[SYSTEM] command: 'User initialization complete'

Received: help
Available commands:
  help   - Show this help message
  status - Show system status
  reset  - Reset the system
  clear  - Clear console
  cls    - Clear console

User commands:
  temperature - Read temperature sensor
  temp        - Read temperature sensor (short)

Received: temperature
[INFO] Reading temperature sensor...

========================================
  Temperature Reading
========================================
  Temperature: 25.34 °C
  Temperature: 77.61 °F
========================================

Received: temp
[INFO] Reading temperature sensor...

========================================
  Temperature Reading
========================================
  Temperature: 25.42 °C
  Temperature: 77.76 °F
========================================
```

---

## API Reference

### Logging Functions

#### `log_info_string(char *str)`
Display informational message
```c
log_info_string("Processing data...");
// Output: [INFO] Processing data...
```

#### `log_info_int(int value)`
Display integer value
```c
log_info_int(42);
// Output: [INFO] 42
```

#### `log_info_float(float value)`
Display float value with 2 decimal places
```c
log_info_float(3.14159);
// Output: [INFO] 3.14
```

#### `log_error(char *message)`
Display error message
```c
log_error("Invalid input");
// Output: [ERROR] command: 'Invalid input'
```

#### `log_warning(char *message)`
Display warning message
```c
log_warning("Buffer nearly full");
// Output: [WARNING] command: 'Buffer nearly full'
```

#### `log_system_status(char *message)`
Display system status
```c
log_system_status("Initialization complete");
// Output: [SYSTEM] command: 'Initialization complete'
```

#### `log_debug(char *message)`
Display debug message
```c
log_debug("Variable value: 123");
// Output: [DEBUG] command: 'Variable value: 123'
```

#### `clear_console(void)`
Clear terminal screen
```c
clear_console();
```

---

### User Input Functions

#### `int get_user_input_int(char *prompt)`
Get integer input from user (blocking)
```c
int age = get_user_input_int("Enter your age: ");
printf("You entered: %d\n", age);
```

**Example:**
```
[INFO] Enter your age: 
25
You entered: 25
```

#### `float get_user_input_float(char *prompt)`
Get float input from user (blocking)
```c
float temperature = get_user_input_float("Enter temperature: ");
printf("Temperature: %.2f\n", temperature);
```

**Example:**
```
[INFO] Enter temperature: 
25.5
Temperature: 25.50
```

#### `void get_user_input_string(char *prompt, char *output_buffer, int max_length)`
Get string input from user (blocking)
```c
char name[50];
get_user_input_string("Enter your name: ", name, sizeof(name));
printf("Hello, %s!\n", name);
```

**Example:**
```
[INFO] Enter your name: 
John
Hello, John!
```

---

### Built-in System Commands

| Command | Description |
|---------|-------------|
| `help` | Display all available commands |
| `status` | Show system status |
| `reset` | Reset the Pico |
| `clear` or `cls` | Clear terminal screen |

---

## Best Practices

### 1. Function Naming Convention
Use descriptive names with prefixes:
```c
// Command handlers
void command_temperature(void);
void command_led_control(void);

// Helper functions
void init_temperature_sensor(void);
float read_sensor_data(void);
```

### 2. Error Handling
Always validate user input and provide feedback:
```c
float value = get_user_input_float("Enter voltage (0-3.3V): ");
if (value < 0.0f || value > 3.3f) {
    log_error("Voltage out of range!");
    return;
}
```

### 3. Use Initialization Function
Initialize hardware in `user_init()`:
```c
#define USER_INIT_ENABLED

void user_init(void) {
    // Initialize all your hardware here
    init_temperature_sensor();
    init_leds();
    init_i2c();
    
    log_system_status("All hardware initialized");
}
```

### 4. Background Tasks
Use background tasks for periodic operations:
```c
#define USER_BACKGROUND_TASKS_ENABLED

void user_background_tasks(void) {
    static uint32_t last_blink = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());
    
    // Blink LED every second
    if (now - last_blink > 1000) {
        toggle_led();
        last_blink = now;
    }
}
```

### 5. Help Text
Always update help text when adding commands:
```c
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        printf("  temperature - Read temperature sensor\n");
        printf("  led         - Control LED (on/off/toggle)\n");
        printf("  sensor      - Read all sensor values\n");
        return;
    }
    // ... rest of commands
}
```

### 6. Consistent Output Format
Use consistent formatting for better readability:
```c
printf("========================================\n");
printf("  Sensor Readings\n");
printf("========================================\n");
printf("  Temperature: %.2f °C\n", temp);
printf("  Humidity:    %.2f %%\n", humidity);
printf("  Pressure:    %.2f hPa\n", pressure);
printf("========================================\n");
```

---

## Common Patterns

### Pattern 1: Simple Command
```c
void command_hello(void) {
    printf("Hello, World!\n");
}

// In handle_user_commands():
if (strcmp(cmd, "hello") == 0) {
    command_hello();
}
```

### Pattern 2: Command with Input
```c
void command_multiply(void) {
    int a = get_user_input_int("Enter first number: ");
    int b = get_user_input_int("Enter second number: ");
    printf("Result: %d × %d = %d\n", a, b, a * b);
}

// In handle_user_commands():
if (strcmp(cmd, "multiply") == 0) {
    command_multiply();
}
```

### Pattern 3: Command with Multiple Aliases
```c
// Support multiple command names
if (strcmp(cmd, "temperature") == 0 || 
    strcmp(cmd, "temp") == 0 || 
    strcmp(cmd, "t") == 0) {
    command_temperature();
}
```

### Pattern 4: Command with Sub-commands
```c
void command_led(void) {
    char action[20];
    get_user_input_string("Enter action (on/off/toggle): ", 
                          action, sizeof(action));
    
    if (strcmp(action, "on") == 0) {
        set_led(true);
        printf("LED turned ON\n");
    }
    else if (strcmp(action, "off") == 0) {
        set_led(false);
        printf("LED turned OFF\n");
    }
    else if (strcmp(action, "toggle") == 0) {
        toggle_led();
        printf("LED toggled\n");
    }
    else {
        log_error("Invalid action");
    }
}
```

---

## Troubleshooting

### Issue: Commands not recognized
**Solution:** Check that you added the command to `handle_user_commands()` and updated the help text.

### Issue: Input functions hanging
**Solution:** Ensure UART is properly initialized and terminal is sending carriage return (`\r`) or newline (`\n`) characters.

### Issue: Compile errors about undefined functions
**Solution:** Make sure all function prototypes are declared before use.

### Issue: Values not persisting
**Solution:** Declare variables as global (outside functions) or static (inside functions).

---

## Advanced Topics

### Adding Multiple User Files

To organize code across multiple files:

1. **Create new file:** `user_implementations/sensors.c`

2. **Update CMakeLists.txt:**
```cmake
add_executable(Pico_05_Generalized_Code
    src/main.c
    src/uart_comm.c
    src/logger.c
    src/user_input.c
    user_implementations/my_functions.c
    user_implementations/sensors.c        # Add new file
)
```

3. **Share functions** via extern declarations or header files

---

## Summary

### Where to Write Code
✅ **ONLY in:** `user_implementations/my_functions.c`

### Three Steps to Add Feature
1. Write function: `void command_myfeature(void)`
2. Add to handler: `if (strcmp(cmd, "myfeature") == 0)`
3. Update help text

### Key Files to Remember
- 📝 **Edit:** `user_implementations/my_functions.c`
- 📖 **Use:** Functions from `logger.h` and `user_input.h`
- 🚫 **Don't Touch:** Everything in `src/` and `inc/`

---

## Quick Start Checklist

- [ ] Clone/download the framework
- [ ] Open `user_implementations/my_functions.c`
- [ ] Write your command function
- [ ] Add command to `handle_user_commands()`
- [ ] Update help text
- [ ] Build with CMake
- [ ] Upload to Pico
- [ ] Test in terminal

---

**Happy Coding! 🚀**

For questions or issues, refer to the Raspberry Pi Pico SDK documentation.
