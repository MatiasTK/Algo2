//! Quicksort pivote mitad
V = [3,4,6,8,10,11,23,44,56,93,94,98]
Pivote = 11
-> Ascendentemente mayores a la izquierda
-> [23,44,56,93,94,98] 11 [3,4,6,8,10]
-> Pivote 56 || 11 || pivote 6
-> [93,94,98] 56 [23,44] 11 [8,10] 6 [3,4]
-> Pivote 94 || 56 || pivote 23 || 11 || Pivote 8 || 6|| pivote 3
-> [98] 94 [93] 56 [44] 23 [] 11 [10] 8 6 [4] 3
-> [98,94,93] 56 [44,23] 11 [10,8] 6 [4,3]
-> [98,94,93,56,44,23] 11 [10,8,6,4,3]
-> [98,94,93,56,44,23,11,10,8,6,4,3]

//!
T(n) = n^2 log_2(n) + log_2(n)^2
-> El primer termino es mas grande por lo tanto analizo el primero -> O(n^2)	
