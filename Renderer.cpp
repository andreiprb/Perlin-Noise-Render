#include "Renderer.h"

Renderer::Renderer(const int& width, const int& height)
{
	this->m_window_width = width;
	this->m_window_height = height;

	this->m_window = new sf::RenderWindow(sf::VideoMode(this->m_window_width, this->m_window_height, 32), "Renderer");
	this->m_pixels = new sf::Uint8[this->m_window_width * this->m_window_height * 4];
}

Renderer::~Renderer()
{
    if (this->m_pixels != nullptr)
    {
        delete[] this->m_pixels;
        this->m_pixels = nullptr;
    }

    if (this->m_window)
    {
        delete this->m_window;
        this->m_window = nullptr;
    }
}

void Renderer::Run()
{
    sf::Texture texture;
    sf::Sprite sprite;

    texture.create(this->m_window_width, this->m_window_height);

    texture.update(this->m_pixels);

    sprite.setTexture(texture);

    while (this->m_window->isOpen())
    {
        sf::Event event;
        while (this->m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->m_window->close();
        }

        this->m_window->clear();
        this->m_window->draw(sprite);

        this->m_window->display();
    }

    this->~Renderer();
}
