#include <SFML/Graphics.hpp>
#include "RocketLanding.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
using namespace std;
using namespace sf;

const int LANDING_FIELD_LENGHT = 100;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 500;
const float GRAVITY_ACCELERATION = 0.091;
const float AIR_RESISTANCE = 0.02;


int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RocketLanding");

	Rocket rocket(WINDOW_WIDTH / 2 - 10, 10);
	int landingFieldPosition = rand() % (WINDOW_WIDTH - LANDING_FIELD_LENGHT);

	srand(static_cast<unsigned>(time(0)));

	enum GAME
	{
		ON,
		WIN,
		LOSE
	};
	GAME game = ON;

	RectangleShape ground(Vector2f(WINDOW_WIDTH, 19));
	ground.setOutlineThickness(1.f);
	ground.setOutlineColor(Color::Black);
	ground.setFillColor(Color{171, 158, 120, 255});
	ground.setPosition(0, WINDOW_HEIGHT - 19);

	RectangleShape landingField(Vector2f(LANDING_FIELD_LENGHT, 19.f));
	landingField.setFillColor(Color(250, 250, 250));
	landingField.setOutlineThickness(1.f);
	landingField.setOutlineColor(Color::Black);
	landingField.setPosition(landingFieldPosition, WINDOW_HEIGHT - 30);

	Texture RocketTexture;
	RocketTexture.loadFromFile("C:\\Users\\79292\\Desktop\\Project2\\images\\Rocket.png");
	RocketTexture.setSmooth(true);
	Sprite RocketSprite(RocketTexture);
	RocketSprite.scale(1, 1);

	Texture ExplosionTexture;
	ExplosionTexture.loadFromFile("C:\\Users\\79292\\Desktop\\Project2\\images\\Explosion.png");
	ExplosionTexture.setSmooth(true);
	IntRect rectSourceSprite(0, 0, 96, 96);
	Sprite ExplosionSprite(ExplosionTexture, rectSourceSprite);

	clock_t tLose;
 
	int i = 0;
	int j = 0;

	while (window.isOpen())
	{
		if (game == ON) {

			rocket.setVelocityX(rocket.getVelocityX() + rocket.getSidePower() - AIR_RESISTANCE);
			rocket.setVelocityY(rocket.getVelocityY() + rocket.getCentralPower() + GRAVITY_ACCELERATION);

			rocket.setX(rocket.getX() + rocket.getVelocityX());
			rocket.setY(rocket.getY() + rocket.getVelocityY());

			if (rocket.getX() < 0
				|| rocket.getX() > WINDOW_WIDTH
				|| rocket.getY() < 0
				|| rocket.getY() > WINDOW_HEIGHT - 10
				|| (rocket.getX() >= landingFieldPosition && rocket.getX() <= LANDING_FIELD_LENGHT + 100
					&& rocket.getY() > WINDOW_HEIGHT - 30))
			{
				game = LOSE;
				tLose = clock();
				continue;
			}
			else if (rocket.getX() >= landingFieldPosition
				&& rocket.getX() <= landingFieldPosition + LANDING_FIELD_LENGHT
				&& rocket.getY() > WINDOW_HEIGHT - 40)
			{
				game = WIN;
				continue;
			}
			
			/*// custom game
			else
			{
				window.clear(Color{ 41, 31, 92, 255 });
				if (rocket.getSidePower() > 0)
					rocket.setFuel(rocket.getFuel() - rocket.getSidePower());
				else if (rocket.getSidePower() < 0)
					rocket.setFuel(rocket.getFuel() + rocket.getSidePower());
				if (rocket.getCentralPower() < 0)
					rocket.setFuel(rocket.getFuel() + rocket.getCentralPower());
				rocket.setCentralPower(0);
				rocket.setSidePower(0);

				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();

					Texture FlameTexture;
					FlameTexture.loadFromFile("C:\\Users\\79292\\Desktop\\Project2\\images\\flame.png");
					FlameTexture.setSmooth(true);
					Sprite FlameSprite(FlameTexture);


					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::A)
							if (rocket.getFuel() > 0)
							{
								rocket.setSidePower(-2 * GRAVITY_ACCELERATION);
								FlameSprite.setRotation(270);
								FlameSprite.setPosition(rocket.getX() + 10, rocket.getY());
								window.draw(FlameSprite);
							}
						if (event.key.code == Keyboard::D)
							if (rocket.getFuel() > 0)
							{
								rocket.setSidePower(2 * GRAVITY_ACCELERATION);
								FlameSprite.setRotation(90);
								FlameSprite.setPosition(rocket.getX() - 10, rocket.getY() - 40);
								window.draw(FlameSprite);
							}
						if (event.key.code == Keyboard::W)
							if (rocket.getFuel() > 0)
							{
								rocket.setCentralPower(-2 * GRAVITY_ACCELERATION);
								FlameSprite.setRotation(0);
								FlameSprite.setPosition(rocket.getX() - 20, rocket.getY());
								window.draw(FlameSprite);
							}
						if (event.key.code == Keyboard::S)
						{
							rocket.setCentralPower(2 * GRAVITY_ACCELERATION);

						}
					}
				}

				window.draw(ground);
				window.draw(landingField);

				RocketSprite.setPosition(rocket.getX() - 15, rocket.getY() - 72);
				window.draw(RocketSprite);
			}
			*/
			// always wwin
			else
			{
				window.clear(Color{ 41, 31, 92, 255 });
				if (rocket.getSidePower() > 0)
					rocket.setFuel(rocket.getFuel() - rocket.getSidePower());
				else if (rocket.getSidePower() < 0)
					rocket.setFuel(rocket.getFuel() + rocket.getSidePower());
				if (rocket.getCentralPower() < 0)
					rocket.setFuel(rocket.getFuel() + rocket.getCentralPower());
				rocket.setCentralPower(0);

				float l = landingFieldPosition - LANDING_FIELD_LENGHT - rocket.getX() ;
				float t = GRAVITY_ACCELERATION / (2 * WINDOW_HEIGHT - 80 - 2 * rocket.getY());
				rocket.setSidePower((l) * sqrt(t) - rocket.getVelocityX() + AIR_RESISTANCE);
			

				window.draw(ground);
				window.draw(landingField);

				RocketSprite.setPosition(rocket.getX() - 15, rocket.getY() - 72);
				window.draw(RocketSprite);
			}

			cout << "\n ROCKET LANDING GAME " << "\n Play with WASD buttons! \n";

			if (rocket.getFuel() >= 0)
			{
				cout << "\n FUEL: " << rocket.getFuel();
			}
			else
			{
				cout << "\n YOU'RE OUT OF FUEL! ";
			}

			cout << "\n\n COORDINATES: \n X: " << rocket.getX() << "; Y: " << rocket.getY() <<
				"\n\n VELOCITY: \n Vx: " << rocket.getVelocityX() << "; Vy: " << rocket.getVelocityY() <<
				"\n\n ACCELERATION: \n Ax: " << rocket.getSidePower() << "; Ay: " << rocket.getCentralPower() + GRAVITY_ACCELERATION;

			system("cls");
		}
		else if (game == WIN)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			window.clear(Color{ 41, 31, 92, 255 });

			window.draw(ground);
			window.draw(landingField);

			RocketSprite.setPosition(rocket.getX() - 15, rocket.getY() - 72);
			window.draw(RocketSprite);

			Texture WinTexture;
			WinTexture.loadFromFile("C:\\Users\\79292\\Desktop\\Project2\\images\\Win.png");
			WinTexture.setSmooth(true);
			Sprite WinSprite(WinTexture);
			WinSprite.setPosition(WINDOW_WIDTH / 2 - 172, WINDOW_HEIGHT / 2 - 49);
			window.draw(WinSprite);
		}
		else if (game == LOSE)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			ExplosionSprite.setPosition(rocket.getX() - 60, rocket.getY() - 100);
			clock_t t = clock();
			if ((t - tLose) % 50 == 0)
			{
				IntRect rectSourceSprite(96 * i, 96 * j, 96, 96);
				ExplosionSprite.setTextureRect(rectSourceSprite);
				i++;
				if (i == 5)
				{

					if (j != 3)
					{
						j++;
					}
					i = 0;
				}
			}
			window.clear(Color{ 41, 31, 92, 255 });

			window.draw(ground);
			window.draw(landingField);

			window.draw(ExplosionSprite);

			Texture LoseTexture;
			LoseTexture.loadFromFile("C:\\Users\\79292\\Desktop\\Project2\\images\\Lose.png");
			LoseTexture.setSmooth(true);
			Sprite LoseSprite(LoseTexture);
			LoseSprite.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 - 40);
			window.draw(LoseSprite);

		}

		window.display();
	}
	system("pause");
	return 0;
}
