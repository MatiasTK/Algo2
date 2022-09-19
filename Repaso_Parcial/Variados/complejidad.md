* T1(n) = 3T(n/2) + n^2

log_2(3) = 2
1,58 < 2
O(n^2)

![D1](https://i.imgur.com/yTfVEVh.png)

* T2(n) = 4T(n/2) + n^2 
  
log_2(2) = 2
2 = 2
O(n^2 log(n)) 

![D2](https://i.imgur.com/N09YiDY.png)

**Es mejor el primero n^2 en complejidad**
**Demostracion**
Si n = 15
O(n^2) = 225
O(n^2 log(n)) = 609,311

* T3(n) = 4T(n/2) - n^2

No se puede hacer no puede tener elementos negativos.
