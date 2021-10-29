#include "ParamCheckBox.h"

ParamCheckBox::ParamCheckBox(json _json, QString _name, string _key){
  name = _name;
  key = _key;

  val = _json["value"].get<bool>();
  setChecked(val);

  QObject::connect(this,&ParamCheckBox::stateChanged,this,&ParamCheckBox::slot_set_val);
}

ParamCheckBox::~ParamCheckBox() {

}

void ParamCheckBox::slot_set_val(int state) {
  if (state == 0)
    val = false;
  else if (state == 2)
    val = true;

  emit(signal_set_json_bool(name, key, val));
}
