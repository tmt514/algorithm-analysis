# 偏序集排序（三）

今天的目標是要試圖找出，計算一個偏序集 $(P, <)$ 上面線性延伸數量 $e(P)$ 的估計。
如果有好辦法得到近似值，就可以拿它來計算排序效率、甚至可以用它來判斷每一次要比較哪兩個元素比較好。

## 順序多胞形 Order Polytope

今天的主角是一個在 $n$ 維空間中的多胞形：$\mathcal{O}(P)$。
更精確地說，它是一個被包含在 $n$ 維空間中單位立方體內的一個多胞形。
我們不妨假設 $P$ 這個集合的元素有 $x_1, x_2, \ldots, x_n$。
而任何一個 $P$ 的線性延伸 $\sigma$ 可以表示成一個註標 $\{1, 2, \ldots, n\}$ 的一個排列
$(\sigma(1), \sigma(2), \ldots, \sigma(n))$，使得 $x_{\sigma(i)} < x_{\sigma(j)}$ $\implies$ $i < j$。（由於是偏序集，逆命題並不一定成立。）

這個多胞形 $\mathcal{O}(P)$ 的定義是這樣的：

$$
\mathcal{O}(P) = \{ (z_1, z_2, \ldots, z_n) \ |\ z_i < z_j \text{ whenever } x_i < x_j \text{ in } P \}
$$

### 定理 24

$\mathcal{O}(P)$ 是一個凸多胞形，而且其體積恰好等於 $e(P)/n!$。

### 證明

要證明 $\mathcal{O}(P)$ 是凸多胞形，只需要說明對任何兩個 $\mathcal{O}(P)$ 裡面的點 $z, z'$，其連線中點 $(z+z')/2$ 仍然落在 $\mathcal{O}(P)$ 裡面即可。根據定義，每一個點都會滿足至少一個對應的 $P$ 的線性延伸。假設 $z$ 對應的是 $\sigma$、$z'$ 對應的是 $\sigma'$，顯然對於所有 $P$ 中的大小順序 $x_i < x_j$，都有 $z_{\sigma^{-1}(i)} \le z_{\sigma^{-1}(j)}$、且 $z'_{\sigma^{-1}(i)} \le z'_{\sigma^{-1}(j)}$。因此加起來除以 $2$ 以後，將所有座標值由小到大排列得到的新的排列 $\sigma''$ 仍然是 $P$ 的一個線性延伸。

關於體積的部分，我們考慮任何一個線性延伸 $\sigma$。由單一線性延伸定義出來的多胞形，它會是一個**單純形（Simplex）**。這邊定義出來的單純形，經過座標置換以後，可以發現其體積總是等價於以下這個單純形的體積：

$$
\Delta_*^n := \{(z_1, z_2, \ldots, z_n)\in \mathbb{R}^n \ |\ 0 \le z_1 \le z_2 \le \cdots \le z_n \le 1\}
$$

這個體積是多少呢？你可以用積分方法求出、也可以用對稱方法求出：總共有 $n!$ 種排列、每一個排列定義出來的單純形，體積都相同，而且它們全部聯集起來恰好組成 $[0, 1]^n\subset \mathbb{R}^n$ 的小方塊，也就是說他們體積總和恰好等於 $1$。一個這樣的單純形的體積是 $1/n!$。於是，$\mathcal{O}(P)$ 的體積就恰好等於 $e(P)/n!$ 啦～
<span style="float:right">$\square$</span>

我們之前隱約提及，要計算 $e(P)$ 的精確值是困難的。而這也等價於，要精確計算出 $\mathcal{O}(P)$ 的體積，也是困難的。
幸虧，1989 年的時候 Dyer, Frieze, 與 Kannan[^1][^3] 提出了一個多項式隨機演算法，能夠有效率地計算出近似值。但他們的方法都是基於 random walk 的，基本的想法是從任何一個 linear extension 開始，利用 random walk 依照某個特定機率分布交換某兩個沒有關聯的元素。後面的分析就精彩了，這邊先暫時留給有興趣的朋友閱讀吧，有機會我會再補上證明的。

最後我們再描述一個關於凸多胞形的性質。

## Ehrhart 多項式

法國數學家 [Eugène Ehrhart](https://en.wikipedia.org/wiki/Eug%C3%A8ne_Ehrhart) 在中學教了十多年的書以後，在六十歲的時候終於獲得了博士學位。在那之前，他於 1962 年提出了皮克公式（Pick's Theorem）的 $N$ 維加強版：[Ehrhart Polynomial](https://en.wikipedia.org/wiki/Ehrhart_polynomial)。

故事是這樣的：假設我們有一個 $N$ 維度的多胞形 $P$，如果把每一個座標軸都伸長 $k$ 倍，那基本上體積也會跟著放大 $k^N$ 倍，對吧？如果這時候我們計較的是這個被放大的多胞形 $kP$，其邊界或內部的「整數座標點」的數量 $L(P, k)$。Ehrhart 證明出了它會形成一個關於 $k$ 的 $N$ 次多項式！

不意外地，$L(P, k)$ 的首項係數（最高次項 $k^N$ 的係數）就會是這個多胞形真正的體積。
這個 Ehrhart 給我們有趣的證明技巧：如果我們要證明兩個多胞形體積相同，我們可以透過證明其 Ehrhart 相等的手法來證明其體積相等。

-----

明天我們來介紹另一種比較平易近人的、計算出 $e(P)$ 近似值的方式。
這個方式是透過 1986 年 Richard P. Stanley[^2] 提出的趣味觀察，把這個順序多胞形與另一個直鏈和多胞形（Chain Polytope，暫譯直鏈和多胞形) 連結在一起，進而從解另一個多胞形上的凸函數優化（Convex Optimization）來達到計算近似 $e(P)$ 的目的。

### 延伸閱讀

* [維基百科：Order Polytope](https://en.wikipedia.org/wiki/Order_polytope)
* https://www.math.sci.hokudai.ac.jp/~wakate/mcyr/2016/pdf/TSUCHIYA.pdf
* [線代啟示錄：多胞形](https://ccjou.wordpress.com/2013/05/20/%E5%A4%9A%E8%83%9E%E5%BD%A2/)

[^1]: Martin Dyer, Alan Frieze, and Ravi Kannan, _A Random Polynomial Time Algorithm for Approximating the Volume of Convex Bodies. [https://www.math.cmu.edu/~af1p/Texfiles/oldvolume.pdf](https://www.math.cmu.edu/~af1p/Texfiles/oldvolume.pdf)

[^2]: Richard P. Stanley, _Two Poset Polytopes_, 1986. [http://dedekind.mit.edu/~rstan/pubs/pubfiles/66.pdf](http://dedekind.mit.edu/~rstan/pubs/pubfiles/66.pdf)

[^3]: Graham Brightwell and Peter Winkler, _Counting Linear Extensions_, 1991. [https://link.springer.com/content/pdf/10.1007/BF00383444.pdf](https://link.springer.com/content/pdf/10.1007/BF00383444.pdf)