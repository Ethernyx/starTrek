/**
* File: Attribut.cpp
* Project: objects
* File Created: Tuesday, 18th July 2023 3:29:05 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:50:20 pm
* Modified By: LALIN Romain
* -----
*/

#include "../include/object/Attribut.hh"


Attribut::Attribut(int ap, int hp, int dp):_hp(hp), _dp(dp), _ap(ap) {}
Attribut::Attribut(cJSON *node) {
    this->_hp = cJSON_GetObjectItem(node, "hp")->valueint;
    this->_dp = cJSON_GetObjectItem(node, "dp")->valueint;
    this->_ap = cJSON_GetObjectItem(node, "ap")->valueint;
}
Attribut::~Attribut(){}

void Attribut::setAttributs(int ap, int hp, int dp) {
    this->_ap = ap;
    this->_hp = hp;
    this->_dp = dp;
}

int Attribut::getAp() {
    return this->_ap;
}
int Attribut::getHp() {
    return this->_hp;
}
int Attribut::getDp() {
    return this->_dp;
}

void    Attribut::setAp(int ap) {
    this->_ap = ap;
}

void    Attribut::setHp(int hp) {
    this->_hp = hp;
}

void    Attribut::setDp(int dp) {
    this->_dp = dp;
}

vector<int> Attribut::get_attributs() {
    vector<int> v{this->_ap, this->_hp, this->_dp};
    return v;
}


