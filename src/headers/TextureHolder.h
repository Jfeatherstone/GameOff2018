#pragma once

#include<SFML/Graphics.hpp>
#include<map>

using namespace sf;
using namespace std;

class TextureHolder {
private:
  // A map container that holds strings and textures
  static map<string, Texture> m_textures;

public:
  static Texture& getTexture(string const& fileName);

};
