/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <map>
#include <memory>

#include "fbpcf/engine/tuple_generator/IArithmeticTupleGenerator.h"
#include "fbpcf/engine/tuple_generator/IProductShareGenerator.h"
#include "fbpcf/engine/tuple_generator/ITupleGenerator.h"
#include "fbpcf/engine/util/AsyncBuffer.h"
#include "fbpcf/engine/util/IPrg.h"

namespace fbpcf::engine::tuple_generator {

/**
 * This object uses product share generators to generate tuples.
 */
class ArithmeticTupleGenerator : public IArithmeticTupleGenerator {
 public:
  /**
   * @param productShareGeneratorMap the underlying product share
   * generators, the size indicates total number of parties.
   * @param prg a prg to generate randomness
   * @param bufferSize how many tuples to buffer in the memory.
   */
  ArithmeticTupleGenerator(
      std::map<int, std::unique_ptr<IProductShareGenerator>>&&
          productShareGeneratorMap,
      std::unique_ptr<util::IPrg> prg,
      uint64_t bufferSize = kDefaultBufferSize);

  /**
   * @inherit doc
   */
  std::vector<IntegerTuple> getIntegerTuple(uint32_t size) override;

  std::pair<uint64_t, uint64_t> getTrafficStatistics() const override;

 private:
  inline std::vector<IntegerTuple> generateTuples(uint64_t size);

  std::map<int, std::unique_ptr<IProductShareGenerator>>
      productShareGeneratorMap_;
  std::unique_ptr<util::IPrg> prg_;

  util::AsyncBuffer<IntegerTuple> asyncBuffer_;
};

} // namespace fbpcf::engine::tuple_generator
