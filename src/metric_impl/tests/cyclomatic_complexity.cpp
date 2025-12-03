#include "metric_impl/cyclomatic_complexity.hpp"

#include <gtest/gtest.h>

namespace analyzer::metric::metric_impl {

TEST(CyclomaticComplexityTest, Loops) {
    CyclomaticComplexityMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/loops.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "TestLoops"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);
    EXPECT_EQ(result.value, 4);
}

TEST(CyclomaticComplexityTest, ManyLines) {
    CyclomaticComplexityMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/many_lines.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "testmultiline"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);
    EXPECT_EQ(result.value, 2);
}

TEST(CyclomaticComplexityTest, NestIf) {
    CyclomaticComplexityMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/nested_if.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "Testnestedif"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);
    EXPECT_EQ(result.value, 4);
}

}  // namespace analyzer::metric::metric_impl
