# Raspberry Pi Pico - Modular UART Communication Framework

A modular, scalable framework for developing applications on Raspberry Pi Pico with UART communication interface.

## 📁 Project Structure

```
project/
├── CMakeLists.txt
├── inc/                          # BASE LIBRARY (Don't modify)
│   ├── uart_comm.h              # UART communication header
│   ├── logger.h                 # Logging functions header
│   └── user_input.h             # User input functions header
├── src/                          # BASE LIBRARY (Don't modify)
│   ├── main.c                   # Main program entry point
│   ├── uart_comm.c              # UART initialization & command routing
│   ├── logger.c                 # Logging functions implementation
│   └── user_input.c             # User input functions implementation
└── user_implementations/         # YOUR WORK AREA
    ├── my_functions.c           # Main command handler
    ├── sorting_algorithms.c     # DSA: Sorting algorithms
    ├── searching_algorithms.c   # DSA: Searching algorithms
    ├── data_structures.c        # DSA: Stack, Queue, Linked List, etc.
    ├── graph_algorithms.c       # DSA: Graph algorithms (DFS, BFS, etc.)
    ├── sensors.c                # Sensor reading and control
    ├── motor_control.c          # Motor control functions
    └── utilities.c              # Helper/utility functions
```

## 🚀 Features

- ✅ **Modular Architecture** - Clean separation between base code and user implementations
- ✅ **UART Communication** - Full-duplex serial communication at 115200 baud
- ✅ **Command-Based Interface** - Easy command routing and handling
- ✅ **Input Helpers** - Built-in functions for int, float, and string input
- ✅ **Logging System** - Structured logging (INFO, ERROR, DEBUG, WARNING)
- ✅ **Extensible** - Add unlimited user implementation files
- ✅ **Real-time Capable** - Background tasks support
- ✅ **DSA Learning Platform** - Perfect for implementing and testing algorithms
- ✅ **IoT Ready** - Sensor integration and real-time data reading

## 📊 System Architecture

### Overall Control Flow

```mermaid
graph TD
    Start([System Power On]) --> Init1[main.c: main function]
    Init1 --> Init2[uart_comm.c: uart_communication_init]
    Init2 --> Init3{USER_INIT_ENABLED?}
    Init3 -->|Yes| Init4[my_functions.c: user_init]
    Init3 -->|No| MainLoop
    Init4 --> MainLoop[Main Loop Starts]
    
    MainLoop --> Check1{UART Data Available?}
    Check1 -->|No| Check2{Background Tasks Enabled?}
    Check1 -->|Yes| Read[Read Character from UART]
    
    Read --> CheckEnter{Character is Enter?}
    CheckEnter -->|No| Buffer[Add to Buffer]
    Buffer --> Check2
    CheckEnter -->|Yes| Process[process_command buffer]
    
    Process --> SysCheck{System Command?}
    SysCheck -->|help| ShowHelp[Show Help + User Help]
    SysCheck -->|status| ShowStatus[Show System Status]
    SysCheck -->|reset| Reset[Reboot System]
    SysCheck -->|clear| Clear[Clear Console]
    SysCheck -->|Other| UserCmd[handle_user_commands]
    
    ShowHelp --> ClearBuf[Clear Buffer]
    ShowStatus --> ClearBuf
    Reset --> ClearBuf
    Clear --> ClearBuf
    
    UserCmd --> Route{Route Command}
    Route -->|DSA| DSA[DSA Command Handlers]
    Route -->|Sensor| Sensor[Sensor Command Handlers]
    Route -->|Motor| Motor[Motor Command Handlers]
    Route -->|Other| Other[Other Handlers]
    Route -->|Unknown| Error[log_error Unknown command]
    
    DSA --> Execute[Execute Function]
    Sensor --> Execute
    Motor --> Execute
    Other --> Execute
    Error --> ClearBuf
    
    Execute --> Helper{Need Input?}
    Helper -->|Yes| GetInput[user_input.c: get_user_input_*]
    Helper -->|No| Output
    GetInput --> Output[logger.c: log_* Print Results]
    
    Output --> ClearBuf
    ClearBuf --> Check2
    
    Check2 -->|Yes| BgTask[user_background_tasks]
    Check2 -->|No| Sleep
    BgTask --> Sleep[sleep_ms 10]
    Sleep --> MainLoop
    
    style Start fill:#90EE90
    style MainLoop fill:#87CEEB
    style Process fill:#FFD700
    style Execute fill:#FFA07A
    style Output fill:#98FB98
```

### Detailed Command Execution Flow

```mermaid
graph TD
    Cmd([User Types: bubblesort]) --> Buffer[Buffer receives characters]
    Buffer --> Enter[User presses Enter]
    Enter --> NullTerm[Null-terminate buffer]
    NullTerm --> ProcessCmd[uart_comm.c: process_command]
    
    ProcessCmd --> Print[Print: Received: bubblesort]
    Print --> CheckSys{System Command?}
    CheckSys -->|No| CallUser[Call handle_user_commands]
    
    CallUser --> MyFunc[my_functions.c: handle_user_commands]
    MyFunc --> StrCmp{strcmp bubblesort?}
    StrCmp -->|Match| CallSort[Call handle_dsa_commands]
    
    CallSort --> SortFile[sorting_algorithms.c: command_bubble_sort]
    SortFile --> GetSize[get_user_input_int: Enter array size]
    GetSize --> WaitSize[Wait for user input]
    WaitSize --> StoreSize[Store size = 5]
    
    StoreSize --> LoopStart{Loop for elements}
    LoopStart -->|i < size| GetElem[get_user_input_int: Element i]
    GetElem --> WaitElem[Wait for user input]
    WaitElem --> StoreElem[Store in array i]
    StoreElem --> IncI[i++]
    IncI --> LoopStart
    
    LoopStart -->|i >= size| LogBefore[log_info_string: Before sorting]
    LogBefore --> PrintBefore[Print array: 64 34 25 12 22]
    PrintBefore --> BubbleSort[Execute bubble_sort algorithm]
    
    BubbleSort --> LogAfter[log_info_string: After sorting]
    LogAfter --> PrintAfter[Print array: 12 22 25 34 64]
    PrintAfter --> Return[Return to main loop]
    Return --> Ready([Ready for next command])
    
    style Cmd fill:#FFE4B5
    style BubbleSort fill:#FF6347
    style Ready fill:#90EE90
```

### File Interaction Diagram

```mermaid
graph LR
    Main[src/main.c] -->|Calls| UartInit[src/uart_comm.c]
    Main -->|Calls| UserInit[user_implementations/my_functions.c]
    Main -->|Loops| UartRead[UART Read Loop]
    
    UartRead -->|Complete Command| ProcessCmd[uart_comm.c: process_command]
    ProcessCmd -->|System Cmd| Logger[src/logger.c]
    ProcessCmd -->|User Cmd| UserHandler[my_functions.c: handle_user_commands]
    
    UserHandler -->|DSA| Sorting[sorting_algorithms.c]
    UserHandler -->|DSA| Searching[searching_algorithms.c]
    UserHandler -->|DSA| DataStruct[data_structures.c]
    UserHandler -->|Sensor| Sensors[sensors.c]
    UserHandler -->|Motor| Motors[motor_control.c]
    
    Sorting -->|Input| UserInput[src/user_input.c]
    Searching -->|Input| UserInput
    DataStruct -->|Input| UserInput
    Sensors -->|Input| UserInput
    Motors -->|Input| UserInput
    
    Sorting -->|Output| Logger
    Searching -->|Output| Logger
    DataStruct -->|Output| Logger
    Sensors -->|Output| Logger
    Motors -->|Output| Logger
    
    UserInput -->|UART| UartComm[UART Hardware]
    Logger -->|UART| UartComm
    
    style Main fill:#4682B4,color:#fff
    style UserHandler fill:#32CD32,color:#fff
    style Logger fill:#FF69B4,color:#fff
    style UserInput fill:#FFD700
```

### Initialization Sequence

```mermaid
sequenceDiagram
    participant Power as System Power On
    participant Main as src/main.c
    participant UART as src/uart_comm.c
    participant User as user_implementations/my_functions.c
    participant Terminal as Serial Terminal
    
    Power->>Main: Program starts
    Main->>UART: uart_communication_init()
    UART->>UART: stdio_init_all()
    UART->>UART: uart_init(115200)
    UART->>UART: Configure GPIO pins
    UART->>UART: Enable FIFO
    UART->>Terminal: Wait 10 seconds
    UART->>Terminal: Print "UART Initialized"
    UART-->>Main: Initialization complete
    
    Main->>User: user_init() [if enabled]
    User->>User: Initialize sensors
    User->>User: Setup GPIO
    User->>User: Initialize data structures
    User->>Terminal: Print "User init complete"
    User-->>Main: Ready
    
    Main->>Main: Enter main loop
    Main->>Terminal: Ready for commands
```

### Command Processing Sequence

```mermaid
sequenceDiagram
    participant Terminal as User Terminal
    participant Main as src/main.c
    participant UART as src/uart_comm.c
    participant MyFunc as my_functions.c
    participant Sort as sorting_algorithms.c
    participant Input as user_input.c
    participant Logger as logger.c
    
    Terminal->>Main: Type "bubblesort" + Enter
    Main->>Main: Build buffer
    Main->>UART: process_command("bubblesort")
    UART->>Logger: Print "Received: bubblesort"
    UART->>MyFunc: handle_user_commands("bubblesort")
    MyFunc->>Sort: command_bubble_sort()
    
    Sort->>Input: get_user_input_int("Enter size:")
    Input->>Terminal: Display prompt
    Terminal->>Input: Type "5" + Enter
    Input-->>Sort: Returns 5
    
    Sort->>Input: get_user_input_int("Element [0]:")
    Input->>Terminal: Display prompt
    Terminal->>Input: Type "64" + Enter
    Input-->>Sort: Returns 64
    
    Note over Sort,Input: Repeat for all 5 elements
    
    Sort->>Logger: log_info_string("Before sorting")
    Logger->>Terminal: Print array
    Sort->>Sort: Execute bubble_sort()
    Sort->>Logger: log_info_string("After sorting")
    Logger->>Terminal: Print sorted array
    
    Sort-->>MyFunc: Done
    MyFunc-->>UART: Done
    UART-->>Main: Done
    Main->>Main: Continue loop
```

## 🔧 Getting Started

### Prerequisites

- Raspberry Pi Pico or Pico W
- Pico SDK installed
- CMake 3.13 or higher
- Serial terminal (PuTTY, minicom, screen, etc.)

### Building the Project

```bash
# Set Pico SDK path (if not already set)
export PICO_SDK_PATH=/path/to/pico-sdk

# Create build directory
mkdir build
cd build

# Configure CMake
cmake ..

# Build
make

# Flash to Pico (copy .uf2 file to Pico in BOOTSEL mode)
cp Pico_05_Generalized_Code.uf2 /media/RPI-RP2/
```

### Connecting to Serial Terminal

```bash
# Linux/Mac
screen /dev/ttyACM0 115200

# Or using minicom
minicom -D /dev/ttyACM0 -b 115200

# Windows - Use PuTTY with COM port and 115200 baud rate
```

## 📝 How to Add Your Own Commands

### Step 1: Create Your Function

In `user_implementations/my_functions.c` (or create a new file):

```c
void my_custom_function(void) {
    int num = get_user_input_int("Enter a number: ");
    log_info_int(num * 2);
}
```

### Step 2: Add Command Handler

In `handle_user_commands()`:

```c
void handle_user_commands(char *cmd) {
    // ... existing code ...
    
    else if (strcmp(cmd, "mycmd") == 0) {
        my_custom_function();
    }
}
```

### Step 3: Add Help Text

```c
if (strcmp(cmd, "help") == 0) {
    printf("  mycmd - My custom command\n");
    return;
}
```

### Step 4: Rebuild and Test

```bash
cd build
make
# Flash to Pico
# Type "mycmd" in terminal
```

## 🎯 Example Use Cases

### 1. DSA Learning Platform

Implement and test algorithms:
- Sorting: Bubble, Quick, Merge, Insertion, Selection
- Searching: Binary, Linear, Jump
- Data Structures: Stack, Queue, Linked List, Tree, Graph
- Dynamic Programming: Fibonacci, Knapsack, LCS

### 2. IoT Sensor Hub

Read and log sensor data:
- Temperature sensors (DHT11, DHT22, DS18B20)
- Distance sensors (HC-SR04)
- Motion sensors (PIR)
- Light sensors (LDR, BH1750)

### 3. Robotics Control

Control robots via UART:
- Motor control (direction, speed)
- Servo positioning
- Sensor-based navigation
- Autonomous behaviors

### 4. Data Logger

Log data to serial or storage:
- Real-time sensor readings
- Environmental monitoring
- Performance benchmarking
- Debug logging

## 📚 Available Base Functions

### User Input Functions
```c
int get_user_input_int(char *prompt);
float get_user_input_float(char *prompt);
void get_user_input_string(char *prompt, char *output_buffer, int max_length);
```

### Logging Functions
```c
void log_error(char *prompt);
void log_system_status(char *prompt);
void log_debug(char *prompt);
void log_warning(char *prompt);
void log_info_int(int value);
void log_info_string(char *str);
void log_info_float(float value);
void clear_console(void);
```

## 🔌 System Commands

| Command | Description |
|---------|-------------|
| `help` | Show all available commands |
| `status` | Display system status |
| `reset` | Reboot the system |
| `clear` or `cls` | Clear the console |

## 🤝 Contributing

1. Create your implementation in `user_implementations/`
2. Add files to `CMakeLists.txt`
3. Update this README with your commands
4. Test thoroughly
5. Submit PR (if sharing)

## 📄 License

This project is open source and available under the MIT License.

## 🙏 Acknowledgments

- Raspberry Pi Foundation for Pico SDK
- Community contributors and testers

---

**Happy Coding! 🚀**

For questions or issues, please open an issue on GitHub.