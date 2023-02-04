#include "ArgParser.h"
#include <iostream>

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& vow) { // vow = vector_of_words
  std::cout << "Start" << std::endl;
  if ((vow.size() == 2) && (vow[1] == "--help")) {
    // some information about parser
    return true;
  }
  int i = 1;
  while (i < vow.size()) {
    if (vow[i][0] != '-') {
      for (int j = 0; j < arg.size(); j++) {
        if (arg[j].IsPositional()) {
          if (ArgumentParser::ArgumentClasses::IntArg == arg[j].arg_class) {
            (arg[j].int_arg.int_vector_argument.stored ? arg[j].int_arg.int_vector_argument.stored_vect: arg[j].int_arg.int_vector_argument.unstored_vect)->push_back(stoi(vow[i]));
          } else {
            (arg[j].string_arg.string_vector_argument.stored? arg[j].string_arg.string_vector_argument.stored_vect: arg[j].string_arg.string_vector_argument.unstored_vect)->push_back(vow[i]);
          }

          break;
        }
      }

      i++;
      continue;
    }

    if (vow[i][1] != '-') {
      int k = 1;
      std::string wd;
      while (k < vow[i].size()) {
        if (vow[i][k] != '=') {
          wd.push_back(vow[i][k]);
          k++;
        } else {
          break;
        }
      }

      if (k == vow[i].size()) {
        for (int k = 0; k < wd.size(); k++) {
          for (int j = 0; j < arg.size(); j++) {
            if (arg[j].argument_short_name == wd[k]) {
              if (arg[j].flag_arg.stored == true) {
                (*arg[j].flag_arg.stored_fl) = true;
              }
              else {
                if (arg[j].flag_arg.unstored_fl == NULL) {
                  arg[j].flag_arg.unstored_fl = new bool(true);
                }
                else {
                  (*arg[j].flag_arg.unstored_fl) = true;
                }
              }
              //if (arg[j].flag_arg.fl == NULL) arg[j].flag_arg.fl = new bool(true);
              //else (*arg[j].flag_arg.fl) = true;
              break;
            }
          }
        }
      } else {
        k = k + 1;
        std::string wd2 = "";
        while (k < vow[i].size()) {
          wd2.push_back(vow[i][k]);
          k++;
        }

        for (int i = 0; i < arg.size(); i++) {
          if (arg[i].argument_short_name == wd[0]) {
            if (arg[i].arg_class == ArgumentClasses::IntArg) {
              if (arg[i].int_arg.int_argument_class == ArgumentClass::Simple) {
                if (arg[i].int_arg.stored) {
                  (*arg[i].int_arg.stored_value_) = std::stoi(wd2);
                }
                else {
                  if (arg[i].int_arg.unstored_value_ == NULL) {
                    arg[i].int_arg.unstored_value_ = new int(std::stoi(wd2));
                  }
                  else {
                    (*arg[i].int_arg.unstored_value_) =std::stoi(wd2);
                  }
                }
                //if (arg[i].int_arg.value_ == NULL) arg[i].int_arg.value_ = new int(std::stoi(wd2));
                //else (*arg[i].int_arg.value_) = std::stoi(wd2);
              } else {
                (arg[i].int_arg.int_vector_argument.stored? arg[i].int_arg.int_vector_argument.stored_vect:arg[i].int_arg.int_vector_argument.unstored_vect)->push_back(std::stoi(wd2));
              }
            } else {
              if (arg[i].string_arg.int_argument_class == ArgumentClass::Simple) {
                if (arg[i].string_arg.stored) {
                  (*arg[i].string_arg.stored_value_) = wd2;
                }
                else {
                  if (arg[i].string_arg.unstored_value_ == NULL) {
                    arg[i].string_arg.unstored_value_ = new std::string(wd2);
                  }
                  else {
                    (*arg[i].string_arg.unstored_value_) = wd2;
                  }
                }

                //if (arg[i].string_arg.value_ == NULL) arg[i].string_arg.value_ = new std::string(wd2);
                //else (*arg[i].string_arg.value_) = wd2;
              } else {
                (arg[i].string_arg.string_vector_argument.stored? arg[i].string_arg.string_vector_argument.stored_vect:arg[i].string_arg.string_vector_argument.unstored_vect)->push_back(wd2);
              }
            }
          }
        }
      }

      i++;
      continue;
    }

    std::string wd = "";
    int k = 2;
    while (k < vow[i].size()) {
      if (vow[i][k] != '=') {
        wd.push_back(vow[i][k]);
        k++;
      } else {
        break;
      }
    }

    if (k == vow[i].size()) {
      for (int j = 0; j < arg.size(); j++) {
        if (arg[j].argument_name == wd) {
          if (arg[j].flag_arg.stored == true) {
            (*arg[j].flag_arg.stored_fl) = true;
          }
          else {
            if (arg[j].flag_arg.unstored_fl == NULL) {
              arg[j].flag_arg.unstored_fl = new bool(true);
            }
            else {
              (*arg[j].flag_arg.unstored_fl) = true;
            }
          }
          //if (arg[j].flag_arg.fl == NULL) arg[j].flag_arg.fl = new bool(true);
          //else (*arg[j].flag_arg.fl) = true;
          break;
        }
      }
    } else {
      k = k + 1;
      std::string wd2 = "";
      while (k < vow[i].size()) {
        wd2.push_back(vow[i][k]);
        k++;
      }
      for (int i = 0; i < arg.size(); i++) {
        if (arg[i].argument_name == wd) {
          if (arg[i].arg_class == ArgumentClasses::IntArg) {
            if (arg[i].int_arg.int_argument_class == ArgumentClass::Simple) {
              if (arg[i].int_arg.stored) {
                (*arg[i].int_arg.stored_value_) = std::stoi(wd2);
              }
              else {
                if (arg[i].int_arg.unstored_value_ == NULL) {
                  arg[i].int_arg.unstored_value_ = new int(std::stoi(wd2));
                }
                else {
                  (*arg[i].int_arg.unstored_value_) =std::stoi(wd2);
                }
              }
              //if (arg[i].int_arg.value_ == NULL) arg[i].int_arg.value_ = new int(std::stoi(wd2));
              //else (*arg[i].int_arg.value_) = std::stoi(wd2);
            } else {
              (arg[i].int_arg.int_vector_argument.stored ? arg[i].int_arg.int_vector_argument.stored_vect: arg[i].int_arg.int_vector_argument.unstored_vect)->push_back(std::stoi(wd2));
            }
          } else {
            if (arg[i].string_arg.int_argument_class == ArgumentClass::Simple) {
              if (arg[i].string_arg.stored) {
                (*arg[i].string_arg.stored_value_) = wd2;
              }
              else {
                if (arg[i].string_arg.unstored_value_ == NULL) {
                  arg[i].string_arg.unstored_value_ = new std::string(wd2);
                }
                else {
                  (*arg[i].string_arg.unstored_value_) = wd2;
                }
              }


              //if (arg[i].string_arg.value_ == NULL) arg[i].string_arg.value_ = new std::string(wd2);
              //else (*arg[i].string_arg.value_) = wd2;
            } else {
              (arg[i].string_arg.string_vector_argument.stored?arg[i].string_arg.string_vector_argument.stored_vect:arg[i].string_arg.string_vector_argument.unstored_vect)->push_back(wd2);
            }
          }
        }
      }
    }

    i++;
    continue;
  }


  for (int j = 0; j < arg.size(); j++) {
    switch (arg[j].arg_class) {
      case ArgumentClasses::Flag:
        if ((arg[j].flag_arg.stored == false) && (arg[j].flag_arg.unstored_fl == NULL)) return false;
        break;
      case ArgumentClasses::IntArg:
        if (arg[j].int_arg.int_argument_class == ArgumentClass::Simple) {
          if ((arg[j].int_arg.stored == false) && (arg[j].int_arg.unstored_value_ == NULL)) return false;
        } else {
          if ((arg[j].int_arg.int_vector_argument.stored ? arg[j].int_arg.int_vector_argument.stored_vect : arg[j].int_arg.int_vector_argument.unstored_vect)->size() < arg[j].int_arg.int_vector_argument.minsize)
            return false;
        }
        break;
      case ArgumentClasses::StringArg:
        if (arg[j].string_arg.int_argument_class == ArgumentClass::Simple) {
          if ((arg[j].string_arg.stored == false) && (arg[j].string_arg.unstored_value_ == NULL)) return false;
        } else {
          if ((arg[j].string_arg.string_vector_argument.stored ? arg[j].string_arg.string_vector_argument.stored_vect : arg[j].string_arg.string_vector_argument.unstored_vect)->size()
              < arg[j].string_arg.string_vector_argument.minsize)
            return false;
        }
    }
  }
  std::cout << "Finish" << std::endl;
  return true;
}
