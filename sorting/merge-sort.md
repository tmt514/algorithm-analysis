# 合併排序法

如果我們不限制每次都交換相鄰兩個數字的話，顯然存在著理論上有更有效率的排序演算法。

分而治之（Divide and Conquer）是重要的解題方法之一：我們將一個大問題拆解成許多小問題、個個擊破以後再把它們組合回來。
如果我們將分而治之法應用在排序問題當中，就可以得到俗稱合併排序法（Merge Sort）的演算法：

* 假設欲排序 $A[0..n-1]$。
  1. 把輸入的資料拆成差不多相等的兩半：$L=A[0..\lfloor\frac{n}{2}\rfloor-1]$、$R=A[\lfloor\frac{n}{2}\rfloor..n-1]$。
  2. 呼叫遞迴將兩邊分別排序。
  3. 假設 $L$ 與 $R$ 已經各自排好順序，將 $L$ 與 $R$ 合併回完整的、排好順序的資料陣列 $A$。
  
實作上大概長得像這樣：

```cpp
void MergeSort(data_t *A, int n) {
  // 只剩一個元素的時候，整個陣列就已經排好順序啦。
  if (n <= 1) return;
  // Divide & Conquer 的各自遞迴部分。
  MergeSort(A, n/2);
  MergeSort(A + n/2, n - n/2);
  // Combine: 這邊是仿效 C++ STL 的 std::merge() 格式。
  Merge(A, A + n/2, A + n/2, A + n, A);
}
```

## 合併兩個序列

要怎麼將兩個排好順序的序列合併起來呢？一個簡單的想法是：每一次考慮兩個序列目前的排頭，把比較小的那個拉出來，最終接成一串。
如果用 linked list 或 vector 寫起來大概像這樣：

```cpp
void Merge(data_t *L_start, data_t *L_end,
           data_t *R_start, data_t *R_end, data_t *Output) {
  vector<data_t> tmp;
  data_t *L_ptr = L_start, *R_ptr = R_start;
  while (L_ptr != L_end || R_ptr != R_end) {
    // 把比較小的那筆資料複製到 vector 裡面。
    if (L_ptr != L_end && (R_ptr == R_end || *L_ptr < *R_ptr))  // (**)
      tmp.push_back(*L_ptr++);
    else
      tmp.push_back(*R_ptr++);
  }
  // 再把合併好的資料抄回去。
  for (const auto &data : tmp) *Output++ = data;
}
```

不難發現，由於兩個指標 `*L_ptr` 和 `*R_ptr` 不斷遞增，而且每次迴圈**恰好**有一者前進一格。
因此整個 `Merge()` 的時間複雜度是線性的 $\Theta(n)$。
正確性來自於對排序資料的假設、以及每一次我們都拉比較小的排頭出來，這個排頭必定是剩下所有還沒被排進來的資料中，最小的一個。

近幾年這個合併兩個序列的方法已經被歸類成一種叫做 Two Pointers 的技巧。當然這個技巧當初是用來描述[龜兔賽跑方法](https://en.wikipedia.org/wiki/Cycle_detection)（這個用來找 Linked List 尾圈方法我們以後再聊），但已經被推廣成泛指「只要維護兩個註標，這兩個註標只會往單方向移動」的演算法。

## 時間複雜度的分析

由於每一次的資料搬移，大致可以對應到 (**) 處的比較，因此合併排序法所需要的時間，我們可以用「兩兩比較次數」代表之。
現在我們來證明合併排序法的時間複雜度是 $O(n\log n)$。

### 引理 8

令 $T(n)$ 表示以合併排序法排序 $n$ 個數字時，所需要進行的比較次數。則 $T(n) = O(n\log n)$。

### 證明

首先，當 $n$ 是 $2$ 的冪次（即 $n$ 形如 $2^k$ 時），兩個子問題的大小都是 $n/2$。此時我們有：

$$
T(n) = \begin{cases} 0 & \text{ if } n\le 1, \\
2T(\frac{n}{2}) + n-1 & \text{ if } n > 1. \end{cases}
$$

然後根據[主定理（Master Theorem）](https://zh.wikipedia.org/zh-tw/%E4%B8%BB%E5%AE%9A%E7%90%86)或是數學歸納法，不難得出 $T(n) = \Theta(n\log n)$ 的結論。

當 $n$ 不是 $2$ 的冪次時（這很重要！）上面這個時間複雜度的遞迴式其實不全然正確。
事實上，遞迴式應該是這樣才對：

$$
T(n) = T(\floor{\frac{n}{2}}) + T(\ceil{\frac{n}{2}}) + n-1
$$

好加在，我們可以利用數學歸納法證明出 $T(n)$ 是遞增的。換句話說，令 $n' = 2^{\ceil{\log n}}$，利用 $n \le n' < 2n$，我們可以得到

$$
T(n) \le T(n') = \Theta(n' \log n') = \Theta(n\log n)\text{。}
$$

-----

合併排序法在合併的時候，會需要**複製**欲排序的資料。因此，合併排序法在實作的時候，一般來說會佔用到 $\Theta(n)$ 的額外記憶體空間。
我們有辦法省下額外的記憶體嗎？