# Problem - Everyone Loves Sweetmelons

- Time Limit: 1 s
- Memory Limit: 2048 KB

## Problem Description
Recall the magical fairy in the house of Demeter Sphynx Abyssinian (DSA)? The fairy's magic spell is represented by a string S, consisting of uppercase English alphabets with a length of N. Each substring of S, termed a segment of the spell, generates a magic effect if it exactly matches the pattern P, which has a length of M. Conversely, a segment may produce the opposite effect if it is a rotation of P. For example, for a string A(A = c1c2...cn) consisting of n alphabets, ci...cn + c1...ci−1 is considered a rotation of A for any i ∈ [2, n]. 

To assist the fairy in debugging zir magic spell, can you calculate the total number of segments in zir spell that may generate either the original or the opposite magic effect?

### Input

The first line contains two integers N and M. The second line contains the magic spell string S, with a length of N. The third line contains the pattern P, with a length of M.

### Output

Output the total number as an integer in a single line.

### Constraints

- 1 ≤ M ≤ N ≤ 10^6
- S and P consist of only uppercase English letters.

### Subtask 1 (10 pts)

- 1 ≤ N ≤ 10^4
- 1 ≤ M ≤ 10^2

### Subtask 2 (15 pts)

- N = M

### Subtask 3 (15 pts)

- 1 ≤ N × M ≤ 2 × 10^7

### Subtask 4 (60 pts)

- No other constraints.

### Sample Input 1
7 5
DEABCDE
ABCDE


### Sample Output 1
3

### Hints

- Substrings of length M in S are [DEABC, EABCD, ABCDE]. The first two are rotations of P, and the last one equals P.

## Program Analysis

實現尋找特定模式P或其旋轉形式在給定的魔法咒語字符串S中出現的所有可能段落的總數。為了達到這一目的，採用了Rabin-Karp算法的變種來處理字符串匹配的問題，並通過哈希表來加速匹配過程。

### Main Function
- 初始化變量並讀取輸入，包括魔法咒語S和模式P的字符串以及它們的長度N和M。
- 對模式P進行預處理，創建一個包含P及其自身連接形式的字符串，以便後續計算其所有可能的旋轉形式的哈希值。
- 通過四個不同的質數創建四個哈希表，以便於後續進行更加準確的字符串匹配。

### Key Functions
- `build_hash`：為模式P的每個可能的旋轉形式計算哈希值並存儲在哈希表中。

### Algorithmic Approach
- 使用Rabin-Karp算法的思想，通過計算魔法咒語S中每個長度為M的子字符串的哈希值並與模式P的哈希值進行比較，來確定是否匹配或為旋轉形式匹配。
- 利用哈希表來存儲模式P的所有可能旋轉形式的哈希值，從而實現快速查找和匹配。

### Efficiency Considerations
- 透過使用多個哈希表來降低偽陽性匹配的可能性，從而提高算法的準確性和效率。
- 採用字符到數字的映射和模數運算來有效地計算和更新哈希值，以適應字符串的旋轉特性。