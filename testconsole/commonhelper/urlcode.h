//
//  urlcode.h
//  testgame
//
//  Created by Tim on 14-11-5.
//
//

#ifndef __testgame__urlcode__
#define __testgame__urlcode__

#include <stdio.h>
#include <string>

using namespace std;
class urlcode {
    
public:
    unsigned char ToHex(unsigned char x);
    unsigned char FromHex(unsigned char x);
    string UrlEncode(const string& str);
    string UrlDecode(const string& str);
};
#endif /* defined(__testgame__urlcode__) */
