#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"

namespace analyzer {

namespace rv = std::ranges::views;
namespace rs = std::ranges;

auto AnalyseFunctions(const std::vector<std::string> &files,
                      const analyzer::metric::MetricExtractor &metric_extractor) {
    using ResultType = std::vector<std::pair<analyzer::function::Function, analyzer::metric::MetricResults>>;

    return files 
            | rv::transform([](const std::string &filename) {
                    analyzer::file::File file(filename);
                    analyzer::function::FunctionExtractor extractor;
                    return extractor.Get(file);
                }) 
            | rv::join
            | rv::transform([&](const analyzer::function::Function &func) {
                    return std::make_pair(func, metric_extractor.Get(func));
                }) 
            | rs::to<ResultType>();
}

auto SplitByClasses(const auto &analysis) {
    return analysis
            | rv::filter([](const auto &item) { return item.first.class_name.has_value(); })
            | rv::chunk_by([](const auto &a, const auto &b) { return a.first.class_name == b.first.class_name; });
}

auto SplitByFiles(const auto &analysis) {
     return analysis
            | rv::chunk_by([](const auto &a, const auto &b) { return a.first.filename == b.first.filename; });
}

void AccumulateFunctionAnalysis(const auto &analysis,
                                const analyzer::metric_accumulator::MetricsAccumulator &accumulator) {
    rs::for_each(analysis | rv::values, [&](const auto &metric_results) {
        accumulator.AccumulateNextFunctionResults(metric_results);
    });
}

}  // namespace analyzer
