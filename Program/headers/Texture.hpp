#ifndef TEXTURE_HPP
#define TEXTURE_HPP


#include <SFML/Graphics/Texture.hpp>

#include <string>

#define IMG_DIR "../../resources/images/"

class Texture{

private:
  sf::Texture m_texture;

public:
  Texture(){};
  ~Texture(){ };
  Texture(const std::string&);
  bool loadFromFile(const std::string&);
  void setTexture(const sf::Texture& t){ m_texture = t; };
  sf::Texture * getTexture() { return &(m_texture); };
};


#endif
