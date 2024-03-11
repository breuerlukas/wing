#ifndef SimpleList_h
#define SimpleList_h

#include <type_traits>
#include <cstddef>
#include <functional>

template<class T>
struct ListNode {
  T                  data;
  ListNode<T>* next = NULL;
};

template<typename T>
class List {
public:
  List();
  List(int(*compare)(T & a, T & b));
  virtual ~List();

  virtual void setCompare(int (* compare)(T& a, T& b));

  virtual int size();
  virtual bool isSorted();
  virtual bool isEmpty();

  virtual void add(int index, T obj);
  virtual void add(T obj);
  virtual void insert(T obj);

  virtual void replace(int index, T obj);
  virtual void swap(int x, int y);

  virtual void remove(int index);
  virtual void removeFirst();
  virtual void removeLast();

  virtual bool has(T obj);
  virtual int count(T obj);

  virtual T shift();
  virtual T pop();
  virtual T get(int index);
  virtual T getFirst();
  virtual T getLast();

  virtual void moveToEnd();

  virtual int search(T obj);
  virtual int searchNext(T obj);
  virtual int binSearch(T obj);

  virtual void sort();
  virtual void clear();

protected:
  int (* compare)(T& a, T& b) = NULL;

  int listSize                 = 0;
  ListNode<T>* listBegin = NULL;
  ListNode<T>* listEnd   = NULL;

  // Helps get() method by saving last position
  ListNode<T>* lastNodeGot = NULL;
  int lastIndexGot               = -1;
  bool isCached                  = false;

  bool sorted = true;

  virtual ListNode<T>* getNode(int index);
  virtual int binSearch(T obj, int lowerEnd, int upperEnd);
};

template<typename T>
List<T>::List() {}

template<typename T>
List<T>::List(int(*compare)(T & a, T & b)) {
  setCompare(compare);
}

// Clear Nodes and free Memory
template<typename T>
List<T>::~List() {
  clear();
}

template<typename T>
void List<T>::setCompare(int (* compare)(T& a, T& b)) {
  this->compare = compare;
  sort();
}

template<typename T>
ListNode<T>* List<T>::getNode(int index) {
  if ((index < 0) || (index >= listSize)) return NULL;

  ListNode<T>* hNode = listBegin;
  int c                    = 0;

  if (isCached && (index >= lastIndexGot)) {
    c     = lastIndexGot;
    hNode = lastNodeGot;
  }

  while (hNode && c < index) {
    hNode = hNode->next;
    c++;
  }

  if (hNode) {
    isCached     = true;
    lastIndexGot = c;
    lastNodeGot  = hNode;
  }

  return hNode;
}

template<typename T>
int List<T>::size() {
  return listSize;
}

template<typename T>
bool List<T>::isSorted() {
  return sorted;
}

template<typename T>
bool List<T>::isEmpty() {
  return listSize == 0;
}

template<typename T>
void List<T>::add(T obj) {
  // create new node
  ListNode<T>* newNode = new ListNode<T>();

  newNode->data = obj;

  if (!listBegin) listBegin = newNode;

  if (listEnd) {
    listEnd->next = newNode;
    listEnd       = newNode;
  } else {
    listEnd = newNode;
  }

  listSize++;
  sorted = false;
}

template<typename T>
void List<T>::add(int index, T obj) {
  if ((index < 0) || (index >= listSize)) {
    return;
  }

  ListNode<T>* newNode = new ListNode<T>();
  newNode->data = obj;

  if (index == 0) {
    listBegin = newNode;
  } else {
    ListNode<T>* nodePrev = getNode(index - 1);
    newNode->next  = nodePrev->next;
    nodePrev->next = newNode;
  }

  listSize++;
  sorted = false;
}

template<typename T>
void List<T>::insert(T obj) {
  if (!compare) {
    add(obj);
    return;
  }

  if (!sorted) sort();

  // create new node
  ListNode<T>* newNode = new ListNode<T>();
  newNode->data = obj;

  if (listSize == 0) {
    // add at start (first node)
    listBegin = newNode;

    listEnd = newNode;
  } else {
    if (compare(obj, listEnd->data) >= 0) {
      // add at end
      listEnd->next = newNode;
      listEnd       = newNode;
    } else if (compare(obj, listBegin->data) < 0) {
      // add at start
      newNode->next = listBegin;
      listBegin     = newNode;
    } else {
      // insertion sort
      ListNode<T>* h = listBegin;
      ListNode<T>* p = NULL;
      bool found           = false;

      // here a sequential search, because otherwise the previous node couldn't be accessed
      while (h && !found) {
        if (compare(obj, h->data) < 0) {
          found = true;
        } else {
          p = h;
          h = h->next;
        }
      }
      newNode->next = h;

      if (p) p->next = newNode;
    }
  }

  listSize++;
}

template<typename T>
void List<T>::replace(int index, T obj) {
  if ((index >= 0) && (index < listSize)) {
    getNode(index)->data = obj;
  }
}

template<typename T>
void List<T>::swap(int x, int y) {
  // only continue when the index numbers are unequal and at least 0
  if ((x != y) && (x >= 0) && (y >= 0)) {
    if (x > y) { // the first index should be smaller than the second. If not, swap them!
      int h = x;
      x = y;
      y = h;
    }

    // When data is small, copy it
    if (sizeof(T) < 24) {
      ListNode<T>* nodeA = getNode(x);
      ListNode<T>* nodeB = getNode(y);
      T h                      = nodeA->data;
      nodeA->data = nodeB->data;
      nodeB->data = h;
    }

      // otherwise change the pointers
    else {
      // Example: a -> b -> c -> ... -> g -> h -> i
      //          we want to swap b with h
      ListNode<T>* nodeA = getNode(x - 1);                      // x.prev
      ListNode<T>* nodeB = getNode(x);                          // x
      ListNode<T>* nodeC = getNode(x + 1);                      // x.next
      ListNode<T>* nodeG = y - 1 == x ? nodeB : getNode(y - 1); // y.prev
      ListNode<T>* nodeH = getNode(y);                          // y
      ListNode<T>* nodeI = getNode(y + 1);                      // y.next

      // a -> h -> i      b -> c -> ... -> g -> h -> i
      if (nodeA) nodeA->next = nodeH;
      else listBegin = nodeH;

      // a -> h -> c -> ... -> g -> h -> i    b -> i
      if (nodeH != nodeC) // when nodes between b and h exist
        nodeH->next = nodeC;
      else nodeH->next = nodeB;

      // a -> h -> i      b -> i
      nodeB->next = nodeI;

      if (!nodeI) listEnd = nodeB;

      // a -> h -> c -> ... -> g -> b -> i
      if (nodeG != nodeB) // when more than 1 nodes between b and h exist
        nodeG->next = nodeB;
    }
  }
}

template<typename T>
void List<T>::remove(int index) {
  if ((index < 0) || (index >= listSize)) return;

  ListNode<T>* nodePrev     = getNode(index - 1);
  ListNode<T>* nodeToDelete = getNode(index);

  if (index == 0) {
    listBegin = nodeToDelete->next;
  } else {
    nodePrev->next = nodeToDelete->next;

    if (!nodePrev->next) listEnd = nodePrev;
  }

  delete nodeToDelete;

  isCached = false;

  listSize--;
}

template<typename T>
void List<T>::removeFirst() {
  remove(0);
}

template<typename T>
void List<T>::removeLast() {
  remove(listSize - 1);
}

template<typename T>
bool List<T>::has(T obj) {
  return binSearch(obj) >= 0;
}

template<typename T>
int List<T>::count(T obj) {
  if (compare == NULL) return -1;

  int c = 0;

  for (int i = 0; i < listSize; i++) {
    if (compare(obj, getNode(i)->data) == 0) c++;
  }

  return c;
}

template<typename T>
T List<T>::get(int index) {
  ListNode<T>* h = getNode(index);

  if (h) return h->data;

  return T();
}

template<typename T>
T List<T>::getFirst() {
  return get(0);
}

template<typename T>
T List<T>::getLast() {
  return get(listSize - 1);
}

template<typename T>
void List<T>::moveToEnd() {
  ListNode<T>* h = listBegin;

  if (!h) return;

  listBegin     = listBegin->next;
  listEnd->next = h;

  h->next = NULL;
  listEnd = h;

  lastNodeGot  = NULL;
  lastIndexGot = -1;
  isCached     = false;

  sorted = false;
}

template<typename T>
int List<T>::search(T obj) {
  if (compare == NULL) return -1;

  int i = 0;

  ListNode<T>* hNode = getNode(i);
  bool found               = compare(obj, hNode->data) == 0;

  while (!found && i < listSize) {
    i++;
    hNode = getNode(i);
    found = compare(obj, hNode->data) == 0;
  }

  return found ? i : -1;
}

template<typename T>
int List<T>::searchNext(T obj) {
  if (compare == NULL) return -1;

  int i = lastIndexGot;

  ListNode<T>* hNode = lastNodeGot;
  bool found               = compare(obj, hNode->data) == 0;

  while (!found && i < listSize) {
    i++;
    hNode = getNode(i);
    found = compare(obj, hNode->data) == 0;
  }

  return found ? i : -1;
}

template<typename T>
int List<T>::binSearch(T obj, int lowerEnd, int upperEnd) {
  if (!compare || !sorted) return search(obj);

  if (!listBegin) return -1;

  int res;
  int mid = (lowerEnd + upperEnd) / 2;

  ListNode<T>* hNode = getNode(0);
  int hIndex               = 0;

  while (lowerEnd <= upperEnd) {
    hNode  = lastNodeGot;
    hIndex = lastIndexGot;
    res    = compare(obj, getNode(mid)->data);

    if (res == 0) {
      return mid;
    } else if (res < 0) {
      // when going left, set cached node back to previous cached node
      lastNodeGot  = hNode;
      lastIndexGot = hIndex;
      isCached     = true;

      upperEnd = mid - 1;
      mid      = (lowerEnd + upperEnd) / 2;
    } else if (res > 0) {
      lowerEnd = mid + 1;
      mid      = (lowerEnd + upperEnd) / 2;
    }
  }

  return -1;
}

template<typename T>
int List<T>::binSearch(T obj) {
  return binSearch(obj, 0, listSize - 1);
}

template<typename T>
T List<T>::pop() {
  T data = getLast();

  removeLast();

  return data;
}

template<typename T>
T List<T>::shift() {
  T data = getFirst();

  removeFirst();

  return data;
}

template<typename T>
void List<T>::clear() {
  while (listSize > 0) removeFirst();

  listSize  = 0;
  listBegin = NULL;
  listEnd   = NULL;

  lastNodeGot  = NULL;
  lastIndexGot = -1;
  isCached     = false;

  sorted = true;
}

template<typename T>
void List<T>::sort() {
  if (compare == NULL) return;

  // selection sort (less swaps than insertion sort)

  int indexH;                 // index of node i
  int indexMin;               // index of next minimum node

  ListNode<T>* nodeMin; // next minimum node
  ListNode<T>* nodeH;   // helper node at index j

  for (int i = 0; i < listSize - 1; i++) {
    nodeMin  = getNode(i);
    indexH   = i;
    indexMin = i;

    for (int j = i + 1; j < listSize; j++) {
      nodeH = getNode(j);

      if (compare(nodeMin->data, nodeH->data) > 0) {
        nodeMin  = nodeH;
        indexMin = j;
      }
    }
    swap(indexH, indexMin);
  }

  this->sorted = true;
}

#endif // ifndef SimpleList_h