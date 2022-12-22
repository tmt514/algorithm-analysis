# 偏序集排序（七）

從前一文章裡，我們發現「只是取出最長的一條鏈」就可以做到還不錯有效率的比較排序。
那麼不斷取出更多的長鏈，說不定就能夠掌握排序的精髓了！是的，我們把這個每一次找出最長可比鏈，得到的結果稱為 **「貪婪鏈分解」（Greedy Chain Decomposition）**。

## 貪婪鏈分解

對於一個偏序集 $(P, <)$，如果我們每一次都找出最長鏈，並且將它從偏序集中移除，那麼就會得到一個分割（Partition）：$C_1, C_2, \ldots, C_k$。
其中每一個鏈 $C_i$ 是一個集合，其內部任兩元素都可比較。嚴謹地描述的話，$C_i$ 會被定義為子偏序集 $P-\bigcup_{1\le j\le i-1} C_j$ 裡面的最長鏈。
值得一提的是，這個分割方法並不唯一。如果有許多最長鏈同時存在的情形時，我們只要隨意選擇一個最長鏈就行了。
這個分割方法可以保證鏈長遞減 $|C_1| \ge |C_2| \ge \cdots \ge |C_k|$。

### 貪婪鏈分解的性質

固定一組貪婪鏈分解 $(C_1, C_2, \ldots, C_k)$。
對於 $P$ 中的任何一個鏈 $C$，每一個 $C$ 中的元素 $v$ 都會對應到某個貪婪鏈分解當中的鏈 $C_{id(v)}$，其中 $id(v)$ 是該鏈的編號。
於是呢，我們可以將鏈中的元素依照其 $id(v)$ 值由小到大重新排列。
注意到，此時排列的順序並不是根據偏序集的大小關係來排序的、而是根據在貪婪鏈分解中對應到的鏈長來排序的。

假設依照 $id(v)$ 的值排好序以後，$C$ 中元素編號依序為 $v_1, v_2, \ldots, v_{|C|}$。
此時我們能有以下性質：

### 引理 28

對所有的 $1\le j \le |C|$，都有 $|C_{id(v_j)}| \ge |C| - j + 1$。

### 證明

由於鏈中元素已經按照 $id(v)$ 的順序排序，去除掉前 $j-1$ 個元素以後，
$C-\{v_1, v_2, \ldots, v_{j-1}\}$ （暫時記作 $C'$）裡頭剩餘的所有元素通通都會在 $P-\bigcup_{1\le x\le id(j)-1} C_{x}$ （暫時記作 $P'$）裡面。
因此，根據定義，此時 $C_{id(v_j)}$ 會是 $P'$ 裡頭的最長鏈。而 $C'$ 也是 $P'$ 當中的某個鏈，於是有 $|C_{id(v_j)}| \ge |C'| = |C| - j + 1$，得證。

## 基於貪婪鏈分解的合併排序法

我們現在來探討有了這個貪婪鏈分解以後，可以怎麼把它應用在比較排序上頭。

每一條長鏈都是有全序排列的，有了很多條排好序的資料以後，我們通常會下意識地把它抓過來做合併排序法。
假設我們就按照一般的合併方法來排序：合併兩條鏈 $C_x$ 與 $C_y$ 需要使用 $|C_x|+|C_y|$ 次比較。
那麼，由於每條鏈的長度都不固定，我們可以採用非常類似霍夫曼編碼演算法的方式，每一次貪心地挑選兩條最短的鏈進行合併。
不難證明，如此進行合併後，所需要的總比較次數 $T_{合併貪婪鏈}$ 不超過

$$
T_{合併貪婪鏈} \le n + \sum_{i=1}^k |C_i| \log \frac{n}{|C_i|}\text{。}
$$

----- 

這個演算法把它寫下來會變這樣：

> * 第一步：進行貪婪鏈分解，得出 $C_1, \ldots, C_k$。
> * 第二步：重複以下操作直到只剩下一條鏈（也就是排序完畢）
>   * 每一次挑選最短的兩個鏈，然後利用合併排序法的合併步驟將它們合併起來。

### 定理 29

基於貪婪鏈分解的合併排序法，其比較次數上界為 $O(\log e(P)) + n$。這個常數可以是 6.33 左右。


### 證明大綱

詳細的證明我們明天講。
但基本上，這個證明要做下面的事情：  
* （一）我們得先證明加強版的引理 26：
$$4\log e(P) + nH(P) \ge n\log n$$
* （二）根據貪婪鏈分解定義出直鏈和多胞形 $\mathcal{C}(P)$ 上面的一個點 $z$。  
根據這個點的值，找出 $nH(P)$ 與 $T_{合併貪婪鏈}$ 之間的關聯。  
* （三）利用引理 27，先把最長鏈挑出來，然後說明剩下的比較次數可以被 $O(\log e(P))$ 處理掉。

然後就得證啦！