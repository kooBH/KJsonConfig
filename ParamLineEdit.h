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
  string val_str;

public:
  enum class TYPE{ INT, DOUBLE, STR };
  TYPE type;

  ParamLineEdit(json _json, QString name, string key, int type_);
  ~ParamLineEdit();

public slots:
  void slot_set_val(const QString& text);

signals:
  void signal_set_json_double(QString _name, string _key, double _val);
  void signal_set_json_int(QString _name, string _key, int _val);
  void signal_set_json_str(QString _name, string _key, string val_);


};