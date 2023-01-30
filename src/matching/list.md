## 最大無權匹配演算法 Maximum Cardinality Matching


| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 時間複雜度 | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
| Edmonds 1965[^1] | 一般圖 | 確定性 | $O(mn^2)$ | |
| Witzgall-Zahn 1965[^3] | 一般圖 | 確定性 | $O(mn^2)$ | |
| Balinski 1969[^4] | 一般圖 | 確定性 | $O(n^3)$ | |
| Gabow 1976[^5] | 一般圖 | 確定性 | $O(n^3)$ | |
| Lawler 1976 |  一般圖 | 確定性 | $O(mn)$ | |
| Karzanov 1976 | 一般圖 | 確定性 | $O(mn)$ | | 


## 最大帶權匹配演算法 Maximum Weighted Matching

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 時間複雜度 | 備註 |
|:---------:|:--------:|:--------:|:-----------:|:-----:|
|  |  | 確定性 | $O(m+n\log n)$ | |



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

