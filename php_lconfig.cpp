#include <phpcpp.h>
#include <sstream>
#include <libgen.h>
#include <libconfig.h++>
#include "php_lconfig.h"

using namespace std;
using namespace libconfig;

bool dump_node(const Setting & node, Php::Value & result)
{
    unsigned int it, len = node.getLength();

    const char * child_name;
    Php::Value dump;

    for (it = 0; it < len; ++it) {
        const Setting & child = node[it];
        dump = nullptr;

        switch (child.getType()) {
            case Setting::TypeString:
                dump = (string) child.c_str();
                break;

            case Setting::TypeInt:
                dump = (int) child;
                break;

            case Setting::TypeInt64:
                dump = (long) child;
                break;

            case Setting::TypeFloat:
                dump = (double) child;
                break;

            case Setting::TypeBoolean:
                dump = (bool) child;
                break;

            case Setting::TypeGroup:
            case Setting::TypeList:
            case Setting::TypeArray:
                dump_node(child, dump);
                break;

            default:
                break;
        };

        child_name = child.getName();
        if (child_name != NULL) {
            result[child_name] = dump;
        } else {
            result[it] = dump;
        };
    };

    return true;
}

Php::Value lconfig_parse(Php::Parameters &params)
{
    string path = params[0];
    ostringstream err;

    char* cfg_rp = realpath(path.c_str(), NULL);

    if (cfg_rp == NULL) {
        err << "Cannot read file: " << path;
        throw Php::Exception(err.str());
    };

    FILE* fd = fopen(cfg_rp, "r");
    if (!fd) {
        err << "Cannot read file: " << cfg_rp;
        throw Php::Exception(err.str());
    };

    Config cfg;
    cfg.setIncludeDir(dirname(cfg_rp));

    try {
        cfg.read(fd);
        fclose(fd);
        free(cfg_rp);
    } catch(const FileIOException & fioex) {
        throw Php::Exception("I/O error while reading file.");
    } catch(const ParseException & pex) {
        err << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError();
        throw Php::Exception(err.str());
    };

    const Setting & root = cfg.getRoot();
    Php::Value result;

    dump_node(root, result);

    return result;
}
