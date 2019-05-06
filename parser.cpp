#include "parser.h"
parser::parser()
{
  tmp = new drone_data;
  tmp->yaw=0;
  tmp->roll=0;
  tmp->pitch=0;
  tmp->height=1000;
  tmp->battery=127;
  tmp->speed=0;
}

void parser::parseString(QString line)
{
    std::string src = line.toStdString();
    std::istringstream iss(src);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
    if(results.size()==8){
        //qDebug()<<QString(results.at(0));
        tmp->yaw=atof((results.at(0).c_str()));
        tmp->pitch=atof((results.at(1).c_str()));
        tmp->roll=atof((results.at(2).c_str()));
        tmp->height=stoul(results.at(3));
        tmp->battery=stoul(results.at(4));
        tmp->speed=atof((results.at(5).c_str()));
        tmp->lat=atof((results.at(6).c_str()));
        tmp->lon=atof((results.at(7).c_str()));

        dataChanged(tmp);
    }
}

