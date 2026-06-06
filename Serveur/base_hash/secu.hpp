#ifndef __SECU__
    #define __SECU__

        #include "db.hpp"
        #include <cstring>
        #include <sodium.h>

        class SECU{
            public:
                SECU(sqlite3* db);
                std::string hash_log(const char* log);
                std::string hash_mdp(const char* mdp);
                bool checkLog(const std::string username, const std::string password);

                ~SECU();
            private:
                sqlite3* db;
                const char* log;
                const char* mdp;
        };

#endif