#ifndef QUERY_H
#define QUERY_H
#include "Builder.h"
#include "Plant.h"
#include <string>
class Query
{
  protected:
    Plant *item;
    std::string type;
    std::string question;

  public:
    Query(Builder *builder);
    std::string getType();
    std::string getQuestion();
    Plant *getItem();
    void printQuery();
};
#endif // !QUERY_H