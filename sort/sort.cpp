#include <iostream>
#include <vector>
#include <numeric>     
#include <algorithm>   
#include <chrono>
#include <cstdlib>    
#include <ctime>     
#include <fstream>
#include <functional>


using namespace std;
using namespace chrono;

template <class T>
void randomPerm(T* a, int n) {
	for (int i = n - 1; i >= 1; --i) {
		int j = rand() % (i + 1);
		swap(a[i], a[j]);
	}
}

template <class T>
void worstinserition(T* a, int n) {
	for (int i = 0; i < n; ++i) {
		a[i] = static_cast<T>(n - i);
	}
}

template <class T>
void worstmergerec(T* a, int l,int r,T* buf) {
	if (l >= r) return;
	int k = 0;
	int i;
	for ( i = 1; i <= r; i += 2) buf[k++] = a[i];
	for ( i = 1+1; i <= r; i += 2) buf[k++] = a[i];
	for ( i = 0; i < k; ++i) a[l + i] = buf[i];
	int m = (l + r) / 2;
	worstmergerec(a, l, m, buf);
	worstmergerec(a, m + 1, r, buf);
}

template<class T>
void worstMerge(T* a, int n)
{
	if (n <= 1) return;

	
	for (int i = 0; i < n; ++i) a[i] = static_cast<T>(i + 1);

	
	std::vector<T> buf(n);
	auto rec = [&](auto&& self, int l, int r) -> void {
		if (l >= r) return;
		int k = 0;
		for (int i = l; i <= r; i += 2) buf[k++] = a[i];   
		for (int i = l + 1; i <= r; i += 2) buf[k++] = a[i];  
		for (int i = 0; i < k; ++i) a[l + i] = buf[i];
		int m = (l + r) / 2;
		self(self, l, m);
		self(self, m + 1, r);
		};
	rec(rec, 0, n - 1);
}

template<class T>
void worstQuick(T* a, int n) {
	for (int i = 0; i < n; ++i) a[i] = n - i;  
}

template<class T>
void worstHeap(T* a, int n) {
	for (int i = 0; i < n; ++i) a[i] = n - i;  
}


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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	srand(static_cast<unsigned>(time(nullptr)));

	
	vector<int> nList = { 500, 1000, 2000, 3000, 4000, 5000, 10000 };

	
	vector<string> sortNames = { "Insertion", "Merge", "Heap", "Quick" };

	
	vector<function<void(int*, int)>> worstGenerators = {
		worstinserition<int>,
		worstMerge<int>,
		worstHeap<int>,
		worstQuick<int>
	};

	
	vector<function<void(int*, int)>> sortFunctions = {
		Inserition<int>,
		mergesort<int>,
		heapsort<int>,
		quicksort<int>
	};

	
	ofstream foutWorst("worst_times.txt");
	ofstream foutRandom("random_times.txt");
	if (!foutWorst || !foutRandom) {
		cerr << "無法開啟輸出檔案\n";
		return 1;
	}

	foutWorst << "n,排序法,平均時間(μs)\n";
	foutRandom << "n,排序法,平均時間(μs)\n";

	const int trials = 10; 

	for (int n : nList) {
		for (int i = 0; i < 4; ++i) {
			long long totalWorstUs = 0;
			long long totalRandomUs = 0;

			for (int t = 0; t < trials; ++t) {
				
				vector<int> worstData(n);
				worstGenerators[i](worstData.data(), n);

				
				vector<int> randomData(n);
				iota(randomData.begin(), randomData.end(), 1);
				randomPerm(randomData.data(), n);

				
				vector<int> work = worstData;
				auto t0 = chrono::steady_clock::now();
				sortFunctions[i](work.data(), n);
				auto t1 = chrono::steady_clock::now();
				totalWorstUs += chrono::duration_cast<chrono::microseconds>(t1 - t0).count();

				
				work = randomData;
				t0 = chrono::steady_clock::now();
				sortFunctions[i](work.data(), n);
				t1 = chrono::steady_clock::now();
				totalRandomUs += chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
			}

			
			long long avgWorstUs = totalWorstUs / trials;
			long long avgRandomUs = totalRandomUs / trials;

			
			foutWorst << n << "," << sortNames[i] << "," << avgWorstUs << "\n";
			foutRandom << n << "," << sortNames[i] << "," << avgRandomUs << "\n";
		}
	}
	foutWorst.close();
	foutRandom.close();
	return 0;
}