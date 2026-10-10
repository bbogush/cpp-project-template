#include "my_component.h"

#include <thread>

namespace project::my_component {

int MyComponent::add(int a, int b) const
{
    // Simulate some heavy computation
    const auto until = std::chrono::steady_clock::now() + std::chrono::microseconds(1);
    while (std::chrono::steady_clock::now() < until) {}

    return a + b;
}

} // namespace project::my_component
