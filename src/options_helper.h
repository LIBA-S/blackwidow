//  Copyright (c) 2017-present The blackwidow Authors.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.

#ifndef SRC_OPTIONS_HELPER_H
#define SRC_OPTIONS_HELPER_H

#include <cstddef>

#include <rocksdb/options.h>

namespace blackwidow {

enum class MemberType {
  kInt,
  kSizeT,
  kUnknown,
};

struct MemberTypeInfo {
  int offset;
  MemberType type;
};

// offset_of is used to get the offset of a class data member with non standard-layout
// http://en.cppreference.com/w/cpp/concept/StandardLayoutType
// https://gist.github.com/graphitemaster/494f21190bb2c63c5516
template <typename T1, typename T2>
inline int offset_of(T1 T2::*member) {
  static T2 obj;
  return int(size_t(&(obj.*member)) - size_t(&obj));
}

static std::unordered_map<std::string, MemberTypeInfo> mutable_db_options_member_type_info = {
    {"max_background_compactions", {offsetof(struct rocksdb::DBOptions, max_background_compactions), MemberType::kInt}},
    {"max_open_files", {offsetof(struct rocksdb::DBOptions, max_open_files), MemberType::kInt}},
};

static std::unordered_map<std::string, MemberTypeInfo> mutable_cf_options_member_type_info = {
    {"max_write_buffer_number", {offset_of(&rocksdb::ColumnFamilyOptions::max_write_buffer_number), MemberType::kInt}},
    {"write_buffer_size", {offset_of(&rocksdb::ColumnFamilyOptions::write_buffer_size), MemberType::kSizeT}},
};

extern bool ParseOptionMember(const MemberType& member_type,
                              const std::string& value,
                              char* member_address);

}  //  namespace blackwidow
#endif  //  SRC_OPTIONS_HELPER_H
