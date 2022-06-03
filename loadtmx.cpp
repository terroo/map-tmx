#include "loadtmx.hpp"

LoadTmx::LoadTmx(FILE *u_file){
  file = u_file;
  offset_x = 0.f;
  speed = 12.f;
  qtd = 0;

  m_doc.LoadFile(file);

  p_root_element = m_doc.RootElement();
  p_tileset = p_root_element->FirstChildElement("tileset");
  p_count = p_root_element->FirstChildElement("tileset");

  while(p_count){
    p_count = p_count->NextSiblingElement("tileset");
    ++qtd;
  }

  tex.resize(qtd);

  int i = 0;
  //for (std::size_t i{}; i < tex.size(); ++i){
  while(p_tileset){
    tinyxml2::XMLElement * p_image = p_tileset->FirstChildElement("image");
    tex[i].loadFromFile(p_image->Attribute("source"));
    ++i;
    p_tileset = p_tileset->NextSiblingElement("tileset");
  }

  set_game_objs();
  tilemap();
}

void LoadTmx::set_game_objs(){

  window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(1280,736),
    "Example Load Tmx",
    sf::Style::Titlebar | sf::Style::Close
  );

  window->setPosition(sf::Vector2i(0,0));
  window->setFramerateLimit(60);

  icon = std::make_shared<sf::Image>();
  icon->loadFromFile("./resources/img/icon.png");

  window->setIcon(
    icon->getSize().x, 
    icon->getSize().y, 
    icon->getPixelsPtr()
  );

  tbg = std::make_shared<sf::Texture>();
  tbg->loadFromFile("./resources/img/bg.jpg");

  tcamera = std::make_shared<sf::Texture>();
  tcamera->loadFromFile("./resources/img/video-camera.png");

  sbg = std::make_shared<sf::Sprite>();
  sbg->setTexture(*tbg);

  scamera = std::make_shared<sf::Sprite>();
  scamera->setTexture(*tcamera);

  rect = std::make_shared<sf::FloatRect>(
    0, 0, 128, 128
  );

  tile = std::make_shared<sf::RectangleShape>(
    sf::Vector2f(32,32)
  );
}

void LoadTmx::events(){
  sf::Event event;
  while(window->pollEvent(event)){
    if(event.type == sf::Event::Closed){
      window->close();
    }
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && 
      scamera->getPosition().x < (window->getSize().x - rect->width) ){
        scamera->setTextureRect(sf::IntRect(0,0,128,128));
        rect->left += speed;
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 
      scamera->getPosition().x > 0){
        scamera->setTextureRect(sf::IntRect(128,0,-128,128));
        rect->left -= speed;
  }

  scamera->setPosition(rect->left - offset_x, rect->top);

  if( (rect->left > (float)window->getSize().x / 2) && 
      (rect->left < (float)window->getSize().x * 2 - (float)window->getSize().x / 2) ){
        offset_x = rect->left - (float)window->getSize().x / 2 - 20;
  }
}

void LoadTmx::draw_all(){
  window->clear(sf::Color::Black);
  window->draw(*sbg);

  for (std::size_t i{}; i < map.size(); ++i){ // H = 23 - map.size()
    for (std::size_t j{}; j <= map[i].size(); ++j){ // W = 80 - map[i].size() 79/80
      for (std::size_t k{}; k <= tex.size(); ++k){
        if(k > 0){
          if(map[i][j] == (int)k){
            tile->setTexture(&tex[k - 1]);
          }
        }
      }

      if( map[i][j] == 0){
        continue;
      }

      tile->setPosition( j * 32 - offset_x, i * 32);
      window->draw(*tile);
    }
  }

  window->draw(*scamera);
  window->display();
}

void LoadTmx::tilemap(){
  int row{};

  tinyxml2::XMLElement * p_layer = p_root_element->FirstChildElement("layer");
  tinyxml2::XMLElement * p_data = p_layer->FirstChildElement("data");

  std::size_t height = std::stoi(p_layer->Attribute("height")) + 1;

  std::string mapa = p_data->GetText(), value{};
  std::vector<std::vector<int>> tiles(height);

  for(std::size_t i{}; i < mapa.length(); ++i) {
    if(mapa[i] == ',') {
      tiles[row].push_back(std::stoi(value));
      value.clear();
    }else if(mapa[i] == '\n') {
      value.clear();
      tiles.push_back({});
      ++row;
      if(tiles.size() > height){
        tiles.pop_back();
      }
    }else if(mapa[i] >= '0' && mapa[i] <= '9'){
      value += mapa[i];
    }
  }
  tiles.erase(tiles.begin());
  map = tiles;
}

void LoadTmx::run(){
  while( window->isOpen() ){
    this->events();
    this->draw_all();
  }
}
