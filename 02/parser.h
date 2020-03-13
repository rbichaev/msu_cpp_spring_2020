void registerBeginParse(void (*callbackFoo)(const char *const ));
void registerEndParse(void (*callbackFoo)());
void registerCallbackNum(void (*callbackFoo)(char *));
void registerCallbackStr(void (*callbackFoo)(char *));
void parse(const char *text);