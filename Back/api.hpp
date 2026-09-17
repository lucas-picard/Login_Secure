#ifndef __API__
    #define __API__

      #include <iostream>
      #include <fstream>
      #define CPPHTTPLIB_OPENSSL_SUPPORT
      #include "httplib.h"
      #include "secu.hpp"

      class API : public SECU{
        public:
          API();
          void page(httplib::Response& res) const;
          void button(httplib::Response& res) const;
          void log(const httplib::Request& req, httplib::Response& res);

          ~API();
        private:
    

      };  

#endif