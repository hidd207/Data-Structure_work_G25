# 41243216 李宗燁

作業一 

## 解題說明

比較4種常見的排序演算法: 1.Insertion 2.Quick 3.Merge 4.Heap在不同輸入下,最壞與平均情況下的效能分析

### 解題步驟

- 使用c++進行解題,並使用`chrono`函式庫記錄排序花費時間
- 產生n從500逐步增加到5000的隨機測資與最壞測資
- 設定迴圈次數後執行4種演算法並記錄平均花費時間

## 程式實作

**Insertion Sort**

```cpp
template <class T>
void Inserition(T* a, int n) {
	for (int i = 1; i < n; ++i) {
		T key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = key;
	}
}
```

**Merge Sort**

```cpp
template<class T>
void merge(T* a, int l, int m, int r, T* buf)
{
	int i = l,     
		j = m + 1, 
		k = 0;     

	while (i <= m && j <= r)
		buf[k++] = (a[i] <= a[j] ? a[i++] : a[j++]);

	while (i <= m) buf[k++] = a[i++];  
	while (j <= r) buf[k++] = a[j++];  
}

template <class T>
void mergesortrec(T* a, int l, int r, T* buf) {
	if (l >= r) return;
	int m = (l + r) / 2;
	mergesortrec(a, l, m, buf);
	mergesortrec(a, m + 1, r, buf);
	merge(a, l, m, r, buf);
}

template <class T>
void mergesort(T* a, int n) {
	vector<T> buf(n);
	mergesortrec(a, 0, n - 1, buf.data());
}
```
**Heap Sort**

```cpp
template<class T>
void siftdown(T* a, int n, int i)
{
	while (true) {
		int l = 2 * i + 1,
			r = l + 1,
			largest = i;            
		if (l < n && a[l] > a[largest]) largest = l;
		if (r < n && a[r] > a[largest]) largest = r;
		if (largest == i) break;
		swap(a[i], a[largest]);
		i = largest;
		
	}
}

template <class T>
void heapsort(T* a, int n) {
	for (int i = n / 2 - 1; i >= 0; --i) siftdown(a, n, i);
	for (int i = n - 1; i > 0; --i) {
		swap(a[0], a[i]);
		siftdown(a, i, 0);
	}
}
```

**Quick Sort**
```cpp

template <class T>
int partition(T* a, int l, int r) {
	T pivot = a[l];
	int i = l + 1, j = r;
	while (1) {
		while (i <= r && a[i] < pivot) ++i;
		while (a[j] > pivot) --j;
		if (i >= j) break;
		swap(a[i], a[j]);
	}
	swap(a[l], a[j]);
	return j;
}

template<class T>
void quicksortrec(T* a, int l, int r) {
	while (l < r) {
		int p = partition(a, l, r);

		
		if (p - l < r - p) {
			quicksortrec(a, l, p - 1);
			l = p + 1;               
		}
		else {
			quicksortrec(a, p + 1, r);
			r = p - 1;               
		}
	}
}

template <class T>
void quicksort(T* a, int n) {
	quicksortrec(a, 0, n - 1);
}
```
## 效能分析

時間複雜度:理論時間複雜度為
### Insertion & Quick: $n^2$
### Merge & Heap: $nlogn$

## 實際測試數據

**平均情況（單位：μs）**
| 數據規模 | Insertion | Quick | Merge | Merge| 
|----------|--------------|----------|----------|----------|
|500|63|23|18|36|
|1000|	0.632015	|0.07899|	2.75133	|0.113925|
|2000|	2.26618	|0.181835	|5.28603	|0.25124|
|3000|	5.37174|	0.299585	|7.30325	|0.397875|
|4000|	9.61726|	0.4156	|10.7534|	0.58034|
|5000|	12.3864	|0.379175|	11.9326	|0.729085|
