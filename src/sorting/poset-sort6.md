# 偏序集排序（六）

使用兩兩元素進行比較的排序演算法，不外乎就是採用「插入」或「合併」兩種策略。給定一個偏序集 $(P, <)$，如同合併插入排序法一般，如果我們找到正確的插入順序，就可以得到一個只需要 $O(\log n \cdot \log e(P))$ 次比較的偏序集排序方法囉！

## 找出最長可比鏈

在偏序集當中，一條鏈（chain）是指一個序列 $x_1, x_2, \ldots, x_\ell \in P$，而且他們形成一個全序關係：$x_1 < x_2 < \cdots < x_\ell$。我們可以利用動態規劃方法在 $O(n^2)$ 的時間（或關於偏序集偏序關係總數之線性時間）內找出偏序集 $P$ 中的最長鏈。

現在，我們將證明以下引理：

### 引理 27

令 $\ell$ 為偏序集 $(P, <)$ 裡面的最長鏈的長度。那麼有 $n-\ell \le \log e(P)$。

### 證明

我們預計要證明的，其實是以下的式子：

$$
e(P) \ge 2^{n-\ell} \label{eq1}\tag{*}
$$

換句話說，在最長鏈長度為 $\ell$ 的條件下，我們想要證明任意偏序集裡面至少存在 $2^{n-\ell}$ 個線性延伸。
要怎麼下手呢？我們其實也沒有太多招可以使用。一個簡單的方法便是使用數學歸納法。
這裡我們使用的數學歸納法，比較不太一樣：在固定總資料筆數 $n$ 的情形下，我們要讓 $\ell$ 的值從大到小進行歸納。

當 $\ell = n$ 的時候，所有的資料都被排序完成了，此時 $e(P) = 1 = 2^{0} = 2^{n-\ell}$，滿足條件。

現在 $\ell < n$。根據歸納假設，對於任何偏序集 $P'$，只要它的最長鏈的長度是 $\ell+1$，那麼$\eqref{eq1}$ 式成立。
考慮一個最長鏈長度恰好為 $\ell$ 的偏序集 $P$，以及上面任何一條最長鏈 $A$。
首先，因為 $\ell < n$，因此對於任何鏈以外 $P\setminus A$ 的資料 $x$，都至少存在 $A$ 中某筆資料無法與其比較。
我們可以將 $A$ 中的資料由小到大排列出來：
$$
a_1 < a_2 < \cdots < a_\ell
$$

因為 $P\setminus A\neq \emptyset$，存在一個**最小的註標** $i$，使得存在 $P\setminus A$ 中的某筆資料 $x$，與 $a_i$ 不分軒輊。這件事情蘊含了 $a_{i-1} < x$。
我們如果拿 $x$ 和 $a_i$ 互相比較，根據比較結果，可能產生兩種情形：

$$
A_1: a_1 < \cdots < a_{i-1} < {\color{red}{x< a_i}}  < a_{i+1} < \cdots < a_\ell
$$

以及 

$$
A_2: a_1 < \cdots < a_{i-1} < {\color{red}{a_i < x < a_{i+1}}} < \cdots < a_\ell
$$

都是滿足偏序集 $P$ 的偏序條件。令前者定義出來的新的偏序集為 $P_1$、後者為 $P_2$。
由於 $x$ 是 $P\setminus A$ 中的極小元素（對於所有 $y\in P\setminus A$、$y\neq x$，要嘛 $x < y$ 要嘛 $x$ 和 $y$ 不可比），不難推得 $e(P_1) \ge e(P_2)$，而且 $e(P) \ge e(P_1) + e(P_2) \ge 2e(P_2)$。
現在，如果我們能證明 $A_2$ 是 $P_2$ 上面的一條最長鏈，由於它的長度為 $\ell+1$，套用歸納假設，我們可以知道 $e(P)$ $\ge 2e(P_2)$ $\ge 2\cdot 2^{n-\ell-1}$ $= 2^{n-\ell}$，故 $\eqref{eq1}$ 對 $\ell$ 成立。

顯然 $A_2$ 是 $P_2$ 上面的一條最長鏈。為什麼呢？我們可以利用反正法證明之：反正一定會對。不是啦，我們可以利用反證法證明：假設存在一條更長的鏈 $A'$，其長度 $|A'|  \ge \ell + 2$。
首先，這條鏈 $A'$ 一定會包含 $x$，如果不會的話，那整條鏈早已出現在 $P$ 中，與假設矛盾。

我們定義 $I'_{< x}$ 為在 $P'$ 裡面以 $x$ 為最大元素的最長鏈。
類似地我們定義 $I'_{> x}$ 為在 $P'$ 裡面以 $x$ 為最小元素的最長鏈。
考慮 $I'_{< x}$ 裡頭到達 $x$ 之前的那個元素，它可以是 $a_i$、也可以是其他元素。
如果是 $a_i$ 接在前面的話顯然有 $|I'_{< x}| \le i+1$。如果是其他元素 $y$ 接在前面的話，這個 $y < x$ 關係顯然被包含在 $P$ 之中、或是透過 $y < a_i {\color{red}{< }}\ x$ 達成的，如果早已在 $P$ 中，根據假設它只能是 $a_1, \ldots, a_{i-1}$ 其中一者，此時 $|I'_{< x}| \le i$。
若是透過 $a_i$ 達成的，那麼把 $a_i$ 接上去會更長。
於是得到結論 $|I'_{< x}| \le i+1$。

類似地，考慮 $I'_{> x}$ 裡頭緊接在 $x$ 之後的那個元素，它可以是 $a_{i+1}$、或是其他元素 $y'$，無論是何種情形都可以得到 $|I'_{> x}| \le \ell-i+1$。於是有 
$$\ell+2 \le |A'| = |I'_{< x}| + |I'_{> x}| - 1 \le (i+1) + (\ell-i+1)-1 = \ell+1$$
矛盾。


<!-- 首先，這條鏈 $A'$ 一定會同時包含 $a_i$ 和 $x$ 這兩筆資料。
這是因為 $a_i < x$ 這個偏序關係是 $P$ 與 $P_2$ 唯一的差別。
如果 $A'$ 少了任何一者，其整條鏈的偏序關係全部都會出現在原先的偏序集 $P$ 中，因此與 $A$ 為最長鏈之假設矛盾。 -->

<!-- 接著，我們可以注意到在 $a_i$ 之前，$a_1, \ldots, a_{i-1}$ 一定是最長的，否則可以換得更長。
然後呢，由於 $x$ 是 $P\setminus A$ 之中的極小資料，因此 $a_i$ 與 $x$ 之間不可能插入任何資料（備註：這邊用到了 $i$ 的最小性質）。 -->

<!-- 接下來，考慮在 $P_2$ 裡面，以 $x$ 為首的最長鏈 $A_x$。這條鏈一定也在 $P$ 中，而且其長度會等於 $\vert A'\vert  - i \ge (\ell+2)-i$。注意到 $x > a_{i-1}$。我們考慮把 $a_1, \ldots, a_{i-1}$ 直接連接在 $A_x$ 之前，此時這條新的鏈完完全全地出現在原先的偏序集裡頭，但它的長度是多少呢？它的長度是 $(\ell+2)-i + (i-1) = \ell+1$，與 $A$ 的最長鏈長度為 $\ell$ 互相矛盾啊。 -->

因此，不存在更長的鏈，於是原命題根據數學歸納法得證啦。

-----

我們從引理 27，得出一個 $O(\log n\cdot \log e(P))$ 次比較的偏序集排序演算法[^1]：

> * 第一步：找出最長鏈 $A$。
> * 第二步：對於剩下的所有資料，依序以二分法插入 $A$ 中。

由於剩下的資料筆數至多為 $\log e(P)$ 個，因此每一筆至多以 $\log n$ 次比較就可以插入最長鏈中，整體比較次數是 $O(\log n\cdot \log e(P))$ 次。整體計算時間為 $O(n^2)$（或偏序集大小）。

-----

如果朋友們有餘力看到這邊，先容我致上深深的感謝。
相信大家看到這邊，應該會說：前一篇文章裡面提到的凸函數最佳化上哪去了？
這東西會有用的。

<!-- 比方說：
假設最長鏈的長度為 $\ell$。那麼令所有變數 $z_i = 1/\ell$ 的時候，保證滿足直鏈和多項式的要求（因為任何的鏈長都不超過 $\ell$，所以鏈上的變數加總起來都不會超過 $1$。）因此，將這個 $z=(z_1, z_2, \ldots, z_n)$ 代入直鏈和多項式的最佳化問題中，我們可以得出 $H(P) \le \log \ell$，即 $-nH(P) \ge -n\log \ell$。 -->

我們明天將證明一個比引理 26 更強的定理：

$$
4\log e(P) + nH(P) \ge n\log n
$$

(在增加左手邊的係數變成 $4$ 以後，不等式的右手邊就可以從 $\log n!$ 變成 $\log n^n$ 了。事實上這個係數可以是 $2$，不過證明比較複雜，所以我只會介紹係數等於 $4$ 的版本。）
事實上，有了這個更強的定理以後，其實才能無痛證明引理 27 的 big-O 版本，昨天的引理 26 是不夠的。


[^1]: 演算法是 Cardinal, Fiorini, Joret, Jungers, 和 Munro 等人提出的[^2]，但這個證明是我自己想的。如果各位朋友們有發現參考資料或<font color=red>任何錯誤</font>的話拜託跟我說 (×﹏×)

[^2]: Jean Cardinal, Samuel Fiorini, Gwenaël Joret, Raphaël M. Jungers, J. Ian Munro, _Sorting under Partial Information (without the Ellipsoid Algorithm)_, Combinatorica 33, 655–697 (2013). https://doi.org/10.1007/s00493-013-2821-5, [ArXiv](https://arxiv.org/pdf/0911.0086.pdf).


<!-- 
首先我們先將引理 26 寫出來：
$$
\log e(P) + nH(P) \ge \log n!
$$

然後利用 [Stirling's Approximation](https://en.wikipedia.org/wiki/Stirling%27s_approximation)，把 $\log n!$ 展開成
$$
\begin{aligned}
\log n! &= n\log n - n \log e + O(\log n)\\
&\ge n\log n - n\log e
\end{aligned}
$$

因此，我們可以寫
$$
\begin{aligned}
\log e(P) &\ge \log n! - n\log \ell\\
&\ge n\log n - n\log e - n\log \ell\\
&\ge n\log \frac{n}{e\ell}
\end{aligned}
$$ -->