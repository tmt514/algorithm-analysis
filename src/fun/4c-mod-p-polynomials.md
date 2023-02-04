# 應用：多項式的解數

這邊我們先假設 $p=998244353$ 是個大家最喜歡的質數吧。

## 第一種想法：利用 NTT

總之 NTT 會帶給你 $f(0), f(1), \ldots, f(p-1)$ 的值，算完之後就可以知道有幾個解啦。
這個時間複雜度是 $O(n+p\log p)$ (吧）

### 小插曲：利用 NTT 計算多項式乘法

如果要把模 $p$ 底下的兩個多項式 $f, g$ 乘起來，且這兩個多項式的度數都不超過 $n$。
那麼使用 NTT 我們可以在 $O(n\log n)$ 時間內計算出乘積 $fg$。

## 第二種想法：兩個多項式的最大公約式

若 $f(x)$ 在模 $p$ 底下有解 $r_1, r_2, \ldots, r_t$，那麼我們能將 $f(x)$ 寫成形如：
$$f(x)\equiv (x-r_1)^{k_1}(x-r_2)^{k_2}\cdots (x-r_t)^{k_t} g(x)$$ 的形式，其中 $k_1, k_2, \ldots, k_t\ge 1$ 為正整數，$g(x)$ 也是一個整係數多項式，而且 $g(x)$ 在模 $p$ 底下毫無整數解。

如果我們將 $f(x)$ 與 $h(x):=x(x-1)(x-2)\cdots (x-(p-1))$ 拿去找出最大公約式 (這個在[歐幾里德整環](https://zh.wikipedia.org/wiki/%E6%AD%90%E5%B9%BE%E9%87%8C%E5%BE%97%E6%95%B4%E7%92%B0)來說能夠被良好地定義出來)，這個最大公約式就必定會是我們想要的：
$$\gcd(f(x), h(x)) = (x-r_1)(x-r_2)\cdots (x-r_t)。$$

而使用這個方法的好處有兩個：其一，如果我們只在乎 $t$ 的值，那麼找出最大公約式以後，它的次數就會是我們要的答案啦！其二，根據[費馬小定理](https://zh.wikipedia.org/wiki/%E8%B4%B9%E9%A9%AC%E5%B0%8F%E5%AE%9A%E7%90%86)，我們會發現 $h(x)$ 其實根本等於 $x^p-x$，非常簡約。
這個簡約的特性，可以讓我們使用反覆平方法或減半平方法加速 $\gcd(f(x), h(x))$ 的第一步的計算！

注意到 $(x^p-x)\bmod f = (x^p \bmod f) - (x \bmod f)$，我們可以先關心要怎麼計算 $x^p\bmod f$。
而這就簡單啦：若要計算 $x^k\bmod f$，可以直接先遞迴求出 $(x^{k/2}\bmod f)$ 之值，然後將之<b>平方</b>然後再取餘數。
(或者是如同 [stackoverflow](https://stackoverflow.com/questions/29001275/roots-of-a-polynomial-mod-a-prime) 上面的建議，事先算出 2 的次方除以 $f$ 的餘數，然後再挑你想要的乘起來。)
注意到 $n$ 是多項式 $f(x)$ 的度數。
這邊需要的計算便是兩個最多 $n$ 次多項式的乘法 (我們可以用 NTT 解決它)、以及一個 $2n$ 次多項式除以 $n$ 次多項式的商和餘數。
除法部分的想法基本上來自於 Schönhage，可以參考[這份投影片](https://mycourses.aalto.fi/pluginfile.php/1182628/mod_resource/content/2/lect3.pdf) 它給我們的時間複雜度也是 $O(n\log n)$ 的。

於是乎！套用 Knuth-Schönhage 或是 Stehlé-Zimmermann 的每次度數剖半的分而治之法，就能夠給我們一個 $O(n\log^2 n)$ 總時間的輾轉相除法啦！

## 參考資料

* [題源參考](https://twitter.com/americaotogamer/status/1619931484760195073)、[解題討論參考](https://twitter.com/hotmanww/status/1619978031510216705)
* [Stackoverflow](https://stackoverflow.com/questions/29001275/roots-of-a-polynomial-mod-a-prime)
* [MIT 講義](http://people.csail.mit.edu/madhu/ST12/scribe/lect06.pdf)
* [芬蘭阿爾托大學 Aalto University 講義](https://mycourses.aalto.fi/pluginfile.php/1188936/mod_resource/content/2/lect5.pdf)


### 備註

* 爆搜的話使用 [Chien Search](https://en.wikipedia.org/wiki/Chien_search) 搭配預處理 [Montgomery Multiplication](https://en.wikipedia.org/wiki/Montgomery_modular_multiplication) 可以讓實作快非常非常多。雖然是 $O(np)$ 時間但是從頭到尾可以只需要加減法和位元運算。
* 我寫得爆炸亂...之後有機會再來好好整理...