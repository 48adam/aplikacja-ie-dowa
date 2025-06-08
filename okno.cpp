
#include "okno.h"
#include "UserManager.h"

void window::initLoginPanelUI()
{
	// Czcionka musi być już załadowana!
	this->panelTitle.setFont(this->font);
	this->panelTitle.setCharacterSize(28);
	this->panelTitle.setString("Tryb: Logowanie");
	this->panelTitle.setFillColor(sf::Color::Black);

	sf::FloatRect titleBounds = this->panelTitle.getLocalBounds();
	this->panelTitle.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
	this->panelTitle.setPosition(
		this->panel.getPosition().x + this->panel.getSize().x / 2,
		this->panel.getPosition().y + 20
	);

	// Login label
	this->loginLabel.setFont(this->font);
	this->loginLabel.setCharacterSize(20);
	this->loginLabel.setString("Login:");
	this->loginLabel.setFillColor(sf::Color::Black);
	this->loginLabel.setPosition(
		this->panel.getPosition().x + 30,
		this->panel.getPosition().y + 70
	);

	// Hasło label
	this->passwordLabel.setFont(this->font);
	this->passwordLabel.setCharacterSize(20);
	this->passwordLabel.setString("Hasło:");
	this->passwordLabel.setFillColor(sf::Color::Black);
	this->passwordLabel.setPosition(
		this->panel.getPosition().x + 30,
		this->panel.getPosition().y + 120
	);

	// Login input text
	this->loginInputText.setFont(this->font);
	this->loginInputText.setCharacterSize(20);
	this->loginInputText.setFillColor(sf::Color::Black);
	this->loginInputText.setPosition(this->loginLabel.getPosition().x + 100, this->loginLabel.getPosition().y);

	// Password input text
	this->passwordInputText.setFont(this->font);
	this->passwordInputText.setCharacterSize(20);
	this->passwordInputText.setFillColor(sf::Color::Black);
	this->passwordInputText.setPosition(this->passwordLabel.getPosition().x + 100, this->passwordLabel.getPosition().y);

	// Przycisk zmiany trybu (logowanie <-> rejestracja)
	modeButton.setSize(sf::Vector2f(150, 40));
	modeButton.setFillColor(sf::Color::Green);
	modeButton.setOutlineColor(sf::Color::Black);
	modeButton.setOutlineThickness(2);

	// Pozycja np. na dole panelu
	modeButton.setPosition(
		panel.getPosition().x + panel.getSize().x / 2 - 75,
		panel.getPosition().y + panel.getSize().y - 60
	);

	// Tekst przycisku
	modeButtonText.setFont(font);
	modeButtonText.setCharacterSize(18);
	modeButtonText.setFillColor(sf::Color::Black);
	modeButtonText.setString("Zmień tryb");

	// Wyśrodkowanie tekstu w przycisku
	sf::FloatRect textBounds = modeButtonText.getLocalBounds();
	modeButtonText.setOrigin(textBounds.width / 2, textBounds.height / 2);
	modeButtonText.setPosition(
		modeButton.getPosition().x + modeButton.getSize().x / 2,
		modeButton.getPosition().y + modeButton.getSize().y / 2 - 5
	);

}


void window::initpanel()
{
	this ->panel.setSize(sf::Vector2f(400, 500));
	panel.setFillColor(sf::Color(128, 128, 128, 150));
	panel.setOutlineColor(sf::Color::Black);
	panel.setOutlineThickness(2);
	panel.setPosition(
		(this->okno->getSize().x - this->panel.getSize().x) / 2,
		(this->okno->getSize().y - this->panel.getSize().y) / 2
	);


}

/// @brief Ładuje teksturę tła z pliku
void window::initbacgrundtexture()
{
	if (!backgroundTexture.loadFromFile("resources/background.jpg")) {
		std::cout << "nieda sie zaladowac obraska" << std::endl;
	}
}

/// @brief Inicjalizuje zmienne klasy (ustawia wskaźniki na nullptr)
void window::initialiseVariable()
{
	this->zalogowano = false;
	this->okno = nullptr;
}

/// @brief Tworzy główne okno aplikacji i ustawia jego parametry
void window::initWindow()
{
	this->VideoMode.width = 1500;
	this->VideoMode.height = 900;
	this->okno = new sf::RenderWindow(this->VideoMode, "aplikacja gieldowa",
		sf::Style::Titlebar | sf::Style::Close);
	this->okno->setFramerateLimit(60);
}


/// @brief Inicjalizuje tekst wyświetlany na ekranie
void window::intttext()
{
	this->uitext.setFont(this->font);
	this->uitext.setCharacterSize(32);
	this->uitext.setFillColor(sf::Color::White);

	
}

/// @brief Ładuje czcionkę z pliku
void window::init_font()
{
	if (!this->font.loadFromFile("resources/sansation.ttf")) {
		std::cout << "ladowanie sie nie powiodł" << std::endl;
	}
}

/// @brief Ustawia sprite tła i dopasowuje jego rozmiar do wielkości okna
void window::inittexturerender()
{
	this->backgroundSprite.setTexture(backgroundTexture);

	sf::Vector2u textureSize = backgroundTexture.getSize();
	sf::Vector2u windowSize = this->okno->getSize();

	if (textureSize.x == 0 || textureSize.y == 0) {
		std::cout << "Błąd: rozmiar tekstury to 0x0 – nie skaluję." << std::endl;
		return;
	}

	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	this->backgroundSprite.setScale(scaleX, scaleY);
}

void window::startUpdateThread() {
	running1 = true;

	updateThread = std::thread([this] {
		while (running1.load()) {
			std::this_thread::sleep_for(std::chrono::seconds(30));
			if (!running1.load()) break;

			std::cout << "[WĄTEK] Aktualizacja akcji...\n";
			market.update();
		}
		});

}



/// @brief Konstruktor klasy window – inicjalizuje wszystkie elementy okna
window::window() : userManager("users.txt")
{


	
	this->initialiseVariable();
	this->initWindow();
	this->init_font();
	this->initbacgrundtexture();
	this->inittexturerender();
	this->intttext();
	this->initpanel();
	this->initLoginPanelUI();
}

/// @brief Destruktor klasy window – zwalnia pamięć
window::~window()
{
	running1 = false;
	if (updateThread.joinable()) {
		updateThread.join();
	}

	delete this->okno;
}

/// @brief Sprawdza, czy okno aplikacji nadal działa (jest otwarte)
/// @return true jeśli okno jest otwarte, false jeśli zamknięte
const bool window::running() const
{
	return this->okno->isOpen();
}

void window::handleTextInput(const sf::Event& e)
{
	if (e.text.unicode < 128)
	{
		char entered = static_cast<char>(e.text.unicode);

		if (entered == '\b') { // backspace
			if (writingLogin && !loginBuffer.empty())
				loginBuffer.pop_back();
			else if (!writingLogin && !passwordBuffer.empty())
				passwordBuffer.pop_back();
		}
		else if (entered == '\r') { // Enter
			if (writingLogin)
				writingLogin = false;
			else {
				processLoginOrRegister();   // wywołaj logikę
				writingLogin = true;        // wróć do loginu
				loginBuffer.clear();
				passwordBuffer.clear();
			}
		}
		else if (std::isprint(static_cast<unsigned char>(entered))) {
			if (writingLogin)
				loginBuffer += entered;
			else
				passwordBuffer += entered;
		}

		// aktualizuj tekst
		loginInputText.setString(loginBuffer);
		passwordInputText.setString(std::string(passwordBuffer.length(), '*'));
	}
}

void window::processLoginOrRegister()
{
	if (mode == LOGIN)
	{
		if (userManager.validateLogin(loginBuffer, passwordBuffer)) {
			market.loadStocks();
			market.update();
			startUpdateThread();     // <-- uruchomienie osobnego wątku
			mode = MARKET_VIEW;
		}



		else {
			this->panelTitle.setString("Błędny login lub hasło.");

		}
	}
	else if (mode == REGISTER)
	{
		if (!userManager.isValidEmail(loginBuffer)) {
			this->panelTitle.setString("Podaj prawidłowy adres e-mail.");
		}
		else if (userManager.userExists(loginBuffer)) {
			this->panelTitle.setString("Użytkownik już istnieje!");
		}
		else {
			userManager.registerUser(loginBuffer, passwordBuffer);
			this->panelTitle.setString("Rejestracja zakończona!");
		}
	}
}


void window::panelrysowanie(sf::RenderTarget& target)
{
	target.draw(panel);                // Tło panelu
	target.draw(panelTitle);          // Tytuł

	target.draw(loginLabel);          // "Login:"
	target.draw(loginInputText);      // Pole loginu

	target.draw(passwordLabel);       // "Hasło:"
	target.draw(passwordInputText);   // Pole hasła

	target.draw(modeButton);
	target.draw(modeButtonText);

}

void window::pollEvent()
{
	while (this->okno->pollEvent(this->wydarzenie))
	{
		switch (this->wydarzenie.type)
		{
		case sf::Event::Closed:
			this->okno->close();
			break;

		case sf::Event::TextEntered:
			this->handleTextInput(this->wydarzenie);
			break;

		case sf::Event::MouseButtonPressed:
		{
			if (wydarzenie.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePos = sf::Vector2f(
					static_cast<float>(wydarzenie.mouseButton.x),
					static_cast<float>(wydarzenie.mouseButton.y)
				);

				if (modeButton.getGlobalBounds().contains(mousePos)) {
					// Zmień tryb
					mode = (mode == LOGIN ? REGISTER : LOGIN);

					// Zmień tytułpanelu
					 this->panelTitle.setString(mode == LOGIN ? "Tryb: Logowanie" : "Tryb: Rejestracja");
					// Zmień tekst na przycisku
					modeButtonText.setString(mode == LOGIN ? "Rejestracja" : "Logowanie");

					// Wycentruj nowy tekst w przycisku
					sf::FloatRect textBounds = modeButtonText.getLocalBounds();
					modeButtonText.setOrigin(textBounds.width / 2, textBounds.height / 2);
					modeButtonText.setPosition(
						modeButton.getPosition().x + modeButton.getSize().x / 2,
						modeButton.getPosition().y + modeButton.getSize().y / 2 - 5
					);
				}

			}
			break;
		}
		case sf::Event::MouseWheelScrolled:
			if (wydarzenie.mouseWheelScroll.delta < 0) {
				// scroll w dół
				if (visibleStockIndex + stocksPerPage < market.getStocks().size())
					visibleStockIndex += stocksPerPage;
			}
			else if (wydarzenie.mouseWheelScroll.delta > 0) {
				// scroll w górę
				if (visibleStockIndex >= stocksPerPage)
					visibleStockIndex -= stocksPerPage;
			}
			break;



		}
	}
}

/// @brief Renderuje tło w oknie
void window::renderowanietła()
{
	this->okno->draw(backgroundSprite);

}

void window::okno_update()
{
	this->pollEvent();  // zawsze odczytaj zdarzenia

	
}

/// @brief Główna funkcja rysująca – czyści, rysuje elementy i wyświetla
void window::okno_render()
{
	if (mode == MARKET_VIEW)
		this->okno->clear(sf::Color::White); // białe tło po zalogowaniu
	else {
		this->okno->clear(sf::Color::Magenta);
		this->renderowanietła(); // tylko w trybie logowania
	}


	if (mode == LOGIN || mode == REGISTER)
		this->panelrysowanie(*this->okno);
	else if (mode == MARKET_VIEW)
		this->renderMarketUI(*this->okno);

	this->okno->display();
}
// Fragment renderMarketUI z ramką i przewijaniem
void window::renderMarketUI(sf::RenderTarget& target)
{
	// ====== 1. RenderTexture jako bufor ramki ======
	sf::RenderTexture contentTexture;
	contentTexture.create(400, 600); // rozmiar taki jak ramki
	contentTexture.clear(sf::Color::White); // tło białe


	const auto& stocks = market.getStocks();
	size_t maxIndex = std::min(visibleStockIndex + stocksPerPage, stocks.size());

	float ramkaHeight = 600.f;
	float lineSpacing = ramkaHeight / static_cast<float>(stocksPerPage); // np. 60px przy 10 akcjach
	float y = 30.f;

	for (size_t i = visibleStockIndex; i < maxIndex; ++i) {
		const auto& stock = stocks[i];

		sf::Text text;
		text.setFont(this->font);
		text.setCharacterSize(18);
		text.setFillColor(sf::Color::Black);
		text.setPosition(10.f, y);

		float change = stock.getCurrentPrice() - stock.getPreviousPrice();
		float changePercent = (change / stock.getPreviousPrice()) * 100.0f;

		std::stringstream ss;
		ss << stock.getSymbol() << " - "
			<< stock.getCurrentPrice() << " PLN ("
			<< (change >= 0 ? "+" : "") << std::fixed << std::setprecision(2)
			<< changePercent << "%)";

		text.setString(ss.str());
		contentTexture.draw(text);

		y += lineSpacing;
	}

	contentTexture.display();

	// ====== 2. Sprite z bufora i przesunięcie (scroll) ======
	sf::Sprite contentSprite(contentTexture.getTexture());
	contentSprite.setPosition(30.f, 30.f - scrollY); // RAMKA + scroll
	target.draw(contentSprite);

	// ====== 3. Ramka na wierzchu ======
	sf::RectangleShape frame;
	frame.setSize(sf::Vector2f(400.f, 600.f));
	frame.setFillColor(sf::Color::Transparent); // przezroczyste tło
	frame.setOutlineColor(sf::Color(100, 100, 100));
	frame.setOutlineThickness(4);
	frame.setPosition(30.f, 30.f);
	target.draw(frame);

	// ====== 4. Pasek przewijania ======
	sf::RectangleShape scrollbar;
	scrollbar.setSize(sf::Vector2f(8.f, 80.f));
	scrollbar.setFillColor(sf::Color(150, 150, 150));
	scrollbar.setPosition(430.f, 30.f + scrollY);
	target.draw(scrollbar);
}





