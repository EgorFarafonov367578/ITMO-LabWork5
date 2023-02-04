#pragma once
#include <string>
#include <vector>
#include <iostream>
namespace ArgumentParser {

enum ArgumentClass { Simple,  Multy };

struct FlagArgument {
  bool stored = false;
  bool* unstored_fl = NULL;
  bool* stored_fl = NULL;

  FlagArgument() {
    stored = false;
    unstored_fl = NULL;
    stored_fl = NULL;
  }

  FlagArgument& Default(bool f) {
    delete unstored_fl;
    unstored_fl = new bool(f);

    return (*this);
  }

  FlagArgument& StoreValue(bool& f) {
    delete unstored_fl;
    unstored_fl = NULL;
    stored = true;
    stored_fl = &f;

    return (*this);
  }
};

struct StringVectorArgument {
  int minsize;
  bool positional = false;
  bool stored = false;
  std::vector<std::string>* unstored_vect = new std::vector<std::string>;
  std::vector<std::string>* stored_vect = NULL;

  StringVectorArgument() {
    positional = false;
    stored = false;
    unstored_vect = new std::vector<std::string>;
    stored_vect = NULL;

    minsize = 0;
  }

  void SetMinsize(int min_size) {
    minsize = min_size;
  }

  StringVectorArgument& StoreValues(std::vector<std::string>& vc) {
    stored = true;
    delete unstored_vect;
    stored_vect = &vc;

    return (*this);
  }

  StringVectorArgument& StoreValue(std::vector<std::string>& vc) {
    stored = true;
    delete unstored_vect;
    stored_vect = &vc;

    return (*this);
  }

  StringVectorArgument& Positional() {
    positional = true;

    return (*this);
  }

  bool IsPositional() {
    return positional;
  }

  StringVectorArgument(const StringVectorArgument& orig) {
    stored = orig.stored;
    minsize = orig.minsize;
    stored_vect = orig.stored_vect;
    positional = orig.positional;
    if (orig.unstored_vect == NULL) {
      unstored_vect = NULL;
    }
    else {
      unstored_vect = new std::vector<std::string>(*orig.unstored_vect);
    }
  }

  void operator =(const StringVectorArgument& orig) {
    stored = orig.stored;
    minsize = orig.minsize;
    stored_vect = orig.stored_vect;
    positional = orig.positional;
    if (orig.unstored_vect == NULL) {
      unstored_vect = NULL;
    }
    else {
      unstored_vect = new std::vector<std::string>(*orig.unstored_vect);
    }
  }

  ~StringVectorArgument() {
    //std::cout << "SV" <<std::endl;
    if (unstored_vect != NULL) delete unstored_vect;
    //std::cout << "Fin" <<std::endl;
  }
};

struct StringArgument {
  ArgumentClass int_argument_class = ArgumentClass::Simple;
  StringVectorArgument string_vector_argument;
  bool stored;
  std::string* stored_value_ = NULL;
  std::string* unstored_value_ = NULL;

  StringArgument() {
    int_argument_class = ArgumentClass::Simple;
    string_vector_argument = StringVectorArgument();
    stored = false;
    stored_value_ = NULL;
    unstored_value_ = NULL;
  }

  StringVectorArgument& MultiValue() {
    int_argument_class = ArgumentClass::Multy;

    return string_vector_argument;
  }

  StringVectorArgument& MultiValue(int min_size) {
    int_argument_class = ArgumentClass::Multy;
    string_vector_argument.SetMinsize(min_size);

    return string_vector_argument;
  }

  StringArgument& StoreValue(std::string& value) {
    stored = true;
    delete unstored_value_;
    stored_value_ = &value;

    return (*this);
  }

  StringArgument& Default(const std::string& value) {
    delete unstored_value_;
    unstored_value_ = new std::string(value);

    return (*this);
  }

  bool IsPositional() {
    if (int_argument_class == ArgumentClass::Multy) {
      return string_vector_argument.IsPositional();
    }

    return false;
  }

  StringArgument(const StringArgument& orig) {
    stored = orig.stored;
    int_argument_class = orig.int_argument_class;
    stored_value_ = orig.stored_value_;
    string_vector_argument = orig.string_vector_argument;
    if (orig.unstored_value_ == NULL) {
      unstored_value_ = NULL;
    }
    else {
      unstored_value_ = new std::string(*orig.unstored_value_);
    }
  }

  ~StringArgument() {
    //std::cout << "S" <<std::endl;
    if (unstored_value_ != NULL) delete unstored_value_;
  }
};

struct IntVectorArgument {
  int minsize;
  bool positional = false;
  bool stored = false;
  std::vector<int>* unstored_vect = NULL;
  std::vector<int>* stored_vect = new std::vector<int>();
  IntVectorArgument() {
    minsize = 0;
  }

  void SetMinsize(int min_size) {
    minsize = min_size;
  }

  IntVectorArgument& StoreValues(std::vector<int>& vc) {
    stored_vect = (&vc);
    delete unstored_vect;
    stored = true;

    return (*this);
  }

  IntVectorArgument& StoreValue(std::vector<int>& vc) {
    stored_vect = (&vc);
    delete unstored_vect;
    stored = true;

    return (*this);
  }

  IntVectorArgument& Positional() {
    positional = true;

    return (*this);
  }

  bool IsPositional() {
    return positional;
  }

  IntVectorArgument(const IntVectorArgument& orig) {
    stored = orig.stored;
    minsize = orig.minsize;
    stored_vect = orig.stored_vect;
    if (orig.unstored_vect == NULL) {
      unstored_vect = NULL;
    }
    else {
      unstored_vect = new std::vector<int> (*orig.unstored_vect);
    }
  }

  ~IntVectorArgument() {
    //std::cout << "IV" <<std::endl;
    if (unstored_vect != NULL) delete unstored_vect;
  }
};

struct IntArgument {
  ArgumentClass int_argument_class = ArgumentClass::Simple;
  IntVectorArgument int_vector_argument;
  int* unstored_value_ = NULL;
  int* stored_value_ = NULL;
  bool stored = false;

  IntArgument() {
    int_argument_class = ArgumentClass::Simple;
    int_vector_argument;
    unstored_value_ = NULL;
    stored_value_ = NULL;
    stored = false;
  }

  IntVectorArgument& MultiValue() {
    int_argument_class = ArgumentClass::Multy;

    return int_vector_argument;
  }

  IntVectorArgument& MultiValue(int min_size) {
    int_argument_class = ArgumentClass::Multy;
    int_vector_argument.SetMinsize(min_size);

    return int_vector_argument;
  }

  bool IsPositional() {
    if (int_argument_class == ArgumentClass::Multy) {
      return int_vector_argument.IsPositional();
    }

    return false;
  }

  IntArgument(const IntArgument& orig) {
    stored = orig.stored;
    int_vector_argument = orig.int_vector_argument;
    int_argument_class = orig.int_argument_class;
    stored_value_ = orig.stored_value_;
    if (orig.unstored_value_ != NULL) {
      unstored_value_ = new int(*orig.unstored_value_);
    }
    else {
      unstored_value_ = NULL;
    }
  }

  ~IntArgument() {
    //std::cout << "I" <<std::endl;
    if (unstored_value_ != NULL) delete unstored_value_;
  }
};

enum ArgumentClasses { IntArg, StringArg, Flag };

struct Argument {
  std::string argument_name;
  char argument_short_name;
  std::string help;
  ArgumentClasses arg_class;
  FlagArgument flag_arg;
  IntArgument int_arg;
  StringArgument string_arg;

  bool IsPositional() {
    if (arg_class == ArgumentClasses::IntArg) {
      return int_arg.IsPositional();
    }
    if (arg_class == ArgumentClasses::StringArg) {
      return string_arg.IsPositional();
    }

    return false;
  }

  Argument(ArgumentClasses arg_cl, const std::string& name) {
    arg_class = arg_cl;
    argument_name = name;
    argument_short_name = ' ';
    help = "";
  }

  Argument(ArgumentClasses arg_cl, const std::string& name, char c_name) {
    arg_class = arg_cl;
    argument_name = name;
    argument_short_name = c_name;
    help = "";
  }

  Argument(ArgumentClasses arg_cl, const std::string& name, char c_name, const std::string& help_for_arg) {
    arg_class = arg_cl;
    argument_name = name;
    argument_short_name = c_name;
    help = help_for_arg;
  }
};

class ArgParser {
 private:
  std::string name;
  std::vector<Argument> arg;
  char help_char = ' ';
  std::string help_string1 = "";
  std::string help_string2 = "";
 public:
  IntArgument& AddIntArgument(const std::string& name) {
    arg.push_back(Argument(ArgumentClasses::IntArg, name));

    return arg[arg.size() - 1].int_arg;
  }

  IntArgument& AddIntArgument(char c_name, const std::string& name) {
    arg.push_back(Argument(ArgumentClasses::IntArg, name, c_name));

    return arg[arg.size() - 1].int_arg;
  }

  IntArgument& AddIntArgument(const std::string& name, const std::string& help_for_int) {
    arg.push_back(Argument(ArgumentClasses::IntArg, name, ' ', help_for_int));

    return arg[arg.size() - 1].int_arg;
  }

  StringArgument& AddStringArgument(const std::string& name) {
    arg.push_back(Argument(ArgumentClasses::StringArg, name));

    return arg[arg.size() - 1].string_arg;
  }

  StringArgument& AddStringArgument(char c_name, const std::string& name) {
    arg.push_back(Argument(ArgumentClasses::StringArg, name, c_name));

    return arg[arg.size() - 1].string_arg;
  }

  StringArgument& AddStringArgument(char c_name, const std::string& name, const std::string& help_for_string) {
    arg.push_back(Argument(ArgumentClasses::StringArg, name, c_name, help_for_string));

    return arg[arg.size() - 1].string_arg;
  }

  FlagArgument& AddFlag(const std::string& name) {
    arg.push_back(Argument(ArgumentClasses::Flag, name));

    return arg[arg.size() - 1].flag_arg;
  }

  FlagArgument& AddFlag(char c_name, const std::string& name) {
    arg.push_back(Argument(ArgumentClasses::Flag, name, c_name));

    return arg[arg.size() - 1].flag_arg;
  }

  FlagArgument& AddFlag(char c_name, const std::string& name, const std::string& help_for_flag) {
    arg.push_back(Argument(ArgumentClasses::Flag, name, c_name, help_for_flag));

    return arg[arg.size() - 1].flag_arg;
  }

  FlagArgument& AddFlag(const std::string& name, const std::string& help_for_flag) {
    arg.push_back(Argument(ArgumentClasses::Flag, name, ' ', help_for_flag));

    return arg[arg.size() - 1].flag_arg;
  }

  ArgParser(const std::string& arg_name) {
    name = arg_name;
  }

  bool Parse(const std::vector<std::string>& vow); // vow = vector_of_words

  bool Parse(int argc, char** argv) {
    std::vector<std::string> input;
    for (int i = 0; i < argc; i++) {
      input.push_back(argv[i]);
    }

    return Parse(input);
  }

  std::string GetStringValue(const std::string& arg_n) {
    for (int i = 0; i < arg.size(); i++) {
      if (arg[i].argument_name == arg_n) {
        if (!arg[i].string_arg.stored) {
          std::cout << "WTF" << std::endl;
        }
        if (arg[i].string_arg.unstored_value_ != NULL) {
          std::cout << "WTF" << std::endl;
        }
        if ((arg[i].string_arg.stored ? arg[i].string_arg.stored_value_: arg[i].string_arg.unstored_value_) != NULL) {
          std::cout << "WTF" << std::endl;
        }
        std::cout << *(arg[i].string_arg.stored ? arg[i].string_arg.stored_value_: arg[i].string_arg.unstored_value_) << std::endl;
        return (*(arg[i].string_arg.stored ? arg[i].string_arg.stored_value_: arg[i].string_arg.unstored_value_));
      }
    }
  }

  int GetIntValue(const std::string& arg_n) {
    for (int i = 0; i < arg.size(); i++) {
      if (arg[i].argument_name == arg_n) {
        return (*(arg[i].int_arg.stored ? arg[i].int_arg.stored_value_: arg[i].int_arg.unstored_value_));
      }
    }
  }

  int GetIntValue(const std::string& arg_n, int j) {
    for (int i = 0; i < arg.size(); i++) {
      if (arg[i].argument_name == arg_n) {
        return ((*(arg[i].int_arg.int_vector_argument.stored ? arg[i].int_arg.int_vector_argument.stored_vect: arg[i].int_arg.int_vector_argument.unstored_vect))[j]);
      }
    }
  }

  bool GetFlag(const std::string& arg_n) {
    for (int i = 0; i < arg.size(); i++) {
      if (arg[i].argument_name == arg_n) {
        return (arg[i].flag_arg.stored? *arg[i].flag_arg.stored_fl: *arg[i].flag_arg.unstored_fl);
      }
    }
  }

  bool Help() {
    return true;
  }

  void AddHelp(char h, const std::string& hp1, const std::string& hp2) {
    help_char = h;
    help_string1 = hp1;
    help_string2 = hp2;
  }

  std::string HelpDescription() {
    std::string help_discription;
    for (int i = 0; i < arg.size(); i++) {
      if (arg[i].arg_class == ArgumentClasses::IntArg) {
        if (arg[i].int_arg.int_argument_class == ArgumentClass::Simple) {
          help_discription.append(
              "Simple int argument, Name: " + arg[i].argument_name + ", Short name: " + arg[i].argument_short_name
                  + ", Some help: " + arg[i].help);
        } else {
          help_discription.append(
              "Multy int argument, Name: " + arg[i].argument_name + ", Short name: " + arg[i].argument_short_name
                  + ", Some help: " + arg[i].help);
        }
      }
      if (arg[i].arg_class == ArgumentClasses::StringArg) {
        if (arg[i].string_arg.int_argument_class == ArgumentClass::Simple) {
          help_discription.append(
              "Simple int argument, Name: " + arg[i].argument_name + ", Short name: " + arg[i].argument_short_name
                  + ", Some help: " + arg[i].help);
        } else {
          help_discription.append(
              "Multy int argument, Name: " + arg[i].argument_name + ", Short name: " + arg[i].argument_short_name
                  + ", Some help: " + arg[i].help);
        }
      }
      if (arg[i].arg_class == ArgumentClasses::Flag) {
        help_discription.append(
            "Multy int argument, Name: " + arg[i].argument_name + ", Short name: " + arg[i].argument_short_name
                + ", Some help: " + arg[i].help);
      }
    }
    return help_discription;
  }
};

} // namespace ArgumentParser
