#include "metric_impl/code_lines_count.hpp"

#include <gtest/gtest.h>

namespace analyzer::metric::metric_impl {

TEST(CodeLinesCountTest, Comments) {
    CodeLinesCountMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/comments.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "Func_comments"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);

    EXPECT_EQ(result.value, 3);
}

TEST(CodeLinesCountTest, Exceptions) {
    CodeLinesCountMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/exceptions.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "Try_Exceptions"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);

    EXPECT_EQ(result.value, 7);
}

TEST(CodeLinesCountTest, If) {
    CodeLinesCountMetric metric;

    analyzer::file::File file(std::string(TEST_FILES_DIR) + "/if.py");
    analyzer::function::FunctionExtractor extractor;
    auto functions = extractor.Get(file);

    auto func_it = std::ranges::find_if(functions, [](const auto &f) { return f.name == "testIf"; });

    ASSERT_NE(func_it, functions.end());
    auto result = metric.Calculate(*func_it);

    EXPECT_EQ(result.value, 3);
}



}  // namespace analyzer::metric::metric_impl
