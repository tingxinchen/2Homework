# 41343128

作業一:Max/Min Heap

## 解題說明
Max/Min Heap要求ADT5.2的MaxPQ改成MinPQ，minheap是父節點小於或等於子節點，queue的規則是先進先出。

### 解題策略
在實作Min Heap時，使用陣列來模擬完全二元樹
1. - 根節點位於 `0`。
   - 找左子節點：`2i + 1`
   - 找右子節點：`2i + 2`
   - 找父節點：`(i - 1) / 2`
2. **插入(Push)**：
   - 將新資料放在列的最後面。
   - 不斷與父節點比較，若新資料較小則交換，直到符合或到根部。
3. **取出最小值Pop)**：
   - 將陣列最後一個節點移至根節點位置，並刪除最後的節點。
   - 從根節點開始，向左、右子節點中比較，如果目前的節點較大就交換。
   - 重複直到節點小於子節點。

## 程式實作
以下是程式碼：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}

    virtual bool IsEmpty() const = 0;     // O(1)
    virtual const T& Top() const = 0;     // O(1)
    virtual void Push(const T&) = 0;      // O(log n)
    virtual void Pop() = 0;               // O(log n)
};
template <class T>
class MinHeap : public MinPQ<T> {
private:
    T heap[1000];
    int size;
public:
    MinHeap() {
        size = 0;     //建立新的樹從根開始
    }
    bool IsEmpty() const override { //看是不是空的
        return size == 0;
    }
    const T& Top() const override {
        if (IsEmpty()) {
            cout << "Heap is empty!" << endl;
            exit(1);
        }
        return heap[0];
    }
    void Push(const T& data) override {
        if (size < 1000) {
            heap[size] = data;
            int i = size;
            size++;
            while (i > 0 && heap[i] < heap[(i - 1) / 2]) {  // heap[(i - 1) / 2] 用來找父節點
                T temp;
                temp = heap[i];
                heap[i] = heap[(i - 1) / 2];
                heap[(i - 1) / 2] = temp;

                i = (i - 1) / 2;
            }
        }
    }
    void Pop() override {   //queue先進先出 
        if (IsEmpty())
            return;
        heap[0] = heap[size - 1];  //用最後面的補位
        size--;

        if (size > 0) {
            int i = 0;
            while (true) {
                int left = 2 * i + 1;
                int right = 2 * i + 2;
                int small = i;



                if (left < size && heap[left] < heap[small]) {
                    small = left;
                }
                if (right < size && heap[right] < heap[small]) {
                    small = right;
                }
                if (small != i) {
                    T temp = heap[i];
                    heap[i] = heap[small];
                    heap[small] = temp;
                    i = small;
                }
                else if (small == i) {
                    break;
                }

            }
        }

    }

};
int main() {
    MinHeap<int> test;

    cout << "測試" << endl;

    //Push功能 
    int data[] = { 30, 10, 50, 5, 20 };
    cout << "Push: 30, 10, 50, 5, 20" << endl;

    for (int i = 0; i < 5; i++) {
        test.Push(data[i]);
    }

    //Top功能
    if (!test.IsEmpty()) {
        cout << "目前最小的" << test.Top() << endl;
    }

    //Pop功能
    cout << "\n取出最小值:" << endl;
    while (!test.IsEmpty()) {
        cout << "取出: " << test.Top() << endl;
        if (!test.IsEmpty()) {
            cout << "目前最小的" << test.Top() << endl;
        }
        test.Pop();
    }


    //isempty測試
    cout << "\n是否為空: " << (test.IsEmpty() ? "是" : "否") << endl;

    return 0;
}
```
##效能分析
*時間複雜度：
*push:O(log n)
*pop:O(log n)
*top:O(1)
*空間複雜度：
*O(n) 使用陣列

## 測試與驗證

### 測試案例
| 測試案例 | 輸入值| 預期輸出 (Top)| 實際輸出 |
|-----------|---------------|---------------|-----------|
| Push |30, 10, 50, 20 | 10 | 10 |
| Pop 1 |- | 20 | 20 |
| Pop 2 | - |30 |30|
