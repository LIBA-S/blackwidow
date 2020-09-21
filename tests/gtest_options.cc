//  Copyright (c) 2017-present The blackwidow Authors.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.

#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>

#include "blackwidow/blackwidow.h"

using namespace blackwidow;

class BlackwidowOptionsTest: public ::testing::Test {
  public:
  BlackwidowOptionsTest() = default;
  virtual ~BlackwidowOptionsTest() = default;

  static void SetUpTestCase() { }
  static void TearDownTestCase() { }

  BlackwidowOptions bw_options;
  blackwidow::Status s;
};

// ResetOptions
TEST_F(BlackwidowOptionsTest, ResetOptionsTest) {
  std::unordered_map<std::string, std::string> cf_options_map {{"write_buffer_size", "4096"},
                                                               {"max_write_buffer_number", "10"}};
  s = bw_options.ResetOptions(OptionType::kColumnFamily, cf_options_map);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(bw_options.options.write_buffer_size, 4096);
  ASSERT_EQ(bw_options.options.max_write_buffer_number, 10);

  std::unordered_map<std::string, std::string> invalid_cf_options_map {{"write_buffer_size", "abc"},
                                                                       {"max_write_buffer_number", "0x33"}};
  s = bw_options.ResetOptions(OptionType::kColumnFamily, invalid_cf_options_map);
  ASSERT_FALSE(s.ok());
  ASSERT_EQ(bw_options.options.write_buffer_size, 4096);
  ASSERT_EQ(bw_options.options.max_write_buffer_number, 10);

  std::unordered_map<std::string, std::string> db_options_map {{"max_open_files", "16"},
                                                               {"max_background_compactions", "32"}};
  s = bw_options.ResetOptions(OptionType::kDB, db_options_map);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(bw_options.options.max_open_files, 16);
  ASSERT_EQ(bw_options.options.max_background_compactions, 32);

  std::unordered_map<std::string, std::string> invalid_db_options_map {{"max_open_files", "a"},
                                                                       {"max_background_compactions", "bac"}};
  s = bw_options.ResetOptions(OptionType::kDB, invalid_db_options_map);
  ASSERT_FALSE(s.ok());
  ASSERT_EQ(bw_options.options.max_open_files, 16);
  ASSERT_EQ(bw_options.options.max_background_compactions, 32);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
