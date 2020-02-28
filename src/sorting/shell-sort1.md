# 謝耳排序法（一）

今天來講講插入排序的另一種特殊變化型。
這一類特化是由 [Donald L. Shell](https://en.wikipedia.org/wiki/Donald_Shell) 在 1959 年提出[^2]。
謝耳排序之所以非常非常有趣，是因為它根據不同的「步長序列」（Gap Sequence）設定，會有著不同的最差情形時間複雜度。

## 步長與步長序列

這個插入排序法的變化是這樣的：一般來說我們會把新加入的資料與前面已經排好序的序列進行插入排序，從最後一個數字往前面逐一比較，並且交換。謝耳教授引入了一個新的想法，如果我們把整個陣列打散，依照指定步長 $h$（或稱為間隔，Gap）分成 $h$ 個群組：每隔 $h$ 筆資料就被分配到同一組。

### 定義

我們說一個陣列是 **$h$-排序（$h$-sorted）** 的，若且唯若每一個群組由左至右都是由小到大排好序的。

從上面的定義看起來，一個真正排好序的序列是 $1$-排序的。
我們的目的是根據某個序列 $h_0=1 < h_1 < \ldots < h_k$，逐步把陣列變成 $h_k$-sorted、$h_{k-1}$-sorted、依此類推最終變成 $1$-sorted。而此時這個序列便稱為 **步長序列（Gap Sequence）**。

### 各自排序

要怎麼把一個陣列整理成 $h$-sorted 呢？我們可以輕易地使用插入排序法完成任務：

```cpp
void h_sort(int arr[], int N, int h) {
  for (int i = 0; i < N; i += h) {
    // 把新的元素 arr[i] 插入所屬群組中。
    for (int j = i; j >= h && arr[j-h] > arr[j]; j -= h)
      swap(arr[j-h], arr[j]);
  }
}
```

### 引理 33

對陣列無任何假設的情形下，`h_sort` 執行的最差時間複雜度為 $O(N^2/h)$。

### 引理 33 的證明

整個陣列根據間隔 $h$ 分成了 $h$ 組，每一組有 $N/h$ 筆資料。上述演算法等價於對每一組分別進行插入排序法，所以最差時間複雜度是 $O(h(N/h)^2) = O(N^2/h)$。
<span style="float:right">$\square$</span>

### 謝耳排序法

整理成 $h$-sorted 以後，就可以根據不同的 $h$ 值呼叫這個子函式了：

```cpp
void shell_sort(int arr[], int N, int h[], int H) {
  // 假設 h[0], h[1], ..., h[H-1] 已經由小排到大了。
  for (int i = H-1; i >= 0; --i)
    h_sort(arr, N, h[i]);
}
```

### 選取步長序列

顯然如果序列只有一個元素 $h[0] = 1$ 的話，演算法就會退化成一般的插入排序法，執行的時間複雜度就是 $O(N^2)$。

在 1959 年由 Shell 提出這個想法的時候，使用的是 $1, \ldots, \floor{N/8}, \floor{N/4}, \floor{N/2}$ 這樣的步長序列。
這個步長序列在 $N$ 是 $2$ 的冪次時，在最壞情形下仍然有著 $\Omega(N^2)$ 的時間複雜度。(為什麼？提示：奇數位置所有數字都比偶數位置來得大。）
謝耳教授只是發現在實際模擬時，這個演算法執行時間優於插入排序法。

好消息是，接下來在 1960、1963、1965、1971 年陸陸續續地出現了因應各種不同的 Gap Sequence 得到的時間複雜度理論上界，證明了謝耳排序法在某些特殊的 Gap Sequence 底下確實比插入排序法有效率得多。

### 關於下界

遺憾的是，Shell 的改良方法在 1992 年由 Plaxton, Poonen 與 Suel 等人[^1]證明出了對於任意步長序列，Shell Sort 在最差情形的時間複雜度至少有 $\Omega(n (\log n / \log\log n)^2)$。因此，任何謝耳排序類型的演算法，並沒有辦法在理論上達到如同快速排序或合併排序法等，逼近真正的 $n\log n$ 比較排序下界。

-----

明天我們來看第一個改進最差時間複雜度的例子：如果 $h_i = 2^i-1$，那麼就可以得到
$O(N^{3/2})$ 時間複雜度的謝耳排序。1960 年的 Lazarus 和 Frank[^3] 提出了這個排序方法、並且在 1961 年出現在 Hibbard[^4] 的實驗中。但一個乾淨的證明直到 Pratt 在史丹佛大學的博士論文[^5]才集大成（對，就是那個 Knuth-Morris-Pratt KMP 演算法的 Pratt）給出了上界證明。

### 推薦閱讀

* [yehyeh's notepad](http://notepad.yehyeh.net/Content/Algorithm/Sort/Shell/Shell.php) 這個對 Shellsort 演算法介紹得很淺顯易懂，但沒有對 Gap Sequence 深入的分析。
* Robert Sedgewick, [Analysis of Shellsort and Related Algorithms](http://thomas.baudel.name/Visualisation/VisuTri/Docs/shellsort.pdf).
* [維基百科 Shellsort](https://en.wikipedia.org/wiki/Shellsort)

[^2]: D.L. Shell, _A high-Speed Sorting Procedure_, Communications of the ACM, 1959. [https://dl.acm.org/doi/10.1145/368370.368387](https://dl.acm.org/doi/10.1145/368370.368387)

[^1]: C.G. Plaxton, B. Poonen, and T. Suel, _Improved lower bounds for Shellsort_, FOCS 1992. [https://ieeexplore.ieee.org/document/267769](https://ieeexplore.ieee.org/document/267769)

[^3]: R.M. Frank, R.B. Lazarus, _A high-speed sorting procedure_, Communications of the ACM, 1960. [https://dl.acm.org/doi/10.1145/366947.366957](https://dl.acm.org/doi/10.1145/366947.366957)

[^4]: Thomas N. Hibbard, _An empirical study of minimal storage sorting_, Communications of the ACM, 1963. [https://dl.acm.org/doi/10.1145/366552.366557](https://dl.acm.org/doi/10.1145/366552.366557)

[^5]: Vaughan R. Pratt, _Shellsort and Sorting Networks_, Ph.D Thesis, Stanford University, 1972. [https://apps.dtic.mil/dtic/tr/fulltext/u2/740110.pdf](https://apps.dtic.mil/dtic/tr/fulltext/u2/740110.pdf)