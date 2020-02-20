# 逆序數對

### 定義

給定一個序列 $A=(a_1, a_2, \ldots, a_n)$。我們說一個數對 $(i, j)$, $1\le i < j\le n$ 是一個它的**逆序數對 (Inversion)**，若 $a_i > a_j$。
而滿足條件的數對總數，我們寫作 $\mathrm{Inv}(A)$。

-----

有了這個定義以後，我們就可以討論當我們限制「每次只能交換相鄰兩數」的排序方法的效率了！

### 引理 4

泡沫排序法、雞尾酒排序法、與插入排序法當中，交換數對的次數皆相同，而且恰好是 $\mathrm{Inv}(A)$。

### 證明

由於交換的方式都是僅交換相鄰兩個數字，而且僅有在 $a_i > a_{i+1}$ 的時候才交換的。因此每一次交換後逆序數對總數恰好減 1。
此外，逆序數對數量為零，等價於序列已排好序。故得證。

### 係理 5

插入排序法的時間複雜度為 $O(n + \mathrm{Inv}(A))$。（證明略）

### 係理 6

存在一筆輸入，使得泡沫排序法的時間複雜度為 $\omega(n + \mathrm{Inv}(A))$。
即，對於該輸入，泡沫排序法需要 $\Theta(n^2)$ 的時間，但是 $\mathrm{Inv}(A)$ 很小，在本例中 $\mathrm{Inv}(A) = O(n)$。

### 證明

該輸入為 $(2, 3, \ldots, n, 1)$，此時要把 $1$ 慢慢晃到最前面，需要歷經 $n-1$ 次 while 迴圈。
注意到這個例子在雞尾酒排序法當中，仍是有效率的。

### 係理 7

1. 泡沫排序法的時間複雜度為 $O(n + n\cdot \mathrm{Inv}(A))$，而且存在一些輸入符合這個時間複雜度。
2. 雞尾酒排序法的時間複雜度為 $O(n + n\cdot \sqrt{\mathrm{Inv}(A)})$，而且存在一些輸入符合這個時間複雜度。

### 證明

第一部分還算單純：每一次 for-loop 之中，如果有 swap 就會讓逆序數對的數量減少 1。
因此泡沫排序法中 while 迴圈的執行次數至多是 $\mathrm{Inv}(A)$ 次。由係理 6 也可以得知這個時間複雜度是緊的。

第二部分比較有意思，而且證明也相對複雜一些。注意到每次從左往右邊的 for-loop，拿來比較的 $A[i]$ 是會越來越大的。
我們定義「上方階梯」為一個註標序列 $1 = u_1 < u_2 < \ldots < u_x\le n$，代表每次由左往右邊看到的越來越大的當前極大值們。
不難發現在此階段的 swap 次數恰好就是 $n-x$ 次。
同理我們可以定義「下方階梯」為另一個註標序列 $1 \le d_y < d_{y-1} < \ldots < d_1 = n$，代表每次從右往左看到的越來越小的極小值們。
由於是雞尾酒排序法，從右往左刷的 swap 次數也恰好是 $n-y$ 次。


我們的目標，是要證明每波操作以後，逆序數對總數至少會降 $\sqrt{\mathrm{Inv}(A)}$ 這麼多。
由此可以推得至多 $O(\sqrt{\mathrm{Inv}(A)})$ 次迴圈就可以把所有數值排好順序了。
如果 $n-x=\Omega(n)$ 或 $n-y=\Omega(n)$，那麼顯然 $n = \Omega(\sqrt{\mathrm{Inv}(A)})$。

我們現在來研究逆序數對總數與 $n-x, n-y$ 之間的關係。我們宣稱

$$
\mathrm{Inv}(A) \le (n-x)^2 + (n-y)(n-x) + (n-y)^2 \le ((n-x) + (n-y))^2\text{。}
$$
由上式可知，一個 while-loop 內來回刷過一次之後，發生的置換次數 $(n-x)+(n-y)$ 次至少有 $\sqrt{\mathrm{Inv}(A)}$ 這麼多次！

要怎麼證明上面這個式子呢？首先可以將所有的逆序數對分成：(1) 兩個註標都不在上方階梯；(2) 兩個註標都不在下方階梯；或 (3) 一個註標在上方階梯、另一個註標在下方階梯。
要注意的是，不可能有兩個註標在上方階梯（或下方階梯）的情形——因為階梯本身就不會出現逆序數對。
此外，也不可能有一個註標同時出現在上方階梯與下方階梯、並且另一個註標同時不出現在階梯上——這是因為，若一個註標同屬於上下階梯的話，不可能產生與之相關的逆序數對。
因此，(1) 可以得出 $(n-x)^2$，(2) 可以得出 $(n-y)^2$，(3) 由於註標不能同時出現在兩階梯，因此可以得到上界 $(n-y)(n-x)$。


考慮函數 $f(k) = k-\sqrt{k}$，我們想要知道的就是迭代多少次以後，$f(\cdots f(f(k))\cdots)$ 的值會變得夠小。
令 $k=t^2$。
由於 $t^2-t \ge (t-1)^2$。
注意到迭代兩次以後 $f(f(k)) = k-\sqrt{k}-\sqrt{k-\sqrt{k}} \le t^2 - t - (t-1) = (t-1)^2$。
因此，只要迭代 $O(t)$ 次以後，就可以回到常數囉。因此，需要的 while-loop 迭代次數至多只要 $O(\sqrt{\mathrm{Inv}(A)})$ 次。

-----

什麼樣的輸入需要讓雞尾酒排序法花到 $\Theta(n+n\sqrt{\mathrm{Inv}(A)})$ 這麼久呢？
可以試試看把 $1$ 到 $n$ 依序排好，然後把前 $k$ 個數字反轉過來，你就會得到一個逆序數對個數為 $k(k-1)/2$、而且時間複雜度是 $O(nk)$ 的結論了。

## 小結論

我們今天透過逆序數對的方法來分析氣泡排序法、雞尾酒排序法以及插入排序法的優劣。

### 參考資料

* https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)
* https://math.stackexchange.com/questions/2998546/sort-an-array-given-the-number-of-inversions