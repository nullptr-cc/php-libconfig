#ifndef __LCONFIG_H
#define __LCONFIG_H
#include <libconfig.h++>
Php::Value lconfig_parse(Php::Parameters &params);
bool dump_node(const libconfig::Setting & node, Php::Value & result);
#endif
