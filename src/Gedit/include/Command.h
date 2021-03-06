#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

class Command {
public:
  inline Command() : args() {}
  static Command parse(const std::string& line);
  inline void setName(const char name) { this->name = name; }
  inline const char getName() const { return name; }
  inline std::vector<std::string>& getArgs() { return args; }
  void execute();
private:
  void createImage();
  void clearImage();
  void colourPixel();
  void print();
  void drawVertical();
  void drawHorizontal();
  void fillRegion();
  char name;
  std::vector<std::string> args;
};

#endif