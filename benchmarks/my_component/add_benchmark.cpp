#include "my_component/my_component.h"

#include <benchmark/benchmark.h>

static void add_throughput(benchmark::State &state)
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

    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(add_throughput);
