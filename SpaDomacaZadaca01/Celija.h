#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

enum StanjeCelije
{
	Ziva, Mrtva
};

class Celija
{
public:
	
	Celija();
	Celija(sf::RenderWindow *windowPointer);
	void Draw();
	void SetPos(float x, float y);
	void SetDisplayWindow(sf::RenderWindow *windowPointer);
	void SetLife(StanjeCelije stanje);
	void ApplyLife();
	StanjeCelije GetLife();
	int GetPosX();
	int GetPosY();
	void NadiSusjede(Celija polje[50][50], int pozicijaJ, int pozicijaI);
	void SetGenBoja(sf::Color boja);

private:
	sf::RenderWindow *windowPointer;
	StanjeCelije trenutnoStanje = Mrtva;
	StanjeCelije pricuvnoStanje = Mrtva;
	float x = 0;
	float y = 0;
	sf::Color bojaGeneracije = sf::Color(0, 0, 0);
};

