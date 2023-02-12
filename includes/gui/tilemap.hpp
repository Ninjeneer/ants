#ifndef PROJET_CPP_TILEMAP_HPP
#define PROJET_CPP_TILEMAP_HPP


#include <SFML/Graphics.hpp>
#include <board.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string &path, sf::Vector2u size, const Board &board, unsigned int width, unsigned int height);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};

#endif //PROJET_CPP_TILEMAP_HPP
