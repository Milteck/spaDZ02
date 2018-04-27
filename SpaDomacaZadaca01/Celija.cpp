#include "Celija.h"

Celija::Celija()
{
}

Celija::Celija(sf::RenderWindow * windowPointer)
{
	this->windowPointer = windowPointer;
}

void Celija::Draw()
{
	sf::RectangleShape rectangle(sf::Vector2f(16, 16));

	if (trenutnoStanje == Mrtva) {
		rectangle.setPosition(sf::Vector2f(x, y));
		rectangle.setFillColor(sf::Color(60, 60, 60));
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color(128, 128, 128));
	}
	else {
		rectangle.setPosition(sf::Vector2f(x, y));
		rectangle.setFillColor(bojaGeneracije);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color(128, 128, 128));
	}




	windowPointer->draw(rectangle);
}

void Celija::SetPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Celija::SetDisplayWindow(sf::RenderWindow * windowPointer)
{
	this->windowPointer = windowPointer;
}


void Celija::SetLife(StanjeCelije stanje)
{
	pricuvnoStanje = stanje;
}

void Celija::ApplyLife()
{
	trenutnoStanje = pricuvnoStanje;
}

StanjeCelije Celija::GetLife()
{
	return trenutnoStanje;
}

int Celija::GetPosX()
{
	return x;
}

int Celija::GetPosY()
{
	return y;
}

void Celija::NadiSusjede(Celija polje[50][50], int pozicijaJ, int pozicijaI)
{
	int susjedi = 0;
	int j = pozicijaI;
	int i = pozicijaJ;

	if (polje[j + 1][i].GetLife() == Ziva && j != 49) {
		susjedi++;
	}
	if (polje[j + 1][i+1].GetLife() == Ziva && j != 49 && i != 49) {
		susjedi++;
	}
	if (polje[j][i+1].GetLife() == Ziva && i != 49) {
		susjedi++;
	}
	if (polje[j - 1][i + 1].GetLife() == Ziva && j != 0 && i != 49) {
		susjedi++;
	}
	if (polje[j - 1][i].GetLife() == Ziva && j != 0) {
		susjedi++;
	}
	if (polje[j - 1][i - 1].GetLife() == Ziva && j != 0 && i != 0) {
		susjedi++;
	}
	if (polje[j][i - 1].GetLife() == Ziva && i != 0) {
		susjedi++;
	}
	if (polje[j + 1][i - 1].GetLife() == Ziva && j != 49 && i != 0) {
		susjedi++;
	}


	if (trenutnoStanje == Ziva && (susjedi == 2 || susjedi == 3)) {
		pricuvnoStanje = Ziva;
	}
	if (susjedi < 2 || susjedi > 3) {
		pricuvnoStanje = Mrtva;
	}
	if (trenutnoStanje == Mrtva && susjedi == 3) {
		pricuvnoStanje = Ziva;
	}
}

void Celija::SetGenBoja(sf::Color boja)
{
	bojaGeneracije = boja;
}

