#include "ParamLineEdit.h"

ParamLineEdit::ParamLineEdit(json _json, QString _name, string _key, bool _is_double) {
  name = _name;
  key = _key;
  is_double = _is_double;

  if(is_double)
    val = _json["value"].get<double>();
  else
    val = _json["value"].get<int>();
  setText(QString::number(val));

  QObject::connect(this, &ParamLineEdit::textChanged, this, &ParamLineEdit::slot_set_val);
}

ParamLineEdit::~ParamLineEdit() {

}

void ParamLineEdit::slot_set_val(const QString& text){
  bool is_valid;
  int temp_int;
  double temp_double;

  if(is_double) {
      temp_double = text.toDouble(&is_valid);
    }
    else {
      temp_int = text.toInt(&is_valid);
  }
  if (!is_valid)
    return;

  if (is_double) {
    val = temp_double;
    emit(signal_set_json_double(name, key, val));
  }
  else {
    val = (double)temp_int;
    emit(signal_set_json_int(name, key, (int)val));
  }
}