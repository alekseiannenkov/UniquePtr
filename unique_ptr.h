//
// Created by Алексей on 08.06.2024.
//

#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <class T>
class UniquePtr {
 private:
  T* pointer_;

 public:
  UniquePtr();
  explicit UniquePtr(T* ptr);

  UniquePtr(const UniquePtr&) = delete;

  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr& operator=(UniquePtr&&) noexcept;

  UniquePtr(UniquePtr&& ptr) noexcept;

  T* Release();
  void Reset(T* ptr = nullptr);
  void Swap(UniquePtr&);

  T* Get() const;
  T& operator*() const;
  T* operator->() const;
  operator bool() const;  // NOLINT

  ~UniquePtr();
};
template <class T>
UniquePtr<T>::UniquePtr() : pointer_(nullptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(T* ptr) : pointer_(ptr) {
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& ptr) noexcept {
  if (this->pointer_ != ptr.pointer_) {
    delete this->pointer_;
    this->pointer_ = ptr.pointer_;

    ptr.pointer_ = nullptr;
  }
  return *this;
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr&& ptr) noexcept : UniquePtr<T>(ptr.pointer_) {
  ptr.pointer_ = nullptr;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
  delete pointer_;
}

template <class T>
T* UniquePtr<T>::Release() {
  T* temp(pointer_);
  pointer_ = nullptr;
  return temp;
}

template <class T>
void UniquePtr<T>::Reset(T* ptr) {
  delete pointer_;
  pointer_ = ptr;
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr& ptr) {
  T* temp = this->pointer_;
  this->pointer_ = ptr.pointer_;
  ptr.pointer_ = temp;
}

template <class T>
T* UniquePtr<T>::Get() const {
  return pointer_;
}

template <class T>
T& UniquePtr<T>::operator*() const {
  return *pointer_;
}

template <class T>
T* UniquePtr<T>::operator->() const {
  return pointer_;
}

template <class T>
UniquePtr<T>::operator bool() const {
  return pointer_ != nullptr;
}

#endif  // UNIQUE_PTR_H
