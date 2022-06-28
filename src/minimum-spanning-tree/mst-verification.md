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
此外，由於每一條不在樹上的邊，都會變成一個樹上路徑最大值的詢問，我們可以預先利用線性 $O(m)$ 時間處理，將所有樹上路徑詢問

### 參考資料

[^1]: János Komlós, [Linear Verification for Spanning Trees](https://www.cs.princeton.edu/courses/archive/fall09/cos521/Handouts/linear.pdf), Combinatorica 1985.

[^2]: Brandon Dixon, Monika Rauch, and Robert E. Tarjan, [Verification and Sensitivity Analysis of Minimum Spanning Trees in Linear Time](https://epubs.siam.org/doi/abs/10.1137/0221070?journalCode=smjcat), SIAM Journal of Computing, 1992.

[^3]: Valerie King, [A Simpler Minimum Spanning Tree Verification Algorithm](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/A%20Simpler%20Minimum%20Spanning.pdf), Algorithmica, 1997. (WADS 1995)

[^4]: Torben Hagerup, [An Even Simpler Linear-Time Algorithm for Verifying Minimum Spanning Trees](https://link.springer.com/chapter/10.1007/978-3-642-11409-0_16), Graph Theoretic Concepts in Computer Science, 2009.

