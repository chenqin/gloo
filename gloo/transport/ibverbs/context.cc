/**
 * Copyright (c) 2018-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "gloo/transport/ibverbs/context.h"

#include "gloo/common/error.h"
#include "gloo/transport/ibverbs/device.h"
#include "gloo/transport/ibverbs/pair.h"

namespace gloo {
namespace transport {
namespace ibverbs {

Context::Context(std::shared_ptr<Device> device, int rank, int size)
    : ::gloo::transport::Context(rank, size), device_(device) {
}

Context::~Context() {
}

std::unique_ptr<transport::Pair>& Context::createPair(
    int rank,
    std::chrono::milliseconds timeout) {
  if (timeout < std::chrono::milliseconds::zero()) {
    GLOO_THROW_INVALID_OPERATION_EXCEPTION("Invalid timeout", timeout.count());
  }
  pairs_[rank] = std::unique_ptr<transport::Pair>(
      new ibverbs::Pair(device_, timeout));
  return pairs_[rank];
}

std::unique_ptr<transport::UnboundBuffer> Context::createUnboundBuffer(
    void* ptr,
    size_t size) {
  GLOO_THROW_INVALID_OPERATION_EXCEPTION(
      "Unbound buffers not supported yet for ibverbs transport");
  return std::unique_ptr<transport::UnboundBuffer>();
}

} // namespace ibverbs
} // namespace transport
} // namespace gloo
