#pragma once

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>

#include <vector>
#include <tuple>
#include <map>
#include <type_traits>
#include <string>
#include <iostream>

#include <fstream>

#include "ParamLineEdit.h"
#include "ParamComboBox.h"
#include "ParamCheckBox.h"
#include "json.hpp"

using json = nlohmann::ordered_json;
using std::string;
using std::vector;
using std::tuple;
using std::map;


class KJsonConfig : public QWidget {
  Q_OBJECT
  
private : 
  // TODO(2024.11.19)
  // Loadable Config is not implemented.
  bool isLoadable;

  QHBoxLayout* layout_main = nullptr;

  map<QString, tuple<json, string, QLabel*>>map_json;
  vector<tuple<QWidget*, QVBoxLayout*>> vec_item;
  // For a Loadable config
  vector<tuple<QHBoxLayout*,QPushButton*, QLabel*>> vec_load;

  vector<tuple<QLabel*, ParamComboBox*>> vec_ComboBox;
  vector<tuple<QLabel*, ParamLineEdit*>> vec_LineEdit;
  vector<tuple<QLabel*, ParamCheckBox*>> vec_CheckBox;

  // <name, path, json>

  void update_json(json j,string path);

  void AddInternal(QString name, string path,
                   bool isLoadable_,
                   QVBoxLayout* externalLayout);

  const json* getValueNode(const QString& name, const std::string& key) const;

  explicit KJsonConfig(QWidget* parent = nullptr);
  static KJsonConfig* s_instance;

public:
  static KJsonConfig& instance() {
    // Lazy initialization; should be called from GUI thread
    if (!s_instance) {
      s_instance = new KJsonConfig(); // parentless top-level widget
    }
    return *s_instance;
  }

  ~KJsonConfig();
  
  void Add(QString name, string path, bool isLoadable_=false);

  // use if adding widget to external layout
  void AddToLayout(QString name, string path,
                   QVBoxLayout* externalLayout,
                   bool isLoadable_=false);

  template<typename T>
  T getValue(const QString& name, const std::string& key, T defaultValue) const {
    const json* node = getValueNode(name, key);
    if (!node) {
      return defaultValue;
    }

    try {
      const json& j = *node;

      if constexpr (std::is_same_v<T, bool>) {
        if (j.is_boolean()) return j.get<bool>();
        if (j.is_number_integer() || j.is_number_unsigned()) return j.get<int>() != 0;
        if (j.is_number_float()) return j.get<double>() != 0.0;
        if (j.is_string()) {
          const auto s = j.get<std::string>();
          if (s == "true" || s == "1")  return true;
          if (s == "false" || s == "0") return false;
        }
        return defaultValue;
      }
      else if constexpr (std::is_same_v<T, int>) {
        if (j.is_number_integer() || j.is_number_unsigned()) return j.get<int>();
        if (j.is_number_float())   return static_cast<int>(j.get<double>());
        if (j.is_boolean())        return j.get<bool>() ? 1 : 0;
        if (j.is_string())         return std::stoi(j.get<std::string>());
        return defaultValue;
      }
      else if constexpr (std::is_same_v<T, double>) {
        if (j.is_number_float())   return j.get<double>();
        if (j.is_number_integer() || j.is_number_unsigned()) return static_cast<double>(j.get<int>());
        if (j.is_boolean())        return j.get<bool>() ? 1.0 : 0.0;
        if (j.is_string())         return std::stod(j.get<std::string>());
        return defaultValue;
      }
      else if constexpr (std::is_same_v<T, std::string>) {
        if (j.is_string())         return j.get<std::string>();
        if (j.is_boolean())        return j.get<bool>() ? "true" : "false";
        if (j.is_number_integer() || j.is_number_unsigned()) return std::to_string(j.get<int>());
        if (j.is_number_float())   return std::to_string(j.get<double>());
        return defaultValue;
      }
      else {
        // Fallback for other types - rely on nlohmann::json conversion
        return j.get<T>();
      }
    } catch (...) {
      return defaultValue;
    }
  }

  //https://stackoverflow.com/questions/5637197/two-square-bracket-overloading
  // => no [][] overloading : need to return pointer
  json operator[](string name) {
    auto val = std::get<0>(map_json[QString::fromStdString(name)]);
    return val;
    /*
    switch (val.type()) {
    //case json::value_t::object :
      //break;
    case json::value_t::boolean :
      return val;
      break;
    case json::value_t::number_float :
      break;
    case json::value_t::number_integer :
      break;
    defualt:
      printf("ERROR::unsupported json type:%d\n",val.type());
    
    }
    */

  }

public slots :
  /* No Template Function for Signal-Slot system */
  // https://stackoverflow.com/questions/26950718/how-to-use-templates-with-qt-signals-and-slots
  //template<typename T>
  //void slot_set_json_val(QString name, string key, T val);
  void slot_set_json_bool(QString name, string key, bool val);
  void slot_set_json_int(QString name, string key, int val);
  void slot_set_json_double(QString name, string key, double val);
  void slot_set_json_str(QString name, string key, std::string val);

};
