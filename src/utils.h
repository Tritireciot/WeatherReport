#pragma once
#include <QString>

static QString windDirRu(const QString& code) {
    if (code == "nw") return "СЗ";
    if (code == "n")  return "С";
    if (code == "ne") return "СВ";
    if (code == "e")  return "В";
    if (code == "se") return "ЮВ";
    if (code == "s")  return "Ю";
    if (code == "sw") return "ЮЗ";
    if (code == "w")  return "З";
    if (code == "c")  return "штиль";
    return code;
}

static QString conditionRu(const QString& code) {
    if (code == "clear")                  return "Ясно";
    if (code == "partly-cloudy")          return "Малооблачно";
    if (code == "cloudy")                 return "Облачно";
    if (code == "overcast")               return "Пасмурно";

    if (code == "drizzle")                return "Морось";
    if (code == "light-rain")             return "Небольшой дождь";
    if (code == "rain")                   return "Дождь";
    if (code == "moderate-rain")          return "Умеренный дождь";
    if (code == "heavy-rain")             return "Сильный дождь";
    if (code == "continuous-heavy-rain")  return "Длительный сильный дождь";
    if (code == "showers")                return "Ливень";

    if (code == "wet-snow")               return "Дождь со снегом";
    if (code == "light-snow")             return "Небольшой снег";
    if (code == "snow")                   return "Снег";
    if (code == "snow-showers")           return "Снегопад";
    if (code == "hail")                   return "Град";

    if (code == "thunderstorm")           return "Гроза";
    if (code == "thunderstorm-with-rain") return "Гроза с дождём";
    if (code == "thunderstorm-with-hail") return "Гроза с градом";

    return code;
}