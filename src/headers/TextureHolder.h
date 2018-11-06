#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include<SFML/Graphics.hpp>
#include<map>

using namespace sf;
using namespace std;

class TextureHolder {
private:
  // A map container that holds strings and textures
  map<string, Texture> m_textures;

  // Create an instance of the class as a pointer
  static TextureHolder* m_s_instance;

public:
  TextureHolder();
  static Texture& getTexture(string const& fileName);
};

#endif
