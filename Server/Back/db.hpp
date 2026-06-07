#ifndef __DB__
    #define __DB__
        #include <iostream>
        #include <string>
        #include "sqlite3.h"

        class DB{
            public:
                DB();
                sqlite3* db;
                void adds(const char* l, const char* m, const char* r);
                void tableL();

                void close();
                ~DB();

            private:
                const char* _l;
                const char* _m;
        };

#endif