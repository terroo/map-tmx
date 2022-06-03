#pragma once

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <memory>

class LoadTmx {
  FILE * file;
  std::uint32_t qtd;
  float offset_x, speed;

  tinyxml2::XMLDocument m_doc;
  tinyxml2::XMLElement *p_root_element;
  tinyxml2::XMLElement *p_tileset, *p_count;
  
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<sf::Image> icon;
  std::shared_ptr<sf::Texture> tbg, tcamera;
  std::shared_ptr<sf::Sprite> sbg, scamera;
  std::shared_ptr<sf::FloatRect> rect;
  std::shared_ptr<sf::RectangleShape> tile;
  
  protected:
    std::vector<sf::Texture> tex;
    std::vector<std::vector<int>> map;
    void tilemap();
    void set_game_objs();
    void events();
    void draw_all();

  public:
    LoadTmx(FILE *);
    void run();
};
