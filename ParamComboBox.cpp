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
  key  = _key;

  // Detect whether this option is string-based or int-based
  if (_json.contains("options") && _json["options"].is_array() && !_json["options"].empty()) {
    const json& firstOpt = _json["options"].front();
    isStringOption = firstOpt.is_string();
  }
  else {
    isStringOption = false; // default: int
  }

  if (isStringOption) {
    // String-based option (ex - process_mode: "mpAB" / "mpADB")
    val_str = _json["value"].get<std::string>();

    for (json::iterator it = _json["options"].begin(); it != _json["options"].end(); ++it) {
      std::string opt = it.value().get<std::string>();
      this->addItem(QString::fromStdString(opt));
    }

    int idx = this->findText(QString::fromStdString(val_str));
    if (idx >= 0) {
      this->setCurrentIndex(idx);
    }
  }
  else {
    // Integer-based option (ex - samplerate: 16000 / 48000)
    val = _json["value"].get<int>();

    for (json::iterator it = _json["options"].begin(); it != _json["options"].end(); ++it) {
      int opt = it.value().get<int>();
      vec_option.push_back(opt);
      this->addItem(QString::number(opt));
    }

    int idx = this->findText(QString::number(val));
    if (idx >= 0) {
      this->setCurrentIndex(idx);
    }
  }

  QObject::connect(this, &ParamComboBox::currentTextChanged, this, &ParamComboBox::slot_set_val);
}

ParamComboBox::~ParamComboBox() {

}

void ParamComboBox::slot_set_val(QString _val) {
  if (isStringOption) {
    val_str = _val.toStdString();
    emit signal_set_json_str(name, key, val_str);
  } else {
    bool ok = false;
    int newVal = _val.toInt(&ok);
    if (!ok) {
      return;
    }
    val = newVal;
    emit signal_set_json_int(name, key, val);
  }
}


