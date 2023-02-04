# 應用：三角形格子點問題

## 重要的觀察：利用 X-Y 鏡射把斜率變陡！

是這樣的，我們可以把這個三角形的區域中的格子點數量寫成下列這個式子：

$$f(a, b, n) = \sum_{i=1}^{n-1} \left\lfloor \frac{a}{b}i \right\rfloor$$

當 $a < b$ 的時候，這是一條比較平緩的線。比如下圖，描述的是當 $n=18$ 的時候且 $a/b = 37/81$ 所圍成的三角形內部的格子點們。
(你可以在這個連結 [https://www.geogebra.org/calculator/hugmrwqu](https://www.geogebra.org/calculator/hugmrwqu) 找到下面這張圖)

![imgur](https://i.imgur.com/uy2qfxQ.png)

但是當你把 X 和 Y 座標反過來以後，就會變成一條斜率為 $81/37$ 的直線了！
所以我們可以得知，當 $a < b$ 的時候，格子點內部的點數為『矩形內部總格點數』扣掉『另一半三角形』扣掉『剛好壓在邊上』的點數。 

$$f(a, b, n) = (n-1)\left(\left\lceil \frac{an}{b} \right\rceil - 1\right) - f(b, a, \left\lceil \frac{an}{b} \right\rceil) - I(a, b, n)$$

其中 $I(a, b, n)$ 是剛好壓在線上的格子點的數量（上述例子中剛好 $I(a, b, n)=0$）。

## 當斜率變陡以後

現在我們考慮 $a > b$ 的情形。此時我們能用輾轉相除法的概念，令 $a=b{\color{red}{q}}+{\color{darkgreen}{r}}$，其中 $r < b$ 是餘數且 $q\ge 1$。
我們便有了另一層代數上的見解：

$$
\begin{aligned}
f(a, b, n) &= \sum_{i=1}^{n-1} \left\lfloor \frac{a}{b}i \right\rfloor\\
&=\sum_{i=1}^{n-1} \left\lfloor \frac{b{\color{red}{q}}+{\color{darkgreen}{r}}}{b}i \right\rfloor \\
&=\sum_{i=1}^{n-1} \left({\color{red}qi} + \left\lfloor \frac{\color{darkgreen}{r}}{b}i \right\rfloor\right)  = q\frac{n(n-1)}{2} + f({\color{darkgreen}{r}}, b, n)\\
\end{aligned}
$$

於是乎，我們就可以使用輾轉相除法的概念解決這題啦，讚吧！