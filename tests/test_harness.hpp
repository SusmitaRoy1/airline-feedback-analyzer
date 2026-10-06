// Minimal zero-dependency test harness.
//
// Deliberately tiny: no FetchContent, no network in CI, nothing to install,
// and small enough to read end-to-end in two minutes.
//
//   TEST("name") { CHECK(cond); CHECK_EQ(a, b); }
//
// Register tests with the TEST macro; main() is provided at the bottom.
#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace afa_test {

struct Case {
    std::string name;
    std::function<void()> fn;
};

inline std::vector<Case>& registry() {
    static std::vector<Case> cases;
    return cases;
}

inline int& failures() {
    static int n = 0;
    return n;
}

inline std::string& current() {
    static std::string name;
    return name;
}

struct Registrar {
    Registrar(const std::string& name, std::function<void()> fn) {
        registry().push_back({name, std::move(fn)});
    }
};

inline void report(const std::string& expr, const std::string& detail, int line) {
    ++failures();
    std::cout << "    FAIL  line " << line << "  " << expr;
    if (!detail.empty()) std::cout << "\n          " << detail;
    std::cout << "\n";
}

template <typename A, typename B>
void check_eq(const A& a, const B& b, const char* expr, int line) {
    if (!(a == b)) {
        std::ostringstream os;
        os << "expected: " << b << "\n          actual:   " << a;
        report(expr, os.str(), line);
    }
}

inline void check_near(double a, double b, double eps, const char* expr, int line) {
    if (std::fabs(a - b) > eps) {
        std::ostringstream os;
        os << "expected: " << b << " (+/-" << eps << ")\n          actual:   " << a;
        report(expr, os.str(), line);
    }
}

inline int run_all() {
    int passed = 0;
    for (auto& c : registry()) {
        const int before = failures();
        current() = c.name;
        std::cout << "  " << c.name << "\n";
        try {
            c.fn();
        } catch (const std::exception& e) {
            report("unexpected exception", e.what(), 0);
        } catch (...) {
            report("unexpected unknown exception", "", 0);
        }
        if (failures() == before) ++passed;
    }
    const int total = static_cast<int>(registry().size());
    std::cout << "\n  " << passed << "/" << total << " tests passed";
    if (failures()) std::cout << "  (" << failures() << " assertion failures)";
    std::cout << "\n";
    return failures() == 0 ? 0 : 1;
}

}  // namespace afa_test

#define AFA_CAT2(a, b) a##b
#define AFA_CAT(a, b) AFA_CAT2(a, b)

#define TEST(name)                                                            \
    static void AFA_CAT(afa_test_fn_, __LINE__)();                            \
    static afa_test::Registrar AFA_CAT(afa_test_reg_, __LINE__)(              \
        name, AFA_CAT(afa_test_fn_, __LINE__));                               \
    static void AFA_CAT(afa_test_fn_, __LINE__)()

#define CHECK(cond)                                                           \
    do {                                                                      \
        if (!(cond)) afa_test::report(#cond, "", __LINE__);                   \
    } while (0)

#define CHECK_EQ(a, b) afa_test::check_eq((a), (b), #a " == " #b, __LINE__)

#define CHECK_NEAR(a, b, eps)                                                 \
    afa_test::check_near((a), (b), (eps), #a " ~= " #b, __LINE__)

#define CHECK_THROWS(expr)                                                    \
    do {                                                                      \
        bool threw = false;                                                   \
        try {                                                                 \
            (void)(expr);                                                     \
        } catch (...) {                                                       \
            threw = true;                                                     \
        }                                                                     \
        if (!threw) afa_test::report(#expr " should throw", "", __LINE__);    \
    } while (0)

// Marks a test the implementer still has to write. Prints a notice and passes,
// so CI stays green while the TODO list stays visible.
#define TODO_TEST(what)                                                       \
    std::cout << "    TODO  " << what << "\n"

#define AFA_TEST_MAIN()                                                       \
    int main() {                                                              \
        std::cout << "\n" << __FILE__ << "\n";                                \
        return afa_test::run_all();                                           \
    }
