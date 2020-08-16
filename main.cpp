#include <SFML\Graphics.hpp>
#include <sstream>
using namespace std;
using namespace sf;
bool win;
bool flag = true;
int bomb = 0;
int main() {
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(384, 384), "Minesweeper");
	
	Texture t, t2;
	t.loadFromFile("images/tiles.jpg");
	t2.loadFromFile("images/win.png");
	Sprite s(t), sWin(t2);
	sWin.setPosition(351.5, 351.5);
	
	int width = 32;

	int sgrid[12][12], grid[12][12];
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			sgrid[i][j] = 10;
			if (rand() % 5 == 0) { grid[i][j] = 9; bomb++; }
			else grid[i][j] = 0;
		}
	}
	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			int n = 0;
			if (grid[i][j] == 9) continue;
			if (grid[i + 1][j] == 9) n++; //справа
			if (grid[i + 1][j + 1] == 9) n++; //верхн€€ права€ диагональ
			if (grid[i - 1][j] == 9) n++; //влево
			if (grid[i - 1][j - 1] == 9) n++;//нижн€€ лева€ диагональ
			if (grid[i][j + 1] == 9) n++;//вверху
			if (grid[i][j - 1] == 9) n++;//снизу
			if (grid[i - 1][j+1] == 9) n++;//лева€ верхн€€ диагональ
			if (grid[i + 1][j-1] == 9) n++; //права€ верхн€€ диагональ
			grid[i][j] = n;
		}
	}

	while (window.isOpen()) {

		Vector2i position = Mouse::getPosition(window);
		int x = position.x / width;
		int y = position.y / width;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) sgrid[x][y] = grid[x][y];
				if (event.key.code == Mouse::Right) {
					switch (flag) {
						case true: sgrid[x][y] = 11; bomb--; flag = false; break;
						case false: sgrid[x][y] = 10; bomb++; flag = true; break;
					}
				}
			}
		}
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (sgrid[i][j] == 11 && grid[i][j] == 9) win = true;
				else win = false;
			}
		}
		window.clear();
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
				s.setTextureRect(IntRect(sgrid[i][j]*width, 0, width, width));
				s.setPosition(width*i, width*j);
				window.draw(s);
			}
		}
		if (win) window.draw(sWin);

		window.display();
	}
	return 0;
}