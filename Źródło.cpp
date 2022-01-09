#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>

#define MAX_LICZBA_POZIOMOW 3

class Menu {

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0;

public:
	Menu(float width, float hegiht);
	~Menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow &window);
};

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height/ (MAX_LICZBA_POZIOMOW + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Pomoc");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wyjscie");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
		window.draw(menu[i]);
	}
};

void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) {
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}

void myDelay(int opoznienie)
	{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
	}

	}

class wr�g
{
private:
	sf::Vector2f position;
	sf::CircleShape ball;
	int maxW;
	float SpawnTimer;
	float SpawnTimerMax;
	std::vector<sf::CircleShape> wrogowie;

public:
	wr�g(float x, float y);
	//~wr�g();
	sf::CircleShape getWr�g() { return ball; }
	sf::FloatRect getWr�gBounds() { return ball.getGlobalBounds(); }
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y);

};

wr�g::wr�g(float x, float y) {
	position.x = x;
	position.y = y;

		ball.setRadius(10);
		ball.setFillColor(sf::Color(255, 0, 0));
		ball.setOutlineThickness(5);
		ball.setOutlineColor(sf::Color(0, 30, 255));
		ball.setPosition(position);
}

std::vector<wr�g> wrogowie;

float randx()
{
	float a = rand() % 800;
	return a;
}
float randy()
{
	float b = rand() % 600;
	return b;
}

void wr�g::draw(sf::RenderWindow& window) {
	for (int i = 0; i < maxW; i++) {
		window.draw(ball);
	};
}

void wr�g::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

class gracz
{
private:
	sf::Vector2f position;
	sf::CircleShape ball;
	sf::RenderWindow* win;
	sf::Vector2f okno;
public:
	gracz(float x, float y, sf::RenderWindow* win);
	void steruj();
	sf::CircleShape getGracz() { return ball; }
	sf::FloatRect getGraczBounds() { return ball.getGlobalBounds(); }
};

gracz::gracz(float x, float y, sf::RenderWindow* w)
{
	win = w;
	okno.x = win->getSize().x;
	okno.y = win->getSize().y;
	position.x = x;
	position.y = y;
	ball.setRadius(20);
	ball.setFillColor(sf::Color(0, 255, 255));
	ball.setOutlineThickness(5);
	ball.setOutlineColor(sf::Color(143, 23, 194));
	ball.setPosition(position);
}

void gracz::steruj()
{
	position = ball.getPosition();
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (position.y > 0))
	{
		ball.move(0, -0.2);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (position.y < okno.y))
	{
		ball.move(0, 0.2);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && (position.x > 0))
	{
		ball.move(-0.2, 0);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && (position.x < okno.x))
	{
		ball.move(0.2, 0);
	}
}





int main()
{
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML demo");
	sf::Texture t;
	t.setRepeated(true);
	t.loadFromFile("bg.png");
	sf::Sprite t�o;
	t�o.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
	t�o.setTexture(t);
	Menu menu(window.getSize().x, window.getSize().y);
	float posx = (window.getSize().x) / 2;
	float posy = (window.getSize().y) / 2;
	gracz g1(posx, posy, &window);
	int maxW = 7;
	wr�g p1(randx(), randy());
	wr�g p2(randx(), randy());
	wr�g p3(randx(), randy());
	wr�g p4(randx(), randy());
	wr�g p5(randx(), randy());
	wr�g p6(randx(), randy());
	wr�g p7(randx(), randy());
	wr�g p8(randx(), randy());
	wr�g p9(randx(), randy());
	std::vector< wr�g > wrogowie = {
		p1,
		p2,
		p3,
		p4,
		p5,
		p6,
		p7
	};
	std::vector<wr�g>::iterator it;
	it = wrogowie.begin();

	sf::Texture pomoctex;
	pomoctex.loadFromFile("pomoc.png");
	sf::Sprite pomoc;
	pomoc.setTexture(pomoctex);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(250);
					menu.przesunG();
				}

			if (event.key.code == sf::Keyboard::Down)
			{
				myDelay(250);
				menu.przesunG();
			}
			if (menu_selected_flag == 0)
			{
				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
				{
					std::cout << "Uruchamiam gre..." << std::endl;
					menu_selected_flag = 1;
				}
				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
				{
					std::cout << "Pomoc..." << std::endl;
					menu_selected_flag = 2;
				}
				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
				{
					std::cout << "Koniec gry..." << std::endl;
					menu_selected_flag = 3;
					window.close();
				}
			}
		
		
		}

	window.clear();
	if (menu_selected_flag == 0)
		menu.draw(window);
	if (menu_selected_flag == 1)
	{
		window.draw(t�o);
		window.draw(g1.getGracz());
		g1.steruj();
		
			for (auto& i : wrogowie) {
				window.draw(i.getWr�g());
			}
		
		for (size_t i = 0; i < wrogowie.size(); i++) {
			if (g1.getGraczBounds().intersects(wrogowie[i].getWr�gBounds())) {
				wrogowie.erase(wrogowie.begin() + i);
			}
		};
		
		if (wrogowie.size() < 7) {

			wrogowie.push_back(p1);
			wrogowie.push_back(p2);
			wrogowie.push_back(p3);
			wrogowie.push_back(p4);
			wrogowie.push_back(p5);
			wrogowie.push_back(p6);
			wrogowie.push_back(p7);
			for (auto& i : wrogowie) {
				window.draw(i.getWr�g());
			}
		}

	}
	if (menu_selected_flag == 2) {
		window.draw(pomoc);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			menu_selected_flag = 0;
	}
	window.display();
}
	return 0;
}