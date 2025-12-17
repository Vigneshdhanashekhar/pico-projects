Code for GCD of Two Numbers

The Core Insight
Key Principle: GCD(a, b) = GCD(b, a % b)
The GCD of two numbers is the same as the GCD of the smaller number and the remainder when the larger is divided by the smaller.

Algorithm Steps
1. Take two numbers: a and b
2. While b ≠ 0:
   - Find remainder: r = a % b
   - Update: a = b
   - Update: b = r
3. When b = 0, a contains the GCD