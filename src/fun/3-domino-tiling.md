# 3 骨牌鋪磚問題 Domino Tilings

> **骨牌鋪磚問題**：給定兩個整數 $m, n$，並考慮大小為 $m\times n$ 的矩形棋盤。其中某些格子有障礙物，不能放置骨牌。請問有多少種方法使用 $1\times 2$ 骨牌能恰好鋪滿這個 $m\times n$ 的棋盤所有不含障礙物的地方？

## 範例

若 $m=3$、$n=4$，且該矩形沒有任何障礙物，那麼答案是 $11$。 

<script>
var table = [];
var M = 6, N = 12;
var NONE = -514;
var BadSpotPairs = 6;

function fill_table_with_some_answer() {
  function dfs(x, y) {
    if (x >= M) return true;
    if (y >= N) {
      return dfs(x+1, 0);
    }
    if (table[x][y] !== NONE) {
      return dfs(x, y+1);
    }
    // now table[x][y] === 0
    var check_horizontal = function(x, y) {
      if (y+1<N && table[x][y+1] === NONE) {
        table[x][y] = 0;
        table[x][y+1] = 1;
        if (dfs(x, y+2) === true) return true;
        table[x][y] = table[x][y+1] = NONE;
      }
      return false;
    };
    var check_vertical = function(x, y) {
      if (x+1<M && table[x+1][y] === NONE) {
        table[x][y] = 2;
        table[x+1][y] = 3;
        if (dfs(x, y+1) === true) return true;
        table[x][y] = table[x+1][y] = NONE;
      }
      return false;
    };
    if (Math.random() < 0.5) {
      if (check_horizontal(x, y)) return true;
      if (check_vertical(x, y)) return true;
    } else {
      if (check_vertical(x, y)) return true;
      if (check_horizontal(x, y)) return true;
    }
    return false;
  };
  return dfs(0, 0);
}

function generateboard() {
  var k = Math.floor(Math.random() * BadSpotPairs);
  do {
    table = [];
    for(i=0;i<M;i++) {
      table.push([]);
      for(j=0;j<N;j++) table[i].push(NONE);
    }
    var blk=[],wte=[];
    var idx;
    for(i=0;i<M;i++)for(j=0;j<N;j++) if((i+j)%2===0) blk.push([i,j]); else wte.push([i,j]);
    for(i=0;i<k;i++) {
      idx = Math.floor(Math.random()*(blk.length-i)) + i;
      [blk[idx], blk[i]] = [blk[i], blk[idx]];
      idx = Math.floor(Math.random()*(wte.length-i)) + i;
      [wte[idx], wte[i]] = [wte[i], wte[idx]];
      table[blk[i][0]][blk[i][1]] = -1;
      table[wte[i][0]][wte[i][1]] = -1;
    }
  } while (!fill_table_with_some_answer());
}

function randomrotate() {
  for(i=0;i<M;i++) for(j=0;j<N;j++) if(table[i][j] !== -1) table[i][j] = NONE;
      fill_table_with_some_answer();
    return;
  //   var rotate_times=4000;
  // while (rotate_times > 0) {
  //   rotate_times -= 1;
  //   var place=[];
  //   for(i=0;i+1<M;i++) for(j=0;j+1<N;j++) {
  //     if(table[i][j]===0 && table[i+1][j]===0 && table[i][j+1]===1 && table[i+1][j+1]===1) place.push([i, j]);
  //     if(table[i][j]===2 && table[i][j+1]===2 && table[i+1][j]===3 && table[i+1][j+1]===3) place.push([i, j]);
  //   }
  //   if (place.length === 0) {
  //     for(i=0;i<M;i++) for(j=0;j<N;j++) if(table[i][j] !== -1) table[i][j] = NONE;
  //     fill_table_with_some_answer();
  //     break;
  //   }
  //   var idx = Math.floor(Math.random()*place.length);
  //   var x = place[idx][0], y = place[idx][1];
  //   if(table[x][y]===0) { table[x][y]=table[x][y+1]=2; table[x+1][y]=table[x+1][y+1]=3; }
  //   else  { table[x][y]=table[x+1][y]=0; table[x][y+1]=table[x+1][y+1]=1;}
  // }

}

var w = 30;
var corner=4;
var shrink=2;
var q_cornerWS = 'q '+ (-corner) +',0' + ' ' + (-corner) + ',' + (corner);
var q_cornerSW = 'q '+ '0,' + (corner) + ' ' + (-corner) + ',' + (corner);
var q_cornerES = 'q '+ (corner) + ',0' + ' ' + (corner) + ',' + (corner);
var q_cornerSE = 'q '+ '0,' + (corner) + ' ' + (corner) + ',' + (corner);
var q_cornerEN = 'q '+ (corner) + ',0' + ' ' + (corner) + ',' + (-corner);
var q_cornerNE = 'q '+ '0,' + (-corner) + ' ' + (corner) + ',' + (-corner);

function path2d_domino(i, j, direction, canvasoffset) {
  // (i, j): upper-left corner of the piece.
  // direction: 0 for (i, j) -- (i, j+1); 2 for (i, j) -- (i+1, j).
  // returns a path2d string.
  canvasoffset ||= {x: w/2, y: w/2};
  var x = w*i;
  var y = w*j;
  var s = ' M ' + (canvasoffset.x) + ',' + (canvasoffset.y);
  if (direction === 0) {
    s += ' m ' + (y+w) + ',' + (x+shrink);
    s += ' h ' + (-w+corner+shrink) + q_cornerWS + ' v' + (w-shrink*2-corner*2) + q_cornerSE + ' h ' + (w-corner-shrink);
    s += ' m ' + (0) + ',' + (-w+shrink*2);
    s += ' h ' + (w-corner-shrink) + q_cornerES + ' v' + (w-shrink*2-corner*2) + q_cornerSW + ' h ' + (-w+corner+shrink); 
  } else {
    s += ' m ' + (y+shrink) + ',' + (x+w);
    s += ' v ' + (-w+corner+shrink) + q_cornerNE + ' h' + (w-shrink*2-corner*2) + q_cornerES + ' v ' + (w-corner-shrink);
    s += ' m ' + (-w+shrink*2) + ',' + (0);
    s += ' v ' + (w-corner-shrink) + q_cornerSE + ' h' + (w-shrink*2-corner*2) + q_cornerEN + ' v ' + (-w+corner+shrink);
  }
  return s;
}

function path2d_cross(i, j, canvasoffset) {
  canvasoffset ||= {x: w/2, y: w/2};
  var rs = '';
  var x=w*i;
  var y=w*j;
  rs += ' M ' + (y+w/4+canvasoffset.x) + ',' + (x+w/4+canvasoffset.y);
  rs += ' l ' + (w/2) +',' + (w/2);
  rs += ' m ' + (0) + ',' + (-w/2);
  rs += ' l ' + (-w/2) + ',' + (w/2);
  return rs;
}

function drawcanvas() {
  w=30;
var can = document.getElementById('canvas1');
var ctx = can.getContext('2d');
ctx.reset();
ctx.fillStyle='rgb(255,255,255)';
var bg = new Path2D();
bg.rect(0, 0, w*N+w, w*M+w);
ctx.fill(bg);
var s = '';
var reds = [];
var i, j;
for(i=0;i<M;i++) for(j=0;j<N;j++) {
  if(table[i][j]===0) {
    s += path2d_domino(i, j, 0);
  } else if (table[i][j] === 2) {
    s += path2d_domino(i, j, 2);
  } else if (table[i][j]===-1) {    
    reds.push(path2d_cross(i, j));
  }
}
var path = new Path2D(s);
ctx.stroke(path);
for (rs of reds) {
  ctx.stroke(new Path2D(rs));
}
}
</script>

<button onClick="javascript:resetboard(1)">隨意產生一種 $6\times 12$ 棋盤</button>
<button onClick="javascript:resetboard(0)">隨意更新一種骨牌覆蓋</button>

<canvas id="canvas1" width="600" height="220"></canvas>

## 方法零：空棋盤的公式解

$$\prod_{j=1}^m\prod_{k=1}^n \left(4\cos^2\frac{j\pi}{m+1}+4\cos^2\frac{k\pi}{n+1}\right)^{1/4}$$

這是個非常優雅的數學解，一生請至少要想通過一次它的[證明](./3a-domino-tiling-proof.md)！
不過呢，若依此公式實際計算該數值，則這個方法存在著滿滿的精確度問題，大家不妨實作看看、細細體會。

## 方法一：枚舉答案系列

我們可以使用基於深度優先搜索 (Depth First Search) 的試誤法：
每一次找一個還沒有被填滿的空格，然後決定要讓骨牌蓋直的還是橫的，如果能放就接著遞迴下去。
由於每次做決策會覆蓋兩格，因此遞迴深度不超過 $mn/2$、且遞迴樹上每個節點最多只會分出兩個子問題。
因此，我們得知整個遞迴樹上的節點數量為 $O(2^{mn/2})$。

但是，這麼一來我們就能聲稱時間複雜度是 $O(2^{mn/2})$ 了嗎？可能會不夠充分。
問題出在哪裡呢？原因是在每一次遞迴呼叫時，『找一個還沒被填滿的空格』這個步驟的執行時間可能不是固定的，最壞情形甚至可能是 $O(mn)$。
好加在，若此時我們使用一個 hashmap + linked list 來存放當前沒有被覆蓋的所有格子座標，就能夠保證每次找到一個空格需要的時間是 $O(1)$。
於是就能正確地達到 $O(2^{mn/2})$ 的時間複雜度啦。

## 分法一之二：預判剪枝

要**搜**，就要好好地搜。到達一個子問題（也就是鋪到一半的棋盤）時，若有某種方法幫我們快速判斷剩下的盤面是否有解，那麼我們就可以透過預判剪枝的方法，將時間複雜度由 $O(2^{mn/2})$ 降到 $O(TDK)$ 時間，其中 $T$ 是判斷盤面是否有解的時間複雜度、$D=O(mn)$ 是遞迴深度、$K$ 則是鋪磚方法的總數。
至於 $TDK$ 和 $2^{mn/2}$ 之間要如何比較呢？這就要端看『判斷剩餘盤面是否有解』的演算法、與『實際鋪滿盤面的解數』了。

若我們使用最陽春的二分圖最大匹配演算法來判斷是否有解，那麼我們有 $T=O(mn\sqrt{mn})$。
此外，若 $m=n$ 的時候，依照 Kasteleyn、Fisher 以及 Temperley 等人提出的算式推導，可以推知鋪滿盤面的解數大約是 $c^{mn/2}$，其中 $c = e^{2G/\pi} \approx 1.79162\ldots$ 而這邊的數值 $G$ 是[卡塔蘭常數 (Catalan constant)](https://en.wikipedia.org/wiki/Catalan%27s_constant) $\frac{1}{1^2}-\frac{1}{1^3}+\frac{1}{1^5}-\frac{1}{1^7}+\cdots\approx 0.915965\ldots$。

於是，我們的演算法就從 $O(2^{mn/2})$ 加速到 $O^*(1.79163^{mn/2})$ 啦～

## 方法二：動態規劃系列

動態規劃 (dynamic programming) 是眾多演算法典範 (algorithmic paradigm) 當中數一數二重要的一種解題典範。
其核心概念首先在於正確地定義子問題、然後找出原問題與子問題之間的遞迴關係 (與邊界條件)、並且找出正確的解題順序。
說得更直接一些，便是將所有曾經計算過的子問題通通記錄下來，並重複利用以加速計算的一種方法。

而將動態規劃應用在鋪磚問題時，則會是一個訓練『子問題設計』很好的練習題目。
比方說，我們可以考慮以下這樣的想法。
假若我們硬生生地考慮矩形棋盤的左邊 $k$ 行，那麼完全身處左邊 $k$ 行之中的骨牌們會形成一種邊緣不完整的鋸齒狀棋盤。
我們觀察到，由於我們使用的是 $1\times 2$ 大小的骨牌進行鋪磚，因此鋸齒的邊界，在每一列只有可能是平的或凹進去恰好一格。
其邊界情形只有 $2^m$ 種（其中 $m$ 是棋盤的列數）。
於是一個有趣的想法誕生了：我們可以考慮對於任意鋸齒的形狀 $(k, \text{邊界長相})$ 定義成『子問題』，並且令 $dp(k, \text{邊界長相})$ 為使用 $1\times 2$ 骨牌鋪滿這個鋸齒狀棋盤的方法數。我們要的答案就是 $dp(n, \text{整條邊界平的})$ 之值。剩下來要考慮的，便是子問題 (或狀態) 的轉移了。



<button onClick="javascript:resetboard(0)">隨意更新一種骨牌覆蓋</button>
<button onClick="javascript:resetboard(514)">固定邊界後更新一種骨牌覆蓋</button>
<button onClick="javascript:change_cuttingIndex()">隨意換一個 $k$</button>

<canvas id="canvas2" width="600" height="220"></canvas>
<script>
  var cuttingIndex = 8;
  var boundaryStateValue = 0;
  var boundaryStateExpression = [];
  function partiallyrandom() {
    var i, j;
    for (i = 0; i < M; i++) for (j = 0; j < N; j++) {
      if (table[i][j]===-1) continue;
      if (j >= cuttingIndex) continue;
      if (table[i][j]===0 && j + 1 >= cuttingIndex) continue;
      if (table[i][j]===0) { table[i][j]=table[i][j+1]=NONE; }
      if (table[i][j]===2) { table[i][j]=table[i+1][j]=NONE; }
    }
    fill_table_with_some_answer();
  }
  function path2d_get_contour() {
    var s = ' M ' + (w/2) + ',' + (w/2);
    boundaryStateValue = 0;
    boundaryStateExpression = [];
    for(i=0;i<M;i++) {
      if (table[i][cuttingIndex-1] === 0) {
        s += ' L ' + (w/2+cuttingIndex*w-w) + ',' + (w/2+i*w);
        s += ' v ' + (w);
      } else {
        s += ' L ' + (w/2+cuttingIndex*w) + ',' + (w/2+i*w);
        s += ' v ' + (w);
        boundaryStateValue += (1<<i);
        boundaryStateExpression.push('2^{' + (i) + '}');
      }
    }
    s += ' L ' + (w/2) + ',' + (w/2 + M*w);
    s += 'z';
    return s;
  }
  function drawcanvas2() {
    w=30;
    var can = document.getElementById('canvas2');
    var ctx = can.getContext('2d');
    ctx.reset();
    ctx.fillStyle='rgb(255,255,255)';
    var bg = new Path2D();
    bg.rect(0, 0, w*N+w, w*M+w);
    ctx.fill(bg);
    var i, j, s;
    var DEFAULT_STROKE_STYLE = `#000000`;
    var DEFAULT_LINE_WIDTH = 1;
    var offsetx = 0, offsety = w/4;
    ctx.fillStyle = `rgb(233,233,233)`;
    for (i = 0; i < M; i++) for (j = 0; j < N; j++) {
      if (j>=cuttingIndex) {
        ctx.strokeStyle=`rgb(233,233,233)`;
      } else {
        ctx.strokeStyle=DEFAULT_STROKE_STYLE;
      }
      if (table[i][j] === 0) {
        s = path2d_domino(i, j, 0);
        var p = new Path2D(s);
        if (j+1 >= cuttingIndex) {
          ctx.strokeStyle=`rgb(233,233,233)`;
          ctx.fill(p);
        }
        ctx.stroke(p);
      } else if (table[i][j] === 2) {
        s = path2d_domino(i, j, 2);
        var p = new Path2D(s);
        if (j >= cuttingIndex) ctx.fill(p);
        ctx.stroke(p);
      } else if (table[i][j] === -1) {
        s = path2d_cross(i, j);
        ctx.stroke(new Path2D(s));
      }
    }
    //var sp = ' M ' + (w*cuttingIndex) + ',' + (w/4);
    //sp += ' l ' + (0) + ',' + (M*w+w/2);
    ctx.strokeStyle="rgb(255,0,0)";
    ctx.lineWidth=3;
    //ctx.stroke(new Path2D(sp));
    ctx.stroke(new Path2D(path2d_get_contour()));
    ctx.strokeStyle=DEFAULT_STROKE_STYLE;
    ctx.lineWidth=DEFAULT_LINE_WIDTH;
  }
</script>

### 狀態壓縮

『邊界長相』是個難以言喻的東西。因此，在實作前我們會試著將它變成可以操作的形式。對這題來說算是相對簡單的：我們可以令平的邊緣為 $1$、凹進去的邊緣為 $0$。
這麼一來，『邊界長相』就可以被一個介於 $0$ 到 $2^m-1$ 之間的整數來表示了。以整數形式（通常是二進位）精簡地描述動態規劃的子問題的技巧，通常我們稱之為狀態壓縮。

以上面的圖樣為範例的話，若將每一橫列之狀態依序以 $2^0, 2^1, \ldots, 2^{m-1}$ 表示，那麼我們可將該子問題描述為 <span id="state_encode">$(k=, \text{邊界}=)$</span>。

<script>
  function updatestateencode() {
    var spandom = window.document.querySelector('#state_encode');
    if (boundaryStateExpression.length > 0)
      spandom.innerHTML = '$(k=' + (cuttingIndex) + ',邊界=' + (boundaryStateExpression.join('+')) + '=' + (boundaryStateValue) + ')$';
    else
      spandom.innerHTML = '$(k=' + (cuttingIndex) + ',邊界=0)$';
    if (window.MathJax !== undefined)
      MathJax.Hub.Typeset(spandom);
  }
  function change_cuttingIndex() {
    cuttingIndex = Math.floor(Math.random() * (N-1)) + 2;
    drawcanvas2();
    updatestateencode();
  }
</script>

### 狀態的轉移與時間複雜度分析

如果我們查看第 $k$ 行、邊緣沒有凹進去的那些地方的骨牌們，則它們可能是橫的或直的。
若我們將這些邊界位置全部放置橫著的骨牌，那麼該情形下的骨牌總數是 $dp(k-1, 2^m-1-邊界)$（因為拿掉這些骨牌後，剛好形成一個少了一行、且邊界鋸齒剛好與原本的鋸齒形狀互補的長相）。若有些邊界地方被放置了豎著的骨牌，那麼有兩種方式可以考慮這些情形：

* 第一種『暴力枚舉』：我們可以再次枚舉所有在該行放置若干豎著的骨牌的方法數，由於放法計數至多與費氏數列相同，因此至多有 $O(\phi^n)$ 種情形需要枚舉。
結合狀態總數 $O(n2^m)$，從而得出整體動態規劃之時間複雜度為 $O(n2^m\phi^n)$。 (備註：這個時間複雜度比暴力法還糟糕呢！)
* 第二種『另一層動態規劃』：如果只針對第 $k$ 行的話，總是可以考慮『最後一個出現豎著放的骨牌的位置』。因此，我們可以拓展原本的子問題定義：令 $dp(k, 邊界, r)$ 表示『把 $(k, 邊界)$ 這個形狀填滿骨牌時，在第 $k$ 行裡頭**允許**出現豎著放的骨牌位置不得超過第 $r$ 列』的時候，有幾種放置 $1\times 2$ 的骨牌方法數。
在這樣的情形下，轉移就可以變成 $O(1)$ 時間的（因為只要考慮第 $k$ 行第 $r$ 列的骨牌到底要橫著還是豎著放就可以；且當 $r=0$ 的時候可以得知所有邊界處都是橫著放骨牌，就可以一次退一排了）。於是整體時間複雜度變成了 $O(mn2^m)$。


## 方法二之二：破碎化的拼貼

與其一口氣關注一整行，如果一次只考慮一格的動態規劃設計，在遞迴轉移的時候反而變得更單純些，實作上也變得相當精簡。這個方法的時間複雜度也是 $O(mn2^m)$。
由於筆者稍微偷懶了一下的關係，不介意的話還請大家參考筆者曾經寫過的 [透過鋪磚塊問題來看看動態規劃可運用之處！](https://ithelp.ithome.com.tw/articles/10227405) 鐵人賽文章。

## 方法三：使用圖論轉化問題

我們可以使用圖論的想法來解決這個問題！
簡單來說，我們可以讓每一個棋盤上的沒有障礙物的格子都變成圖上的一個點、並且將相鄰的格子連上一條邊。
這樣建立出來的圖為 $G$，其點數恰好為空格的數量、而每條邊就對應著可以放置骨牌的位置。
一個成功的骨牌鋪法，便對應了圖 $G$ 上面的一組**完美匹配** (perfect matching)。

<canvas id="canvas3" width="600" height="220"></canvas>
<script>
  function drawcanvas3() {
    w=30;
var can = document.getElementById('canvas3');
var ctx = can.getContext('2d');
ctx.reset();
ctx.fillStyle='rgb(255,255,255)';
var bg = new Path2D();
bg.rect(0, 0, w*N+w, w*M+w);
ctx.fill(bg);
ctx.strokeStyle=`rgb(244,244,244)`;
ctx.fillStyle=`rgb(244,244,244)`;
var s = '';
var reds = [];
var i, j;
for(i=0;i<M;i++) for(j=0;j<N;j++) {
  if(table[i][j]===0) {
    s += path2d_domino(i, j, 0);
  } else if (table[i][j] === 2) {
    s += path2d_domino(i, j, 2);
  } else if (table[i][j]===-1) {    
    reds.push(path2d_cross(i, j));
  }
}
  var path = new Path2D(s);
  ctx.stroke(path);
  ctx.fill(path);
  for (rs of reds) {
    ctx.stroke(new Path2D(rs));
  }
  ctx.strokeStyle='#000000';
  ctx.lineWidth=2;
  for(i=0;i<M;i++) for(j=0;j<N;j++) {
    if(table[i][j]!==-1 && j+1<N && table[i][j+1] !==-1) {
      ctx.lineWidth=1;
      ctx.strokeStyle='#CCCCCC';
      ctx.beginPath();
      ctx.moveTo(w*j+w,w*i+w);
      ctx.lineTo(w*j+w+w,w*i+w);
      ctx.stroke();
    }
    if(table[i][j]!==-1 && i+1<M && table[i+1][j] !==-1) {
      ctx.lineWidth=1;
      ctx.strokeStyle='#CCCCCC';
      ctx.beginPath();
      ctx.moveTo(w*j+w,w*i+w);
      ctx.lineTo(w*j+w,w*i+w+w);
      ctx.stroke();
    }
    if(table[i][j]===0) {
      ctx.strokeStyle='#999999';
      ctx.lineWidth=6;
      ctx.beginPath();
      ctx.moveTo(w*j+w,w*i+w);
      ctx.lineTo(w*j+w+w,w*i+w);
      ctx.stroke();
      ctx.strokeStyle='#000000';
      ctx.lineWidth=2;
      ctx.beginPath();
      ctx.moveTo(w*j+w,w*i+w);
      ctx.lineTo(w*j+w+w,w*i+w);
      ctx.stroke();
    }
    if(table[i][j]===2) {
      ctx.strokeStyle='#999999';
      ctx.lineWidth=6;
      ctx.beginPath();
      ctx.moveTo(w*j+w,w*i+w);
      ctx.lineTo(w*j+w,w*i+w+w);
      ctx.stroke();
      ctx.strokeStyle='#000000';
      ctx.lineWidth=2;
      ctx.beginPath();
      ctx.moveTo(w*j+w,w*i+w);
      ctx.lineTo(w*j+w,w*i+w+w);
      ctx.stroke();
    }
  }
  for(i=0;i<M;i++) for(j=0;j<N;j++) if(table[i][j] !== -1) {
    ctx.fillStyle='rgb(244,244,244)';
    ctx.strokeStyle='#000000';
    ctx.lineWidth=2;
      ctx.beginPath();
      ctx.arc(w*j+w/2+w/2,w*i+w/2+w/2,4,0,2*Math.PI);
      ctx.fill();
      ctx.beginPath();
      ctx.arc(w*j+w/2+w/2,w*i+w/2+w/2,4,0,2*Math.PI);
      ctx.stroke();
    }
}
</script>

而尋求骨牌鋪磚的鋪法數量，就可以轉化到圖 $G$ 上面完美匹配的數量了。
對於一般的圖 $G$，這個問題其實在計算上是非常困難的 ([♯P-Complete](https://en.wikipedia.org/wiki/%E2%99%AFP-complete))。
不過呢，我們建立出來的這個圖 $G$，是個平面圖 (planar graph)，在平面圖上則有個相當美妙的 Fischer-Kasteleyn-Temperley (FKT) 演算法來計算完美匹配的數量。

### Fischer-Kasteleyn-Temperley 演算法

這個在平面圖上計算完美匹配數量的 FKT 演算法意外地酷炫而且單純，但是要證明它的正確性需要一些有趣的線性代數小知識。
因此我們首先介紹這個演算法的步驟，然後再試圖證明它。

* 第一步：先把圖 $G$ 繪製在平面上，找出每一個面 (face)。
  * 此時我們可以先把『必定匹配的那些邊和點暫時拔掉』，所以剩下的每條邊都身處環中。
* 第二步：找出圖 $G$ 的任意一個生成樹 (spanning tree)，並且對生成樹上的所有邊隨意**定向** (orientation)。
* 第三步：重複以下步驟直到所有的邊都被定向為止：
  * 找出一個面，使得構成這個面的邊們，恰好只剩下一條邊 $e$ 還沒被定向。
  * 定向這條邊，使得沿著這個面順時針走訪時，恰好有**奇數條**順向的邊。
* 經過第三步以後，我們得到一個有向圖 $G$。我們建構一個帶有正負號的鄰接矩陣 ($(-1, 1, 0)$-adjacency matrix) $A$，矩陣內 $(i, j)$ 位置的值根據邊 $(i, j)$ 的方向來決定：順向為 $1$、反向為 $-1$、沒有邊的時候是 $0$。
* 我們要找的答案就是 $A$ 的[行列式值](https://en.wikipedia.org/wiki/Determinant)開平方根：$\sqrt{\det(A)}$。


<script>
var vertexID = [], vn = 0;
var vinfo = [];
var adj = [];
var edges = [];
var reversedEdge = {};
var disabledvertices = {};
var faces = [];
var faceids = [];
var missingeids = [];
var LTR=1, RTL=2, NOTORIENTED=0, EDGEDISABLEDMATCH=3, EDGEDISABLEDEMPTY=4;
var spanningtreeedges = [];
function build_graph_from_table() {
  // reset graph
  adj = [];
  edges = [];
  reversedEdge = {};
  faces = [];
  vertexID = [];
  vinfo = [];
  vn = 0;
  var i, j;
  for(i=0;i<M;i++) {
    vertexID.push([]);
    for(j=0;j<N;j++) vertexID[i].push(-1);
  }
  // Vertex IDs.
  for(i=0;i<M;i++) for(j=0;j<N;j++) {
    if (table[i][j] !== -1) {
      vertexID[i][j] = vn;
      vn++;
      adj.push([]);
      vinfo.push([i, j]);
    }
  }
  // Edges.
  for(i=0;i<M;i++) for(j=0;j<N;j++) {
    if(table[i][j] === -1) continue;
    function addEdge(u, v) {
      edges.push([u, v, NOTORIENTED]);
      adj[u].push(edges.length-1);
      adj[v].push(edges.length-1);
      reversedEdge[u+","+v] = edges.length-1;
      reversedEdge[v+","+u] = edges.length-1;
    };
    if(i+1<M && table[i+1][j] !== -1) addEdge(vertexID[i][j], vertexID[i+1][j]);
    if (j+1<N && table[i][j+1] !== -1) addEdge(vertexID[i][j], vertexID[i][j+1]);
  }
  // Remove deg 1 leaves and its matching.
  disabledvertices = {};
  var changed=true;
  while (changed === true) {
    changed=false;
    for (v=0;v<vn;v++) {
      if (disabledvertices[v] === true) continue;
      var nbrcnt=0, vvnote=0, einote=0;
      for (ei of adj[v]) {
        var vv = edges[ei][0]+edges[ei][1]-v;
        if (disabledvertices[vv] !== true) {
          ++nbrcnt;
          vvnote=vv;
          einote=ei;
        }
      }
      if (nbrcnt === 1) {
        changed=true;
        disabledvertices[v] = true;
        disabledvertices[vvnote] = true;
        edges[einote][2] = EDGEDISABLEDMATCH;
        for (ei of adj[v]) if (edges[ei][2] === NOTORIENTED) edges[ei][2] = EDGEDISABLEDEMPTY;
        for (ei of adj[vvnote]) if (edges[ei][2] === NOTORIENTED) edges[ei][2] = EDGEDISABLEDEMPTY;
      }
    }
  }
  // Spanning Trees.
  var vs = [];
  for (v=0;v<vn;v++) vs.push(v);
  for (v=0;v<vn;v++) {
    var vi = Math.floor(Math.random() * (vn-v))+v;
    [vs[v], vs[vi]] = [vs[vi], vs[v]];
  }
  var vused = {};
  spanningtreeedges = [];
  for (vi=0;vi<vn;vi++) {
    var v = vs[vi];
    if (vused[v] === true || disabledvertices[v] === true) continue;
    vused[v] = true;
    var que = [v], qb=0, qe=1;
    while (qb < qe) {
      v = que[qb];
      qb++;
      for (eid of adj[v]) {
        vv = edges[eid][0] + edges[eid][1] - v;
        if (vused[vv] === true || disabledvertices[vv] === true) continue;
        vused[vv] = true;
        que[qe] = vv;
        qe++;
        spanningtreeedges.push(eid);
        edges[eid][2] = (edges[eid][0] === v? LTR:RTL);
      }
    }
  }
  // Faces.
  faces = [];
  var visitedcell = {};
  for(i=1;i<M;i++) for(j=1;j<N;j++) {
    if(visitedcell[i+","+j]===true) continue;
    visitedcell[i+","+j]=true;
    var que = [[i, j]], qb = 0, qe = 1;
    var freeworld = false;
    while (qb < qe) {
      [x, y] = que[qb];
      qb++;
      function testedge(x, y, coor) {
        u = vertexID[coor[0]][coor[1]];
        v = vertexID[coor[2]][coor[3]];
        var canwalkthrough = false;
        if (u === -1 || v === -1) canwalkthrough = true;
        else if (disabledvertices[u] === true || disabledvertices[v] === true) canwalkthrough = true;
        else {
          eid = reversedEdge[u+","+v];
          if (edges[eid][2] === EDGEDISABLEDMATCH || edges[eid][2] === EDGEDISABLEDEMPTY)
            canwalkthrough = true;
        }
        if (canwalkthrough === true) {
          if (x <= 0 || x >= M || y <= 0 || y >= N) return true;
          if (visitedcell[x+","+y] ===true) return false;
          visitedcell[x+","+y] = true;
          que.push([x, y]);
          qe++;
        }
        return false;
      };
      freeworld ||= testedge(x-1, y, [x-1, y-1, x-1, y]);
      freeworld ||= testedge(x, y+1, [x-1, y, x, y]);
      freeworld ||= testedge(x+1, y, [x, y, x, y-1]);
      freeworld ||= testedge(x, y-1, [x, y-1, x-1, y-1]);
    }
    if (freeworld === false) {
      faces.push(que); // store entire que.
    }
  }
  // Re-order all faces.
  var nfaces = faces.length;
  var visitedfaces = {};
  faceids = [];
  missingeids = [];
  for (nf = 0; nf < nfaces; nf++) {
    for (i = 0; i < nfaces; i++) {
      if (visitedfaces[i] === true) continue;
      var clockwisecnt = 0;
      var alreadyEdge = {};
      var unknownedgecnt = 0, unknowneid = 0, shouldbe = NOTORIENTED;
      function consideredge(sx, sy, tx, ty) {
        u = vertexID[sx][sy];
        v = vertexID[tx][ty];
        if (u === -1 || v === -1) return 0;
        if (disabledvertices[u] === true || disabledvertices[v] === true) return 0;
        eid = reversedEdge[u+","+v];
        if (edges[eid][2] === EDGEDISABLEDMATCH || edges[eid][2] === EDGEDISABLEDEMPTY) return 0;
        if (alreadyEdge[eid] === true) return 0;
        alreadyEdge[eid] = true;
        if (edges[eid][2] === NOTORIENTED) {
          ++unknownedgecnt;
          unknowneid = eid;
          if (edges[eid][0] === u) shouldbe = LTR;
          if (edges[eid][0] === v) shouldbe = RTL;
          return 0;
        }
        if (edges[eid][0] === u && edges[eid][2] === LTR) return 1;
        if (edges[eid][0] === v && edges[eid][2] === RTL) return 1;
        return 0;
      }
      for ([x, y] of faces[i]) {
        clockwisecnt += consideredge(x-1, y-1, x-1, y);
        clockwisecnt += consideredge(x-1, y, x, y);
        clockwisecnt += consideredge(x, y, x, y-1);
        clockwisecnt += consideredge(x, y-1, x-1, y-1);
      }
      if (unknownedgecnt === 1) {
        faceids.push(i);
        missingeids.push(unknowneid);
        if (clockwisecnt % 2 !== 0) shouldbe = (LTR+RTL-shouldbe);
        edges[unknowneid][2] = shouldbe;
        visitedfaces[i] = true;
        break;
      }
    }
  }
}
</script>

<button onClick='javascript:startanimation(0)'>第一步：繪製圖 $G$ 然後把其中端點度數為 $1$、必須匹配的邊拔光光</button><br/>
<button onClick='javascript:startanimation(1)'>第二步：找一個生成樹，並且將生成樹的邊隨意定向</button><br/>
<button onClick='javascript:startanimation(2)'>第三步：每次找個有唯一缺口的面，並決定那條缺口上的邊的方向</button><br/>
<canvas id="canvas4" width="600" height="290"></canvas>

<script>
var animationStartTime = null;
var previousTimestamp = null;
var currentRequestID = null;

function ctxdrawvertex(ctx, cx, cy, isdisabled) {
  ctx.fillStyle='rgb(244,244,244)';
  if (isdisabled === true) {
    ctx.fillStyle='rgb(0,0,0)';
  }
  ctx.strokeStyle='#000000';
  ctx.lineWidth=2;
  ctx.beginPath();
  ctx.arc(cx,cy,4,0,2*Math.PI);
  ctx.fill();
  ctx.beginPath();
  ctx.arc(cx,cy,4,0,2*Math.PI);
  ctx.stroke();
}

function ctxreset(ctx) {
  ctx.reset();
  ctx.fillStyle='rgb(255,255,255)';
  var bg = new Path2D();
  bg.rect(0, 0, w*N+w, w*M+w);
  ctx.fill(bg);
}

function ctxdrawgraph(ctx, edgecounts) {
  var showedvertices = {};
  for (e=0;e<edgecounts && e<edges.length;e++) {
    x = edges[e][0];
    y = edges[e][1];
    [ix, jx] = [vinfo[x][0], vinfo[x][1]];
    [iy, jy] = [vinfo[y][0], vinfo[y][1]];
    showedvertices[x] = true;
    showedvertices[y] = true;
    ctx.lineWidth=1;
    ctx.strokeStyle='#CCCCCC';
    if (edges[e][2] === EDGEDISABLEDMATCH) {
      ctx.strokeStyle='#333333';
      ctx.lineWidth=3;
    }
    if (edges[e][2] === EDGEDISABLEDEMPTY) {
      continue;
    }
    ctx.beginPath();
    ctx.moveTo(w*jx+w,w*ix+w);
    ctx.lineTo(w*jy+w,w*iy+w);
    ctx.stroke();
  }
  for (v=0;v<vn;v++) {
    if (v in showedvertices) {
      [i, j] = [vinfo[v][0], vinfo[v][1]];
      var cx = w*j+w/2+w/2;
      var cy = w*i+w/2+w/2;
      ctxdrawvertex(ctx, cx, cy, disabledvertices[v]);
    }
  }
}

function ctxdrawarrow(arrowtip, ctx, sx, sy, tx, ty) {
  var dx = (sx - tx);
  var dy = (sy - ty);
  var dx5 = dx * 5.0 / Math.sqrt(dx*dx+dy*dy);
  var dy5 = dy * 5.0 / Math.sqrt(dx*dx+dy*dy);
  ctx.beginPath();
  ctx.moveTo(sx, sy);
  ctx.lineTo(tx+dx5, ty+dy5);
  if (arrowtip === true) {
    var theta = Math.PI/7;
    var vx = (dx*Math.cos(theta)-dy*Math.sin(theta)) * 0.35;
    var vy = (dx*Math.sin(theta)+dy*Math.cos(theta)) * 0.35;
    var vvx = (dx*Math.cos(theta)+dy*Math.sin(theta)) * 0.35;
    var vvy = (-dx*Math.sin(theta)+dy*Math.cos(theta)) * 0.35;
    ctx.lineTo(tx+vx, ty+vy);
    ctx.moveTo(tx+dx5, ty+dy5);
    ctx.lineTo(tx+vvx, ty+vvy);
  }
  ctx.stroke();
}

function ctxdrawspanningtree(ctx, est, estdir) {
  for (ei = 0; ei < est && ei < spanningtreeedges.length; ei++) {
    x = edges[spanningtreeedges[ei]][0];
    y = edges[spanningtreeedges[ei]][1];
    dirs = edges[spanningtreeedges[ei]][2];
    if (dirs === RTL) [x, y] = [y, x];
    [ix, jx] = [vinfo[x][0], vinfo[x][1]];
    [iy, jy] = [vinfo[y][0], vinfo[y][1]];
    ctx.lineWidth=2;
    ctx.strokeStyle='#EE3333';
    if (ei < estdir)
      ctxdrawarrow(/*arrowtip=*/true, ctx, w*jx+w, w*ix+w, w*jy+w, w*iy+w);
    else
      ctxdrawarrow(false, ctx, w*jx+w, w*ix+w, w*jy+w, w*iy+w);
  }
}

function ctxdrawfaces(ctx, fcnt) {
  for (fi = 0; fi < fcnt && fi < faceids.length; fi++) {
    for ([x, y] of faces[faceids[fi]]) {
      if (fi === Math.floor(fcnt)) {
        ctx.fillStyle='rgb(200,200,255)';
      } else {
        ctx.fillStyle='rgb(244,244,255)';
      }
      ctx.fillRect(w*y, w*x, w, w);
    }
  }
  for (fi = 0; fi < fcnt && fi < faceids.length; fi++) {
    for ([x, y] of faces[faceids[fi]]) {
      ctx.strokeStyle='#3333FF';
      ctx.lineWidth=2;
      u = edges[missingeids[fi]][0];
      v = edges[missingeids[fi]][1];
      dirs = edges[missingeids[fi]][2];
      if (dirs === RTL) [u, v] = [v, u];
      [ix, jx] = [vinfo[u][0], vinfo[u][1]];
      [iy, jy] = [vinfo[v][0], vinfo[v][1]];
      ctxdrawarrow(true, ctx, w*jx+w, w*ix+w, w*jy+w, w*iy+w);
    }
  }
}

function animate(timestamp) {
  currentRequestID = null;
  var alreadydone = false;
  if (animationStartTime === null) {
    animationStartTime = timestamp;
    previousTimestamp = timestamp;
  }
  var elapsed = timestamp - animationStartTime;
  if (timestamp - previousTimestamp < 20) {
    currentRequestID = requestAnimationFrame(animate);
    return;
  }

  var canvas = document.getElementById('canvas4');
  var ctx = canvas.getContext('2d');
  var edgecounts = edges.length * elapsed / 1000;
  ctxreset(ctx);
  ctxdrawgraph(ctx, edgecounts);

  if (elapsed >= 1000) alreadydone = true;
  previousTimestamp = timestamp;
  if (!alreadydone)
    currentRequestID = requestAnimationFrame(animate);
}

function animate1(timestamp) {
  currentRequestID = null;
  var alreadydone = false;
  if (animationStartTime === null) {
    animationStartTime = timestamp;
    previousTimestamp = timestamp;
  }
  var elapsed = timestamp - animationStartTime;
  if (timestamp - previousTimestamp < 20) {
    currentRequestID = requestAnimationFrame(animate1);
    return;
  }

  var canvas = document.getElementById('canvas4');
  var ctx = canvas.getContext('2d');
  ctxreset(ctx);
  ctxdrawgraph(ctx, edges.length);

  var est = spanningtreeedges.length * elapsed / 1000;
  var estdir = spanningtreeedges.length * (Math.max(0, elapsed-1000)) / 1000;
  ctxdrawspanningtree(ctx, est, estdir);

  // draw vertices again.
  for (v=0;v<vn;v++) {
    [i, j] = [vinfo[v][0], vinfo[v][1]];
    var cx = w*j+w/2+w/2;
    var cy = w*i+w/2+w/2;
    ctxdrawvertex(ctx, cx, cy, disabledvertices[v]);
  }
  
  if (elapsed >= 2000) alreadydone = true;

  previousTimestamp = timestamp;
  if (!alreadydone)
    currentRequestID = requestAnimationFrame(animate1);
}

function animate2(timestamp) {
  currentRequestID = null;
  var alreadydone = false;
  if (animationStartTime === null) {
    animationStartTime = timestamp;
    previousTimestamp = timestamp;
  }
  var elapsed = timestamp - animationStartTime;
  if (timestamp - previousTimestamp < 20) {
    currentRequestID = requestAnimationFrame(animate2);
    return;
  }

  var canvas = document.getElementById('canvas4');
  var ctx = canvas.getContext('2d');
  ctxreset(ctx);

  var fcnt = faceids.length * elapsed / 1000;
  ctxdrawfaces(ctx, fcnt);
  ctxdrawgraph(ctx, edges.length);
  ctxdrawspanningtree(ctx, spanningtreeedges.length, spanningtreeedges.length);

  // draw vertices again.
  for (v=0;v<vn;v++) {
    [i, j] = [vinfo[v][0], vinfo[v][1]];
    var cx = w*j+w/2+w/2;
    var cy = w*i+w/2+w/2;
    ctxdrawvertex(ctx, cx, cy, disabledvertices[v]);
  }
  
  if (elapsed >= 1000) alreadydone = true;

  previousTimestamp = timestamp;
  if (!alreadydone)
    currentRequestID = requestAnimationFrame(animate2);
}

function startanimation(animatetype) {
  w=40;
  animationStartTime = null;
  previousTimestamp = null;
  if (currentRequestID !== null) {
    cancelAnimationFrame(currentRequestID);
  }
  if (animatetype === 0) {
    currentRequestID = requestAnimationFrame(animate);
  } else if (animatetype === 1) {
    currentRequestID = requestAnimationFrame(animate1);
  } else if (animatetype === 2) {
    currentRequestID = requestAnimationFrame(animate2);
  }
}

function drawcanvas4() {
  var canvas = document.getElementById('canvas4');
  var ctx = canvas.getContext('2d');
  w=40;
  ctxreset(ctx);
  ctxdrawfaces(ctx, faceids.length);
  ctxdrawgraph(ctx, edges.length);
  ctxdrawspanningtree(ctx, spanningtreeedges.length, spanningtreeedges.length);
  // draw vertices again.
  for (v=0;v<vn;v++) {
    [i, j] = [vinfo[v][0], vinfo[v][1]];
    var cx = w*j+w/2+w/2;
    var cy = w*i+w/2+w/2;
    ctxdrawvertex(ctx, cx, cy, disabledvertices[v]);
  }
  w=30;
}
</script>

這樣定義出來的矩陣 $A$，是一個斜對稱矩陣 (skew-symmetric)，在斜對稱矩陣上，其行列式值 $\det(A)$ 恰好會等於普法夫值 (Pfaffian) $\mathrm{pf}(A)$ 的平方。而根據每個面周圍的邊定向的情形，可以得知 $A$ 的普法夫值的**絕對值**恰好等於圖 $G$ 中完美匹配的數量。
上面的證明大家可以參考[這份講義](http://scipp.ucsc.edu/~haber/webpage/pfaffian2.pdf)以及下面參考資料的投影片們囉！

## 參考資料

* 精美的投影片 [https://www.math.cmu.edu/~bwsulliv/domino-tilings.pdf](https://www.math.cmu.edu/~bwsulliv/domino-tilings.pdf)
* 精妙的各種鋪磚結果 Federico Ardila and Richard P. Stanley, 《Tilings》 [https://math.mit.edu/~rstan/papers/tilings.pdf](https://math.mit.edu/~rstan/papers/tilings.pdf)
* 平面圖上的完美匹配介紹 [https://people.maths.bris.ac.uk/~csxam/presentations/matchings.pdf](https://people.maths.bris.ac.uk/~csxam/presentations/matchings.pdf)
* 線代啟示錄，[《特殊矩陣 (13)：反對稱矩陣》](https://ccjou.wordpress.com/2010/08/27/%E7%89%B9%E6%AE%8A%E7%9F%A9%E9%99%A313%EF%BC%9A%E5%8F%8D%E5%B0%8D%E7%A8%B1%E7%9F%A9%E9%99%A3/), 2010.
* 偶數階反對稱方陣的 Pfaffian 值證明 Walter Ledermann, [A Note on Skew-Symmetric Determinants](https://www.cambridge.org/core/services/aop-cambridge-core/content/view/043C555E8C291D0E6E803E627A78930D/S0013091500018423a.pdf/note_on_skewsymmetric_determinants.pdf), 1991.
* 更多 Pfaffian 值的證明 [http://scipp.ucsc.edu/~haber/webpage/pfaffian2.pdf](http://scipp.ucsc.edu/~haber/webpage/pfaffian2.pdf)
* Kasteleyn's Theorem [https://www.theoremoftheday.org/MathPhysics/Kasteleyn/TotDKasteleyn.pdf](https://www.theoremoftheday.org/MathPhysics/Kasteleyn/TotDKasteleyn.pdf)
* 《Kasteleyn cokernels》 [https://arxiv.org/pdf/math/0108150.pdf](https://arxiv.org/pdf/math/0108150.pdf)



<script>
  var i_bad_style = true;
  function resetboard(reset) {
    w = 30;
    if (reset === 1) generateboard();
    if (reset === 0) randomrotate();
    if (reset === 514) partiallyrandom();
    drawcanvas();
    drawcanvas2();
    drawcanvas3();
    build_graph_from_table();
    drawcanvas4();
    if (reset !== 514) updatestateencode();
    if(i_bad_style === true) {
      console.log('這份 javascript 寫得很糟...還請各位先進同好多多指教，鞭小力一點 Q_____Q');
      i_bad_style = false;
    }
  }
  (function() {
   // your page initialization code here
   // the DOM will be available here
   resetboard(1);
})();
</script>