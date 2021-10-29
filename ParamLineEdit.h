#pragma once

#include <QLineEdit>
#include <string>
using std::string;
#include "json.hpp"

using std::string;
using json = nlohmann::json;

class ParamLineEdit: public QLineEdit {
  Q_OBJECT

private:
  QString name;
  string key;
  double val;
  bool is_double;

public:
  ParamLineEdit(json _json, QString name, string key, bool is_double);
  ~ParamLineEdit();

public slots:
  void slot_set_val(const QString& text);

signals:
  void signal_set_json_double(QString _name, string _key, double _val);
  void signal_set_json_int(QString _name, string _key, int _val);


};