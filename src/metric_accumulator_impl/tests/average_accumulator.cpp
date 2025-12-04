#include "metric_accumulator_impl/average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

TEST(AverageAccumulatorTest, BasicAverage) {
    AverageAccumulator accumulator;

    accumulator.Accumulate(metric::MetricResult{"test", 1});
    accumulator.Accumulate(metric::MetricResult{"test", 2});
    accumulator.Accumulate(metric::MetricResult{"test", 3});
    accumulator.Accumulate(metric::MetricResult{"test", 4});
    accumulator.Accumulate(metric::MetricResult{"test", 5});
    accumulator.Accumulate(metric::MetricResult{"test", 6});
    accumulator.Accumulate(metric::MetricResult{"test", 7});

    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get(), 4.);
}

TEST(AverageAccumulatorTest, Reset) {
    AverageAccumulator accumulator;

    accumulator.Accumulate(metric::MetricResult{"test", 1});
    accumulator.Accumulate(metric::MetricResult{"test", 2});
    accumulator.Accumulate(metric::MetricResult{"test", 3});
    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get(), 2.);

    accumulator.Reset();
    accumulator.Accumulate(metric::MetricResult{"test", 1});
    accumulator.Accumulate(metric::MetricResult{"test", 2});
    accumulator.Accumulate(metric::MetricResult{"test", 3});
    accumulator.Accumulate(metric::MetricResult{"test", 4});
    accumulator.Accumulate(metric::MetricResult{"test", 5});
    accumulator.Accumulate(metric::MetricResult{"test", 6});
    accumulator.Accumulate(metric::MetricResult{"test", 7});
    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get(), 4.);
}

TEST(AverageAccumulatorTest, WithoutFinalize) {
    AverageAccumulator accumulator;

    accumulator.Accumulate(metric::MetricResult{"test", 1});

    EXPECT_THROW(accumulator.Get(), std::runtime_error);
}

TEST(AverageAccumulatorTest, OnlyFinalize) {
    AverageAccumulator accumulator;

    accumulator.Finalize();

    EXPECT_NO_THROW(accumulator.Get());
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
