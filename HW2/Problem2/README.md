# Problem - Magical Cats

## Problem Description
Demeter Sphynx Abyssinian (a.k.a. DSA) is a passionate cat lover who shares zir home with hundreds of thousands of furry felines. These adorable creatures consume tons of food every day, so DSA wants to gather statistics in order to formulate a feeding plan for the future.

There are N cats in the house, and each cat living in the ith room has a unique appetite ai. This appetite value represents the amount of food distributed to that cat every day. Furthermore, each cat is associated with a color represented by an integer value bi.

DSA is interested in establishing a correlation between a cat’s color and its appetite. In particular, ze wants to determine the number of cats that have an appetite falling within the range [lj,rj] and possess the color cj.

Nevertheless, there are some greedy cats in the household who desire more food and sneakily exchange their bowls with some unsuspecting cats. To avoid getting caught by DSA, a greedy cat always picks a victim whose appetite is closest to its own from among the cats with larger appetites. Whenever two cats’ bowls are swapped, their appetites are swapped as well, since DSA distributes food based on the size of the bowls. Please note that the cat that has the largest appetite at any point cannot be greedy.

Recently, a magical fairy pays a visit to DSA’s home and casts some spells on the cats. The fairy first selects a particular color cj and then picks the cat with the highest or lowest appetite among all the cats with that color. The chosen cat will then be able to increase its appetite to the highest appetite of all cats plus one, denoted as max0≤i < N(ai) + 1. However, on occasion, the magic may fail, causing the opposite effect that decreases the cat’s appetite to the smallest appetite of all cats minus one, denoted as min0≤i< N (ai) − 1. The selection of the cat with the highest (1) or lowest (0) appetite to receive the magic is represented by sj ∈ {1,0}, and the success (1) or failure (0) of the magic is represented by tj ∈ {1, 0}. It is important to note that a cat’s appetite may become negative as a result of this magic.

Given M mixed steps of DSA’s question-asking, greedy cats’ swapping, and fairy’s magic spells, can you make sure that each of DSA’s questions is answered correctly?

### Input Format
The first line contains two space-separated integers N, M, the number of cats and the number of steps. The cats will be 0-indexed. The second line contains N space-separated integers a0, a1, . . . , aN−1, where ai is the appetite of the ith cat. The third line contains N space-separated integers b0, b1, . . . , bN−1, where bi is the color of the ith cat. Each of the next M lines contains one of the following:

1. cj lj rj: a questioning step (1) followed by three space-separated integers cj, lj, rj, which denote the color, the lower bound, and the upper bound of the question. There can be no cats that are of color cj in a questioning step.
2. kj: a swapping step (2) followed by an integer kj, which is the index of a greedy cat.
3. cj sj tj: a magic step (3) followed by three space-separated integers cj, sj, tj, which denotes the color, the direction of the magic, and the success/failure of the magic. We guarantee that a cat with color cj always exists for a magic step.

### Output Format
For each questioning step, output the answer to the question in a new line.

### Constraints
- 2 ≤ N ≤ 3 × 10^5
- 1 ≤ M ≤ 3 × 10^5
- 1 ≤ ai, bi, cj ≤ 10^9
- 0 ≤ kj < N
- sj, tj ∈ {0,1}
- −2 × 10^9 ≤ lj ≤ rj ≤ 2 × 10^9

### Subtasks

#### Subtask 1 (10 pts)
- 1 ≤ M ≤ 10^3
#### Subtask 2 (10 pts)
- Only questioning steps.
#### Subtask 3 (30 pts)
- Only questioning and swapping steps. Hint: You are highly encouraged to conquer this subtask (or even easier ones) first before solving the problem in general.
#### Subtask 4 (50 pts)
- No other constraints.

### Sample Input 1
6 5   
2 1 6 4 5 3  
2 1 3 2 3 3   
1 2 1 4   
1 4 3 6   
2 3   
1 2 2 3   
1 3 4 6  
### Sample Output 1
2  
0  
1  
2 

## Program Analysis

旨在管理具有獨特食慾和顏色的貓在DSA家庭的複雜情境。處理了查詢貓統計數據、由於貪婪行為而進行的交換操作，以及影響貓食慾的魔法干預。

### Main Function
- 初始化變量以儲存貓的食慾、顏色、問題、交換和魔法效果的步驟。
- 讀取N隻貓的食慾和顏色的輸入，接著是M步操作。
- 將貓組織成數組和鏈表，以便於高效地查詢、更新和追蹤食慾和顏色。

### Key Functions
- `compare`：幫助按它們的食慾或顏色對貓的數組進行排序，以便於高效查詢。
- `binarySearch_color`& variant：在結構化數據中進行高效搜索，以找到特定顏色或具有某些範圍食慾的貓。
- 處理魔法行動和交換的函數：應用邏輯來根據魔法效果或貪婪行為調整貓的食慾，並計算DSA的查詢結果。

### Algorithmic Approach

- 利用數組、鏈表和二分搜索算法有效地組織和查詢有關貓的食慾和顏色的數據。
- 實施排序機制以便於快速查找和更新貓的信息。
- 通過對數據結構進行特定操作來模擬貪婪行為和魔法干預，相應地更新貓的食慾。

### Efficiency Considerations
- 通過排序和二分搜索有效地處理數據，減少了操作的複雜性，確保系統能夠有效地管理大量的貓和步驟。
- 通過動態更新數據結構，如鏈表，允許實時追踪由於交換或魔法而發生的貓的食慾變化，最小化了全面遍歷或重複計算的需求。