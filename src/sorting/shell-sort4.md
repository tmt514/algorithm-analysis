# 謝耳排序法（四）

嗨大家好久不見！為了讓大家快速回憶起謝耳排序法厲害的地方：利用兩個互質數字的次方，達到排序的目的。我們用這個定理作為開頭。

### 定理 40 [Incerpi-Sedgewick 1985]

給定一個長度 $m$，存在一個長度為 $m$ 的步長序列，使得謝耳排序法的時間複雜度為 $O(mN^{1 + O(1/\sqrt{m})})$。

### 證明

想像一下，如果我們以 $2^x3^y$ 的形式挑選我們的步長，那麼所需要的步長序列長度不超過 $\lceil\log_2(N+1)\rceil\lceil\log_3(N+1)\rceil$。反過來思考，如果我們需要長度是 $m$ 的步長序列，那麼我們只要挑選最大的整數 $a$，使其滿足 $\lceil\log_a(N+1)\rceil\lceil\log_{a+1}(N+1)\rceil\le m$ 即可。

這時候套用謝耳排序法所需要的時間複雜度是多少呢？根據[係理 35](shell-sort2.html#%E4%BF%82%E7%90%86-35)，進行一次 $h$-sort 所需要的時間是 $O(a^2)$。因此整體時間複雜度為 $O(a^2mN)$。那麼，$a$ 與 $m$ 的關係如何呢？透過

$$\left(\frac{\log N}{\log a}\right)^2 \approx m$$

可以解得

$$a = N^{\Theta(1/\sqrt{m})}$$

證畢。

------

上面這個式子，在 $m$ 的值足夠小的時候，是可以把 $m$ 的數值吃進 $N^{1/\sqrt{m}}$ 這一項裡面的。於是我們有以下係理。

### 係理 41

給定一個長度 $m \le (\log N / \log \log N)^2$，對於所有足夠大的 $N$，存在一個步長序列，使得進行謝耳排序法所需要的比較次數至多為 $N^{1+O(1/\sqrt{m})}$。

------

為什麼要注重於 $N^{1+O(1/\sqrt{m})}$ 這個形狀的函數呢？在 1992 年的時候，Plaxton-Poonen-Suel[^1] 給出了一個下界序列的構造，他們證明了對於任何整數 $m \le (\log N/ \log\log N)^2$，存在一個序列使得謝耳排序法所需要的比較次數至少是 $N^{1+\Omega(1/\sqrt{m})}$。換句話說，謝耳排序法無論如何在最壞的情形下，都至少要花費 $\Omega(N(\log N/\log\log N)^2)$ 的時間。

這個是目前為止最佳的理論下界了。能不能把這個下界跟 $O(N\log^2 N)$ 的上界合起來，還有待大家的努力。


## 附錄：其他的變種下界

* Cypher 在 1989 年[^2] 率先找出了在排序網路(Sorting Network) 上面的 $\Omega(N\log^2N/\log\log N)$ 下界。在這個模型中，謝耳排序的上界仍然是 $O(N\log^2 N)$，因此還是有個懸而未解的空隙。我們會在接下的文章討論排序網路。
* Jiang, Li, 以及 Vitányi 在 1999 年[^3] 的時候，以資訊理論的角度證明了任何長度為 $m$ 的步長序列，其平均時間複雜度至少是 $\Omega(mN^{1+1/m})$。該結果由 Vitányi 在 2018 年[^4] 推廣到關於步長序列的函數。


[1]: Plaxton, Poonen, and Suel. [Improved lower bounds for Shellsort](https://ieeexplore.ieee.org/document/267769) (FOCS 1992)

[2]: Cypher. [A lower bound on the size of shellsort networks](https://dl.acm.org/doi/abs/10.1145/72935.72942) (SPAA 1989)

[3]: Jiang, Li, Vitányi. [Average-Case Complexity of Shellsort](https://arxiv.org/abs/cs/9901010) (ICALP 1999) [比較乾淨的版本](https://arxiv.org/pdf/cs/9906008.pdf)。

[4]: Vitányi. [On The Average-Case Complexity of Shellsort.](https://arxiv.org/pdf/1501.06461.pdf) (RSA 2018)

