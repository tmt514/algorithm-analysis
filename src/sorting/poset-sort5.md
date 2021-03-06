# 偏序集排序（五）

前一次我們提到了，從一個偏序集 $(P, <)$ 定義出來的直鏈和多胞形（Chain Polytope）$\mathcal{C}(P)$，其體積與順序多胞形（Order Polytope）$\mathcal{O}(P)$ 相等，且剛好等於 $e(P) / n!$。

但是計算一個任意多胞形的確切體積，是困難的。幸好，如果我們只需要估計 $e(P)$ 的值（甚至可以放寬條件、只需要估計 $\log e(P)$ 的值就行了），不需要計算出整個多胞形的確切體積。

## 利用長方體估算體積

能夠簡單計算體積的形狀，大概就是長方體了吧。
透過觀察，我們發現，對於任何一個直鏈和多胞形內的點 $z=(z_1, z_2, \ldots, z_n) \in\mathcal{C}(P)$，都可以定義出一個長方體，其兩個對角點剛好分別是原點 $(0, 0, \ldots, 0)$ 以及 $z$。
換句話說，這個長方體
$$
\text{Box}(z) = [0, z_1]\times [0, z_2]\times \cdots \times [0, z_n]\subset \mathcal{C}(P)
$$

$\text{Box}(z)$ 的體積，顯然可以直接寫出來：$z_1z_2\cdots z_n$。既然長方體的體積如此好算，那麼我們試圖找出 $\mathcal{C}(P)$ 內部最大的長方體，用它來估計 $e(P)$ 的值，應該很有希望。於是，我們可以寫下一個最佳化問題：

$$
\begin{aligned}
\text{maximize }\ \ & z_1z_2\cdots z_n\\
\text{subject to }\ \ & z\in \mathcal{C}(P)
\end{aligned}
$$

這個問題，乍看之下有點棘手，理由是，目前我們能夠輕鬆解決的問題，大多是線性規劃、或是凸函數最佳化等等。
而上述題目，有兩個地方跟我們平常解的最佳化問題有些出入：其一是目標函數，全部乘在一起了看起來有點麻煩；其二是變數條件，$\mathcal{C}(P)$ 雖然是個多胞形，能夠被許多線性條件表示。
但是， $\mathcal{C}(P)$ 的定義並非如 $\mathcal{O}(P)$ 一般可以單純以 $z_i \le z_j \ \ \forall x_i, x_j\in P, x_i < x_j$ 的條件來表示之。
最直接的寫法──枚舉所有最大獨立集，並設定所有參與獨立集裡面的變數總和不超過 1 ──可能會需要指數級別數量的線性不等式。

不過呢，如果我們把目標函數取個 $-\log$，然後除個 $n$ 平均一下，就可以讓目標函數變成凸函數啦～於是第一個問題變得可解一些：

$$
\begin{aligned}
\text{minimize }\ \ & H(z) := -\frac{1}{n}\sum_{i=1}^n \log z_i \\
\text{subject to }\ \ & z\in \mathcal{C}(P)
\end{aligned}
$$

（備註：上面的 $1/n$ 並不影響最佳化的解，加上去是因為這個東西根本一臉資訊理論中的熵 entropy 的定義，為了保持定義的一致性加上去的。）
要解決第二個問題，我們其實可以利用 membership oracle 的觀念：拿來解線性規劃的工具，如橢球法（Ellipsoid Method）與內點法（Interior Point Method），都只需要判斷「目前某個點是否滿足指定條件」的工具就行了。也就是說，我們可以透過兩個多胞形之間的轉換 $\varphi^{-1}$，將欲判斷 membership 的點從 $\mathcal{C}(P)$ 換到 $\mathcal{O}(P)$ 去檢查（或等價地、乾脆直接在 poset 上面作一次動態規劃），就可以在 $O(n^2)$ 時間內判斷欲查詢的點是否在 $\mathcal{C}(P)$ 內部囉。

於是，我們可以套用凸函數最佳化的大刀，幫助我們找出直鏈和多胞形內部最大的長方體[^1]。
假設這個最佳化問題的解是 $z^*$，對應到的長方體體積為 $\text{vol}(\text{Box}(z^*)) = 2^{-nH(z^*)}$。為了方便起見，我們暫且把這個體積記作 $2^{-nH(P)}$。於是呢，可以得出以下結論：

### 引理 26

$$
2^{-nH(P)} \le e(P)/n!
$$

整理一下可得

$$
\log e(P) + nH(P) \ge \log n!
$$

這告訴我們什麼呢？當這個解 $nH(P)$ 的值越小的時候，$\log e(P)$ 越大（存在更多的線性延伸）。等價地地，若 $\log e(P)$ 很小（只有少許的線性延伸），那麼 $nH(P)$ 保證很大。
說到這裡，筆者不禁捫心自問，原本不是想估計 $e(P)$ 的值嗎？為什麼我們可以只關心 $\log e(P)$？

## 主題──偏序集排序

原因是這樣的：如果給定了部分資料之間的大小關係 $P$，顯然從前些日子提到的 $S(12)>29$ 來看，存在一些偏序集無法在恰好 $\ceil{\log e(P)}$ 次比較之內排好所有資料的順序。那麼，我們想知道的是，能否退而求其次，如同大多數使用 $O(n\log n)$ 次比較的排序演算法，允許常數倍數的誤差，在 $O(\log e(P))$ 次比較之內排好順序呢？

也就是說，如果這個偏序集 $P$ 已經幾乎排好序了，有沒有比 $\Theta(n\log n)$ 使用更少次數的排序演算法，可以正確地利用少少的 $O(\log e(P))$ 次比較，從而達到正確排序呢？
答案是有的[^2]，我們可以利用這幾天討論過的觀念，一步一步邁向 $O(\log e(P))$ 的偏序集排序。我們甚至還不需要真的用大刀解凸函數最佳化問題，只需要觀念就可以了。

一個有趣的暖身是這樣的：從上面的引理 26，我們可以得到一個超簡單 $O(\log n\cdot \log e(P))$ 的偏序集排序演算法。大家也不妨猜猜看！這個我們明天講～

-----

[^1]: 至於大刀該怎麼用比較正確，詳情以後再談好了…。

[^2]: Jean Cardinal, Samuel Fiorini, Gwenaël Joret, Raphaël M. Jungers, J. Ian Munro, _Sorting under Partial Information (without the Ellipsoid Algorithm)_, Combinatorica 33, 655–697 (2013). https://doi.org/10.1007/s00493-013-2821-5, [ArXiv](https://arxiv.org/pdf/0911.0086.pdf).
