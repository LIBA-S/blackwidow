//  Copyright (c) 2017-present The blackwidow Authors.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.

#include "src/options_helper.h"

#include <string>

namespace blackwidow {

// strToInt may throw exception
static bool strToInt(const std::string& value, int* num, int base = 10) {
  size_t end;
  *num = std::stoi(value, &end, base);
  return end < value.size() ? false : true;
}

// strToUint64 may throw exception
static bool strToUint64(const std::string& value, uint64_t* num, int base = 10) {
  size_t end;
  *num = std::stoull(value, &end, base);
  return  end < value.size() ? false : true;
}

bool ParseOptionMember(const MemberType& member_type,
    const std::string& value, char* member_address)  {
  switch (member_type) {
    case MemberType::kInt:
      int intVal;
      if (!strToInt(value, &intVal)) return false;
      *reinterpret_cast<int*>(member_address) = intVal;
      break;
    case MemberType::kSizeT:
      uint64_t uint64Val;
      if (!strToUint64(value, &uint64Val)) return false;
      *reinterpret_cast<size_t*>(member_address) = static_cast<size_t>(uint64Val);
      break;
    default:
      return false;
  }
  return true;
}

}  // namespace blackwidow
