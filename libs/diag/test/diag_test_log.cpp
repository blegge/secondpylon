// Copyright 2009 Brian Legge

#include "secondpylon/diag/diag_log.h"
#include "secondpylon/plat/plat_compiler.h"
#include "unittest++/src/UnitTest++.h"

namespace secondpylon {
namespace diag {
namespace test {

class StoringLogListener : public diag::LogListenerInterface {
  SPUNCOPYABLE(StoringLogListener);

  enum { kStorageSize = 80 };

public:
  StoringLogListener() {
    Message_[0] = '\0';
  }

  virtual void OnMessage(const char* message) {
    strncpy_s(Message_, message, kStorageSize);
    Message_[kStorageSize-1] = '\0';
  }

  const char* GetMessage() const { return Message_; }

private:
  char Message_[kStorageSize];
};

TEST(LogAddListener) {
  const char* msg = "test";

  diag::Log testLog;
  StoringLogListener listener;
  testLog.AddListener(&listener);
  testLog.Message(msg);
  testLog.RemoveListener(&listener);

  CHECK_EQUAL(msg, listener.GetMessage());
}

TEST(LogLogMessage) {
  const char* msg = "test";

  diag::Log testLog;
  StoringLogListener listener;
  testLog.AddListener(&listener);
  RSDIAG_LOG(testLog, msg);
  testLog.RemoveListener(&listener);

  CHECK_EQUAL(msg, listener.GetMessage());
}

}  // namespace secondpylon
}  // namespace diag
}  // namespace test
