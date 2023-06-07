#pragma once

#include <sstream>

#define CHECK_RESULT(res) if( res == false ) {  std::stringstream ss; ss <<"the operation could not be completed. "  << __FILE__ << ": " << __LINE__; LOG_ERROR(ss.str());  ss.clear(); return; }  

#define to_glm_vec(imvec) glm::vec2(imvec.x, imvec.y)

#define to_im_vec(vector) ImVec2(vector.x, vector.y)
