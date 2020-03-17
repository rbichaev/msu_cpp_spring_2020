using beginParse = void (*)(const std::string &);
using endParse = void (*)();
using numParse = void (*)(int);
using strParse = void (*)(const std::string &);

void registerBeginParse(beginParse callbackFoo);
void registerEndParse(endParse callbackFoo);
void registerCallbackNum(numParse callbackFoo);
void registerCallbackStr(strParse callbackFoo);
bool parse(const std::string &text);