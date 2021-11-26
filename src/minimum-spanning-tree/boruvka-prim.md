# 最小生成樹的 Borůvka-Prim 演算法

如果借助費氏堆積 (Fibonacci Heap) 或 Brodal Queue 等可合併堆積資料結構，那麼 Prim's 演算法可以在 $O(m + n\log n)$ 的時間內找出最小生成樹。

若預先進行 $\log\log n$ 次 Borůvka 步驟後，根據[引理 MST.7](boruvka-mst.html#%E6%99%82%E9%96%93%E8%A4%87%E9%9B%9C%E5%BA%A6%E5%BC%95%E7%90%86-mst7)，縮完連通元件的圖，其點數至多只有 $n' \le n/\log n$ 個點。若我們直接在此時套用上述 Prim's 演算法，那麼便能夠在 $O(m+n'\log n')= O(m+n)$ 線性時間計算出最小生成樹！

### 係理 MST.8

Borůvka-Prim 演算法的時間複雜度為 $O(m\log\log n)$。

## 完結

沒錯，這篇就是這麼乾淨！