#include <benchmark/benchmark.h>

#include <thread>
#include <vector>

#include "main.hpp"

static void BM_ConcurrentQueuePush(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    Queue<int> q;
    std::vector<std::thread> threads;
    int num_threads = state.range(0);
    int items_per_thread = 1000;

    state.ResumeTiming();

    for (int i = 0; i < num_threads; ++i) {
      threads.emplace_back([&q, items_per_thread]() {
        for (int j = 0; j < items_per_thread; ++j) {
          q.push(j);
        }
      });
    }

    for (auto& t : threads) {
      t.join();
    }
  }

  state.SetItemsProcessed(state.iterations() * state.range(0) * 1000);
}

static void BM_ConcurrentQueuePop(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();  // Pause timing while setting up the test

    Queue<int> q;
    std::vector<std::thread> threads;
    int numThreads = state.range(0);
    int itemsPerThread = 1000;

    // Pre-fill the queue with enough items for the test
    for (int i = 0; i < numThreads * itemsPerThread; ++i) {
      q.push(i);
    }

    state.ResumeTiming();  // Resume timing for the actual benchmark

    for (int i = 0; i < numThreads; ++i) {
      threads.emplace_back([&q, itemsPerThread]() {
        for (int j = 0; j < itemsPerThread; ++j) {
          q.pop();
        }
      });
    }

    for (auto& t : threads) {
      t.join();
    }
  }

  state.SetItemsProcessed(state.iterations() * state.range(0) * 1000);
}

static void BM_ConcurrentQueueFront(benchmark::State& state) {
  for (auto _ : state) {
    Queue<int> q;
    q.push(1);  // Ensure the queue is not empty

    for (auto _ : state) {
      benchmark::DoNotOptimize(q.front());
    }
  }

  state.SetItemsProcessed(state.iterations());
}

// Register the function as a benchmark
BENCHMARK(BM_ConcurrentQueuePush)->Range(1, 8);  // Test with 1 to 8 threads
BENCHMARK(BM_ConcurrentQueuePop)->Range(1, 8);
BENCHMARK(BM_ConcurrentQueueFront)->Range(1, 8);
BENCHMARK_MAIN();