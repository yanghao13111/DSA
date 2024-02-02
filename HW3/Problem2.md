# Problem 1 - Greatest Common Divisor of Big Integers

## Problem Description
The greatest common divisor gcd(a,b) between two positive integers a and b is defined as the largest positive integer that divides both a and b without a remainder. Mathematically speaking, for any positive integers a and b, gcd(a, b) satisfies the following properties:
- a ≡ 0 mod gcd(a,b)
- b ≡ 0 mod gcd(a,b)
- ∀k ∈ N and k > gcd(a,b),(a̸≡0 mod k)or(b̸ ≡ 0 mod k)

GCD is a very powerful tool in modern cryptography, and when the target integers to be calculated are small (less than 10^8), GCD can be calculated in a few seconds with a naïve method. However, the numbers in modern cryptography require at least 512 digits to prevent attackers from using a brute-force method to derive the secret key. This required number is too large for the naïve methods to calculate GCD in a reasonable time and the numbers exceed the limit of even long long in the C language. In this problem, we will guide you to calculate the GCD of two big integers efficiently.

### Input Format
One line containing two positive integers, a and b.

### Output Format
Please output a positive integer representing gcd(a, b).

### Constraints
- 0 < a,b < 10^256.

### Subtasks
1. 0 < a, b < 10^6 . Note that you may not need the Binary Algorithm, or at least not the Binary Algorithm on BigInt, to solve this subtask.
2. 0 < b < 10^6
3. no other constraints

### Sample Input 1
20230228 82203202

### Sample Output 1
2

### Sample Input 2
987654321987654321987654321 123456789123456789123456789

### Sample Output 2
9000000009000000009

## Program Analysis

旨在計算兩個超出標準整型範圍的大整數的最大公約數（GCD）。在處理大數字的背景下，包括動態記憶體分配、陣列操作和算法問題解決等幾個關鍵的程式設計概念的應用。以下是對其主要function的分析：

### Main Function
- 初始化字符陣列 `a` 和 `b` 以存儲輸入數字作為字符串。
- 確定哪個數字較小並將兩個字符串轉換為整數陣列以進行處理。
- 調用 `gcd` 函數計算兩個數字的GCD。

### Key Functions
- `checkSize`：比較兩個字符串的大小（長度）以確定哪一個代表較小的數字。
- `toInt`：將數字的字符串表示轉換為整數陣列，每個元素存儲單個數字。
- `calLength`：計算存儲在整數陣列中的數字的實際長度，忽略用於標記未使用位置的任何尾隨 `-1`。
- `swap`：交換兩個整數陣列的內容。
- `divide`：將以整數陣列表示的數字除以 2，用於二進制GCD算法。
- `multiply`：將以整數陣列表示的數字乘以一個整數，用於在重複除以 2 之後調整最終的GCD。
- `subtraction`：從另一個數字中減去一個數字（以整數陣列表示），是二進制GCD算法中的一步。
- `gcd`：實現二進制GCD算法，使用輔助函數進行如除以 2 和減法等操作。

### Algorithmic Approach
- 使用二進制GCD算法，該算法對於大數字比傳統的歐幾里得算法更有效。
- 重複地將兩個數字除以 2（如果它們是偶數），從較大的數字中減去較小的數字，並在必要時交換它們，直到其中一個數字變為 0。然後通過 2^k 的因子（其中 k 是兩個數字都可以被 2 整除的次數）調整GCD。

### Efficiency Considerations
- 通過對整數陣列而不是C中的內建整型進行操作，可以處理遠大於標準C數據類型通常支持的數字。
- 使用動態記憶體分配（`malloc`）創建足夠大的整數陣列來存儲輸入數字的數字，以便在沒有溢出問題的情況下計算它們的GCD。