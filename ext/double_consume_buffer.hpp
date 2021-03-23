#include <thread>
#include <shared_mutex>
#include <memory>
#include <utility>

namespace ext {

template <typename DataStruture>
class ConsumerBase {
 public:
  virtual void Consume(const std::shared_ptr<DataStruture>& consume_buffer) = 0;

  virtual void Clear(const std::shared_ptr<DataStruture>& consume_buffer) {}
};

template <typename DataStrutrue, typename Consumer = ConsumerBase<DataStrutrue>>
class DoubleConsumeBuffer {
 public:
  template <typename... Args>
  DoubleConsumeBuffer(uint32_t loop_ms, const Args&... args) :
      buffer_({std::make_shared<DataStrutrue>(args...), std::make_shared<DataStrutrue>(args...)}),
      is_stop_(false),
      write_buffer_index_(0),
      loop_ms_(loop_ms),
      consume_thread_(Run, this)
  {
  }

  std::shared_ptr<DataStrutrue> GetWriteBuffer() {
    bool index = write_buffer_index_;
    bool locked = lock_[index].try_lock_shared();
    while (!locked) {
      index = write_buffer_index_;
      locked = lock_[index].try_lock_shared();
    }
    return SharedPtr<DataStrutrue>(buffer_[index], &lock_[index]);
  }

 protected:
  template <typename Type>
  class SharedPtr : public std::shared_ptr<Type> {
   private:
    SharedPtr(const std::shared_ptr<Type>& ptr, std::shared_mutex* lock) : std::shared_ptr<Type>(ptr) {
      lock_ = lock;
    }
    ~SharedPtr() {
      lock_->unlock_shared();
    }
    std::shared_mutex* lock_;
    friend class DoubleConsumeBuffer;
  };

  static void Run(DoubleConsumeBuffer* self) {
    while (!self->is_stop_) {
      bool index = self->write_buffer_index_;
      {
        self->write_buffer_index_ = !self->write_buffer_index_;
        std::unique_lock<std::shared_mutex>(self->lock_[index]);
        self->consumer_.Consume(self->buffer_[index]);
        self->consumer_.Clear(self->buffer_[index]);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(self->loop_ms_));
    }
  }

  std::shared_ptr<DataStrutrue> buffer_[2];
  bool is_stop_;
  bool write_buffer_index_;
  uint32_t loop_ms_;
  std::thread consume_thread_;
  Consumer consumer_;
  std::shared_mutex lock_[2];
};

}  // namespace ext