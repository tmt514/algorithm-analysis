# 偏序集排序（九）

今天來證明定理 29，的後半部。


## 定理 29

基於貪婪鏈分解的合併排序法，其比較次數 $T_{合併貪婪鏈} \le 6.33 \log e(P) + n$。

### 定理 29 的證明

首先，讓我們試圖把引理 30 帶入引理 31 之中，我們可以得到

$$\begin{aligned}
T_{合併貪婪鏈} &\le \frac{1}{1-\delta} \left(n\log \frac{n}{\delta} - nH(P)\right) \\
&\le \frac{1}{1-\delta} \left(n\log \frac{n}{\delta} + 4\log e(P) - n\log n\right) \\
& = \frac{1}{1-\delta} \left(4\log e(P) + n\log \frac{1}{\delta}\right)
\end{aligned}\tag{*}\label{eq0}
$$

當我們選取 $\delta = 1/2$ 的時候，可以得到 $T_{合併貪婪鏈} \le 8\log e(P) + 2n$。
選取 $\delta \to 1$ 的時候，後面 $n$ 的常數也只是趨近於 $1/\ln 2\approx 1.44$。
這個常數比起上面的 $6.6\log e(P)+n$ 還要差了一點點呢。這代表我們還需要一些觀察。

而事實上，[引理 27](./poset-sort6.html#引理-27) 給予了我們相當大的提示。
這個觀察是這樣的：我們如果把最長的鏈先拿到旁邊放著，那麼剩下的 $n-|C_1|$ 筆資料拿去做貪婪鏈合併之後，
所需要的比較次數複雜度會長得像 $T' \le c_1\log e(P') + c_2 (n-|C_1|)$。其中 $P'$ 是指將 $P$ 中最長鏈移除後的子偏序集。
顯然移除了一些集合元素以後，我們有 $e(P') \le e(P)$、而且 $n-|C_1| \le \log e(P)$。因此可以順水推舟得到
$T' \le (c_1 + c_2)\log e(P)$。最後再將合併完成的 $C_2\cup C_3\cup\cdots \cup C_k$ 與 $C_1$ 進行合併。顯然這步最多只要花費 $n$ 次比較就行了。因此加起來我們可以得到 $O(\log e(P)) + n$ 次比較。

### 引理 32

$$
T_{合併貪婪鏈} \le n + (n - |C_1|) + \sum_{i=2}^k |C_i| \log \frac{n-|C_1|}{|C_i|}
$$

### 引理 32 的證明

這個分析是先把 $|C_1|$ 拿掉，然後合併其他部分，最終再將 $|C_1|$ 與剩下的資料合併。
由於採用貪婪法合併序列所得到的總比較次數是最優的，因此這個方法得到的總比較次數，不會比原本的貪婪法合併來得好。
<span style="float:right">$\square$</span>

-----

結合 $\eqref{eq0}$ 的論證過程以後，我們可以得到新的上界：

$$
\begin{aligned}
T_{合併貪婪鏈} &\le n + (n - |C_1|) + \sum_{i=2}^k |C_i| \log \frac{n-|C_1|}{|C_i|} \\
&\le n +  (n - |C_1|)+ \frac{1}{1 - \delta}\left( 4\log e(P) + (n-|C_1|)\log \frac{1}{\delta}\right)\\
&\le n + \log e(P) + \frac{1}{1 - \delta}\left( 4\log e(P) + \log e(P) \log \frac{1}{\delta}\right)\\
&\le n + \left(1 + \frac{4}{1-\delta} + \frac{1}{1-\delta} \log \frac{1}{\delta} \right) \log e(P)
\end{aligned}
$$

透過 [Wolfram Alpha](https://www.wolframalpha.com/input/?i=min+1+%2B+4%2F%281-x%29+%2B+%281%2F%281-x%29%29log2%281%2Fx%29+in+%5B0%2C+1%5D) 來看，選取 $\delta\approx 0.18274$ 左右的時候，可以得到 $8.89\log e(P) + n$ 的結論。

如果我們將 Cardinal 等人的原作[^1] 裡面的結論帶入的話（把 4 換成 2），就可以得到[最小值](https://www.wolframalpha.com/input/?i=min+1+%2B+2%2F%281-x%29+%2B+%281%2F%281-x%29%29log2%281%2Fx%29+in+%5B0%2C+1%5D)出現在 $\delta\approx 0.27081$ 左右，可以得到 $6.33\log e(P) + n$ 的結論！

[^1]: Jean Cardinal, Samuel Fiorini, Gwenaël Joret, Raphaël M. Jungers, J. Ian Munro, _Sorting under Partial Information (without the Ellipsoid Algorithm)_, Combinatorica 33, 655–697 (2013). https://doi.org/10.1007/s00493-013-2821-5, [ArXiv](https://arxiv.org/pdf/0911.0086.pdf).