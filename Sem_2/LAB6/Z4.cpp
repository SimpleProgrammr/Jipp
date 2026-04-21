//
// Created by Elmo on 16/04/2026.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <cmath>
#include <filesystem>
#include <iomanip>
#include <__chrono/file_clock.h>

using namespace std;
namespace fs = std::filesystem;


struct DivisionByZeroError : std::runtime_error {
    DivisionByZeroError() : std::runtime_error("dzielenie przez zero") {
    }
};

struct NegativeSqrtError : std::runtime_error {
    explicit NegativeSqrtError(double x)
        : std::runtime_error("pierwiastek z liczby ujemnej: " + std::to_string(x)) {
    }
};

struct FileNotFoundError : std::runtime_error {
    explicit FileNotFoundError(const std::string &path)
        : std::runtime_error("nie można otworzyć pliku: " + path) {
    }
};

struct EmptyFileError : std::runtime_error {
    explicit EmptyFileError(const std::string &path)
        : std::runtime_error("plik nie zawiera danych: " + path) {
    }
};


class Task {
public:
    virtual ~Task() = default;

    virtual std::string name() const = 0;

    virtual double run() const = 0;
};


class DivideTask : public Task {
    double a_, b_;

public:
    DivideTask(double a, double b) : a_(a), b_(b) {
    }

    std::string name() const override {
        return "DivideTask(" + std::to_string(a_) + " / " + std::to_string(b_) + ")";
    }

    double run() const override {
        if (b_ == 0.0)
            throw DivisionByZeroError{};
        return a_ / b_;
    }
};

class SqrtTask : public Task {
    double x_;

public:
    explicit SqrtTask(double x) : x_(x) {
    }

    std::string name() const override {
        return "SqrtTask(" + std::to_string(x_) + ")";
    }

    double run() const override {
        if (x_ < 0.0)
            throw NegativeSqrtError{x_};
        return std::sqrt(x_);
    }
};


class FileSizeTask : public Task {
    std::string path_;

public:
    explicit FileSizeTask(std::string path) : path_(std::move(path)) {
    }

    std::string name() const override {
        return "FileSizeTask(\"" + path_ + "\")";
    }

    double run() const override {
        std::error_code ec;
        auto size = fs::file_size(path_, ec);
        if (ec)
            throw FileNotFoundError{path_};
        return static_cast<double>(size);
    }
};

class MeanFromBinaryFileTask : public Task {
    std::string path_;

public:
    explicit MeanFromBinaryFileTask(std::string path) : path_(std::move(path)) {
    }

    std::string name() const override {
        return "MeanFromBinaryFileTask(\"" + path_ + "\")";
    }

    double run() const override {
        std::ifstream file(path_, std::ios::binary);
        if (!file.is_open())
            throw FileNotFoundError{path_};

        double value{};
        double sum = 0.0;
        std::size_t count = 0;

        while (file.read(reinterpret_cast<char *>(&value), sizeof(double))) {
            sum += value;
            ++count;
        }

        if (count == 0)
            throw EmptyFileError{path_};

        return sum / static_cast<double>(count);
    }
};


class TaskRunner {
public:
    void runAll(const std::vector<std::unique_ptr<Task> > &tasks) const {
        const int w = 50;

        std::cout << std::string(w, '=') << "\n";
        std::cout << "  Task Executor — uruchamianie " << tasks.size() << " zadań\n";
        std::cout << std::string(w, '=') << "\n\n";

        int ok = 0, failed = 0;

        for (const auto &task: tasks) {
            std::cout << "[TASK] " << task->name() << "\n";
            try {
                double result = task->run();
                std::cout << "  [OK]  wynik = "
                        << std::fixed << std::setprecision(6) << result << "\n";
                ++ok;
            } catch (const DivisionByZeroError &e) {
                std::cout << "  [ERR] Błąd matematyczny: " << e.what() << "\n";
                ++failed;
            } catch (const NegativeSqrtError &e) {
                std::cout << "  [ERR] Błąd matematyczny: " << e.what() << "\n";
                ++failed;
            } catch (const EmptyFileError &e) {
                std::cout << "  [ERR] Błąd pliku: " << e.what() << "\n";
                ++failed;
            } catch (const FileNotFoundError &e) {
                std::cout << "  [ERR] Błąd pliku: " << e.what() << "\n";
                ++failed;
            } catch (const std::exception &e) {
                std::cout << "  [ERR] Nieoczekiwany błąd: " << e.what() << "\n";
                ++failed;
            }
            std::cout << "\n";
        }

        std::cout << std::string(w, '-') << "\n";
        std::cout << "  Podsumowanie: "
                << ok << " OK, "
                << failed << " błędów (łącznie: " << tasks.size() << ")\n";
        std::cout << std::string(w, '=') << "\n";
    }
};


static void createSampleBinaryFile(const std::string &path,
                                   const std::vector<double> &values) {
    std::ofstream file(path, std::ios::binary);
    for (double v: values)
        file.write(reinterpret_cast<const char *>(&v), sizeof(double));
}

int main() {
    createSampleBinaryFile("numbers.bin", {1.5, 2.5, 3.5, 4.5, 5.5});
    createSampleBinaryFile("empty.bin", {});


    std::vector<std::unique_ptr<Task> > tasks;

    tasks.push_back(std::make_unique<DivideTask>(10.0, 4.0));
    tasks.push_back(std::make_unique<DivideTask>(7.0, 0.0));
    tasks.push_back(std::make_unique<SqrtTask>(144.0));
    tasks.push_back(std::make_unique<SqrtTask>(-9.0));
    tasks.push_back(std::make_unique<FileSizeTask>("task_executor.cpp"));
    tasks.push_back(std::make_unique<FileSizeTask>("nie_istnieje.txt"));
    tasks.push_back(std::make_unique<MeanFromBinaryFileTask>("numbers.bin"));
    tasks.push_back(std::make_unique<MeanFromBinaryFileTask>("empty.bin"));
    tasks.push_back(std::make_unique<MeanFromBinaryFileTask>("brak.bin"));

    TaskRunner runner;
    runner.runAll(tasks);

    // Sprzątanie
    fs::remove("numbers.bin");
    fs::remove("empty.bin");

    return 0;
}