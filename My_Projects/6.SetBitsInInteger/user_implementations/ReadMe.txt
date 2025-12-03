Code for Setbit count in integer.

# Set Bits Counter

## Overview
This function counts the number of set bits (1's) in the binary representation of an integer.

## Function Signature
```c
void setbitsint()
```

## Algorithm Explanation

### What are Set Bits?
Set bits are the positions in a binary number that contain the value `1`.

**Example:**
- Decimal: `5`
- Binary: `101`
- Set bits: **2** (two 1's)

### Step-by-Step Logic

1. **Get Input**
   ```c
   num_to_find_setbits = get_user_input_int("Enter the Integer: ");
   ```
   - Prompt user for an integer

2. **Initialize Variables**
   ```c
   temp = num_to_find_setbits;
   count = 0;  // CRITICAL: Reset counter
   ```
   - Copy input to temp variable (to preserve original)
   - Reset count to 0

3. **Extract and Count Bits**
   ```c
   while(temp > 0){
       int bit_val = temp % 2;  // Get rightmost bit
       if (bit_val == 1){
           count++;              // Increment if bit is 1
       }
       temp = temp / 2;          // Shift right (divide by 2)
   }
   ```

### How It Works (Example: Input = 5)

| Iteration | temp | Binary | temp % 2 | bit_val | count | temp / 2 |
|-----------|------|--------|----------|---------|-------|----------|
| Start     | 5    | 101    | -        | -       | 0     | -        |
| 1         | 5    | 101    | 1        | 1       | 1     | 2        |
| 2         | 2    | 10     | 0        | 0       | 1     | 1        |
| 3         | 1    | 1      | 1        | 1       | 2     | 0        |
| End       | 0    | -      | -        | -       | 2     | -        |

**Result: 2 set bits**

### Key Operations

- **`temp % 2`**: Extracts the rightmost bit
  - Returns `1` if bit is set
  - Returns `0` if bit is not set

- **`temp / 2`**: Removes the rightmost bit (right shift)
  - `5 / 2 = 2` (binary: `101` → `10`)
  - `2 / 2 = 1` (binary: `10` → `1`)
  - `1 / 2 = 0` (binary: `1` → `0`)

## Common Examples

| Decimal | Binary  | Set Bits |
|---------|---------|----------|
| 0       | 0       | 0        |
| 1       | 1       | 1        |
| 5       | 101     | 2        |
| 7       | 111     | 3        |
| 15      | 1111    | 4        |
| 255     | 11111111| 8        |

## Important Notes

### ⚠️ Critical Bug Fix
Always initialize `count = 0` before the loop. If `count` is a global/static variable, it will retain values from previous calls:

```c
// WRONG - count not reset
count = ???;  // Could be 5 from previous call
// Input: 5 → Output: 7 (INCORRECT)

// CORRECT - count reset
count = 0;
// Input: 5 → Output: 2 (CORRECT)
```

### Alternative Bit Manipulation Method
For better performance, you can use Brian Kernighan's algorithm:

```c
while(temp > 0){
    temp = temp & (temp - 1);  // Removes rightmost set bit
    count++;
}
```

This is faster because it only iterates once per set bit, not once per total bit.

## Complexity
- **Time Complexity**: O(log n) - where n is the input number
- **Space Complexity**: O(1) - constant space

## Output
```
Enter the Integer: 5
The number of setbits is: 2
```