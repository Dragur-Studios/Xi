#pragma once

#include <sstream>

#define CHECK_RESULT(res) if( res == false ) {  std::stringstream ss; ss <<"the operation could not be completed. "  << __FILE__ << ": " << __LINE__; LOG_ERROR(ss.str());  ss.clear(); return; }  
