# 期望線性時間的 Karger-Klein-Tarjan 演算法

當確定性的演算法 (deterministic algorithms) 開始變得複雜的時候，眾人們便開始考慮隨機演算法 (randomized algorithms) 的可能性。
最小生成樹是一個很經典而且適用於前一句的標準例子：至今大家仍然不知道，確定性演算法究竟能不能做到線性時間。但隨機演算法，已經能夠做到**期望**線性時間了！

將隨機方法導入圖論演算法這個領域並進行分析的，任職於 MIT 的 David Karger 教授應該是第一人了吧。今天我們將介紹 Karger, Klein 以及 Tarjan 等人利用一個絕妙觀察設計出來的期望線性時間演算法。

