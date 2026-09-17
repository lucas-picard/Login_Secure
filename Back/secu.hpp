#ifndef __SECU__
    #define __SECU__

        #include "db.hpp"
        #include <cstring>
        #include <sodium.h>

        class SECU : public DB{
            public:
                SECU();
                std::string hash_mdp(const char* mdp);
                bool checkLog(const std::string& username, const std::string& password) const;

                ~SECU();
            private:
                const char* log;
                const char* mdp;
        };

#endif