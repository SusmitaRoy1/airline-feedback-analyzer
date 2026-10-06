// Command-line entry point.
//
// YOUR IMPLEMENTATION -- commits 8 to 11.
//
// Right now this only wires up `--help` and `version`, so the binary builds
// and runs from commit 1. Fill in the subcommands as the library lands.
//
// Conventions to keep:
//   * data to stdout, errors to stderr
//   * non-zero exit on failure
//   * never write a file unless --out was given
//   * --seed makes the train/dev/test split reproducible

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "afa/csv_reader.hpp"
#include "afa/evaluator.hpp"
#include "afa/lexicon.hpp"
#include "afa/scorer.hpp"
#include "afa/tokenizer.hpp"

namespace {

constexpr char kVersion[] = "0.1.0";

int usage(std::ostream& os) {
    os << "afa " << kVersion << " -- airline feedback analyzer\n\n"
       << "usage:\n"
       << "  afa train    --input <csv> --out <lexicon> [--max-terms 800] [--min-df 5]\n"
       << "  afa tune     --lexicon <file> --input <dev csv>\n"
       << "  afa eval     --lexicon <file> --input <test csv> [--format table|json|csv]\n"
       << "  afa classify --lexicon <file> --text \"...\" [--explain]\n"
       << "  afa classify --lexicon <file> --input <csv> [--out <csv>]\n"
       << "  afa sweep    --input <csv>\n"
       << "  afa version\n";
    return 0;
}

[[noreturn]] void not_implemented(const std::string& command) {
    std::cerr << "afa: '" << command << "' is not implemented yet.\n"
              << "See DESIGN.md for the specification and the commit plan.\n";
    std::exit(2);
}

}  // namespace

int main(int argc, char** argv) {
    const std::vector<std::string> args(argv + 1, argv + argc);

    if (args.empty() || args[0] == "--help" || args[0] == "-h" || args[0] == "help") {
        return usage(std::cout);
    }

    const std::string& command = args[0];

    if (command == "version" || command == "--version") {
        std::cout << kVersion << "\n";
        return 0;
    }

    if (command == "train" || command == "tune" || command == "eval" ||
        command == "classify" || command == "sweep") {
        not_implemented(command);
    }

    std::cerr << "afa: unknown command '" << command << "'\n\n";
    usage(std::cerr);
    return 1;
}
