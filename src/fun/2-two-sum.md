# 2 兩數之和問題 Two Sum

在單調序列上頭使用雙指標技巧 (two pointers) 的題目中，最經典的大概就屬 Two Sum 了。

> **Two Sum 問題**：給定一個長度為 $n$ 的整數陣列 $A[0..n-1]$ 以及一個目標整數 $\mathit{target}$，請設計一個演算法判斷是否存在兩個數字之和恰好為 $\mathit{target}$。輸入保證所有整數介於 $-U$ 與 $U$ 之間，為了方便起見我們**允許**兩數字重複選取。

## 範例

若 $A=[2, 3, -4, 5, 1, 4]$ 且 $\mathit{target}=0$，那麼答案為 $\tt{YES}$。

## 往下看之前

可以先想看看，能不能設計出以下目標時間/空間複雜度的演算法？

| 時間 | 額外空間 | 可否使用隨機數 |
|:---:|:---:|:------:|
| $O(n\log n)$ | $O(1)$ |  No |
| $O(n\log\log n)$ | $O(n)$ |  No |
| $O(n)$ | $O(n)$ |  Yes |
| $O(n)$ | $O(1)$ |  Yes |
| $O(n)$ | $O(1)$ |  No |


## 方法一：排序以後使用雙指標

雙指標 (two pointers) 其實泛指一類長相類似的演算法們，大家根據這些演算法的行為觀察後給予的一個稱呼。
在這些演算法之中，比較常見的便是應用在已排序陣列中，利用陣列內容的單調性 (monotonicity)，進行搜尋或比較的一系列小技巧。
比方說：快速排序法裡頭將陣列依照支點 $\mathit{pivot}$ 值分成兩半的副程式 (subroutine)、合併排序法裡頭合併兩個已排序陣列的副程式等。
本題 Two Sum 在陣列排序後，也能夠使用雙指標小技巧唷！

如果陣列 $A$ 中的元素已經由小排到大了，那麼我們就可以維護兩個註標 $i$ 與 $j$（分別初始化為 $i=0$ 與 $j=n-1$），接著我們可以依據當前的 $A[i]+A[j]$ 之值決定如何更新我們的搜尋：若 $A[i]+A[j] > \mathit{target}$，那麼我們便令 $j\gets j-1$；若 $A[i]+A[j] < \mathit{target}$ 那我們令 $i\gets i+1$。重複這個操作直到 $A[i]+A[j]=\mathit{target}$ 或 $i > j$ 為止。由於 $i$ 只會增加、$j$ 只會減少，這個部分需要花費的時間是 $O(n)$ 的。

### 起手砸個排序

至於排序的部分，我們可以依據可使用的額外空間需求設計排序演算法：

* 使用基於比較的排序方法可以輕鬆做到 $O(n\log n)$ 時間以及 $O(1)$ 額外空間（比如堆積排序法）。
* 使用基於整數的排序方法可以做到 $O(n\log_{1/\epsilon} U)$ 時間以及 $O(U^\epsilon)$ 額外空間（比如基數排序法），其中 $\epsilon$ 可以是任意小的整數。
* 如果有 $O(n)$ 的空間，那麼使用較複雜的 Han-Thorup 整數排序法可以做到 $O(n\log\log n)$ 確定性時間，或者是 $O(n\sqrt{\log\log n})$ 期望時間。

目前還不確定整數排序是否能真的做到線性時間。

## 不是方法二的方法二：使用雜湊方法

總之可以建立一個 [`HashMap`](https://www.w3schools.com/java/java_hashmap.asp) / [Python `set`](https://wiki.python.org/moin/TimeComplexity) / [C++ `unordered_set`](https://en.cppreference.com/w/cpp/container/unordered_set) 然後把 $A$ 中所有數字丟進去，然後對每一筆資料 $x\in A$，檢查 $\mathit{target}-x$ 是否也出現在該資料結構內即可。

『時間與空間複雜度理所當然就是 $O(n)$。』

細心的朋友們一定發現了，這樣的回答非常非常不嚴謹。上述這些資料結構，由於預設為固定亂數種子的關係，在最壞情況下，其表現可能是非常非常糟糕的。

## 方法二：使用雜湊函數與雜湊表

如果要設計基於隨機與雜湊的演算法，就一定得提及 (1) 雜湊族 (hash family) 的選取與 (2) 雜湊表 (hash table) 資料結構的選擇。

如果有 $O(n)$ 的額外空間，那麼使用已知的雜湊表如 Hashing with Chaining (Linear Hashing)、Cuckoo Hashing、Linear Probing 等，都可以在 $O(n)$ 期望/最差時間內將 $n$ 個不同鍵值存放至不同地方。這些雜湊表搭配常見的[通用雜湊函數族 (universal hash function family)](https://en.wikipedia.org/wiki/Universal_hashing) 都相當有效。
因此，對於每一筆資料 $x\in A$，我們只需要檢查 $\mathit{target}-x$ 是否出現在陣列 $A$ 之中即可。

-----

現在我們試著利用通用雜湊函數族的特性，將額外空間降至 $O(1)$。

考慮通用雜湊函數族 $\mathcal{H}$，其中的函數們 $h: \{-U,\ldots, U\}\to\{0, 1, \ldots, n-1\}$。
根據通用函數族的定義，兩筆鍵值碰撞的機率是

$$
\Pr_{h\in \mathcal{H}}(h(x)=h(y)) \le \frac1m.
$$

上面這個式子告訴我們，如果從通用雜湊函數族隨機挑選一個雜湊函數出來，並將 $n$ 筆鍵值透過 $h$ 映射至 $\{0, 1, \ldots, n-1\}$ 的話，期望的總碰撞對數不超過 ${n\choose 2}/n = (n-1)/2$ 的。利用這點，我們可以從中得到另一個更強的散佈性質：

### 引理（散佈性質）

若一個 $\mathcal{H}:  \{-U,\ldots, U\}\to \{0, 1, \ldots, n-1\}$ 是一個通用雜湊函數族，那麼『$n$ 筆相異鍵值被映射至至少 $0.1n$ 個相異雜湊值』這個事件發生的機率至少為 $9/10$。 

### 證明

令隨機變數 $X$ 為總碰撞次數，從前述觀察我們有 $\mathbb{E}[X]\le(n-1)/2$。
根據馬可夫不等式 (Markov's Inequality)，我們得知
$$
\Pr(X \ge 5.5n) \le \frac{\mathbb{E}[X]}{5.5n} < \frac{1}{10}
$$

但是，當 $n$ 筆相異鍵值被映射至至多 $0.1n$ 個相異雜湊值時，至少會出現 $55\times 0.1n=5.5n$ 次碰撞。根據上式，我們得出這樣的壞事件，出現的機率不超過 $1/10$，換句話說，成功的機率至少有 $9/10$。

-----

上面這個散佈性質的引理有什麼用途呢？對於每一個不同的雜湊值，我們可以只選第一次遇到的鍵值當作比對的對象（並將該鍵值交換至對應的陣列位置）。換句話說，經過一輪雜湊加上比對以後，有九成的機率我們可以排除至少一成的資料。當我們發現沒排除一成的資料的時候，我們可以視為雜湊失敗並重新雜湊。
於是，我們可以在**期望**$O(n)$ 的時間內**保證**排除一成資料。
也就是說，『每一輪』的雜湊比對，能夠花期望 $O(n)$ 的時間進行比對，讓剩餘沒有被比對過的資料數降至 $\le 0.9n$。利用期望值的可加性，這個演算法解決 Two Sum 問題的總期望時間是

$$n + 0.9n + (0.9)^2n + \cdots = O(n).$$



## 備註

不曉得有沒有 $O(n)$ 時間、$O(1)$ 額外空間的確定性演算法？

## 參考資料

* Leetcode 1 - [Two Sum](https://leetcode.com/problems/two-sum/)
* [(Cornell 課程筆記) 為什麼不該假設雜湊函數總是 Uniform 的呢](https://www.cs.cornell.edu/courses/cs312/2008sp/lectures/lec21.html)
* [Chiu CC 的網誌：Hash Table 簡介](http://alrightchiu.github.io/SecondRound/hash-tableintrojian-jie.html)