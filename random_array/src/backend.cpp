#include "backend.h"

Backend::Backend(QObject* parent) : QObject{parent}, backgroundThread_{new QThread{this}} {}

Backend::~Backend() {}

void Backend::start() 
{
  
}

void Backend::pause() 
{
  
}

void Backend::stop() 
{
  
}
