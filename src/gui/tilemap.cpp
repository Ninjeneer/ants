#include <SFML/Graphics.hpp>
#include <gui/tilemap.hpp>
#include <board.hpp>

bool
TileMap::load(const std::string &path, sf::Vector2u size, const Board& board, unsigned int width, unsigned int height) {
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(path))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j) {
            // on récupère le numéro de tuile courant
            int tileNumber = board.cells[j][i].isRevealed() ? board.cells[j][i].getType() : 187;


            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / size.x);
            int tv = tileNumber / (m_tileset.getSize().x / size.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * size.x, j * size.y);
            quad[1].position = sf::Vector2f((i + 1) * size.x, j * size.y);
            quad[2].position = sf::Vector2f((i + 1) * size.x, (j + 1) * size.y);
            quad[3].position = sf::Vector2f(i * size.x, (j + 1) * size.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * size.x, tv * size.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * size.x, tv * size.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * size.x, (tv + 1) * size.y);
            quad[3].texCoords = sf::Vector2f(tu * size.x, (tv + 1) * size.y);
        }

    return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}
