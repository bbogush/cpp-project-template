#include "my_component/my_component.h"

#include <benchmark/benchmark.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <vector>

static void add_benchmark(benchmark::State &state)
{
    const project::my_component::MyComponent component;
    int a = 1;
    int b = 2;

    for (auto _ : state) {
        // Hide the operands from the optimizer so the call is not folded away
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
        int sum = component.add(a, b);
        benchmark::DoNotOptimize(sum);
    }
}

BENCHMARK(add_benchmark);

static void add_benchmark_p50_p99(benchmark::State &state)
{
    const project::my_component::MyComponent component;
    int a = 1;
    int b = 2;

    std::vector<std::uint64_t> samples;
    samples.reserve(state.max_iterations);

    for (auto _ : state) {
        const auto start = std::chrono::steady_clock::now();

        // Hide the operands from the optimizer so the call is not folded away
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);

        int sum = component.add(a, b);

        benchmark::DoNotOptimize(sum);

        const auto end = std::chrono::steady_clock::now();

        samples.push_back(
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    }

    // Calculate percentiles P50 and P99
    if (!samples.empty()) {
        std::sort(samples.begin(), samples.end());
        const auto percentile = [&samples](double p) {
            const auto index = static_cast<std::size_t>(
                p * static_cast<double>(samples.size() - 1));
            return samples[index];
        };
        state.counters["P50_ns"] = percentile(0.50);
        state.counters["P99_ns"] = percentile(0.99);
    }
}

BENCHMARK(add_benchmark_p50_p99);