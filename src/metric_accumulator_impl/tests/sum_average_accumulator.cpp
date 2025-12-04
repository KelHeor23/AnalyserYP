#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

TEST(SumAverageAccumulatorTest, BasicSumAverage) {
    SumAverageAccumulator accumulator;

    accumulator.Accumulate(metric::MetricResult{"test", 1});
    accumulator.Accumulate(metric::MetricResult{"test", 2});
    accumulator.Accumulate(metric::MetricResult{"test", 3});
    accumulator.Accumulate(metric::MetricResult{"test", 4});
    accumulator.Accumulate(metric::MetricResult{"test", 5});
    accumulator.Accumulate(metric::MetricResult{"test", 6});
    accumulator.Accumulate(metric::MetricResult{"test", 7});

    accumulator.Finalize();

    auto result = accumulator.Get();
    EXPECT_EQ(result.sum, 28);
    EXPECT_DOUBLE_EQ(result.average, 4.);
}

TEST(SumAverageAccumulatorTest, Reset) {
    SumAverageAccumulator accumulator;

    accumulator.Accumulate(metric::MetricResult{"test", 1});
    accumulator.Accumulate(metric::MetricResult{"test", 2});
    accumulator.Accumulate(metric::MetricResult{"test", 3});
    accumulator.Finalize();

    auto result1 = accumulator.Get();
    EXPECT_EQ(result1.sum, 6);
    EXPECT_DOUBLE_EQ(result1.average, 2.);

    accumulator.Reset();
    accumulator.Accumulate(metric::MetricResult{"test", 1});
    accumulator.Accumulate(metric::MetricResult{"test", 2});
    accumulator.Accumulate(metric::MetricResult{"test", 3});
    accumulator.Accumulate(metric::MetricResult{"test", 4});
    accumulator.Accumulate(metric::MetricResult{"test", 5});
    accumulator.Accumulate(metric::MetricResult{"test", 6});
    accumulator.Accumulate(metric::MetricResult{"test", 7});
    accumulator.Finalize();

    auto result2 = accumulator.Get();
    EXPECT_EQ(result2.sum, 28);
    EXPECT_DOUBLE_EQ(result2.average, 4.);
}

TEST(SumAverageAccumulatorTest, WithoutFinalize) {
    SumAverageAccumulator accumulator;

    accumulator.Accumulate(metric::MetricResult{"test", 1});

    EXPECT_THROW(accumulator.Get(), std::runtime_error);
}

TEST(SumAverageAccumulatorTest, OnlyFinalize) {
    SumAverageAccumulator accumulator;

    accumulator.Finalize();

    EXPECT_NO_THROW(accumulator.Get());
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
