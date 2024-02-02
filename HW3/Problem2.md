# Problem 2 - Mega Knights

## Problem Description
In a realm, n mega knights are positioned at n unique locations. Each mega knight Ki (1 ≤ i ≤ n) can inflict ai damage (attack points) when attacking and possesses hi health points, indicating the maximum damage the knight can sustain.

Upon receiving an attack command, a mega knight Ka summons all knights at his location to advance towards the target mega knight Ks, engaging in a collective assault. The area-effect attack reduces the health points of all knights at Ks's location by the total attack points of the assailants. Any knight whose health drops to 0 or below is deemed defeated. Post-attack, the assailants occupy Ks's position.

A fallen knight cannot initiate or become the target of attacks. Should such a command arise, it results in no action. Similarly, if Ka and Ks share the same location prior to the attack, the command is disregarded.

Given m attack instructions, ascertain the total successful attacks executed by each mega knight, including both direct commands and instances where the knight joins another's attack.

### Input Format
The initial line specifies n and m—the number of mega knights and attack rounds, separated by a space. The subsequent line lists n positive integers h1, h2, ..., hn, denoting each knight's health points. The following line presents n positive integers a1, a2, ..., an—each knight's attack points. Each of the m ensuing lines contains two positive integers, Ka and Ks, indicating the attacking and target knights, respectively.

### Output Format
Produce a line with n integers, separated by spaces, where the i-th integer reflects the total successful attacks by the i-th mega knight.

### Constraints
- 1 ≤ n, m ≤ 2 × 10^5
- 1 ≤ ai, hi ≤ 10^9
- 1 ≤ Ka, Ks ≤ n
- Ka ≠ Ks

### Subtasks

#### Subtask 1 (15 pts)
- 1 ≤ n, m ≤ 10^3
#### Subtask 2 (20 pts)
- It is guaranteed no mega knight will perish.
#### Subtask 3 (65 pts)
- No additional constraints.

### Sample Input 1
6 5  
7 7 7 7 7 14   
3 1 4 1 5 9   
2 3  
2 1  
4 3  
1 6  
3 6  

### Sample Output 1
1 3 2 2 0 0

## Program Analysis

模擬了一個涉及巨型騎士、攻擊指令和騎士間互動的復雜場景。通過結構化數據跟踪每個騎士的攻擊點、健康點和成功攻擊次數，以及騎士死亡的狀態。

### Main Function
- 初始化變量並讀取巨型騎士的數量、健康點、攻擊點和攻擊指令。
- 根據指令更新騎士的狀態，包括計算攻擊造成的傷害、確定騎士的生死狀態，並在攻擊後更新騎士的位置。。

### Key Functions
- `find_set`&`union_set`：實現並查集操作，用於管理騎士間的聯合攻擊和位置聚集。
- `compare`：在min heap操作中使用，幫助維護騎士的健康狀態和攻擊效果。

### Algorithmic Approach

- 採用disjointed set和min heap結構來有效管理騎士群體的動態變化，包括攻擊、死亡和位置變更。
- 透過迭代更新過程來處理每個攻擊指令，計算攻擊結果並更新相關騎士的狀態和統計。

### Efficiency Considerations
- 使用disjointed set結構減少了對騎士群體動態變化的重複計算，提高了處理大量騎士和攻擊指令的效率。
- min heap的使用幫助快速確定和更新需要從攻擊中移除的騎士，以及調整騎士間的位置和攻擊力分配。