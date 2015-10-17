/*
 * libjingle
 * Copyright 2011, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TALK_BASE_ROLLINGACCUMULATOR_H_
#define TALK_BASE_ROLLINGACCUMULATOR_H_

#include <vector>

#include "talk/base/common.h"

namespace talk_base {

// RollingAccumulator stores and reports statistics
// over N most recent samples.
//
// T is assumed to be an int, long, double or float.
template<typename T>
class RollingAccumulator {
 public:
  explicit RollingAccumulator(size_t max_count)
    : count_(0),
      next_index_(0),
      sum_(0.0),
      sum_2_(0.0),
      samples_(max_count) {
  }
  ~RollingAccumulator() {
  }

  int max_count() const {
    return samples_.size();
  }

  int count() const {
    return count_;
  }

  void AddSample(T sample) {
    if (count_ == max_count()) {
      // Remove oldest sample.
      T sample_to_remove = samples_[next_index_];
      sum_ -= sample_to_remove;
      sum_2_ -= sample_to_remove * sample_to_remove;
    } else {
      // Increase count of samples.
      ++count_;
    }
    // Add new sample.
    samples_[next_index_] = sample;
    sum_ += sample;
    sum_2_ += sample * sample;
    // Update next_index_.
    next_index_ = (next_index_ + 1) % max_count();
  }

  T ComputeSum() const {
    return static_cast<T>(sum_);
  }

  T ComputeMean() const {
    if (count_ == 0) {
      return static_cast<T>(0);
    }
    return static_cast<T>(sum_ / count_);
  }

  // Compute estimated variance.  Estimation is more accurate
  // as the number of samples grows.
  T ComputeVariance() const {
    if (count_ == 0) {
      return static_cast<T>(0);
    }
    // Var = E[x^2] - (E[x])^2
    double count_inv = 1.0 / count_;
    double mean_2 = sum_2_ * count_inv;
    double mean = sum_ * count_inv;
    return static_cast<T>(mean_2 - (mean * mean));
  }

 private:
  int count_;
  int next_index_;
  double sum_;    // Sum(x)
  double sum_2_;  // Sum(x*x)
  std::vector<T> samples_;

  DISALLOW_COPY_AND_ASSIGN(RollingAccumulator);
};

}  // namespace talk_base

#endif  // TALK_BASE_ROLLINGACCUMULATOR_H_
