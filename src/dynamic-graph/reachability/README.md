# 有向圖的連通問題 Reachability

有向圖版本的動態資料結構，需要支援的操作有：

* 更新類型的操作：
  - insert($u, v$): 新增一條從 $u$ 連到 $v$ 的邊。
  - delete($u, v$): 移除一條已存在的 $(u, v)$ 邊。
* 查詢類型的操作：
  - reachable($u, v$): 詢問在當前的圖中是否 $u$ 走得到 $v$。

## Fully Dynamic Reachability

### 均攤更新時間

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 均攤更新時間<br>Amortized<br>Update Time | 最差查詢時間 |
|:---------:|:--------:|:--------:|:-----------:|:-----------:|
| Demetrescu-Italiano [^7] | general | 確定性 | $O(n^2)$ | $O(1)$ |
| Henzinger-King[^9] | general | 蒙地卡羅 | $O(m\sqrt{n}\log^2n)$ | $O(n/\log n)$ |
| Roditty-Zwick [^1] | general | 確定性 | $O(m\sqrt{n})$ | $O(\sqrt{n})$ |
| Roditty-Zwick [^1] | general | 蒙地卡羅 | $O(m^{0.58}n)$ | $O(m^{0.43})$ | 
| Demetrescu-Italiano [^8] | DAGs | 蒙地卡羅 | $O(n^{1.58})$ | $O(n^{0.58})$ |
| Roditty-Zwick [^2] | general | 確定性 | $O(m + n\log n)$ | $O(n)$ |

### 最差更新時間

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 最差更新時間<br>Worst Case<br>Update Time | 最差查詢時間 |
|:---------:|:--------:|:--------:|:-----------:|:-----------:|
| Sankowski[^3] | general | 蒙地卡羅 | $O(n^2)$ | $O(1)$ |
| Sankowski[^3] | general | 蒙地卡羅 | $O(n^{1.58})$ | $O(n^{0.58})$ | 
| Sankowski[^3] | general | 蒙地卡羅 | $O(n^{1.447})$[^4] | $O(n^{1.447})$[^4] |
| van den Brand,<br>Nanongkai,<br>Saranurak [^4] | general | 蒙地卡羅 | $O(n^{1.407})$ | $O(n^{1.407})$ |

## Incremental Reachability

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 更新時間 | 最差查詢時間 |
|:---------:|:--------:|:--------:|:-----------:|:-----------:|
| Italiano[^5] | general | 確定性 | 均攤 $O(n)$ | $O(n)$ |

## Decremental Reachability

| 演算法文獻 | <nobr>圖的種類</nobr> | <nobr>演算法類型</nobr> | 更新時間 | 最差查詢時間 |
|:---------:|:--------:|:--------:|:-----------:|:-----------:|
| Roditty-Zwick [^1] | general | 拉斯維加斯 | 全部 $O(mn)$ | $O(1)$ | 
| Łącki[^10] | general | 確定性 | 全部 $O(mn)$ | $O(1)$ |

## 參考資料

[^1]: Roditty and Zwick, [Improved Dynamic Reachability Algorithms for Directed Graphs](https://doi.org/10.1137/060650271). SIAM J. Comput 2008.

[^2]: Roditty and Zwick, [A Fully Dynamic Reachability Algorithm for Directed Graphs with an Almost Linear Update Time](https://doi.org/10.1137/13093618X). SIAM J. Comput 2016.

[^3]: Sankowski, [Dynamic transitive closure via dynamic matrix inverse](https://ieeexplore.ieee.org/document/1366271). FOCS 2004.

[^4]: van den Brand, Nanongkai, and Saranurak. [Dynamic Matrix Inverse: Improved Algorithms and Matching Conditional Lower Bounds](https://arxiv.org/abs/1905.05067). FOCS 2019.

[^5]: G.F.Italiano, [Amortized Efficiency of a Path Retrieval Data Structure](https://dl.acm.org/doi/10.5555/39515.39523). TCS 1986. 

[^6]: Liam Roditty, [A Faster and Simpler Fully Dynamic Transitive Closure](https://dl.acm.org/doi/10.1145/1328911.1328917). SODA 2003. TALG 2008.

[^7]: C. Demetrescu and G.F. Italiano, [Fully Dynamic Transitive Closure: Breaking Through the $O(n^2)$ Barrier](https://ieeexplore.ieee.org/document/892126?section=abstract). FOCS 2000.

[^8]: C. Demetrescu and G.F. Italinao, [Trade-offs for Fully Dynamic Transitive Closure on DAGs: Breaking Through the $O(n^2)$ Barrier](https://core.ac.uk/download/pdf/194937906.pdf). J ACM 2005.

[^9]: M.R. Henzinger and V. King, [Fully Dynamic Biconnectivity and Transtive Closure](https://www.computer.org/csdl/proceedings-article/focs/1995/71830664/12OmNrJAe8t). FOCS 1995.

[^10]: J Łącki, [Improved Deterministic Algorithms for Decremental Transitive Closure](https://dl.acm.org/doi/10.1145/2483699.2483707). SODA 2011. TALG 2013.