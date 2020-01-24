# 排序 Sorting

排序是整理資料中一種最直接的方式。

## 基於比較的排序 Comparison Based Sorting

| 演算法 | 時間複雜度 | 空間複雜度 |
|-------|---------|----------|
| 泡沫排序法 | 最差 $O(n^2)$, $O(n + n\tau)$ | 最差 $O(1)$ |
| 雞尾酒排序法 | 最差 $O(n^2)$, $O(n + n\sqrt{\tau})$ | 最差 $O(1)$ |
| 插入排序法 | 最差 $O(n^2)$, $O(n + \tau)$ | 最差 $O(1)$ |
| 選擇排序法 | 最差 $O(n^2)$ | 最差 $O(1)$ |
| 合併排序法 | 最差 $O(n\log n)$ | 最差 $O(n)$ |
| 原地合併排序 | 最差 $O(n\log n)$ | 最差 $O(1)$ |
| 快速排序法 - 第一個數字 pivot | 最差 $O(n^2)$ | 最差 $O(d) = O(n)$ |
| 快速排序法 - 隨機選 pivot | 期望 $O(n\log n)$ | 期望 $O(d) = O(\log n)$ |
| 快速排序法 - 找中位數 pivot | 最差 $O(n\log n)$ | 最差 $O(d) = O(\log n)$ |
| 原地快速排序 | 最差 $O(n^2)$ | 最差 $O(1)$ |
| 堆積排序法 | 最差 $O(n\log n)$ | 最差 $O(1)$ |

### 註記

* $n$ 代表輸入的資料量（序列元素個數）。
* $\tau$ 代表輸入序列的逆序數對個數。
* $d$ 代表遞迴深度。

## 資料不改變存取位置的排序 Data-Oblivious Sorting

| 演算法 | 時間複雜度 | 排序網路深度 |
|-------|----------|-----------|
| Shell 排序法 | 最差 $O(n^2)$ | $O(n)$ |
| Shell 排序法 - Pratt 版本 | 最差 $O(n\log^2 n)$ | $O(\log^2 n)$ |
| Batcher 雙調排序法 | 最差 $O(n\log^2 n)$ | $O(\log^2 n)$ |
| 奇偶合併排序 | 最差 $O(n\log^2 n)$ | $O(\log^2 n)$ |
| Ajtai-Komlós-Szemerédi 排序網路 | 最差 $O(n\log n)$ | $O(\log n)$ |
| Goodrich 排序網路 | 最差 $O(n\log n)$ | $O(n\log n)$ |

## 基於資料數值的排序 Numbers Sorting

| 演算法 | 時間複雜度 | 備註 |
|-------|----------|------|
| 計數排序法 | $O(n+M)$ | 正整數資料範圍 $O(M)$ |
| $k$-進制桶子排序法 | $O((n+k)\log_k \frac{1}{\epsilon})$ | 最相近兩數之相對誤差 $\epsilon = \frac{\min_{i\neq j} |A[i]-A[j]|}{\max_i |A[i]|}$ |
| $k$-進制基數排序法 | $O((n+k)\log_k M)$ | 正整數資料範圍 $O(M)$ |

## 二進位整數排序 Sorting in Word RAM Model

| 演算法 | 時間複雜度 | 備註 |
|-------|----------|------|
| van Emde Boas 樹 | $O(n\log\log M)$ | 空間複雜度 $O(M)$ |
| X-fast 字母樹 | $O(n\log\log M)$ | 空間複雜度 $O(n\log M)$ |
| Y-fast 字母樹 | $O(n\log\log M)$ | 空間複雜度 $O(n)$ |
| Fusion Tree | $O(n\log n/\log\log n)$ | 允許隨機與除法可做到 $O(n\sqrt{\log n})$ |
| Packed Sort | | |
| Signature Sort | | |
| Han-Thorup 整數排序 - 確定性 | $O(n\log \log n)$ | 空間複雜度 $O(n)$ |
| Han-Thorup 整數排序 - 隨機 | 期望 $O(n\sqrt{\log \log n})$ | 空間複雜度 $O(n)$ |

### 推薦閱讀

* https://www.bigocheatsheet.com/
* 排序網路（維基百科）：https://en.wikipedia.org/wiki/Sorting_network
* Shell 排序法（維基百科）：https://en.wikipedia.org/wiki/Shellsort
