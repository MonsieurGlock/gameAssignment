#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <random>
#include <ctime>
#include <math.h>

int Enemy(int x);
bool distance(float x1, float x2, float y1, float y2);
int checkScore(int score);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 900), "Higher", sf::Style::Close);
	window.setFramerateLimit(60);

	sf::RectangleShape player(sf::Vector2f(90, 90));
	player.setFillColor(sf::Color::White);
	player.setOrigin(sf::Vector2f(0, 85));

	sf::RectangleShape plat(sf::Vector2f(100, 25));
	plat.setFillColor(sf::Color::Yellow);

	sf::RectangleShape enemy(sf::Vector2f(50, 50));
	enemy.setFillColor(sf::Color::Red);


	sf::RectangleShape gameoverBackground(sf::Vector2f(500, 700));
	gameoverBackground.setFillColor(sf::Color::White);

	sf::Font font;
	sf::Text scoreText;
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::Red);
	sf::Text gameoverText;
	gameoverText.setFont(font);
	gameoverText.setString("Game Over!");
	gameoverText.setCharacterSize(80);
	gameoverText.setFillColor(sf::Color::Red);


	// initialize platforms
	sf::Vector2u platformPosition[10];
	std::uniform_int_distribution<unsigned> x(0, 800);
	std::uniform_int_distribution<unsigned> y(100, 800);
	std::default_random_engine e(time(0));

	for (size_t i = 0; i < 10; ++i)
	{
		platformPosition[i].x = x(e);
		platformPosition[i].y = y(e);
	}


	sf::Vector2f P;
	// player's positon and down velocity
	float playerX = 250;
	int playerY = 151;
	float dy = 0;
	int height = 450;
	int score = 0;
	int i,j;
	bool temp;
	int diffi;
	//enemy
	struct sEnemy{
		sf::Vector2u enemyPos;
		bool built=false;
	}en;
	

	// player's bounding box. It should modify according to the image size
	const int PLAYER_LEFT_BOUNDING_BOX = 90;
	const int PLAYER_RIGHT_BOUNDING_BOX = 90;
	const int PLAYER_BOTTOM_BOUNDING_BOX = 90;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			playerX -= 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			playerX += 4;*/
		float vecol;
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		vecol = (mousePos.x - 400) / 12;
		if (playerX > -61 && playerX < 801) {

				player.move(vecol,0);
			
		}
		P = player.getPosition();
		playerX = P.x;
		if (playerX > 800)
			playerX = 0;
		if (playerX < -60){
			//playerX = window.getSize().x - 90;
			playerX = 750;
		}

		//set Enemy
		for (i = 0; i < 10 && en.built == false;i++) {
			if (Enemy(platformPosition[i].x )) {
				en.built = (Enemy(platformPosition[i].x) && platformPosition[i].y < 10);
			}
			if (en.built == true) {
				en.enemyPos.x = platformPosition[i].x;
				en.enemyPos.y = platformPosition[i].y+50;
				break;
			}
		}
		
			

		// score
		// dy = -1.60001 is terminal velocity that player stand on the platform and don't go up anymore
		// score can't increase in this situation
		if (playerY == height && dy < (-1.62))
		{
			score += 1;
			scoreText.setString("Score: " + std::to_string(score));
		}
		printf("Score = %d\n",score);

		// player's jump mechanism
		dy += 0.2;
		playerY += dy;

		diffi = checkScore(score);
		if (playerY < height) {
			for (size_t i = 0; i < 10; ++i)
			{
				playerY = height;
				platformPosition[i].y -= dy;  // vertical translation
				if (platformPosition[i].y > 900) // set new platform on the top
				{
					temp = false;
					while(temp != true && i < diffi){
						platformPosition[i].y = 1;
						platformPosition[i].x = x(e);
						for (j = 0; j < 10; j++) {
							
							if(i != j){
								temp = distance(platformPosition[i].x, platformPosition[j].x, platformPosition[i].y, platformPosition[j].y);
								if (temp == false) {
									break;
								}
							}
						
							
						}
					}
					
					
				}
				if (en.enemyPos.y > 990) {
					en.built = false;
				}

			}
			en.enemyPos.y -= dy;
		}
		if (en.built == true) {
			enemy.setPosition(en.enemyPos.x , en.enemyPos.y-90);
			window.draw(enemy);

		}
		// detect jump on the platform
		for (size_t i = 0; i < 10; ++i)
		{
			if ((playerX + PLAYER_RIGHT_BOUNDING_BOX > platformPosition[i].x) && (playerX  < platformPosition[i].x + 100)        // player's horizontal range can touch the platform
				&& (playerY + 5 > platformPosition[i].y) && (playerY  < platformPosition[i].y + 25)  // player's vertical   range can touch the platform
				&& (dy > 0)) // player is falling
			{

				dy = -15;
			}

		}
		player.setPosition(playerX, playerY);
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())  && dy > 0) {
			dy = -30;
			printf("Hit enemy\n");
		}


		window.draw(player);

		// set and draw platforms
		for (size_t i = 0; i < 10; ++i)
		{
			plat.setPosition(platformPosition[i].x, platformPosition[i].y);
			window.draw(plat);
		}

		window.draw(scoreText);
		window.display();
		window.clear();
	}
}

int Enemy(int x) {
	if (x % 13 == 0) {
		return true;
	}
	else { return false; }

}

bool distance(float x1,float x2,float y1 ,float y2) {
	float d;
	d = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	if (d >=100) {
		return true;
	}
	else{
		return false;
	}
}

int checkScore(int score) {
	if (score <= 700) {
		return 10;
	}
	if (score > 700 && score <= 1400) {
		return 6;
	}
	if (score > 1400) {
		return 4;
	}
}


