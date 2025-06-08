#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
#include <cctype>  
#include <thread>
#include <atomic>

#include <SFML/Graphics.hpp>


#include "UserManager.h"
#include "StockMarket.h" 




class window 
{
private:

	//window 
	sf::RenderWindow* okno;
	sf::Event wydarzenie;
	sf::VideoMode VideoMode;
	sf::RectangleShape panel;
	sf::Text panelTitle;
	sf::RectangleShape modeButton;
	sf::Text modeButtonText;

	//podanie chas³a i loginu
	sf::Text loginLabel;
	sf::Text passwordLabel;

	sf::Text loginInputText;
	sf::Text passwordInputText;

	std::string loginBuffer;
	std::string passwordBuffer;

	bool writingLogin = true;
	////////////////////////////////////

	//resorses
	sf::Font font;

	//tekst 
	sf::Text uitext;

	// Za³aduj teksturê z pliku
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	UserManager userManager;   
	StockMarket market;

	enum Mode { LOGIN, REGISTER, MARKET_VIEW };
	Mode mode = LOGIN;
	bool zalogowano;
	float scrollY = 0.f; // pozycja przewiniêcia

	size_t visibleStockIndex = 0;      // indeks pierwszej widocznej akcji
	const size_t stocksPerPage = 10;   // ile pokazywaæ na raz


	//dotyczy aktualizacji akcji co 30sek
	sf::Clock updateClock;
	const sf::Time updateInterval = sf::seconds(30.f);  // co 30 sekund
	std::thread updateThread;
	std::atomic<bool> running1 = false;

	//prywatne funkcje
	void initLoginPanelUI();
	void initpanel();
	void initbacgrundtexture();
	void initialiseVariable();
	void initWindow();
	void intttext();
	void init_font();
	void inittexturerender();
	

public: 

	//konstruktor i destruktor
	window() ;
	virtual ~window();

	//akcesorie
	const bool running() const;

	//funkcje 
	void startUpdateThread();
	void handleTextInput(const sf::Event& e);
	void processLoginOrRegister();
	void panelrysowanie(sf::RenderTarget& target);
	void pollEvent();
	void renderowaniet³a();
	void okno_update();
	void okno_render();
	void renderMarketUI(sf::RenderTarget& target);
};

