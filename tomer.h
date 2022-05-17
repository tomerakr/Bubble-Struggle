button in menu:
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(xSize, ySize), "Normal" });
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Survival" });
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Create Level" });
//m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Settings" }); //consider
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Help" });
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Exit" });

m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Solo" });
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Duo" });
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Online" });
m_buttons.emplace_back(Button{ sf::Vector2f(), sf::Vector2f(), "Same PC" });