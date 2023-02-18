## 最大無權匹配演算法 Maximum Cardinality Matching


| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 時間複雜度 | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
| Edmonds 1965[^1] | 一般圖 | 確定性 | $O(mn^2)$ | |
| Witzgall-Zahn 1965[^3] | 一般圖 | 確定性 | $O(mn^2)$ | |
| Balinski 1969[^4] | 一般圖 | 確定性 | $O(n^3)$ | |
| Gabow 1976[^5] | 一般圖 | 確定性 | $O(n^3)$ | |
| Lawler 1976 |  一般圖 | 確定性 | $O(mn)$ | |
| Karzanov 1976 | 一般圖 | 確定性 | $O(mn)$ | | 
| Hopcroft-Karp 1971[^11] | 二分圖 | 確定性 | $O(m\sqrt{n})$ | |
| Dinitz-Karzanov 1973[^13] | 二分圖 | 確定性 | $O(m\sqrt{n})$ | Max Flow |
| Micali-Vazirani 1980 | 一般圖 | 確定性 | $O(m\sqrt{n})$ | Vazirani 2014 |
| Gabow-Tarjan 1991 | 一般圖 | 確定性 | $O(m\sqrt{n})$ | |
| Feder-Motwani 1995[^12] | 二分圖 | 確定性 | $O(m\sqrt{n}/f(n, m))$ | |

* $f(n, m) = \log n / \log (n^2/m)$

## 最大帶權匹配演算法 Maximum Weighted Matching

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 時間複雜度 | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
| Kuan 1955[^7] | 二分圖 | 確定性 | $O(n^3)$ | 匈牙利演算法 |
| Fredman-Tarjan 1984[^8] | 二分圖 | 確定性 | $O(n(m+n\log n))$ | Fibonacci Heaps |
| Gabow 1985[^9] | 二分圖 | 確定性 | $O(n^{3/4}m\log W)$ | Scaling |
| Gabow-Tarjan 1989[^10] | 二分圖 | 確定性 | $O(\sqrt{n}m\log(nW))$ | |
| Kao-Lam-Sung-Ting 1999[^6] | 二分圖 | 確定性 | $O(\sqrt{n}S/f(n, S/W))$ | |

* $S$ 是所有邊權重總和。$W$ 是最大整數邊權。
* $f(n, m) = \log n / \log (n^2/m)$

## 近似最大匹配

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>近似值</nobr> | 時間複雜度 | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
|  |  | 確定性 | $O(m+n\log n)$ | |

## 最大帶權完美匹配 Maximum Weighted Perfect Matching

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>近似值</nobr> | 時間複雜度 | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
|  |  | 確定性 | $O(m+n\log n)$ | |

## 動態近似匹配 Dynamic Approximate Maximum Matching

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>近似值</nobr> | 更新時間 Update Time | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
| Ivković-Lloyd 1994 | 一般圖 | $2$ | 均攤 $O((m+n)^{\sqrt{2}/2})$ | 無權重 |
| Onak-Rubinfield 2010 | 一般圖 | $O(1)$ | 高機率均攤 $O(\log^2 n)$ | 無權重 |
| Gupta-Peng 2012 | 一般圖 | $1-\epsilon$ | $O(\sqrt{m}\epsilon^{-2})$ | 無權重 |
| Gupta-Peng 2012 | 一般圖 | $1/3-\epsilon$ | $O(\sqrt{m}\epsilon^{-3}\log W)$ | 帶權 |
| Gupta-Peng 2012 | 一般圖 | $1-\epsilon$ | $O(\sqrt{m}\epsilon^{-2-O(1/\epsilon)}\log W)$ | 帶權 |
| Berstein-Stein 2016 | 一般圖 | $2/3-\epsilon$ | $O(m^{1/4}\epsilon^{-2.5})$ | 帶權 |

* Gupta and Peng 2012. [https://arxiv.org/pdf/1304.0378.pdf](https://arxiv.org/pdf/1304.0378.pdf)
* Berstein and Stein SODA 2016. [https://aaronbernstein.cs.rutgers.edu/wp-content/uploads/sites/43/2018/12/SODA_2016.pdf](https://aaronbernstein.cs.rutgers.edu/wp-content/uploads/sites/43/2018/12/SODA_2016.pdf)
* Behnezhad and Khanna SODA 2022. [https://arxiv.org/pdf/2201.02905v1.pdf](https://arxiv.org/pdf/2201.02905v1.pdf)
* Zoran Ivković & Errol L. Lloyd. [https://link.springer.com/chapter/10.1007/3-540-57899-4_44](https://link.springer.com/chapter/10.1007/3-540-57899-4_44)
* Onak and Rubinfield, STOC 2010. [Maintaining a Large Matching and a Small Vertex Cover](https://onak.pl/papers/stoc_2010-maintaining_large_matching.html)


## 參考資料

* Ran Duan and Seth Pettie, [Linear-Time Approximation for Maximum Weight Matching](https://web.eecs.umich.edu/~pettie/papers/ApproxMWM-JACM.pdf), JACM 2014.

[^1]: Jack Edmonds, [Path, Trees, and Flowers](https://math.nist.gov/~JBernal/p_t_f.pdf), Canadian Journal of Mathematics, 1965.

[^2]: Jack Edmonds, [Maximum Matching and a Polyhedron With 0,1-Vertices](https://nvlpubs.nist.gov/nistpubs/jres/69B/jresv69Bn1-2p125_A1b.pdf), Journal of Research of the National Bureau of Standards, Section B: Mathematics and Mathematical Physics, 1965.

[^3]: C. Witzgall and C. T. Zahn Jr, [Modification of Edmonds' Maximum Matching Algorithm](https://nvlpubs.nist.gov/nistpubs/jres/69B/jresv69Bn1-2p91_A1b.pdf), Journal of Research of the National Bureau of Standards, Section B: Mathematics and Mathematical Physics, 1965.

[^4]: Balinski, M.L. (1969) Labelling to Obtain a Maximum Matching, in Combinatorial Mathematics and Its Applications. In: Bose, R.C. and Dowling, T.A., Eds., University of North Carolina Press, Chapel Hill, 585-602.

[^5]: Harold N. Gabow, [An Efficient Implementation of Edmonds' Algorithm for Maximum Matching on Graphs](https://web.eecs.umich.edu/~pettie/matching/Gabow-general-matching-1976.pdf). (also in [Gabow's 1974 PhD Thesis](https://books.google.com/books/about/Implementation_of_Algorithms_for_Maximum.html?id=x9A-AAAAIAAJ))

[^9]: H. N. Gabow, Scaling algorithms for network problems, Journal of Computer and System
Sciences, 31 (1985), pp. 148–168.

[^6]: Ming-Yang Kao, Tak Wah Lam, Wing-Kin Sung, and Hing-Fung Ting.
[A Decomposition Theorem for Maximum Weight Bipartite Matchings](https://arxiv.org/pdf/cs/0011015.pdf). J, ACM 2001 and ESA 1999.

[^7]: H. W. Kuan. The Hungarian method for the assignment problem, Naval Research Logistics
Quarterly, 2 (1955), pp. 83–97.

[^8]: M. L. Fredman and R. E. Tarjan. Fibonacci heaps and their uses in improved network
optimization algorithms, Journal of the ACM, 34 (1987), pp. 596–615. FOCS 1984

[^10]: H. N. Gabow and R. E. Tarjan, Faster scaling algorithms for network problems, SIAM
Journal on Computing, 18 (1989), pp. 1013–1036. (also STOC 1988)

[^11]: J. E. Hopcroft and R. M. Karp, An $n^{5/2}$ algorithm for maximum matching in bipartite
graphs, SIAM Journal on Computing, 2 (1973), pp. 225–231

[^12]: T. Feder and R. Motwani, Clique partitions, graph compression and speeding-up algorithms,
Journal of Computer and System Sciences, 51 (1995), pp. 261–272

[^13]: Shimon Even, [The Max Flow Algorithm of Dinic and Karzanov: An Exposition](http://publications.csail.mit.edu/lcs/pubs/pdf/MIT-LCS-TM-080.pdf), 1976.