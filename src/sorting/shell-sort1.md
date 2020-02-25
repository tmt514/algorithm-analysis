# 謝耳排序

今天來講講插入排序的另一種特殊變化型。
這一類特化是由 [Donald L. Shell](https://en.wikipedia.org/wiki/Donald_Shell) 在 1959 年提出。
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

### 謝耳排序

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

### 百家爭鳴的步長序列

我們知道插入排序法的最差時間複雜度是 $O(n^2)$。
最早由 Shell 提出這個改進的時候，謝耳教授只是發現在實際模擬時，這個演算法執行時間優於插入排序法。
接下來在 1960、1963、1965、1971 年陸陸續續地出現了因應各種不同的 Gap Sequence 得到的時間複雜度理論上界，證明了謝耳排序確實比插入排序法有效率得多。

### 一個觀察

遺憾的是，Shell 的改良方法在 1992 年由 Plaxton, Poonen 與 Suel 等人[^1]證明出了對於任意步長序列，Shell Sort 在最差情形的時間複雜度至少有 $\Omega(n (\log n / \log\log n)^2)$。因此，這類型的改良方法並沒有辦法在理論上達到如同快速排序或合併排序法等，接近真正的比較排序下界。


### 推薦閱讀

* [yehyeh's notepad](http://notepad.yehyeh.net/Content/Algorithm/Sort/Shell/Shell.php) 這個對 Shellsort 演算法介紹得很淺顯易懂，但沒有對 Gap Sequence 深入的分析。

[^1]: C.G. Plaxton, B. Poonen, and T. Suel, _Improved lower bounds for Shellsort_, FOCS 1992. [https://ieeexplore.ieee.org/document/267769](https://ieeexplore.ieee.org/document/267769)
