# 最小生成樹的 Borůvka's 演算法

捷克數學家 [Otakar Borůvka](https://en.wikipedia.org/wiki/Otakar_Bor%C5%AFvka) 早在 1926 年就已經提出解決最小生成樹問題的演算法了，但由於以捷克文寫成的，當時又在一次世界大戰，所以他的論文並沒有快速地流通全世界。
相同概念的演算法稍後在 1938 (Choquet, 法國), 1951 (Florek, Łukasiewicz, Perkal, Steinhaus, and Zubrzycki, 法國), 1965 (Sollin, 法國) 年也被多次重新發現並且發表。

## Borůvka's 演算法

Borůvka 觀察到一件非常重要的事情：假設圖 $G$ 是一個連通且邊權重皆相異的圖。對於每一個點連出去的所有邊中，權重最小的邊必定屬於最小生成樹。這個觀察非常重要，顯然它是安全邊定義中的一個特例（集合 $S$ 內恰好只包含一個點）。現在對所有點分別選擇一條連出去權重最小的邊，這些邊是最小生成樹中的子集合。也就是說，如果此時我們把藉由這些邊直接或間接的點，全部縮起來，那麼縮起來的圖上面的最小生成樹，一定就是原本圖 $G$ 上面的最小生成樹，將對應位置的點集合縮起來之後的結果。我們可以把上面這個觀察寫成以下的引理：

### 引理 MST.5

假設圖 $G$ 是一個連通且邊權重皆相異的圖。令 $T=\text{MST}(G)$ 是圖 $G$ 上的最小生成樹。
令 $S\subseteq T$ 是 $T$ 上的一棵子樹，那麼將 $S$ 上的所有點收縮起來得到的圖 $H := G\circ S$，其最小生成樹 $\text{MST}(H) = T\circ S$。

### 引理 MST.5 的證明

首先，我們知道因為 $S$ 是一棵子樹，所以縮起來以後 $T\circ S$ 是一棵樹（連通的、恰好有 $n-|V(S)|+1$ 個點、恰好有 $n-1-|E(S)|$ 條邊）。
其次，$H$ 上的每一條邊權重顯然都不同，且 $H$ 連通。因此 $H$ 裡的安全邊就是最小生成樹上的邊。
考慮任何 $H$ 上的一條安全邊，


## 參考資料

* 維基百科 https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm
* [Princeton cos423 演算法分析課程的講義](https://www.cs.princeton.edu/courses/archive/spring18/cos423/lectures/04GreedyAlgorithmsII-2x2.pdf)
* https://hsm.stackexchange.com/questions/11982/how-did-yao-come-up-with-his-minimum-spanning-tree-algorithm