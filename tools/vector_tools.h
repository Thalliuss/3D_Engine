//
//  vector_tools.h
//  tools
//
//  Created by Jesse Gall on 17/04/16.
//
//

#ifndef __game_framework__vector_tools__
#define __game_framework__vector_tools__

#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

template<class T> bool vectorContains(vector<T*>& vector, T* object) {
    return std::find(vector.begin(), vector.end(), object) != vector.end();
};

template<class T> bool vectorContains(vector<T>& vector, T object) {
	return std::find(vector.begin(), vector.end(), object) != vector.end();
};

template<class T> void removeFromVector(vector<T*>& vector, T* object) {
    vector.erase(std::remove(vector.begin(), vector.end(), object), vector.end());
}

#endif /* defined(__tools__vector_tools__) */
