# 驗證最小生成樹 Minimum Spanning Tree Verification

我們知道給定一個圖，算出最小生成樹可能沒有那麼容易做到線性時間（我們甚至不知道是否能做到線性次數比較）。
如果反過來說，給定一個有權重的圖 $G$ 以及一棵樹 $T$，我們有沒有辦法快速判斷樹 $T$ 是最小生成樹呢？

### 利用 Tree Path Maximum 來解決

這個問題其實可以藉由我們前一篇提及的「樹上路徑最大值問題」來解決：對於每一條不在樹上的邊 $(u, v)$，我們只要詢問 $T$ 上面這條連接 $u$ 和 $v$ 的路徑 $u\leadsto v$ 上頭最重的一條邊，其權重是否大於 $(u, v)$ 這條邊的權重即可。

### 一點小小的歷史

Komlós[^1] 在 1985 年率先證明出來，如果要驗證一棵樹是否為最小生成樹，存在一個演算法在最差情形下「只需要進行 $O(m+n)$ 次兩數值比較」。
但是直到 1992 年，才由 Dixon、Rauch、以及 Tarjan[^2] 把這個想法實作出線性時間的演算法。
不過他們的縮樹演算法太複雜了，得預處理一大堆東西。緊接著 King[^3] 在 1995 年給出了一個稍微簡單一些的驗證最小生成樹演算法。
在若干年後 Hagerup[^4] 化簡了 King 的線性時間演算法，
為了表示其演算法的簡單程度，Hagerup 很自豪地在論文中提供了用 D 語言的程式碼。

我們現在就來看看 Hagerup 演算法到底是怎麼做到線性時間的吧！

## 第一步：Borůvka 樹分治

首先，我們可以利用 King's 轉化，將整棵樹 $T$ 轉化成一棵完滿分叉樹（Full Branching Tree）$B$。
此外，由於每一條不在樹上的邊，都會變成一個樹上路徑最大值的詢問，我們可以預先利用線性 $O(m)$ 時間計算每個詢問兩端點的最小共同祖先 (LCA)，將所有樹上路徑詢問轉換成 $O(m)$ 個『子孫、祖先』之間的路徑最大值詢問。

## 第二步：Komlós 查詢

現在，對於這個完滿分叉樹 $B$ 上面的每一個節點 $v$，我們可以預先知道有哪些詢問 $(u, v)$ 是以 $v$ 作為子孫節點的。
我們令 $Q_v$ 為所有以 $v$ 為子孫節點的詢問 $(u, v)$ 所形成的集合。
令 $A_v$ 為以 $v$ 為根的子樹中，所有節點 $x$ 中，$Q_x$ 內祖先節點 $u$ 所形成的集合。
換句話說
$$
A_v := \bigcup_{x\in T_v} \{u \ |\ (u, x)\in Q_x\}
$$
用白話來講的話，$A_v$ 包含了進入 $v$ 節點以後所有可能詢問到的祖先集合。
注意到這個集合大小至多是 $\log n$ 的，因為 $B$ 是一棵完滿分叉樹。
換句話說，如果我們能夠**預先處理**所有從 $v$ 到 $A_v$ 之間的路徑最大值，
並且將它們存放在一個雜湊陣列 $\mathit{Stack}_v$ 中，
那麼對於每一個 $Q_v$ 內部的詢問，我們都可以花常數時間查看這個陣列並取得答案。


## 第三步：單調堆疊

為什麼我們會將該陣列命名為 $\mathit{Stack}_v$ 呢？
因為它根本是一個單調堆疊 (monotonic stack) 的樣貌：
該陣列中，隨著查詢的祖先節點深度越淺、其答案（路徑最大值）也必定越大。

此外，假設我們從 $v$ 走到其子節點 $v'$，那麼首先我們會有 $A_{v'} \subseteq A_v$。
對於陣列 $\mathit{Stack}_v$ 中的 (祖先、路徑最大值) 組合，一定會從最深的點開始壓起。
因此從 $\mathit{Stack}_v$ 到 $\mathit{Stack}_{v'}$ 的過程，只是拿掉一些陣列中的元素、並且進行一次單調堆疊的插入而已。

但是進行單調堆疊的插入，會花費很多次比較。
Komlós 想到了一個辦法：既然 $\mathit{Stack}_v$ 已經是個隨著深度越深、路徑最大值單調遞減的陣列了，那何不直接用二分搜尋呢？
Komlós 在 1985 年給出了一個超酷的定理，若你只在乎從每個點進行更新堆疊時，二分搜尋所花費的**比較次數**，那麼總比較次數是線性的：

### 定理 MST.18 [Komlós 1985]

若 $B$ 是一個完滿分叉樹，而且對於所有 $v\in B$。令 $m=\sum_{v\in B} |Q_v|$ 且假設 $|Q_v|\ge 1$。那麼
$$
\sum_{v\in B} \log(|A_v|+1) = O(n\log\left( \frac{m+n}{n}\right)) = O(m+n)
$$

### 證明 MST.18 的歸納部分

我們可以由下至上，逐層以數學歸納法證明：令某個固定高度 $h$ 並考慮所有高度為 $h$ 節點為樹根的子樹們叫做 $\mathrm{Trees}(h)$。
由數學歸納法的歸納假設我們可以知道，對於任何 $T_w\in \mathrm{Trees}(h-1)$，令 $m_w = \sum_{x\in T_w}|Q_x|$ 且 $n_w = |T_w|$，那麼有 $\sum_{x\in T_w} \log(|A_x|+1) \le  c_{h-1} n_w \log\left(\frac{m_w+n_w}{n_w}\right)$，其中 $c_{h-1}$ 是某個與 $h$ 有關的參數。
現在對於每一個高度 $h$ 節點為樹根的樹 $T_v\in \mathrm{Trees}(h)$，利用 $\log$ 函數的凹性，依據延森不等式我們有

$$
\begin{aligned}
\sum_{x\in T_v}\log(|A_x|+1) &= \log(|A_v|+1) + \sum_{w: v \textrm{ 的子節點}}\ \ \ \  \sum_{x\in T_w}\log(|A_x|+1) \\
&\le \log(|A_v|+1) + \sum_{w: v \text{ 的子節點}}\ \ \ \  c_{h-1}n_w\log \left(\frac{m_w+n_w}{n_w}\right) \\
&\le \log(m_v+1) + \sum_{w: v \text{ 的子節點}}\ \ \ \  \underbrace{c_{h-1}\log \left(\frac{m_w+n_w}{n_w}\right) + \cdots + c_{h-1}\log \left(\frac{m_w+n_w}{n_w}\right)}_{n_w\text{ 個}}\\
&\le \log(m_v+n_v) + c_{h-1} n_v\log\left(\frac{m_v+n_v}{n_v}\right) \ \ \ (\text{延森不等式})\\
&= \log\left[\left(\frac{m_v+n_v}{n_v}\right)^{c_{h-1}\ n_v}\left(\frac{m_v+n_v}{n_v}\right) n_v\right]\\
&\le \log\left[\left(\frac{m_v+n_v}{n_v}\right)^{c_{h-1}\ n_v+1+\log_2n_v}\right]\ \ \ (\text{利用 } m_v\ge n_v \text{ 所以底數至少是 } 2)
\end{aligned}
$$

重點來啦～由於 $B$ 是一個完滿分叉樹，因此我們知道高度是 $h$ 的樹，其節點數量至少有 $2^h$ 這麼多個。
因此，我們可以隨意估計：存在一個絕對的常數 $\hat{c}\ge 100$，使得對於所有的 $h$，皆有 $1+\log_2 n_v \le \frac{\hat{c}}{h^2}n_v$。
於是我們可以定義 $c_h = \hat{c}(\frac{1}{1^2} + \frac{1}{2^2} + \cdots + \frac{1}{h^2}) = \Theta(1)$，
這麼一來便有 $c_{h-1}n_v + 1 + \log_2 n_v \le c_hn_v$，滿足數學歸納法的要求，所以就得證啦。

### Komlós 演算法

有了以上重要的 Komlós 分析以後，我們便能輕易地得到一個「只需要 $O(m+n)$ 次數值比較」的最小生成樹驗證演算法：

* 第一次 DFS：找出每一個節點之 $A_v$ 集合。
* 第二次 DFS：找出每一個節點之 $\mathit{Stack}_v$ 陣列，並且順手回答所有 $Q_v$ 的詢問。

## 第四步：使用 Bit Tricks 把其他部分變成常數時間操作

看到這邊，對於位元運算等操作熟稔的朋友們，應該已經可以喜孜孜地重現 Hagerup 的論文：將 Komlós 演算法用線性時間內實作出來～
由於 $B$ 是完滿分叉樹，其深度保證是 $O(\log n)$，在 Word RAM 模型底下，我們總是能假設每一個位元組都有 $O(\log n)$ 個位元。
因此每一個 $A_v$ 集合我們可以用常數個 bit mask 來表示，而其他的操作也可以順手用 Bit Tricks / 預處理查表輕鬆搞定。



### 參考資料

* Valerie King 的投影片 [http://www.cs.technion.ac.il/~idddo/mstverif.pdf](http://www.cs.technion.ac.il/~idddo/mstverif.pdf)

[^1]: János Komlós, [Linear Verification for Spanning Trees](https://www.cs.princeton.edu/courses/archive/fall09/cos521/Handouts/linear.pdf), Combinatorica 1985.

[^2]: Brandon Dixon, Monika Rauch, and Robert E. Tarjan, [Verification and Sensitivity Analysis of Minimum Spanning Trees in Linear Time](https://epubs.siam.org/doi/abs/10.1137/0221070?journalCode=smjcat), SIAM Journal of Computing, 1992.

[^3]: Valerie King, [A Simpler Minimum Spanning Tree Verification Algorithm](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/A%20Simpler%20Minimum%20Spanning.pdf), Algorithmica, 1997. (WADS 1995)

[^4]: Torben Hagerup, [An Even Simpler Linear-Time Algorithm for Verifying Minimum Spanning Trees](https://link.springer.com/chapter/10.1007/978-3-642-11409-0_16), Graph Theoretic Concepts in Computer Science, 2009.

