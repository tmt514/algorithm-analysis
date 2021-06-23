# 最小生成樹的 Borůvka's 演算法

捷克數學家 [Otakar Borůvka](https://en.wikipedia.org/wiki/Otakar_Bor%C5%AFvka) 早在 1926 年就已經提出解決最小生成樹問題的演算法了，但由於以捷克文寫成的，當時又在一次世界大戰，所以他的論文並沒有快速地流通全世界。
相同概念的演算法稍後在 1938 (Choquet, 法國), 1951 (Florek, Łukasiewicz, Perkal, Steinhaus, and Zubrzycki, 法國), 1965 (Sollin, 法國) 年也被多次重新發現並且發表。

## Borůvka's 演算法

Borůvka 觀察到一件非常重要的事情：假設圖 $G$ 是一個連通且邊權重皆相異的圖。對於每一個點連出去的所有邊中，權重最小的邊必定屬於最小生成樹。這個觀察非常重要，顯然它是安全邊定義中的一個特例（集合 $S$ 內恰好只包含一個點）。現在對所有點分別選擇一條連出去權重最小的邊，這些邊是最小生成樹中的子集合。也就是說，如果此時我們把藉由這些邊直接或間接的點，全部縮起來，那麼縮起來的圖上面的最小生成樹，一定就是原本圖 $G$ 上面的最小生成樹，將對應位置的點集合縮起來之後的結果。我們可以把上面這個觀察寫成以下的引理：

### 引理 MST.5

假設圖 $G$ 是一個連通且邊權重皆相異的圖。令 $T=\text{MST}(G)$ 是圖 $G$ 上的最小生成樹。
令 $S\subseteq T$ 是 $T$ 上的一棵子樹，那麼將 $S$ 上的所有點收縮起來得到的圖 $H := G\circ S$，其最小生成樹 $\text{MST}(H) = T\circ S$。

### 引理 MST.5 的證明

首先，我們知道因為 $S$ 是一棵子樹，所以縮起來以後 $T\circ S$ 是一棵樹（連通的、恰好有 $n-|V(S)|+1$ 個點、恰好有 $n-1-|E(S)|$ 條邊）。不妨以 $v_S$ 代表將 $S$ 所有節點縮起來以後的點。
其次，$H$ 上的每一條邊權重顯然都不同，且 $H$ 連通。因此我們只要證明 $H$ 裡的安全邊恰好是 $T\circ S$ 的所有邊就行了。
考慮任何 $H$ 上的一條安全邊 $e_H$，其對應在圖 $G$ 上的邊為 $e_G$。

$e_H$ 這條安全邊對應到的集合 $X\subseteq V(H)$ 如果包含了 $v_S$，那麼 $e_G$ 也會是 $X\setminus\{v_S\}\cup S \subseteq V(G)$ 往外連的邊中權重最小的。如果 $v_S\notin X$，那麼 $e_G$ 也會是 $X\subseteq V(G)$ 外連邊中權重最小的。因此我們有 $\text{MST}(H)\subseteq T\circ S$。由於邊數相同，因此 $\text{MST}(H)=T\circ S$，得證。

------

如果我們反覆重複「找外連的最小邊」、「把連在一起的子樹縮起來」這兩件事情，當所有點都連起來的時候，我們就得到最小生成樹啦！

Borůvka 演算法步驟如下：

1. 初始化 $E'=\emptyset$ 為欲輸出的最小生成樹的邊所形成的集合。
2. 重複以下動作直到 $G$ 剩下一個點：
    * 對每一個 $V(G)$ 中的點選擇連出去權重最小的邊，將這些邊的原始參照加入 $E'$ 中。
    * 這些邊會形成森林 $F$，找出這個森林的連通元件 $S_1, S_2, \ldots, S_k$，並且對每一個點 $v$ 找出其對應的連通元件編號 $\sigma(v)$。
    * （建立縮點後的圖）建立新的圖 $G^*=(V^*, E^*)$，其中 $V^*=\{1, 2, \ldots, k\}$，對於 $(u, v)\in E$，如果 $\sigma(u)\neq \sigma(v)$，我們就把一條相同權重的 $(\sigma(u), \sigma(v))$ 邊加入 $E^*$ 裡面，並且保留圖 $G$ 中的原始參照。
    * 把 $G$ 換成 $G^*$。

## Borůvka 演算法的實作

實作的部分相對於 Prim's 或 Kruskal's 演算法來說就直接了些。找出連通元件的部分可以利用 BFS 或 DFS 在 $O(m+n)$ 的線性時間做到，而製作新的圖所需的時間也是線性的。

## Borůvka 演算法的分析

### 正確性的證明：引理 MST.6

輸出之 $E'$ 包含所有 $G$ 上最小生成樹的邊。

### 引理 MST.6 的證明

假設步驟 2 每一次執行時對應的圖為 $G_0=G, G_1, G_2, \ldots, G_t$。每次執行時演算法都會將 $G_i$ 內的某些安全邊加入 $E'$ 中，而根據引理 MST.5，這些邊都是 $G_{i-1}, G_{i-2}, \ldots, G_0$ 上的安全邊，因此 $E'$ 內的所有邊都是輸入的圖 $G$ 中的安全邊。
此外，我們可以透過觀察得知，針對 $G_i$ 執行步驟 2 之後，對於新的圖 $|E'| + V(G_{i+1})$ 恆等於 $n$。因此當演算法停止時，我們得到 $|E'|=n-1$，因此 $E'$ 包含了所有圖 $G$ 上的安全邊，根據定理 MST.1，$E'$ 包含了最小生成樹上的所有邊。
<span style="float:right">$\square$</span>

### 時間複雜度：引理 MST.7

對於任何 $i$，$|V(G_{i+1})| \le  |V(G_{i})| / 2$。

### 引理 MST.7 的證明

考慮步驟 2 形成的森林 $F$。在這個森林的 $k$ 個連通元件中，每一個連通元件至少包含兩個點，因此必定有 $|V(G_i)| \ge 2k$，即 $|V(G_{i+1})|=k \le |V(G_i)|/2$。
<span style="float:right">$\square$</span>

由引理 MST.7 不難發現步驟 2 至多只會執行 $O(\log n)$ 次，因此 Borůvka 演算法執行總時間為 $O(m\log n)$。


## 參考資料

* 維基百科 https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm
* [Princeton cos423 演算法分析課程的講義](https://www.cs.princeton.edu/courses/archive/spring18/cos423/lectures/04GreedyAlgorithmsII-2x2.pdf)
* https://hsm.stackexchange.com/questions/11982/how-did-yao-come-up-with-his-minimum-spanning-tree-algorithm