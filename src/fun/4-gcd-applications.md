# 輾轉相除法的應用 Applications of Euclidean Algorithm

<!-- toc -->

## 關於輾轉相除法

歐幾里得的[輾轉相除法](https://zh.wikipedia.org/wiki/%E8%BC%BE%E8%BD%89%E7%9B%B8%E9%99%A4%E6%B3%95)可謂之最古早被記錄下來的演算法。對於任何兩個正整數 $a, b$，輾轉相除法能夠幫助我們快速找到最大公因數 $d=\gcd(a, b)$。即最大的正整數 $d$ 同時整除 $a$ 與 $b$。利用最大公因數的特性 $\gcd(a, b) = \gcd(b, |a-b|)$ 我們能夠設計出以下超級沒有效率的輾轉相除法：

```rust
# fn abs(a: i32) -> i32 { if a < 0 {-a} else {a} }
fn gcd(a: i32, b: i32) -> i32 {
  match a {
    0 => b,
    _ => gcd(b, abs(a-b)),
  }
}
# fn main() {
#   let a = 123;
#   let b = 456;
#   println!("gcd({a}, {b}) = {}", gcd(a, b));
# }
```

如果我們被允許使用乘法與除法，那麼我們可以利用取餘數的方法，避免 $a, b$ 兩數差距懸殊時多餘的重複計算。
其正確性當然是源自 $\gcd(a, b) = \gcd(b, (a\bmod b))$。

```rust
fn gcd(a: i32, b: i32) -> i32 {
  match (a, b) {
    (0, _) => b,
    (_, 0) => a,
    (_, _) => gcd(b, a%b),
  }
}
# fn main() {
#   let a = 514;
#   let b = 999;
#   println!("gcd({a}, {b}) = {}", gcd(a, b));
# }
```

要分析輾轉相除法的 $O(\log (a+b))$ 時間複雜度，可以透過以下觀察：

### 觀察
原本之輸入 $(a, b)$ 經過遞迴兩次以後得到的 $(a'', b'')$，必定有 $a''+b'' < \frac23(a+b)$。

### 觀察的證明

對於輸入 $(a, b)$，我們令第一次遞迴時傳入的參數是 $(a', b')$、第二次遞迴時傳入的參數為 $(a'', b'')$。
顯然運算過程中兩數之和不會變大，即 $a''+b''\le a'+b' \le a+b$。

* 若 $a \ge b$，那麼第一次遞迴呼叫時：
  * 當 $b > a/2$ 時我們有 $(a\bmod b) = a - b$；  
  於是 $a'+b' = b + (a-b) = a < \frac23(a+b)$
  * 當 $b \le a/2$ 時我們有 $(a\bmod b) < b$；  
  於是 $a'+b' < b + b \le \frac23(a+b)$。
* 若 $a < b$，那麼第一次遞迴呼叫相當於兩數交換，第二次遞迴呼叫時就能套用上述分析得證了。

#### 備註
看到這個『嚴格小於』就知道，這樣的分析其實是很不緊的。事實上，我們能證明遞迴次數不超過 $2+\lceil\log_\varphi\max(a, b)\rceil$ 次，其中 $\varphi\approx 1.618...$ 是黃金比例。至於這費事的證明就留給聰明的讀者您囉～

### The Binary GCD Algorithm

使用乘除法其實相當地昂貴，實作上如此、從計算理論中的 circuit complexity 角度來看[更是如此](https://www.csa.iisc.ac.in/~chandan/courses/arithmetic_circuits/notes/lec5.pdf)。因此，我們能提出一個兼具理論與實作上相當有意思的問題：是否存在僅使用 $O(\log (a+b))$ 次加減法及位元計算 (特別地指『除以 2』這種右移運算) 就能算出最大公因數呢？答案是可行的。利用到當 $a, b$ 皆為偶數時，$\gcd(a, b)=2\gcd(a/2,b/2)$、以及其中一者為偶數時可以直接把它除以 $2$，就能設計出一個理想的輾轉相除法。

```rust
# use std::cmp::min;
# fn abs(x: i32) -> i32 { if x < 0 {-x} else {x} }
fn binary_gcd(a: i32, b: i32) -> i32 {
  match (a, b, a%2, b%2) {
    (0, ..) | (_, 0, ..) => a+b,
    (.., 0, 0) => 2*binary_gcd(a/2, b/2),
    (.., 0, _) => binary_gcd(a/2, b),
    (.., _, 0) => binary_gcd(a, b/2),
    (.., _, _) => binary_gcd(abs(a-b), min(a, b)),
  }
}
# fn main() {
#   let a = 514;
#   let b = 999;
#   println!("gcd({a}, {b}) = {}", binary_gcd(a, b));
# }
```

#### 備註

Knuth 在他撰寫的《The Art of Computer Programming Vol. 2》巨著中指出，這個二元歐幾里德演算法，被學者們公認由 Silver 和 Terzian (1961) 與 Stein (1967) 這兩組人馬相繼提出。不過，Knuth 提及，相同的演算法其實可以追溯到漢代的《九章算術》，在[維基文庫](https://zh.wikisource.org/wiki/%E4%B9%9D%E7%AB%A0%E7%AE%97%E8%A1%93)找到的原文是這樣說的：

『術曰：可半者半之；不可半者，副置分母、子之數，以少減多，**更相減損**，求其等也。以等數約之。』

文中提及可以用更相減損的方式化簡 $\frac{49}{91}$ 這個分數，翻譯成現代演算法語言正是二元歐幾里德演算法！更多有趣的故事可以參考：

* 澳洲國立大學的 Richard P. Brent 教授撰寫的[《Twenty year's analysis of the Binary Euclidean Algorithm》](https://maths-people.anu.edu.au/~brent/pd/rpb183pr.pdf) 以及[《Analysis of Binary Euclidean Algorithm》](https://apps.dtic.mil/sti/pdfs/ADA029130.pdf)。
* 國家圖書館的演講[東西數學風格比較：《九章算術》vs.《幾何原本》](https://www.ncl.edu.tw/downloadfile2_297_333.html)，台師大的洪萬生教授主講。
* 台大 2020 年 DSA 課程作業一 [https://www.csie.ntu.edu.tw/~htlin/course/dsa20spring/hw1/](https://www.csie.ntu.edu.tw/~htlin/course/dsa20spring/hw1/)

### Stehlé-Zimmermann 演算法 (無細節)

你可能會覺得，上面描述的輾轉相除法，已經可以做到 $O(\log(a+b))$ 時間，應該已經很快了吧！其實不然。這邊的『時間複雜度』，指的是在特定計算模型底下對該演算法的分析。而我們在這個計算模型中，假設了加減法與位元運算可以在常數時間內做到。這對於一般的 32-位元、或是 64-位元整數來說是成立的。但是當數字變得超大，例如 $10^5$ 位元的時候，現實與理論就會脫勾：因為我們沒有辦法在常數時間內精確地算出任意兩個整數的差。

若計算 $\kappa$ 位元整數的加減法，需要花費 $O(\kappa)$ 的時間，那麼前面提及的二元歐幾里德演算法，所花費的時間會是 $O(\kappa^2)=O(\log^2(a+b))$。Knuth 與 Schönhage 在 1971 年，在這個較為貼近現實的計算模型中，相繼提出了更快速的歐幾里德演算法，其時間複雜度分別為 $O(\kappa\log^5\kappa\log\log\kappa)$ 與 $O(\kappa\log^2\kappa\log\log \kappa)$。Knuth 與 Schönhage 演算法在實作或證明上都有一定程度的複雜性。

而 2004 年由兩位法國電腦科學家 [Damien Stehlé](http://perso.ens-lyon.fr/damien.stehle/) 與 [Paul Zimmermann](https://en.wikipedia.org/wiki/Paul_Zimmermann_(mathematician)) 提出了將 Knuth-Schönhage 演算法簡化後的 [Generalized Binary Euclidean Algorithm](https://link.springer.com/chapter/10.1007/978-3-540-24847-7_31)([勘誤](https://perso.ens-lyon.fr/damien.stehle/BINARY.html))，其時間複雜度也是 $O(\kappa\log^2\kappa\log\log \kappa)$，但號稱無論在實作或證明上都比 Knuth-Schönhage 演算法簡單一些。

詳情可以參考[倫敦大學 Martin R. Albrecht 教授](https://malb.io/)的[網誌](https://martinralbrecht.wordpress.com/2020/03/21/the-approximate-gcd-problem/)。

## 常見且重要的應用

* 擴展的歐幾里德演算法 Extended Euclidean Algorithm。這個擴展的輾轉相除法可以用來解出[貝祖定理 (Bézout's Lemma)](https://zh.wikipedia.org/wiki/%E8%B2%9D%E7%A5%96%E7%AD%89%E5%BC%8F)需要的整數係數。這在解決一類[線性丟番圖問題](https://math.libretexts.org/Courses/Mount_Royal_University/MATH_2150%3A_Higher_Arithmetic/5%3A_Diophantine_Equations/5.1%3A_Linear_Diophantine_Equations)是相當有用的，而且在程式比賽中也常常出現！除了[維基百科](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)以外，還可以參考這篇[林禾堃同學的文章](https://hackmd.io/@Koios/rJ_lER719)、以及 [CP-Algorithms](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#algorithm)。


```rust
# fn gcd(a: i32, b: i32) -> i32 {
#   match (a, b) {
#     (0, _) => b,
#     (_, 0) => a,
#     (_, _) => gcd(b, a%b),
#   }
# }
/// 這個函數會回傳兩個係數 x 和 y 使得 x*a + y*b = gcd(a, b)。
fn ext_gcd(a: i32, b: i32) -> (i32, i32) {
  match (a, b) {
    (0, _) => (0, 1),
    (_, 0) => (1, 0),
    (_, _) => {
      let (x, y) = ext_gcd(b, a%b); // x*b + y*(a%b) = GCD
      (y, x-y*(a/b))                // ?*a + ?*b     = GCD
    },
  }
}
# fn main() {
#   let a = 514;
#   let b = 999;
#   let (x, y) = ext_gcd(a, b);
#   println!("({x}) * {a} + ({y}) * {b} = {}", gcd(a, b));
# }
```

* 擴展的歐幾里德演算法可以被運用在尋找模 $p$ 底下的乘法反元素，這在比如 [RSA 等加密演算法](https://crypto.stackexchange.com/questions/22490/rsa-key-generation-how-is-multiplicative-inverse-computed) 以及[中國剩餘定理](https://zh.m.wikipedia.org/wiki/%E4%B8%AD%E5%9B%BD%E5%89%A9%E4%BD%99%E5%AE%9A%E7%90%86)裡頭相當有用。
* 此外，輾轉相除法在[因數分解](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm)等數論演算法來說也佔有一席之地。

## 應用問題 1：倒水問題

<div style="display:flex;flex-direction:column;justify-content:center;align-items:center;">
<img src="https://i.imgur.com/BnbQoCA.png" style="max-width:400px" alt="倒水問題在遊戲中的範例"/>
<span>▲倒水問題是個很經典的益智遊戲。圖片節錄自《地下城物語》這款遊戲。</span>
</div>

## 應用問題 2：夾在中間的分數

## 應用問題 3：