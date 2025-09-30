#pragma once

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <vector>
#include <tuple>
#include <map>

#include <string>
using std::string;

#include "json.hpp"
using nlohmann::json;
#include <fstream>
#include <iostream>
#include <QPushButton>
#include <QFileDialog>

#include "ParamLineEdit.h"
#include "ParamComboBox.h"
#include "ParamCheckBox.h"


using std::vector;
using std::tuple;
using std::map;


class KJsonConfig : public QWidget {
  Q_OBJECT
  
private : 
  // TODO(2024.11.19)
  // Loadable Config is not implemented.
  bool isLoadable;

#ifdef green_theme
  QHBoxLayout layout_main;
  //vector<tuple<json, QString, string, QLabel*>> vec_json;
#else
  QHBoxLayout* layout_main = nullptr;
#endif

  map<QString, tuple<json, string, QLabel*>>map_json;
  vector<tuple<QWidget*, QVBoxLayout*>> vec_item;
  // For a Loadable config
  vector<tuple<QHBoxLayout*,QPushButton*, QLabel*>> vec_load;

  vector<tuple<QLabel*, ParamComboBox*>> vec_ComboBox;
  vector<tuple<QLabel*, ParamLineEdit*>> vec_LineEdit;
  vector<tuple<QLabel*, ParamCheckBox*>> vec_CheckBox;

  // <name, path, json>

  void update_json(json j,string path);

public:
  KJsonConfig();
  ~KJsonConfig();
  void Add(QString name, string path, bool isLoadable_=false);

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
