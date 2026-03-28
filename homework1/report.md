# 41343128

作業一problem1:Max/Min Heap

## 解題說明
Max/Min Heap要求ADT5.2的MaxPQ改成MinPQ，minheap是父節點小於或等於子節點，queue的規則是先進先出。

### 解題策略和步驟
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
* **時間複雜度**：
    * `push`: $O(\log n)$
    * `pop`: $O(\log n)$
    * `top`: $O(1)$
* **空間複雜度**：
    * $O(n)$ 使用陣列儲存
## 測試與驗證

### 測試案例
| 測試案例 | 輸入值| 預期輸出 (Top)| 實際輸出 |
|-----------|---------------|---------------|-----------|
| Push |30, 10, 50, 20 | 10 | 10 |
| Pop 1 |- | 20 | 20 |
| Pop 2 | - |30 |30|

### 結論
1. 程式可自動照大小排好樹的位置。
2. 用陣列儲存，程式清晰。
3. pop會重新檢查並排好。


## 申論及開發報告
寫程式時先把MaxPQ的類別改變成MinPQ的，然後一點一點把每個函式寫出功能，在Push中確保新節點若小於父節點則向上交換，在 Pop中從左、右子節點中選出較小者與當前節點比較，若當前節點較大則向下交換。
在Pop的比較大小時，容易出錯的地方在於界線的判斷。加入了 left < size 與 right < size 的條件檢查，防止程式存取到陣列範圍外的無效節點。


# 41343128

作業一problem2:Binary Search Tree

## 解題說明
要求實作一個二元搜尋樹，並透過隨機插入 $n$ 個數值（$n = 100$ 至 $10000$），觀察其實際高度（Height）與理論對數高度（$\log_2 n$）的比值。第二部分，實作刪除功能並分析時間複雜度是多少。

### 解題策略和步驟
1. 建立一個包含 $\{100, 500, 1000, 2000, 5000, 10000\}$ 的整數陣列。
2. 利用 ctime 的 time(NULL) 作為隨機種子，讓測試數據不重複。
3. 使用巢狀迴圈，在每一次運作時生成 $n$ 個隨機整數並呼叫insert建構BST。
4. 每完成一棵樹，呼叫Height記錄樹的高度，並計算$\log_2 n$的比值。
5. delete尋找目標節點後，依子節點數量執行刪除、子節點替換或右子樹最小值替補以維持 BST 結構。

---
## 程式實作
```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>   
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (root == NULL) {
        return new Node(val);
    }
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

int Height(Node* root) {
    if (root == NULL) return -1;

    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);

    return max(leftHeight, rightHeight) + 1;
}

Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int val) {
    if (root == NULL) return NULL;

    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    srand(time(NULL));

    int ns[] = { 100, 500, 1000, 2000, 5000, 10000 };
    int num_tests = 6;

    for (int i = 0; i < num_tests; i++) {
        int n = ns[i];
        Node* root = NULL;
        int last_val = 0;

        for (int j = 0; j < n; j++) {
            last_val = rand();
            root = insert(root, last_val);
        }

        int h = Height(root);

        double ratio = h / log2(n);

        cout << "n = " << n << ", height = " << h << ", ratio = " << ratio << endl;

        root = deleteNode(root, last_val);
    }

    return 0;
}
```
##效能分析
* **時間複雜度**：
    * 插入與搜尋 (Insert/Search)：平均 $O(\log n)$
    * 刪除 (Delete)：平均 若資料依序插入
    * 若資料依序插入$O(n)$
* **空間複雜度**：
    * $O(n)$ 動態配置記憶體來儲存 $n$ 個節點的資料與左右子指標。

## 測試與驗證

### 測試案例
| 測試案例 | 輸入值 | 預期輸出 (Root/Result) | 實際輸出 |
|:---|:---|:---|:---|
| **Insert** | 30, 10, 50, 20 | Root 為 30 | 30 |
| **Search** | 50 | 找到節點 50 | 找到節點 50 |
| **Delete (Leaf)** | 20 | 20 消失，10 的右子變 NULL | 符合 |
| **Delete (1 Child)** | 10 | 10 消失，30 的左子由 20 遞補 | 符合 |
| **Delete (2 Child)** | 30 | 30 消失，由 50 遞補根節點 | 符合 |
