// delay_accuracy.cpp

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <sys/syspage.h>
#include <sys/neutrino.h>
#include <limits>

using namespace std;

#define NUM_ITERATIONS 1000

inline long long getClockCycles() {
    return ClockCycles();
}

void test_delay_accuracy() {
    long long total_delay = 0;
    long long min_delay = LLONG_MAX;
    long long max_delay = LLONG_MIN;

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        long long start = getClockCycles();
        delay(1);  // Задержка на 1 миллисекунду
        long long end = getClockCycles();

        long long delay_cycles = end - start;
        total_delay += delay_cycles;
        
        if (delay_cycles < min_delay) {
            min_delay = delay_cycles;
        }
        if (delay_cycles > max_delay) {
            max_delay = delay_cycles;
        }
    }

    double average_delay = (double)total_delay / NUM_ITERATIONS;
    cout << "Average delay (cycles): " << average_delay << endl;
    cout << "Min delay (cycles): " << min_delay << endl;
    cout << "Max delay (cycles): " << max_delay << endl;

    // Перевод в секунды
    double average_delay_sec = average_delay / (double)SYSPAGE_ENTRY(qtime)->cycles_per_sec;
    cout << "Average delay (sec): " << average_delay_sec << endl;
}

int main() {
    test_delay_accuracy();
    return 0;
}
