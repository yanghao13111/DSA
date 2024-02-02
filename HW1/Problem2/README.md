# Problem - Cycling Teams and Bakeries (100 pts)

## Problem Description
Cycling teams resemble swarms of locusts, swiftly moving through and consuming everything in their path. Seven city consists of a street grid with n horizontal roads and m vertical roads. The horizontal roads are numbered by their position relative to the north, indexed by i, while the vertical roads are numbered by their position relative to the west, indexed by j. The distance between any two consecutive horizontal roads (i and i + 1) is equal to the distance between any two consecutive vertical roads (j and j + 1), for all 1 ≤ i ≤ n − 1 and 1 ≤ j ≤ m − 1. At every intersection of a horizontal road i and a vertical road j, there is an open bakery denoted by bij. Based on its Google Map reviews and ratings, each bakery is assigned a unique rank uij between 1 and mn. Furthermore, each bakery is initially stocked with a certain number of toasts, denoted by tij.

There are two training periods for cycling teams, and one racing period in between. The first training period is of T1 days, the second training period is of T2 days, and the racing period is for R days. On each day k within the training periods (1 ≤ k ≤ T1 or T1+R+1 ≤ k ≤ T1+R+T2), a cycling team with sk members would be at an open bakery of rank rk as the initial gathering bakery, and plans a tour of length at most lk to other bakeries based on the following steps:

1. Select all open bakeries that are located on the same horizontal or vertical road as the team’s current position but have not been visited on day k, excluding the gathering bakery at the current position. If no such open bakeries exist, the team ends its training and returns home.
2. Among the selected bakeries, choose the ones with the minimum distance to the gathering bakery.
3. Among the chosen bakeries, visit the one with the smallest rank.
4. Let each member of the team eat a piece of toast to restore energy at the bakery being visited. That is, decrease the number of toasts tij by sk for the bakery. If the new tij ≤ 0, the bakery being visited would then need to be closed.
5. If the number of bakeries that the team has visited does not exceed lk, set the bakery being visited as the new gathering bakery, and go to step 1. Otherwise, the team ends its training and returns home.

On each day k within the racing period (T1 + 1 ≤ k ≤ T1 + R), the 80kings would choose an open bakery with rank rk as the center of the racing track. The track is a square with a side length of lk − 1, with an odd number lk of intersections on each side. The many cycling teams would race through the streets at breakneck speeds, their powerful legs propelling them forward with such force that a mighty tornado formed in their wake. As they hurtled around the square track, the tornado wreaked havoc on the surrounding area, lifting and rotating bakeries within the square, including those on the racing track, by 180 degrees with tremendous force.

Given the plan on each day of the training and racing periods, output the final number of toasts of the bakeries.

### Input Format
- There are 2 integers n, m separated by a space in the first line.
- Each of the next n lines contains m integers separated by spaces. The j-th integer of the i-th line is uij (the rank of bij).
- Each of the next n lines contains m integers separated by spaces. The j-th integer of the i-th line is tij (the initial number of toasts of bij).
- There are 3 integers T1, R, T2 separated by spaces in the next line, which denote the number of days for the first training period, the racing period, and the second training period, respectively.
- Each of the next T1 lines corresponds to each day in the first training period, and contains 3 integers rk (the rank of the initial gathering bakery), lk (the maximum riding length), and sk (the size of the cycling team), separated by spaces.
- Each of the next R lines corresponds to each day in the racing period, and contains 2 integers rk (the rank of the center bakery) and lk (the odd side length of the square track), separated by spaces.
- Each of the next T2 lines corresponds to each day in the second training period, and contains 3 integers rk (the rank of the initial gathering bakery), lk (the maximum riding length), and sk (the size of the cycling team), separated by spaces.

### Output Format
Output n lines, each line contains m integers separated by spaces. The j-th integer of the i-th line should be tij, which is the final number of toasts of bij, for any open bakery. If the bakery is closed (i.e. tij ≤ 0), simply output 0.

### Constraints
- 1 ≤ n, m ≤ 1000
- 1 ≤ tij, sk ≤ 10^9, ∀i,j,k
- 1 ≤ uij, rk ≤ nm, ∀i,j,k. All uij are distinct.
- lk ≥ 0
- T1 + R + T2 ≤ 10^6
- ∑ lk ≤ 10^6 k

### Subtasks
#### Subtask 1 (10 pts)
- ∑lk ≤ 10^3
#### Subtask 2 (15 pts)
- R = 0
#### Subtask 3 (15 pts)
- T1 = T2 = 0
#### Subtask 4 (60 pts)
- no other constraints
### Sample Input 1
5 5  
8 9 10 11 17  
7 15 16 12 18  
6 14 4 13 19  
5 3 2 1 20  
25 24 23 22 21  
49 1 7 14 7  
2 14 49 7 7  
7 49 14 2 7  
7 7 1 49 14  
14 7 7 7 49  
1 1 1  
1 11 4  
4 3  
1 10 9  
### Sample Output 1
45 0 0 1 7  
0 49 0 0 7  
0 0 5 40 7  
0 0 40 5 14  
14 7 7 7 49  

## Program Analysis

程式碼旨在模擬自行車隊在城市中的訓練和比賽期間對麵包店的影響。它通過動態記憶體分配、鏈表操作、和複雜算法來解決問題，展示了數據結構和算法在解決實際問題中的應用。以下是對其主要功能的分析：

### Main Function
- 讀取城市尺寸、麵包店的初始排名和麵包數量、訓練和比賽的天數。
- 初始化地圖來存儲麵包店的位置和麵包數量。
- 分別對第一和第二個訓練期間以及比賽期間執行模擬，更新麵包店的麵包數量和開閉狀態。
- 輸出最終所有麵包店的麵包數量。

### Key Functions
- `eatToast`：模擬自行車隊在訓練期間訪問麵包店，消耗麵包。
- `chooseNext`：根據規則選擇下一個要訪問的麵包店。
- `relativePosition`&`relativePositionForTrain2`：初始化麵包店的相對位置信息，用於訓練期間的導航。
- `listRotation`：在比賽期間旋轉賽道內的麵包店。
- `listToArray`：將麵包店的鏈表結構轉換回陣列結構以便最後輸出。

### Algorithmic Approach
- 使用結構化數據來管理城市中的麵包店和自行車隊的移動。
- 透過選擇最近且排名最高的麵包店作為訓練路徑的一部分。
- 在比賽期間採用旋轉算法來模擬賽道內麵包店的位置變化。

### Efficiency Considerations
- 通過使用鏈表來有效管理動態變化的麵包店位置，降低了在大規模數據集上操作的複雜度。
- 利用動態記憶體分配來靈活管理麵包店的數據，適應於比賽期間可能的位置變化。