#pragma once 

#include <QCheckBox>
#include <string>
#include "json.hpp"

using std::string;
using json = nlohmann::json;

class ParamCheckBox : public QCheckBox {
  Q_OBJECT

private:
  QString name;
  string key;
  bool val;

public:
  ParamCheckBox(json _json, QString name, string key);
  ~ParamCheckBox();

public slots:
  void slot_set_val(int  _state);

signals:
  void signal_set_json_bool(QString _name, string _key, bool _val);


};