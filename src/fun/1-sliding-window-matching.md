# 1 外卡匹配問題 Wildcard Matching

在經典字串匹配問題中，我們通常會被給予一份文本 $T$ (Text) 以及一個較短的型樣字串 $P$ (Pattern)。
文本與型樣原則上是取自一個字母集 $\Sigma$（例如二元集 $\{0, 1\}$、英文字母集 `[a-z]` 等，總之是個固定大小的有限集合）。
而目標便是要找出所有型樣字串 $P$ 出現在文本中的位置。

而外卡匹配問題則是引入了外卡符號 $\texttt{?}$ (wildcard)，代表該符號與任意字母都能夠匹配。
我們令 $\Sigma_\star = \Sigma\cup \{\texttt{?}\}$ 為包含外卡符號之延伸字母集。
對於兩個長度皆為 $m$ 的字串 $A, B\in \Sigma_\star^m$，我們定義 $A$ 與 $B$ **匹配**若且唯若對於所有整數 $i\in [0, m-1]$ 皆有 $A[i]=B[i]$ 或者 $A[i]$、$B[i]$ 至少一者為外卡符號。

> **外卡匹配問題**：給定長度為 $n$ 的文本 $T\in \Sigma_\star^n$ 以及長度為 $m$ 的型樣字串 $P\in \Sigma_\star^m$。
請設計一個演算法找出所有 $P$ 出現在 $T$ 中的位置。意即，找出所有註標 $i\in [0, n-m]$，使得文本中以 $i$ 開始的子字串 $T[i..i+m-1]$ 與 $P$ 匹配。


## 範例

若 $T={\texttt{ab?ac?ab?b?a?ca}}$、$P={\texttt{a?b}}$，那麼 $P$ 出現在 $T$ 中 6 次。

## 方法一：直截了當地暴力比對

這個方法其實寫起來滿有效率的呢。時間複雜度可想而知是個 $O(mn)$。

## 方法二：如果文本沒有外卡符號...

如果型樣字串也沒有外卡符號，那麼原本的問題便能夠以 KMP 或 Rabin-Karp 等經典字串匹配演算法在 $O(n+m)$ 的時間很有效率地解決。
利用這點，我們可以將型樣字串用 $P$ 以外卡符號的位置切成好幾段，找出每一段子字串出現在文本當中的位置，最後拼湊起來。這麼一來時間複雜度是 $O(n(k+1))$ 其中 $k$ 是型樣字串中外卡字元的數量。如果這個數量很少，那麼這個方法便相對地有效率。

另外也可以考慮將文本符號建立一個後綴樹 (Suffix Tree)。
並且讓型樣字串沿著該後綴樹走訪，如果遇到的字元是外卡符號，那麼便『同時』沿著所有可能的下一條路走之。
也就是說，我們要維護的是，當前型樣字串出現在後綴樹中所有可能的位置的集合。
但由於這個集合可能是後綴樹中所有的節點，因此該方法在最糟情形下是 $O(nm|\Sigma|)$ 的。


## 方法三：如果型樣字串沒有外卡符號...

考慮將文本 $T$ 以外卡符號切成許多片段 $T_0, T_1, \ldots, T_k$，其中 $k$ 是外卡符號的數量。
對於每一個片段 $T_i$ 我們想知道的是「哪些型樣字串 $P$ 的前綴是 $T_i$ 的後綴」、「哪些型樣字串 $P$ 的後綴是 $T_i$ 的前綴」、以及「哪些型樣字串 $P$ 的子字串完整地表達了 $T_i$」。把這些訊息組合起來就可以在 $O((k+1)m)$ 的時間內得到我們要的答案啦～

## 方法四：利用摺積計算個別字元「不匹配」的數量

這類滑動窗框的問題，只要把其中一邊反過來，總是可以跟摺積 (convolution) 聯想在一起。
[離散摺積](https://en.wikipedia.org/wiki/Convolution#Discrete_convolution)能做到什麼呢？
它可以用來表達形如 $C[i] := \sum_j A[-j]B[i+j]$ 的乘積和。
若 $A$ 與 $B$ 為兩個長度為 $N$ 的陣列，那麼[快速傅立葉轉換](https://en.wikipedia.org/wiki/Fast_Fourier_transform)能幫助我們在 $O(N\log N)$ 的時間計算出所有非零的 $C[i]$ 之值。

如果我們能夠透過計數，算出 $P$ 與 $T[i..i+m-1]$ 有多少個位置「不匹配」，就可以用來判定實際上有多少個子字串是匹配的啦！
首先，一個簡單的想法是，我們可以針對每一種字元 $x\in\Sigma$，計算它在文本中每個對應窗框的不匹配數量。
具體來說要怎麼做呢？若 $P[j]=x$，那麼我們便令 $A[-j]=1$，否則令 $A[-j]=0$；
相對地，若 $T[i]=x$ 或外卡符號 $\texttt{?}$ 那麼我們就令 $B[i]=0$，否則令 $B[i]=1$。
如此一來，$C[i] = \sum_j A[-j]B[i+j]$ 剛好就會等於型樣字串中的 $x$ 與文本片段 $T[i..i+m-1]$ 不匹配的位置數量啦～

於是我們就得到一個 $O(|\Sigma| n\log n)$ 的演算法。
而這個演算法還可以利用簡單的切塊技巧加速至 $O(|\Sigma| n\log m)$ 時間複雜度。

### Fischer-Paterson 演算法

只要不匹配的數量不為零，就代表 $P$ 與 $T[i..i+m-1]$ 不匹配。
因此，求出不匹配的數量並非重點，有些不匹配的數量被多算幾次其實也沒關係。
我們可以利用二分法個概念，將 $O(|\Sigma| n\log m)$ 時間複雜度的演算法加速至 $O(n\log m\log|\Sigma|)$：

不妨假設所有字母都是正整數，即 $\Sigma=\{1, 2, \ldots, |\Sigma|\}$。
在第 $k$ 次的摺積計算中，我們將 $\Sigma$ 依照該字母的二進位表達式裡面的第 $k$ 個位元之值，分成兩半，其中一邊該位元是 $0$ 另一邊該位元是 $1$。
然後只要設計出對應的 $A, B$ 陣列之值，就可以算出「該位元」不匹配的位置數量啦。

### Clifford-Clifford 演算法

上述演算法於 1978 年被提出後，其實陸續地有更有效率的 $O(n\log m)$ 演算法出現，比方說 2002 年的 [Cole-Hariharan 高維摺積演算法](https://dl.acm.org/doi/abs/10.1145/509907.509992)與 2002 年的 [Kalai 隨機演算法](https://cglab.ca/~morin/teaching/484/notes/strings/kalai.pdf)。
筆者覺得最神奇的，則是 2007 年才被發現的 Clifford-Clifford 演算法：

他們注意到『兩個字元相等若且唯若他們的差是零』

（廢話......)

但是，將他們的差「平方」以後，就可以用摺積來表達了（酷）。換句話說，在不存在外卡符號的情形下，$P$ 與 $T[i..i+m-1]$ 兩字串匹配若且唯若 $\sum (P[-j]-T[i+j])^2=0$。如果我們令外卡符號的值為 $0$，那麼 $P$ 與 $T[i..i+m-1]$ 兩字串匹配若且唯若 

$$\sum P[-j] T[i+j] (P[-j]-T[i+j])^2=0,$$

展開以後得到

$$
\sum P[-j]^3T[i+j] - 2\sum P[-j]^2T[i+j]^2 + \sum P[-j]T[i+j]^3 = 0.
$$

於是乎，我們只需要進行 3 次摺積運算（定義不同的 $A$、$B$ 陣列之值），然後把三次找到的數值加起來，就能夠分辨出哪些位置能匹配了！
而利用切塊法簡單加速後，時間複雜度也會是乾淨的 $O(n\log m)$。

## 參考資料

* Peter Clifford and Raphaël Clifford, [Simple Deterministic Wildcard Matching](https://www.cs.cmu.edu/afs/cs/academic/class/15750-s16/Handouts/WildCards2006.pdf), Information Processing Letter (IPL), 2007.
* M. Fischer and M. Paterson, [String matching and other products](http://publications.csail.mit.edu/lcs/pubs/pdf/MIT-LCS-TM-041.pdf), SIAM-AMS Complexity of Computations, 1978.
* Leetcode 10 - [Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/) 
* MPC 底下的外卡匹配 [String Matching with Wildcards in the Massively Parallel
Computation Model](https://arxiv.org/pdf/1910.11829.pdf)
* 利用位元運算加速的外卡匹配 [Fast Convolutions of Packed Strings and Pattern Matching with Wildcards](https://www.worldscientific.com/doi/abs/10.1142/S0129054117500186)