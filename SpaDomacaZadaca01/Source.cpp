#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include "Celija.h"
#include <ctime>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Igra Zivota");
	window.setFramerateLimit(60);

	sf::Clock SatSimulacija;
	float brzinaSimulacije = 1.0f; // 1x brzina
		
	int StanjeIgre = -1; // -1 pauzirano 1 pokrenuto
	srand(time(NULL));

	int Generacija = 0; // Koliko generacija smo prosli
	sf::Color bojaGeneracije = sf::Color(0, 0, 0);

	Celija testCelija(&window);
	
	vector<Celija> sveCelije;

	Celija poljeCelija[50][50];

	for (int i = 0; i < 800; i+=16)
	{
		for (int j = 0; j < 800; j+= 16)
		{
			Celija tempCelija(&window);
			tempCelija.SetPos(i, j);
			if (rand() % 100 < 25) {
				tempCelija.SetLife(Ziva);
			}
			else {
				tempCelija.SetLife(Mrtva);
			}
			tempCelija.ApplyLife();
			
			poljeCelija[j / 16][i / 16] = tempCelija;
		}
	}


#pragma region Stvaranje Teksta

	// Da bi koristili tekst moramo prvo ucitati neki font u program
	sf::Font font;
	if (!font.loadFromFile("Resursi/arial.ttf"))
	{
		return 1;
	}

	// Stvaramo text objekt i zadajemo mu neke osnovne postavke
	sf::Text text;
	text.setFont(font);
	text.setString("");
	text.setCharacterSize(24);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	std::stringstream ss; // Koristimo stringstream kako bi mogli sve informacije o cvijetu strpati u jedan string, tako mozemo koristiti samo jedan Text objekt
#pragma endregion





	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					StanjeIgre *= -1;
				}

				if (event.key.code == sf::Keyboard::W)
				{
					brzinaSimulacije++;
				}
				if (event.key.code == sf::Keyboard::S)
				{
					if (brzinaSimulacije > 1.0f)
					{
						brzinaSimulacije--;
					}
					
				}
			}
			if (sf::Event::MouseButtonPressed) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					int x = sf::Mouse::getPosition(window).x;
					int y = sf::Mouse::getPosition(window).y;
					for (int i = 0; i < 50; i++)
					{
						for (int j = 0; j < 50; j++)
						{
							if ((poljeCelija[i][j].GetPosX() <= x && poljeCelija[i][j].GetPosX() + 16 >= x) && (poljeCelija[i][j].GetPosY() <= y && poljeCelija[i][j].GetPosY() + 16 >= y)) {
									poljeCelija[i][j].SetLife(Ziva);
									poljeCelija[i][j].ApplyLife();
							}
						}
					}
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					int x = sf::Mouse::getPosition(window).x;
					int y = sf::Mouse::getPosition(window).y;
					for (int i = 0; i < 50; i++)
					{
						for (int j = 0; j < 50; j++)
						{
							if ((poljeCelija[i][j].GetPosX() <= x && poljeCelija[i][j].GetPosX() + 16 >= x) && (poljeCelija[i][j].GetPosY() <= y && poljeCelija[i][j].GetPosY() + 16 >= y)) {
								poljeCelija[i][j].SetLife(Mrtva);
								poljeCelija[i][j].ApplyLife();
							}
						}
					}
				}

			}
		}
		window.clear();

		sf::Time predenoVrijeme = SatSimulacija.getElapsedTime();
		if (predenoVrijeme.asSeconds() >=  2.0f / brzinaSimulacije)
		{
			if (StanjeIgre == 1) {
				Generacija++;
				for (int i = 0; i < 50; i++)
				{
					for (int j = 0; j < 50; j++)
					{
						poljeCelija[i][j].NadiSusjede(poljeCelija, j, i);
					}
				}

				for (int i = 0; i < 50; i++)
				{
					for (int j = 0; j < 50; j++)
					{
						poljeCelija[i][j].ApplyLife();
					}
				}


			}
			
			SatSimulacija.restart();
		}



		for (int i = 0; i < 50; i ++)
		{
			for (int j = 0; j < 50; j++)
			{
				poljeCelija[i][j].Draw();
			}
		}

		// U stringstream stavljamo sve podatke o igri koje zelimo prikazati
		if (StanjeIgre == 1)
		{
			ss << "Generacija: " << Generacija << endl << "Brzina Simulacije: " << brzinaSimulacije << "x" << " - Koristite W/S za brzinu"<< endl;
		}
		else {
			ss << "Generacija: " << Generacija << endl << "Brzina Simulacije: " << brzinaSimulacije << "x" << " - Koristite W/S za brzinu" << endl << "Pauzirano - prisinite P" << endl;
		}
		

		text.setString(ss.str());
		window.draw(text); // Crtanje teksta
		ss.str("");

		window.display();
	}

	return 0;
}