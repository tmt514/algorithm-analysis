# 最小生成樹演算法


| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 時間複雜度 | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
| Dijkstra-Jarník-Prim |  | 確定性 | $O(m+n\log n)$ | |
| Kruskal |  | 確定性 | $O(m\log n)$ | 排序後 $O(m\alpha(n))$ |
| Borůvka |  | 確定性 | $O(m\log n)$ | |
| Borůvka-Prim |  | 確定性 | $O(m\log\log n)$ | |
| Yao[^1] |  | 確定性 | $O(m\log\log n)$ | |
| Tarjan[^2] |  | 確定性 | $O(m\log\log n)$ | |
| Fredman-Tarjan[^3] | | 確定性 | $O(m\log^* n)$ | Fibonacci Heaps 問世 |
| Gabow-Galil-Spencer-Tarjan[^4] | | 確定性 | $O(m\log\log^* n)$ | |
| Fredman-Willard | 整數權重 | 確定性 | $O(m)$ | |
| Karger-Klein-Tarjan[^5] | | 期望時間 | $O(m)$ | |
| Chazelle[^6] | | 確定性 | $O(m\alpha(n))$ | |
| Pettie-Ramachandran[^7] | | 確定性 | 決策樹最佳的 | |


### 驗證最小生成樹

* Tarjan 1979. $O(m\alpha(m, n))$ [Applications of path compressions on balanced trees](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/applications%20of%20path%20compression.pdf)
* Komlós 1985. 給出了只需要 $O(m)$ 次邊權比較的演算法  [Linear Verification for Spanning Trees](https://www.cs.princeton.edu/courses/archive/fall09/cos521/Handouts/linear.pdf), Combinatorica 1985.
* Dixon-Rauch-Tarjan 1992. 利用查表實作 Komlós 演算法得到 $O(m)$ [Verification and Sensitivity Analysis of Minimum Spanning Trees in Linear Time.](https://epubs.siam.org/doi/abs/10.1137/0221070?journalCode=smjcat)
* King 1995. 簡化了查表、給出有趣的樹分治結構 $O(m)$ [A Simpler Minimum Spanning Tree Verification Algorithm](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/A%20Simpler%20Minimum%20Spanning.pdf), Algorithmica, 1997.
* Hagerup 2009. 簡化了 King 的演算法當中對輕重邊的編碼部分 $O(m)$ [An Even Simpler Linear-Time Algorithm for Verifying Minimum Spanning Trees](https://link.springer.com/chapter/10.1007/978-3-642-11409-0_16), Graph Theoretic Concepts in Computer Science, 2009.

### 近似最小生成樹

* Chazelle-Rubinfeld-Trevisan 2005. [Approximating the Minimum Spanning Tree Weight in Sublinear Time](https://epubs.siam.org/doi/10.1137/S0097539702403244)

## 參考資料

* https://www.cs.cmu.edu/~anupamg/advalgos17/scribes/lec01.pdf
* [CMU Advanced Algorithms Fall 2020 課程講義，第一章](http://www.cs.cmu.edu/~15850/notes/cmu850-f20.pdf)
* Gregory Bint, [Minimum Spanning Tree Verification](http://people.scs.carleton.ca/~maheshwa/courses/5703COMP/Notes/MST/comp5703mstv.pdf), Lecture Notes, 2013.

[^1]: Andrew Chi-chih Yao, [An $O(|E|\log\log |V|)$ algorithm for finding minimum spanning trees](https://www.sciencedirect.com/science/article/abs/pii/0020019075900563), Information Processing Letters, 1975.

[^2]: Robert Endre Tarjan, [Finding Minimum Spanning Trees](http://www2.eecs.berkeley.edu/Pubs/TechRpts/1975/ERL-m-501.pdf), Technical Report, 1975.

[^3]: Michael L. Fredman and Robert Endre Tarjan, [Fibonacci heaps and their uses in improved network optimization algorithms](https://dl.acm.org/doi/10.1145/28869.28874), JACM, 1987.

[^4]: H. N. Gabow, Z. Galil, T. Spencer, and  R. E. Tarjan, [Efficient algorithms for finding minimum spanning trees in undirected and directed graphs](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/efficient%20algorithm%20for%20funding.pdf), Combinatorica, 1986.

[^5]: David R. Karger, Philip N. Klein, and Robert E. Tarjan, [A randomized linear-time algorithm to find minimum spanning trees](http://cs.brown.edu/research/pubs/pdfs/1995/Karger-1995-RLT.pdf), JACM, 1995.

[^6]: Bernard Chazelle, [A Minimum Spanning Tree Algorithm with Inverse-Ackermann Type Complexity](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/Minimum%20Spanning%20Tree-Inverse.pdf), JACM, 2000.

[^7]: Seth Pettie and Vijaya Ramachandran, [An optimal minimum spanning tree algorithm](https://dl.acm.org/doi/abs/10.1145/505241.505243), JACM 2002.

[^8]: Tianqi Yang, [Tree Path Minimum Query Oracle via Boruvka Trees](https://arxiv.org/pdf/2105.01864.pdf), ArXiv 2021.

### 直接應用的文章

* MST on Minor-Closed Graphs 是線性時間：https://www.emis.de/journals/AM/04-3/am1139.pdf
(可以理解，因為 Minor-Closed Graphs 是稀疏圖，永遠有 $m=O(n)$。)
* MST on High Girth 是線性時間：https://www.cs.utexas.edu/~danama/papers/mst/high-girth.pdf (居然沒有發表過...，這篇傳達的概念是說，從 graph girth 去解決 MST 可能是希望渺茫的：如果有常數腰圍的線性時間演算法，就能有真正的線性時間演算法。)