#include "ParamComboBox.h"

/*
key = _key;
file_path = _file_path;

QObject::connect(this, &ParamComboBox::currentTextChanged,
  [&](const QString& item) {
#ifndef NDEBUG
        //          cout <<"NOTE::"<<key <<" : "<<item.toStdString() << endl;
#endif
        std::ifstream ifs(file_path);
        json j = json::parse(ifs);
        j["PARAM"][key]["VALUE"] = stoi(item.toStdString());
        std::ofstream ofs(file_path);
        ofs << j.dump(4);
        ofs.close();
      }
    );
 */

ParamComboBox::ParamComboBox(json _json, QString _name, string _key) {
  name = _name;
  key = _key;
  val = _json["value"].get<int>();
  setCurrentText(QString::number(val));


  for (json::iterator it = _json["options"].begin(); it != _json["options"].end(); ++it) {
      this->addItem(QString::number(it.value().get<int>()));
  }
  QObject::connect(this, &ParamComboBox::currentTextChanged, this, &ParamComboBox::slot_set_val);

}

ParamComboBox::~ParamComboBox() {

}

void ParamComboBox::slot_set_val(QString _val) {
  val = _val.toInt();
  setCurrentText(_val);

  emit(signal_set_json_int(name,key,val));

}


