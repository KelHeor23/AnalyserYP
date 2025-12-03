#include "metric_impl/parameters_count.hpp"

#include <gtest/gtest.h>

namespace analyzer::metric::metric_impl {

TEST(ParametersCountTest, ManyParameters) {
    CountParametersMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/many_parameters.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "__test_multiparameters__"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);
    EXPECT_EQ(result.value, 5);
}

TEST(ParametersCountTest, MatchCase) {
    CountParametersMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/match_case.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "test_Match_case"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);
    EXPECT_EQ(result.value, 1);
}

TEST(ParametersCountTest, Simple) {
    CountParametersMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/simple.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "test_simple"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);
    EXPECT_EQ(result.value, 0);
}

TEST(ParametersCountTest, Comments) {
    CountParametersMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/comments.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "Func_comments"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);
    EXPECT_EQ(result.value, 3);
}

}  // namespace analyzer::metric::metric_impl
