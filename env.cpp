#include <unistd.h>
#include <util/string.h>

#include "env.h"
#include "globals.h"

#ifndef EOF
#define EOF (-1)
#endif

static std::set<std::string> const pre_defined({
    "console", "setTimeout", "setInterval", "clearTimeout", "parseInt", "parseFloat", "Number",
    "Date", "Math", "Object", "Function", "escape", "unescape", "encodeURI", "encodeURIComponent",
    "decodeURI", "decodeURIComponent", "JSON", "NaN", "null", "undefined", "isFinite", "isNaN",
    "RegExp",
});

void flats::initEnv(int argc, char* argv[])
{
    int ch;
    opterr = 0;
    while ((ch = getopt(argc, argv, "e:E:i:")) != EOF) {
        switch (ch) {
        case 'e':
            Globals::g.external_syms.insert(optarg);
            continue;
        case 'E':
            for (std::string s: util::split_str(optarg, ":")) {
                Globals::g.external_syms.insert(s);
            }
            continue;
        case 'i':
            Globals::g.input_file = optarg;
            continue;
        }
    }
    for (std::string const& i: pre_defined) {
        Globals::g.external_syms.insert(i);
    }
}
