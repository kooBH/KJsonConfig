#pragma once

#include <QComboBox>
#include <vector>
using std::vector;

#include <string>
using std::string;


#include "json.hpp"
using nlohmann::json;


class ParamComboBox : public QComboBox {
  Q_OBJECT
private:
  std::string key;
  QString name;

  int val = 0;
  std::string val_str;
  
  vector<int> vec_option;
  bool isStringOption = false;

public:
  ParamComboBox(json _json, QString name, std::string _key);

    ~ParamComboBox();
public slots:
  void slot_set_val(QString  _val);

signals:
  void signal_set_json_int(QString _name, string _key, int _val);
  void signal_set_json_str(QString _name, string _key, std::string _val);
};
