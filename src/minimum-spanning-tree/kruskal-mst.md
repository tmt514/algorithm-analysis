# 最小生成樹的 Kruskal's 演算法

Kruskal's 演算法步驟如下：

1. 將所有 $E$ 中的邊依照長度由小至大排序。令排序後的邊為 $e_1, e_2, \ldots, e_m$。
2. 初始化 $E'=\emptyset$ 為欲輸出的最小生成樹的邊所成的集合。
3. 依序考慮 $i=1, 2, \ldots, m$：
    * 若 $E'\cup \{e_i\}$ 不包含任何圈（也就是說 $e_i$ 連接了 $(V, E')$ 中兩個不同的連通元件），那麼就將 $e_i$ 加入 $E'$ 中。


## 定理 MST.4

若輸入之圖 $G$ 為連通，且所有邊權重皆不相等，那麼執行完 Kruskal's 演算法後，$E'=E_{\textit{safe}}$ 包含圖 $G$ 上所有的安全邊。

### 定理 MST.4 的證明

對於每一條被加入 $E'$ 的邊 $e_i$。考慮當 $e_i$ 加入 $E'$ 的時候的圖 $(V, E')$。假設 $e_i=(u, v)$，定義此時包含 $u$ 之連通元件對應的點集合為 $S$。我們宣稱 $w(e_i) = \min_{e\in \partial S} w(e)$。

## 參考資料

* Joseph Kruskal, [_On The Shortest Spanning Subtree of a Graph and the Traveling Salesman Problem_](https://www.ams.org/journals/proc/1956-007-01/S0002-9939-1956-0078686-7/S0002-9939-1956-0078686-7.pdf), AMS 1956.