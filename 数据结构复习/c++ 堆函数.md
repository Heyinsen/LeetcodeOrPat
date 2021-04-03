[make_heap()等的使用](https://blog.csdn.net/qq_34793133/article/details/81222919)

# c++ STL容器中heap的使用

本文介绍如何使用STL里的heap（堆）算法。第一次接触heap这种数据结构是在大学的数据结构教材上，它是一棵完全二叉树。在STL中，heap是算法的形式提供给我们使用的。包括下面几个函数：

- `make_heap`: 根据指定的迭代器区间以及一个可选的比较函数，来创建一个heap. O(N)
- `push_heap`: 把指定区间的最后一个元素插入到heap中. O(logN)
- `pop_heap`: 弹出heap顶元素, 将其放置于区间末尾. O(logN)
- `sort_heap`：堆排序算法，通常通过反复调用`pop_heap`来实现. `N*O(logN)`

C++11加入了两个新成员：

- `is_heap`: 判断给定区间是否是一个heap. O(N)
- `is_heap_until`: 找出区间中第一个不满足heap条件的位置. O(N)

因为heap以算法的形式提供，所以要使用这几个api需要包含 `#include <algorithm>`

# heap相关算法的使用

## `make_heap`

STL中的通过`make_heap`创建的堆，默认是大顶堆(max heap)，即每个非叶子节点元素的值均不”小于”(默认使用<作为比较准则)其左右孩子节点。要改变堆的建立准则，可以自己制定一个比较函数，如下第二个版本的`make_heap`声明:

```cpp
// 1
template< class RandomIt >
void make_heap( RandomIt first, RandomIt last );
// 2
template< class RandomIt, class Compare >
void make_heap( RandomIt first, RandomIt last, Compare comp );
```

示例代码：

### 默认的`make_heap`

```cpp
vector<int> vi{6, 1, 2, 5, 3, 4};
printContainer(vi, "vi: ");             // vi: 6 1 2 5 3 4

make_heap(vi.begin(), vi.end());
printContainer(vi, "vi: ");             // vi: 6 5 4 1 3 2
```

需要注意的是，`make_heap`需使用随机迭代器来创建heap。

### 自己指定比较函数的`make_heap`

```cpp
vector<int> v2{6, 1, 2, 5, 3, 4};
printContainer(v2, "v2 before make_heap: ");
make_heap(v2.begin(), v2.end(), greater<int>());
printContainer(v2, "v2 after make_heap: ");
```

输出：

```cpp
v2 before make_heap: 6 1 2 5 3 4
v2 after make_heap: 1 3 2 5 6 4
```

这里使用了`greater<int>()`来代替默认的`less<int>()`来创建int类型的heap。可以按层次遍历的顺序把这个heap画出来，可以看到它跟默认情况刚好相反，会是一个小顶堆。

## `push_heap`

```cpp
// 1
template< class RandomIt >
void push_heap( RandomIt first, RandomIt last );
// 2
template< class RandomIt, class Compare >
void push_heap( RandomIt first, RandomIt last, Compare comp );
```

与`make_heap`类似，`push_heap`也有两个版本，其中有一个版本可以指定堆的比较函数，并且也是以一对迭代器指定的区间来进行操作。

示例代码：

```cpp
vector<int> v1{6, 1, 2, 5, 3, 4};
make_heap(v1.begin(), v1.end()); 
v1.push_back(200);
printContainer(v1, "before push_heap: ");        // before push_heap: 6 5 4 1 3 2 200
push_heap(v1.begin(), v1.end());
printContainer(v1, "after push_heap: ");         // after push_heap: 200 5 6 1 3 2 4
```

先用`make_heap`来构造一个堆，然后在容器末尾追加元素之后，把新的迭代器区间传给`push_heap`，这样新尾部元素也被添加到堆中。

注意：使用`push_heap(f, l)`的话，调用者需要确保`[f, l-1)`已经是一个堆. `push_heap(f, l)`仅仅会把`*(l-1)`插入到`[f, l-1)`这个区间形成的堆中，时间复杂度是O(logN).

即, STL书中所述：the caller has to ensure, on entry, the elements in the range `[begin, end)` are a heap(according to the same sorting criterion).

如果一开始不用`make_heap`处理，直接`push_heap`会怎样？

```cpp
vector<int> v2{6, 1, 2, 5, 3, 4};
v2.push_back(200);
printContainer(v2, "v2 before push_heap: ");
push_heap(v2.begin(), v2.end());
printContainer(v2, "v2 after push_heap: ");
```

输出：

```cpp
v2 before push_heap: 6 1 2 5 3 4 200
v2 after push_heap: 200 1 6 5 3 4 2
```

可以看出直接调用`push_heap`的结果并不是一个heap. 下面要提到的`pop_heap`也有同样的要求。

## `pop_heap`

```cpp
// 1    
template< class RandomIt >
void pop_heap( RandomIt first, RandomIt last );
// 2
template< class RandomIt, class Compare >
void pop_heap( RandomIt first, RandomIt last, Compare comp );
Swaps the value in the position first and the value in the position last-1 and makes the subrange [first, last-1) into a max heap. This has the effect of removing the first (largest) element from the heap defined by the range [first, last).
```

它的作用是：交换`*first`和`*(last-1)`， 然后把`[first, last-1)`建成一个max heap. 也就是说把堆顶的最大元素交换到区间尾，然后把除了尾部的元素的剩余区间重新调整成堆。

需要注意的是，调用者要保证，在调用`pop_heap`时`[first, last)`已经是一个堆(使用相同的排序准则)。

```cpp
vector<int> v1{6, 1, 2, 5, 3, 4};

make_heap(v1.begin(), v1.end());
printContainer(v1, "after make_heap: ");
pop_heap(v1.begin(), v1.end());
printContainer(v1, "after pop_heap: ");
auto largest = v1.back();
psln(largest);
v1.pop_back();
printContainer(v1, "delete largest: ");
```

输出：

```cpp
after make_heap: 6 5 4 1 3 2
after pop_heap: 5 3 4 1 2 6
largest = 6
delete largest: 5 3 4 1 2
```

## `sort_heap`

```cpp
// 1
template< class RandomIt >
void sort_heap( RandomIt first, RandomIt last );
// 2
template< class RandomIt, class Compare >
void sort_heap( RandomIt first, RandomIt last, Compare comp );
```

`sort_heap`即经典的堆排序算法，通过每次弹出堆顶直到堆为空，依次被弹出的元素就组成了有序的序列了。STL中的`priority_queue`即使用heap的这个特性来实现。

使用`sort_heap(f, l)`处理过的区间因为已经有序，就不再是一个heap了。

```cpp
vector<int> v1{6, 1, 2, 5, 3, 4};
printContainer(v1, "before sort_heap: ");       
make_heap(v1.begin(), v1.end());
sort_heap(v1.begin(), v1.end());
printContainer(v1, "after sort_heap: ");
```

输出：

```cpp
before sort_heap: 6 1 2 5 3 4
after sort_heap: 1 2 3 4 5 6
```

注意：调用者仍需确保区间已经是一个堆。

## `is_heap`

```cpp
// (1)  (since C++11)
template< class RandomIt >
bool is_heap( RandomIt first, RandomIt last );
// (2)  (since C++11)
template< class RandomIt, class Compare >
bool is_heap( RandomIt first, RandomIt last, Compare comp );
```

示例：

```cpp
vector<int> v1{6, 1, 2, 5, 3, 4};
psln(is_heap(v1.begin(), v1.end()));
pln("after make_heap");
make_heap(v1.begin(), v1.end());
psln(is_heap(v1.begin(), v1.end()));
```

输出：

```cpp
is_heap(v1.begin(), v1.end()) = 0
after make_heap
is_heap(v1.begin(), v1.end()) = 1
```

## `is_heap_until`

原型:

```cpp
// (1)  (since C++11)
template< class RandomIt >
RandomIt is_heap_until( RandomIt first, RandomIt last );
// (2)  (since C++11)
template< class RandomIt, class Compare >
RandomIt is_heap_until( RandomIt first, RandomIt last, Compare comp );
```

-  

```cpp
vector<int> v1{6, 1, 2, 5, 3, 4};
auto iter = is_heap_until(v1.begin(), v1.end());
psln(*iter);        // *iter = 5    5 是第一个不满足heap条件的位置。
make_heap(v1.begin(), v1.end());
iter = is_heap_until(v1.begin(), v1.end());
ASSERT_TRUE(iter == v1.end());
```

# 总结

1. 建堆，`make_heap`
2. 堆操作：增加元素(`push_heap`)，删除元素(`pop_heap`), 排序(`sort_heap`), 均要求区间已经是一个heap，并且是与当前操作使用相同的排序准则
3. `is_heap`, `is_heap_until`当做辅助判断函数来用
4. 所有的heap算法操作的区间都需要是随机迭代器组成

# 测试

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
// #include<functional>
using namespace std;

vector<int>heap;

template <class T>
bool myLess(T a,T b){
    return a<b;
}

template <class T>
struct Less{
    bool operator()(const T& a,const T& b)const{
        return a<b;
    }
};


void print_heap(vector<int>&heap){
    for(int i=0;i<heap.size();i++){
        cout<<heap[i]<<" ";
    }
    cout<<"\n";
}
int main(){
    vector<int> a({1,5,4,2,3});
    for(int i=0;i<a.size();i++){
        heap.push_back(a[i]);
    }
    // make_heap(heap.begin(),heap.end());// 默认最大堆
    {
        make_heap(heap.begin(),heap.end(),less<>());// 最大堆
        // print_heap(heap);
        // make_heap(heap.begin(),heap.end(),greater<>());// 最小堆

        // make_heap(heap.begin(),heap.end(),myLess<int>);// 最大堆
        // make_heap(heap.begin(),heap.end(),Less<int>());// 最大堆
    }
    heap[4]=10;// 直接更改里面的元素不会进行堆的调整
    // print_heap(heap);

    push_heap(heap.begin(),heap.end());     // push_heap()并不会去主动调整所有的元素,只会调整最后一个元素,自底向上的形成堆
    print_heap(heap);

    heap.push_back(11);
    push_heap(heap.begin(),heap.end());     
    print_heap(heap);

    pop_heap(heap.begin(),heap.end());      // pop出堆顶的第一个元素放到vector<>的末尾,需要保证[heap.begin(),heap.end())已经是一个堆
    pop_heap(heap.begin(),heap.end()-1);
    print_heap(heap);

    make_heap(heap.begin(),heap.end());// sort_heap之前需要保证是一个堆,最好make_heap()
    sort_heap(heap.begin(),heap.end());// 堆排序
    print_heap(heap);

    // is_heap()
    cout<<is_heap(heap.begin(),heap.end())<<endl;
    // is_heap_until(heap.begin(),heap.end()); // 返回迭代器,*iter是元素的值
    auto iter=is_heap_until(heap.begin(),heap.end());
    auto iter1=heap.begin();
    cout<<*iter1<<endl;
    cout<<*is_heap_until(heap.begin(),heap.end())<<endl;

}
```

