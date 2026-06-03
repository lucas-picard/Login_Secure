#ifndef __DB__
    #define __DB__
        #include <iostream>
        #include <string>
        #include "sqlite3.h"

        class DB{
            public:
                DB();
                void adds(const char* l, const char* m, const char* r);
                void tableL();

                void close();
                ~DB();

            private:
                sqlite3* db;
                const char* l;
                const char* m;
        };

#endif