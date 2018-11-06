#include "headers/TextureHolder.h"

// Include the assert feature
#include <assert.h>

TextureHolder* TextureHolder::m_s_instance = nullptr;

TextureHolder::TextureHolder() {
  // Make sure that the instance of the TextureHolder class doesn't exist
  assert(m_s_instance == nullptr);
  // Now assign the texture class to this instance
  // This makes sure that there is always only one instance at any given time
  m_s_instance = this;
}

sf::Texture& TextureHolder::getTexture(std::string const& fileName) {
  // Get a reference to m_textures using m_s_instance
  auto& m = m_s_instance->m_textures;
  // auto is used as shorthand for map<string, Texture> here

  // Create an interator to roll through key-value pairs in our map
  auto keyValuePair = m.find(fileName);
  // auto is used as shorthand for map<string, Texture>::iterator

  if (keyValuePair != m.end()) {
    // Assuming we found something
    // We now return the text
    return keyValuePair->second;
  } else {
    // If there is no entry for this texture file, we should make one
    auto& texture = m[fileName];
    texture.loadFromFile(fileName);

    // Return our new texture
    return texture;
  }
}
