# Problem - Rotating... Again?!

## Problem Description
Do you recall the game developer, Little Cucumber, who recently launched his game? He invited a magical fairy to give it a try, but to his surprise, the fairy cast a bizarre rotating spell on the game.

Long story short, you have to maintain a multiset of strings S. At the beginning, S has N strings. Let ti denote the i-th string in S, 1 ≤ i ≤ N. Then, Q operations will be performed on S, where each operation can be one of the following two:

- insert(tj): insert the string tj into S.
- remove(tj): remove one instance of the string tj from S, it is guaranteed that at least
one tj isinS.

Consider two strings, A and B, of the same length L. A and B are rotationally identical if and only if there exists k,1 ≤ k ≤ L such that A1A2 ...AL = BkBk+1 ...BLB1 ...Bk−1, i.e., if B is rotated by k characters, then A and B are identical.

You are asked to output the number of string pairs in S which are rotationally identical before the first operation and after each operation.

### Input Format
The first line contains two integers N and Q, the number of strings inside S initially and the number of operations, respectively. Then, the next N lines have ti in order, 1 ≤ i ≤ N, where ti is a string in S initially. Each of the next Q lines contains an integer P and a string tj.

- If P = 1, it represents an insert(tj) operation.  
- If P = 2, it represents a remove(tj) operation.

### Output Format
The output should consist of Q + 1 lines. The first line should contain an integer representing the number of rotationally identical string pairs in S initially. Each of the next Q lines should also contain an integer representing the number of rotationally identical string pairs in S after each operation.

### Constraints
- 2 ≤ N ≤ 10^6
- 0 ≤ Q ≤ 10^6
- 1 ≤ |ti| = |tj| = M ≤ 10^6
- Strings consist only of lowercase Latin letters.
- (N + Q)M ≤ 10^6

### Subtask 1 (10 pts)

- N, Q, M ≤ 50


### Subtask 2 (15 pts)

- Q = 0

### Subtask 3 (15 pts)

- M = 3

### Subtask 4 (60 pts)

- No other constraints.

### Sample Input 1
6 0
ntu
tun
unt
sad
dsa
qqq

### Sample Output 1
4

### Sample Input 2
3 7
bananana
nananaba
cucumber
1 nanabana
1 nabanana
1 anananab
2 cucumber
1 cumbercu
1 bercucum
2 nanabana


### Sample Output 2
1
3
6
10
10
10
11
7


## Program Analysis

這個程式設計用於維護一個多重集合S，其中包含N個字符串。通過進行Q個操作，包括插入和移除字符串，來動態地更新集合。利用旋轉等價概念，判斷兩字符串是否通過旋轉能夠匹配。此外，通過計算集合中旋轉等價字符串對的數量，來應對每個操作前後的狀態變化。

### Main Function
- 初始化變數，讀取初始字符串集合S及操作數量。
- 對於每個操作，更新集合S，計算並輸出旋轉等價字符串對的數量。

### Key Functions
- `build_hash`&`insert_hash`&`delete_hash`：這些函數實現對字符串的哈希計算，以及根據旋轉等價規則插入和移除字符串。
- 使用Rabin-Karp哈希算法來有效比較字符串及其所有旋轉版本的哈希值。


### Algorithmic Approach
- 採用哈希表來存儲每個字符串及其旋轉版本的哈希值，從而快速識別旋轉等價的字符串對。
- 對於每個操作，動態更新哈希表並重新計算旋轉等價字符串對的總數。

### Efficiency Considerations
- 通過哈希算法減少了對字符串旋轉版本的直接比較，提高了比較效率。
- 功能函數的設計使得對於大量操作和大規模數據的處理變得高效。