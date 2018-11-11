#include "headers/TextureHolder.h"
#include <iostream>

map<string, Texture> TextureHolder::m_textures = map<string, Texture>();

Texture& TextureHolder::getTexture(string const& fileName) {

  // First, we look through the map to see if there is an entry already
  for (auto element: TextureHolder::m_textures) {
    if (element.first == fileName) {
      Texture& texture = TextureHolder::m_textures[element.first];
      return texture;
    }
  }
  // If the code has made it to this point, we assume the value isn't in our map

  // If there is no entry for this texture file, we should make one
  Texture texture;
  texture.loadFromFile(fileName);
  TextureHolder::m_textures[fileName] = texture;

  Texture& ref = TextureHolder::m_textures[fileName];
  return ref;
}
