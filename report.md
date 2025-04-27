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
