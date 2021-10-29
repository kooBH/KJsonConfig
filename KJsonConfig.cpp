#include "KJsonConfig.h"



KJsonConfig::KJsonConfig() {

  setLayout(&layout_main);
}

KJsonConfig::~KJsonConfig() {

}
/*
{
    "param 1": {
    "type":"bool",
    "value":true,
    "default":false
  },
     "param 2": {
    "type":"bool",
    "value":true,
    "default":false
  }
}

*/
void KJsonConfig::Add(QString name, string path) {
   /*read json from path*/
  std::ifstream ifs(path);

  if (!ifs.is_open()) {
    QMessageBox::critical(
      this,
      tr("KParam"),
      tr("Can't Open Config.json File!"));
    exit(-1);
  }

  /*parse type*/
  json j = json::parse(ifs);
  QLabel* t_name = new QLabel(name);

  //vec_json.push_back(std::make_tuple(j,name,path,t_name));
  map_json.insert({ name,std::make_tuple(j,path,t_name) });

  QWidget* t_widget = new QWidget();
  QVBoxLayout* t_layout = new QVBoxLayout();


  t_widget->setLayout(t_layout);
  layout_main.addWidget(t_widget);

  vec_item.push_back(std::make_tuple(t_widget,t_layout));

  t_layout->addWidget(t_name);

  t_layout->setAlignment(Qt::AlignTop);

  for (json::iterator it = j.begin(); it != j.end(); ++it) {
    if (!it.value()["type"].get<string>().compare("option")) {
      QLabel* t_label = new QLabel(QString::fromStdString(it.key()));
      ParamComboBox* t_combo = new ParamComboBox(it.value(), name, it.key());

      vec_ComboBox.push_back(std::make_tuple(t_label, t_combo));

      t_layout->addWidget(t_label);
      t_layout->addWidget(t_combo);

      QObject::connect(t_combo, &ParamComboBox::signal_set_json_int, this, &KJsonConfig::slot_set_json_int);

    }
    else if (!it.value()["type"].get<string>().compare("int")) {
      QLabel* t_label = new QLabel(QString::fromStdString(it.key()));
      ParamLineEdit* t_lineEdit = new ParamLineEdit(it.value(), name, it.key(),false);

      vec_LineEdit.push_back(std::make_tuple(t_label, t_lineEdit));

      t_layout->addWidget(t_label);
      t_layout->addWidget(t_lineEdit);

      QObject::connect(t_lineEdit, &ParamLineEdit::signal_set_json_int, this, &KJsonConfig::slot_set_json_int);
    }
    else if (!it.value()["type"].get<string>().compare("double")) {
      QLabel* t_label = new QLabel(QString::fromStdString(it.key()));
      ParamLineEdit* t_lineEdit = new ParamLineEdit(it.value(), name, it.key(),true);

      vec_LineEdit.push_back(std::make_tuple(t_label, t_lineEdit));

      t_layout->addWidget(t_label);
      t_layout->addWidget(t_lineEdit);

      QObject::connect(t_lineEdit, &ParamLineEdit::signal_set_json_double, this, &KJsonConfig::slot_set_json_double);


    }
    else if (!it.value()["type"].get<string>().compare("bool")) {
      QLabel* t_label = new QLabel(QString::fromStdString(it.key()));
      ParamCheckBox* t_checkBox = new ParamCheckBox(it.value(),name,it.key());

      vec_CheckBox.push_back(std::make_tuple(t_label,t_checkBox));

      t_layout->addWidget(t_label);
      t_layout->addWidget(t_checkBox);

      QObject::connect(t_checkBox, &ParamCheckBox::signal_set_json_bool, this, &KJsonConfig::slot_set_json_bool);
    }
  }
}

void KJsonConfig::update_json(json j, string path) {
  std::ofstream ofs(path);
  ofs << j.dump(4);
  ofs.close();
}

void KJsonConfig::slot_set_json_bool(QString _name, string _key, bool _val) {
  /*
  for (auto it = vec_json.begin(); it != vec_json.end(); it++) {
    if (QString::compare(std::get<1>(*it),_name)==0) {
      std::get<0>(*it)[_key]["value"] = _val;
      update_json(std::get<0>(*it), std::get<2>(*it));
      break;
    }
  }
  */

  auto *target =  &map_json[_name];
  std::get<0>(*target)[_key]["value"]= _val;
  update_json(std::get<0>(*target), std::get<1>(*target));
}
void KJsonConfig::slot_set_json_int(QString _name, string _key, int _val) {
  auto *target =  &map_json[_name];
  std::get<0>(*target)[_key]["value"]= _val;
  update_json(std::get<0>(*target), std::get<1>(*target));
}
void KJsonConfig::slot_set_json_double(QString _name, string _key, double _val) {
  auto *target =  &map_json[_name];
  std::get<0>(*target)[_key]["value"]= _val;
  update_json(std::get<0>(*target), std::get<1>(*target));
}



