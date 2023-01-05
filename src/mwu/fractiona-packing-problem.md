# 分數包裝問題 Fractional Packing Problem

該問題的線性規劃表達式如下：

$$
\begin{aligned}
\text{minimize}\ \ & \lambda \\
\text{subject to}\ \  & \mathbf{A}\mathbf{x}\le \lambda \mathbf{b}\\
& \mathbf{x}\in \mathcal{P}
\end{aligned}
$$


## 分數包裝問題的 Primal-Dual 演算法

這個演算法的運作原理是透過對偶的性質，從初始解 $\mathbf{x}, \mathbf{y}$，透過一步步的更新，得到足夠好的解。

### 互補鬆弛性質

我們令 $\lambda$ 這個函數為 $\lambda := \max_i \frac{\mathbf{A}_i \mathbf{x}}{\mathbf{b}_i}$。

* (P1): $(1-\delta)\lambda \mathbf{y}^\top \mathbf{b} \le \mathbf{y}^\top \mathbf{A}\mathbf{x}$.
* (P2): $\lambda\mathbf{y}^\top\mathbf{b} - C_P(\mathbf{y}) \le \delta(\mathbf{y}^\top \mathbf{A}\mathbf{x} + \lambda \mathbf{y}^\top \mathbf{b})$, 其中 $C_P(\mathbf{y}) = \min_{\mathbf{x}\in\mathcal{P}} \mathbf{y}^\top \mathbf{A}\mathbf{x}$.

### 引理（互補鬆弛性質蘊含著近似解）

若 $\delta \le 1/6$，而且 $\mathbf{x}, \mathbf{y}$ 同時滿足 (P1) 與 (P2)，那麼 $\mathbf{x}$ 是一個 $6\delta$-近似解。
換句話說，由 $\mathbf{x}$ 定義出來的 $\lambda$ 值滿足 $\lambda \le (1-6\delta)\lambda^{\mathrm{OPT}}$。

### Plotkin-Shmoys-Tardos 的近似演算法

* 令參數 $\kappa\gets $
* 令初始值 $\lambda_0 \gets \max_i \mathbf{A}_i\mathbf{x}/\mathbf{b}_i$。
* 當 $\max_i \mathbf{A}_i\mathbf{x}/\mathbf{b}_i \ge (1-\delta)\lambda_0$，且 $\mathbf{y}$ 不滿足 (P2) 的時候進行以下更新：
  * 對所有 $i$，更新 $\mathbf{y}_i \gets \frac{1}{\mathbf{b}_i}\exp(\kappa \mathbf{A}_i\mathbf{x}/\mathbf{b}_i)$
  * 對於這個新的 $\mathbf{y}$，計算 $\tilde{\mathbf{x}} \gets \text{argmin}_{\mathbf{x}\in\mathcal{P}} \mathbf{y}^\top \mathbf{A}\mathbf{x}$
  * 更新 $\mathbf{x}\gets (1-\sigma)\mathbf{x} + \sigma \tilde{\mathbf{x}}$

### 引理（正確性）

若 $\kappa \ge 4\lambda^{-1}\delta^{-1}\ln (2m\delta^{-1})$，那麼對於任意合法的解 $\mathcal{x}$，上述演算法定義出來的 $\mathcal{y}$ 總是滿足條件 (P1)。

### 引理（時間）

定義勢能函數 $\Phi(\mathbf{y}) = \mathbf{y}^\top \mathbf{b}$。假設 $\Phi$ 為當前的勢能函數而 $\hat\Phi$ 為更新一次 $\mathbf{y}$ 以後的勢能函數。那麼此時有 $\Phi - \hat\Phi \ge \lambda\delta\kappa\sigma \Phi$。


## 參考資料

* Plotkin, Shmoys, and Tardos. [Fast Approximation Algorithms
for Fractional Packing and Covering Problems](http://infolab.stanford.edu/pub/cstr/reports/cs/tr/92/1419/CS-TR-92-1419.pdf), Stanford Technical Report, 1992.