# 關於空棋盤骨牌鋪磚公式 Formula for Domino Tilings

（這篇文章並不完整，如果想要看完整的證明還請您直接滑到最下面查看參考資料～）

這個公式幾乎是同時間被 Temperley 以及 Fisher [^1] 與 Kasteleyn [^2] 在 1961 年相繼提出。
這邊給出的證明是使用 Kasteleyn Matrix 的技巧，雖然 Kasteleyn Matrix 本身只能使用在沒有洞的格子點上，並不能直接推廣到平面圖，但中間使用圖譜論的計算方法還是滿有意思的。

## 定理

給定正整數 $m$ 與 $n$。那麼，使用 $1\times 2$ 骨牌恰好鋪滿 $m\times n$ 大小的棋盤的方法數恰有

$$\prod_{j=1}^m\prod_{k=1}^n \left(4\cos^2\frac{j\pi}{m+1}+4\cos^2\frac{k\pi}{n+1}\right)^{1/4}$$

這麼多種。

## Kasteleyn 矩陣

首先我們可以將 $m\times n$ 棋盤做黑白染色。
若我們將黑格與白格分別當作二分圖的兩邊，那麼我們可以透過一個方陣來描述哪些格子是相鄰的。
而 Kasteleyn 矩陣 $K\in\mathbb{C}^{\frac{mn}{2}\times \frac{mn}{2}}$ 就是對這個方陣的值進行特殊的賦權。其定義如下：

$$K(b, w) = \left\{\begin{aligned}
1 & \ \ \ \ \text{ 若黑格 } b \text{ 與白格 } w \text{ 水平相鄰；}\\
i & \ \ \ \ \text{ 若黑格 } b \text{ 與白格 } w \text{ 垂直相鄰；}\\
0 & \ \ \ \ \text{ 其他。}
\end{aligned}\right.$$

其中 $i=\sqrt{-1}$。

### Kasteleyn 矩陣的行列式值

我們用 $\sigma$ 來描述一個 $1,2,\ldots, \frac{mn}{2}$ 的排列。
將所有黑格與白格依照任意順序編號後，根據行列式的定義，我們可以把 $\det(K)$ 寫成：

$$
\det(K)=\sum_{\sigma} (-1)^\sigma \prod_{i=1}^{mn/2} K(i, \sigma(i))
$$

其中 $(-1)^\sigma$ 代表該排列的奇偶性。
從上面的式子可以看出，每一個排列 $\sigma$ 對應的就是一組可能的白格、黑格的配對。
而且那些 $\prod_{i} K(i, \sigma(i))\neq 0$ 非零的項，代表了棋盤上的一組完美匹配。
因此我們只需要證明任意兩組完美匹配 $M, M'$ 對應之排列 $\sigma_M, \sigma'_M$ 不會互相消掉即可。如果互相消掉的話可能就相消玉殞了。



### Kasteleyn 定理 [1961]

對於任意兩組完美匹配 $M$ 與 $M'$，

$$
(-1)^{\sigma_M}\prod_{i=1}^{mn/2} K(i,\sigma_M(i)) = (-1)^{\sigma'_M}\prod_{i=1}^{mn/2} K(i, \sigma'_M(i)).
$$

而從上可以得出 $|\det(A)|$ 恰為完美匹配的數量的結論。

### Kasteleyn 定理大概的證明

若 $M$ 與 $M'$ 是兩組完美匹配，那麼考慮其對稱差 (symmetric difference) $M\Delta M'$：它將會由若干個不相交的環所構成。
因此，我們只需要考慮簡化後的版本，不妨假設 $M\Delta M'$ 恰好是一個環 $C$。
由於是格子點，因此要構成一個環，其環的長度一定是偶數。令 $2k$ 為環的長度且 $\ell$ 為被 $C$ 包圍住的內部格子點的數量。
若我們將奇數位置的邊 $M\cap C$ 與偶數位置的邊 $M'\cap C$ 分開計算，那麼只要證明以下引理，便能使定理成立：

$$(-1)^{k+\ell-1} = \prod_{e\in (M\cap C)} K(e) \bigg/ \prod_{e \in(M'\cap C)} K(e).$$

稍微整理一下兩邊，可以發現我們需要的是 $(-1)^{k+\ell-1} = (-1)^{\sigma_M} / (-1)^{\sigma'_M}$。
由於 $M$ 與 $M'$ 是兩個完美匹配、因此內部格子點的數量必定是偶數（否則把這個 cycle 拿掉後內部與外部就分開了，內部根本沒辦法形成一個完美匹配）。於是我們知道 $\ell$ 是偶數。此外，從 $\sigma_M$ 的確是可以透過 $k-1$ 次置換變成 $\sigma'_M$ (證明略)。因此定理成立。

### 非常粗略的引理證明

這邊可以使用的是歸納法！這邊推薦的是 [Cornell 講義](https://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-17.pdf)給出的證明。該證明是對總環長與內部格子數進行歸納。Base Case 是兩條重合的邊，結論顯然成立。Inductive Case 是考慮環的某個角落，並且將之往內推進一格。此時可能會有三種推進一格的情形，而三種情形都恰好可以被處理乾乾淨淨 ：）

## 擴充成鄰接矩陣

上述定義的卡斯德林 Kasteleyn 矩陣其實並非圖 $G$ 的鄰接矩陣。
但其實我們可以把它拓展成鄰接矩陣：

$A=\begin{bmatrix}
0 & K \\
K^\top & 0 \\
\end{bmatrix}$

而經過某些線性代數計算後我們得知 $\det(A) = \det(K)^2$。
若我們的目標是 $m\times n$ 大小的棋盤上的完美匹配數量，我們只要求得其鄰接矩陣 (某些項為 $i$、某些項為 $1$) 之行列式值的公式即可！

### 特殊的圖有著特殊的行列式值

要算出行列式值，也可以透過把所有特徵值通通乘起來得到它。於是我們的目標就是要找出所有矩陣 $A$ 的特徵值！
這邊我們可以利用圖譜論加上有趣的笛卡爾乘積圖 (或張量分解) 來解決它。
細節可以參考[圖譜論 Spectral Graph Theory 介紹與導讀](https://math.uchicago.edu/~may/REU2012/REUPapers/JiangJ.pdf)與[Cornell 講義的後半段](http://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-18.pdf)。


## 參考資料

[^1]: H. N. V. Temperley & Michael E. Fisher (1961) [Dimer problem in statistical mechanics-an exact result](https://www.tandfonline.com/doi/abs/10.1080/14786436108243366), The Philosophical Magazine: A Journal of Theoretical Experimental and Applied Physics, 6:68, 1061-1063.

[^2]: P.W.Kasteleyn (1961) [The statistics of dimers on a lattice: I. The number of dimer arrangements on a quadratic lattice](https://www.sciencedirect.com/science/article/abs/pii/0031891461900635), Physica, 27:12, 1209-1225.

* 精簡的證明，感覺有點簡化過頭了，很多地方其實沒交代地太清楚。 [https://joshuahhh.com/projects/counting-domino-tilings.pdf](https://joshuahhh.com/projects/counting-domino-tilings.pdf)
* 最重要的是 Lemma 12: [https://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-17.pdf](https://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-17.pdf)
* 這個也很精簡。[http://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-18.pdf](http://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-18.pdf)
* 圖譜論 Spectral Graph Theory 介紹與導讀 Jiaqi Jiang,《An Introduction to Spectral Graph Theory》 [https://math.uchicago.edu/~may/REU2012/REUPapers/JiangJ.pdf](https://math.uchicago.edu/~may/REU2012/REUPapers/JiangJ.pdf)
