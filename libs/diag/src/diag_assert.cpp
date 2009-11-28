// Copyright 2009 Brian Legge

#include "secondpylon/diag/diag_assert.h"
#include <cstdio>
#include <cstdarg>

namespace  {
  class DefaultAssertHandler : public secondpylon::diag::AssertHandlerInterface {
  public:
    secondpylon::diag::AssertSystem::EAssertAction OnAssert(
      const char* error
      , const char* message) {
      SPDIAG_UNREFERENCED(error);
      SPDIAG_UNREFERENCED(message);
      return secondpylon::diag::AssertSystem::kBreak;
    }
  };

}  // namespace unnamed


namespace secondpylon {
namespace diag {

static DefaultAssertHandler s_DefaultHandler;
secondpylon::diag::AssertHandlerInterface* AssertSystem::s_handler_ =
  &s_DefaultHandler;

AssertSystem::EAssertAction AssertSystem::HandleAssert(
  const char* condition
  , const char* format, ...) {
  va_list args;
  va_start(args, format);
  char message[1024];
  _vsnprintf_s(message, ArraySize(message), ArraySize(message), format, args);
  va_end(args);

  return s_handler_->OnAssert(condition, message);
}

secondpylon::diag::AssertHandlerInterface* AssertSystem::SetAssertHandler(
  secondpylon::diag::AssertHandlerInterface* new_handler) {
  AssertHandlerInterface* pPreviousHandler = s_handler_;
  s_handler_ = new_handler;
  return pPreviousHandler;
}

}  // namespace diag
}  // namespace secondpylon


