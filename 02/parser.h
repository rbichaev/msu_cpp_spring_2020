void registerBeginParse(void (*callbackFoo)(std::string));
void registerEndParse(void (*callbackFoo)());
void registerCallbackNum(void (*callbackFoo)(std::string));
void registerCallbackStr(void (*callbackFoo)(std::string));
bool parse(std::string text);