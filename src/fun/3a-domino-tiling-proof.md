# 空棋盤骨牌鋪磚公式的證明 Proof to Domino Tilings

這個公式幾乎是同時間被 Temperley 以及 Fisher [^1] 與 Kasteleyn [^2] 在 1961 年相繼提出。
這邊給出的證明是使用 Kasteleyn Matrix 的技巧，雖然 Kasteleyn Matrix 本身只能使用在空棋盤上，但中間使用圖譜論的計算方法還是滿有意思的。

## 定理

給定正整數 $m$ 與 $n$。那麼，使用 $1\times 2$ 骨牌恰好鋪滿 $m\times n$ 大小的棋盤的方法數恰有

$$\prod_{j=1}^m\prod_{k=1}^n \left(4\cos^2\frac{j\pi}{m+1}+4\cos^2\frac{k\pi}{n+1}\right)^{1/4}$$

這麼多種。

## Kasteleyn 矩陣

首先我們可以將 $m\times n$ 棋盤做黑白染色。
若我們將黑格與白格分別當作二分圖的兩邊，那麼我們可以透過一個方陣來描述哪些格子是相鄰的。
而 Kasteleyn 矩陣 $A$ 就是對這個方陣的值進行特殊的賦權。其定義如下：

$$A_{b, w} = \left\{\begin{aligned}
1 & \ \ \ \ \text{ 若黑格 } b \text{ 與白格 } w \text{ 水平相鄰；}\\
i & \ \ \ \ \text{ 若黑格 } b \text{ 與白格 } w \text{ 垂直相鄰；}\\
0 & \ \ \ \ \text{ 其他。}
\end{aligned}\right.$$

其中 $i=\sqrt{-1}$ 為一複數。

現在，讓我們不妨令 $t:=mn/2$ 為方陣 $A$ 的邊長。

## 參考資料

[^1]: H. N. V. Temperley & Michael E. Fisher (1961) [Dimer problem in statistical mechanics-an exact result](https://www.tandfonline.com/doi/abs/10.1080/14786436108243366), The Philosophical Magazine: A Journal of Theoretical Experimental and Applied Physics, 6:68, 1061-1063.

[^2]: P.W.Kasteleyn (1961) [The statistics of dimers on a lattice: I. The number of dimer arrangements on a quadratic lattice](https://www.sciencedirect.com/science/article/abs/pii/0031891461900635), Physica, 27:12, 1209-1225.

* 精簡的證明，感覺有點簡化過頭了，很多地方其實沒交代地太清楚。 [https://joshuahhh.com/projects/counting-domino-tilings.pdf](https://joshuahhh.com/projects/counting-domino-tilings.pdf)
* 這個也很精簡。[http://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-18.pdf](http://pi.math.cornell.edu/~levine/18.312/alg-comb-lecture-18.pdf)
