# 謝耳排序法（二）

在前一篇文章裡面，我們定義了 $h$-排序（$h$-sorted）與步長序列（Gap Sequence），它們能帶給我們什麼樣的好處呢？
如果我們換一個角度來觀察 $h$-排序：經過了 $h$-排序以後，對於陣列中任何一個位置 $i$，都有 $A[i] \le A[i+h] \le A[i+2h]\le \cdots$。

## 一口氣考慮兩種 $h$

經過了 $h_1$-sorted 以及 $h_2$-sorted 以後，我們能不能對於，除了間隔 $h_1$ 或是間隔 $h_2$ 的整數倍以外，從某些陣列元素之間獲取一些大小關係呢？其實是可以的！
比方說，我們利用 $h_1$-sorted 的性質寫下
$$
A[i] \le A[i+kh_1]\ \ \ \forall k\in\mathbb{N}
$$
然後再利用 $h_2$-sorted 性質寫下 
$$
A[i+kh_1] \le A[i+kh_1 + \ell h_2]\ \ \ \forall k, \ell\in\mathbb{N}
$$
如果 $h_1$ 與 $h_2$ **互質（coprime）** 的話，透過下述經典的 **湊郵票問題**，我們可以發現每一個元素與 **足夠遠** 的資料其實都已經排好了大小順序！

### 引理 34（湊郵票問題）

假設你有兩種郵票：第一種每張面額 $a$ 元、第二種每張面額 $b$ 元。
如果 $\gcd(a, b)=1$，那麼對於任意整數 $c\ge ab-a-b+1$，我們保證能用若干張郵票，湊出恰好 $c$ 元的郵資。

### 引理 34 的證明

讓我們快速回憶一下關於最大公因數的 [貝祖定理 Bézout's Lemma](https://zh.wikipedia.org/wiki/%E8%B2%9D%E7%A5%96%E7%AD%89%E5%BC%8F)：對於任意正整數 $a, b$，若 $\gcd(a, b)=1$，則存在整數 $x, y$ 使得 $ax+by=1$。

現在把等式兩邊同乘以命題中的 $c$ 值：$a(cx) + b(cy) = c$。
若 $cx$ 與 $cy$ 都是非負，那麼顯然我們用 $cx$ 張面額為 $a$ 的郵票、以及 $cy$ 張面額為 $b$ 的郵票，就可以湊出想要的值。
否則的話，$cx$ 與 $cy$ 一正一負。
我們不妨暫且假設 $cx > 0$。此時我們把式子整理一下，把 $cx$ 當中可以被 $b$ 整除的部分通通搬到右邊去補那個負數。得到：
$$ a(cx\bmod b) + b Y = c $$

其中 $Y = cy + a \floor{cx/b}$ 是一個整數。由於 $cx\bmod b \ge 0$，我們只要能夠證明 $Y \ge 0$ 我們就能保證得到一種郵票的湊法了！
注意到「$b Y = c - a(cx\bmod b)$」總是 $b$ 的倍數，因此，只要 $c - a(cx\bmod b) \ge -(b-1)$，就能夠推得 $Y \ge 0$。

根據 $cx\bmod b$ 的定義、與我們對 $c$ 的假設，可以得到
$$
\begin{aligned}
bY &= c - a(cx\bmod b) \\
& \ge c - a(b-1) \\
&\ge (ab - a - b + 1) - a(b-1) \\
&= -(b - 1)  
\end{aligned}
$$

因此，$Y \ge 0$，得證。
事實上，無論是否 $cx > 0$，只要我們定義 $(cx\bmod b) = cx - b\floor{cx/b}$，基本上該值就是非負。
<span style="float:right">$\square$</span>

-----

有了引理 34 以後，對於同時滿足 $a$-sorted 與 $b$-sorted 的陣列來說，只要距離超過 $c\ge ab-a-b+1$，就能夠保證 $A[i]\le A[i+c]$。換句話說，如果要在此時進行插入排序法，每一個元素只要往前換最多 $ab-a-b+1=\Theta(ab)$ 次即可！
如果在此時對某個 $h$ 進行 `h_sort`，那麼每一個元素只需要往前考慮 $\Theta(ab/h)$ 次交換即可，於是有以下小結論：

### 係理 35

令 $h_1, h_2, h_3\in \mathbb{N}$。假設 $\gcd(h_1, h_2)=1$。
若陣列 $A$ 是 $h_1$-sorted 且為 $h_2$-sorted，
那麼欲將陣列以 `h_sort` 整理成 $h_3$-sorted，只需要 $O(Nh_1h_2/h_3)$ 的時間。
<span style="float:right">$\square$</span>


有了係理 35 以後，我們就能證明前一篇文章中最後提到的 $O(N^{3/2})$ 時間排序。
假設我們考慮的步長序列為 $h=(1, 3, 7, 15, \ldots, 2^i-1, \ldots)$。從最接近 $N$ 的那個步長開始，逐步往下進行 `h_sort`。
現在這個「**每一項都是 2 的冪次減 1**」的這個步長設定，就顯然變得比較有意義了：我們希望相鄰兩個步長總是互質的！

### 定理 36

對於步長序列 $h_i=2^i-1$，謝耳排序法的時間複雜度為 $O(N^{3/2})$。

### 定理 36 的證明

對於所有 $h_i > \sqrt{N}$ 的那些步長，使用引理 33 可以知道每一次時間複雜度正比於 $N^2/h_i \le N^{3/2}$，
而且每一次放大兩倍，所以全部加起來的執行時間是 $O(N^{3/2})$。
對於所有 $h_i < \sqrt{N}$ 的那些步長，在執行 $h_i$-sort 之前，由於已執行過 $h_{i+1}$-sort 與 $h_{i+2}$-sort。
因此根據係理 35，進行 $h_i$-sort 的時間複雜度為 $O(Nh_{i+1}h_{i+2}/h_i) = O(N2^i)$，因此全部加起來時間正比於 $N^{3/2}$，得證。
<span style="float:right">$\square$</span>

-----

我們下一篇要把這個湊郵票的問題發揮到極致，邁向 Pratt 版本的 $O(N\log^2 N)$ 時間謝耳排序！


### 備註

定理 36 的分析是緊的，從 Pratt 的論文[^1]中的第 22 頁構造了一組長度為 $N$ 的輸入，
它使用這個 2 的冪次減一版本的步長序列進行謝耳排序，至少要花 $\Omega(N^{3/2})$ 的時間。
Poonen[^2] 提供了更多的 Worst case examples。

[^1]: Vaughan R. Pratt, _Shellsort and Sorting Networks_, Ph.D Thesis, Stanford University, 1972. [https://apps.dtic.mil/dtic/tr/fulltext/u2/740110.pdf](https://apps.dtic.mil/dtic/tr/fulltext/u2/740110.pdf)

[^2]: Bjorn Poonen, _The Worst Case in Shellsort and Related Algorithms_, J. Algorithms, 1993. [https://math.mit.edu/~poonen/papers/shell.pdf](https://math.mit.edu/~poonen/papers/shell.pdf)