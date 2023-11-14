#include "ParamLineEdit.h"

ParamLineEdit::ParamLineEdit(json _json, QString _name, string _key, int type_) {
  name = _name;
  key = _key;
  type = static_cast<TYPE>(type_);

  switch (type){
  case ParamLineEdit::TYPE::INT:
    val = _json["value"].get<int>();
    setText(QString::number(val));
    break;
  case ParamLineEdit::TYPE::DOUBLE:
    val = _json["value"].get<double>();
    setText(QString::number(val));
    break;
  case ParamLineEdit::TYPE::STR:
    val_str = _json["value"].get<string>();
    setText(QString::fromStdString(val_str));
    break;
  default:
    break;
  }

  QObject::connect(this, &ParamLineEdit::textChanged, this, &ParamLineEdit::slot_set_val);
}

ParamLineEdit::~ParamLineEdit() {

}

void ParamLineEdit::slot_set_val(const QString& text){
  bool is_valid;
  int temp_int;
  double temp_double;
  string temp_str;

  switch (type) {
  case TYPE::DOUBLE:
    temp_double = text.toDouble(&is_valid);
    val = temp_double;
    emit(signal_set_json_double(name, key, val));
    break;
  case TYPE::INT:
    temp_int = text.toInt(&is_valid);
    val = (double)temp_int;
    emit(signal_set_json_int(name, key, (int)val));
    break;
  case TYPE::STR:
    temp_str = text.toStdString();
    val_str = temp_str;
    emit(signal_set_json_str(name, key, val_str));
    break;
  }
}