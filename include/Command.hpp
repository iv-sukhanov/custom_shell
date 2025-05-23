#pragma once

#include <optional>
#include <string>
#include <vector>

class Command {
   public:
    Command(std::string name, std::vector<std::string> args);
    std::string getName() const;
    std::vector<std::string> getArgs() const;
    void setOutputRedirect(const std::string& file);
    void setInputRedirect(const std::string& file);
    std::optional<std::string> getOutputRedirect() const;
    std::optional<std::string> getInputRedirect() const;
    void setParallel(bool);
    bool isParallel() const;

   private:
    std::string name;
    std::vector<std::string> args;
    std::optional<std::string> inputFile;
    std::optional<std::string> outputFile;
    bool inParallel;
};
