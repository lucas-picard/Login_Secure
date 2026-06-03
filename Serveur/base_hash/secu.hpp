#ifndef __SECU__
    #define __SECU__

        #include <iostream>
        #include <string>
        #include <cstring>
        #include <sodium.h>

        class SECU{
            public:
                SECU();
                std::string hash_log(const char* log);
                std::string hash_mdp(const char* mdp);

                ~SECU();
            private:
                const char* log;
                const char* mdp;
        };

#endif