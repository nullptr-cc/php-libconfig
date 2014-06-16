#include <phpcpp.h>
#include "php_lconfig.h"

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module()
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("lconfig", "0.1");

        // @todo    add your own functions, classes, namespaces to the extension
        extension.add("lconfig_parse", lconfig_parse, {
            Php::ByVal("path", Php::Type::String, true)
        });

        // return the extension
        return extension;
    }
}
