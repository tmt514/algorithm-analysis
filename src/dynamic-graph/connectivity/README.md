# 無向圖的連通問題 Connectivity

## 型態一：基本詢問

* 更新類型操作：
  - Insert(u, v): 插入一條 $(u, v)$ 邊。
  - Delete(u, v): 刪除一條 $(u, v)$ 邊。
* 查詢類型操作：
  - Query(u, v): 詢問 $u$ 與 $v$ 之間是否為 $k$-點連通 或 $k$-邊連通的。

| 演算法文獻 | <nobr>$k$</nobr> | <nobr>更新方式</nobr> | <nobr>演算法類型</nobr> | 更新 | 查詢 |
|:---------:|:--------:|:-------:|:--------:|:-----------:|:-----------:|
| Eppstein, Galil, Italiano, and Nissenzweig[^1] | <nobr>$1$-連通</nobr> | Fully | 確定性 | 最差 $O(\sqrt{n})$ | |


## 型態二：整體詢問

* 更新類型操作：
  - Insert(u, v): 插入一條 $(u, v)$ 邊。
  - Delete(u, v): 刪除一條 $(u, v)$ 邊。
* 查詢類型操作：
  - Query(): 詢問圖 $G$ 是否為 $k$-點連通 或 $k$-邊連通的。


| 演算法文獻 | <nobr>$k$</nobr> | <nobr>更新方式</nobr> | <nobr>演算法類型</nobr> | 更新 | 查詢 |
|:---------:|:--------:|:-------:|:--------:|:-----------:|:-----------:|
| Eppstein et al[^1] | <nobr>$2$-點連通</nobr> | Fully | 確定性 | 最差 $O(n)$ | |
| Eppstein et al[^1] | <nobr>$3$-點連通</nobr> | Fully | 確定性 | 最差 $O(n)$ | |
| Eppstein et al[^1] | <nobr>$4$-點連通</nobr> | Fully | 確定性 | 最差 $O(n\alpha(n))$ | |
| Eppstein et al[^1] | <nobr>$2$-邊連通</nobr> | Fully | 確定性 | 最差 $O(\sqrt{n})$ | |
| Eppstein et al[^1] | <nobr>$3$-邊連通</nobr> | Fully | 確定性 | 最差 $O(n^{2/3})$ | |
| Eppstein et al[^1] | <nobr>$4$-邊連通</nobr> | Fully | 確定性 | 最差 $O(n\alpha(n))$ | |
| Eppstein et al[^1] | <nobr>$\ge 5$-邊連通</nobr> | Fully | 確定性 | 最差 $O(n\log n)$ | |

## 型態三：容錯模型

### 動態子圖連通問題

* 更新類型操作：
  - Disable/Enable Vertex to/from $S$.
  - Insert/Delete Edge.
* 查詢類型操作：
  - Query(u, v): 詢問 $u$ 與 $v$ 之間是否避開 $S$ 仍然連通。
* 參考文獻：
  - Ran Duan and Le Zhang, [Faster Randomized Worst-Case Update Time for Dynamic Subgraph Connectivity](https://arxiv.org/abs/1611.09072), WADS 2017.

### 點容錯模型

* 更新類型操作：
  - Insert/Delete Edge.
* 查詢預處理操作：
  - VertexFailure($S$): 現在擬定點集合 $S$ 為容錯集合。
* 查詢操作：
  - $\text{Query}_S(u, v)$: 詢問避開 $S$ 情形下 $u$ 與 $v$ 是否連通。
* 參考文獻：
  - Ran Duan and Seth Pettie, [Connectivity Oracles for Failure Prone Graphs](https://web.eecs.umich.edu/~pettie/papers/dfailure.pdf), STOC 2010.
  - Ran Duan and Seth Pettie, [Connectivity Oracles for Graphs Subject to Vertex Failures](https://arxiv.org/abs/1607.06865), SODA 2017, SICOMP 2020.




[^1]: David Eppstein, Zvi Galil, Giuseppe F. Italiano, and Amnon Nissenzweig, [Sparsification-A Technique for Speeding Up Dynamic Graph Algorithms](http://www.cs.ust.hk/mjg_lib/bibs/qzhang_lib/Dynamic/p669-eppstein.pdf), JACM 1997.