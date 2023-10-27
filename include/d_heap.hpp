#ifndef __d_heap_hpp__
#define __d_heap_hpp__

#include <iostream>
#include <vector>

#define HEAP_SIZE \
  std::min(((size_t)heap.size() - (size_t)1), (size_t)heap.size())
#define RESERVE_HEAP_SIZE_MAX \
  SIZE_MAX  // reserve that node for return value if child isn't exist

namespace heap {

  template <typename T, size_t dimension>
  class d_Heap {
  public:
    d_Heap(void) = default;
    d_Heap(const std::vector<T>& vector);
    d_Heap(const T* vector, const size_t size);

    ~d_Heap() = default;

    size_t Get_size(void);
    size_t Get_capacity(void);
    bool isEmpty(void);

    size_t first_child(const size_t i);
    size_t last_child(const size_t i);
    size_t father(const size_t i);
    size_t min_child(const size_t i);

    T extract_min(void);
    void push(const T& value);
    T pop(const size_t i);
    void sift_up(size_t i);
    void sift_down(size_t i);
    void make_heap(void);
    void make_heap(const std::vector<T>& vector);
    void make_heap(const T* vector, const size_t size);

    template <typename Tp, size_t d>
    friend std::ostream& operator<<(std::ostream& cout,
      const d_Heap<Tp, d>& heap_);

  private:
    std::vector<T> heap;
  };

  template <typename T, size_t dimension>
  inline size_t d_Heap<T, dimension>::Get_size(void) {
    return heap.size();
  }

  template <typename T, size_t dimension>
  inline size_t d_Heap<T, dimension>::Get_capacity(void) {
    return heap.capacity();
  }

  template <typename T, size_t dimension>
  inline bool d_Heap<T, dimension>::isEmpty(void) {
    return heap.empty();
  }

  template <typename T, size_t dimension>
  inline size_t d_Heap<T, dimension>::first_child(const size_t i) {
    size_t firstChild = dimension * i + (size_t)1;
    if (firstChild > HEAP_SIZE) return RESERVE_HEAP_SIZE_MAX;
    return firstChild;
  }

  template <typename T, size_t dimension>
  inline size_t d_Heap<T, dimension>::last_child(const size_t i) {
    if (first_child(i) == (size_t)RESERVE_HEAP_SIZE_MAX)
      return RESERVE_HEAP_SIZE_MAX;
    return std::min(dimension * i + dimension, HEAP_SIZE);
  }

  template <typename T, size_t dimension>
  inline size_t d_Heap<T, dimension>::father(const size_t i) {
    size_t index = std::min(i - (size_t)1, i);
    return index / dimension;
  }

  template <typename T, size_t dimension>
  inline size_t d_Heap<T, dimension>::min_child(const size_t i) {
    size_t childFirst = first_child(i);
    if (childFirst == RESERVE_HEAP_SIZE_MAX) return RESERVE_HEAP_SIZE_MAX;

    size_t childLast = last_child(i);
    size_t min_child = childFirst;
    for (size_t j = childFirst + (size_t)1; j <= childLast; ++j) {
      if (heap[j] < heap[min_child]) {
        min_child = j;
      }
    }
    return min_child;
  }

  template <typename T, size_t dimension>
  inline void d_Heap<T, dimension>::sift_up(size_t i) {
    if (heap.empty() || i > HEAP_SIZE)
      throw std::invalid_argument("Wrong set number of node");
    T heap_i = heap[i];
    size_t parent = father(i);
    while (i != (size_t)0 && heap[parent] > heap_i) {
      heap[i] = heap[parent];
      i = parent;
      parent = father(i);
    }
    heap[i] = heap_i;
  }

  template <typename T, size_t dimension>
  inline void d_Heap<T, dimension>::sift_down(size_t i) {
    size_t child = min_child(i);
    if (child == RESERVE_HEAP_SIZE_MAX) return;
    T heap_i = heap[i];
    while ((child < heap.size()) && (heap[child] < heap_i)) {
      heap[i] = heap[child];
      i = child;
      child = min_child(i);
    }
    heap[i] = heap_i;
  }

  template <typename T, size_t dimension>
  inline T d_Heap<T, dimension>::extract_min(void) {
    if (!heap.empty()) {
      T min = heap.front();
      heap.front() = heap.back();
      heap.resize(HEAP_SIZE);
      if (!heap.empty()) sift_down((size_t)0);
      return min;
    }
    throw std::invalid_argument("The heap is empty");
  }

  template <typename T, size_t dimension>
  inline void d_Heap<T, dimension>::push(const T& value) {
    heap.push_back(value);
    sift_up(HEAP_SIZE);
  }

  template <typename T, size_t dimension>
  inline T d_Heap<T, dimension>::pop(const size_t i) {
    if (!heap.empty() || i >= heap.size()) {
      T pop = heap[i];
      heap[i] = heap.back();
      heap.resize(HEAP_SIZE);
      if (!heap.empty()) sift_down(i);
      return pop;
    }
    throw std::invalid_argument("The heap is empty or wrong index");
  }

  template <typename T, size_t dimension>
  inline void d_Heap<T, dimension>::make_heap(void) {
    for (size_t i = HEAP_SIZE / dimension; i != RESERVE_HEAP_SIZE_MAX; i--) {
      sift_down(i);
    }
  }

  template <typename T, size_t dimension>
  inline void d_Heap<T, dimension>::make_heap(const std::vector<T>& vector) {
    heap = vector;
    make_heap();
  }

  template <typename T, size_t dimension>
  inline void d_Heap<T, dimension>::make_heap(const T* vector,
    const size_t size) {
    heap.resize(size);
    for (size_t i = (size_t)0; i < HEAP_SIZE; ++i) {
      heap[i] = vector[i];
    }
    make_heap();
  }

  template <typename T, size_t dimension>
  inline d_Heap<T, dimension>::d_Heap(const std::vector<T>& vector) {
    make_heap(vector);
  }

  template <typename T, size_t dimension>
  inline d_Heap<T, dimension>::d_Heap(const T* vector, const size_t size) {
    heap.reserve(size);
    for (size_t i = 0; i < size; ++i) {
      heap.push_back(vector[i]);
    }
    make_heap();
  }

  template <typename Tp, size_t d>
  inline std::ostream& operator<<(std::ostream& cout,
    const d_Heap<Tp, d>& heap_) {
    for (const Tp& i : heap_.heap) {
      cout << i << " ";
    }
    cout << std::endl;
    return cout;
  }

}  // namespace heap

#endif  // __d_heap_hpp__