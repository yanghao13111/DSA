# Problem - King of DSA

- Time Limit: 1 s
- Memory Limit: 2048 KB

## Problem Description
Little Cucumber is currently developing “Digital Savage Arena” (DSA), a video game in- spired by KoH (King of the Hill), with plans to release the alpha version on April 11th to collect feedback from players. However, he has been facing difficulties with the arena system for weeks due to his lack of study in the data structures and algorithms class. Since you have successfully completed the notorious Homework 0 in the class, can you assist him with solving the final piece of the puzzle?

In DSA, N players compete in an arena to earn prestigious honor. The game consists of N rounds. The i-th player, which carries an attack power of ai, enters the arena at the beginning of the i-th round. As soon as the player enters the arena, ze kills all other players that hold a lower attack power.

At the end of each round, the player with the highest attack power is awarded the “King of DSA.” In the event of a tie, the player who entered the arena earlier will be awarded the title. However, due to memory limitations, the size of the arena must be limited. If the number of surviving players in the arena exceeds M, a revolution will occur, resulting in the King of DSA being overthrown and killed by the other M players.

In short, round i of the game executes the following three steps orderly:
1. Player i enters the arena.
2. Player i kills all other players that hold a lower attack power.
3. Check if a revolution occurs. If so, the King of DSA is killed.

Given the attack power of the N players, can you help Little Cucumber calculate the players that are killed in each round?

### Input
The first line contains two integers N and M—the number of rounds (players) and the arena’s maximum capacity. The second line contains N integers a1, a2, . . . , aN , which is the attack power of each player, separated by space.

### Output
The output should consist of N + 1 lines. The first N lines should begin with the string “Round i:”, where i is the round number. Each of the N lines should include the player(s) that are killed in that round. The last line should begin with the string “Final:”, followed by the players who are still alive at the end of the game. When outputting the players (killed ones in the first lines and the surviving ones in the last line), print out the players’ indices (the round that each of them entered the arena), sorted in descending order and separated by space.

### Constraints
- 1 ≤ N ≤ 10^6
- 1 ≤ M ≤ 10^3
- 1 ≤ ai ≤ 10^9

### Subtask 1 (10 pts)
- 1 ≤ N ≤ 10^3

### Subtask 2 (30 pts)
- It is guaranteed that a revolution will never occur.

### Subtask 3 (60 pts)
- No other constraints.

### Sample Input 1
10 4  
8 5 2 4 7 6 5 3 4 6
### Sample Output 1
Round 1:  
Round 2:  
Round 3:  
Round 4: 3  
Round 5: 4 2  
Round 6:  
Round 7:  
Round 8: 1  
Round 9: 8  
Round 10: 9 7  
Final: 10 6 5  

### Hints
- Please note the memory limit, which requires you to use O(M) memory.

## Program Analysis

旨在解決“King of DSA”問題，利用結構體陣列來存儲玩家的索引和攻擊力，並使用二分法來優化搜索和更新過程。

### Main Function
- 首先讀入玩家數量和競技場的最大容量。
- 對於每一位進入競技場的玩家，計算該輪中被殺死的玩家，並根據需要更新存活玩家的列表。
- 利用二分搜索法來確定新玩家是否擁有足夠的攻擊力來殺死其他玩家，並相應地更新存活玩家的列表。
- 如果存活玩家的數量超過競技場的容量，則會發生“革命”，導致當前的“DSA之王”被殺死，並從列表中移除。
- 最後輸出每一輪中被殺死的玩家的索引，以及遊戲結束時仍存活的玩家的索引。

### Efficiency Considerations
- 通過在存儲玩家資訊時使用結構體陣列和二分法來查找和更新玩家，有效地減少了運行時間和記憶體使用。
- 這種方法允許在維持低記憶體使用的同時，快速處理大量玩家的情況。